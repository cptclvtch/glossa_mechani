#define NAME LABEL(SET_RANDOM_SEED)
#define ARGUMENTS 1

#ifdef VARIABLE_MODE
DATA_TYPE seed = 0;
#endif

#include "../internal/instruction_pre_template.c"

#ifdef IMPLEMENTATION_MODE
seed = MEMORY_AT_ADDRESS(arguments[0]);
#endif

#define DESCRIPTION \
Sets the seed of the RNG as specified in the first argument.

#include "../internal/instruction_post_template.c"
