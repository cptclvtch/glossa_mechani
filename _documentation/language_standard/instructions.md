<details>
<summary>
Program Flow</summary>

Name | Number of arguments | Description
---|---|---
EMPTY | 0 | Does nothing.
DECAPITATE | 0 | Kills the current head.
IF | 1 | Places the head on the next instruction if the argument is greater than 0, or places the head on the instruction after that if the argument is 0.
GO_TO | 2 | Places the head at the array specified by the first argument and the index specified by the second argument.
GO_TO_INDEX | 1 | Places the head on the index specified in the first argument.
SKIP | 2 | Tells the head to move backwards or forwards from the current position. First argument determines distance, second argument determines direction( 0 for forwards, 1 and greater for backwards). An error will be emitted if the first argument has a value of 0.
SET_HEAD | 0 | Reserved for future versions.
GET_HEAD | 2 | Populates the two arguments with the current location of the head (array and index respectively).
SET_ERROR_TRAP | 3 | Sets the locations for capturing errors, as specified by the first three arguments. The error information is type, array and index location respectively. If the error trap itself is faulty, it will overwrite the error info onto itself.
GET_PLATFORM | 3 | Places platform codes into the provided arguments.Each code represents a new branch in the following encoding tree:0 - desktop 0 - Windows 0 - 10 1 - 11 1 - Linux 2 - MacOS1 - mobile 0 - Android 1 - iOS2 - console 0 - XBox 0 - One 1 - Series X 1 - PS 0 - 4 1 - 5 2 - Nintendo 0 - Switch4 - VR5 - other
GET_INSTRUCTION_INFO | 3 | Places the information according to the inquiry of the first two arguments (instruction code and information type respectively) into the third argument. The information types are: 0 or greater for the number of arguments.
</details>
<details>
<summary>
Memory Management</summary>

Name | Number of arguments | Description
---|---|---
RESIZE_MEMORY_TO | 1 | Resizes the interpreter memory to the size specified in the first argument. Thus, this instruction can additionally trigger a memory limit trap.
GET_MEMORY_MAX_INDEX | 1 | Places the size of the interpreter memory into the first argument.
RESIZE_ARRAY_TO | 2 | Resizes the array specified in the first argument to the size specified in the second argument. Thus, this instruction can additionally trigger a memory limit trap.
GET_ARRAY_MAX_INDEX | 2 | Places the size of the array specified by the second argument into the first argument.
DELETE_ARRAY_RANGE | 2 | Deletes the range of arrays specified by the first two arguments. The range cannot end with the last array. If the head is contained in the array range, it will be placed immediately after it, with index 0.
DELETE_INDEX_RANGE | 2 | Deletes the range of indices specified by the first two arguments. The range cannot end with the last index. The range needs to belong to a single array, but will work even if the second argument is from a different array. If the head is contained in the index range, it will be placed immediately after it.
COPY_ARRAY_RANGE | 3 | Copies array range specified in the first two arguments, to the location specified by the third argument. Thus, this instruction can additionally trigger a memory limit trap.
COPY_INDEX_RANGE | 3 | Copies a range of data, as specified by the first two arguments, to the location specified by the third argument. The range needs to belong to a single array, but will work even if the second argument is from a different array.
OVERWRITE | 2 | Replaces the value of the first argument with the value of the second argument.
OVERWRITE_INDEX_RANGE | 3 | Uses the range specified with the first two arguments to overwrite data at the location specified in the third argument. If the destination array is too short, the range becomes truncated to fit. The range needs to belong to a single array, but will work even if the second argument is from a different array.
MOVE_ARRAY_RANGE | 3 | Moves the array range specified in the first and second arguments to the position specified in the third argument.
MOVE_INDEX_RANGE | 3 | Moves a range of data, as specified by the first two arguments, to the location specified by the third argument. The range needs to belong to a single array, but will work even if the second argument is from a different array. The destination array will be resized to fit. Thus, this instruction can additionally emmit an error.
SPLIT_ARRAY | 1 | Splits up an array at the specified location. The new array starts with the index specified. Splitting at 0 does nothing.
CONJOIN_ARRAY_RANGE | 2 | Turns a range of arrays into one array.
</details>
<details>
<summary>
Algebra</summary>

Name | Number of arguments | Description
---|---|---
ADD | 3 | Adds the second argument to the first argument. The third argument is set to 1 if the instruction overflows, and 0 if it doesnt.
SUBTRACT | 3 | Subtracts the second argument out of the first argument. The third argument is set to 1 if the instruction underflows, and 0 if it doesnt.
MULTIPLY | 3 | Multiplies the first argument by the second argument. The third argument is set to 1 if the instruction overflows, and 0 if it doesnt.
DIVIDE | 4 | Divides the first argument by the second argument. The remainder goes into the third argument. A second argument of 0 outputs a remainder thats the same as the first argument. The fourth argument is set to 1 if divided by zero, and 0 if it doesnt.
BITWISE_AND | 2 | Performs a binary "and" on the first argument, using the second one.
BITWISE_OR | 2 | Performs a binary "or" on the first argument, using the second one.
BITWISE_XOR | 2 | Performs a binary "xor" on the second argument using the first argument.
BITWISE_NOT | 1 | Performs a binary "not" on the first argument.
LOGICAL_SHIFT | 3 | Performs a logical shift on the first argument by the amount specified in the second argument, in the direction specified in the third argument (0 for left and >0 for right).
AND | 3 | Places the result of a logical "and" of the first and second argument into the third argument.
OR | 3 | Places the result of a logical "or" of the first and second argument into the third argument.
NOT | 2 | Places the result of a logical "not" of the first into the second argument.
EQUALS | 3 | Places a '1' into the third argument, if the first and second arguments are equal. Places a '0' otherwise.
GREATER_THAN | 3 | Places a '1' into the third argument if the first argument is greater than the second argument. Places a '0' otherwise.
LESS_THAN | 3 | Places a '1' into the third argument if the first argument is less than the second argument. Places a '0' otherwise.
SET_RANDOM_SEED | 1 | Sets the seed of the RNG as specified in the first argument.
GET_RANDOM | 1 | Places a pseudo-random (LCG) value in the first argument.
</details>
