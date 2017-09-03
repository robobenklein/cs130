short multiply(byte left, byte right)
{
  short result = 0;
  bool negate = false;

  //Write the code to multiply here

  if (left & (1<<7)) {
    left = ~left + 1;
    negate = !negate;
  }
  if (right & (1<<7)) {
    right = ~right + 1;
    negate = !negate;
  }
  
  // Left to the left,
  // Right to the right

  for (int i = 0; i < 8; i++) {
    if (right & 1) {
      result += (left << i);
    } else {
      
    }
    right = right >> 1;
  }

  if (negate) {
    result = ~result + 1;
  }
  
  return result;
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Enter left right to multiply: ");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial && (Serial.available() > 0)) {
    String input = Serial.readString();
    int left;
    int right;
    int i;

    for (i = 0;i < input.length();i++) {
      if (input.charAt(i) == ' ') {
        break;
      }
    }
    left = input.substring(0, i).toInt();
    right = input.substring(i+1).toInt();

    Serial.println("Result = " + String(multiply((byte)left, (byte)right), DEC));
    Serial.print("\n");
    Serial.println("Enter left right to multiply: ");  
  }
  else {
    delay(115);
  }
}
