  globs::s_CryShift_Table[0][5] = crystals;
  // local_70 = tableCounts;
  globs::s_CryShift_Table[1][5] = usedCrystals;
  //int i = 0;
  //pBaseCount = baseCounts;
  //do {
    // int j = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 6; j++) {
      int k = 0;
			for (k = 0; k < baseCounts[i]; k++) {
				if (tableCounts[i][k].cryCount == globs::s_CryShift_Table[i][j]) {
					tableCounts[i][k].unkCount += 1;
					break;
				}
			}
      // if (*pBaseCount != 0) {
      //   // pCVar6 = local_70;
      //   do {
      //     if (tableCounts[i][k].cryCount == globs::s_CryShift_Table[i][j]) {
      //       tableCounts[i][k].unkCount += 1;
      //       break;
      //     }
      //     k += 1;
      //     // pCVar6 = pCVar6 + 1;
      //   } while (k < *pBaseCount);
      // }
      if (k == baseCounts[i]) {
        tableCounts[i][k].cryCount = globs::s_CryShift_Table[i][j];
        tableCounts[i][k].unkCount = 1;
        baseCounts[i] += 1;
      }
      // j += 1;
    } //while (j < 6);
    //i += 6;
    // local_70 = local_70 + 6;
    // pBaseCount = pBaseCount + 1;
  } //while( true );


	for (int i = 0; i < 2; i++) {

	// int i = 0;
	// do {
		uint baseCount = baseCounts[i];
		uint maxFound = 0;
		// if (baseCount != 0) {
		pCVar6 = tableCounts;
		pCryUnkCount = &tableCounts[i][0];//.unkCount;
		for (int k = 0; k < baseCounts[i]; k++) {
		// do {
			if (maxFound < tableCounts[i][k].unkCount) {
				maxFound = tableCounts[i][k].unkCount;
				if (i == 0) {
					crystals = tableCounts[0][k].cryCount;
				}
				else {
					usedCrystals = tableCounts[i][k].cryCount;
				}
			}
			pCVar6++;
			pCryUnkCount++;
			baseCount--;
		} //while (baseCount != 0);
		// }
	// 	i += 1;
	} //while (i < 2);