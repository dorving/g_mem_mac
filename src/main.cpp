#include <sys/proc_info.h>
#include <libproc.h>
#include "process/mac/MacProcess.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"

pid_t find_pids(const char *name)
{
    spdlog::info("Looking for process with name {}...", name);
    pid_t pids[2048];
    size_t bytes = proc_listpids(PROC_ALL_PIDS, 0, pids, sizeof(pids));
    size_t n_proc = bytes / sizeof(pids[0]);

    for (int i = 0; i < n_proc; i++) {
        struct proc_bsdinfo proc{};
        size_t st = proc_pidinfo(pids[i], PROC_PIDTBSDINFO, 0,
                              &proc, PROC_PIDTBSDINFO_SIZE);
        if (st == PROC_PIDTBSDINFO_SIZE) {
            if (strcmp(name, proc.pbi_name) == 0) {
                /* Process PID */
                spdlog::info("-> Found process: {} [{}] [{}]\n", pids[i], proc.pbi_comm, proc.pbi_name);
                return pids[i];
            }
        }
    }
    spdlog::error("-> Did not find process, exiting...");
    exit(EXIT_FAILURE);
}

void setDefaultLogger(const spdlog::filename_t &logFile)
{

    // Create a file rotating logger with 5mb size max and 3 rotated files
    auto max_size = 1048576 * 5;
    auto max_files = 3;
    auto logger = spdlog::rotating_logger_mt("g_mem", logFile, max_size, max_files);
    spdlog::set_default_logger(logger);
}

int main()
{
    std::string cacheDir = std::string(getenv("HOME")) + "/.g_mem";
    std::string logDir = cacheDir + "/logs/rotating.log";

    spdlog::debug("Setting cache directory as {}", cacheDir);
    spdlog::debug("Subsequent log output will be saved to {}", logDir);

    setDefaultLogger(logDir);

    pid_t habbo_pid = find_pids("Habbo");

    spdlog::info("Attempting to connect to Habbo process with pid {}", habbo_pid);

    auto habbo_process = new MacProcess(habbo_pid);

    habbo_process->printRC4Possibilities();
    return 0;
}
