#include <string>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <signal.h>


int main(int argc, char *argv[])
{
    int rval;
    sigset_t set;
    int sig;

    /*
     * Block SIGTERM and wait for it to come.
     */
    sigemptyset(&set);
    sigaddset(&set, SIGTERM);
    sigprocmask(SIG_BLOCK, &set, NULL);
    sigwait(&set, &sig);
    sigprocmask(SIG_UNBLOCK, &set, NULL);

    { // Execute stuff on TERM
        char* catDir = getenv("CAT_DIR");
        std::string command;
        if (nullptr != catDir) {
            command = catDir;
        }
        else {
            command = ".";
        }

        command += "/scripts/queue_app_logs_to_ftb.sh";

        rval = std::system(command.c_str());
    }

    return rval;
}
