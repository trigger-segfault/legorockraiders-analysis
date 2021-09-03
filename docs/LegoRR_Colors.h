
// <LegoRR.exe@ 004a9f28>
ColorRGBF radarColours[30];
radarColours[0]  = rgb(255,204,  0); // 0xd: REINFORCEMENT (border drawn around block)
radarColours[1]  = rgb( 45,  0, 75); // 0x11: CAVERN (floor/ground)
radarColours[2]  = rgb( 41, 96,255); // 0x7: WATER (unused, see: LAKE)
radarColours[3]  = rgb(255, 90,  0); // 0x6: LAVA
radarColours[4]  = rgb(164,227,149); // 0x5 && ??: SOIL (unused)
radarColours[5]  = rgb( 97,203, 86); // 0x4 && ??: LOOSE (dirt)
radarColours[6]  = rgb(  0,175, 12); // 0x3 && ??: MEDIUM (loose rock)
radarColours[7]  = rgb(  0, 93,  0); // 0x2 && ??: HARD (hard rock)
radarColours[8]  = rgb(  0, 47,  0); // 0x1 && ??: IMMOVABLE (solid rock)
radarColours[9]  = rgb(199,123,255); // 0x5 && exposed: SOIL (unused)
radarColours[10] = rgb(174, 89,233); // 0x4 && exposed: LOOSE (dirt)
radarColours[11] = rgb(144, 60,200); // 0x3 && exposed: MEDIUM (loose rock)
radarColours[12] = rgb(115, 30,168); // 0x2 && exposed: HARD (hard rock)
radarColours[13] = rgb( 86,  2,136); // 0x1 && exposed: IMMOVABLE (solid rock)
radarColours[14] = rgb(255,204,  0); // FRIENDLY UNIT (and everything else)
radarColours[15] = rgb(255,  0,  0); // ROCKMONSTER
radarColours[16] = rgb(  0,255,  0); // ORE, CRYSTAL
radarColours[17] = rgb(255,123,251); // 0x5 && ??: SOIL (unused)
radarColours[18] = rgb(233, 89,226); // 0x4 && ??: LOOSE (dirt)
radarColours[19] = rgb(200, 60,192); // 0x3 && ??: MEDIUM (loose rock)
radarColours[20] = rgb(168, 30,158); // 0x2 && ??: HARD (hard rock)
radarColours[21] = rgb(136,  2,125); // 0x1 && ??: IMMOVABLE (solid rock)
radarColours[22] = rgb(255,255,  0); // 0xe: PATH (powered)
radarColours[23] = rgb(157,155,  0); // 0xe: PATH (unpowered)
radarColours[24] = rgb(155, 65, 14); // 0x8: ORESEAM
radarColours[25] = rgb(180,255,  0); // 0xa: CRYSTALSEAM
radarColours[26] = rgb(255,255,  0); // 0xb: RECHARGESEAM (and everything else)
radarColours[27] = rgb(  0, 47,181); // 0x9: LAKE
radarColours[28] = rgb(191,191,191); // flags1=0x100000: FOUNDATION (building path)
radarColours[29] = rgb(108,  0,  0); // 0x10 && flags1=0x20000: UNDISCOVERED

/// UNUSED:
// <LegoRR.exe@ 004abeb8>
ColourRGBPacked basicColours[8];
basicColours[0] = rgb(  0,  0,  0);
basicColours[1] = rgb(255,255,255);
basicColours[2] = rgb(255,  0,  0);
basicColours[3] = rgb(  0,255,  0);
basicColours[4] = rgb(  0,  0,255);
basicColours[5] = rgb(255,255,  0);
basicColours[6] = rgb(255,  0,255);
basicColours[7] = rgb(  0,255,255);

