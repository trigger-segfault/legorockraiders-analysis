// LightEffects.cpp : Defines topdown spotlight effects in 3D-game-space.
//
/// STATUS: [COMPLETE]

#include "LightEffects.h"
//#include "VectorMath.h"


using namespace lego;
using namespace lego::light;


#pragma region Globals

/// PRIVATE:
// <LegoRR.exe @004ebdd8 - 004ebecc>
LightEffectsManager lego::globals::g_Light;

#pragma endregion


#pragma region Functions

/// PUBLIC:
// <LegoRR.exe @0044c9d0>
void __cdecl lego::light::InitLightEffects(ResourceData* resRootSpotlight, ResourceData* resRootLight, float initialRed, float initialGreen, float initialBlue)
{
	globals::g_Light.initialRGB.red   = initialRed;
	globals::g_Light.initialRGB.green = initialGreen;
	globals::g_Light.initialRGB.blue  = initialBlue;
	globals::g_Light.currentRGB.red   = initialRed;
	globals::g_Light.currentRGB.green = initialGreen;
	globals::g_Light.currentRGB.blue  = initialBlue;

	globals::g_Light.resRootSpotlight = resRootSpotlight;
	globals::g_Light.resRootLight     = resRootLight;

	LightEffects_ResetColor();
}

/// PRIVATE:
// Resets LightEffects to its initialRGB colour value (hardcoded as 0.8:0.8:0.8).
// <LegoRR.exe @0044ca20>
void __cdecl lego::light::LightEffects_ResetColor(void)
{
	res::Res_SetLightColor(globals::g_Light.resSpotlight,
		globals::g_Light.initialRGB.red, globals::g_Light.initialRGB.green, globals::g_Light.initialRGB.blue, 1.0f);
}

/// PUBLIC:
// <LegoRR.exe @0044ca50>
void __cdecl lego::light::LightEffects_SetDisabled(BOOL isDisabled)
{
	if (isDisabled) {
		globals::g_Light.flags |= LIGHTEFFECTS_DISABLED /*0x100*/;
		LightEffects_ResetColor();
	}
	else {
		globals::g_Light.flags &= ~LIGHTEFFECTS_DISABLED /*~0x100*/;
	}
}

// Return not used, but *can* be used.
// <LegoRR.exe @0044ca80>
BOOL __cdecl lego::light::LightEffects_Load(CFGProperty* root, const char* rootPath)
{
	LightEffects_LoadBlink(root, rootPath);
	LightEffects_LoadFade(root, rootPath);
	return LightEffects_LoadMove(root, rootPath); // again, this return is unused, this function was likely void
}

/// PRIVATE:
// <LegoRR.exe @0044cab0>
BOOL __cdecl lego::light::LightEffects_LoadBlink(CFGProperty* root, const char* rootPath)
{
	char* stringParts[10];

	ColourRGBF rgbMax = { 0.0f, 0.0f, 0.0f }; // dummy init
	const char* keyPath = cfg::CFG_JoinPath(rootPath, "LightEffects", "BlinkRGBMax", nullptr);
	if (cfg::CFG_ReadRGBF(root, keyPath, &rgbMax.red, &rgbMax.green, &rgbMax.blue)) {

		const char* value;
		keyPath = cfg::CFG_JoinPath(rootPath,"LightEffects", "MaxChangeAllowed", nullptr);
		if (cfg::CFG_ReadString(root, keyPath) == nullptr) {
			value = ""/*EMPTYSTR*/;
		}
		else {
			keyPath = cfg::CFG_JoinPath(rootPath, "LightEffects", "MaxChangeAllowed", nullptr);
			value = cfg::CFG_ReadString(root, keyPath);
		}
		float maxChange = std::atof(value);
		if (maxChange != 0.0f) {
			/// TODO: What fraction is this?
			maxChange *= 0.003921569;
		}

		keyPath = cfg::CFG_JoinPath(rootPath, "LightEffects", "RandomRangeForTimeBetweenBlinks", nullptr);
		char* str = cfg::CFG_CopyString(root, keyPath);
		if (str != nullptr) {
			int numParts = util::stringSplit(str, stringParts, ":");
			if (numParts == 2) {
				Range2F range = {
					(std::atof(stringParts[0]) * 25.0f),
					(std::atof(stringParts[1]) * 25.0f)
				};
				std::free(str);

				/// CHANGE: Multiplication was originally performed during parameter passing
				LightEffects_SetBlink(rgbMax.red, rgbMax.green, rgbMax.blue,
									  maxChange, range.min, range.max);

				return true;
			}
			std::free(str);
		}
	}
	return false;
}

// <LegoRR.exe @0044cc30>
void __cdecl lego::light::LightEffects_SetBlink(float red, float green, float blue, float maxChange, float minRange, float maxRange)
{
	globals::g_Light.BlinkRGBMax.red   = red;
	globals::g_Light.BlinkRGBMax.green = green;
	globals::g_Light.BlinkRGBMax.blue  = blue;

	globals::g_Light.RandomRangeForTimeBetweenBlinks.min = minRange;
	globals::g_Light.RandomRangeForTimeBetweenBlinks.max = maxRange;
	globals::g_Light.MaxChangeAllowed = maxChange;

	globals::g_Light.flags |= LIGHTEFFECTS_HASBLINK /*0x1*/;
}

// <LegoRR.exe @0044cc80>
BOOL __cdecl lego::light::LightEffects_LoadFade(CFGProperty* root, const char* rootPath)
{
	char* stringParts[10];

	ColourRGBF rgbMin = { 0.0f, 0.0f, 0.0f }; // dummy init
	const char* keyPath = cfg::CFG_JoinPath(rootPath, "LightEffects", "FadeRGBMin", nullptr);
	if (cfg::CFG_ReadRGBF(root, keyPath, &rgbMin.red, &rgbMin.green, &rgbMin.blue)) {

		ColourRGBF rgbMax = { 0.0f, 0.0f, 0.0f }; // dummy init
		keyPath = cfg::CFG_JoinPath(rootPath, "LightEffects", "FadeRGBMax", nullptr);
		if (cfg::CFG_ReadRGBF(root, keyPath, &rgbMax.red, &rgbMax.green, &rgbMax.blue)) {

			keyPath = cfg::CFG_JoinPath(rootPath, "LightEffects", "RandomRangeForTimeBetweenFades", nullptr);
			char* str = cfg::CFG_CopyString(root, keyPath);
			if (str != nullptr) {
				int numParts = util::stringSplit(str, stringParts, ":");
				if (numParts == 2) {
					Range2F time = {
						(std::atof(stringParts[0]) * 25.0f),
						(std::atof(stringParts[1]) * 25.0f)
					};
					std::free(str);
	
					keyPath = cfg::CFG_JoinPath(rootPath, "LightEffects", "RandomRangeForFadeTimeFade", nullptr);
					str = cfg::CFG_CopyString(root, keyPath);
					if (str == nullptr)
						return false;

					numParts = util::stringSplit(str, stringParts, ":");
					if (numParts == 2) {
						Range2F fade = {
							(std::atof(stringParts[0]) * 25.0f),
							(std::atof(stringParts[1]) * 25.0f)
						};
						std::free(str);

						keyPath = cfg::CFG_JoinPath(rootPath, "LightEffects", "RandomRangeForHoldTimeOfFade", nullptr);
						str = cfg::CFG_CopyString(root, keyPath);
						if (str == nullptr)
							return false;

						numParts = util::stringSplit(str, stringParts, ":");
						if (numParts == 2) {
							Range2F hold = {
								(std::atof(stringParts[0]) * 25.0f),
								(std::atof(stringParts[1]) * 25.0f)
							};
							std::free(str);

							/// CHANGE: Multiplication was originally performed during parameter passing
							LightEffects_SetFade(rgbMin.red, rgbMin.green, rgbMin.blue,
												 rgbMax.red, rgbMax.green, rgbMax.blue,
												 time.min, time.max, 
												 fade.min, fade.max,
												 hold.min, hold.max);

							return true;
						}
					}
				}
				// this will free any of the 3 str mallocs above, if any numParts != 2
				std::free(str);
			}
		}
	}
	return false;
}

// <LegoRR.exe @0044ced0>
void __cdecl lego::light::LightEffects_SetFade(float minRed, float minGreen, float minBlue, float maxRed, float maxGreen, float maxBlue, float minTime, float maxTime, float minFade, float maxFade, float minHold, float maxHold)
{
	globals::g_Light.FadeRGBMin.red   = minRed;
	globals::g_Light.FadeRGBMin.green = minGreen;
	globals::g_Light.FadeRGBMin.blue  = minBlue;
	globals::g_Light.FadeRGBMax.red   = maxRed;
	globals::g_Light.FadeRGBMax.green = maxGreen;
	globals::g_Light.FadeRGBMax.blue  = maxBlue;

	globals::g_Light.RandomRangeForTimeBetweenFades.min = minTime;
	globals::g_Light.RandomRangeForTimeBetweenFades.max = maxTime;
	globals::g_Light.RandomRangeForFadeTimeFade.min = minFade;
	globals::g_Light.RandomRangeForFadeTimeFade.max = maxFade;
	globals::g_Light.RandomRangeForHoldTimeOfFade.min = minHold;
	globals::g_Light.RandomRangeForHoldTimeOfFade.max = maxHold;

	globals::g_Light.flags |= LIGHTEFFECTS_HASFADE /*0x4*/;
}

// <LegoRR.exe @0044cf60>
BOOL __cdecl lego::light::LightEffects_LoadMove(CFGProperty* root, const char* rootPath)
{
	char *stringParts[10];

	const char* keypath = cfg::CFG_JoinPath(rootPath, "LightEffects", "RandomRangeForTimeBetweenMoves", nullptr);
	char* str = cfg::CFG_CopyString(root, keypath);
	if (str != nullptr) {
		int numParts = util::stringSplit(str, stringParts, ":");
		if (numParts == 2) {
			Range2F time = {
				std::atof(stringParts[0]),
				std::atof(stringParts[1])
			};
			std::free(str);

			keypath = cfg::CFG_JoinPath(rootPath, "LightEffects", "RandomRangeForSpeedOfMove", nullptr);
			str = cfg::CFG_CopyString(root, keypath);
			if (str == nullptr)
				return false;

			numParts = util::stringSplit(str, stringParts, ":");
			if (numParts == 2) {
				Range2F speed = {
					std::atof(stringParts[0]),
					std::atof(stringParts[1])
				};
				std::free(str);

				keypath = cfg::CFG_JoinPath(rootPath, "LightEffects", "RandomRangeForDistOfMove", nullptr);
				str = cfg::CFG_CopyString(root, keypath);
				if (str == nullptr)
					return false;

				numParts = util::stringSplit(str, stringParts, ":");
				if (numParts == 2) {
					Range2F dist = {
						std::atof(stringParts[0]),
						std::atof(stringParts[1])
					};
					std::free(str);

					keypath = cfg::CFG_JoinPath(rootPath, "LightEffects", "MoveLimit", nullptr);
					str = cfg::CFG_CopyString(root, keypath);
					if (str == nullptr)
						return false;

					numParts = util::stringSplit(str, stringParts, ":");
					if (numParts == 3) {
						Vector3F limit = {
							std::atof(stringParts[0]),
							std::atof(stringParts[1]),
							std::atof(stringParts[2])
						};
						std::free(str);

						/// CHANGE: Multiplication was originally performed during parameter passing
						///          (only time and speed have multiplication)
						LightEffects_SetMove(time.min,  time.max,
											 speed.min, speed.max,
											 hold.min,  hold.max,
											 limit.x, limit.y, limit.z);

						return true;
					}
				}
			}
		}
		// this will free any of the 4 str mallocs above, if any numParts != 2 (or numParts != 3 for limit)
		std::free(str);
	}
	return false;
}

// <LegoRR.exe @0044d1b0>
void __cdecl lego::light::LightEffects_SetMove(float minTime, float maxTime, float minSpeed, float maxSpeed, float minDist, float maxDist, float limitX, float limitY, float limitZ)
{
	globals::g_Light.RandomRangeForTimeBetweenMoves.min = minTime;
	globals::g_Light.RandomRangeForTimeBetweenMoves.max = maxTime;
	globals::g_Light.RandomRangeForSpeedOfMove.max = maxSpeed;
	globals::g_Light.RandomRangeForSpeedOfMove.min = minSpeed;
	globals::g_Light.RandomRangeForDistOfMove.min = minDist;
	globals::g_Light.RandomRangeForDistOfMove.max = maxDist;
	// Writes position to Vector3F globals::g_Light.resPosition
	res::Res_GetPosition(globals::g_Light.resSpotlight, globals::g_Light.resRootLight, &globals::g_Light.resPosition);
	globals::g_Light.MoveLimit.x = limitX;
	globals::g_Light.MoveLimit.y = limitY;
	globals::g_Light.MoveLimit.z = limitZ;
	globals::g_Light.flags |= LIGHTEFFECTS_HASMOVE /*0x40*/;
}

/// PUBLIC:
// <LegoRR.exe @0044d230>
void __cdecl lego::light::LightEffects_InvalidatePosition(void)
{
	// Writes position to Vector3F globals::g_Light.resPosition
	res::Res_GetPosition(globals::g_Light.resSpotlight, globals::g_Light.resRootLight, &globals::g_Light.resPosition);
	globals::g_Light.flags &= ~LIGHTEFFECTS_MOVING /*0x80*/;
}

// <LegoRR.exe @0044d260>
void __cdecl lego::light::LightEffects_Update(float elapsed)
{
	if (!(globals::g_Light.flags & LIGHTEFFECTS_DISABLED /*0x100*/) &&
		globals::g_Light.resSpotlight != nullptr)
	{
		LightEffects_UpdateBlink(elapsed);
		LightEffects_UpdateFade(elapsed);
		LightEffects_UpdateMove(elapsed);
		LightEffects_UpdateDimmer(elapsed);
		LightEffects_UpdateResource();
	}
}

/// PRIVATE:
// <LegoRR.exe @0044d2b0>
void __cdecl lego::light::LightEffects_UpdateResource(void)
{
	float r = globals::g_Light.currentRGB.red;
	float g = globals::g_Light.currentRGB.green;
	float b = globals::g_Light.currentRGB.blue;
	if      (r < 0.0f) r = 0.0f;
	else if (r > 1.0f) r = 1.0f;

	if      (g < 0.0f) g = 0.0f;
	else if (g > 1.0f) g = 1.0f;

	if      (b < 0.0f) b = 0.0f;
	else if (b > 1.0f) b = 1.0f;

	res::Res_SetLightColor(globals::g_Light.resSpotlight, r, g, b, 1.0f);
}

// <LegoRR.exe @0044d390>
void __cdecl lego::light::LightEffects_UpdateBlink(float elapsed)
{
	if (!(globals::g_Light.flags & LIGHTEFFECTS_HASBLINK /*0x1*/))
		return; // blink not setup, can't update

	globals::g_Light.blinkTime -= elapsed;
	if (globals::g_Light.blinkTime > 0.0f)
		return; // no need to update

	float time = util::randomChooseRange(globals::g_Light.RandomRangeForTimeBetweenBlinks.min,
										 globals::g_Light.RandomRangeForTimeBetweenBlinks.max);
	globals::g_Light.blinkTime = time;

	short rng = util::randomInt16();
	float value = (float)((int)rng % 1000) * 0.001f; // (... / 1000.0f)

	ColourRGBF rgb = {
		((globals::g_Light.BlinkRGBMax.red   + globals::g_Light.BlinkRGBMax.red)   * value) - globals::g_Light.BlinkRGBMax.red,
		((globals::g_Light.BlinkRGBMax.green + globals::g_Light.BlinkRGBMax.green) * value) - globals::g_Light.BlinkRGBMax.green,
		((globals::g_Light.BlinkRGBMax.blue  + globals::g_Light.BlinkRGBMax.blue)  * value) - globals::g_Light.BlinkRGBMax.blue
	};

	if (globals::g_Light.MaxChangeAllowed <= std::abs(rgb.red + globals::g_Light.blinkChange)) {
		LightEffects_UpdateBlink_FlipSign(&rgb.red);
		LightEffects_UpdateBlink_FlipSign(&rgb.green);
		LightEffects_UpdateBlink_FlipSign(&rgb.blue);

		if (globals::g_Light.MaxChangeAllowed <= std::abs(rgb.red + globals::g_Light.blinkChange))
			return;
	}

	globals::g_Light.currentRGB.red   += rgb.red;
	globals::g_Light.currentRGB.green += rgb.green;
	globals::g_Light.currentRGB.blue  += rgb.blue;
	globals::g_Light.blinkChange += rgb.red; // yes, it's just red...
}

/// RESULT: ref_value = -ref_value
// This function is kind of dumb, the way it negates the value is different depending
//  on the sign, but the end result will always be the same.
// <LegoRR.exe @0044d510>
void __cdecl lego::light::LightEffects_UpdateBlink_FlipSign(float* ref_value)
{
	// I don't even...
	if (*ref_value < 0.0f) {
		*ref_value *= -1.0;
	}
	else {
		*ref_value = -*ref_value;
	}
}

// <LegoRR.exe @0044d540>
void __cdecl lego::light::LightEffects_UpdateFade(float elapsed)
{
	if (!(globals::g_Light.flags & LIGHTEFFECTS_HASFADE /*0x4*/))
		return; // fade not setup, can't update

	if (!(globals::g_Light.flags & LIGHTEFFECTS_FADING /*0x8*/)) {
		/// STATE: 1 START FADE  (!0x8)

		globals::g_Light.fadeTime -= elapsed;
		if (globals::g_Light.fadeTime > 0.0f)
			return; // no need to update

		float time = util::randomChooseRange(globals::g_Light.RandomRangeForTimeBetweenFades.min,
											 globals::g_Light.RandomRangeForTimeBetweenFades.max);
		globals::g_Light.fadeTime = time;
		float hold = util::randomChooseRange(globals::g_Light.RandomRangeForHoldTimeOfFade.min,
											 globals::g_Light.RandomRangeForHoldTimeOfFade.max);
		globals::g_Light.fadeHoldTime = hold;

		// fadePosRGB = 0;
		globals::g_Light.fadePosRGB.red   = 0.0f;
		globals::g_Light.fadePosRGB.green = 0.0f;
		globals::g_Light.fadePosRGB.blue  = 0.0f;

		short rng = util::randomInt16();
		float value = (float)((int)rng % 1000) * 0.001f; // (... / 1000.0f)
		
		// fadeDestRGB = FadeRGBMin + randRange(abs(FadeRGBMax - FadeRGBMin));
		globals::g_Light.fadeDestRGB.red   = std::abs(globals::g_Light.FadeRGBMax.red   - globals::g_Light.FadeRGBMin.red)   * value + globals::g_Light.FadeRGBMin.red;
		globals::g_Light.fadeDestRGB.green = std::abs(globals::g_Light.FadeRGBMax.green - globals::g_Light.FadeRGBMin.green) * value + globals::g_Light.FadeRGBMin.green;
		globals::g_Light.fadeDestRGB.blue  = std::abs(globals::g_Light.FadeRGBMax.blue  - globals::g_Light.FadeRGBMin.blue)  * value + globals::g_Light.FadeRGBMin.blue;

		LightEffects_RandomizeFadeSpeedRGB();
		globals::g_Light.flags |= LIGHTEFFECTS_FADE_FORWARD|LIGHTEFFECTS_FADING /*0x10 | 0x8*/;

	}
	else if (globals::g_Light.flags & LIGHTEFFECTS_FADE_FORWARD /*0x10*/) {
		/// STATE: 2 FADING FORWARD  (0x10 && (0x8))

		// currentRGB += elapsed * fadeSpeedRGB;
		globals::g_Light.currentRGB.red   += elapsed * globals::g_Light.fadeSpeedRGB.red;
		globals::g_Light.currentRGB.green += elapsed * globals::g_Light.fadeSpeedRGB.green;
		globals::g_Light.currentRGB.blue  += elapsed * globals::g_Light.fadeSpeedRGB.blue;
		// fadePosRGB += elapsed * fadeSpeedRGB;
		globals::g_Light.fadePosRGB.red   += elapsed * globals::g_Light.fadeSpeedRGB.red;
		globals::g_Light.fadePosRGB.green += elapsed * globals::g_Light.fadeSpeedRGB.green;
		globals::g_Light.fadePosRGB.blue  += elapsed * globals::g_Light.fadeSpeedRGB.blue;

		// is negative speed?
		if ((elapsed * globals::g_Light.fadeSpeedRGB.red) < 0.0f) {

			if (globals::g_Light.fadePosRGB.red <= globals::g_Light.fadeDestRGB.red) {
				// count up to fadeDestRGB
				// currentRGB += (fadeDestRGB - fadePosRGB);
				globals::g_Light.currentRGB.red   += (globals::g_Light.fadeDestRGB.red   - globals::g_Light.fadePosRGB.red);
				globals::g_Light.currentRGB.green += (globals::g_Light.fadeDestRGB.green - globals::g_Light.fadePosRGB.green);
				globals::g_Light.currentRGB.blue  += (globals::g_Light.fadeDestRGB.blue  - globals::g_Light.fadePosRGB.blue);
				globals::g_Light.flags &= ~LIGHTEFFECTS_FADE_FORWARD /*~0x10*/;
			}
		}
		else {
			if (globals::g_Light.fadePosRGB.red >= globals::g_Light.fadeDestRGB.red) {
				// count down to fadeDestRGB
				// currentRGB -= (fadePosRGB - fadeDestRGB);
				globals::g_Light.currentRGB.red   -= (globals::g_Light.fadePosRGB.red   - globals::g_Light.fadeDestRGB.red);
				globals::g_Light.currentRGB.green -= (globals::g_Light.fadePosRGB.green - globals::g_Light.fadeDestRGB.green);
				globals::g_Light.currentRGB.blue  -= (globals::g_Light.fadePosRGB.blue  - globals::g_Light.fadeDestRGB.blue);
				globals::g_Light.flags &= ~LIGHTEFFECTS_FADE_FORWARD /*~0x10*/;
			}
		}
	}
	else if (!(globals::g_Light.flags & LIGHTEFFECTS_FADE_REVERSE /*0x20*/)) {
		/// STATE: 3 START REVERSE  (!0x20 && (!0x10 && 0x8))

		globals::g_Light.fadeHoldTime -= elapsed;
		if (globals::g_Light.fadeHoldTime > 0.0f)
			return; // no need to update

		LightEffects_RandomizeFadeSpeedRGB();

		// fadePosRGB = fadeDestRGB;
		globals::g_Light.fadePosRGB.red   = globals::g_Light.fadeDestRGB.red;
		globals::g_Light.fadePosRGB.green = globals::g_Light.fadeDestRGB.green;
		globals::g_Light.fadePosRGB.blue  = globals::g_Light.fadeDestRGB.blue;
		globals::g_Light.flags |= LIGHTEFFECTS_FADE_REVERSE /*0x20*/;
	}
	else {
		/// STATE: 4 FADING REVERSE  (0x20 && (!0x10 && 0x8))

		globals::g_Light.currentRGB.red   -= elapsed * globals::g_Light.fadeSpeedRGB.red;
		globals::g_Light.currentRGB.green -= elapsed * globals::g_Light.fadeSpeedRGB.green;
		globals::g_Light.currentRGB.blue  -= elapsed * globals::g_Light.fadeSpeedRGB.blue;
		globals::g_Light.fadePosRGB.red   -= elapsed * globals::g_Light.fadeSpeedRGB.red;
		globals::g_Light.fadePosRGB.green -= elapsed * globals::g_Light.fadeSpeedRGB.green;
		globals::g_Light.fadePosRGB.blue  -= elapsed * globals::g_Light.fadeSpeedRGB.blue;

		// is negative speed?
		if ((elapsed * globals::g_Light.fadeSpeedRGB.red) < 0.0f) {

			if (globals::g_Light.fadePosRGB.red >= 0.0f) {
				// count down to zero
				globals::g_Light.currentRGB.red   -= globals::g_Light.fadePosRGB.red;
				globals::g_Light.currentRGB.green -= globals::g_Light.fadePosRGB.green;
				globals::g_Light.currentRGB.blue  -= globals::g_Light.fadePosRGB.blue;
				globals::g_Light.flags &= ~(LIGHTEFFECTS_FADE_REVERSE|LIGHTEFFECTS_FADING) /*~(0x20|0x8)*/;
			}
		}
		else {
			if (globals::g_Light.fadePosRGB.red <= 0.0f) {
				// count up to zero
				globals::g_Light.currentRGB.red   -= globals::g_Light.fadePosRGB.red;
				globals::g_Light.currentRGB.green -= globals::g_Light.fadePosRGB.green;
				globals::g_Light.currentRGB.blue  -= globals::g_Light.fadePosRGB.blue;
				globals::g_Light.flags &= ~(LIGHTEFFECTS_FADE_REVERSE|LIGHTEFFECTS_FADING) /*~(0x20|0x8)*/;
			}
		}
	}
}

// <LegoRR.exe @0044d9d0>
void __cdecl lego::light::LightEffects_RandomizeFadeSpeedRGB(void)
{
	float value = util::randomChooseRange(globals::g_Light.RandomRangeForFadeTimeFade.min,
										  globals::g_Light.RandomRangeForFadeTimeFade.max);

	globals::g_Light.fadeSpeedRGB.red   = fadeDestRGB.red   / value;
	globals::g_Light.fadeSpeedRGB.green = fadeDestRGB.green / value;
	globals::g_Light.fadeSpeedRGB.blue  = fadeDestRGB.blue  / value;
}

// <LegoRR.exe @0044da20>
void __cdecl lego::light::LightEffects_UpdateMove(float elapsed)
{
	bool bVar1;
	float fVar2;
	BOOL BVar3;
	float10 fVar4;
	Vector3F local_18;
	Vector3F local_c;

	bVar1 = false;
	if (!(globals::g_Light.flags & LIGHTEFFECTS_HASMOVE /*0x40*/))
		return; // move not setup, can't update

	// flag 0x80 is set when light is currently moving, if unset, a new direction must be specified
	if (!(globals::g_Light.flags & LIGHTEFFECTS_MOVING /*0x80*/)) {
		globals::g_Light.moveTime -= elapsed;
		if (globals::g_Light.moveTime > 0.0f)
			return; // no need to update

		float time = util::randomChooseRange(globals::g_Light.RandomRangeForTimeBetweenMoves.min,
											 globals::g_Light.RandomRangeForTimeBetweenMoves.max);
		globals::g_Light.moveTime = time;

		float speed = util::randomChooseRange(globals::g_Light.RandomRangeForSpeedOfMove.min,
											  globals::g_Light.RandomRangeForSpeedOfMove.max);
		globals::g_Light.moveSpeed = speed;

		float dist = util::randomChooseRange(globals::g_Light.RandomRangeForDistOfMove.min,
											 globals::g_Light.RandomRangeForDistOfMove.max);
		globals::g_Light.moveDist = dist;

		// Randomize + Normalize vector, multiplied by speed.
		// AKA: speed in a random 3D direction.
		math::Vector3_Random(&globals::g_Light.vectorMove); // an existing alias for ::D3DRMVectorRandom(Vector3F*)
		float length = 1.0f / std::sqrt((globals::g_Light.vectorMove.x*globals::g_Light.vectorMove.x) +
										(globals::g_Light.vectorMove.y*globals::g_Light.vectorMove.y) +
										(globals::g_Light.vectorMove.z*globals::g_Light.vectorMove.z));

		globals::g_Light.vectorMove.x *= length * globals::g_Light.moveSpeed;
		globals::g_Light.vectorMove.y *= length * globals::g_Light.moveSpeed;
		globals::g_Light.vectorMove.z *= length * globals::g_Light.moveSpeed;

		// New movement calculated, start moving next update
		globals::g_Light.flags |= LIGHTEFFECTS_MOVING /*0x80*/;
	}
	else {
		// Currently moving
		Vector3F lastPosition = { 0.0f, 0.0f, 0.0f }; // dummy init
		res::Res_GetPosition(globals::g_Light.resSpotlight, globals::g_Light.resRootLight, &lastPosition);

		Vector3F newPosition = { 0.0f, 0.0f, 0.0f }; // dummy init
		newPosition.x = lastPosition.x + globals::g_Light.vectorMove.x;
		newPosition.y = lastPosition.y + globals::g_Light.vectorMove.y;
		newPosition.z = lastPosition.z + globals::g_Light.vectorMove.z;
		if (!LightEffects_CheckMoveLimit(&newPosition)) {
			
			// This is the same deal as the `LightEffects_UpdateBlink_FlipSign(float*)` tuple seen in UpdateBlink
			//  it's just that blink doesn't have extra math involved.
			newPosition.x = lastPosition.x - globals::g_Light.vectorMove.x;
			newPosition.y = lastPosition.y - globals::g_Light.vectorMove.y;
			newPosition.z = lastPosition.z - globals::g_Light.vectorMove.z;
			if (!LightEffects_CheckMoveLimit(&newPosition)) {

				// Not too sure, but a bad move vector (exceeds limit)? Recalculate vector.
				globals::g_Light.flags &= ~LIGHTEFFECTS_MOVING /*~0x80*/;
				return;
			}
		}

		// Update position
		res::Res_SetPosition(globals::g_Light.resSpotlight, globals::g_Light.resRootLight,
							 newPosition.x, newPosition.y, newPosition.z);

		globals::g_Light.moveDist -= globals::g_Light.moveSpeed;
		if (globals::g_Light.moveDist > 0.0f)
			return; // no need to update

		// Done moving, calculate a new move direction.
		globals::g_Light.flags &= ~LIGHTEFFECTS_MOVING /*~0x80*/;
		return;
	}
}

// <LegoRR.exe @0044dc60>
BOOL __cdecl lego::light::LightEffects_CheckMoveLimit(const Vector3F* vector)
{
	if (std::abs(vector->x - globals::g_Light.resPosition.x) > globals::g_Light.MoveLimit.x)
		return false;
	if (std::abs(vector->y - globals::g_Light.resPosition.y) > globals::g_Light.MoveLimit.y)
		return false;
	if (std::abs(vector->z - globals::g_Light.resPosition.z) > globals::g_Light.MoveLimit.z)
		return false;
	
	return true;
}

/// PUBLIC:
// This might be some sort of reset function
// <LegoRR.exe @0044dce0>
void __cdecl lego::light::LightEffects_SetDimmerMode(BOOL isDimoutMode)
{
	if (isDimoutMode) {
		globals::g_Light.flags &= ~LIGHTEFFECTS_DIMIN_DONE /*~0x400*/;
		globals::g_Light.flags |= LIGHTEFFECTS_DIMOUT /*0x200*/;
	}
	else {
		globals::g_Light.flags &= ~(LIGHTEFFECTS_DIMOUT_DONE|LIGHTEFFECTS_DIMOUT) /*~(0x1000 | 0x200)*/;
	}
}

/// PRIVATE:
// <LegoRR.exe @0044dd10>
void __cdecl lego::light::LightEffects_UpdateDimmer(float elapsed)
{
	if (!(globals::g_Light.flags & LIGHTEFFECTS_DIMOUT /*0x200*/)) {
		if (!(globals::g_Light.flags & LIGHTEFFECTS_DIMIN_DONE /*0x400*/)) {
			// currentRGB += (elapsed * 0.1f);
			globals::g_Light.currentRGB.red   += (elapsed * 0.1f);
			globals::g_Light.currentRGB.green += (elapsed * 0.1f);
			globals::g_Light.currentRGB.blue  += (elapsed * 0.1f);

			if (globals::g_Light.currentRGB.red >= globals::g_Light.initialRGB.red) {
				/// BUG: Uhhh... assigning blue to red?? This has to be a bug, right?
				///       Well, it doesn't matter since all 3 values are hardcoded to 0.8...
				globals::g_Light.currentRGB.red = globals::g_Light.initialRGB.blue;
				
				globals::g_Light.flags |= LIGHTEFFECTS_DIMIN_DONE /*0x400*/; // end of mode, now do nothing
			}
		}
		else {
			// do nothing
		}
	}
	else {
		if (!(globals::g_Light.flags & LIGHTEFFECTS_DIMOUT_DONE /*0x1000*/)) {
			// currentRGB -= (elapsed * 0.1f);
			globals::g_Light.currentRGB.red   -= (elapsed * 0.1f);
			globals::g_Light.currentRGB.green -= (elapsed * 0.1f);
			globals::g_Light.currentRGB.blue  -= (elapsed * 0.1f);

			if (globals::g_Light.currentRGB.red <= 0.0f) {
				globals::g_Light.currentRGB.red = 0.0f;

				globals::g_Light.flags |= LIGHTEFFECTS_DIMOUT_DONE /*0x1000*/; // end of mode, next time set currentRGB to 0
			}
		}
		else {
			// currentRGB = 0;
			globals::g_Light.currentRGB.red   = 0.0f;
			globals::g_Light.currentRGB.green = 0.0f;
			globals::g_Light.currentRGB.blue  = 0.0f;
		}
	}
}

#pragma endregion

