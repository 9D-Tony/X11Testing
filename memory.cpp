

//use mmap to grap memory as page size

#define Kilobytes(value) ((value) * 1024)
#define Megabytes(value) (Kilobytes(value) * 1024)
#define Gigabytes(value) (Megabytes(value) * 1024)

struct MemArena
{
    // can't be over 4GB in size for the moment
    uint32 size;
    uint32 used;
    void* base;
};

void allocateMemoryArena(MemArena* arena)
{
    //if arena size is more than 4GB then stop.
    assert(arena->size < UINT32_MAX);
    
    uint32 pageSize = getpagesize();
    arena->base = mmap(NULL,arena->size,PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE,-1,0);    
    
     printf("memory allocated successfully at: %#010x \n", arena->base);     
}

bool deallocateMemoryArena(MemArena* arena)
{
    if(munmap(arena->base,arena->size) > -1)
    {
        printf("memory deallocated successfully at: %#010x \n", arena->base);
        
        return true;
    }
    
    printf("memory did NOT deallocate properly!!\n");
    return false;
}



