//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
// Memory Manager File For <GODS PSX>
//
// Started:	10-07-98
// Coding:	Glenn Benson
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹

// Include all Header Files

//ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
#include	"libgods.h"
//‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹



extern u_long	__heapbase;						// LibSN memory vars.
extern u_long	__heapsize;
extern u_long	_ramsize;
extern u_long	_stacksize;

#ifdef MEMORY_TRACKING

WATCH	watch;


/*

	Initialise watch list and file name directory

*/
void memory_watch_init(void)
{
	int		n;

	printf("memory watch init\n");
	for (n=0; n<MAX_WATCHES; n++)
	{
		watch.list[n].malloc_ptr=NULL;
		watch.list[n].size=0;
	}
	watch.total=0;
	watch.blocks=0;
	watch.totalWatched=0;
	watch.blocksWatched=0;
	watch.active=FALSE;
}



void	memory_watch_on(void)
{
	printf("memory watch on\n");
	watch.active=TRUE;
}

void	memory_watch_off(void)
{
	watch.active=FALSE;
}




/* malloc block and record details */
void* malloc3_watch(unsigned int size, char *file, int line, char *fname)
{
	void		*temp=NULL;
	int		n;

	temp=malloc3(size);

	if (temp!=NULL)
	{

		/* add stats to non watch counters */

		watch.blocks++;
		watch.total+=size;

		if (watch.active)
		{
			for (n=0; n<MAX_WATCHES; n++)
			{
			 	if (watch.list[n].malloc_ptr==NULL)
				{
					watch.list[n].malloc_ptr=temp;
					watch.list[n].size=size;
					watch.blocksWatched++;
					watch.totalWatched+=size;
	
					/* add name and line number info */
	
					watch.list[n].file_index=file;
					watch.list[n].line_number=line;
					if(fname)
					{
						strcpy(watch.list[n].file_name,fname);
					}
					else
					{
						strcpy(watch.list[n].file_name,"");
					}
	
					return	(temp);
				}
			}
			printf("WARNING - malloc could not be added to watch list\n");
		}
	}
	else
		printf("ERROR! - malloc failed file=%s,line:%d,size:%d\n",file,line,size);

	return	(temp);
}




void free3_watch(void *ptr)
{
	int		n;

	for (n=0; n<MAX_WATCHES; n++)
	{
	 	if (watch.list[n].malloc_ptr==ptr)
		{			
			watch.list[n].malloc_ptr=NULL;		/* return to pool */
			free3(ptr);
			watch.blocksWatched--;
			watch.totalWatched-=watch.list[n].size;
			return;
		}
	}
//	printf("WARNING - block to be freed not in watch list (Location %x)\n",ptr);
	free3(ptr);
}


void mem_show_total(void)
{


	char	string[80];
	int	n,y=16,len,count=0;

	printf("Showing total memory allocation\n");
	for (n=0; n<MAX_WATCHES; n++)
	{

		if (watch.list[n].malloc_ptr)
		{
			printf("Memory index %d :- File %s, line %d, address %x, size %d",count,watch.list[n].file_index,watch.list[n].line_number,watch.list[n].malloc_ptr,watch.list[n].size);
			if(strlen(watch.list[n].file_name))
			{
				printf(",file name %s",watch.list[n].file_name);
			}
			printf("\n");
			count++;
		}
	}

	printf(string,"total=%d, blocks=%d",watch.total,watch.blocks);

}

#else

//void *malloc_mem(unsigned int _size,char *file,unsigned int line)
void *malloc_mem(Uint32 _size,char *file,unsigned int line)
{
	void *ret = NULL;

	ret = malloc3(_size);
//	printf("Malloc ADDR %x in file %s, line %d, size %d\n", ret, file, line, _size);
	if(!ret)
	{
		printf("Malloc failed in file %s, line %d, size %d\n", file, line, _size);
	}
	return ret;
}

void free_mem(void *mem)
{
//	printf("Free ADDR %x\n", mem);
	free3(mem);
}

#endif


/* SteveD - adjusted size for bank 0 on the basis of saving 120k from the primitive buffers */
/* adjusted size again to 230*1024!!! -ADRIAN- */
#define BANK0_SIZE 530*1024					/* was 530*1024 */

void Mem_Reset(unsigned int bank)
{
	InitHeap3(__heapbase,__heapsize);
	return;
	/*
	void *base;
	unsigned int size;

	base = (void *)__heapbase;
	printf("%x %d\n",__heapbase,__heapsize);
	size = BANK0_SIZE;

	if(bank == 1)
	{
		base += BANK0_SIZE;
		size = __heapsize - BANK0_SIZE;
	}

	// temp
	size = __heapsize;


//	printf("Current heap start %x, length %x (%d)\n",base,size,size);
//	printf("Heap start %x, length %x (%d)\n",__heapbase,__heapsize,__heapsize);
//	printf("Ram size %x, stack size %x \n",_ramsize,_stacksize);

	InitHeap3(base,size);
	*/
}
