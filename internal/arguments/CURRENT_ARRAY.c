case CURRENT_ARRAY:
{
  target.array = head.array;
  target.index = AT_HEAD_OFFSET(argument_index*ARGUMENT_SIZE + 2);

  if(target.index > MAX_INDEX_AT(target.array))
  {
    SET_ERROR(INDEX_ACCESS_FAILED, head.array, head.index + ARGUMENT_SIZE*argument_index + 2)

    goto advance_head;
  }

  arguments[argument_index].index = target.index;
  break;
}