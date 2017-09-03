///////////////////////////////////////////////
//
// DO NOT MODIFY ANYTHING IN THIS FILE!
//
///////////////////////////////////////////////
struct Person
{
  char name[40];
  int birthday;
  int birthmonth;
  int birthyear;
  int height;
  int weight;
};

struct List
{
  Person p;
  List *next;
} *head = NULL;
int people = 0;

extern "C"
{
  void CopyString(char *dest, const char *src);
  void NewPerson(const char *name, int bday, int bmonth, int byear, int height, int weight);
  void AddToList(Person &p)
  {
    List *l = new List;
    l->p = p;
    l->next = head;
    head = l;

    people++;
  }
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
  Serial.write("Commands:\n");
  Serial.write("   new <name> <birth_day> <birth_month> <birth_year> <height> <weight> - Add a new person\n");
  Serial.write("   list - List all of the people currently added\n");
  
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
  char cmd[200];
  char buf[1024];
  Person p;
  int i;
  int k;

  if (Serial.available() > 0) {
    String input = Serial.readString();
    sscanf(input.c_str(), "%s", cmd);

    if (!strcmp(cmd, "new")) {
      sscanf(input.c_str(), "%s %s %d %d %d %d %d", cmd, p.name, &p.birthday, &p.birthmonth, &p.birthyear, &p.height, &p.weight);
      NewPerson(p.name, p.birthday, p.birthmonth, p.birthyear, p.height, p.weight);
      sprintf(buf, "Added '%s' to the list.\n", p.name);
      Serial.write(buf);
    }
    else if (!strcmp(cmd, "list")) {
      List *l;
      for (l = head;l != NULL;l = l->next) {
        sprintf(buf, "Person '%s':\n", l->p.name);
        Serial.write(buf);
        sprintf(buf, "   Birthday: %d/%d/%d\n", l->p.birthday, l->p.birthmonth, l->p.birthyear);
        Serial.write(buf);
        sprintf(buf, "   Height: %d, Weight: %d\n", l->p.height, l->p.weight);
        Serial.write(buf);
      }
    }
    else {
      sprintf(buf, "Unknown command '%s'\n", cmd);
      Serial.write(buf);
      help();
    }
  }
  k = people % 10000;
  i = k / 1000;
  k -= i * 1000;
  SetSegment(0, i);
  i = k / 100;
  k -= i * 100;
  SetSegment(1, i);
  i = k / 10;
  k -= i * 10;
  SetSegment(2, i);
  SetSegment(3, k);
  
}
