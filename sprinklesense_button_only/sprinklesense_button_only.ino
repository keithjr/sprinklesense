
const int BUTTON_PIN = 2;  
const int VALVE_PIN  = 12; 
const int LED_PIN    = 13; //mirror valve output on LED
const unsigned long MINS_ACTIVE = 15;  //Number of minutes to remain active after button press
const unsigned long SECS_ACTIVE = MINS_ACTIVE * 60;

int button_state = 0;     
int prev_button_state = 0;

//Used for millis commands
unsigned long start_time = 0;
unsigned long dbg_cur_millis = 0;
unsigned long dbg_prev_millis = 0;
unsigned long dbg_secs_elapsed = 0;

void setup() {
  pinMode(VALVE_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  // debug interface
  Serial.begin(9600);
}

void loop() {
  // read the state of the pushbutton value:
  button_state = digitalRead(BUTTON_PIN);
  // check if the pushbutton is pressed
  if ((button_state == HIGH) && (prev_button_state == LOW)) {
    Serial.print("Button push detected\n");
    Serial.print("Target seconds active: ");
    Serial.print(SECS_ACTIVE);
    Serial.print("\n");
    digitalWrite(VALVE_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);    
    start_time = millis();
    while (millis() < start_time + (SECS_ACTIVE*1000)) {
      //Pure delay, this space used for debug
      dbg_cur_millis = millis();
      if (dbg_cur_millis - dbg_prev_millis >= 1000) {
        dbg_secs_elapsed++;
        Serial.print("Elapsed: ");
        Serial.print(dbg_secs_elapsed);
        Serial.print(" / ");
        Serial.print(SECS_ACTIVE);
        Serial.print("\n");
        dbg_prev_millis = dbg_cur_millis;
      }
    }
    digitalWrite(VALVE_PIN,LOW);
    digitalWrite(LED_PIN,LOW);
  } 

  prev_button_state = button_state;
}
