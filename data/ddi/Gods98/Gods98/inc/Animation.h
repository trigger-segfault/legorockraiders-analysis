////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Rect.h: interface for the G98CRect class.
//
//////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

#if !defined(_RECT_H_)
#define _RECT_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

//#undef Warn
#define Warn(b, str)

template <class T>
class G98CRect
{
private:
	T m_top, m_left, m_width, m_height;

public:

	G98CRect(T left, T top, T width, T height) {
		m_top = top;     m_left = left;
		m_width = width; m_height = height;
	}
	G98CRect() { }

	virtual ~G98CRect() { }

	T& Top()    { return m_top;    }
	T& Left()   { return m_left;   }
	T& Width()  { return m_width;  }
	T& Height() { return m_height; }

	operator RECT() {
		RECT r;
		r.top  = (long) m_top;
		r.left = (long) m_left;
		r.bottom = (long) (m_top + m_height);
		r.right  = (long) (m_left + m_width);
		return r;
	}

};

template class G98CRect<int>;
template class G98CRect<float>;

#endif // !defined(_RECT_H_)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Surface.h: interface for the G98CSurface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_SURFACE_H)
#define _SURFACE_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

enum {
	G98Colour_Trans,				// The standard palettised colours.
	G98Colour_Black,
	G98Colour_White,
	G98Colour_Red,
	G98Colour_Green,
	G98Colour_Blue,
	G98Colour_Yellow,
	G98Colour_Purple,
	G98Colour_Cyan,
};

extern LPDIRECTDRAW4 ddraw;

class G98CSurfaceLock;

class G98CSurface
{
protected:

private:
	void PreInit(bool fullScreen = false);
	LPDIRECTDRAWCLIPPER m_clipper;	// Clipper
	bool m_surfaceLocked;			// Is the surface currently locked
	int m_bpp;						// Bits per pixel of the surface.
	LPDIRECTDRAWPALETTE m_palette;	// The Direct Draw palette
	bool m_colourKeyed;				// Set to true if the surface has a transparent colour key.
	bool m_squashToEdge;			// Squah the image up at the edge of the screen
	bool m_15bit;					// The 16 bit mode is really fifteen bit
	bool m_surfaceInited;			// Is the surface initialised

	//////////////////////////////////////////////////////////////////////////
	// Use the G98CSurfaceLock class to lock the surface.  Allows its destructor
	// to clean up when stack unwinding occurs
	//////////////////////////////////////////////////////////////////////////
	friend class G98CSurfaceLock;
	bool Lock();
	bool Unlock();
	void *Data() { return m_desc.lpSurface; }			// Only sutiable when lock taken thus access through G98CSurfaceLock

protected:

	LPDIRECTDRAWSURFACE4 m_surf;		// Direct Draw surface.
	DDSURFACEDESC2 m_desc;			// Description of the surface

	/////////////////////////////////////////////////////////////////////////////
	// Counts the number of bits in a bit mask (for R,G or B)
	/////////////////////////////////////////////////////////////////////////////
	long CountMaskBits(unsigned long mask);

	/////////////////////////////////////////////////////////////////////////////
	// Counts the number of bits needed to shift a mask by
	/////////////////////////////////////////////////////////////////////////////
	unsigned long CountMaskBitShift(unsigned long mask);

	/////////////////////////////////////////////////////////////////////////////
	// What is the bit depth of the desktop
	/////////////////////////////////////////////////////////////////////////////
	int GetDesktopBitDepth();

public:
	G98CSurface(bool fullScreen = false);
	G98CSurface(int width, int height, int bpp, bool vram = false, bool fullScreen = false);
	virtual ~G98CSurface();
	bool Init(int width, int height, int bpp, bool vram);

	LPDIRECTDRAWSURFACE4 GetSurface() { return m_surf; }

	void Clear(unsigned char r, unsigned char g, unsigned char b);
	DWORD MakeColourFromSurface(unsigned char r, unsigned char g, unsigned char b);

	// Blitting functions.
	void Copy(int x, int y, G98CSurface *src);
	void Copy(G98CRect<int> *srG98CRect, G98CSurface *src, G98CRect<int> *dstRect);

	bool Resize(int width, int height);

	void SetClipper(HWND hWnd=0);
	void SetClipRect();

	bool IsLocked() { return m_surfaceLocked; }

	bool SetPaletteColour(int which, unsigned char r, unsigned char g, unsigned char b, int count=1);

	virtual int Width()  { return m_desc.dwWidth;  }
	virtual int Height() { return m_desc.dwHeight; }

	int Pitch()  { return m_desc.lPitch;   }
	int BytesPerPixel() {
		switch (Bpp()) {
		case 8:  return 1;
		case 15:
		case 16: return 2;
		case 24: return 3;
		case 32: return 4;
		default: return 0;
		}
	}

	unsigned short Convert15Bit(unsigned char r, unsigned char g, unsigned char b) {
		return  ((r >> 3) << 10) | ((g >> 3) << 5) | (b >> 3);
	}

	unsigned short Convert16Bit(unsigned char r, unsigned char g, unsigned char b) {
		return  ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
	}

	void SetColourKey(unsigned char r, unsigned char g=0, unsigned char b=0);

	void Line(int sx, int sy, int ex, int ey, unsigned char r, unsigned char g=0, unsigned char b=0);

	inline void WritePixel(int x, int y, unsigned int colour);
	inline unsigned int GetPixel(int x, int y);

	int Bpp()	 { 
		if (m_15bit) return 15;
		else return m_desc.ddpfPixelFormat.dwRGBBitCount; 
	}

	HDC GetDC() {
		HDC hdc;
		if (DD_OK == m_surf->GetDC(&hdc)) {
			return hdc;
		}
		return 0;
	}

	void ReleaseDC(HDC hDC) {
		m_surf->ReleaseDC(hDC);
	}

	int  BoundX(int x) {
		if (x < 0) {
			return 0;
		} else if (x >= Width()) {
			return Width() - 1;
		} else return x;
	}
	int  BoundY(int y) {
		if (y < 0) {
			return 0;
		} else if (y >= Height()) {
			return Width() - 1;
		} else return y;
	}

	void Box(int x1, int y1, int x2, int y2, unsigned char r, unsigned char g, unsigned char b, bool filled=false);

	bool& SquashToEdge() { return m_squashToEdge; }

	void FlipToGDISurface() {
		ddraw->FlipToGDISurface();
	}
	void CheckRestore() {
		if (m_surf) {
			if (m_surf->IsLost() != DD_OK) {
				Warn(true, "Restoring lost surface");
				if (DD_OK == m_surf->Restore()) {
					Warn(true, "Surface restored");
				} else {
					Warn(true, "Restore failed.");
				}
			}
		}
	}
	unsigned char GetPaletteRed(int i);
	unsigned char GetPaletteGreen(int i);
	unsigned char GetPaletteBlue(int i);
};

class G98CSurfaceLock {
private:
	
	bool m_lockHeld;
	G98CSurface *m_surf;

public:
	
	G98CSurfaceLock(G98CSurface *surf) {
		m_surf = surf;
		m_lockHeld = false;
		if (!m_surf->IsLocked())
			if (m_surf->Lock()) m_lockHeld = true;
	}

	~G98CSurfaceLock() {
		if (m_lockHeld) m_surf->Unlock();
	}
	
	void *Data() { 
		return m_surf->Data();
	}

	bool IsLocked() { return m_lockHeld; }
};

#endif //_SURFACE_H




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _ANIMATION_H
#define _ANIMATION_H

class G98CAnimation
{
	PAVISTREAM         m_aviStream;
	PGETFRAME          m_decompressFn;
	AVISTREAMINFO      m_aviStreamInfo;

	bool m_colourKeySet, m_init;
//	G98CSurface *m_dest;
	RECT m_movieRect;

	float m_startTime;
	float m_currTime;
	float m_aviTimeScale;
	unsigned int m_currFrame;
	unsigned int m_length;

	void BMICopy(LPBITMAPINFO bmi);

	G98CSurface *m_movieSurf;

public:

	LPDIRECTDRAWSURFACE4 GetSurface() { return m_movieSurf->GetSurface(); }

	/////////////////////////////////////////////////////////////////////////////
	// Length of the movie
	/////////////////////////////////////////////////////////////////////////////
	unsigned int Length();

	/////////////////////////////////////////////////////////////////////////////
	// Set the time of the stream
	/////////////////////////////////////////////////////////////////////////////
	void SetTime(unsigned int time);

	/////////////////////////////////////////////////////////////////////////////
	// Get the current time of the stream
	/////////////////////////////////////////////////////////////////////////////
	unsigned int GetTime();

	/////////////////////////////////////////////////////////////////////////////
	// Get the size of the animation
	/////////////////////////////////////////////////////////////////////////////
	RECT *GetRect() { return &m_movieRect; }

	/////////////////////////////////////////////////////////////////////////////
	// Construction (name and dest) and destruction
	/////////////////////////////////////////////////////////////////////////////
	G98CAnimation(char *fName/*, G98CSurface *backBuffer*/);
	virtual ~G98CAnimation();

	void SetColourKey(void);
	bool Update(/*RECT &destRect*/ void);

	bool IsOk() { return m_init; }
};

#endif // __cplusplus

#endif _ANIMATION_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef void		*lpAnimation;

#ifdef _GODS98COMPILE
void Animation_Initialise(LPDIRECTDRAW4 directDraw);
#endif // _GODS98COMPILE
lpAnimation __cdecl Animation_Load(char *fName);
int __cdecl Animation_Update(lpAnimation anim);
void __cdecl Animation_BlitToBackBuffer(lpAnimation anim, RECT *dest);
void __cdecl Animation_SetTime(lpAnimation anim, unsigned int time);
unsigned int __cdecl Animation_GetTime(lpAnimation anim);
unsigned int __cdecl Animation_GetLength(lpAnimation anim);
void __cdecl Animation_Free(lpAnimation anim);
int __cdecl Animation_IsOk(lpAnimation anim);

#ifdef __cplusplus
}
#endif // __cplusplus


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

