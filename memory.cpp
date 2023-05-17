

//use mmap to grap memory as page size

void* allocateMemoryArena(size_t arenaSize)
{
    void* memory;
    uint32 pageSize = getpagesize();
    memory = mmap(NULL,4096,PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE,-1,0);
    
    return memory;
}

bool deallocateMemoryArena(void* memory, size_t arenaSize)
{

    if(munmap(memory,4096) > -1)
    {
        printf("memory deallocated successfully!\n");
        return true;
    }
    
    printf("memory did NOT deallocate properly!!\n");
    return false;
}
