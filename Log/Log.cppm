module;
#include <print>
#include <iostream>
#include <source_location>

#include <chrono>
#include <iomanip>
#include <sstream>

export module Log;
import Constants;

std::string getDateTime(bool get_ms) {
    // Get the current time as a time_point
    auto now = std::chrono::system_clock::now();
    
    // Convert to time_t for formatting
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    // Convert to tm structure
    std::tm now_tm = *std::gmtime(&now_time_t);

    // Create a string stream to format the time
    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%F %T");

    if (get_ms) {
        // Get the milliseconds part
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
        oss << '.' << std::setw(3) << std::setfill('0') << milliseconds.count();
    }

    return oss.str();
}

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
        if (Print::time) {
            std::cout << getDateTime(true) << " ";
        }

        if (Print::log_level) {
            std::cout << get_level_name(ll) << " ";
        }

        if (Print::source::location) {
            using namespace Print::source;
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
