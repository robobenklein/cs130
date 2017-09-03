.syntax unified

//EQU directives go here
//struct Person
//  char name[40]; starts at 0, goes 40 * 1byte char
.equ PERSON_NAME, 0
//  int birthday; ints are all 4 bytes
.equ PERSON_BIRTHDAY, 40
//  int birthmonth;
.equ PERSON_BIRTHMONTH, 44
//  int birthyear;
.equ PERSON_BIRTHYEAR, 48
//  int height;
.equ PERSON_HEIGHT, 52
//  int weight;
.equ PERSON_WEIGHT, 56

.section .text
.global CopyString
CopyString:
    //Put your code for CopyString here
    //void CopyString(char *dest, const char *src);

    // working set:
    // r0: destination address
    // r1: source address
    // r2: char being moved
    // r3: position down string
    mov r3, 0

  copychar:
    // read char from dat memory
    ldrb r2, [r1, r3]
    // put dat char
    strb r2, [r0, r3]
    // is this a zero/null?
    cmp r2, 0
    it eq // if zero, then
    beq done // jump to done
    // else:
    add r3, 1
    b copychar
  done:
    // ok done...

    //Change bx lr to whatever you need below
    bx  lr

.global NewPerson
NewPerson:
    //Put your code for NewPerson here
    // void NewPerson
      //r0 const char *name,
      //r1 int bday,
      //r2 int bmonth,
      //r3 int byear,
      //s1 int height,
      //s2 int weight

    push {r4, lr}

    // start the objects stack
    // yeah IK there is an add right below,
    // this makes it more readable
    sub sp, 64
    // 64 so that we have 4 non-collision bytes before hitting
    // our object memory area

    // move the things we have and know
    str r1, [sp, PERSON_BIRTHDAY]
    str r2, [sp, PERSON_BIRTHMONTH]
    str r3, [sp, PERSON_BIRTHYEAR]

    // string copy for name
    // source is our first argument
    mov r1, r0
    // destination is our stack pointer
    mov r0, sp
    //void CopyString(char *dest, const char *src);
    bl CopyString

    // those others are deep in our og stack
    ldr r1, [sp, 72] // 64 + 4*2 that we pushed earlier
    str r1, [sp, PERSON_HEIGHT]
    ldr r2, [sp, 76]
    str r2, [sp, PERSON_WEIGHT]

    mov r0, sp
    bl AddToList

    // get our og stack back
    add sp, 64

    // took a few hours with friends to find that popping PC fixed it...
    pop {r4, pc}

    //Change bx lr to whatever you need below
    bx  lr

