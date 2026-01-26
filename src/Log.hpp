#pragma once
#define WLR_USE_UNSTABLE
#include <hyprland/src/debug/log/logger.hpp>

template <typename... Args>
void hyprfocus_log(Hyprutils::CLI::eLogLevel level, std::format_string<Args...> fmt,
                   Args &&...args) {
  auto msg = std::vformat(fmt.get(), std::make_format_args(args...));
  Log::Logger->log(level, "[hyprfocus] {}", msg);
}
