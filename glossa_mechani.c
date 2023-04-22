#ifndef GLOSSA_MECHANI
#define GLOSSA_MECHANI

//"glossa mechani", also reffered to as "gamma mu", is Greek for "machine language"

#ifdef __cplusplus
extern "C" {
#endif

  #ifdef CLT
  #include "internal/testing/CLT.c"
  #endif

  #include "internal/libraries.c"
  #include "internal/macros.c"

  #include "internal/platform_specific_wrappers.c"

  #include "internal/definitions.c"
  #include "internal/functions.c"

  #ifdef CLT
  #include "internal/testing/testing_utilities.c"
  #endif


#ifdef __cplusplus
}
#endif
#endif
