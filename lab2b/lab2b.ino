////////////////////////////////////////
// COSC 130, Lab 2 Template File
// Modify the functions below
//
////////////////////////////////////////

String decimal_to_bin(int input)
{
  String output;
  // Write the binary value of input into
  // the string output
  for (int shift = 31; shift >= 0; shift--) {
    if ((input >> shift) & 1) {
      output += '1';
      input -= 1 << shift;
    } else {
      output += '0';
    }
    //input = working_input;
  }

  return output;
}

String decimal_to_hex(int input)
{
  String output;
  // Write the hex value of input into
  // the string output
  char nextchar;
  for (int shift = 28; shift >= 0; shift -= 4) {
    if ((input >> shift) & 15) {
      //We need to do something with these 4 bits
      if (((input >> shift) & 15) < 10) {
        nextchar = ((input >> shift) & 15) + '0';
        output += nextchar;
      } else {
        nextchar = (((input >> shift) & 15) - 10) + 'a';
        output += nextchar;
      }
      input -= ((input >> shift) & 15) << shift;
    } else {
      // Nothing.
      output += '0';
    }
  }

  return output;
}

String decimal_to_oct(int input)
{
  String output;
  char nextchar;
  // Write the octal value of input into
  // the string output
  nextchar = ((input >> 30) & 3) + '0';
  output += nextchar;
  for (int shift = 27; shift >= 0; shift = shift - 3) {
    if ((input >> shift) & 7) {
      nextchar = ((input >> shift) & 7) + '0';
      output += nextchar;
    } else {
      output += '0';
    }
  }

  return output;
}

////////////////////////////////////////
//
// DO NOT MODIFY ANY FUNCTIONS BELOW
//
////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial && (Serial.available() > 0)) {
    String input = Serial.readString();
    int i_input = input.toInt();

    Serial.println("Dec: " + input);
    Serial.println("Bin: " + decimal_to_bin(i_input));
    Serial.println("Oct: " + decimal_to_oct(i_input));
    Serial.println("Hex: " + decimal_to_hex(i_input));
    Serial.print("\n");

  }
  else {
    delay(115);
  }
}
