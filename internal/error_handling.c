#ifndef ERROR_HANDLING
  #define ERROR_HANDLING
  #define common_SET_ERROR(name, array, index)   MEMORY_AT_ADDRESS(error_storage[0]) = name;\
                                                    MEMORY_AT_ADDRESS(error_storage[1]) = array;\
                                                    MEMORY_AT_ADDRESS(error_storage[2]) = index;
  #ifdef CLT
  #define SET_ERROR(name, array, index) common_SET_ERROR(name, array, index) \
                                        PRINT("\n!!! %s !!!\n", error_messages[name])
  #else
  #define SET_ERROR(name, array, index) common_SET_ERROR(name, array, index)
  #endif
#endif

#ifdef VARIABLE_MODE
  #ifdef CLT
  const char* error_messages[] = {
    "ARRAY_RESIZE_FAILED",
    "MEMORY_RESIZE_FAILED",

    "ARRAY_ACCESS_FAILED",
    "INDEX_ACCESS_FAILED",
    "INVALID_INSTRUCTION"
  };
  #endif

ADDRESS   error_storage[3];
SPECIFY_ADDRESS(error_storage[0], 0,0)
SPECIFY_ADDRESS(error_storage[1], 0,0)
SPECIFY_ADDRESS(error_storage[2], 0,0)
#endif