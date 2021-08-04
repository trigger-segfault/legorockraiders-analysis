# Map of code separation by function address

> __Legend__<br>
> **Bold** = known filenames based on log messages.<br>
> &lt;AngleBrackets&gt; = external libraries (except for &lt;???&gt;)<br>
> \[SquareBrackets\] = being lazy/not entirely sure<br>
> *???* = unidentified function space<br>
> 
> *The higher in the list you go, the more tired I get*

***

|File/Contents|Notes|
|:------------|:----|
|`Advisors.c`| |
|\[Misc:Vector math\]| |
|\[Config/StartInfo\]| |
|`AITasks.c`| |
|`Creatures.c`| |
| \|&mdash; \[Bubbles\]| |
|`Buildings.c`| |
|*???*| |
|*???*| |
|*???*| |
|\[Misc:GameLogic\]|misc unidentified game/level logic|
|\[Flocks:Unk\]| |
|*???*| |
|\[Front:Mouse/Typing\]| |
|\[Front:Logic\]| |
|`SaveMenu.c`| |
|`HelpWindow.c`| |
|`InfoPanel.c`| |
|`GameInterface.c`| |
|`GamePanels.c`| |
|*???*| |
|`Game.c`|base game functions hooked into WinMain game loop|
|`Menus.c`| |
|\[LoadLevel\]|CFG/Map file loading|
|\[LoadObjectTypes\]| |
|\[Misc:Effects?\]|has recharge sparkle|
|`Level.c`| |
|\[CFG:BlocksLoad\]|CFG block loading: Samples, info, text, panel(?), so so...|
|*???*| |
|\[Struct BC\]| |
|`LiveObject.c`|+basic reserved pool|
|\[LiveObj:Nulls/Acts??\]|*a big pile of mush*|
|\[Flocks:Init/Logic?\]| |
|`LightEffects.c`| |
|*???*| |
|\[LoadScreen\]|+Loader Profile|
|\[Misc:SurfaceMap\]| |
|\[PolyMesh\]| |
|`PTLMessageLogic.c`| |
|`Units.c`|mostly selection|
|`NERPs.c`| |
|`Objectives.c`| |
|\[Savefile/ObjRecall\]|"SORR"|
|`ObjInfo.c`|Hover info over units|
|`Panels.c`| |
| \|&mdash; \[Buttons\]| |
| \|&mdash; \[RotationControl\]| |
| \|&mdash; \[CryOre SideBar\]| |
| \|&mdash; \[Priorities\]|front end only?|
| \|&mdash; \[PTLMessages\]| |
|`Rewards.c`| |
|*???*| |
|\[NERPs:rewards?\]| |
|*???*| |
|\[RoofTexture\]| |
|\[InfoScrollPanel\]| |
|*???*| |
|`AudioPlayer.c`| |
|`SmokeAnim.c`| |
|*???*| |
|\[BlockC/LevelStart?\]| |
|`Stats.c`| |
|\[Linked Struct 20\]| |
|\[TextMessagePanel\]| |
|`Text.c`| |
|`ToolTips.c`| |
|\[Vehicle Upgrades\]| |
|`Vehicles.c`| |
|\[LevelStruct 428\]| |
|`Weapons.c`| |
|\[Struct b20\]| |
|*???*| |
|\[LiveObj:Checks\]|Many functions to iterate live objects and predicate callbacks|
| | |
|**Start of DDI Engine**| |
| | |
|*???*| |
|`AVIFile.c`| |
|`ResourceData.c`|+actual ResourceData structure|
|\[Res:Light/Mesh/Frame\]| |
|\[Res:ResourceAppData\]| |
|\[Res:TextureUV/Mesh\]| |
|`Viewport.c`| |
|`StringUtils.h`|+split, hash, parseBool, strstri, etc.|
|**`Main.c`**|+WinMain, Window functions, directx setup, sound mixer(?) setup|
|`CFG.c`| |
|\[Rand/VectorMath\]| |
|\[Flocks:MatrixMath\]| |
|`Font.c`| |
|`AudioManager.c`| |
|`RenderManager.c`|+ScreenMode population|
|**`Image.c`**| |
|`AVIPlayer.c`| |
|**`Input.c`**| |
|**`Files.c`**| |
|\[LightWave:LWO\]| |
|`TextureManagement.c`| |
|*???*| |
|`RenderSurface.c`| |
|`KeyNames.c`| |
|`DrawSurface.c`| |
|\[LightWave:LWS\]| |
|`SoundSystem.c`| |
|`SharedFileBuffers.c`|Only used to load `.map` files|
|\[ActFrameResource\]| |
|&lt;D3D/D3DImage&gt;| |
|\[Scan/Diagnostics\]| |
|`Registry.c`| |
|`WAD.c`| |
|\[Mesh:Struct20\]| |
|&lt;C Runtime Library&gt;| |
|&lt;D3DRM&gt;| |
|&lt;DDraw&gt;| |
|&lt;AVIFile&gt;| |
|&lt;DSound&gt;| |
|`RNC.c`|Rob Northern compression for WAD files|
|`ScreenModes.c`|Registered compatible screen modes|
|&lt;Misc:CString&gt;| |
