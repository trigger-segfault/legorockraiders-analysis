# Map of code separation by address in LegoRR.exe



## Functions: Individual modules by address

***

### LegoRR modules

#### From: `00401000` to `004729d0`

Game code specific to LEGO Rock Raiders. All LegoRR game modules appear in alphabetical order (or at least *almost* every module*). Many names are based off of the PSX symbols dump, or based on commonly used names in CFG, NERPs, etc.

Many enum names are dead giveaway for a section's module, as the GODS engine also follows the pattern of prefixing enum names with the module name.

<details open><summary><i>Click to view table</i></summary>

|Current Name   |Real Name     |Notes|
|:--------------|:-------------|:----|
|`Advisor`      |              |Chief animations shown in-game|
|`AITask`       |              |All AI functionality|
|Routing        |*BezierCurve(?)*||path-finding|
|Creature       |*BasicObject(?)*|enemy/player units: ae|
|`Bubble`       |              |shown above RR heads|
|`Building`     |              |building units: ae|
|`Collision`    |              |possibly only building collision|
|`Construction` |              |Building construction and laying foundation|
|*CryOre(?)*    | ??           |*extension of `Construction`?*|
|`Credits`      |              |Just a single function to play the Credits|
|`DamageFont`   |              |fancy RPG damage text when hit|
|`Dependencies` |              | |
|`DynamicPM`    | ???          |World textures/mesh|
|`Effect`       |              |particles/miscobjects/anims|
|`ElectricFence`|              | |
|`Encyclopedia` |              |unused menu feature|
|`Erode`        |              |lava erosion|
|`Fallin`       |              |land slides/cave-ins|
|`Flocks`       |              |bats movement|
|`FrontEnd`     |              |various out-of-game interfaces, menus (and in-game menu windows, like options), a very big module|
|`HelpWindow`   |              |"you've teleported down a rock raider, now you can do X"|
|`Info`         |InfoMessage(?)|in-game info icons e.g. *"landslide has occurred"*|
|`Interface`    |              |in-game menu icons in top right|
|`LRR` / `Game` /<br>`Level`|`Lego`|main LRR stuff, this module is really big|
|`Camera`       |`LegoCamera`  | |
|`LiveObject`   |`LegoObject`  |live in-game objects|
|`LightEffects` |              |cursor spotlight|
|`Loader`       |              |loading screen/LoaderProfile.txt|
|`Map3D`        |              |3D surface map data of current level|
|`MeshPoly`*(PM?)*             | ??? |LOD meshes for different views|
|`Message`      |              |game actions/events/PTL|
|`NERPs`        |              |scripting: like half of all LRR functions|
|`Objective`    |              |mission requirements|
|`ObjectRecall` |              |remember RRs that have trained abilities/leveled up/or renamed, etc.|
|`ObjInfo`      |              |more over-head RR info like health bar|
|`Panel`        |              |in-game buttons and interfaces all over the screen|
|`Pointer`      |              |mouse cursor images/flh's|
|`Priorities`   |              |Order of operations for what tasks AI should do first|
|`RadarMap`     |              | |
|`Reward`       |              |objective front end, shown at end of level|
|`RoofMesh`     | ?            |world mesh for Roof, which is an optional part of levels|
|`SelectPlace`  | ?            |selection grid highlight when placing building, handles logic too|
|`SFX`          |              | |
|`Smoke`        |              |a special effect type|
|`SpiderWeb`    |              |unused object type|
|`Stats`        |              |object stats/levels|
|`Teleporter`   |              |all player-owned units are teleported in/out via this system|
|`Text`         |              |text message panel display, big green window|
|`ToolTip`      |              | |
|`Upgrade`      |              |upgrade ae parts|
|`Vehicle`      |              |vehicle units: ae|
|`Water`        |              |flood water unused feature|
|`Weapon`       |              |Weapons (and some tools) stats and projectiles|
|???            | ???          |*extension of `Weapon`?*|
|`VideoPlayer`  |`Movie`       |video player for intros end-game AVIs (probably part of Gods98, but not in source leak)|

</details>

***


### Gods98 modules

#### From: `004729d0` to `0048dbe0`

[Data Design Interactive's GODS engine](https://www.giantbomb.com/gods-engine/3015-3590/). Code not specific to LEGO Rock Raiders. **All names are source-accurate**, thanks to legally-obtained dumps of the GODS engine (for Windows 98).

<details open><summary><i>Click to view table</i></summary>

|Name        |Notes|
|:-----------|:----|
|`Container` |Wrapper around most primary game asset types|
|`Viewport`  |     |
|`Util`      |Utility string functions (includes `std::_strdup`)|
|`Main`      |Includes `WinMain` and `Direct3DRM` setup|
|`Config`    |`.cfg`, `.ol`, `.ptl`, and `.ae` files. (`CFG`) Most names have not been changed because I hate DDI's name choices here|
|`Maths`     |Includes `Matrix`|
|`Font`      |Extension of `Image` module|
|`Sound3D`   |Extension of `Sound` module|
|`DirectDraw`|     |
|`Image`     |     |
|`Animation` |Includes `G98CAnimation` and `G98CSurface`|
|`Input`     |     |
|`File`      |Managed file system for access to `Data` folder and routing through `Wad` files|
|`Mesh`      |`.x` and friends mesh files|
|`Flic`      |`.flh` files animation loading and playback|
|`TextWindow`|Extension of `Font` for managed text rendering|
|`Keys`      |`KEY*` enum names/defines|
|`Draw`      |Pixel-drawing vector graphics (**SLOW AF** manual pixel-by-pixel CPU drawing)|
|`Lws`       |`.lws` LightWave scene files|
|`Sound`     |Basic sound file loading (using `mmio`), and Music management (using `mci`)|
|`Mem`       |Helpers for shared buffer allocations (only used by `.map` files indirectly through `File` module)|
|`Material`  |Just one function|
|`AnimClone` |     |
|`BMP`       |`.bmp` file loading (internal use only)|
|`Dxbug`     |Part of `Error`, but separate file|
|`Error`     |     |
|`Registry`  |     |
|`Wad`       |`.wad` files|
|`Lwt`       |`.lwo` LightWave object files|

</details>

***


### Remaining modules

Misc groups of modules. Contains GODS module: `Init`, and GODS indirectly-related module: `RNC`.

#### From: `0048dbe0` to `0049f000`

<details open><summary><i>Click to view table</i></summary>

|Name               |Notes         |
|:------------------|:-------------|
|&lt;C Runtime&gt;  |              |
|&lt;Direct3DRM&gt; |`D3DRM.DLL`   |
|&lt;DirectDraw&gt; |`DDRAW.DLL`   |
|&lt;AVIFile&gt;    |`AVIFIL32.DLL`|
|&lt;DirectInput&gt;|`DINPUT.DLL`  |
|&lt;DSound&gt;     |`DSOUND.DLL`  |
|&lt;RtlUnwind&gt;  |`KERNEL32.DLL`|
|`RNC`|**RNC**: "[Rob Northern Compression](https://segaretro.org/Rob_Northen_compression)". Optional file compression for entries in WAD files (unused)|
|`Init`|**Gods98Init**: "Mode selection dialog". Also handles startup when dialog isn't shown.|
|&lt;remaining C Runtime&gt;|      |
|&lt;Unwind@&gt;    |              |

</details>

***

## Module groups by address

<details open><summary><i>Click to view table</i></summary>

|Functions Group    |From      |To        |
|:------------------|:---------|:---------|
|LegoRR modules     |`00401000`|`004729d0`|
|Gods98 modules     |`004729d0`|`0048dbe0`|
|C Runtime          |`0048dbe0`|`0049b970`|
|DLL imports        |`0049b970`|`0049ca80`|
|RNC                |`0049ca80`|`0049d2f0`|
|Gods98Init         |`0049d2f0`|`0049dd70`|
|remaining C Runtime|`0049dd70`|`0049e050`|
|Unwind@            |`0049e050`|`0049f000`|

</details>

***

***

## Globals: Individual modules by address

**TODO**
