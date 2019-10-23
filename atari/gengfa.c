#define LIBFUNC(_fn, name, _nargs) \
FUNCTION zlib_ ## name() NL \
  $F% NL \
  LOCAL exec% NL \
  exec%=LONG{ADD(zlib_slb%,4)} NL \
  return C:exec%(L:LONG{zlib_slb%},L:_fn,L:_nargs) NL \
ENDFUNC

#define LIBFUNC2(_fn, name, _nargs) LIBFUNC(_fn, name, _nargs)
#define NOFUNC
#include "exports.h"


