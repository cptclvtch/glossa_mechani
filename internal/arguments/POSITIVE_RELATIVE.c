case POSITIVE_RELATIVE:
{
  target.index = AT_HEAD_OFFSET(argument_index*ARGUMENT_SIZE + 2);

  if(array_left < target.index)
  {
    SET_ERROR(INDEX_ACCESS_FAILED, head.array, head.index + 2 + ARGUMENT_SIZE*argument_index)
    
    goto advance_head;
  }

  arguments[argument_index].index += target.index;
  break;
}