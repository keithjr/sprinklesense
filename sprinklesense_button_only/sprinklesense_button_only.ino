
const int BUTTON_PIN = 2;     // the number of the pushbutton pin
const int VALVE_PIN =  13;      // the number of the valve pin
const int MINS_ACTIVE = 15;  //Number of minutes to remain active after button press
const int SECS_ACTIVE = MINS_ACTIVE * 60;

int button_state = 0;     
int prev_button_state = 0;

//Used for millis commands
unsigned long start_time = 0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(VALVE_PIN, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(BUTTON_PIN, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  button_state = digitalRead(BUTTON_PIN);
  //FIXME need to worry about debounce?
  // check if the pushbutton is pressed
  if ((button_state == HIGH) && (prev_button_state == LOW)) {
    digitalWrite(VALVE_PIN, HIGH);
    start_time = millis();
    while (millis() < start_time + (SECS_ACTIVE*1000)) {
    }
    digitalWrite(VALVE_PIN,LOW);
  } 

  prev_button_state = button_state;
}



