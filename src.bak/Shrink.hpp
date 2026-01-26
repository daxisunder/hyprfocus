#include "IFocusAnimation.hpp"

class CShrink : public IFocusAnimation {
public:
  void onWindowFocus(PHLWINDOW pWindow, HANDLE pHandle) override;
  void init(HANDLE pHandle, std::string animationName) override;
  void setup(HANDLE pHandle, std::string animationName) override;

  PHLANIMVAR<float> m_sShrinkAnimation;
};
