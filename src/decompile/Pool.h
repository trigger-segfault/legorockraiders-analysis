// Pool.h : Helper declarations to simplify usage of ReservedPool<,> collection types.
//
/// STATUS: [Usable, but constantly being rewritten]
/// PURPOSE: The ReservedPool<,> container is a common occurance in LegoRR.exe.
///          In total, 9 different structure types make use of this container.
///
/// NAMESPACE: lego::pool

#pragma once

#include "Common.h"


#pragma region Pool Template Subtypes
namespace lego:pool {

// Pool container item around template type.
// Always extends type size by +0x4, and ends in a pointer to another of the same type.
// This structure exists for INTERNAL USE ONLY by ReservedPool<T,Size> as a method of templating
//  a typename, without also including the unecessary size template parameter.
template <typename T>
struct PoolItem
{
	/*0,T*/ T m_item;
	/*T,4*/ PoolItem* m_next;
	/*T+4*/
};

} /* namespace lego:pool */
#pragma endregion


#pragma region Main Template Class
namespace lego:pool {

// This is a template declaration describing the common behavior in LegoRR
//  of storing resources in a style of linked list where all the allocations
//  are managed at a global-level.
//  (items returned from the pool should not have to manage freeing themselves)
template <typename T, size_t Size = 32U, typename F = uint>
class ReservedPool
{
private:
	// All ReservedPool fields are observed as global variables, hence the naming convention is kept here.

	// Table of exponentially-sized pools, allocated as needed.
	//  g_TABLE[0] = new T[1],  g_TABLE[1] = new T[2],  g_TABLE[2] = new T[4], g_TABLE[3] = new T[8],
	//  g_TABLE[4] = new T[16], g_TABLE[5] = new T[32], g_TABLE[6] = new T[64]...
	PoolItem<T>* g_TABLE[Size];
	// Next available ReservedPool<T,Size> to use, or NULL if another table needs to be allocated.
	PoolItem<T>* g_NEXT;
	// Exponential size of the last-created table (max is 32).
	uint g_COUNT;

public:
	// True if ReservedPool<T,Size>::Init() has been called, and ReservedPool<T,Size>::Cleanup() has not been called.
	// Sometimes this field is used as a set of flags (where 0x1 always states the pool has been initialized).
	F initFlags;

private:
	// Allocate the next exponentionally-sized pool (MUST be called when ReservedPool<T,Size>::g_NEXT is NULL).
	void __cdecl Alloc() {
		uint count = 1 << (this->g_COUNT & 0x1f);
		PoolItem<T>* nextPool = (PoolItem<T>*)std::malloc(count * sizeof(PoolItem<T>));
		assert(nextPool != nullptr); // (asserts are for testing only)
		this->g_TABLE[this->g_COUNT] = nextPool;
		if (nextPool != nullptr && count != 0) {
			this->g_COUNT++;
			for (uint i = 1; i < count; i++)
				nextPool[i - 1].m_next = &nextPool[i];
			nextPool[count - 1].m_next = this->g_NEXT;
			assert(nextPool[count - 1].m_next == nullptr); // (asserts are for testing only)
			this->g_NEXT = &nextPool[0];
		}
	}

public:
	// Initialize the table to it default state.
	void __cdecl Init() {
		std::memset(this->g_TABLE, 0, sizeof(ReservedPool<T, Size>::g_TABLE));
		this->g_NEXT = nullptr;
		this->g_COUNT = 0;
		this->g_ISINIT = TRUE;
	}
	// Cleanup the table and free all allocated pools.
	void __cdecl Cleanup() {
		for (int i = 0; i < Size; i++) {
			if (this->g_TABLE[i] != nullptr)
				std::free(this->g_TABLE[i]);
		}
		this->g_NEXT = nullptr;
		this->g_ISINIT = FALSE;
	}
	// Return (and allocate if needed) the next available item in the pool.
	// This function is usually combined with the initialization function for a structure.
	T* __cdecl Next() {
		if (this->g_NEXT == nullptr)
			this->Alloc();

		PoolItem<T>* current = this->g_NEXT;
		this->g_NEXT = this->g_NEXT->m_next; // move to next available
		// A pool item whose's m_next field points to itself,
		// is an item that has been loaned out.
		assert(current->m_next != current);
		current->m_next = current; // sever link to next available in our returned item
		return &current->m_item;
	}
	// Release a loaned item, and return it to the pool.
	// Similar to Next, more actions than just this are often performed in the Release function.
	void __cdecl Release(T* item) {
		// Cast to the full PoolItem<T> container type
		//  (which always starts at the same address as item)
		PoolItem<T>* current = (PoolItem<T>*)item;

		// This behavior treats g_NEXT like a linked list stack.
		// Released items get pushed on top, and link back to
		// previously released/unused pool items.
		assert(current->m_next == current);
		current->m_next = this->g_NEXT; // restore link to next available in our released item
		this->g_NEXT = current; // change next available to our released item
	}
};
/*template <typename T, size_t Size> PoolItem<T>* ReservedPool<T,Size>::g_TABLE[Size];
template <typename T, size_t Size> PoolItem<T>* ReservedPool<T,Size>::g_NEXT = nullptr;
template <typename T, size_t Size> uint ReservedPool<T,Size>::g_COUNT = 0;
template <typename T, size_t Size> BOOL ReservedPool<T,Size>::g_ISINIT = FALSE;*/

} /* namespace lego::pool */
#pragma endregion

