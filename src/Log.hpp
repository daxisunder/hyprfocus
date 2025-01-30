#pragma once
#define WLR_USE_UNSTABLE
#include <hyprland/src/debug/Log.hpp>

template <typename... Args>
void hyprfocus_log(LogLevel level, std::format_string<Args...> fmt,
                   Args &&...args) {
  auto msg = std::vformat(fmt.get(), std::make_format_args(args...));
  Debug::log(level, "[hyprfocus] {}", msg);
}
