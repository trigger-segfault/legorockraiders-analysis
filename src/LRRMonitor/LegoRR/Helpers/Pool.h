// Pool.h : Declares ReservedPool<,> collection used by LegoRR to manage
//          unordered objects without reallocation.
//

#pragma once

#include "../Common.h"


namespace lego {
namespace pool {

#pragma region Template Subtypes

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

#pragma endregion


#pragma region Main Template Class

// This is a template declaration describing the common behavior in LegoRR
//  of storing resources in a style of linked list where all the allocations
//  are managed at a global-level.
//  (items returned from the pool should not have to manage freeing themselves)
template <typename T, size_t Size = 32U, typename I = unsigned int, size_t AddrTable = 0, size_t AddrNext = 0, size_t AddrCount = 0, size_t AddrInit = 0>
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
	size_t g_COUNT;

public:
	// True if ReservedPool<T,Size>::Init() has been called, and ReservedPool<T,Size>::Cleanup() has not been called.
	// Sometimes this field is used as a set of flags (where 0x1 always states the pool has been initialized).
	I g_INITFLAGS;

private:
	// Allocate the next exponentionally-sized pool (MUST be called when ReservedPool<T,Size>::g_NEXT is NULL).
	void __cdecl Alloc() {
		unsigned int count = 1 << ((unsigned char)this->g_COUNT & 0x1f);
		PoolItem<T>* nextPool = (PoolItem<T>*)std::malloc(count * sizeof(PoolItem<T>));
		assert(nextPool != nullptr); // (asserts are for testing only)
		this->g_TABLE[this->g_COUNT] = nextPool;
		if (nextPool != nullptr && count != 0) {
			this->g_COUNT++;
			for (size_t i = 1; i < count; i++)
				nextPool[i - 1].m_next = &nextPool[i];
			nextPool[count - 1].m_next = this->g_NEXT;
			assert(nextPool[count - 1].m_next == nullptr); // (asserts are for testing only)
			this->g_NEXT = &nextPool[0];
		}
	}

public:
	// Initialize the table to it default state.
	void Init() {
		std::memset(this->g_TABLE, 0, sizeof(ReservedPool<T, Size>::g_TABLE));
		this->g_NEXT = nullptr;
		this->g_COUNT = 0;
		this->g_INITFLAGS = 0x1;
	}
	// Cleanup the table and free all allocated pools.
	void Cleanup() {
		for (int i = 0; i < Size; i++) {
			if (this->g_TABLE[i] != nullptr)
				std::free(this->g_TABLE[i]);
		}
		this->g_NEXT = nullptr;
		this->g_INITFLAGS = 0;
	}
	// Return (and allocate if needed) the next available item in the pool.
	// This function is usually combined with the initialization function for a structure.
	T* Next() {
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
	void Release(T* item) {
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

	// Helper function to check whether an item is in-use or not.
	bool IsUsed(T* item) const {
		// Cast to the full PoolItem<T> container type
		//  (which always starts at the same address as item)
		return ((PoolItem<T>*)item)->m_next == ((PoolItem<T>*)item);
	}

	// Helper function to return the capacity of all allocated pools.
	size_t Capacity() const {
		size_t capacity = 0;
		for (size_t i = 0; i < this->g_COUNT; i++) {
			capacity += 1U << (i & 0x1f);
		}
		return capacity;
	}
	// Helper function to return the capacity of all allocated pools, and total number of items in-use.
	size_t Capacity(size_t* out_total) const {
		size_t capacity = 0;
		size_t total = 0;
		for (size_t i = 0; i < this->g_COUNT; i++) {
			size_t curCount = 1U << (i & 0x1f);
			capacity += curCount;
			for (size_t j = 0; j < curCount; j++) {
				PoolItem<T>* current = &this->g_TABLE[i][j];
				if (current->m_next == current)
					total++;
			}
		}
		if (out_total != nullptr)
			*out_total = total;
		return capacity;
	}
	size_t Total() const {
		size_t total = 0;
		for (size_t i = 0; i < this->g_COUNT; i++) {
			size_t curCount = 1U << (i & 0x1f);
			for (size_t j = 0; j < curCount; j++) {
				PoolItem<T>* current = &this->g_TABLE[i][j];
				if (current->m_next == current)
					total++;
			}
		}
		return total;
	}
	int IndexOf(T* item, int* out_pool, int* out_poolIndex) const {
		// Cast to the full PoolItem<T> container type
		//  (which always starts at the same address as item)
		PoolItem<T>* current = (PoolItem<T>*)item;
		size_t capacity = 0;
		size_t total = 0;
		for (size_t i = 0; i < this->g_COUNT; i++) {
			size_t curCount = 1U << (i & 0x1f);
			if (current >= &this->g_TABLE[i][0] && current < &this->g_TABLE[i][curCount]) {
				*out_pool = (int)i;
				int poolIndex = (int)(current - &this->g_TABLE[i][0]) / (int)sizeof(PoolItem<T>);
				if (out_pool != nullptr)
					*out_pool = (int)i;
				if (out_poolIndex != nullptr)
					*out_poolIndex = poolIndex;
				return (int)capacity + poolIndex;
			}
			capacity += curCount;
			for (size_t j = 0; j < curCount; j++) {
				PoolItem<T>* current = &this->g_TABLE[i][j];
				if (current->m_next == current)
					total++;
			}
		}
		if (out_pool != nullptr)
			*out_pool = -1;
		if (out_poolIndex != nullptr)
			*out_poolIndex = -1;
		return -1;
	}
};
/*template <typename T, size_t Size> PoolItem<T>* ReservedPool<T,Size>::g_TABLE[Size];
template <typename T, size_t Size> PoolItem<T>* ReservedPool<T,Size>::g_NEXT = nullptr;
template <typename T, size_t Size> unsigned int ReservedPool<T,Size>::g_COUNT = 0;
template <typename T, size_t Size> BOOL ReservedPool<T,Size>::g_ISINIT = FALSE;*/

#pragma endregion

struct MyStruct
{
	char data[0x30];
};

ReservedPool<MyStruct, 20, unsigned int, 0x00541584, 0x005415d4, 0x005415d8, 0xffffffff> MyStructPool;

} /* namespace pool */
} /* namespace lego */
