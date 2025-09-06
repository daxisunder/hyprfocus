# hyprfocus

A plugin which provides focus animations for us borderless folks, originally inspired by [flashfocus](https://github.com/fennerm/flashfocus)!
Modified to work with the latest Hyprland, to support hyprpm as well as some other improvements.

## Animations:

flash

![preview](flash.gif)

shrink

![preview](shrink.gif)

## Installation:

Instructions based on [the official wiki](https://wiki.hyprland.org/Plugins/Using-Plugins/#compiling-official-plugins)

```
hyprpm add https://github.com/daxisunder/hyprfocus
hyprpm enable hyprfocus
```

## Getting started:

To start using hyprfocus, add this to your hyprland config:

```
plugin {
  hyprfocus {
    enabled = yes
    animate_floating = no
    animate_workspacechange = no
    focus_animation = flash
      # Beziers for focus animations
    bezier = bezIn, 0.5, 0.0, 1.0, 0.5
    bezier = bezOut, 0.0, 0.5, 0.5, 1.0
    bezier = overshot, 0.05, 0.9, 0.1, 1.05
    bezier = smoothOut, 0.36, 0, 0.66, -0.56
    bezier = smoothIn, 0.25, 1, 0.5, 1
    bezier = realsmooth, 0.28, 0.29, 0.69, 1.08
    bezier = easeInOutBack, 0.68, -0.6, 0.32, 1.6
      # Flash settings
    flash {
      flash_opacity = 0.7
      in_bezier = bezIn
      in_speed = 0.5
      out_bezier = bezOut
      out_speed = 3
    }
      # Shrink settings
    shrink {
      shrink_percentage = 0.99
      in_bezier = easeInOutBack
      in_speed = 1.5
      out_bezier = easeInOutBack
      out_speed = 3
    }
  }
}
```

### Plugin configuration:

`enabled` (yes/no) -> enable or disable the plugin

`focus_animation` (flash/shrink/none) -> animation for keyboard-driven focus

`animate_workspacechange` (yes/no) -> Whether to trigger the focus animation when changing workspaces

`animate_floating` (yes/no) -> Whether to trigger the focus animation for floating windows

### Animations configuration:

Animations can be configured within the plugin scope with the following syntax:

```
plugin {
    hyprfocus {
        <animation> {

        }
    }
}
```

### Shared animation variables:

`in_bezier` (bezier) -> bezier curve towards the animation apex

`out_bezier` (bezier) -> bezier curve towards the default window state

`in_speed` (float) -> speed for the 'in' bezier

`out_speed` (float) -> speed for the 'out' bezier

### Flash:

`flash_opacity` (float) -> opacity to during the flash's apex

### Shrink:

`shrink_percentage` (float) -> the amount a window has shrunk during the animation's apex

### Dispatching:

Hyprfocus can also flash the currently focused window through the `animatefocused` dispatcher:

```
bind = $mod, space, animatefocused
```

# Special thanks:

- [flashfocus](https://github.com/fennerm/flashfocus): An earlier project of similar nature
- [Original repo](https://github.com/VortexCoyote/hyprfocus.git)
- [upstream](https://github.com/pyt0xic/hyprfocus) Unmaintained since Hyprland 0.48.0
- [fork](https://github.com/avih7531/hyprfocus)
