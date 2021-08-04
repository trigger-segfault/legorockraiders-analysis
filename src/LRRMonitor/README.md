# LRR:CE-based DLL injection

This project exists to inject and replace functions within LEGO Rock Raiders for debugging purposes. It relies on `LegoRRCE.exe` (Community Edition), which already has DLL loading setup for `LRRCE.DLL`.

Community Edition requires that the following function be exported by `LRRCE.DLL`, in order to load the DLL:

```cpp
extern "C" void __cdecl Dummy();
```

The attributes `extern "C"` and `__cdecl` are required in order to avoid name mangling of the function name.