

## Menu formats

**Menu:**
* `MenuCount number`
* `Title name`
* `FullName name`
* `Position x:y`
* `MenuFont bmp`
* `AutoCenter bool`
* `DisplayTitle bool`
* `CanScroll bool`
* `MenuImage bmp:x:y:bool` (bool is either `1` for true, or anything else for false)

### Item formats

**Trigger:**
```
Item%i type:x1:y1:banner:end

Item1 Trigger:20:20:Start:1
```

**Slider:**
```
Item%i type:x1:y1:x2:y2:banner:min:max[:image1:image2:image3:image4]

Item1 Slider:20:20:20:20:Sound_Volume:0:10:path\a.bmp:path\b.bmp:path\c.bmp:path\d.bmp
```

**Next:**
```
Item%i type:x1:y1:banner:MenuLink

Item1 Next:20:20:Next:Menu2
```

### Overlay format

Note that overlays in this version should not have the `!` prefix.

```
Overlay%i flic:x:y

Overlay path\overlay.flh:20:20
```

### Menu layouts

Each menu expects the following menu items in the specified order. Note that `Next` items can appear anywhere in-between other items as they have no hardcoded behaviour.

**MainMenuFull:**

1. `Trigger` - Quit Game

**SaveMenu:**

*Only contains `Next` items.*

**PausedMenu:**

1. `Trigger` - Continue Mission
2. `Slider` - Game Speed
3. `Slider` - Music Volume
4. `Slider` - SFX Volume
5. `Slider` - Brightness
6. `Trigger` - Quit Mission

**OptionsMenu:**

1. `Slider` - Game Speed
2. `Slider` - Music Volume
3. `Slider` - SFX Volume
4. `Slider` - Brightness
5. `Trigger` - Continue Mission