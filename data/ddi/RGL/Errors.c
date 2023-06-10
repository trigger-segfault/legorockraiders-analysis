
#include <windows.h>
#include <stdarg.h>

#include "Standard.h"
#include "Errors.h"
#include "Main.h"

#ifdef _DEBUG

#include <d3d.h>
#include <ddraw.h>
#include <d3drm.h>
#include <dxfile.h>
#include <dinput.h>

#define ERROR_MAXHRESULTS		4096

struct ErrorHR {

	LPUCHAR name;
	HRESULT code;
	enum ErrorDirectXModule module;
};

typedef struct ErrorHR		ErrorHR, *lpErrorHR;

struct ErrorGlobs {

	FILE *logFile;
	LPUCHAR dxErrorName[ErrorDirectXModule_Count][4096];
	LPUCHAR dxName[ErrorDirectXModule_Count];
	BOOL fullScreen;

	LPUCHAR dxModulePrefix[ErrorDirectXModule_Count];
	struct ErrorHR dxErrorHR[ERROR_MAXHRESULTS];
	ULONG dxErrorHRCount;

	LPUCHAR errorFunction;

} errorGlobs = { 0 };

VOID Error_SetErrorFunction(LPUCHAR name) {

	errorGlobs.errorFunction = name;
}

LPUCHAR Error_GetErrorFunction(VOID) {

	return errorGlobs.errorFunction;
}

VOID Error_RegisterHRFunc(ULONG hr, LPUCHAR name) {

	lpErrorHR ehr = &errorGlobs.dxErrorHR[errorGlobs.dxErrorHRCount++];
	ULONG loop;

	ehr->name = name;
	ehr->code = hr;
	for (loop=0 ; loop<ErrorDirectXModule_Count ; loop++) {
		ehr->module = loop;
		if (0 == strnicmp(errorGlobs.dxModulePrefix[loop], name, strlen(errorGlobs.dxModulePrefix[loop]))) break;
	}
}

VOID Error_RegisterHResults(VOID) {

	errorGlobs.dxModulePrefix[ErrorDirectXModule_DirectDraw] = "DDERR";
	errorGlobs.dxModulePrefix[ErrorDirectXModule_Direct3DRM] = "D3DRMERR";
	errorGlobs.dxModulePrefix[ErrorDirectXModule_Direct3D] = "D3DERR";
	errorGlobs.dxModulePrefix[ErrorDirectXModule_DirectXFile] = "DXFILEERR";
	errorGlobs.dxModulePrefix[ErrorDirectXModule_DirectInput] = "DIERR";

	Error_RegisterHR(D3DERR_BADMAJORVERSION);
	Error_RegisterHR(D3DERR_BADMINORVERSION);
	Error_RegisterHR(D3DERR_INVALID_DEVICE);
	Error_RegisterHR(D3DERR_INITFAILED);
	Error_RegisterHR(D3DERR_DEVICEAGGREGATED);
	Error_RegisterHR(D3DERR_EXECUTE_CREATE_FAILED);
	Error_RegisterHR(D3DERR_EXECUTE_DESTROY_FAILED);
	Error_RegisterHR(D3DERR_EXECUTE_LOCK_FAILED);
	Error_RegisterHR(D3DERR_EXECUTE_UNLOCK_FAILED);
	Error_RegisterHR(D3DERR_EXECUTE_LOCKED);
	Error_RegisterHR(D3DERR_EXECUTE_NOT_LOCKED);
	Error_RegisterHR(D3DERR_EXECUTE_FAILED);
	Error_RegisterHR(D3DERR_EXECUTE_CLIPPED_FAILED);
	Error_RegisterHR(D3DERR_TEXTURE_NO_SUPPORT);
	Error_RegisterHR(D3DERR_TEXTURE_CREATE_FAILED);
	Error_RegisterHR(D3DERR_TEXTURE_DESTROY_FAILED);
	Error_RegisterHR(D3DERR_TEXTURE_LOCK_FAILED);
	Error_RegisterHR(D3DERR_TEXTURE_UNLOCK_FAILED);
	Error_RegisterHR(D3DERR_TEXTURE_LOAD_FAILED);
	Error_RegisterHR(D3DERR_TEXTURE_SWAP_FAILED);
	Error_RegisterHR(D3DERR_TEXTURE_LOCKED);
	Error_RegisterHR(D3DERR_TEXTURE_NOT_LOCKED);
	Error_RegisterHR(D3DERR_TEXTURE_GETSURF_FAILED);
	Error_RegisterHR(D3DERR_MATRIX_CREATE_FAILED);
	Error_RegisterHR(D3DERR_MATRIX_DESTROY_FAILED);
	Error_RegisterHR(D3DERR_MATRIX_SETDATA_FAILED);
	Error_RegisterHR(D3DERR_MATRIX_GETDATA_FAILED);
	Error_RegisterHR(D3DERR_SETVIEWPORTDATA_FAILED);
	Error_RegisterHR(D3DERR_INVALIDCURRENTVIEWPORT);
	Error_RegisterHR(D3DERR_INVALIDPRIMITIVETYPE);
	Error_RegisterHR(D3DERR_INVALIDVERTEXTYPE);
	Error_RegisterHR(D3DERR_TEXTURE_BADSIZE);
	Error_RegisterHR(D3DERR_INVALIDRAMPTEXTURE);
	Error_RegisterHR(D3DERR_MATERIAL_CREATE_FAILED);
	Error_RegisterHR(D3DERR_MATERIAL_DESTROY_FAILED);
	Error_RegisterHR(D3DERR_MATERIAL_SETDATA_FAILED);
	Error_RegisterHR(D3DERR_MATERIAL_GETDATA_FAILED);
	Error_RegisterHR(D3DERR_INVALIDPALETTE);
	Error_RegisterHR(D3DERR_ZBUFF_NEEDS_SYSTEMMEMORY);
	Error_RegisterHR(D3DERR_ZBUFF_NEEDS_VIDEOMEMORY);
	Error_RegisterHR(D3DERR_SURFACENOTINVIDMEM);
	Error_RegisterHR(D3DERR_LIGHT_SET_FAILED);
	Error_RegisterHR(D3DERR_LIGHTHASVIEWPORT);
	Error_RegisterHR(D3DERR_LIGHTNOTINTHISVIEWPORT);
	Error_RegisterHR(D3DERR_SCENE_IN_SCENE);
	Error_RegisterHR(D3DERR_SCENE_NOT_IN_SCENE);
	Error_RegisterHR(D3DERR_SCENE_BEGIN_FAILED);
	Error_RegisterHR(D3DERR_SCENE_END_FAILED);
	Error_RegisterHR(D3DERR_INBEGIN);
	Error_RegisterHR(D3DERR_NOTINBEGIN);
	Error_RegisterHR(D3DERR_NOVIEWPORTS);
	Error_RegisterHR(D3DERR_VIEWPORTDATANOTSET);
	Error_RegisterHR(D3DERR_VIEWPORTHASNODEVICE);
	Error_RegisterHR(D3DERR_NOCURRENTVIEWPORT);
	Error_RegisterHR(D3DERR_INVALIDVERTEXFORMAT);
	Error_RegisterHR(D3DERR_COLORKEYATTACHED);
	Error_RegisterHR(D3DERR_VERTEXBUFFEROPTIMIZED);
	Error_RegisterHR(D3DERR_VBUF_CREATE_FAILED);
	Error_RegisterHR(D3DERR_VERTEXBUFFERLOCKED);
	Error_RegisterHR(D3DERR_VERTEXBUFFERUNLOCKFAILED);
	Error_RegisterHR(D3DERR_ZBUFFER_NOTPRESENT);
	Error_RegisterHR(D3DERR_STENCILBUFFER_NOTPRESENT);
	Error_RegisterHR(D3DERR_WRONGTEXTUREFORMAT);
	Error_RegisterHR(D3DERR_UNSUPPORTEDCOLOROPERATION);
	Error_RegisterHR(D3DERR_UNSUPPORTEDCOLORARG);
	Error_RegisterHR(D3DERR_UNSUPPORTEDALPHAOPERATION);
	Error_RegisterHR(D3DERR_UNSUPPORTEDALPHAARG);
	Error_RegisterHR(D3DERR_TOOMANYOPERATIONS);
	Error_RegisterHR(D3DERR_CONFLICTINGTEXTUREFILTER);
	Error_RegisterHR(D3DERR_UNSUPPORTEDFACTORVALUE);
	Error_RegisterHR(D3DERR_CONFLICTINGRENDERSTATE);
	Error_RegisterHR(D3DERR_UNSUPPORTEDTEXTUREFILTER);
	Error_RegisterHR(D3DERR_TOOMANYPRIMITIVES);
	Error_RegisterHR(D3DERR_INVALIDMATRIX);
	Error_RegisterHR(D3DERR_TOOMANYVERTICES);
	Error_RegisterHR(D3DERR_CONFLICTINGTEXTUREPALETTE);
	Error_RegisterHR(D3DERR_INVALIDSTATEBLOCK);
	Error_RegisterHR(D3DERR_INBEGINSTATEBLOCK);
	Error_RegisterHR(D3DERR_NOTINBEGINSTATEBLOCK);

	Error_RegisterHR(D3DRMERR_BADOBJECT);
	Error_RegisterHR(D3DRMERR_BADTYPE);
	Error_RegisterHR(D3DRMERR_BADALLOC);
	Error_RegisterHR(D3DRMERR_FACEUSED);
	Error_RegisterHR(D3DRMERR_NOTFOUND);
	Error_RegisterHR(D3DRMERR_NOTDONEYET);
	Error_RegisterHR(D3DRMERR_FILENOTFOUND);
	Error_RegisterHR(D3DRMERR_BADFILE);
	Error_RegisterHR(D3DRMERR_BADDEVICE);
	Error_RegisterHR(D3DRMERR_BADVALUE);
	Error_RegisterHR(D3DRMERR_BADMAJORVERSION);
	Error_RegisterHR(D3DRMERR_BADMINORVERSION);
	Error_RegisterHR(D3DRMERR_UNABLETOEXECUTE);
	Error_RegisterHR(D3DRMERR_LIBRARYNOTFOUND);
	Error_RegisterHR(D3DRMERR_INVALIDLIBRARY);
	Error_RegisterHR(D3DRMERR_PENDING);
	Error_RegisterHR(D3DRMERR_NOTENOUGHDATA);
	Error_RegisterHR(D3DRMERR_REQUESTTOOLARGE);
	Error_RegisterHR(D3DRMERR_REQUESTTOOSMALL);
	Error_RegisterHR(D3DRMERR_CONNECTIONLOST);
	Error_RegisterHR(D3DRMERR_LOADABORTED);
	Error_RegisterHR(D3DRMERR_NOINTERNET);
	Error_RegisterHR(D3DRMERR_BADCACHEFILE);
	Error_RegisterHR(D3DRMERR_BOXNOTSET);
	Error_RegisterHR(D3DRMERR_BADPMDATA);
	Error_RegisterHR(D3DRMERR_CLIENTNOTREGISTERED);
	Error_RegisterHR(D3DRMERR_NOTCREATEDFROMDDS);
	Error_RegisterHR(D3DRMERR_NOSUCHKEY);
	Error_RegisterHR(D3DRMERR_INCOMPATABLEKEY);
	Error_RegisterHR(D3DRMERR_ELEMENTINUSE);
	Error_RegisterHR(D3DRMERR_TEXTUREFORMATNOTFOUND);
	Error_RegisterHR(D3DRMERR_NOTAGGREGATED);

	Error_RegisterHR(DDERR_ALREADYINITIALIZED);
	Error_RegisterHR(DDERR_CANNOTATTACHSURFACE);
	Error_RegisterHR(DDERR_CANNOTDETACHSURFACE);
	Error_RegisterHR(DDERR_CURRENTLYNOTAVAIL);
	Error_RegisterHR(DDERR_EXCEPTION);
	Error_RegisterHR(DDERR_HEIGHTALIGN);
	Error_RegisterHR(DDERR_INCOMPATIBLEPRIMARY);
	Error_RegisterHR(DDERR_INVALIDCAPS);
	Error_RegisterHR(DDERR_INVALIDCLIPLIST);
	Error_RegisterHR(DDERR_INVALIDMODE);
	Error_RegisterHR(DDERR_INVALIDOBJECT);
	Error_RegisterHR(DDERR_INVALIDPIXELFORMAT);
	Error_RegisterHR(DDERR_INVALIDRECT);
	Error_RegisterHR(DDERR_LOCKEDSURFACES);
	Error_RegisterHR(DDERR_NO3D);
	Error_RegisterHR(DDERR_NOALPHAHW);
	Error_RegisterHR(DDERR_NOSTEREOHARDWARE);
	Error_RegisterHR(DDERR_NOSURFACELEFT);
	Error_RegisterHR(DDERR_NOCLIPLIST);
	Error_RegisterHR(DDERR_NOCOLORCONVHW);
	Error_RegisterHR(DDERR_NOCOOPERATIVELEVELSET);
	Error_RegisterHR(DDERR_NOCOLORKEY);
	Error_RegisterHR(DDERR_NOCOLORKEYHW);
	Error_RegisterHR(DDERR_NODIRECTDRAWSUPPORT);
	Error_RegisterHR(DDERR_NOEXCLUSIVEMODE);
	Error_RegisterHR(DDERR_NOFLIPHW);
	Error_RegisterHR(DDERR_NOGDI);
	Error_RegisterHR(DDERR_NOMIRRORHW);
	Error_RegisterHR(DDERR_NOTFOUND);
	Error_RegisterHR(DDERR_NOOVERLAYHW);
	Error_RegisterHR(DDERR_OVERLAPPINGRECTS);
	Error_RegisterHR(DDERR_NORASTEROPHW);
	Error_RegisterHR(DDERR_NOROTATIONHW);
	Error_RegisterHR(DDERR_NOSTRETCHHW);
	Error_RegisterHR(DDERR_NOT4BITCOLOR);
	Error_RegisterHR(DDERR_NOT4BITCOLORINDEX);
	Error_RegisterHR(DDERR_NOT8BITCOLOR);
	Error_RegisterHR(DDERR_NOTEXTUREHW);
	Error_RegisterHR(DDERR_NOVSYNCHW);
	Error_RegisterHR(DDERR_NOZBUFFERHW);
	Error_RegisterHR(DDERR_NOZOVERLAYHW);
	Error_RegisterHR(DDERR_OUTOFCAPS);
	Error_RegisterHR(DDERR_OUTOFVIDEOMEMORY);
	Error_RegisterHR(DDERR_OVERLAYCANTCLIP);
	Error_RegisterHR(DDERR_OVERLAYCOLORKEYONLYONEACTIVE);
	Error_RegisterHR(DDERR_PALETTEBUSY);
	Error_RegisterHR(DDERR_COLORKEYNOTSET);
	Error_RegisterHR(DDERR_SURFACEALREADYATTACHED);
	Error_RegisterHR(DDERR_SURFACEALREADYDEPENDENT);
	Error_RegisterHR(DDERR_SURFACEBUSY);
	Error_RegisterHR(DDERR_CANTLOCKSURFACE);
	Error_RegisterHR(DDERR_SURFACEISOBSCURED);
	Error_RegisterHR(DDERR_SURFACELOST);
	Error_RegisterHR(DDERR_SURFACENOTATTACHED);
	Error_RegisterHR(DDERR_TOOBIGHEIGHT);
	Error_RegisterHR(DDERR_TOOBIGSIZE);
	Error_RegisterHR(DDERR_TOOBIGWIDTH);
	Error_RegisterHR(DDERR_UNSUPPORTEDFORMAT);
	Error_RegisterHR(DDERR_UNSUPPORTEDMASK);
	Error_RegisterHR(DDERR_INVALIDSTREAM);
	Error_RegisterHR(DDERR_VERTICALBLANKINPROGRESS);
	Error_RegisterHR(DDERR_WASSTILLDRAWING);
	Error_RegisterHR(DDERR_DDSCAPSCOMPLEXREQUIRED);
	Error_RegisterHR(DDERR_XALIGN);
	Error_RegisterHR(DDERR_INVALIDDIRECTDRAWGUID);
	Error_RegisterHR(DDERR_DIRECTDRAWALREADYCREATED);
	Error_RegisterHR(DDERR_NODIRECTDRAWHW);
	Error_RegisterHR(DDERR_PRIMARYSURFACEALREADYEXISTS);
	Error_RegisterHR(DDERR_NOEMULATION);
	Error_RegisterHR(DDERR_REGIONTOOSMALL);
	Error_RegisterHR(DDERR_CLIPPERISUSINGHWND);
	Error_RegisterHR(DDERR_NOCLIPPERATTACHED);
	Error_RegisterHR(DDERR_NOHWND);
	Error_RegisterHR(DDERR_HWNDSUBCLASSED);
	Error_RegisterHR(DDERR_HWNDALREADYSET);
	Error_RegisterHR(DDERR_NOPALETTEATTACHED);
	Error_RegisterHR(DDERR_NOPALETTEHW);
	Error_RegisterHR(DDERR_BLTFASTCANTCLIP);
	Error_RegisterHR(DDERR_NOBLTHW);
	Error_RegisterHR(DDERR_NODDROPSHW);
	Error_RegisterHR(DDERR_OVERLAYNOTVISIBLE);
	Error_RegisterHR(DDERR_NOOVERLAYDEST);
	Error_RegisterHR(DDERR_INVALIDPOSITION);
	Error_RegisterHR(DDERR_NOTAOVERLAYSURFACE);
	Error_RegisterHR(DDERR_EXCLUSIVEMODEALREADYSET);
	Error_RegisterHR(DDERR_NOTFLIPPABLE);
	Error_RegisterHR(DDERR_CANTDUPLICATE);
	Error_RegisterHR(DDERR_NOTLOCKED);
	Error_RegisterHR(DDERR_CANTCREATEDC);
	Error_RegisterHR(DDERR_NODC);
	Error_RegisterHR(DDERR_WRONGMODE);
	Error_RegisterHR(DDERR_IMPLICITLYCREATED);
	Error_RegisterHR(DDERR_NOTPALETTIZED);
	Error_RegisterHR(DDERR_UNSUPPORTEDMODE);
	Error_RegisterHR(DDERR_NOMIPMAPHW);
	Error_RegisterHR(DDERR_INVALIDSURFACETYPE);
	Error_RegisterHR(DDERR_NOOPTIMIZEHW);
	Error_RegisterHR(DDERR_NOTLOADED);
	Error_RegisterHR(DDERR_NOFOCUSWINDOW);
	Error_RegisterHR(DDERR_NOTONMIPMAPSUBLEVEL);
	Error_RegisterHR(DDERR_DCALREADYCREATED);
	Error_RegisterHR(DDERR_NONONLOCALVIDMEM);
	Error_RegisterHR(DDERR_CANTPAGELOCK);
	Error_RegisterHR(DDERR_CANTPAGEUNLOCK);
	Error_RegisterHR(DDERR_NOTPAGELOCKED);
	Error_RegisterHR(DDERR_MOREDATA);
	Error_RegisterHR(DDERR_EXPIRED);
	Error_RegisterHR(DDERR_TESTFINISHED);
	Error_RegisterHR(DDERR_NEWMODE);
	Error_RegisterHR(DDERR_D3DNOTINITIALIZED);
	Error_RegisterHR(DDERR_VIDEONOTACTIVE);
	Error_RegisterHR(DDERR_NOMONITORINFORMATION);
	Error_RegisterHR(DDERR_NODRIVERSUPPORT);
	Error_RegisterHR(DDERR_DEVICEDOESNTOWNSURFACE);

	Error_RegisterHR(DXFILEERR_BADOBJECT);
	Error_RegisterHR(DXFILEERR_BADVALUE);
	Error_RegisterHR(DXFILEERR_BADTYPE);
	Error_RegisterHR(DXFILEERR_BADSTREAMHANDLE);
	Error_RegisterHR(DXFILEERR_BADALLOC);
	Error_RegisterHR(DXFILEERR_NOTFOUND);
	Error_RegisterHR(DXFILEERR_NOTDONEYET);
	Error_RegisterHR(DXFILEERR_FILENOTFOUND);
	Error_RegisterHR(DXFILEERR_RESOURCENOTFOUND);
	Error_RegisterHR(DXFILEERR_URLNOTFOUND);
	Error_RegisterHR(DXFILEERR_BADRESOURCE);
	Error_RegisterHR(DXFILEERR_BADFILETYPE);
	Error_RegisterHR(DXFILEERR_BADFILEVERSION);
	Error_RegisterHR(DXFILEERR_BADFILEFLOATSIZE);
	Error_RegisterHR(DXFILEERR_BADFILECOMPRESSIONTYPE);
	Error_RegisterHR(DXFILEERR_BADFILE);
	Error_RegisterHR(DXFILEERR_PARSEERROR);
	Error_RegisterHR(DXFILEERR_NOTEMPLATE);
	Error_RegisterHR(DXFILEERR_BADARRAYSIZE);
	Error_RegisterHR(DXFILEERR_BADDATAREFERENCE);
	Error_RegisterHR(DXFILEERR_INTERNALERROR);
	Error_RegisterHR(DXFILEERR_NOMOREOBJECTS);
	Error_RegisterHR(DXFILEERR_BADINTRINSICS);
	Error_RegisterHR(DXFILEERR_NOMORESTREAMHANDLES);
	Error_RegisterHR(DXFILEERR_NOMOREDATA);
	Error_RegisterHR(DXFILEERR_BADCACHEFILE);
	Error_RegisterHR(DXFILEERR_NOINTERNET);

	Error_RegisterHR(DIERR_OLDDIRECTINPUTVERSION);
	Error_RegisterHR(DIERR_BETADIRECTINPUTVERSION);
	Error_RegisterHR(DIERR_BADDRIVERVER);
	Error_RegisterHR(DIERR_DEVICENOTREG);
	Error_RegisterHR(DIERR_NOTFOUND);
	Error_RegisterHR(DIERR_OBJECTNOTFOUND);
	Error_RegisterHR(DIERR_INVALIDPARAM);
	Error_RegisterHR(DIERR_NOINTERFACE);
	Error_RegisterHR(DIERR_GENERIC);
	Error_RegisterHR(DIERR_OUTOFMEMORY);
	Error_RegisterHR(DIERR_UNSUPPORTED);
	Error_RegisterHR(DIERR_NOTINITIALIZED);
	Error_RegisterHR(DIERR_ALREADYINITIALIZED);
	Error_RegisterHR(DIERR_NOAGGREGATION);
	Error_RegisterHR(DIERR_OTHERAPPHASPRIO);
	Error_RegisterHR(DIERR_INPUTLOST);
	Error_RegisterHR(DIERR_ACQUIRED);
	Error_RegisterHR(DIERR_NOTACQUIRED);
	Error_RegisterHR(DIERR_READONLY);
	Error_RegisterHR(DIERR_HANDLEEXISTS);
	Error_RegisterHR(DIERR_INSUFFICIENTPRIVS);
	Error_RegisterHR(DIERR_DEVICEFULL);
	Error_RegisterHR(DIERR_MOREDATA);
	Error_RegisterHR(DIERR_NOTDOWNLOADED);
	Error_RegisterHR(DIERR_HASEFFECTS);
	Error_RegisterHR(DIERR_NOTEXCLUSIVEACQUIRED);
	Error_RegisterHR(DIERR_INCOMPLETEEFFECT);
	Error_RegisterHR(DIERR_NOTBUFFERED);
	Error_RegisterHR(DIERR_EFFECTPLAYING);
	Error_RegisterHR(DIERR_UNPLUGGED);
	Error_RegisterHR(DIERR_REPORTFULL);
}

#endif //_DEBUG

VOID Error_Initialise(VOID) {

#ifdef _DEBUG

	Error_RegisterHResults();

	{
		ULONG loop;

		Error_RegisterDXMName(ErrorDirectXModule_DirectDraw);
		Error_RegisterDXMName(ErrorDirectXModule_Direct3D);
		Error_RegisterDXMName(ErrorDirectXModule_Direct3DRM);
		Error_RegisterDXMName(ErrorDirectXModule_DirectXFile);
		Error_RegisterDXMName(ErrorDirectXModule_DirectInput);
		
		for (loop=0 ; loop<ErrorDirectXModule_Count ; loop++) {
			if (NULL == errorGlobs.dxName[loop]) Error_Fatal(TRUE, Error_Format("DirectXModule #%i is not registered", loop));
		}
	}

	{
		UCHAR path[1024];
		BOOL inquotes = FALSE;
		LPUCHAR s = GetCommandLine();

		sprintf(path, "%s", s);

		for (s=path ; '\0'!=*s ; s++) {
			if ('\"' == *s) inquotes = !inquotes;
			else if (' ' == *s) {
				*s = '\0';
				break;
			}
		}

		if ('\"' == path[0]) s = &path[1];
		else s = path;
		if ('\"' == path[strlen(path)-1]) path[strlen(path)-1] = '\0';
		strcat(path, ".errorlog");

		errorGlobs.logFile = fopen(s, "w");
		Error_Warn(NULL==errorGlobs.logFile, Error_Format("Cannot open error log file '%s' - resuming with standard logging", path));
	}
#endif //_DEBUG

}

VOID Error_Shutdown(VOID) {

#ifdef _DEBUG
	if (errorGlobs.logFile) fclose(errorGlobs.logFile);
#endif // _DEBUG

}

VOID Error_Exit(VOID) {

	Error_Shutdown();
	exit(0);
}

VOID Error_FullScreenMode(BOOL fullScreen) {

#ifdef _DEBUG
	errorGlobs.fullScreen = fullScreen;

	if (fullScreen) Error_Warn(TRUE, "Switching to full screen mode - Message boxes disabled");
	else Error_Warn(TRUE, "Switching out of full screen mode - Message boxes enabled");
#endif //_DEBUG

}

#ifdef _DEBUG

VOID Error_DirectXFunc(HRESULT r, LPUCHAR function, LPUCHAR file, ULONG line) {

	lpErrorHR ehr;
	ULONG loop;
	LPUCHAR error = "Unknown";
	LPUCHAR module = "Unknown";

	for (loop=0 ; loop<errorGlobs.dxErrorHRCount ; loop++) {
		ehr = &errorGlobs.dxErrorHR[loop];
		if (ehr->code == r) {
			if (ehr->name) error = ehr->name;
			if (ErrorDirectXModule_Count != ehr->module) module = errorGlobs.dxName[ehr->module];
			break;
		}
	}
	
	Error_Out(DD_OK!=r, TRUE, file, line, "%s() in module \"%s\" failed with error \"%s\"", function, module, error);
}

VOID Error_Out(BOOL condition, BOOL fatal, LPUCHAR file, ULONG line, LPUCHAR msg, ...) {

	va_list args;
	UCHAR output[2][1024];

	if (condition) {
		va_start(args, msg);
		vsprintf(output[0], msg, args);
		if (errorGlobs.logFile) {
			sprintf(output[1], "%s(%i): %s - %s\n", file, line, fatal?"Fatal":"Warning", output[0]);
			fputs(output[1], errorGlobs.logFile);
		}
		sprintf(output[1], "Select 'Retry' to Debug\n\n%s(%i):\n%s", file, line, output[0]);
		va_end(args);
		if (fatal) {
			if (errorGlobs.fullScreen) Error_Exit();
			else {

				int r;

				ShowCursor(TRUE);
				r = MessageBox(Main_hWnd(), output[1], "Fatal Error", MB_ABORTRETRYIGNORE);
				if (IDRETRY == r) DebugBreak();
				else if (IDABORT == r) Error_Exit();
				ShowCursor(FALSE);
			}
		}
	}
}

LPUCHAR Error_Format(LPUCHAR msg, ...) {

	va_list args;
	static UCHAR line[1024];

	va_start(args, msg);
	vsprintf(line, msg, args);
	va_end(args);

	return line;
}

#endif // _DEBUG
