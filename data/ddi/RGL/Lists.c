
#include "Standard.h"
#include "Errors.h"
#include "Lists.h"
#include "Mem.h"

struct ListGlobs {

	struct List *globalList;

} listGlobs = { 0 };

VOID List_Shutdown(VOID) {

	lpList list, next;

	for (list=listGlobs.globalList ; list ; list=next) {

		next = list->globalListNext;

		Error_Warn(TRUE, Error_Format("Unremoved list created by %s(%d)", list->file, list->line));
		
		List_Remove(list);
	}
}

ULONG List_GetItemCount(lpList list) {

	lpListGenericItemType item;
	ULONG count = (1 << list->listCount);

	for (item=list->freeList ; item ; item=item->nextFree) count--;

	return count;
}

#ifdef _DEBUG
VOID List_Debug_CheckDead(lpList type, LPVOID check, LPUCHAR file, ULONG line) {

	LPUCHAR itemSpace = (LPUCHAR) check;
	lpListGenericItemType item = (lpListGenericItemType) (itemSpace - sizeof(struct ListGenericItemType));

	Error_Fatal(NULL == check, "Item is NULL");
	Error_Fatal(NULL != type && type != item->ownerList, "Item does not belong to this list");
	Error_Out((item->flags & LIST_DEBUG_FLAG_RETURNED), TRUE, file, line, "Item used after being removed...");
}
#endif // _DEBUG

#ifdef _DEBUG
lpList List_Debug_Create(size_t itemWidth, LPUCHAR file, ULONG line) {
#else
lpList List_Create(size_t itemWidth) {
#endif // _DEBUG

	lpList type = Mem_AllocClear(sizeof(*type));

	if (type->globalListNext = listGlobs.globalList) type->globalListNext->globalListPrev = type;
	listGlobs.globalList = type;

	type->itemWidth = sizeof(struct ListGenericItemType) + itemWidth;

#ifdef _DEBUG
	type->file = file;
	type->line = line;
//	type->compareBuffer = Mem_Alloc(itemWidth);
//	memset(type->compareBuffer, LIST_DEBUG_FILLVALUE, itemWidth);
#endif // _DEBUG

	return type;
}

VOID List_Remove(lpList list) {

	if (list == NULL)	return;

	if (list->globalListNext) list->globalListNext->globalListPrev = list->globalListPrev;
	if (list->globalListPrev) list->globalListPrev->globalListNext = list->globalListNext;
	else listGlobs.globalList = list->globalListNext;

	List_Deflate(list, TRUE);
	Mem_Free(list);
}

LPVOID List_ObtainItem(lpList type) {

	lpListGenericItemType item;

	Error_Fatal(NULL==type, "NULL passed as type");

	if (NULL == type->freeList) List_AddArray(type);

	if (item = type->freeList) {
		type->freeList = item->nextFree;
		memset(item->itemSpace, 0, type->itemWidth - sizeof(struct ListGenericItemType));
		item->nextFree = item;							// Point items that are in use to themselves...
	}

#ifdef _DEBUG
	item->flags &= ~LIST_DEBUG_FLAG_RETURNED;
#endif // _DEBUG

	return item->itemSpace;
}

VOID List_ReturnItem(lpList type, LPVOID dead) {

	LPUCHAR itemSpace = (LPUCHAR) dead;
	lpListGenericItemType item = (lpListGenericItemType) (itemSpace - sizeof(struct ListGenericItemType));

	Error_Fatal(NULL == type, "NULL passed as type");
	Error_Fatal(NULL == dead, "NULL passed as dead");
	List_CheckItem(type, dead);

#ifdef _DEBUG
	memset(item->itemSpace, LIST_DEBUG_FILLVALUE, type->itemWidth - sizeof(struct ListGenericItemType));

	if (type->returnedList) {
		type->returnedListEnd->nextFree = item;
		type->returnedListEnd = item;
	} else type->returnedList = type->returnedListEnd = item;
	item->nextFree = NULL;

	if (type->returnedCount < LIST_DEBUG_MAXRETURNEDLISTSIZE) type->returnedCount++;
	else {	// Pop the least recently returned item off the head of the returned list onto the free list...
		item = type->returnedList;
		type->returnedList = type->returnedList->nextFree;
		item->nextFree = type->freeList;
		type->freeList = item;
	}

	item->flags |= LIST_DEBUG_FLAG_RETURNED;
#else // _DEBUG

	item->nextFree = type->freeList;
	type->freeList = item;

#endif // _DEBUG

}

LPVOID List_RunThrough(lpList type, BOOL (*Callback)(LPVOID item, LPVOID data), LPVOID data) {

	lpListGenericItemType item;
	ULONG loop, length, sub;
	LPUCHAR bytePtr;

	Error_Fatal(NULL==type, "NULL passed as type");

	for (loop=0 ; loop<type->listCount ; loop++) {
		bytePtr = (LPUCHAR) type->listSet[loop];
		length = 1<<loop;
		for (sub=0 ; sub<length ; sub++) {
			item = (lpListGenericItemType) &bytePtr[type->itemWidth * sub];
			if (item->nextFree == item) {
				if (Callback(item->itemSpace, data)) return item->itemSpace;
			}
		}
	}

	return NULL;
}

static VOID List_RemoveItemFromFreeList(lpList type, lpListGenericItemType item) {

	lpListGenericItemType prevItem;

	Error_Fatal(item->nextFree == item, "Item is not on the free list");

	if (type->freeList == item) {
		type->freeList = item->nextFree;
#ifdef _DEBUG
	} else if (type->returnedList == item) {
		type->returnedList = item->nextFree;
		if (item == type->returnedListEnd) type->returnedListEnd = NULL;
		type->returnedCount--;
#endif // _DEBUG
	} else {
		for (prevItem=type->freeList ; prevItem ; prevItem=prevItem->nextFree) {
			if (prevItem->nextFree == item) break;
		}
#ifdef _DEBUG
		if (NULL == prevItem) {
			for (prevItem=type->returnedList ; prevItem ; prevItem=prevItem->nextFree) {
				if (prevItem->nextFree == item) break;
			}
			Error_Fatal(NULL == prevItem, "Cannot find item on either the free or returned list!!!");
			if (item == type->returnedListEnd) type->returnedListEnd = prevItem;
			type->returnedCount--;
		}
#endif // _DEBUG

		prevItem->nextFree = item->nextFree;
	}

	item->nextFree = (lpListGenericItemType) 0xD0d0Dead;
}

VOID List_Deflate(lpList type, BOOL force) {

	if (force) {

		ULONG loop;

#ifdef _DEBUG
		type->returnedList = NULL;
		type->returnedListEnd = NULL;
		type->returnedCount = 0;
#endif // _DEBUG

		type->freeList = NULL;
		for (loop=0 ; loop<type->listCount ; loop++) {
			Mem_Free(type->listSet[loop]);
			type->listSet[loop] = NULL;
		}
		type->listCount = 0;

	} else {

		lpListGenericItemType item;
		ULONG length, sub;
		LPUCHAR bytePtr;
		SLONG loop;

		for (loop=type->listCount-1 ; loop>=0 ; loop--) {

			bytePtr = (LPUCHAR) type->listSet[loop];
			length = 1 << loop;
			
			for (sub=0 ; sub<length ; sub++) {
				item = (lpListGenericItemType) &bytePtr[type->itemWidth * sub];
				if (item->nextFree == item) break;
			}

			if (sub == length) {

				for (sub=0 ; sub<length ; sub++) {
					item = (lpListGenericItemType) &bytePtr[type->itemWidth * sub];
					if (item->nextFree != item) List_RemoveItemFromFreeList(type, item);
				}

				Mem_Free(type->listSet[loop]);
				type->listSet[loop] = NULL;
				type->listCount--;

			} else break;
		}
	}	
}

static VOID List_AddArray(lpList type) {

	if (type->listCount < LIST_COUNT) {

		lpListGenericItemType item;
		ULONG length, loop;
		LPUCHAR bytePtr;

		// Allocate a new list, double the length of the previous one...
		length = 1 << type->listCount;
		type->listSet[type->listCount] = Mem_AllocClear(type->itemWidth * length);
		bytePtr = (LPUCHAR) type->listSet[type->listCount];

		// Add all of these new items to the free list...
		for (loop=0 ; loop<length ; loop++) {
			item = (lpListGenericItemType) &bytePtr[type->itemWidth * loop];
			item->nextFree = type->freeList;
			type->freeList = item;

#ifdef _DEBUG
			item->ownerList = type;
#endif // _DEBUG

		}

		type->listCount++;

	} else {
		Error_Fatal(TRUE, "Run out of lists");
	}
}
