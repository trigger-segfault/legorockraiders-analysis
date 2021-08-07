// Import.h : Declares macro functions for declaring/defining fixed-address
//            variables and functions being referenced by the source program.
//
// 

// DEFINES:
// 
// * VOLATILE_IMPORTS : all variables created with defVar will be volatile by default.
// * DEFINE_IMPORTS   : use this before including files with Import.h to define the actual values.

#ifdef VOLATILE_IMPORTS

#define DEFIMPORT_VOLATILE volatile

#else

#define DEFIMPORT_VOLATILE

#endif


#ifndef DEFINE_IMPORTS

#pragma once
//#define defExtern(symbol, cast, address) extern symbol
//#define defExtern(symbol, cast, address) extern symbol
//#define defExtern(symbol, cast, address) extern symbol
//#define defGlob(symbol, cast, address) extern symbol
//#define defFunc(symbol, cast, address) extern symbol
//#define defCdecl(ADDR, RETURN, NAME, ...) extern RETURN (__cdecl* NAME) __VA_ARGS__ ;

// Declare a variable import from a fixed address
// ... is used to define fixed-array globals, which normally appear after the name
#define defVar(ADDR, TYPE, NAME, ...) /* <LegoRR.exe @ ##ADDR## > */ \
	 extern DEFIMPORT_VOLATILE TYPE (& NAME) __VA_ARGS__ 


// Declare a function import from a fixed address
// ... is used to define function arguments
#define defFun(ADDR, RETURN, CONV, NAME, ...)  /* <LegoRR.exe @ ##ADDR## > */ \
	extern RETURN (CONV* NAME)( __VA_ARGS__ )

#else
//#define defExtern(symbol, cast, address) symbol cast address
//#define defExtern(symbol, cast, address) symbol cast address
//#define defGlob(symbol, cast, address) symbol cast address
//#define defFunc(symbol, cast, address) symbol cast address
//#define defCdecl(ADDR, RETURN, NAME, ...) RETURN (__cdecl* NAME) __VA_ARGS__ = *(decltype(NAME))ADDR;

// Define a variable import with its fixed address
// ... is used to define fixed-array globals, which normally appear after the name
#define defVar(ADDR, TYPE, NAME, ...) \
	DEFIMPORT_VOLATILE TYPE (& NAME) __VA_ARGS__ = *(std::remove_reference_t<decltype(NAME)>*)ADDR

// Define a function import with its fixed address
// ... is used to define function arguments
#define defFun(ADDR, RETURN, CONV, NAME, ...) \
	RETURN (CONV* NAME)( __VA_ARGS__ ) = *(decltype(NAME))ADDR

#endif

// Needed for decltype() and std::remove_reference_t<>
#include <type_traits>

