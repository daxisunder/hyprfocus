#include "Shrink.hpp"
#include "Log.hpp"

void CShrink::init(HANDLE pHandle, std::string animationName) {
  IFocusAnimation::init(pHandle, "shrink");
}

void CShrink::setup(HANDLE /*pHandle*/, std::string /*animationName*/) {}

void CShrink::onWindowFocus(PHLWINDOW /*pWindow*/, HANDLE /*pHandle*/) {
  hyprfocus_log(
      Log::WARN,
      "The shrink animation is disabled until fix for Hyprland 0.56.");
}
