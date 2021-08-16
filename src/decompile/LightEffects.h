// LightEffects.h : Declares topdown spotlight effects in 3D-game-space.
//
/// STATUS: [COMPLETE]
/// PURPOSE: Manages flickering and other lighting effects related to the mouse cursor
///          in topdown view.
///
/// NAMESPACE: lego::light
/// INITIALIZE: Call `InitLightEffects(ResourceData*,ResourceData*,float,float,float)` once on startup.
///             (no cleanup)
///             (may need to call `LightEffects_SetDimmerMode(BOOL)` to reset)
/// GLOBALS: private

#pragma once

#include "Common.h"
#include "CFG.h"
#include "ResourceData.h"


#pragma region Flags
namespace lego {

/// PRIVATE:
// Flags for LightEffectsManager global variable @004ebec8
enum LightEffectsFlags : unsigned int
{
	LIGHTEFFECTS_NONE          = 0,

	LIGHTEFFECTS_HASBLINK      = 0x1, // Blink is enabled (all Blink CFG arguments are present)
	//LIGHTEFFECTS_UNK_2         = 0x2, // Unused flag, maybe for blinking?
	LIGHTEFFECTS_HASFADE       = 0x4, // Fade is enabled (all Fade CFG arguments are present)
	LIGHTEFFECTS_FADING        = 0x8, // fade mode, states 2-4 (or state 0 if this flag is unset)

	LIGHTEFFECTS_FADE_FORWARD  = 0x10, // fade mode, fading forward to destination color
	LIGHTEFFECTS_FADE_REVERSE  = 0x20, // fade mode, fading in reverse back to default color
	LIGHTEFFECTS_HASMOVE       = 0x40, // Move is enabled (all Move CFG arguments are present)
	LIGHTEFFECTS_MOVING        = 0x80, // in-progress of moving light

	LIGHTEFFECTS_DISABLED      = 0x100, // F9 debug key, disables LightEffects_Update (and changes light color back to initial)
	LIGHTEFFECTS_DIMOUT        = 0x200, // dim-out mode, current color transitions to black in 10 seconds.
	LIGHTEFFECTS_DIMIN_DONE    = 0x400, // dim-in mode finished (current color has transitioned to `initialRGB` in 10 seconds).
	//LIGHTEFFECTS_UNK_COLOR_800 = 0x800,

	LIGHTEFFECTS_DIMOUT_DONE   = 0x1000, // dim-out mode finished (current color has transitioned to black in 10 seconds).
};

} /* namespace lego */
#pragma endregion


#pragma region Globals
namespace lego::light {

/// PRIVATE:
// <LegoRR.exe @004ebdd8 - 004ebecc>
struct LightEffectsManager
{
	// <LegoRR.exe @004ebdd8>
	/*00,4*/ ResourceData* resSpotlight; // [Res+Move] init
	// <LegoRR.exe @004ebddc>
	/*04,4*/ ResourceData* resRootLight; // [Move] init
	// <LegoRR.exe @004ebde0>
	/*08,c*/ ColourRGBF initialRGB; // [Color] init
	// <LegoRR.exe @004ebdec>
	/*14,c*/ ColourRGBF currentRGB; // [Color+Blink+Fade] init+update
	// <LegoRR.exe @004ebdf8>
	/*20,c*/ ColourRGBF BlinkRGBMax; // [Blink] init
	// <LegoRR.exe @004ebe04>
	/*2c,4*/ float blinkTime; // [Blink] update
	// <LegoRR.exe @004ebe08>
	/*30,8*/ Range2F RandomRangeForTimeBetweenBlinks; // [Blink] init
	// <LegoRR.exe @004ebe10>
	/*38,4*/ float blinkChange; // [Blink] update
	// <LegoRR.exe @004ebe14>
	/*3c,4*/ float MaxChangeAllowed; // [Blink] init
	// <LegoRR.exe @004ebe18>
	/*40,c*/ ColourRGBF fadeDestRGB; // [Fade] update
	// <LegoRR.exe @004ebe24>
	/*4c,c*/ ColourRGBF FadeRGBMin; // [Fade] init
	// <LegoRR.exe @004ebe30>
	/*58,c*/ ColourRGBF FadeRGBMax; // [Fade] init
	// <LegoRR.exe @004ebe3c>
	/*64,4*/ float fadeTime; // [Fade] update
	// <LegoRR.exe @004ebe40>
	/*68,8*/ Range2F RandomRangeForTimeBetweenFades; // [Fade] init
	// <LegoRR.exe @004ebe48>
	/*70,c*/ ColourRGBF fadeSpeedRGB; // [Fade] update
	// <LegoRR.exe @004ebe54>
	/*7c,8*/ Range2F RandomRangeForFadeTimeFade; // [Fade] init
	// <LegoRR.exe @004ebe5c>
	/*84,4*/ float fadeHoldTime; // [Fade] update
	// <LegoRR.exe @004ebe60>
	/*88,8*/ Range2F RandomRangeForHoldTimeOfFade; // [Fade] init
	// <LegoRR.exe @004ebe68>
	/*90,c*/ ColourRGBF fadePosRGB; // [Fade] update
	// <LegoRR.exe @004ebe74>
	/*9c,c*/ Vector3F resPosition; // [Move] init+update
	// <LegoRR.exe @004ebe80>
	/*a8,c*/ Vector3F MoveLimit; // [Move] init
	// <LegoRR.exe @004ebe8c>
	/*b4,4*/ float moveTime; // [Move] update
	// <LegoRR.exe @004ebe90>
	/*b8,8*/ Range2F RandomRangeForTimeBetweenMoves; // [Move] init
	// <LegoRR.exe @004ebe98>
	/*c0,4*/ float moveSpeed; // [Move] update
	// <LegoRR.exe @004ebe9c>
	/*c4,8*/ Range2F RandomRangeForSpeedOfMove; // [Move] init
	// <LegoRR.exe @004ebea4>
	/*cc,c*/ Vector3F vectorMove; // [Move] update
	// <LegoRR.exe @004ebeb0>
	/*d8,4*/ float moveDist; // [Move] update
	// <LegoRR.exe @004ebeb4>
	/*dc,8*/ Range2F RandomRangeForDistOfMove; // [Move] init
	// <LegoRR.exe @004ebebc>
	/*e4,c*/ unsigned char reserved1[12]; // possibly an unused Vector3F/ColourRGBF
	// <LegoRR.exe @004ebec8>
	/*f0,4*/ LightEffectsFlags flags; // [all] init+update
	/*f4*/
};

} /* namespace lego::light */
namespace lego::globals {

/// PRIVATE:
// <LegoRR.exe @004ebdd8 - 004ebecc>
extern lego::light::LightEffectsManager g_Light;

} /* namespace logo::globals */
#pragma endregion


#pragma region Functions
namespace lego::light {

/// PUBLIC:
// <LegoRR.exe @0044c9d0>
void __cdecl InitLightEffects(ResourceData* resRootSpotlight, ResourceData* resRootLight, float initialRed, float initialGreen, float initialBlue);

/// PRIVATE:
// Resets LightEffects to its initialRGB colour value (hardcoded as 0.8:0.8:0.8).
// <LegoRR.exe @0044ca20>
void __cdecl LightEffects_InitColor(void);

/// PUBLIC:
// <LegoRR.exe @0044ca50>
void __cdecl LightEffects_SetDisabled(BOOL isDisabled);
// Return not used, but *can* be used.
// <LegoRR.exe @0044ca80>
BOOL __cdecl LightEffects_Load(CFGProperty* root, const char* rootPath);

/// PRIVATE:
// <LegoRR.exe @0044cab0>
BOOL __cdecl LightEffects_LoadBlink(CFGProperty* root, const char* rootPath);
// <LegoRR.exe @0044cc30>
void __cdecl LightEffects_SetBlink(float red, float green, float blue, float maxChange, float minRange, float maxRange);
// <LegoRR.exe @0044cc80>
BOOL __cdecl LightEffects_LoadFade(CFGProperty* root, const char* rootPath);
// <LegoRR.exe @0044ced0>
void __cdecl LightEffects_SetFade(float minRed, float minGreen, float minBlue, float maxRed, float maxGreen, float maxBlue, float minTime, float maxTime, float minFade, float maxFade, float minHold, float maxHold);
// <LegoRR.exe @0044cf60>
BOOL __cdecl LightEffects_LoadMove(CFGProperty* root, const char* rootPath);
// <LegoRR.exe @0044d1b0>
void __cdecl LightEffects_SetMove(float minTime, float maxTime, float minSpeed, float maxSpeed, float minDist, float maxDist, float limitX, float limitY, float limitZ);

/// PUBLIC:
// Forces the LightEffect to re-obtain the resRootSpotlight position,
//  and also restarts movement effects.
// <LegoRR.exe @0044d230>
void __cdecl LightEffects_InvalidatePosition(void);
// <LegoRR.exe @0044d260>
void __cdecl LightEffects_Update(float elapsed);

/// PRIVATE:
// <LegoRR.exe @0044d2b0>
void __cdecl LightEffects_UpdateResource(void);
// <LegoRR.exe @0044d390>
void __cdecl LightEffects_UpdateBlink(float elapsed);
/// RESULT: ref_value = -ref_value
// This function is kind of dumb, the way it negates the value is different depending
//  on the sign, but the end result will always be the same.
// <LegoRR.exe @0044d510>
void __cdecl LightEffects_UpdateBlink_FlipSign(float* ref_value);
// <LegoRR.exe @0044d540>
void __cdecl LightEffects_UpdateFade(float elapsed);
// <LegoRR.exe @0044d9d0>
void __cdecl LightEffects_RandomizeFadeSpeedRGB(void);
// <LegoRR.exe @0044da20>
void __cdecl LightEffects_UpdateMove(float elapsed);
// <LegoRR.exe @0044dc60>
BOOL __cdecl LightEffects_CheckMoveLimit(const Vector3F* vector);

/// PUBLIC:
// This might be some sort of reset function
// <LegoRR.exe @0044dce0>
void __cdecl LightEffects_SetDimmerMode(BOOL isDimoutMode);

/// PRIVATE:
// <LegoRR.exe @0044dd10>
void __cdecl LightEffects_UpdateDimmer(float elapsed);

} /* namespace lego::light */
#pragma endregion

