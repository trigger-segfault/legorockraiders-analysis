
#ifndef LEGORR__RESERVED_POOL_H
#define LEGORR__RESERVED_POOL_H

#include "Common.h"


#pragma region /// RESERVED POOL ////////////////////////

// This is a template declaration describing the common behavior in LegoRR
//  of storing resources in a style of linked list where all the allocations
//  are managed at a global-level.
//  (items returned from the pool should not have to manage freeing themselves)
template <typename T> class ReservedPool {
private:
	/*0,T*/ T m_item;
	/*T,4*/ ReservedPool* m_next;
	/*T+4*/

	// Table of exponentially-sized pools, allocated as needed
	//  g_TABLE[0] = new T[1],  g_TABLE[1] = new T[2],  g_TABLE[2] = new T[4], g_TABLE[3] = new T[8],
	//  g_TABLE[4] = new T[16], g_TABLE[5] = new T[32], g_TABLE[6] = new T[64]...
	static ReservedPool* g_TABLE[32];
	// Next available ReservedPool<T> to use, or NULL if another table needs to be allocated
	static ReservedPool* g_NEXT;
	// Exponential size of the last-created table (max is 32)
	static unsigned int g_COUNT;
	// True if ReservedPool<T>::Init() has been called, and ReservedPool<T>::Cleanup() has not been called
	static BOOL g_ISINIT;

	// Allocate the next exponentionally-sized pool (MUST be called when ReservedPool<T>::g_NEXT is NULL)
	static void __cdecl Alloc() {
		unsigned int count = 1 << ((unsigned char)ReservedPool<T>::g_COUNT & 0x1f);
		ReservedPool<T>* nextPool = (ReservedPool<T>*)malloc(count * sizeof(ReservedPool<T>));
		assert(nextPool != NULL); // (asserts are for testing only)
		ReservedPool<T>::g_TABLE[ReservedPool<T>::g_COUNT] = nextPool;
		if (nextPool != NULL && count != 0) {
			ReservedPool<T>::g_COUNT++;
			for (unsigned int i = 1; i < count; i++)
				nextPool[i - 1].m_next = &nextPool[i];
			nextPool[count - 1].m_next = ReservedPool<T>::g_NEXT;
			assert(nextPool[count - 1].m_next == NULL); // (asserts are for testing only)
			ReservedPool<T>::g_NEXT = &nextPool[0];
		}
	}

public:
	// Initialize the table to it default state
	static void __cdecl Init() {
		memset(ReservedPool<T>::g_TABLE, 0, sizeof(ReservedPool<T>::g_TABLE));
		ReservedPool<T>::g_NEXT = NULL;
		ReservedPool<T>::g_COUNT = 0U;
		ReservedPool<T>::g_ISINIT = true /*1*/;
	}
	// Cleanup the table and free all allocated pools
	static void __cdecl Cleanup() {
		for (int i = 0; i < 32; i++) {
			if (ReservedPool<T>::g_TABLE[i] != NULL)
				free(ReservedPool<T>::g_TABLE[i]);
		}
		ReservedPool<T>::g_NEXT = NULL;
		ReservedPool<T>::g_ISINIT = false /*0*/;
	}
	// Return (and allocate if needed) the next available item in the pool
	static T* __cdecl Next() {
		if (ReservedPool<T>::g_NEXT == NULL) {
			ReservedPool<T>::Alloc();
		}
		ReservedPool<T>* current = ReservedPool<T>::g_NEXT;
		ReservedPool<T>::g_NEXT = ReservedPool<T>::g_NEXT->m_next; // move to next available
		current->m_next = current; // sever link to next available in our returned item
		return &current->m_item;
	}
};
template <typename T> ReservedPool<T>* ReservedPool<T>::g_TABLE[32];
template <typename T> ReservedPool<T>* ReservedPool<T>::g_NEXT = NULL;
template <typename T> unsigned int ReservedPool<T>::g_COUNT = 0U;
template <typename T> BOOL ReservedPool<T>::g_ISINIT = false /*0*/;

#pragma endregion


#pragma region /// CFG EXAMPLE //////////////////////////

// CFG Property (node) structure
// this type is used for the root, block properties, and key/value properties.
struct CFGProperty {
	/*00,4*/ char* rootFileText; // the entire CFG file text (only stored for root property)
	/*04,4*/ char* key;   // init: NULL
	/*08,4*/ char* value; // init: NULL
	/*0c,4*/ unsigned int depth;    // init: 0 (if root)
	/*10,4*/ unsigned int field_10; // init: 0 (unknown usage)
	/*14,4*/ CFGProperty* propNext; // init: NULL
	/*18,4*/ CFGProperty* propPrevious;  // init: NULL (if root)
	/*1c*/
};

template <typename T> ReservedPool<T>* ReservedPool<T>::g_TABLE[32];
template <typename T> ReservedPool<T>* ReservedPool<T>::g_NEXT = NULL;
template <typename T> unsigned int ReservedPool<T>::g_COUNT = 0U;
template <typename T> BOOL ReservedPool<T>::g_ISINIT = false /*0*/;

// <LegoRR.exe @00507498>
static ReservedPool<CFGProperty>* ReservedPool<CFGProperty>::g_TABLE[32];
// <LegoRR.exe @00507518>
static ReservedPool<CFGProperty>* ReservedPool<CFGProperty>::g_NEXT;
// <LegoRR.exe @0050751c>
static unsigned int ReservedPool<CFGProperty>::g_COUNT;
// <LegoRR.exe @00507520>
static BOOL ReservedPool<CFGProperty>::g_ISINIT;

// <LegoRR.exe @004790b0>
static void __cdecl ReservedPool<CFGProperty>::Init();
// <LegoRR.exe @004790e0>
static void __cdecl ReservedPool<CFGProperty>::Cleanup();
// <LegoRR.exe @00479750>
static void __cdecl ReservedPool<CFGProperty>::Alloc();
// (this function always seems to be inlined within the structure's initialize function)
// <LegoRR.exe -> CFG_allocNextProperty @00479530>
static CFGProperty* __cdecl ReservedPool<CFGProperty>::Next();

// <LegoRR.exe @00479530>
CFGProperty* __cdecl CFG_allocNextProperty(CFGProperty* previous)
{
	CFGProperty* prop = ReservedPool<CFGProperty>::Next();

	prop->key = NULL;
	prop->value = NULL;
	prop->propNext = NULL;
	if (previous != NULL) {
		previous->propNext = prop;
		prop->propPrevious = previous;
		prop->depth = previous->depth;
		prop->rootFileText = NULL; // field not used by non-root properties.
	}
	else {
		prop->propPrevious = NULL;
		prop->depth = 0;
	}
	return prop;
}

// <LegoRR.exe @00477a60>
int WinEntry(HINSTANCE hInstance) {
	ReservedPool<CFGProperty>::Init();


	ReservedPool<CFGProperty>::Cleanup();
}

#pragma endregion


#endif /* LEGORR__RESERVED_POOL_H */
