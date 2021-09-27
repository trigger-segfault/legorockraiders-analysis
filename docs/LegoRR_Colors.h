
/////////////////////////////////////////////////////////////////////
/// DRAW: Radar Map tiles
//
// <LegoRR.exe@ 004a9f28> (data)
ColourRGBF radarColours[30];
radarColours[0]  = rgb(255,204,  0); // 0xd: REINFORCEMENT (border drawn around block)
radarColours[1]  = rgb( 45,  0, 75); // 0x11: CAVERN (floor/ground)
radarColours[2]  = rgb( 41, 96,255); // 0x7: WATER (unused, see: LAKE)
radarColours[3]  = rgb(255, 90,  0); // 0x6: LAVA
radarColours[4]  = rgb(164,227,149); // 0x5 && scanned: SOIL (unused)
radarColours[5]  = rgb( 97,203, 86); // 0x4 && scanned: LOOSE (dirt)
radarColours[6]  = rgb(  0,175, 12); // 0x3 && scanned: MEDIUM (loose rock)
radarColours[7]  = rgb(  0, 93,  0); // 0x2 && scanned: HARD (hard rock)
radarColours[8]  = rgb(  0, 47,  0); // 0x1 && scanned: IMMOVABLE (solid rock)
radarColours[9]  = rgb(199,123,255); // 0x5 && exposed: SOIL (unused)
radarColours[10] = rgb(174, 89,233); // 0x4 && exposed: LOOSE (dirt)
radarColours[11] = rgb(144, 60,200); // 0x3 && exposed: MEDIUM (loose rock)
radarColours[12] = rgb(115, 30,168); // 0x2 && exposed: HARD (hard rock)
radarColours[13] = rgb( 86,  2,136); // 0x1 && exposed: IMMOVABLE (solid rock)
radarColours[14] = rgb(255,204,  0); // FRIENDLY UNIT (and everything else)
radarColours[15] = rgb(255,  0,  0); // ROCKMONSTER
radarColours[16] = rgb(  0,255,  0); // ORE, CRYSTAL
radarColours[17] = rgb(255,123,251); // 0x5 && tunneled: SOIL (unused)
radarColours[18] = rgb(233, 89,226); // 0x4 && tunneled: LOOSE (dirt)
radarColours[19] = rgb(200, 60,192); // 0x3 && tunneled: MEDIUM (loose rock)
radarColours[20] = rgb(168, 30,158); // 0x2 && tunneled: HARD (hard rock)
radarColours[21] = rgb(136,  2,125); // 0x1 && tunneled: IMMOVABLE (solid rock)
radarColours[22] = rgb(255,255,  0); // 0xe: PATH (powered)
radarColours[23] = rgb(157,155,  0); // 0xe: PATH (unpowered)
radarColours[24] = rgb(155, 65, 14); // 0x8: ORESEAM
radarColours[25] = rgb(180,255,  0); // 0xa: CRYSTALSEAM
radarColours[26] = rgb(255,255,  0); // 0xb: RECHARGESEAM (and everything else)
radarColours[27] = rgb(  0, 47,181); // 0x9: LAKE
radarColours[28] = rgb(191,191,191); // flags1=0x100000: FOUNDATION (building path)
radarColours[29] = rgb(108,  0,  0); // 0x10 && flags1=0x20000: UNDISCOVERED


/////////////////////////////////////////////////////////////////////
/// DRAW: Radar Camera view
// _________________
// \       .       /
//  \     / \ <---/-- Arrow
//   \   /_ _\   /  
//    \   | |   /   
//     \  |_|  /<---- Ray(?)
//      \_____/     
//
// effect = DrawEffect_HalfTrans;
//
// <LegoRR.exe@ 0045de80> (function)
ColourRGBF radarCameraArrowLineColour = rgb(255,255,255);
ColourRGBF radarCameraRayLineColour   = rgb(178,178,178);


/////////////////////////////////////////////////////////////////////
/// DRAW: Radar Survey/Scanner dots
//     /A\        
//    . - .       
// .'       '.    
// -    :)   - >>>
// '.       .'  | 
//    ` - `     +- Units' circles all expand in unison
//     \V/ <----+ 
//
// colour *= (1.0 - (liveGlobs.radarElapsed_67c / 25.0))
//
// <LegoRR.exe@ 0045ddc0> (function)
ColourRGBF radarSurveyDotsColour = rgb(178,229,255);


/////////////////////////////////////////////////////////////////////
/// DRAW: SelectBoxRGB
//  __  __ 
// |      |
//    :)   
// |__  __|
//
// if (GAME1_CAMERADISABLED) colour *= 0.3;
//
/// DRAW: Selected unit box
// <LegoRR.exe@ 00424700> (function)
ColourRGBF trackerSelectBox       = rgb(255,  0,  0); // laser tracker state
// <LegoRR.exe@ 00424760> (function)
ColourRGBF primaryUnitSelectBox   = rgb(  0,255,  0);
ColourRGBF secondaryUnitSelectBox = rgb(255,255,  0);
//
/// DRAW: Encyclopedia unit box
// <LegoRR.exe@ 0040e800> (function)
ColourRGBF encyclopediaSelectBox  = rgb(  0,255,  0); // unused feature


/////////////////////////////////////////////////////////////////////
/// DRAW: DragBoxRGB
//   _____ 
//  |     |
//  |_____|
//       /A
//
// <LegoRR.exe@ 0041fa80> (function, cfg)
ColourRGBF dragBoxColourDefault = rgb( 51,178,255);


/////////////////////////////////////////////////////////////////////
/// DRAW: BorderBox (just like Windows 95 button shading)
//
// hhhhhhhh/l
// h|ffffff|l
// h|ffffff|l
// h/llllllll
//
/// DRAW: RewardTextBackgroundBox
//
// <LegoRR.exe@ 00461a50> (function)
// if (REWARDITEM_NAMETEXT_HALFTRANS) effect = DrawEffect_HalfTrans;
ColourRGBF rewardBoxColours[3]; // { fill, high, low }
rewardBoxColours[0] = rgb( 30, 30, 30);
rewardBoxColours[1] = rgb( 59, 59, 59);
rewardBoxColours[2] = rgb(  0,  0,  0);
//
/// DRAW: ToolTipRGB
//
// <LegoRR.exe@ 0046b490> (function, cfg)
ColourRGBF toolTipBoxColourDefault = rgb( 83, 83, 83);
ColourRGBF toolTipBoxColours[3]; // { fill, high, low }
toolTipBoxColours[0] = colour;
toolTipBoxColours[1] = colour * 1.4; // clamp((colour+colour*0.4), 0, 255)
toolTipBoxColours[2] = colour * 0.6; // clamp((colour-colour*0.4), 0, 255)


/////////////////////////////////////////////////////////////////////
/// MESH: Selected block highlight ("WallHighlight")
//
// <LegoRR.exe@ 004a62c0> (data)
ColourRGBF wallHighlightColours[6];
wallHighlightColours[0] = rgb(255,255,255); // <none>
wallHighlightColours[1] = rgb(127,127,127); // Drill
wallHighlightColours[2] = rgb(255,127,102); // Dynamite
wallHighlightColours[3] = rgb(127,255,127); // Reinforce
wallHighlightColours[4] = rgb(102,127,255); // Selected
wallHighlightColours[5] = rgb(153,153,  0); // Tutorial


/////////////////////////////////////////////////////////////////////
/// MESH: Water tile ("Water", flood water unused feature)
//
// <LegoRR.exe@ 0046e140> (function)
ColourRGBAF waterPoolMeshColour = rgba(   0,76,204,153);


/////////////////////////////////////////////////////////////////////
/// MESH: Building placement highlights ("SelectPlace")
//
// <LegoRR.exe@ 00464480> (function)
ColourRGBAF selectPlaceMeshColours[5]; // (not a real array)
selectPlaceMeshColours[0] = rgba(153,  0,  0, 51); // Occupied tile / no path connection (all tiles red)
selectPlaceMeshColours[1] = rgba(178,178,  0, 51); // OK Path tile
selectPlaceMeshColours[2] = rgba(178,  0,178, 51); // Too rough Building tile
selectPlaceMeshColours[3] = rgba(  0,178, 25, 51); // OK Building tile
selectPlaceMeshColours[4] = rgba(  0,178,229, 51); // OK Water tile


/////////////////////////////////////////////////////////////////////
/// UNUSED:
//
// <LegoRR.exe@ 004abeb8> (data)
ColourRGBPacked basicColours[8];
basicColours[0] = rgb(  0,  0,  0);
basicColours[1] = rgb(255,255,255);
basicColours[2] = rgb(255,  0,  0);
basicColours[3] = rgb(  0,255,  0);
basicColours[4] = rgb(  0,  0,255);
basicColours[5] = rgb(255,255,  0);
basicColours[6] = rgb(255,  0,255);
basicColours[7] = rgb(  0,255,255);
