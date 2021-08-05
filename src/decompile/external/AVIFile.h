#pragma once


// <LegoRR.exe @0049b98e>
HRESULT AVIStreamInfoA(IUnknown * pIAVIStream, void * pAVIStreamInfoA, LONG lSize);
// <LegoRR.exe @0049b994>
IUnknown * AVIStreamGetFrameOpen(IUnknown * pIAVIStream, BITMAPINFOHEADER * lpbiWanted);
// <LegoRR.exe @0049b99a>
HRESULT AVIStreamOpenFromFileA(IUnknown * * lplpIAVIStream, LPCSTR szFile, DWORD fccType, LONG lParam, UINT mode, CLSID * pclsidHandler);
// <LegoRR.exe @0049b9a0>
ULONG AVIStreamRelease(IUnknown * pIAVIStream);
// <LegoRR.exe @0049b9a6>
LPVOID AVIStreamGetFrame(IUnknown * pIGetFrame, LONG lPos);

