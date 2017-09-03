////////////////////////////////////////////////////////
//
// Do not modify anything in this file.
//
////////////////////////////////////////////////////////

extern "C"
{
  int mystery1(int);
  int mystery2(int);
  int mystery3(int);
}


#define BUTTON_1 A1
#define BUTTON_2 A2
#define BUTTON_3 A3

#define CLK_DIO 7
#define DATA_DIO 8
#define LATCH_DIO 4

const int SEGMENTS[] = {0b11110001, 0b11110010, 0b11110100, 0b11111000};
const int DIGITS[] = {0b11000000, 0b11111001, 0b10100100, 0b10110000, 0b10011001, 0b10010010, 0b10000010, 0b11111000, 0b10000000, 0b10011000,
                     /*a*/0b10001000,
                     /*b*/0b10000011,
                     /*c*/0b10100111,
                     /*d*/0b10100001,
                     /*e*/0b10000110,
                     /*f*/0b10001110,
                     /*-*/0b10111111,
};
bool BUTZ[] = {false, false, false};
int global_i = 0;
char buf[1024];

void SetSegment(int segment, int digit)
{
  digitalWrite(LATCH_DIO, LOW);

  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, DIGITS[digit]);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENTS[segment]);
  
  digitalWrite(LATCH_DIO, HIGH);
  
}

void setup() {
  // put your setup code here, to run once:
  pinMode(CLK_DIO, OUTPUT);
  pinMode(DATA_DIO, OUTPUT);
  pinMode(LATCH_DIO, OUTPUT);

  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  pinMode(BUTTON_3, INPUT);

  Serial.begin(115200);
}

void loop() {
  bool but;
  String command, sval;
  int value;
  int values[4];
  int i;

  but = digitalRead(BUTTON_1) ? false : true;
  if (BUTZ[0] != but) {
    if (but == true) {
      global_i = mystery1(global_i);
    }
    BUTZ[0] = but;
  }
  
  but = digitalRead(BUTTON_2) ? false : true;
  if (BUTZ[1] != but) {
    if (but == true) {
      global_i = mystery2(global_i);
    }
    BUTZ[1] = but;
  }
  
  but = digitalRead(BUTTON_3) ? false : true;
  if (BUTZ[2] != but) {
    if (but == true) {
      global_i = mystery3(global_i);
    }
    BUTZ[2] = but;
  }

  value = global_i & 0xffff;
  i = value / 1000;
  SetSegment(0, (i % 10) & 0xf);
  value -= i * 1000;
  i = value / 100;
  SetSegment(1, (i % 10) & 0xf);
  value -= i * 100;
  i = value / 10;
  SetSegment(2, (i % 10) & 0xf);
  value -= i * 10;
  i = value;
  SetSegment(3, (i % 10) & 0xf);
}
