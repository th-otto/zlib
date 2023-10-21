/* char *strerror(int errnum) */

#define SYS_NERR (sys_errlist_internal_end-sys_errlist_internal)/2

  move.l     4(a7),d1
  lea.l      sys_err_msgs(pc),a0
  move.l     a0,d0
  cmpi.l     #SYS_NERR,d1
  bhi.s      strerror1
  add.l      d1,d1
  lea.l      sys_errlist_internal(pc),a0
  movea.w    0(a0,d1.l),a0
  add.l      a0,d0
strerror1:
  rts

#define ERR(s, o) .asciz s
#define NONE
sys_err_msgs:
	.asciz "Unknown error"
#include "strerror.h"


#define ERR(s, o) .dc.w o
#define NONE .dc.w 0
sys_errlist_internal:
#include "strerror.h"
sys_errlist_internal_end:
