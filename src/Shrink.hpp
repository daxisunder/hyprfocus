#pragma once

#include "IFocusAnimation.hpp"

class CShrink : public IFocusAnimation {
public:
  void init(HANDLE pHandle, std::string animationName) override;
  void setup(HANDLE pHandle, std::string animationName) override;
  void onWindowFocus(PHLWINDOW pWindow, HANDLE pHandle) override;
};
