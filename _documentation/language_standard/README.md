
# Memory model
---------------------------------
The program memory is a shared space where both instructions and data reside. This allows for runtime code modification and encourages new programming techniques.

The smallest unit of data is an unsigned 32 bit integer.

A dynamic array can hold these units of data, the valid index range for them being [0 ... 0XFFFFFFFF]

Finally, the dynamic program memory can hold these arrays, the valid index range for them being [0 ... 0xFFFFFFFB].

A moving "head" drives program execution.

# Head Movement
---------------------------------
The head starts at [0,0].

If a valid instruction is found at the head's location, that instruction gets executed.
Otherwise, an error is emitted to be trapped and the head moves forward once.

When the head reaches the end of an array, it attempts to continue running to the next array.
If the head is contained in a range of memory being moved, it will follow that movement so as to follow its intent. As in, the head will respect the continuity of the program space.

Instructions can be as small as 1 value (their instruction code), or contain multiple values depending on the input required by the instruction.

Most instructions take a set of arguments as input.
These arguments are tuples where their first element is a type that decides the interpretation of the second element.

# Argument Types
---------------------------------
There are 5 different argument types:

- IMMEDIATE [0XFFFFFFFF]
Uses the data immediately specified in the argument value.

- CURRENT_ARRAY [0XFFFFFFFE]
Refers to data located in the current array, at the index specified in the argument value.

- POSITIVE_RELATIVE [0xFFFFFFFD]
Refers to data located forwards in the array, with an offset specified by the argument value.

- NEGATIVE_RELATIVE [0xFFFFFFFC]
Refers to data located backwards in the array, with an offset specified by the argument value.

- DIRECT [0 ... 0xFFFFFFFB]
This value represents an array index.
The argument value accompanying it is the data index.

These arguments need to point to a valid memory address. If not, program execution continues while an error is emitted to be trapped by error traps.

# Error Guide
---------------------------------
When an error occurs, its information (type, array and index) are stored in the locations specified by SET_ERROR_TRAP.
The starting error trap location is [0,0] for all 3 error data. It is recommended that you set your own error trap location.

Here are the error types:
- ARRAY_RESIZE_FAILED   - Gets triggered when an array can't be resized. This can include some memory management instructions.
- MEMORY_RESIZE_FAILED  - Gets triggered when the memory can't be resized. This can include some memory management instructions.

- ARRAY_ACCESS_FAILED   - Gets triggered when referencing an array that is out of memory bounds.
- INDEX_ACCESS_FAILED   - Gets triggered when referencing an index that is out of array bounds.
- INVALID_INSTRUCTION   - Gets triggered when trying to interpret an invalid instruction code.

# NOTES
---------------------------------
Glossa Mechani was designed to be:
 - used with graph editors
 - programmer friendly
