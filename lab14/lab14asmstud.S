.syntax unified

//Put your .equ statements here for x, y, and z
.equ IVECTOR3_x, 0
.equ IVECTOR3_y, 4
.equ IVECTOR3_z, 8


.section .text
.global cross
.global dot

dot:
	//Write your functionality for dot product here
	//Remember the first parameter is the first vector
	//the second parameter is the second vector and you
	//return the dot product.

  push {r3, r4}

  // input, r0 = vector A, r1 = vector B
  // working, r2 = a_?, r3 = b_?, r4 = working sum

  // Mul a.x, b.x
  ldr r2, [r0, IVECTOR3_x] // get a_x
  ldr r3, [r1, IVECTOR3_x] // get b_x

  muls r2, r3, r2
  mov r4, r2
  
  // Mul a.y, b.y
  ldr r2, [r0, IVECTOR3_y] // get a_y
  ldr r3, [r1, IVECTOR3_y] // get b_y

  muls r2, r3, r2
  add r4, r2, r4

  // Mul a.z, b.z
  ldr r2, [r0, IVECTOR3_z] // get a_z
  ldr r3, [r1, IVECTOR3_z] // get b_z
  
  muls r2, r3, r2
  add r4, r2, r4

  // return dat final addition in r0
  mov r0, r4

  // get back r3+
  pop {r3, r4}
	
	//Replace bx lr with whatever you need
	bx	lr
	
cross:
	//Write your functionality for the cross product here
	//The first parameter is the RESULTANT vector
	//The second parameter is the first vector (left)
	//The third parameter is the second vector (right)
	//This is a void function, so nothing is returned

  push {r3, r4, r5, r6}

  // input r0 = vector C, r1 = vector A, r2 = vector B
  // no outputs
  // working set:
  /*
    r3 a.party first half mul
    r4 b.partz
    r5 a.partz second half mul
    r6 b.party sub of total
  */

  // load vals for calc
  ldr r3, [r1, IVECTOR3_y] // get a_y
  ldr r4, [r2, IVECTOR3_z] // get b_z
  ldr r5, [r1, IVECTOR3_z] // get a_z
  ldr r6, [r2, IVECTOR3_y] // get b_y
  // mul for
  mul r3, r4, r3
  mul r5, r6, r5
  sub r6, r3, r5 // r6 < r3-r5
  // store result into c_
  str r6, [r0, IVECTOR3_x]

  // load vals for calc
  ldr r3, [r1, IVECTOR3_z] // get
  ldr r4, [r2, IVECTOR3_x] // get
  ldr r5, [r1, IVECTOR3_x] // get
  ldr r6, [r2, IVECTOR3_z] // get
  // mul for
  mul r3, r4, r3
  mul r5, r6, r5
  sub r6, r3, r5 // r6 < r3-r5
  // store result into c_
  str r6, [r0, IVECTOR3_y]

  // load vals for calc
  ldr r3, [r1, IVECTOR3_x] // get
  ldr r4, [r2, IVECTOR3_y] // get
  ldr r5, [r1, IVECTOR3_y] // get
  ldr r6, [r2, IVECTOR3_x] // get
  // mul for
  mul r3, r4, r3
  mul r5, r6, r5
  sub r6, r3, r5 // r6 < r3-r5
  // store result into c_
  str r6, [r0, IVECTOR3_z]

  pop {r3, r4, r5, r6}
  
	//Replace bx lr with whatever you need
	bx	lr

