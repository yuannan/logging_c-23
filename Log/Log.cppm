module;
#include <print>
#include <iostream>
#include <source_location>
export module Log;
import Constants;

using namespace Constants::SplLog;

export namespace Log {
    enum Level {
        TRACE = 0,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        CRITICAL,
        OFF,
        LOG_LEVEL_NUM
    };

    constexpr std::string Level_Names[Level::LOG_LEVEL_NUM] = {
        "TRACE",
        "DEBUG",
        "INFO",
        "WARN",
        "ERROR",
        "CRITICAL",
        "OFF",
    };

    constexpr std::string get_level_name (Log::Level ll) {
        return Level_Names[ll];
    }

    template <typename... Ts>
    void log_manual(Level ll, const std::source_location& cl, const std::format_string<Ts...> fmt, Ts&&... as) {
        using namespace Print;
        if (log_level) {
            std::cout << get_level_name(ll) << " ";
        }

        using namespace source;
        if (location) {
            if (file) {
                std::cout << cl.file_name() << " ";
            }

            // Start of [line:col]
            if (line | col) {
                std::cout << "[";
            }

            if (line) {
                std::cout << cl.line();
            }

            // Middle of [line:col]
            if (line | col) {
                std::cout << ":";
            }

            if (col) {
                std::cout << cl.column();
            }

            // End of [line:col]
            if (line | col) {
                std::cout << "] ";
            }

            if (function) {
                std::cout << cl.function_name() << " ";
            }
        }

        std::print(fmt, std::forward<Ts>(as)...);
    }

    template <typename... Ts>
    struct debug
    {
        debug(const std::format_string<Ts...> fmt, Ts&&... as, const std::source_location& loc = std::source_location::current()) {
            Log::log_manual(Level::DEBUG, loc, fmt, std::forward<Ts>(as)...);
        }
    };
    template <typename... Ts>
    debug(const std::format_string<Ts...>, Ts&&...) -> debug<Ts...>;
};
