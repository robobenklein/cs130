//Lab 5
//COSC 130

const int CLK_DIO = 7;
const int DATA_DIO = 8;
const int LATCH_DIO = 4;

int counter = 0;

//////////////////////////////////////////////
//
// Finish the arrays below
//
///////////////////////////////////////////////

//SEGMENTS contains the segment selector 0b1111XYZW
const int SEGMENTS[] = {
  0b11110001, /* finish here */
  0b11110010,
  0b11110100,
  0b11111000
};

//DIGITS contains the actual digits where DIGITS[0]
//will be the bit string to draw a 0 on the 7-segment display
const int DIGITS[] = {
  0b11000000, // Number Zero
  0b11111001, // One
  0b10100100, // Two
  0b10110000, // Three
  0b10011001, // Four
  0b10010010, // Five
  0b10000010, // Six
  0b11111000, // Seven
  0b10000000, // 8
  0b10011000 // Nine
};

//////////////////////////////////////////
//
// Modify SetupPins below
//
/////////////////////////////////////////////
void SetupPins()
{
  //Make sure that we can write to CLK_DIO, DATA_DIO, and LATCH_DIO
  pinMode(CLK_DIO, OUTPUT);
  pinMode(DATA_DIO, OUTPUT);
  pinMode(LATCH_DIO, OUTPUT);

}

///////////////////////////////////////////
//
// Modify SetSegment below
//
/////////////////////////////////////////////
void SetSegment(int segment, int digit)
{
  //Set <segment>'s value to <digit>

  //Steps to write a value
  //1. Open the latch (LATCH_DIO) by setting it's value LOW using digitalWrite()
  digitalWrite(LATCH_DIO, LOW);
  
  //2. Write the digit to the shift register using shiftOut()
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, DIGITS[digit]);
  
  //3. Write the segment to the shift register using shiftOut()
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENTS[segment]);
  
  //4. Close the latch (LATCH_DIO) by setting it's value HIGH using digitalWrite()
  digitalWrite(LATCH_DIO, HIGH);
 
}



////////////////////////////////////////////
//
// Do NOT modify any functions below
//
// Too late! I did so anyways. 
//
////////////////////////////////////////////
const int segment_limit = sizeof(SEGMENTS) / sizeof(int);
const int digit_limit = sizeof(DIGITS) / sizeof(int);

int values[] = {0, 0, 0, 0};

void setup() {
  SetupPins();
  Serial.begin(115200);
  Serial.print("Enter value: ");
}

void loop() 
{
  
  /*
  if (Serial && Serial.available() > 0) {
    String input = Serial.readString();
    int value = input.toInt();
    char buf[10];

    if (value > 9999 || value < 0) {
      value = 1234;
    }
    values[0] = value / 1000;
    value -= values[0] * 1000;
    values[1] = value / 100;
    value -= values[1] * 100;
    values[2] = value / 10;
    value -= values[2] * 10;
    values[3] = value;
    
    sprintf(buf, "%d %d %d %d", values[0], values[1], values[2], values[3]);
 
    Serial.print("\nDisplay set to ");
    Serial.print(buf);
    Serial.print("\nEnter value: ");
  }
  */

  int value = counter;

  if (counter >= 9999) {
    counter = 0;
  }

  values[0] = value / 1000;
  value -= values[0] * 1000;
  values[1] = value / 100;
  value -= values[1] * 100;
  values[2] = value / 10;
  value -= values[2] * 10;
  values[3] = value;
  
  
  for (int i = 0;i < 4;i++) {
    if (i >= segment_limit) {
      break;
    }
    if (values[i] < digit_limit) {
      SetSegment(i, values[i]);
    }
  }

  counter++;
  delay(10);

}
