.syntax unified

.section .data
by: .int 0

.section .text

// void setby(int)
.global setby
setby:
  // get mem addr
  ldr r1, =by
  // put r0 into mem addr
  str r0, [r1]

  bx lr

// int increment(int)
.global increment
increment:
  ldr r1, =by
  ldr r1, [r1]
  add r0, r1

  bx lr

.global decrement
decrement:
  ldr r1, =by
  ldr r1, [r1]
  mvn r1, r1
  add r1, 1
  add r0, r1

  bx lr

.global zeroit
zeroit:
  eor r0, r0

  bx lr

