/*
 * Tool to rename your HM-10 bluetooth dongle
 * v1.0 - 20211201
 * 
 * 1. Change the name you want for your robot from ESCORNABOT to something different in
 *    the first "#define" line of the code.
 * 2. Unplug the dongle from the Escornabot.
 * 3. Upload this Arduino sketch to your Escornabot.
 * 4. Replug the dongle to the Escornabot and restart it: after 2 seconds, you should 
 *    see the onboard LED flashing twice (first check), and after 2 more seconds, five 
 *    more times if everything went OK (second check).
 * 5. Reflash your Escornabot with its original firmware again and enjoy!
 *    (https://www.roboteach.es/escornabot-firmware/)
 */

#define BOTNAME "ESCORNABOT"


/* 
 * >>>>  Rest of the code: DO NOT TOUCH :)  <<<< 
 */
String answer;

void blinkLED(int times) {
  for (int i=0; i<times; i++) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(300);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
  }
  digitalWrite(LED_BUILTIN, LOW);
}

void setup() {
  // initial config
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(9600);

  // initial check
  delay(2000);
  Serial.write("AT\r\n");
  answer = Serial.readStringUntil('\n');
  if (answer=="OK\r") {
    blinkLED(2);
    delay(2000);
  } else {
    while (true); // halt
  }

  // change name
  Serial.write("AT+NAME");
  Serial.write(BOTNAME);
  Serial.write(0); // this does the trick to remove CRLF from the name itself for the BT-05!
  Serial.write("\r\n");

  // check answer
  String valid = "+NAME=";
  valid.concat(BOTNAME);
  valid.concat("\r");
  answer = Serial.readStringUntil('\n');
  if (answer==valid) {
    blinkLED(5);
  }
}

void loop() {
}
