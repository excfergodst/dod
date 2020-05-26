#include "Rish/Core/Log.h"
#include "Rish/Config.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/dup_filter_sink.h>

namespace rl {

/// TODO: make imgui sink

std::shared_ptr<spdlog::logger> Logger::CoreLogger;
std::shared_ptr<spdlog::logger> Logger::ClientLogger;

void Logger::Init()
{
    // Create sinks (stdout, file)
    std::vector<spdlog::sink_ptr> logSinks;
    logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("dod.log", true));

    auto duplicateFilter = std::make_shared<spdlog::sinks::dup_filter_sink_mt>(std::chrono::seconds(1));

    for(auto &i : logSinks)
    {
        duplicateFilter->add_sink(i);
    }

    // Set pattern: "[time] [cat] [level]: texts"
    logSinks[0]->set_pattern("[%T] [%n/%^%l%$] %v");
    logSinks[1]->set_pattern("[%T] [%n/%^%l%$] %v");
    // Create engine logger
    CoreLogger = std::make_shared<spdlog::logger>("Engine", duplicateFilter);
    spdlog::register_logger(CoreLogger);
    CoreLogger->set_level(spdlog::level::trace);
    CoreLogger->flush_on(spdlog::level::trace);
    // Create app logger
    ClientLogger = std::make_shared<spdlog::logger>("App", duplicateFilter);
    spdlog::register_logger(ClientLogger);
    ClientLogger->set_level(spdlog::level::trace);
    ClientLogger->flush_on(spdlog::level::trace);
}

const char *GetSrcFileRelativePath(const char *path)
{
    return strstr(path, SOURCE_DIR_PATH) ?
        (path + SOURCE_DIR_PATH_LEN) :
        (nullptr);
}

}