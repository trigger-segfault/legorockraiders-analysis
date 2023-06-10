
#include "Standard.h"
#include "DirectX.h"
#include "Files.h"
#include "DXT.h"

#include <dxtguid.c>

struct DXTGlobs {

	IDXSurfaceFactory *surfaceFactory;

	ULONG flags;

} dxtGlobs = { 0 };

VOID DXT_Initialise(VOID) {

	HRESULT hr;

	if (SUCCEEDED(hr = CoCreateInstance(&CLSID_DXTransformFactory, NULL, CLSCTX_INPROC, &IID_IDXSurfaceFactory, (LPVOID *) &dxtGlobs.surfaceFactory))) {

		dxtGlobs.flags |= DXTFLAG_INITIALISED;
	}
}

LPDIRECTDRAWSURFACE7 DXT_LoadImage(LPUCHAR fname) {

	LPDIRECTDRAWSURFACE7 surface;
	IDXSurface *dxSurface;
	UWORD path[FILE_MAXPATH];

	mbstowcs(path, File_GetActualPath(fname, FALSE), FILE_MAXPATH);

	if (SUCCEEDED(dxtGlobs.surfaceFactory->lpVtbl->LoadImage(dxtGlobs.surfaceFactory, path, (IUnknown *)DirectX_DirectDraw(), NULL, NULL, &IID_IDXSurface, &dxSurface))) {
		if (SUCCEEDED(dxSurface->lpVtbl->GetDirectDrawSurface(dxSurface, &IID_IDirectDrawSurface7, &surface))) {

			return surface;

		} else {
			dxSurface->lpVtbl->Release(dxSurface);
			dxSurface = NULL;
		}
	}

	return NULL;
}