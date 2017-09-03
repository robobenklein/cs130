.syntax unified

.section .text

//Compare two ints
.global compare
compare:
  cmp r0, r1

  it eq
  moveq r2, 0

  it gt
  movgt r2,1

  it lt
  movlt r2,-1

  mov r0, r2
  bx lr

// String Length > char pointer
.global strlength

strlength:
  mov r2, 0

  1:
  ldrb r1,[r0], 1
  cmp r1, 0

  it eq
  beq 1f
  add r2, 1
  b 1b

  1:
  mov r0, r2

  bx lr

//Minimum of three ints
.global minimum
minimum:
  push {r4, r5, r6, lr}
  mov r4, r0
  mov r5, r1
  mov r6, r2

  bl compare
  cmp r0, 0
  it gt
  movgt r4, r5

  mov r1, r6
  mov r0, r4

  bl compare
  cmp r0, 0
  it gt
  movgt r4, r6

  mov r0, r4
  pop {r4, r5, r6, pc}

// Maximum of three ints
.global maximum
maximum:
  push {r4, r5, r6, lr}
  mov r4, r0
  mov r5, r1
  mov r6, r2

  bl compare
  cmp r0, 0
  it lt
  movlt r4, r5

  mov r1, r6
  mov r0, r4

  bl compare
  cmp r0, 0
  it lt
  movlt r4, r6

  mov r0, r4
  pop {r4, r5, r6, pc}
 
