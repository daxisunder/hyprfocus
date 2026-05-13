#include "IFocusAnimation.hpp"
#include "Globals.hpp"

#include <hyprland/src/config/shared/animation/AnimationTree.hpp>
#include <hyprland/src/plugins/PluginAPI.hpp>
#include <hyprlang.hpp>

SP<Config::Values::CFloatValue>
IFocusAnimation::registerFloat(HANDLE pHandle, const std::string &name,
                               float def) {
  m_configNames.emplace_back(name);
  auto v = makeShared<Config::Values::CFloatValue>(m_configNames.back().c_str(),
                                                   "hyprfocus plugin value",
                                                   (Config::FLOAT)def);
  HyprlandAPI::addConfigValueV2(pHandle, v);
  return v;
}

SP<Config::Values::CStringValue>
IFocusAnimation::registerString(HANDLE pHandle, const std::string &name,
                                const std::string &def) {
  m_configNames.emplace_back(name);
  auto v = makeShared<Config::Values::CStringValue>(
      m_configNames.back().c_str(), "hyprfocus plugin value", def);
  HyprlandAPI::addConfigValueV2(pHandle, v);
  return v;
}

void IFocusAnimation::init(HANDLE pHandle, std::string animationName) {
  m_szAnimationName = std::move(animationName);
  hyprfocus_log(Log::INFO, "Initializing focus animation: {}",
                m_szAnimationName);

  m_pInBezier =
      registerString(pHandle, configPrefix() + "in_bezier", "default");
  m_pOutBezier =
      registerString(pHandle, configPrefix() + "out_bezier", "default");
  m_pInSpeed = registerFloat(pHandle, configPrefix() + "in_speed", 1.f);
  m_pOutSpeed = registerFloat(pHandle, configPrefix() + "out_speed", 5.f);

  m_sFocusInAnimConfig = makeShared<SAnimationPropertyConfig>();
  m_sFocusInAnimConfig->internalEnabled = 1;
  m_sFocusInAnimConfig->internalStyle =
      std::string("hyprfocus_") + m_szAnimationName + "_in";
  m_sFocusInAnimConfig->pValues = m_sFocusInAnimConfig;

  m_sFocusOutAnimConfig = makeShared<SAnimationPropertyConfig>();
  m_sFocusOutAnimConfig->internalEnabled = 1;
  m_sFocusOutAnimConfig->internalStyle =
      std::string("hyprfocus_") + m_szAnimationName + "_out";
  m_sFocusOutAnimConfig->pValues = m_sFocusOutAnimConfig;
}

void IFocusAnimation::setup(HANDLE /*pHandle*/, std::string /*animationName*/) {
  // Hook point for animation-specific setup; currently unused.
}

void IFocusAnimation::onWindowFocus(PHLWINDOW /*pWindow*/, HANDLE /*pHandle*/) {
  hyprfocus_log(Log::INFO, "Base callback for animation: {}",
                m_szAnimationName);
  if (!m_pInBezier || !m_pOutBezier || !m_pInSpeed || !m_pOutSpeed) {
    hyprfocus_log(Log::ERR, "Config values not registered for animation {}",
                  m_szAnimationName);
    return;
  }

  m_sFocusInAnimConfig->internalBezier = m_pInBezier->value();
  m_sFocusInAnimConfig->internalSpeed = m_pInSpeed->value();

  m_sFocusOutAnimConfig->internalBezier = m_pOutBezier->value();
  m_sFocusOutAnimConfig->internalSpeed = m_pOutSpeed->value();

  hyprfocus_log(
      Log::INFO, "In bezier: {} In speed: {} Out bezier: {} Out speed: {}",
      m_sFocusInAnimConfig->internalBezier, m_sFocusInAnimConfig->internalSpeed,
      m_sFocusOutAnimConfig->internalBezier,
      m_sFocusOutAnimConfig->internalSpeed);
}

void IFocusAnimation::addConfigValue(HANDLE pHandle, const std::string &name,
                                     Hyprlang::CConfigValue value) {
  HyprlandAPI::addConfigValue(pHandle, configPrefix() + name, value);
}

Hyprlang::CConfigValue *
IFocusAnimation::getConfigValue(HANDLE pHandle, const std::string &name) {
  return HyprlandAPI::getConfigValue(pHandle, configPrefix() + name);
}
