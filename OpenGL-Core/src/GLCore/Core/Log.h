#pragma once

#include "GLCore/Core/Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace GLCore {

    class Log
    {
    public:
        static void Init();

        static Ref<spdlog::logger>& GetLogger() { return s_Logger; }
    private:
        static Ref<spdlog::logger> s_Logger;
    };

}

// TODO: strip in distribution versions
// TODO: pass in __LINE__ and __FILE__

#define LOG_TRACE(...)         ::GLCore::Log::GetLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)          ::GLCore::Log::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)          ::GLCore::Log::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)         ::GLCore::Log::GetLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...)      ::GLCore::Log::GetLogger()->critical(__VA_ARGS__)