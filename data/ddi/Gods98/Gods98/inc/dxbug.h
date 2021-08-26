// Set a directX error value
#define SET_DXERROR(hres, module) Error_SetDXError(hres, module, __FILE__, __LINE__)

// Set a DX erro valuer for a supported module 
// (ie. R.etained M.ode / D.irect D.raw / D.irect I.nput / I.U.nknown)
#define SET_RMERROR(hres) SET_DXERROR((hres), ERROR_D3DRM)
#define SET_DDERROR(hres) SET_DXERROR((hres), ERROR_DDRAW)
#define SET_DIERROR(hres) SET_DXERROR((hres), ERROR_DINPUT)
#define SET_IUERROR(hres) SET_DXERROR((hres), ERROR_IUNKNOWN)

// Check a Direct X return value
#define CHKRM(hres) {if ((hres) != D3DRM_OK)	{ SET_RMERROR(hres);}}
#define CHKDD(hres) {if ((hres) != DD_OK)		{ SET_DDERROR(hres);}}
#define CHKDI(hres) {if ((hres) != DI_OK)		{ SET_DIERROR(hres);}}
#define CHKIU(hres) {if ((hres) != S_OK)		{ SET_IUERROR(hres);}}

// Check the return value and return if failed
#define CHKRM_V(hres) {if ((hres) != D3DRM_OK)	{ SET_RMERROR(hres); return; }}
#define CHKDD_V(hres) {if ((hres) != DD_OK)		{ SET_DDERROR(hres); return; }}
#define CHKDI_V(hres) {if ((hres) != DI_OK)		{ SET_DIERROR(hres); return; }}
#define CHKIU_V(hres) {if ((hres) != S_OK)		{ SET_IUERROR(hres); return; }}

// as above but return an arbitrary value
#define CHKRM_RET(hres,retval) {if ((hres) != D3DRM_OK)	{ SET_RMERROR(hres); return (retval); }}
#define CHKDD_RET(hres,retval) {if ((hres) != DD_OK)	{ SET_DDERROR(hres); return (retval); }}
#define CHKDI_RET(hres,retval) {if ((hres) != DI_OK)	{ SET_DIERROR(hres); return (retval); }}
#define CHKIU_RET(hres,retval) {if ((hres) != S_OK)		{ SET_IUERROR(hres); return (retval); }}

// As above but return TRUE
#define CHKRM_T(hres) CHKRM_RET(hres,TRUE);
#define CHKDD_T(hres) CHKDD_RET(hres,TRUE);
#define CHKDI_T(hres) CHKDI_RET(hres,TRUE);
#define CHKIU_T(hres) CHKIU_RET(hres,TRUE);

// As above but return FALSE
#define CHKRM_F(hres) CHKRM_RET(hres,FALSE);
#define CHKDD_F(hres) CHKDD_RET(hres,FALSE);
#define CHKDI_F(hres) CHKDI_RET(hres,FALSE);
#define CHKIU_F(hres) CHKIU_RET(hres,FALSE);

// Return a boolean depending on result
#define CHKRM_B(hres) {if (hres == D3DRM_OK)	return TRUE; else { SET_RMERROR(hres); return FALSE; }}
#define CHKDD_B(hres) {if (hres == DD_OK)		return TRUE; else { SET_DDERROR(hres); return FALSE; }}
#define CHKDI_B(hres) {if (hres == DI_OK)		return TRUE; else { SET_DIERROR(hres); return FALSE; }}
#define CHKIU_B(hres) {if (hres == S_OK)		return TRUE; else { SET_IUERROR(hres); return FALSE; }}

// Supported error modules/objects
enum { ERROR_UNKNOWN, ERROR_D3DRM, ERROR_DINPUT, ERROR_DDRAW, ERROR_DSOUND, ERROR_DPLAY, ERROR_D3DIM, ERROR_IUNKNOWN };

// Function prototypes
extern HRESULT Error_SetDXError(HRESULT err, int DXModule, char *File, int Line);
extern int Error_GetNumDXErrors(void);
extern char *Error_GetLastDXError(void);
extern void Error_ShowLastDXError(void);
