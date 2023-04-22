case NEGATIVE_RELATIVE:
{
  target.index = AT_HEAD_OFFSET(argument_index*ARGUMENT_SIZE + 2);

  if(target.index > head.index)
  {
    SET_ERROR(INDEX_ACCESS_FAILED, head.array, head.index + ARGUMENT_SIZE*argument_index + 2)

    goto advance_head;
  }

  arguments[argument_index].index -= target.index;
  break;
}