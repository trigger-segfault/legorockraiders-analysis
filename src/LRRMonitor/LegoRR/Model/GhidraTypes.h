#pragma once

// Base types defined by Ghidra. Fighting against these would be more trouble than its worth

typedef long double				float10;  // No... Visual Studio doesn't support this. Just give up :c
typedef long long				longlong;
typedef unsigned char			uchar;
typedef unsigned int			uint;
typedef unsigned long			ulong;
typedef unsigned long long		ulonglong;

typedef unsigned char			undefined;
typedef unsigned char			undefined1;
typedef unsigned short			undefined2;
typedef unsigned int			undefined4;
//typedef unsigned long long		undefined6;
typedef unsigned long long		undefined8;
typedef unsigned short			ushort;

typedef unsigned char			byte;
typedef unsigned short			word;
typedef unsigned int			dword;
typedef unsigned long long		qword;

typedef void*					pointer;
