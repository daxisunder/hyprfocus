#include "Shrink.hpp"
#include "Log.hpp"

#include <hyprland/src/Compositor.hpp>
#include <hyprland/src/desktop/view/Window.hpp>
#include <hyprland/src/layout/LayoutManager.hpp>
#include <hyprland/src/managers/animation/AnimationManager.hpp>
#include <hyprland/src/plugins/PluginAPI.hpp>

void CShrink::init(HANDLE pHandle, std::string animationName) {
  IFocusAnimation::init(pHandle, "shrink");
  addConfigValue(pHandle, "shrink_percentage", Hyprlang::FLOAT{0.95f});
}

void CShrink::setup(HANDLE pHandle, std::string animationName) {}

void CShrink::onWindowFocus(PHLWINDOW pWindow, HANDLE pHandle) {
  IFocusAnimation::onWindowFocus(pWindow, pHandle);

  static const auto *shrinkPercentage =
      (Hyprlang::FLOAT *const *)(getConfigValue(pHandle, "shrink_percentage")
                                     ->getDataStaticPtr());

  const float scale = std::clamp(**shrinkPercentage, 0.1f, 1.0f);

  hyprfocus_log(Log::INFO, "Shrink: percentage={}", scale);

  const Vector2D ORIGINAL_POS = pWindow->m_realPosition->goal();
  const Vector2D ORIGINAL_SIZE = pWindow->m_realSize->goal();

  const Vector2D newSize = ORIGINAL_SIZE * scale;
  const Vector2D newPos = ORIGINAL_POS + (ORIGINAL_SIZE - newSize) / 2.f;

  pWindow->m_realPosition->setConfig(m_sFocusOutAnimConfig);
  pWindow->m_realSize->setConfig(m_sFocusOutAnimConfig);

  *pWindow->m_realPosition = newPos;
  *pWindow->m_realSize = newSize;

  pWindow->m_realSize->setCallbackOnEnd(
      [w = PHLWINDOWREF{pWindow}, this, ORIGINAL_POS,
       ORIGINAL_SIZE](WP<CBaseAnimatedVariable> pav) {
        if (!w)
          return;

        w->m_realSize->setConfig(m_sFocusInAnimConfig);
        w->m_realPosition->setConfig(m_sFocusInAnimConfig);

        if (w->m_isFloating) {
          *w->m_realPosition = ORIGINAL_POS;
          *w->m_realSize = ORIGINAL_SIZE;
        } else {
          g_layoutManager->recalculateMonitor(w->m_monitor.lock());
        }

        w->m_realSize->setCallbackOnEnd(nullptr);
      });
}
