#ifndef SWAP_CORE
#define SWAP_CORE SWAP_CORE_is_missing_implementation
#endif

if(move_to_index == move_first_index) return;

//check and adjust for direction
if(move_to_index < move_first_index)
{
  DATA_TYPE new_move_to = 1 + move_last_index - move_first_index;
  move_last_index = move_first_index - 1;
  move_first_index = move_to_index;
  move_to_index += new_move_to;
}

//simplify problem by determining bounds
DATA_TYPE range_width = move_last_index - move_first_index;
DATA_TYPE range_length = range_width + 1;
DATA_TYPE max_target_index = MAX_INDEX - range_length + 1;
if(move_to_index > max_target_index) move_to_index = max_target_index;

#define start move_first_index
#define end   move_to_index + range_width

#define SWAP(from,to,cache) cache = from; from = to; to = cache;
DATA_TYPE swap_cache;

DATA_TYPE items_left_to_move = 1 + end - start;
DATA_TYPE working_length = items_left_to_move;
DATA_TYPE cache_index = 0;
DATA_TYPE to_index = 0;

//perform recursive swap algorithm
while(items_left_to_move > 0)
{
  to_index += working_length*(to_index < range_length) - range_length;

  if(to_index == cache_index)
  {
    cache_index++;
    to_index++;
    items_left_to_move--;
    continue;
  }

  SWAP_CORE

  items_left_to_move--;
}

#undef SWAP
#undef SWAP_ARRAYS
#undef SWAP_CACHE
#undef MAX_INDEX
#undef start
#undef end
/*
 1  2 | 3  4  5  6  7  8        0  1  2 | 3  4  5        0  1  2  3  4 | 5

(1) 2 | 3  4  5  6 [7] 8       (0) 1  2 |[3] 4  5       (0)[1] 2  3  4 | 5
(7) 2 | 3  4 [5] 6  1  8        3 (1) 2 | 0 [4] 5       (1) 0 [2] 3  4 | 5
(5) 2 |[3] 4  7  6  1  8        3  4 (2)| 0  1 [5]      (2) 0  1 [3] 4 | 5
 3 (2)| 5  4  7  6  1 [8]                               (3) 0  1  2 [4]| 5
 3 (8)| 5  4  7 [6] 1  2        3  4  5 | 0  1  2       (4) 0  1  2  3 |[5]
 3 (6)| 5 [4] 7  8  1  2
                                                         5  0  1  2  3 | 4
 3  4 | 5  6  7  8  1  2
*/
