#define PRIMARY_PLATFORM 5
#define SECONDARY_PLATFORM 0
#define TERTIARY_PLATFORM 0

//MEMORY
#define ALLOCATE_MEMORY(length, type) (type *) mmap(NULL, (unsigned long long)(length + 1) * sizeof(type), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS,-1,0);
#define DEALLOCATE_MEMORY(address,length) (unsigned int)munmap(address, (unsigned long long)(length + 1));

#define MEMORY_ALLOCATION_FAILED MAP_FAILED //(void*)-1
#define DEALLOCATION_SUCCESSFUL 0

#ifdef _WIN32
#undef PRIMARY_PLATFORM
#define PRIMARY_PLATFORM 0

#undef ALLOCATE_MEMORY
#define ALLOCATE_MEMORY(length, type) (type *) VirtualAlloc(NULL, (unsigned long long)(length + 1) * sizeof(type), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#undef DEALLOCATE_MEMORY
#define DEALLOCATE_MEMORY(address,length) (unsigned int)VirtualFree(address, 0, MEM_RELEASE);

#undef MEMORY_ALLOCATION_FAILED
#define MEMORY_ALLOCATION_FAILED NULL //0
#undef DEALLOCATION_SUCCESSFUL
#define DEALLOCATION_SUCCESSFUL 1
#endif

#ifdef __unix__
#undef PRIMARY_PLATFORM
#define PRIMARY_PLATFORM 0
#undef SECONDARY_PLATFORM
#define SECONDARY_PLATFORM 1
#endif

#ifdef __APPLE__
#undef PRIMARY_PLATFORM
#define PRIMARY_PLATFORM 0
#undef SECONDARY_PLATFORM
#define SECONDARY_PLATFORM 2
#endif

#ifdef TARGET_OS_IPHONE
#undef PRIMARY_PLATFORM
#define PRIMARY_PLATFORM 1
#undef SECONDARY_PLATFORM
#define SECONDARY_PLATFORM 1
#endif

#ifdef __ANDROID__
#undef PRIMARY_PLATFORM
#define PRIMARY_PLATFORM 1
#undef SECONDARY_PLATFORM
#define SECONDARY_PLATFORM 0
#endif

#ifdef XBOXONE
#undef PRIMARY_PLATFORM
#define PRIMARY_PLATFORM 2
#undef SECONDARY_PLATFORM
#define SECONDARY_PLATFORM 0
#endif

#define MEMORY_ALLOCATION_SUCCESSFUL !(MEMORY_ALLOCATION_FAILED)