#ifndef LPSSATOTALSLASTSTOREDTRUCKMESSAGE_H
#define LPSSATOTALSLASTSTOREDTRUCKMESSAGE_H

#include <interfaces/LpsSaLoadRecordChannel/LpsSaLoadRecordChannel.h>
#include <ext/rapidjson/RapidJsonGuarded.h>
#include <chrono/print.hpp>

#include <sys/types.h>
#include <unistd.h>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <thread>
#include <iostream>

namespace LastTruckMessage {
    inline bool sendLastTruckMessage(const boost::filesystem::path& filePath, const LpsSaLoadRecordChannel& loadRecord, const std::string& ip,
            uint32_t port, const std::string& productId) {

        auto subtotalCount = loadRecord.subtotalCount();
        bool sentFile = true;

        for (uint32_t x=1; x<=subtotalCount; ++x) {
            const auto& subtotal = loadRecord.getSubtotalByIndex(x);

            bool createdFile = false;

            { // Create the file to send
                std::ofstream fp (filePath.c_str(), std::ofstream::out | std::ofstream::trunc);
                if (fp) {
                    bool autoStore = (LpsSaLoadRecordStoreAction::AUTO == loadRecord.storeAction());
                    rapidjson::StringBuffer sb;
                    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer{ sb };
                    writer.SetIndent(' ', 2);
                    writer.SetMaxDecimalPlaces(2);
                    writer.StartObject();
                    writer.Key("autoStore"); writer.tBool(autoStore);
                    writer.Key("serialNumber"); writer.String(productId);
                    writer.Key("truckName"); writer.String(subtotal.truckName);
                    writer.Key("truckId"); writer.Uint(subtotal.truckId);
                    writer.Key("truckTargetWeight"); writer.Double(subtotal.truckTargetWeightTonnes);
                    writer.Key("totalWeight"); writer.Double(subtotal.weightTonnes());
                    writer.Key("materialName"); writer.String(subtotal.materialName);
                    writer.Key("materialId"); writer.Uint(subtotal.materialId);
                    writer.Key("materialDensity"); writer.Double(subtotal.materialDensity);
                    writer.Key("tag1"); writer.String(subtotal.tag1);
                    writer.Key("tag2"); writer.String(subtotal.tag2);
                    writer.Key("tag3"); writer.String(subtotal.tag3);
                    writer.Key("tag4"); writer.String(subtotal.tag4);
                    writer.Key("numPasses"); writer.Uint(subtotal.passCount());
                    writer.Key("printerTicketNumber"); writer.Uint(loadRecord.ticketNumber());
                    writer.Key("startTime"); writer.String(tes_common_ais::putTime(subtotal.startTime.utcTime, "%FT%TZ"));
                    writer.Key("endTime"); writer.String(tes_common_ais::putTime(subtotal.endTime.utcTime, "%FT%TZ"));
                    writer.Key("passes");
                    writer.StartArray();
                    for (const auto& t : subtotal.passes()) {
                        writer.StartObject();
                        writer.Key("time"); writer.String(tes_common_ais::putTime(t.time.utcTime, "%FT%TZ"));
                        writer.Key("weight"); writer.Double(t.weightTonnes);
                        writer.EndObject();
                    }
                    writer.EndArray();
                    writer.EndObject();
                    if (writer.IsComplete()) {
                        fp << sb.GetString();
                        createdFile = true;
                    }
                    else {
                        AIS_LOG_ERROR("Incomplete json document, cannot write.");
                    }
                    fp.close();
                }
                else {
                    AIS_LOG_ERROR("Could not open %s for write access.", filePath.c_str());
                }
            }

            if (createdFile) {
                try {
                    boost::asio::io_service io_service;
                    boost::asio::ip::udp::socket sock(io_service);
                    boost::asio::ip::udp::endpoint destination_ = boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(ip), port);

                    // Setting destination ip address and port
                    sock.open(boost::asio::ip::udp::v4()); // Opening socket

                    std::ifstream fp(filePath.c_str());
                    std::string data((std::istreambuf_iterator<char>(fp)), (std::istreambuf_iterator<char>())); // Read data from file
                    fp.close();

                    sock.send_to(boost::asio::buffer(data), destination_); // Sending data
                    sock.close(); // Closing socket
                    io_service.stop(); // This will close if any thread running due to io_service

                }
                catch (const std::exception& error) {
                    AIS_LOG_ERROR("Failed to send data over UDP due to %s", error.what());
                    sentFile = false;
                }
            }
            else {
                // File was not created, hence not sent
                sentFile = false;
            }
        }

        return sentFile;
    }
};

#endif
