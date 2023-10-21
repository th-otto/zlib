/* ssize_t read(int fd, void *buf, size_t nbytes) */

  move.l     a2,-(a7)
  move.l     d2,-(a7)
  move.l     16(a7),-(a7)
  move.l     24(a7),-(a7)
  move.w     22(a7),-(a7)
  move.w     #0x003f,-(a7)
  trap       #1
  lea.l      12(a7),a7
  tst.l      d0
  bge.s      read1
  moveq.l    #-1,d0
read1:
  move.l     (a7)+,d2
  movea.l    (a7)+,a2
  rts
