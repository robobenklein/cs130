///////////////////////////////////////////////
//
// DO NOT MODIFY ANYTHING IN THIS FILE!
//
///////////////////////////////////////////////
struct IVECTOR3
{
  int x, y, z;
};
extern "C"
{
  void cross(IVECTOR3 &result, IVECTOR3 &left, IVECTOR3 &right);
  int dot(IVECTOR3 &left, IVECTOR3 &right);
}

#define LED_1  13
#define LED_2  12
#define LED_3  11
#define LED_4  10
#define CLK_DIO 7
#define DATA_DIO 8
#define LATCH_DIO 4
#define BUTTON_1 A1
#define BUTTON_2 A2
#define BUTTON_3 A3

#define NUM_VECTORS 3
IVECTOR3 vectors[NUM_VECTORS];

bool BUTZ[] = {false, false, false};
const int SEGMENTS[] = {0b11110001, 0b11110010, 0b11110100, 0b11111000};
const int DIGITS[] = {/*0*/0b11000000,
                      /*1*/0b11111001,
                      /*2*/0b10100100,
                      /*3*/0b10110000,
                      /*4*/0b10011001,
                      /*5*/0b10010010,
                      /*6*/0b10000010,
                      /*7*/0b11111000,
                      /*8*/0b10000000,
                      /*9*/0b10011000,
                      /*a*/0b10001000,
                      /*b*/0b10000011,
                      /*c*/0b10100111,
                      /*d*/0b10100001,
                      /*e*/0b10000110,
                      /*f*/0b10001110,
                      /*-*/0b10111111,
};
int global_i = 0;

void LightLED(int led)
{
  digitalWrite(LED_1, HIGH);  
  digitalWrite(LED_2, HIGH);
  digitalWrite(LED_3, HIGH);
  digitalWrite(LED_4, HIGH);
  switch (led)
  {
    case 1:
      digitalWrite(LED_1, LOW);
      break;
    case 2:
      digitalWrite(LED_2, LOW);
      break;
    case 3:
      digitalWrite(LED_3, LOW);
      break;
    case 4:
      digitalWrite(LED_4, LOW);
      break;
  }
}

void LightLED(bool led1, bool led2, bool led3, bool led4=false)
{
  digitalWrite(LED_1, led1 ? LOW : HIGH);
  digitalWrite(LED_2, led2 ? LOW : HIGH);
  digitalWrite(LED_3, led3 ? LOW : HIGH);
  digitalWrite(LED_4, led4 ? LOW : HIGH);
}

void SetSegment(int segment, int digit)
{
  digitalWrite(LATCH_DIO, LOW);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, DIGITS[digit]);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENTS[segment]);
  digitalWrite(LATCH_DIO, HIGH);
}

void help()
{
  Serial.write("set <i> <x> <y> <z> - Set vector i to values x, y, z\n");
  Serial.write("get <i> - Get the values of vector i\n");
  Serial.write("dot <i> <j> - Get the dot product of vectors i and j\n");
  Serial.write("cross <i> <j> <k> - Get the cross product of vectors i x j and store into vector k\n");
}

void setup() {
  // put your setup code here, to run once:
  pinMode(CLK_DIO, OUTPUT);
  pinMode(DATA_DIO, OUTPUT);
  pinMode(LATCH_DIO, OUTPUT);

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);

  LightLED(0);

  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  pinMode(BUTTON_3, INPUT);
  
  Serial.begin(115200);
  help();
}

void loop() {
  char buf[1024];
  char buf2[256];
  char cmd[200];
  bool but;
  int i = 0;
  int x = 0;
  int y = 0;
  int z = 0;

  if (Serial.available() > 0) {
    String input = Serial.readString();
    sscanf(input.c_str(), "%s", cmd);

    if (!strcmp(cmd, "set")) {
      sscanf(input.c_str(), "%s %d %d %d %d", cmd, &i, &x, &y, &z);
      i %= NUM_VECTORS;
      vectors[i].x = x;
      vectors[i].y = y;
      vectors[i].z = z;
      sprintf(buf, "Set vector %d to {%d, %d, %d}\n", i, x, y, z);
      Serial.write(buf);
    }
    else if (!strcmp(cmd, "get")) {
      sscanf(input.c_str(), "%s %d", cmd, &i);
      i %= NUM_VECTORS;
      sprintf(buf, "Vector %d = {%d, %d, %d}\n", i, vectors[i].x, vectors[i].y, vectors[i].z);
      Serial.write(buf);
    }
    else if (!strcmp(cmd, "dot")) {
      sscanf(input.c_str(), "%s %d %d", cmd, &x, &y);
      x %= NUM_VECTORS;
      y %= NUM_VECTORS;
      sprintf(buf, "Dot product of vector %d {%d, %d, %d} and %d {%d, %d, %d} is %d\n",
              x, vectors[x].x, vectors[x].y, vectors[x].z,
              y, vectors[y].x, vectors[y].y, vectors[y].z,
              dot(vectors[x], vectors[y])
              );
      Serial.write(buf);
    }
    else if (!strcmp(cmd, "cross")) {
      sscanf(input.c_str(), "%s %d %d %d", cmd, &x, &y, &z);
      x %= NUM_VECTORS;
      y %= NUM_VECTORS;
      z %= NUM_VECTORS;
      sprintf(buf, "Cross product of vector %d {%d, %d, %d} and %d {%d, %d, %d}",
          x, vectors[x].x, vectors[x].y, vectors[x].z,
          y, vectors[y].x, vectors[y].y, vectors[y].z
          );
      cross(vectors[z], vectors[x], vectors[y]);
      sprintf(buf, "%s is %d {%d, %d, %d}\n", buf, 
          z, vectors[z].x, vectors[z].y, vectors[z].z
      );
      Serial.write(buf);
    }
    else {
      sprintf(buf, "Unknown command '%s'\n", cmd);
      Serial.write(buf);
      help();
      but = false;
    }
  }
  but = digitalRead(BUTTON_1) ? false : true;
  if (BUTZ[0] != but) {
    if (but == true) {
      global_i = 0;
    }
    BUTZ[0] = but;
  }
  
  but = digitalRead(BUTTON_2) ? false : true;
  if (BUTZ[1] != but) {
    if (but == true) {
      global_i = 1;
    }
    BUTZ[1] = but;
  }
  
  but = digitalRead(BUTTON_3) ? false : true;
  if (BUTZ[2] != but) {
    if (but == true) {
      global_i = 2;
    }
    BUTZ[2] = but;
  }
  SetSegment(0, global_i % NUM_VECTORS);
  SetSegment(1, abs(vectors[global_i].x) % 16);
  SetSegment(2, abs(vectors[global_i].y) % 16);
  SetSegment(3, abs(vectors[global_i].z) % 16);

  LightLED(false, vectors[global_i].x < 0, vectors[global_i].y < 0, vectors[global_i].z < 0);
    
}
