  move.l     a2,-(a7)
  move.l     d2,-(a7)
  move.l     12(a7),d0
  move.w     d0,-(a7)
  move.w     #0x003e,-(a7)
  trap       #1
  addq.l     #4,a7
  tst.l      d0
  sne        d0
  ext.w      d0
  ext.l      d0
  move.l     (a7)+,d2
  movea.l    (a7)+,a2
  rts
