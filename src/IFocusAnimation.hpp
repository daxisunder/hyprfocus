#pragma once

#include <hyprlang.hpp>
#define WLR_USE_UNSTABLE

#include <hyprland/src/config/ConfigManager.hpp>
#include <hyprland/src/config/values/types/FloatValue.hpp>
#include <hyprland/src/config/values/types/StringValue.hpp>
#include <hyprland/src/plugins/PluginAPI.hpp>
#include <hyprutils/animation/AnimationConfig.hpp>

using namespace Hyprutils::Memory;
using namespace Hyprutils::Animation;

class IFocusAnimation {
public:
  virtual ~IFocusAnimation() = default;

  // Called when a window gains focus.
  virtual void onWindowFocus(PHLWINDOW pWindow, HANDLE pHandle);
  // Called once when the animation type is created.
  virtual void init(HANDLE pHandle, std::string animationName);
  // Optional per-animation setup hook.
  virtual void setup(HANDLE pHandle, std::string animationName);

  // V2 API: register plugin-owned values.
  SP<Config::Values::CFloatValue>
  registerFloat(HANDLE pHandle, const std::string &name, float def);
  SP<Config::Values::CStringValue> registerString(HANDLE pHandle,
                                                  const std::string &name,
                                                  const std::string &def);

  // V1-style helpers (used by CShrink).
  void addConfigValue(HANDLE pHandle, const std::string &name,
                      Hyprlang::CConfigValue value);
  Hyprlang::CConfigValue *getConfigValue(HANDLE pHandle,
                                         const std::string &name);

public:
  // Animation property configs cloned from the global animation settings.
  SP<SAnimationPropertyConfig> m_sFocusInAnimConfig;
  SP<SAnimationPropertyConfig> m_sFocusOutAnimConfig;

  std::string m_szAnimationName;

  // Per-animation config values (V2).
  SP<Config::Values::CStringValue> m_pInBezier;
  SP<Config::Values::CStringValue> m_pOutBezier;
  SP<Config::Values::CFloatValue> m_pInSpeed;
  SP<Config::Values::CFloatValue> m_pOutSpeed;

  // String storage so the const char* in the IValue stays valid.
  std::vector<std::string> m_configNames;

  std::string configPrefix() const {
    return std::string("plugin:hyprfocus:") + m_szAnimationName + ":";
  }
};
