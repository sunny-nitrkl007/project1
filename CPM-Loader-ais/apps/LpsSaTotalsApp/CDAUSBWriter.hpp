#ifndef CDAUSBWRITER_HPP
#define CDAUSBWRITER_HPP

#include <iostream>
#include <memory>
#include <vector>
#include <tuple>
#include <iomanip>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <string>
#include <chrono>

#include <ais/log/Logger.h>
#include "fileio/oflocker.hpp"
#include <boost/asio.hpp>
#include <thread>         // std::thread

#ifdef GRPC_SUPPORTED
#include <CDASecureConfigs.h>
#include <grpc++/grpc++.h>

// include our generated files and setup our namespace
#include "CDAUSBWrite.pb.h"
#include "CDAUSBWrite.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using namespace CDA::USBWriter;
#endif

#include "fsa.h"
#include "LpsSaTotalsLoadHistory.h"

#define HOSTS_PATH "/etc/hosts"

#ifdef GRPC_SUPPORTED
class CDAUSBWriter {
public:
    CDAUSBWriter(LpsSaTotalsHistoryManager& historyManager) :
        cda_server_ip_address_(),
        port_(),
        init_thread_running_{false},
        worker_thread_running_{false},
        connection_established_{false},
        command_(),
        saveProgress_(),
        productId_("UNKNOWN"),
        historyManager_(historyManager) {}

    virtual ~CDAUSBWriter() = default;

    bool initCDAUSBWriter(std::string cda_server_ip_address, std::string port) {

        cda_server_ip_address_ = cda_server_ip_address;
        port_ = port;

        // spawn thread to establish CDA connection
        std::thread(&CDAUSBWriter::initCDAUSBThread, this).detach();

        return connection_established_;
    }
    bool isCDAConnectionEstablished() {
        return connection_established_;
    }

    enum USBSaveCmd {
        USB_CMD_CANCEL_SAVE,
        USB_CMD_SAVE_NEW,
        USB_CMD_SAVE_ALL,
    };

    enum USBSaveStatus {
        USB_SAVE_STATE_IN_PROCESS,
        USB_SAVE_STATE_COMPLETE,
        USB_SAVE_STATE_ERROR_GENERIC,
        USB_SAVE_STATE_ERROR_INSUFFICIENT_SPACE,
        USB_SAVE_STATE_ERROR_NO_USB_DETECTED,
        USB_SAVE_STATE_CANCELLED,
    };

    struct USBSaveProgress_t {
        uint8_t status = USB_SAVE_STATE_ERROR_GENERIC;
        int totalFiles = 0;
        int filesTransferred = 0;
    };

    const USBSaveProgress_t& getUSBSaveProgress(void) {
        return saveProgress_;
    }

    void setProductId(std::string productId) {
        productId_ = productId;
    }

    bool processUSBSaveCmd(USBSaveCmd cmd) {
        if (connection_established_) {
            command_ = cmd;
            if (worker_thread_running_) {
                /* a thread is already out there working, it will handle the new command */
            }
            else {
                /* We will spawn a thread to go process the cmd */
                std::thread(&CDAUSBWriter::processCmdThread, this).detach();
            }
        }
        else {
            saveProgress_.status = USB_SAVE_STATE_ERROR_GENERIC;
            AIS_LOG_ERROR("No Connection to CDA-USB Server");
            return false;
        }

        return true;
    }



private:
    bool appGetCDAServerDns( const std::string& ipAddr, std::string& CDAServerDns )
    {
       bool retVal = false;

       do {
           std::ifstream hostsFile( HOSTS_PATH, std::ios_base::in );
           if ( hostsFile.is_open() )
           {
               std::string nextLine;
               while ( getline( hostsFile, nextLine ) )
               {
                   std::string::size_type serverIpPos = nextLine.find( ipAddr );
                   if( std::string::npos != serverIpPos )
                   {
                       nextLine.erase( serverIpPos, ipAddr.length() );
                       // Erase spaces and tabs (Erase–remove idiom)
                       nextLine.erase( std::remove( nextLine.begin(), nextLine.end(), ' ' ), nextLine.end() );
                       nextLine.erase( std::remove( nextLine.begin(), nextLine.end(), '\t' ), nextLine.end() );
                       CDAServerDns = nextLine;
                       retVal = true;
                       break;
                   }
               }
               hostsFile.close();

               if (retVal) {
                   break;
               }
               else {
                   // retry after 10s
                   sleep(10);
                   AIS_LOG_ERROR("Host not found, retry forever");
               }
           }
           else {
               // retry after 10s
               sleep(10);
               AIS_LOG_ERROR("Not able to open hosts file, retry forever...");
           }
       } while (1);

       return retVal;
    }

    void initCDAUSBThread() {
        init_thread_running_ = true;
        AIS_LOG_INFO("Init CDA-USB Thread Started...");

        //Getting the DNS name of server to connect
        AIS_LOG_INFO("Getting the DNS name of the server");
        std::string DNSServerName;

        if( !appGetCDAServerDns(cda_server_ip_address_, DNSServerName))
        {
            AIS_LOG_ERROR("Error getting DNS name of the server. Exiting ...");
            init_thread_running_ = false;
            return;
        }

        AIS_LOG_INFO("CDA Server Found");

        //Adding the secure port in which server listens to client in the D6CX
        DNSServerName=DNSServerName+":"+port_;

        // Load the client certificate to be presented to server
        AIS_LOG_INFO("Loading the client public certificate to present to server");
        std::ifstream clientCert(HARDWARE_PUBLIC_CERTIFICATE);
        if(!clientCert.is_open())
        {
            AIS_LOG_ERROR("Error loading client public certificate. Exiting ...");
            init_thread_running_ = false;
            return;
        }

        std::stringstream clientCertStream;
        clientCertStream << clientCert.rdbuf();
        clientCert.close();

        // Load the client private identity
        AIS_LOG_INFO("Loading the client private key needed to securely communicate with server");
        std::ifstream clientPrivKey(HARDWARE_PRIVATE_KEY);
        if(!clientPrivKey.is_open())
        {
            AIS_LOG_ERROR("Error loading client private key %s. Exiting ...");
            init_thread_running_ = false;
            return;
        }
        std::stringstream clientPrivKeyStream;
        clientPrivKeyStream << clientPrivKey.rdbuf();
        clientPrivKey.close();

        // Load the CDA servers trusted ca chain
        AIS_LOG_INFO("Loading the servers trusted CA chain to trust the certificate presented by server");
        std::ifstream trustedCAChain(CDA_SERVER_CA_CERT_CHAIN_PATH);
        if(!trustedCAChain.is_open())
        {
            AIS_LOG_ERROR("Error loading servers trusted CA chain %s. Exiting ...");
            init_thread_running_ = false;
            return;
        }
        std::stringstream trustedCAChainStream;
        trustedCAChainStream << trustedCAChain.rdbuf();
        trustedCAChain.close();

        struct grpc::SslCredentialsOptions clientCredentialOpts;
        clientCredentialOpts.pem_root_certs=trustedCAChainStream.str();
        clientCredentialOpts.pem_private_key=clientPrivKeyStream.str();
        clientCredentialOpts.pem_cert_chain=clientCertStream.str();

        AIS_LOG_INFO("Connecting to CDA-Server...%s", DNSServerName.c_str());
        auto channelCredentials = grpc::SslCredentials(clientCredentialOpts);

        std::shared_ptr<Channel> channel = grpc::CreateChannel(DNSServerName.c_str(), channelCredentials);
        m_stub = USBWriter::NewStub(channel);

        connection_established_ = true;
        init_thread_running_ = false;
    }

    void processCmdThread() {
        worker_thread_running_ = true;
        AIS_LOG_INFO("Worker CDA-USB Process Cmd Thread Started...");

        switch (command_) {
        case USB_CMD_SAVE_ALL:
        case USB_CMD_SAVE_NEW: {
            saveProgress_.status = USB_SAVE_STATE_IN_PROCESS;

            // get # of files to send, pass the cmd (save all, save new)
            LpsSaTotalsHistoryManager::Iterator it;

            if (command_ == USB_CMD_SAVE_ALL) {
                saveProgress_.totalFiles = historyManager_.countAllFiles();
                it = historyManager_.iteratorAll();
            }
            else
            {
                saveProgress_.totalFiles = historyManager_.countNewFiles();
                it = historyManager_.iteratorNew();
            }

            AIS_LOG_INFO("countFiles: %d", saveProgress_.totalFiles);

            saveProgress_.filesTransferred = 0;

            // sleep for a 1 second and exit if no files to save
            if (0 == saveProgress_.totalFiles) {
                sleep(1);
                saveProgress_.status = USB_SAVE_STATE_COMPLETE;
                worker_thread_running_ = false;
                return;
            }

            // loop # of files to send
            for (; it != it.end(); ++it) {

                LpsSaTotalsHistoryStorage loadHistory;
                it.getLoadHistory(loadHistory);
                LpsSaTotalsPrinterInfo tmp;
                std::stringstream strStream;
                loadHistory.toCsv(strStream, tmp);

                int retry = 3;  // initialize to 3 for every file

                // send file
                do {
                    USBWriteCommand request;
                    USBWriteStatus response;
                    ClientContext context;
                    Status status;

                    std::string filename = it.getPath().stem().string() + ".csv";
                    request.set_file_name(filename.c_str());
                    request.set_directory(productId_.c_str());
                    request.set_file_contents(strStream.str());
                    request.set_usb_command(USBWriteCommand_COMMAND_USB_FILE_WRITE);

                    // set timeout - need to be discussed. There are 3 retries so this could be potentially
                    //  30secs delay for user feedback. It takes ~2.7secs per 1MB file so 10secs is ~3x of that
                    //  There could potentially be slower USB sticks which may take longer??
                    context.set_deadline(std::chrono::system_clock::now() + std::chrono::seconds(10));

                    status = m_stub->SubmitFileToUSBSynchronous(&context, request, &response);

                    // update saveProgress, check for grpc response to either retry, abort or continue
                    if (status.ok()) {
                        switch (response.usb_device_status()) {
                        case USBWriteStatus_STATUS_USB_WRITE_SUCCESS:
                            retry=0;
                            saveProgress_.filesTransferred++;
                            AIS_LOG_INFO("Successfully saved: %s", filename.c_str());
                            break;

                        case USBWriteStatus_STATUS_USB_FILE_NAME_MISSING:
                        case USBWriteStatus_STATUS_USB_FILE_SIZE_EXCEEDED:
                            AIS_LOG_ERROR("Failed to Save File with Error(moving on to next file):%d", response.usb_device_status());
                            // move on to next file
                            retry=0;
                            break;

                        case USBWriteStatus_STATUS_USB_DEVICE_NOT_DETECTED:
                        case USBWriteStatus_STATUS_USB_DEVICE_MOUNT_FAILED:
                            // abort save
                            saveProgress_.status = USB_SAVE_STATE_ERROR_NO_USB_DETECTED;
                            AIS_LOG_ERROR("Failed to Save File with Error(Aborting): USB_SAVE_STATE_ERROR_NO_USB_DETECTED");
                            unmountUSB();
                            worker_thread_running_ = false;
                            return;
                            break;

                        case USBWriteStatus_STATUS_USB_DEVICE_FULL_ERROR:
                            // abort save
                            saveProgress_.status = USB_SAVE_STATE_ERROR_INSUFFICIENT_SPACE;
                            AIS_LOG_ERROR("Failed to Save File with Error(Aborting): USBWriteStatus_STATUS_USB_DEVICE_FULL_ERROR");
                            unmountUSB();
                            worker_thread_running_ = false;
                            return;
                            break;

                        case USBWriteStatus_STATUS_USB_WRITE_ERROR:
                        case USBWriteStatus_STATUS_USB_DEVICE_BUSY:
                            // these are times we will retry
                            AIS_LOG_ERROR("Retrying - Failed to Save File with Error Code (Retrying):%d", response.usb_device_status() );
                            usleep(100000); //sleep for 100ms between retries
                            retry--;

                            // if we are done retrying set error and exit
                            if (!retry) {
                                AIS_LOG_ERROR("Exiting - Failed to Save File with Error Code (Retrying):%d", response.usb_device_status() );
                                saveProgress_.status = USB_SAVE_STATE_ERROR_GENERIC;
                                unmountUSB();
                                worker_thread_running_ = false;
                                return;
                            }

                            break;

                        default:
                            // all other errors, abort save
                            saveProgress_.status = USB_SAVE_STATE_ERROR_GENERIC;
                            AIS_LOG_ERROR("Failed to Save File with Error Code (Aborting):%d", response.usb_device_status() );
                            unmountUSB();
                            worker_thread_running_ = false;
                            return;
                            break;
                        }
                    }
                    else {
                        // grpc failed, retry
                        AIS_LOG_ERROR("Retrying - GRPC failed with error message: %s, Error Code:%d", status.error_message().c_str(), status.error_code());
                        usleep(100000); //sleep for 100ms between retries
                        retry--;

                        // if we are done retrying set error and exit
                        if (!retry) {
                            AIS_LOG_ERROR("Exiting - GRPC failed with error message: %s, Error Code:%d", status.error_message().c_str(), status.error_code());
                            saveProgress_.status = USB_SAVE_STATE_ERROR_GENERIC;
                            unmountUSB();
                            worker_thread_running_ = false;
                            return;
                        }
                    }
                } while (retry);

                // check to see if cancel command has been received
                if (command_ == USB_CMD_CANCEL_SAVE) {
                    // abort file transfer
                    saveProgress_.status = USB_SAVE_STATE_CANCELLED;
                    AIS_LOG_INFO("Received and Processed Cancel Save Command");
                    unmountUSB();
                    worker_thread_running_ = false;
                    return;
                }
            }

            break;
        }
        case USB_CMD_CANCEL_SAVE:
            // Nothing to cancel, should never get here
            AIS_LOG_ERROR("Nothing to Cancel");
            worker_thread_running_ = false;
            return;
            break;

        default:
            // Should never get here
            AIS_LOG_ERROR("Invalid Command received");
            worker_thread_running_ = false;
            return;
            break;
        }

        // when we get here, we have successfully saved the files, just make sure we are able to unmount
        if (unmountUSB()) {
            historyManager_.updateLastDownloadTime();
            saveProgress_.status = USB_SAVE_STATE_COMPLETE;
        }
        else {
            saveProgress_.status = USB_SAVE_STATE_ERROR_GENERIC;
        }

        worker_thread_running_ = false;
    }

    bool unmountUSB() {
        int retry = 3;
        bool success = false;

        do {
            USBWriteCommand request;
            USBWriteStatus response;
            ClientContext context;
            Status status;

            request.set_file_name("");
            request.set_directory("");
            request.set_file_contents("");
            request.set_usb_command(USBWriteCommand_COMMAND_USB_DEVICE_UNMOUNT);

            context.set_deadline(std::chrono::system_clock::now() + std::chrono::seconds(5));

            status = m_stub->SubmitFileToUSBSynchronous(&context, request, &response);

            // update saveProgress, check for grpc response to either retry, abort or continue
            if (status.ok()) {
                retry = 0; // no retries needed, CDA has internal retries for un-mounting
                switch (response.usb_device_status()) {
                case USBWriteStatus_STATUS_USB_DEVICE_UNMOUNTED:
                    AIS_LOG_INFO("USB_DEVICE_UNMOUNTED");
                    success = true;
                    break;

                case USBWriteStatus_STATUS_USB_DEVICE_UNMOUNT_FAILED:
                    AIS_LOG_ERROR("USB_DEVICE_UNMOUNT_FAILED");
                    break;

                default:
                    // all other errors
                    AIS_LOG_ERROR("Failed to unmount?:%d", response.usb_device_status() );
                    break;
                }
            }
            else {
                // grpc failed, retry
                AIS_LOG_ERROR("Retrying Unmount - GRPC failed with error message: %s, Error Code:%d", status.error_message().c_str(), status.error_code());
                usleep(100000); //sleep for 100ms between retries
                retry--;
            }

        } while (retry);

        return success;
    }

    std::string cda_server_ip_address_;
    std::string port_;
    bool init_thread_running_;
    bool worker_thread_running_;
    bool connection_established_;
    USBSaveCmd command_;
    USBSaveProgress_t saveProgress_;
    std::string productId_;
    LpsSaTotalsHistoryManager& historyManager_;

    std::unique_ptr<USBWriter::Stub> m_stub;
};
#endif /* GRPC_SUPPORTED */

#endif /* CDAUSBWRITER_HPP */
