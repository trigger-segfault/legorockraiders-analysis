# Microsoft Developer Studio Project File - Name="Gods98" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Gods98 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Gods98.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Gods98.mak" CFG="Gods98 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Gods98 - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Gods98 - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "Gods98 - Win32 Stripped" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/LFPC/Gods98", XPAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Gods98 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Gods98 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_GODS98COMPILE" /D "_GODS98_USEWAD_" /YX /FD /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Gods98 - Win32 Stripped"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Gods98__"
# PROP BASE Intermediate_Dir "Gods98__"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Stripped"
# PROP Intermediate_Dir "Stripped"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /ZI /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_GODS98COMPILE" /D "_GODS98_USEWAD_" /FR /YX /FD /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "Gods98 - Win32 Release"
# Name "Gods98 - Win32 Debug"
# Name "Gods98 - Win32 Stripped"
# Begin Group "Source Files"

# PROP Default_Filter "*.c"
# Begin Source File

SOURCE=.\src\3DSound.c
# End Source File
# Begin Source File

SOURCE=.\src\Activities.c
# End Source File
# Begin Source File

SOURCE=.\src\AnimClone.c
# End Source File
# Begin Source File

SOURCE=.\src\Bmp.c
# End Source File
# Begin Source File

SOURCE=.\src\Config.c
# End Source File
# Begin Source File

SOURCE=.\src\Containers.c
# End Source File
# Begin Source File

SOURCE=.\src\DirectDraw.c
# End Source File
# Begin Source File

SOURCE=.\src\Draw.c
# End Source File
# Begin Source File

SOURCE=.\src\dxbug.c
# End Source File
# Begin Source File

SOURCE=.\src\Errors.c
# End Source File
# Begin Source File

SOURCE=.\src\Files.c
# End Source File
# Begin Source File

SOURCE=.\src\Flic.c
# End Source File
# Begin Source File

SOURCE=.\src\Fonts.c
# End Source File
# Begin Source File

SOURCE=.\src\Images.c
# End Source File
# Begin Source File

SOURCE=.\src\Input.c
# End Source File
# Begin Source File

SOURCE=.\src\Keys.c
# End Source File
# Begin Source File

SOURCE=.\src\Lws.c
# End Source File
# Begin Source File

SOURCE=.\src\lwt.c
# End Source File
# Begin Source File

SOURCE=.\src\Main.c
# End Source File
# Begin Source File

SOURCE=.\src\Materials.c
# End Source File
# Begin Source File

SOURCE=.\src\Maths.c
# End Source File
# Begin Source File

SOURCE=.\src\Memory.c
# End Source File
# Begin Source File

SOURCE=.\src\Mesh.c
# End Source File
# Begin Source File

SOURCE=.\src\net.c
# End Source File
# Begin Source File

SOURCE=.\src\Registry.c
# End Source File
# Begin Source File

SOURCE=.\src\Sound.c
# End Source File
# Begin Source File

SOURCE=.\src\TextWindow.c
# End Source File
# Begin Source File

SOURCE=.\src\Utils.c
# End Source File
# Begin Source File

SOURCE=.\src\Viewports.c
# End Source File
# Begin Source File

SOURCE=.\src\Wad.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\inc\3DSound.h
# End Source File
# Begin Source File

SOURCE=.\inc\Activities.h
# End Source File
# Begin Source File

SOURCE=.\inc\Animation.h
# End Source File
# Begin Source File

SOURCE=.\inc\AnimClone.h
# End Source File
# Begin Source File

SOURCE=.\inc\Bmp.h
# End Source File
# Begin Source File

SOURCE=.\inc\Compress.h
# End Source File
# Begin Source File

SOURCE=.\inc\Config.h
# End Source File
# Begin Source File

SOURCE=.\inc\Containers.h
# End Source File
# Begin Source File

SOURCE=.\inc\DirectDraw.h
# End Source File
# Begin Source File

SOURCE=.\inc\Draw.h
# End Source File
# Begin Source File

SOURCE=.\inc\dxbug.h
# End Source File
# Begin Source File

SOURCE=.\inc\Errors.h
# End Source File
# Begin Source File

SOURCE=.\inc\Files.h
# End Source File
# Begin Source File

SOURCE=.\inc\Flic.h
# End Source File
# Begin Source File

SOURCE=.\inc\Fonts.h
# End Source File
# Begin Source File

SOURCE=.\inc\Images.h
# End Source File
# Begin Source File

SOURCE=.\inc\Input.h
# End Source File
# Begin Source File

SOURCE=.\inc\Keys.h
# End Source File
# Begin Source File

SOURCE=.\inc\Lws.h
# End Source File
# Begin Source File

SOURCE=.\inc\lwt.h
# End Source File
# Begin Source File

SOURCE=.\inc\Main.h
# End Source File
# Begin Source File

SOURCE=.\inc\Materials.h
# End Source File
# Begin Source File

SOURCE=.\inc\Maths.h
# End Source File
# Begin Source File

SOURCE=.\inc\Memory.h
# End Source File
# Begin Source File

SOURCE=.\inc\Mesh.h
# End Source File
# Begin Source File

SOURCE=.\inc\Net.h
# End Source File
# Begin Source File

SOURCE=.\inc\Registry.h
# End Source File
# Begin Source File

SOURCE=.\inc\Sound.h
# End Source File
# Begin Source File

SOURCE=.\inc\Standard.h
# End Source File
# Begin Source File

SOURCE=.\inc\TextWindow.h
# End Source File
# Begin Source File

SOURCE=.\inc\Utils.h
# End Source File
# Begin Source File

SOURCE=.\inc\Viewports.h
# End Source File
# Begin Source File

SOURCE=.\inc\wad.h
# End Source File
# End Group
# Begin Group "Prototype Files"

# PROP Default_Filter "*.prot"
# Begin Source File

SOURCE=.\src\3DSound.prot
# End Source File
# Begin Source File

SOURCE=.\src\AnimClone.prot
# End Source File
# Begin Source File

SOURCE=.\src\Bmp.prot
# End Source File
# Begin Source File

SOURCE=.\src\Config.prot
# End Source File
# Begin Source File

SOURCE=.\src\Containers.prot
# End Source File
# Begin Source File

SOURCE=.\src\DirectDraw.prot
# End Source File
# Begin Source File

SOURCE=.\src\Draw.prot
# End Source File
# Begin Source File

SOURCE=.\src\Errors.prot
# End Source File
# Begin Source File

SOURCE=.\src\Files.prot
# End Source File
# Begin Source File

SOURCE=.\src\Flic.prot
# End Source File
# Begin Source File

SOURCE=.\src\Fonts.prot
# End Source File
# Begin Source File

SOURCE=.\src\Images.prot
# End Source File
# Begin Source File

SOURCE=.\src\Keys.prot
# End Source File
# Begin Source File

SOURCE=.\src\Lws.prot
# End Source File
# Begin Source File

SOURCE=.\src\Main.prot
# End Source File
# Begin Source File

SOURCE=.\src\Materials.prot
# End Source File
# Begin Source File

SOURCE=.\src\Maths.prot
# End Source File
# Begin Source File

SOURCE=.\src\Mesh.prot
# End Source File
# Begin Source File

SOURCE=.\src\Sound.prot
# End Source File
# Begin Source File

SOURCE=.\src\TextWindow.prot
# End Source File
# Begin Source File

SOURCE=.\src\Utils.prot
# End Source File
# Begin Source File

SOURCE=.\src\Viewports.prot
# End Source File
# End Group
# Begin Source File

SOURCE=.\Animation.cpp
# End Source File
# End Target
# End Project
