/* off_t lseek(int fd, off_t offset, int whence) */

  move.l     a2,-(a7)
  move.l     d2,-(a7)
  move.w     22(a7),-(a7)
  move.w     18(a7),-(a7)
  move.l     12(a7),-(a7)
  move.w     #0x0042,-(a7)
  trap       #1
  lea.l      10(a7),a7
  move.l     (a7)+,d2
  movea.l    (a7)+,a2
  rts
