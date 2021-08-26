/****************************************************************************************/
/* Header Files																			*/
/****************************************************************************************/

#include <windows.h>
#include <ddraw.h>
#include <vfw.h>
#include "inc\Animation.h"

//////////////////////////
// STUFF!!!!!!
//////////////////////////

inline int Release(LPVOID &arg) { 
	int count = -1; 
	LPUNKNOWN lpUnk = (LPUNKNOWN) arg;
	if (lpUnk) { count = lpUnk->Release(); arg = 0; } 
	return count;
}

bool g98NoAvis = false;

extern "C" char *File_VerifyFilename(char *);

/****************************************************************************************/
/* CPP File  																			*/
/****************************************************************************************/


// Surface.cpp: implementation of the G98CSurface class.
//
//////////////////////////////////////////////////////////////////////

LPDIRECTDRAW4 ddraw = 0;

static unsigned char std8BitColourTable[8][3] = {
	{ 0,   0,   0   },					// Black
	{ 255, 255, 255 },					// White
	{ 255, 0,   0   },					// Red
	{ 0,   255, 0   },					// Green
	{ 0,   0,   255 },					// Blue
	{ 255, 255, 0   },					// Yellow
	{ 255, 0,   255 },					// Purple
	{ 0,   255, 255 }					// Cyan
};

//////////////////////////////////////////////////////////////////////
// Debug macros
//////////////////////////////////////////////////////////////////////

#define hResDecl(x)				\
	case x:						\
	OutputDebugString(#x"\n");	\
	break;

#define DDhRes(hRes)			\
switch (hRes) {					\
case 0:							\
	break;						\
hResDecl(DDERR_GENERIC)			\
hResDecl(DDERR_INVALIDCLIPLIST)	\
hResDecl(DDERR_INVALIDOBJECT)	\
hResDecl(DDERR_INVALIDPARAMS)	\
hResDecl(DDERR_INVALIDRECT)		\
hResDecl(DDERR_NOALPHAHW)		\
hResDecl(DDERR_NOBLTHW)			\
hResDecl(DDERR_NOCLIPLIST)		\
hResDecl(DDERR_NODDROPSHW)		\
hResDecl(DDERR_NOMIRRORHW)		\
hResDecl(DDERR_NORASTEROPHW)	\
hResDecl(DDERR_NOROTATIONHW)	\
hResDecl(DDERR_NOSTRETCHHW)		\
hResDecl(DDERR_NOZBUFFERHW)		\
hResDecl(DDERR_SURFACEBUSY)		\
hResDecl(DDERR_SURFACELOST)		\
hResDecl(DDERR_UNSUPPORTED)		\
hResDecl(DDERR_WASSTILLDRAWING)	\
default:						\
	OutputDebugString(			\
	"Unkown DD error"			\
	);							\
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

G98CSurface::G98CSurface(bool fullscreen) : 
	m_squashToEdge(false), m_15bit(false)
{
	PreInit(fullscreen);
}

G98CSurface::~G98CSurface()
{

	// Release the surface.
	Release((void*&)m_surf);
	Release((void*&)m_palette);

	// Release DirectDraw reference
/*	if (ddraw) {
		LPVOID tempdd = ddraw;
		if (0 == (refCount = Release(tempdd))) {
			Info(true, "DirectDraw has been shutdown");
			ddraw = 0;
		}
	}*/
}

G98CSurface::G98CSurface(int width, int height, int bpp, bool vram, bool fullScreen) :
	m_clipper(0), m_surf(0), m_squashToEdge(false), m_15bit(false)
{
	m_surfaceInited = false;
	PreInit(fullScreen);
	if (Init(width, height, bpp, vram)) 
		m_surfaceInited = true;
}

bool G98CSurface::Init(int width, int height, int bpp, bool vram)
{
	m_desc.dwFlags |= 
		(width  == 0 ? 0 : DDSD_WIDTH)  | 
		(height == 0 ? 0 : DDSD_HEIGHT) | 
		 DDSD_CAPS;

	m_bpp = bpp;
	if (width  != 0) m_desc.dwWidth  = width;
	if (height != 0) m_desc.dwHeight = height;
	if (!width && !height) {
		// We want the whole front buffer if no size specced.
		m_desc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	} else {
		m_desc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
		if (vram) m_desc.ddsCaps.dwCaps |= DDSCAPS_VIDEOMEMORY;
		else m_desc.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
	}

	if (0 != bpp) {
		m_desc.dwFlags |= DDSD_PIXELFORMAT;
		m_desc.ddpfPixelFormat.dwSize = sizeof(m_desc.ddpfPixelFormat);
		m_desc.ddpfPixelFormat.dwRGBBitCount = (bpp == 15) ? 16 : bpp;
		if (bpp == 24) {
			m_desc.ddpfPixelFormat.dwRBitMask = 0x00ff0000;
			m_desc.ddpfPixelFormat.dwGBitMask = 0x0000ff00;
			m_desc.ddpfPixelFormat.dwBBitMask = 0x000000ff;
			m_desc.ddpfPixelFormat.dwFlags = DDPF_RGB;
		} else if (bpp == 16) {
			m_desc.ddpfPixelFormat.dwRBitMask = 0x0000f800;
			m_desc.ddpfPixelFormat.dwGBitMask = 0x000007e0;
			m_desc.ddpfPixelFormat.dwBBitMask = 0x0000001f;
			m_desc.ddpfPixelFormat.dwFlags = DDPF_RGB;
		} else if (bpp == 15) {
			m_desc.ddpfPixelFormat.dwRBitMask = 0x00007c00;
			m_desc.ddpfPixelFormat.dwGBitMask = 0x000003e0;
			m_desc.ddpfPixelFormat.dwBBitMask = 0x0000001f;
			m_desc.ddpfPixelFormat.dwFlags = DDPF_RGB;
		} else if (bpp == 8) {
			m_desc.ddpfPixelFormat.dwRBitMask = 0x00ff0000;		// I Doubt that the masks are valid 
			m_desc.ddpfPixelFormat.dwGBitMask = 0x0000ff00;		// but wont seem to work otherwise
			m_desc.ddpfPixelFormat.dwBBitMask = 0x000000ff;
			m_desc.ddpfPixelFormat.dwFlags = DDPF_PALETTEINDEXED8 | DDPF_RGB;
		}
	}

	if (DD_OK == ddraw->CreateSurface(&m_desc, &m_surf, 0)) {
		Lock();
		Unlock();
		if (m_desc.ddpfPixelFormat.dwRGBBitCount == 8) {
			PALETTEENTRY pal[256];
			for (int i=0; i<256; i++) {
				pal[i].peRed   = 0;
				pal[i].peGreen = 0;
				pal[i].peBlue  = 0;
				pal[i].peFlags = 0;
			}
			if (DD_OK != ddraw->CreatePalette(DDPCAPS_8BIT, pal, &m_palette, 0)) {
				return false;
			}
			if (DD_OK != m_surf->SetPalette(m_palette)) {
				return false;
			}
		}

		// Last thing is to lock the surface and get it info.
		int maskCount;
		if (16 == m_desc.ddpfPixelFormat.dwRGBBitCount) {
			if ((maskCount = CountMaskBits(m_desc.ddpfPixelFormat.dwRBitMask) + 
				 CountMaskBits(m_desc.ddpfPixelFormat.dwGBitMask) + 
				 CountMaskBits(m_desc.ddpfPixelFormat.dwBBitMask)) == 15) m_15bit = true;
		}
		return true;
	} else {
		return false;
	}
}

void G98CSurface::PreInit(bool fullScreen)
{

	if (!ddraw) {

		///////////////////////
		// ROB THROW AN ERROR - must have ddraw
		///////////////////////

	} else {
		///////////////////////
		//
		// ROB - I AddRef ddraw and remove it in destructor
		//
		///////////////////////

	}

	memset(&m_desc, 0, sizeof(DDSURFACEDESC2));
	m_desc.dwSize = sizeof(DDSURFACEDESC2);
	m_surf = 0;
	m_palette = 0;
	m_surfaceLocked = false;
	m_colourKeyed = false;
}

DWORD G98CSurface::MakeColourFromSurface(unsigned char r, 
									  unsigned char g, 
									  unsigned char b) {
	DWORD dw = 0;
	unsigned char *ptr = (unsigned char*) &dw;

	if (!m_surfaceInited) return 0;

	switch (Bpp()) {
	case 8:
		{
			// Find thge nearest colour to this
			int diff[8];
			for (int i=1; i<9; i++) {
				diff[i-1] = 0;
				diff[i-1] += abs(r - std8BitColourTable[i-1][0]);
				diff[i-1] += abs(g - std8BitColourTable[i-1][0]);
				diff[i-1] += abs(b - std8BitColourTable[i-1][0]);
			}
			// Find the minimal entry (ie the closest colour).
			int minEntry = 0;
			for (i=1; i<8; i++) {
				if (diff[i]<diff[minEntry]) minEntry = i;
			}
		}
		break;
	case 24:
	case 32:
		ptr[0] = b;
		ptr[1] = g;
		ptr[2] = r;
		break;
	case 15:
		dw = Convert15Bit(r, g, b);
		break;
	case 16:
		dw = Convert16Bit(r, g, b);
		break;
	}

	return dw;
}

void G98CSurface::Copy(G98CRect<int> *srG98CRect, G98CSurface *srcSurf, G98CRect<int> *dstRect) {
	if (!m_surfaceInited) return;

	DWORD flag;
	RECT src, dst;
	HRESULT hRes;

	if (srG98CRect) {
		src = RECT(*srG98CRect);
		if (m_squashToEdge) {
			if (src.top < 0) src.top = 0;
			if (src.left < 0) src.left = 0;
			if (src.right > srcSurf->Width()) src.right = srcSurf->Width();
			if (src.bottom > srcSurf->Height()) src.bottom = srcSurf->Height();
		}
	}
	if (dstRect) {
		dst = RECT(*dstRect);
		if (m_squashToEdge) {
			if (dst.top < 0) dst.top = 0;
			if (dst.left < 0) dst.left= 0;
			if (dst.right > Width()) dst.right = Width();
			if (dst.bottom > Height()) dst.bottom = Height();
		}
	}

	flag = DDBLT_WAIT;
	if (srcSurf->m_colourKeyed) flag |= DDBLT_KEYSRC;

#ifdef _BLITBOX_DEBUG
	if (srG98CRect) {
		Warn(true, Format("Src (%i, %i) -> (%i, %i)",
			srG98CRect->Top(), srG98CRect->Left(), srG98CRect->Width(), srG98CRect->Height()));
	}
	if (dstRect) {
		Warn(true, Format("Dst (%i, %i) -> (%i, %i)",
			dstRect->Top(), dstRect->Left(), dstRect->Width(), dstRect->Height()));
	}
#endif//_BLITBOX_DEBUG

	while (DDERR_SURFACEBUSY == (hRes = m_surf->Blt(dstRect ? &dst : 0, 
		srcSurf->m_surf, srG98CRect ? &src : 0, flag, 0)));

	if (DD_OK != hRes) DDhRes(hRes);
}

void G98CSurface::Copy(int x, int y, G98CSurface *src) {

	G98CRect<int> dst(x, y, src->m_desc.dwWidth, src->m_desc.dwHeight);
	Copy(0, src, &dst);
}

void G98CSurface::Clear(unsigned char r, unsigned char g, unsigned char b) {
	if (!m_surfaceInited) return;

	DWORD fillColour = MakeColourFromSurface(r, g, b);
	DDBLTFX ddblt;

#ifdef _DEBUG
	HRESULT hRes;
#endif

	if (m_surf)
	{
		memset(&ddblt, 0, sizeof(ddblt));
		ddblt.dwSize = sizeof(ddblt);
		ddblt.dwFillColor = fillColour; 

#ifdef _DEBUG
		hRes = 
#endif
		m_surf->Blt(NULL, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddblt);
	}
}

bool G98CSurface::Resize(int width, int height) {

	if (!m_surfaceInited) return false;

	LPDIRECTDRAWSURFACE4 surf;
	DDSURFACEDESC2 desc;
	memset(&desc, 0, sizeof(DDSURFACEDESC2));
	desc.dwSize = sizeof(DDSURFACEDESC2);

	// Create a surface of the desired format and size
	desc.dwFlags |= 
		(width  == 0 ? 0 : DDSD_WIDTH)  | 
		(height == 0 ? 0 : DDSD_HEIGHT) | 
		 DDSD_CAPS;

	if (width  != 0) desc.dwWidth  = width;
	if (height != 0) desc.dwHeight = height;
	
	if (!width && !height) {
		// We want the whole front buffer if no size specced - this should never be the case (unless the window gets too small.......)
		desc.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	} else {
		desc.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
	}

	if (0 != m_bpp) {
		desc.ddpfPixelFormat.dwRGBBitCount = m_bpp == 15 ? 16 : m_bpp;
	}

	if (DD_OK == ddraw->CreateSurface(&desc, &surf, 0)) {
		DWORD cnt; 

		// Release the old surface
		cnt = Release((void*&)m_surf);

		// Point the data to the new one.
		m_surf = surf;
		m_desc = desc;

		// If there was a clipper on the surface then reattach it.
		if (m_clipper) {
			m_surf->SetClipper(m_clipper);
		}
		if (m_palette) {
			m_surf->SetPalette(m_palette);
		}

		// Set the surface data by locking the surface
		Lock();
		Unlock();

		return true;
	} else {
		// No harm done but should sutdown here.
		return false;
	}
}

void G98CSurface::SetClipRect() {
	if (!m_surfaceInited) return;

	if (m_clipper) {
		void *data = new char [sizeof(RGNDATAHEADER) + sizeof(RECT)];
		RGNDATAHEADER *rh = (RGNDATAHEADER *) data;
		rh->dwSize = sizeof(RGNDATAHEADER);
		rh->iType = RDH_RECTANGLES;
		rh->nCount = 1;
		rh->nRgnSize = 0;
		RECT *r = (RECT *) (((char*)data) + sizeof(RGNDATAHEADER));
		r->top = 0;
		r->left = 0;
		r->bottom = m_desc.dwHeight;
		r->right = m_desc.dwWidth;
		memcpy(&(rh->rcBound), r, sizeof(RECT));
		if (DD_OK != m_clipper->SetClipList((LPRGNDATA) data, 0)) {
			return;
		}
		delete [] data;
	}
}

void G98CSurface::SetClipper(HWND hWnd) {

	if (!m_surfaceInited) return;
	if (DD_OK == DirectDrawCreateClipper(0, &m_clipper, 0)) {
		if (m_clipper) {

			if (hWnd) {
				if (DD_OK != m_clipper->SetHWnd(0, hWnd)) {
					return;
				}
			}
			if (DD_OK != m_surf->SetClipper(m_clipper)) {
				return;
			}

		}
	} else return;
}

bool G98CSurface::Lock() {
	if (!m_surfaceLocked) {
		memset(&m_desc, 0, sizeof(DDSURFACEDESC2));
		m_desc.dwSize = sizeof(DDSURFACEDESC2);
		if (DD_OK == m_surf->Lock(0, &m_desc, DDLOCK_WAIT|DDLOCK_NOSYSLOCK, 0)) {
			m_surfaceLocked = true;
			return true;
		} else return false;
	} 
	return false;
}

bool G98CSurface::Unlock() {
	if (m_surfaceLocked) {
		if (DD_OK == m_surf->Unlock(0)) {
			m_surfaceLocked = false;
			return true;
		} return false;
	} 
	return false;
}

bool G98CSurface::SetPaletteColour(int which, unsigned char r, unsigned char g, unsigned char b, int count) {
	PALETTEENTRY entry;

	if (m_surf && m_palette && count) {
		entry.peRed   = r;
		entry.peGreen = g;
		entry.peBlue  = b;
		entry.peFlags = 0;
		if (DD_OK != m_palette->SetEntries(0, which, count, &entry)) return false;
		else return true;
	}

	return false;
}

unsigned char G98CSurface::GetPaletteRed(int i) {
	if (8 == m_desc.ddpfPixelFormat.dwRGBBitCount) {
		if (m_palette) {
			PALETTEENTRY pe;
			if (DD_OK == m_palette->GetEntries(0, i, 1, &pe)) {
				return pe.peRed;
			}
		}
	}
	return 0;
}

unsigned char G98CSurface::GetPaletteGreen(int i) {
	if (8 == m_desc.ddpfPixelFormat.dwRGBBitCount) {
		if (m_palette) {
			PALETTEENTRY pe;
			if (DD_OK == m_palette->GetEntries(0, i, 1, &pe)) {
				return pe.peGreen;
			}
		}
	}
	return 0;
}

unsigned char G98CSurface::GetPaletteBlue(int i) {
	if (8 == m_desc.ddpfPixelFormat.dwRGBBitCount) {
		if (m_palette) {
			PALETTEENTRY pe;
			if (DD_OK == m_palette->GetEntries(0, i, 1, &pe)) {
				return pe.peBlue;
			}
		}
	}
	return 0;
}

void G98CSurface::SetColourKey(unsigned char r, unsigned char g, unsigned char b) {
	if (!m_surfaceInited) return;
	
	DDCOLORKEY key;
	PALETTEENTRY pe;

	if (m_surf) {
		if (8 == Bpp()) {
			// Uses red component as the colour key
			if (m_palette) { 
				m_palette->GetEntries(0, r, 1, &pe);			// This has no right what-so-ever to fail.
			} else memset(&pe, 0, sizeof(PALETTEENTRY));	// Default to 0 as transparent

			r = pe.peRed; 
			g = pe.peGreen; 
			b = pe.peBlue;
		}
		key.dwColorSpaceLowValue = MakeColourFromSurface(r, g, b);
		key.dwColorSpaceHighValue = MakeColourFromSurface(r, g, b);
		if (DD_OK == m_surf->SetColorKey(DDCKEY_SRCBLT, &key)) {
			m_colourKeyed = true;
		}
	}
}

void G98CSurface::WritePixel(int x, int y, unsigned int colour) {
	if (!m_surfaceInited) return;

	G98CSurfaceLock lock(this);		// Bear in mind this is only taken if it has not been locked already
	int pitch = Pitch();

	// Check that the pixel is okay to draw.
	if (y >= Height() || x >= Width() || y < 0 || x < 0) return;

	switch (Bpp()) {
	case 8:
		{
			unsigned char *data = (unsigned char *) lock.Data();
			data[(pitch * y) + x] = (unsigned char)colour;
		}
		break;
	case 15:
	case 16:
		{
			unsigned short *data = (unsigned short *) lock.Data();
			data[((pitch / 2) * y) + x] = (unsigned short)colour;
		}
		break;
	case 24:
		{
			unsigned char *data = (unsigned char *) lock.Data();
			data[(pitch * y) + (x * 3) + 0] = ((unsigned char *)&colour)[0];
			data[(pitch * y) + (x * 3) + 1] = ((unsigned char *)&colour)[1];
			data[(pitch * y) + (x * 3) + 2] = ((unsigned char *)&colour)[2];
		}
		break;
	case 32:
		{
			unsigned int *data = (unsigned int *) lock.Data();
			data[((pitch / 4) * y) + x] = (unsigned int)colour;
		}
		break;
	}
}

unsigned int G98CSurface::GetPixel(int x, int y) {
	if (!m_surfaceInited) return 0;

	G98CSurfaceLock lock(this);		// Bear in mind this is only taken if it has not been locked already
	int pitch = Pitch();

	// Check that the pixel is okay to draw.
	if (y >= Height() || x >= Width() || y < 0 || x < 0) return 0;

	switch (Bpp()) {
	case 8:
		{
			unsigned char *data = (unsigned char *) lock.Data();
			unsigned char ret = data[(pitch * y) + x];
			return (unsigned int) ret;
		}
		break;
	case 15:
	case 16:
		{
			unsigned short *data = (unsigned short *) lock.Data();
			unsigned short ret = data[((pitch / 2) * y) + x];
			return (unsigned int) ret;
		}
		break;
	case 24:
		{
			unsigned int ret = 0;
			unsigned char *ptr = (unsigned char *) &ret;
			unsigned char *data = (unsigned char *) lock.Data();
			ptr[0] = data[(pitch * y) + (x * 3) + 0];
			ptr[1] = data[(pitch * y) + (x * 3) + 1];
			ptr[2] = data[(pitch * y) + (x * 3) + 2];
			return ret;
		}
		break;
	case 32:
		{
			unsigned int *data = (unsigned int *) lock.Data();
			return data[((pitch / 4) * y) + x];
		}
		break;
	}
	return 0;
}

void G98CSurface::Box(int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b, bool filled) {
	if (!m_surfaceInited) return;

	x1 = BoundX(x1);
	x2 = BoundX(x2);
	y1 = BoundY(y1);
	y2 = BoundY(y2);

	if (!filled) {
		Line(x1, y1, x1, y2, r, g, b);
		Line(x2, y1, x2, y2, r, g, b);
		Line(x1, y1, x2, y1, r, g, b);
		Line(x1, y2, x2, y2, r, g, b);
	} else {
		if (y1 > y2) {
			int xt, yt;
			xt = x1; yt = y1;
			x1 = x2; x1 = y2;
			x2 = xt; y2 = yt;
		}
		for (int i=y1; i<y2; i++) {
			Line(x1, i, x2, i, r, g, b);
		}
	}

}

void G98CSurface::Line(int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b) {
	if (!m_surfaceInited) return;

	G98CSurfaceLock lock(this);
	unsigned int colour;

	// Get the colour
	colour = MakeColourFromSurface(r, g, b);

	int deltax,deltay,numpixels;
	int d,dinc1,dinc2;
	int x,xinc1,xinc2;
	int y,yinc1,yinc2;
	int loop;
	
	deltax = abs(x2-x1);
	deltay = abs(y2-y1);
	
	if (deltax >= deltay) {

		numpixels = deltax+1;
		d = 2 * deltay - deltax;
		dinc1 = deltay << 1;
		dinc2 = (deltay - deltax) << 1;
		xinc1 = 1;
		xinc2 = 1;
		yinc1 = 0;
		yinc2 = 1;

	} else {

		numpixels = deltay + 1;
		d = (2 * deltax) - deltay;
		dinc1 = deltax << 1;
		dinc2 = (deltax - deltay) << 1;
		xinc1 = 0;
		xinc2 = 1;
		yinc1 = 1;
		yinc2 = 1;

	}

	if (x1 > x2) {
		xinc1 =- xinc1;
		xinc2 =- xinc2;
	}

	if (y1 > y2) {
		yinc1 =- yinc1;
		yinc2 =- yinc2;
	}

	x = x1;
	y = y1;
	
	for (loop = 1; loop <= numpixels; loop++) {

		WritePixel(x, y, colour);
		
		if (d < 0) {
			d = d + dinc1;
			x = x + xinc1;
			y = y + yinc1;
		} else {
			d = d + dinc2;
			x = x + xinc2;
			y = y + yinc2;
		}

	}
}

long G98CSurface::CountMaskBits(unsigned long mask) {

	unsigned long i, count=0;

	for (i=0; i<(sizeof(mask) * 8); i++) {
		if (0 != (mask & (1<<i))) count++;
	}

	return count;
}

unsigned long G98CSurface::CountMaskBitShift(unsigned long mask) {
	unsigned long i;
	for (i=0; i<(sizeof(mask) * 8); i++) {
		if (0 != (mask & (1<<i))) return i;
	}
	return 0xffffffff;
}

int G98CSurface::GetDesktopBitDepth()
{
	HDC hdc;
	int bpp;

	hdc = ::GetDC(NULL);
	bpp = GetDeviceCaps(hdc, BITSPIXEL);
	::ReleaseDC(NULL, hdc);

	return bpp;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Animation.cpp: implementation of the G98CAnimation class.
//
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

G98CAnimation::G98CAnimation(char *fName/*, G98CSurface *backBuffer*/) : 
	m_colourKeySet(false), m_init(false)/*, m_dest(0)*/, m_movieSurf(0) {
	
	char *name = File_VerifyFilename(fName);
	m_decompressFn = 0;
	m_aviStream = 0;
	memset(&m_aviStreamInfo, 0, sizeof(m_aviStreamInfo));

	m_movieRect.top    = 0;
	m_movieRect.bottom = 0;
	m_movieRect.left   = 0;
	m_movieRect.right  = 0;

	if (!g98NoAvis) {
		if (S_OK == AVIStreamOpenFromFile(&m_aviStream, name, streamtypeVIDEO, 0, OF_READ, NULL)) {
			// Load the video stream
			if (m_decompressFn = AVIStreamGetFrameOpen(m_aviStream, 
				(LPBITMAPINFOHEADER) AVIGETFRAMEF_BESTDISPLAYFMT)) {
				if (S_OK == AVIStreamInfo(m_aviStream, &m_aviStreamInfo, sizeof(AVISTREAMINFO))) {
					// Get info - length, rectangle etc
					m_startTime = ((float)timeGetTime()) / 1000.0f;
					m_init = true;
					m_currFrame = 0;
//					m_dest = backBuffer;
					m_movieRect.top    = m_aviStreamInfo.rcFrame.top;
					m_movieRect.bottom = m_aviStreamInfo.rcFrame.bottom;
					m_movieRect.left   = m_aviStreamInfo.rcFrame.left;
					m_movieRect.right  = m_aviStreamInfo.rcFrame.right;
					m_movieSurf = new G98CSurface(m_movieRect.right - m_movieRect.left, m_movieRect.bottom - m_movieRect.top, 0);
				}
			}
		}
	}

}

G98CAnimation::~G98CAnimation() {

	if (!g98NoAvis) {
		if (m_aviStream) AVIStreamRelease(m_aviStream);
		if (m_movieSurf) delete m_movieSurf;
	}

}

void G98CAnimation::BMICopy(LPBITMAPINFO bmi) {

	G98CSurfaceLock lock(m_movieSurf);
	unsigned short *pSrc  = (unsigned short *) (((unsigned char *) bmi) + bmi->bmiHeader.biSize);
	unsigned short *pDest = (unsigned short *) lock.Data();
	int width, height;

	// Width and height of the bitmap (and indeed the destination surface)
	width  = m_movieRect.right  - m_movieRect.left;
	height = m_movieRect.bottom - m_movieRect.top;

	// Caluclate the dest surface skip
//	int skipSrc  = ((m_movieSurf->Pitch() + 3) & ~3) / 2;
	int skipSrc  = m_movieSurf->Pitch() / 2;
	int skipDest = m_movieSurf->Pitch() / 2;

	// Animations are ONLY gonna be done in 16/15 bit - note m_movieSurf is created in the primary display format (since no BPP was given).
	if(m_movieSurf->Bpp() == 15) {

		// Set the source to the last line
		pSrc += (height-1) * skipSrc;

		for (int i=0; i<height; i++) {
			memcpy(pDest, pSrc, sizeof(unsigned short) * width);		// NEED LINE CONVERSION HERE I FEAR (BUT AM NOT SURE!)
			pSrc  -= skipSrc;
			pDest += skipDest;
		}

	} else if (m_movieSurf->Bpp() == 16) {

		// Set the source to the last line
		pSrc += (height-1) * skipSrc;

		for (int i=0; i<height; i++) {
			memcpy(pDest, pSrc, sizeof(unsigned short) * width);
			pSrc  -= skipSrc;
			pDest += skipDest;
		}

	}

}

bool G98CAnimation::Update(/*RECT &destRect*/ void) {

	HRESULT r = S_OK;

	if (!m_init) return false;

	if (g98NoAvis) return false;

	/// Get the pointer to the bitmap info
    BITMAPINFO* pbmi;
    if (pbmi = (LPBITMAPINFO)AVIStreamGetFrame(m_decompressFn, m_currFrame)) {

		// Copy the frame to the surface
		BMICopy(pbmi);
//		G98CRect<int> r(destRect.left, destRect.top, destRect.right - destRect.left, destRect.bottom - destRect.top);
//		m_dest->Copy(0, m_movieSurf, &r);

		// Update to the next frame - do it here so that we can check the frame number to see if we have overrun
		m_currTime		   = ((float)timeGetTime()) / 1000.0f;
		float fElapsedTime = m_currTime - m_startTime;
		m_aviTimeScale	   = ((float)m_aviStreamInfo.dwRate) / m_aviStreamInfo.dwScale;
		m_currFrame		   = (unsigned int) (fElapsedTime * m_aviTimeScale);

	}

	return r == S_OK ? true : false;

}

void G98CAnimation::SetColourKey(void) {

	if (g98NoAvis) return;

	m_movieSurf->SetColourKey(0, 0, 0);
	m_colourKeySet = true;

}

unsigned int G98CAnimation::Length() {

	int len = 0;
	if (g98NoAvis) return 0;
	return (unsigned int) m_aviStreamInfo.dwLength;

}

void G98CAnimation::SetTime(unsigned int time) {

	if (g98NoAvis) return;

	// Adjust the curr frame and start time so that the following frames time correctly.
	m_currFrame = time;
	m_currTime = (float)timeGetTime() / 1000.0f;
	m_startTime = m_currTime - ((float) m_currFrame / m_aviTimeScale);

}

unsigned int G98CAnimation::GetTime() {

	int time = m_currFrame;
	if (g98NoAvis) return 0;
	return time;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma comment ( lib , "vfw32" )

extern "C" LPDIRECTDRAWSURFACE4 DirectDraw_bSurf(VOID);

void Animation_Initialise(LPDIRECTDRAW4 directDraw) {

	ddraw = directDraw;
	AVIFileInit();
}

void Animation_ShutDown(VOID) {

	AVIFileExit();
}

lpAnimation Animation_Load(char *fName) {

	G98CAnimation *animation = new G98CAnimation(fName);

	return animation;
}

int Animation_Update(lpAnimation anim) {

	G98CAnimation *animation = (G98CAnimation *) anim;

	return animation->Update();
}

void Animation_BlitToBackBuffer(lpAnimation anim, RECT *destRect) {

	G98CAnimation *animation = (G98CAnimation *) anim;

	if (animation->IsOk()) {
		DirectDraw_bSurf()->Blt(destRect, animation->GetSurface(), NULL, DDBLT_WAIT, NULL);
	}
}

void Animation_SetTime(lpAnimation anim, unsigned int time) {

	G98CAnimation *animation = (G98CAnimation *) anim;
	
	animation->SetTime(time);
}

unsigned int Animation_GetTime(lpAnimation anim) {

	G98CAnimation *animation = (G98CAnimation *) anim;
	
	return animation->GetTime();
}

unsigned int Animation_GetLength(lpAnimation anim) {

	G98CAnimation *animation = (G98CAnimation *) anim;
	
	return animation->Length();
}

void Animation_Free(lpAnimation anim) {

	G98CAnimation *animation = (G98CAnimation *) anim;

	delete animation;
}

int Animation_IsOk(lpAnimation anim) {

	G98CAnimation *animation = (G98CAnimation *) anim;

	return animation->IsOk();
}
