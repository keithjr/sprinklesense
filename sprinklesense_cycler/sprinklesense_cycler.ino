const int MINUTES_TO_WATER = 15;
const int SECONDS_TO_WATER = 60 * MINUTES_TO_WATER;

const int HOURS_TO_WAIT = 48;
const int MINUTES_TO_WAIT = HOURS_TO_WAIT * 60;
const int SECONDS_TO_WAIT = MINUTES_TO_WAIT * 60;

const int solenoid_pin =  13;
const int start_button_pin =  1;
const int stop_button_pin =  1;

int solenoid_state;
int start_button_state;
int stop_button_state;

int timer_display_hours;
int timer_display_minutes;
int timer_display_seconds;
int timer_seconds;

int cur_millis;
int prev_millis;

enum state_t {
  IDLE_ON,
  WATERING,
  WAITING
}

state_t cur_state;

void setup() {
  pinMode(solenoid_pin, OUTPUT);
  pinMode(start_button_pin, INPUT);
  pinMode(stop_button_pin, INPUT);
  
  cur_state = IDLE_ON;
  
  prev_millis = millis();
  cur_millis = millis();

}

void loop() {
  //Get button states before entering FSM
  start_button_state = digitalRead(start_button_pin);
  stop_button_state  = digitalRead(stop_button_pin);
  cur_millis = millis();
  
  switch(cur_state) {
    case IDLE_ON:
      solenoid_state = LOW;
      if (start_button_state == HIGH) {
        cur_state = WATERING
        timer_seconds = SECONDS_TO_WATER;        
      }
      break;

    case WATERING:
      solenoid_state = HIGH;
      if (stop_button_state == HIGH) {
        cur_state = IDLE_ON;
      }
      else {
        //Check to see if one second has passed
        if (curr_millis - prev_millis > 1000) {
          timer_seconds--;
        }
        if (timer_seconds == 0) {
          cur_state = WAITING;
          timer_seconds = SECONDS_TO_WAIT;
        }  
      }
      break;
      
    case WAITING:
      solenoid_state = LOW;
      if (stop_button_state == HIGH) {
        cur_state = IDLE_ON;
      }
      else {
        //Check to see if one second has passed
        if (curr_millis - prev_millis > 1000) {
          timer_seconds--;
        }
        if (timer_seconds == 0) {
          cur_state = WATERING;
          timer_seconds = SECONDS_TO_WATER;        
        }
      }
      break;
   
    default:
      solenoid_state = LOW;
  }        
  prev_millis = curr_millis;    
  digitalWrite(solenoid_pin, solenoid_state);
  
}

