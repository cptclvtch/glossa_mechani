target.array = AT_HEAD_OFFSET(argument_index*ARGUMENT_SIZE + 1);

target.index = AT_HEAD_OFFSET(argument_index*ARGUMENT_SIZE + 2);

if(target.array > MEMORY_MAX_INDEX)
{
  SET_ERROR(ARRAY_ACCESS_FAILED, head.array, head.index + ARGUMENT_SIZE*argument_index + 1)

  goto advance_head;
}

if(target.index > MAX_INDEX_AT(target.array))
{
  SET_ERROR(INDEX_ACCESS_FAILED, head.array, head.index + ARGUMENT_SIZE*argument_index + 2)

  goto advance_head;
}

SPECIFY_ADDRESS(arguments[argument_index], target.array, target.index)
