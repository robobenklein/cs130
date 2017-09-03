////////////////////////////////////////////////////////
//
// Do not modify anything in this file. All of your code
// will go into lab11asm.S
//
////////////////////////////////////////////////////////
extern "C"
{
  int compare(int, int);
  int minimum(int, int, int);
  int maximum(int, int, int);
  int strlength(const char *);
}

void help()
{
  Serial.write("compare x y   - Compares X and Y and returns the result\n");
  Serial.write("minimum x y z - Gives you the minimum of x, y, and z\n");
  Serial.write("maximum x y z - Gives you the maximum of x, y, and z\n");
  Serial.write("strlength x   - Gives the length of string x\n");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  help();
}

void loop() {
  char buf[1024];
  char buf2[1024];
  int x, y, z;
  int i;
  String command;
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    String s = Serial.readString();
    sscanf(s.c_str(), "%s", buf);
    String k = buf;
    if (k == "compare") {
      sscanf(s.c_str(), "%s %d %d", buf, &x, &y);
      sprintf(buf, "Compared %d and %d, got %d\n", x, y, compare(x, y));
      Serial.write(buf);
    }
    else if (k == "minimum") {
      sscanf(s.c_str(), "%s %d %d %d", buf, &x, &y, &z);
      sprintf(buf, "Minimum of %d, %d, and %d is %d\n", x, y, z, minimum(x, y, z));
      Serial.write(buf);
    }
    else if (k == "maximum") {
      sscanf(s.c_str(), "%s %d %d %d", buf, &x, &y, &z);
      sprintf(buf, "Maximum of %d, %d, and %d is %d\n", x, y, z, maximum(x, y, z));
      Serial.write(buf);
    }
    else if (k == "strlength") {
      sscanf(s.c_str(), "%s %s", buf, buf2);
      sprintf(buf, "Length of '%s' is %d\n", buf2, strlength(buf2));
      Serial.write(buf);
    }
    else {
      help();
    }
  }
}
