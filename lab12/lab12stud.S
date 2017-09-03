.syntax unified

.section .text
.global mystery1
mystery1:
//  movs r1, 1
  .short 0b0010000100000001
//  lsls  r0, r1
  .short 0b0100000010001000
//  bx   lr
  .short 0b0100011101110000

.global mystery2
mystery2:
//  .short  0b00101 000 11111111
  cmp r0, 255
//  .short  0b1011 1111 1100 1000
  it gt
//  .short  0b010000 0001 000 000
  eorgt r0, r0
//  .short  0b00 100 001 00000010
  movs r1, 2
//  .short  0b000 11 00 001 000 000
  adds r0, r0, r1
//  .short  0b010001 11 0 1110 000
  bx r14

.global mystery3
mystery3:
//  push  {r1, lr}
  .short 0b1011010100000001
//  movs  r1, 1
  .short 0b0010000100000001
//  lsrs   r0, r1
  .short 0b0100000011001000
//  pop   {r2, pc}
  .short 0b1011110100000010

