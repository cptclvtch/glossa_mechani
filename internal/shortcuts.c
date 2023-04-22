//implementation shortcuts
#define MEMORY_AT(x,y)              interpreter->memory.data[x].data[y]
#define MEMORY_AT_ADDRESS(x)        MEMORY_AT(x.array, x.index)
#define SPECIFY_ADDRESS(var,x,y)    var.array = x; var.index = y;
#define MEMORY_DATA                 interpreter->memory.data
#define MEMORY_MAX_INDEX            interpreter->memory.max_index
#define ARRAY_AT(x)                 interpreter->memory.data[x]
#define MAX_INDEX_AT(x)             interpreter->memory.data[x].max_index

#define INSTRUCTION_INFO_AT(name, item) interpreter->instruction_info.data[name].data[item]

#define AT_HEAD_OFFSET(x)           MEMORY_AT(head.array, head.index + x)
#define ADVANCE_HEAD                head.index += 1 + INSTRUCTION_INFO_AT(instruction, NUMBER_OF_ARGUMENTS)*ARGUMENT_SIZE;
