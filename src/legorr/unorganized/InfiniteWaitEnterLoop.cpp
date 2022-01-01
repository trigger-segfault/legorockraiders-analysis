
NERPs:SetMessage(*, False) // 0x0
// textFlags = 0x18000; // (0x10000 | 0x08000)
NERPs:SetMessage(*, True)  // 0x1
// textFlags = 0x10001; // (0x10000 | 0x1)

// This... doesn't do anything...
// textFlags -= 1; -> 0x10000
// textFlags -= 1; -> 0x0ffff


```cpp
if (NERPsRuntime_GetMessageWait())
{
  // Ensure the screen has rendered before going into the endless wait loop.
  DirectDraw_Flip();
  // IsKeyUp(KEY_RETURN) || IsKeyUnchanged(KEY_RETURN)  (28)
  // 
  // ...What is going on here? An infinite loop until the user presses enter??
  // ...This is really bad.
  while (!IsKeyPressed(KEY_RETURN))
  {
    Input_ReadKeys();
  }
}
```