
#include "Standard.h"
#include "Errors.h"
#include "Mem.h"
#include "Quantizer.h"

VOID Quantizer_Hist3D(LPUWORD qAdd, ULONG size, LPUCHAR Ir, LPUCHAR Ig, LPUCHAR Ib, LPSLONG vwt, LPSLONG vmr, LPSLONG vmg, LPSLONG vmb, LPREAL m2) {
	
	ULONG ind, r, g, b;
	ULONG inr, ing, inb, table[256];
	ULONG i;
	
	for (i=0; i<256; ++i) table[i] = i*i;

	for (i=0 ; i<size; i++) {

		r = Ir[i];
		g = Ig[i];
		b = Ib[i];

		inr = (r>>3)+1;
		ing = (g>>3)+1;
		inb = (b>>3)+1;
		ind = (inr<<10) + (inr<<6) + inr + (ing<<5) + ing + inb;

		qAdd[i] = (UWORD) ind;
		/*[inr][ing][inb]*/

		++vwt[ind];
		vmr[ind] += r;
		vmg[ind] += g;
		vmb[ind] += b;
		m2[ind] += (REAL)(table[r]+table[g]+table[b]);
	}
}

VOID Quantizer_Moments3D(LPSLONG vwt, LPSLONG vmr, LPSLONG vmg, LPSLONG vmb, LPREAL m2) {

	UWORD ind1, ind2;
	UCHAR i, r, g, b;
	SLONG line, line_r, line_g, line_b, area[33], area_r[33], area_g[33], area_b[33];
	REAL line2, area2[33];
	
	for(r=1; r<=32; ++r){
		for(i=0; i<=32; ++i) {
			area2[i] = 0.0f;
			area[i] = area_r[i] = area_g[i] = area_b[i] = 0;
		}

		for(g=1; g<=32; ++g) {
			line2 = 0.0f;
			line = line_r = line_g = line_b = 0;
			for (b=1; b<=32; ++b){
				ind1 = (r<<10) + (r<<6) + r + (g<<5) + g + b; /* [r][g][b] */
				line += vwt[ind1];
				line_r += vmr[ind1]; 
				line_g += vmg[ind1]; 
				line_b += vmb[ind1];
				line2 += m2[ind1];
				area[b] += line;
				area_r[b] += line_r;
				area_g[b] += line_g;
				area_b[b] += line_b;
				area2[b] += line2;
				ind2 = ind1 - 1089; /* [r-1][g][b] */
				vwt[ind1] = vwt[ind2] + area[b];
				vmr[ind1] = vmr[ind2] + area_r[b];
				vmg[ind1] = vmg[ind2] + area_g[b];
				vmb[ind1] = vmb[ind2] + area_b[b];
				m2[ind1] = m2[ind2] + area2[b];
			}
		}
	}
}

SLONG Quantizer_Volume(lpQuantizerBox cube, SLONG mmt[33][33][33]) {

    return (
		mmt[cube->r1][cube->g1][cube->b1] 
	   -mmt[cube->r1][cube->g1][cube->b0]
	   -mmt[cube->r1][cube->g0][cube->b1]
	   +mmt[cube->r1][cube->g0][cube->b0]
	   -mmt[cube->r0][cube->g1][cube->b1]
	   +mmt[cube->r0][cube->g1][cube->b0]
	   +mmt[cube->r0][cube->g0][cube->b1]
	   -mmt[cube->r0][cube->g0][cube->b0]
	   );
}

SLONG Quantizer_Bottom(lpQuantizerBox cube, UCHAR dir, SLONG mmt[33][33][33]) {

	switch(dir){
	case QUANTIZER_RED:
		return(
			-mmt[cube->r0][cube->g1][cube->b1]
			+mmt[cube->r0][cube->g1][cube->b0]
			+mmt[cube->r0][cube->g0][cube->b1]
			-mmt[cube->r0][cube->g0][cube->b0] );
		break;
	case QUANTIZER_GREEN:
		return(
			-mmt[cube->r1][cube->g0][cube->b1]
			+mmt[cube->r1][cube->g0][cube->b0]
			+mmt[cube->r0][cube->g0][cube->b1]
			-mmt[cube->r0][cube->g0][cube->b0] );
		break;
	case QUANTIZER_BLUE:
		return(
			-mmt[cube->r1][cube->g1][cube->b0]
			+mmt[cube->r1][cube->g0][cube->b0]
			+mmt[cube->r0][cube->g1][cube->b0]
			-mmt[cube->r0][cube->g0][cube->b0] );
		break;
	}

	return 0;
}

SLONG Quantizer_Top(lpQuantizerBox cube, UCHAR dir, SLONG pos, SLONG mmt[33][33][33]) {

	switch(dir){
	case QUANTIZER_RED:
		return(
			mmt[pos][cube->g1][cube->b1] 
			-mmt[pos][cube->g1][cube->b0]
			-mmt[pos][cube->g0][cube->b1]
			+mmt[pos][cube->g0][cube->b0] );
		break;
	case QUANTIZER_GREEN:
		return(
			mmt[cube->r1][pos][cube->b1] 
			-mmt[cube->r1][pos][cube->b0]
			-mmt[cube->r0][pos][cube->b1]
			+mmt[cube->r0][pos][cube->b0] );
		break;
	case QUANTIZER_BLUE:
		return(
			mmt[cube->r1][cube->g1][pos]
			-mmt[cube->r1][cube->g0][pos]
			-mmt[cube->r0][cube->g1][pos]
			+mmt[cube->r0][cube->g0][pos] );
		break;
	}

	return 0;
}

REAL Quantizer_Variance(lpQuantizerBox cube, SLONG wt[33][33][33], SLONG mr[33][33][33], SLONG mg[33][33][33], SLONG mb[33][33][33], REAL gm2[33][33][33]) {

	REAL dr, dg, db, xx;
	
	dr = (REAL) Quantizer_Volume(cube, mr); 
	dg = (REAL) Quantizer_Volume(cube, mg); 
	db = (REAL) Quantizer_Volume(cube, mb);
	xx = gm2[cube->r1][cube->g1][cube->b1] 
		-gm2[cube->r1][cube->g1][cube->b0]
		-gm2[cube->r1][cube->g0][cube->b1]
		+gm2[cube->r1][cube->g0][cube->b0]
		-gm2[cube->r0][cube->g1][cube->b1]
		+gm2[cube->r0][cube->g1][cube->b0]
		+gm2[cube->r0][cube->g0][cube->b1]
		-gm2[cube->r0][cube->g0][cube->b0];
	
	return (xx - (dr*dr+dg*dg+db*db)/ (REAL) Quantizer_Volume(cube,wt));
}

REAL Quantizer_Maximize(lpQuantizerBox cube, UCHAR dir, SLONG first, SLONG last, LPSLONG cut, SLONG whole_r, SLONG whole_g, SLONG whole_b, SLONG whole_w, SLONG wt[33][33][33], SLONG mr[33][33][33], SLONG mg[33][33][33], SLONG mb[33][33][33]) {

	SLONG half_r, half_g, half_b, half_w;
	SLONG base_r, base_g, base_b, base_w;
	SLONG i;
	REAL temp, max;
	
	base_r = Quantizer_Bottom(cube, dir, mr);
	base_g = Quantizer_Bottom(cube, dir, mg);
	base_b = Quantizer_Bottom(cube, dir, mb);
	base_w = Quantizer_Bottom(cube, dir, wt);
	max = 0.0;
	*cut = -1;
	for(i=first; i<last; ++i){
		half_r = base_r + Quantizer_Top(cube, dir, i, mr);
		half_g = base_g + Quantizer_Top(cube, dir, i, mg);
		half_b = base_b + Quantizer_Top(cube, dir, i, mb);
		half_w = base_w + Quantizer_Top(cube, dir, i, wt);
		/* now half_x is sum over lower half of box, if split at i */
		if (half_w == 0) {      /* subbox could be empty of pixels! */
			continue;             /* never split into an empty box */
		} else
			temp = ((REAL)half_r*half_r + (REAL)half_g*half_g +
			(REAL)half_b*half_b)/half_w;
		
		half_r = whole_r - half_r;
		half_g = whole_g - half_g;
		half_b = whole_b - half_b;
		half_w = whole_w - half_w;
		if (half_w == 0) {      /* subbox could be empty of pixels! */
			continue;             /* never split into an empty box */
		} else
			temp += ((REAL)half_r*half_r + (REAL)half_g*half_g +
			(REAL)half_b*half_b)/half_w;
		
		if (temp > max) {max=temp; *cut=i;}
	}
	return(max);
}

BOOL Quantizer_Cut(lpQuantizerBox set1, lpQuantizerBox set2, SLONG wt[33][33][33], SLONG mr[33][33][33], SLONG mg[33][33][33], SLONG mb[33][33][33]) {

	UCHAR dir;
	SLONG cutr, cutg, cutb;
	REAL maxr, maxg, maxb;
	SLONG whole_r, whole_g, whole_b, whole_w;
	
	whole_r = Quantizer_Volume(set1, mr);
	whole_g = Quantizer_Volume(set1, mg);
	whole_b = Quantizer_Volume(set1, mb);
	whole_w = Quantizer_Volume(set1, wt);
	
	maxr = Quantizer_Maximize(set1, QUANTIZER_RED, set1->r0+1, set1->r1, &cutr, whole_r, whole_g, whole_b, whole_w, wt, mr, mg, mb);
	maxg = Quantizer_Maximize(set1, QUANTIZER_GREEN, set1->g0+1, set1->g1, &cutg, whole_r, whole_g, whole_b, whole_w, wt, mr, mg, mb);
	maxb = Quantizer_Maximize(set1, QUANTIZER_BLUE, set1->b0+1, set1->b1, &cutb, whole_r, whole_g, whole_b, whole_w, wt, mr, mg, mb);
	
	if ((maxr>=maxg) && (maxr>=maxb)) {
		dir = QUANTIZER_RED;
		if (cutr < 0) return FALSE;
	} else if ((maxg>=maxr) && (maxg>=maxb)) dir = QUANTIZER_GREEN;
	else dir = QUANTIZER_BLUE; 
	
	set2->r1 = set1->r1;
	set2->g1 = set1->g1;
	set2->b1 = set1->b1;
	
	switch (dir){
	case QUANTIZER_RED:
		set2->r0 = set1->r1 = cutr;
		set2->g0 = set1->g0;
		set2->b0 = set1->b0;
		break;
	case QUANTIZER_GREEN:
		set2->g0 = set1->g1 = cutg;
		set2->r0 = set1->r0;
		set2->b0 = set1->b0;
		break;
	case QUANTIZER_BLUE:
		set2->b0 = set1->b1 = cutb;
		set2->r0 = set1->r0;
		set2->g0 = set1->g0;
		break;
	}
	set1->vol=(set1->r1-set1->r0)*(set1->g1-set1->g0)*(set1->b1-set1->b0);
	set2->vol=(set2->r1-set2->r0)*(set2->g1-set2->g0)*(set2->b1-set2->b0);

	return TRUE;
}

VOID Quantizer_Mark(lpQuantizerBox cube, SLONG label, LPUCHAR tag) {

	SLONG r, g, b;
	
	for (r=cube->r0+1 ; r<=cube->r1 ; ++r) {
		for (g=cube->g0+1 ; g<=cube->g1 ; ++g) {
			for (b=cube->b0+1 ; b<=cube->b1 ; ++b) {
				tag[(r<<10) + (r<<6) + r + (g<<5) + g + b] = (UCHAR) label;
			}
		}
	}
}

LPULONG Quantizer_Generate(LPUCHAR rList, LPUCHAR gList, LPUCHAR bList, ULONG width, ULONG height, LPUCHAR dest, ULONG destPitch, LPULONG colourCount) {

	// Takes the list of red, green and blue values and outputs them to the destination buffer as
	// a quantized images with the specified number of colour levels..
	// Uses 15bit colour precision.
	
	struct QuantizerBox cube[256];
	SLONG wt[33][33][33] = { 0 };
	SLONG mr[33][33][33] = { 0 };
	SLONG mg[33][33][33] = { 0 };
	SLONG mb[33][33][33] = { 0 };
	REAL gm2[33][33][33] = { 0.0f };
	REAL vv[256], temp;
	SLONG next, weight;
	ULONG i, k, x, y;
	LPULONG clut;
	LPUCHAR tag;
	LPUWORD qAdd;
	UCHAR r, g, b;
	
	Error_Fatal(NULL==colourCount||*colourCount>256, "Invalid colour count specified (0-256)");
	
	qAdd = Mem_AllocClear(sizeof(qAdd[0]) * width * height);
	
	Quantizer_Hist3D(qAdd, width * height, rList, gList, bList, (LPSLONG) wt, (LPSLONG) mr, (LPSLONG) mg, (LPSLONG) mb, (LPREAL) gm2);
	Quantizer_Moments3D((LPSLONG) wt, (LPSLONG) mr, (LPSLONG) mg, (LPSLONG) mb, (LPREAL) gm2);
	
	cube[0].r0 = cube[0].g0 = cube[0].b0 = 0;
	cube[0].r1 = cube[0].g1 = cube[0].b1 = 32;
	
	next = 0;
	for(i=1 ; i<*colourCount ; ++i) {
		if (Quantizer_Cut(&cube[next], &cube[i], wt, mr, mg, mb)) {
			vv[next] = (cube[next].vol>1) ? Quantizer_Variance(&cube[next], wt, mr, mg, mb, gm2) : 0.0f;
			vv[i] = (cube[i].vol>1) ? Quantizer_Variance(&cube[i], wt, mr, mg, mb, gm2) : 0.0f;
		} else {
			vv[next] = 0.0;
			i--;
		}
		next = 0; temp = vv[0];
		for(k=1; k<=i; ++k) {
			if (vv[k] > temp) {
				temp = vv[k]; next = k;
			}
		}
		if (temp <= 0.0) {
			*colourCount = i+1;
			break;
		}
	}
	
	tag = Mem_AllocClear(33*33*33);
	clut = Mem_AllocClear(sizeof(clut[0]) * *colourCount);
	
	for(k=0 ; k<*colourCount ; ++k){
		Quantizer_Mark(&cube[k], k, tag);
		weight = Quantizer_Volume(&cube[k], wt);
		if (weight) {
			r = (UCHAR) (Quantizer_Volume(&cube[k], mr) / weight);
			g = (UCHAR) (Quantizer_Volume(&cube[k], mg) / weight);
			b = (UCHAR) (Quantizer_Volume(&cube[k], mb) / weight);
			clut[k] = (r<<16)|(g<<8)|(b);
		} else {
			Error_Warn(TRUE, Error_Format("Bogus box %d\n", k));
			clut[k] = 0;
		}
	}
	
	for (y=0 ; y<height ; y++) {
		for (x=0 ; x<width ; x++) {
			dest[(y * destPitch) + x] = tag[qAdd[(y * width) + x]];
		}
	}
	
	Mem_Free(tag);
	Mem_Free(qAdd);
	
	return clut;
}
