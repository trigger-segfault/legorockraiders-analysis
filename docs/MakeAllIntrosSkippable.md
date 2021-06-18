# Make All Lego Intros Skippable in Assembly

[NOP Sleds](https://en.wikipedia.org/wiki/NOP_slide), to allow skipping ALL intros without needing the programmer mode command line argument :D

This assumes the LegoRR Masterpiece executable is being used.

***

## Original Assembly

#### **LegoAvi:** ASM to load slow-*as-lv1-rockraider-over-rubble* Lego Media AVI
```asm
0042020d f7 d8     NEG   EAX
0042020f 1b c0     SBB   EAX,EAX
00420211 f7 d8     NEG   EAX
00420213 50        PUSH  EAX
00420214 68 5c 4b  PUSH  s_LegoAvi_004a4b5c                   = "LegoAvi"
         4a 00
00420219 e8 22 56  CALL  lego::main::Boot_loadAVIProperty     void Boot_loadAVIProperty(char*,BOOL)
         ff ff
```

#### **LMILogo:** ASM to load LMI splash
```asm
0042025d f7 d8     NEG   EAX
0042025f 1b c0     SBB   EAX,EAX
00420261 f7 d8     NEG   EAX
00420263 50        PUSH  EAX
00420264 68 24 4b  PUSH  s_LMILogo_004a4b24                   = "LMILogo"
         4a 00
00420269 e8 82 54  CALL  lego::main::Boot_loadSplashProperty  void Boot_loadSplashProperty(char*,BOOL,char*)
         ff ff
```

***

## NOP Sled Assembly

#### ASM Instructions used by sled
```asm
90              NOP
6a 01           PUSH       0x1
```


#### **Sled:** ASM to replace for both normally unskippable intros
```asm
NOP (5),       PUSH 0x1
90 90 90 90 90 6a 01
```

#### **LegoAvi:** Search & Replace the first 7 bytes with sled
```asm
f7 d8 1b c0 f7 d8 50 68 5c 4b 4a 00
;|  |  |  |  |  |  |  \___________\__ search for this as its unique
;v  v  v  v  v  v  v
90 90 90 90 90 6a 01
```

#### **LMILogo:** Search & Replace the first 7 bytes with sled
```asm
f7 d8 1b c0 f7 d8 50 68 24 4b 4a 00
;|  |  |  |  |  |  |  \___________\__ search for this as its unique
;v  v  v  v  v  v  v
90 90 90 90 90 6a 01
```
