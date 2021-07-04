int PULSE_LED = 7;
int MODE_BTN = 2;
int PULSE_BTN = 10;
int HALT_ISR_PIN = 3;

//macros for bebounce protection on rising edge of manual pulse button 
#define DRE(signal, state) (state=(state<<1)|signal)==B00001111
byte pulseButtonRisingState;

//macros for bebounce protection on falling edge of manual pulse button 
#define DFE(signal, state) (state=(state<<1)|signal)==B11110000
byte pulseButtonFallingState;

enum PulseMode { CLOCK, MANUAL };

int delayLength = 1000;
int pulseMode = CLOCK;
int pulseState = LOW;
bool halted = false;

/*
 * Setup PIN modes, initial states
 * and Interrupts
 */
void setup() {
  pinMode(PULSE_LED, OUTPUT); 
  pinMode(MODE_BTN, INPUT); 
  pinMode(PULSE_BTN, INPUT);
  pinMode(HALT_ISR_PIN, INPUT);
  pinMode(A0, INPUT);
  digitalWrite(MODE_BTN, HIGH);
  digitalWrite(PULSE_BTN, HIGH);
  digitalWrite(HALT_ISR_PIN, LOW);

  attachInterrupt(digitalPinToInterrupt(MODE_BTN), modeButtonIsPressed, FALLING);
  attachInterrupt(digitalPinToInterrupt(HALT_ISR_PIN), halt, CHANGE);
}

/*
 * Set the Pulse state if the 
 * program is not halted. 
 */
void setPulseState(int state){
  if(!halted){
    pulseState = state;
    digitalWrite(PULSE_LED, state); 
  }
}

/*
 * Perform 1 full clock cycle HIGH to LOW
 * delay between states is determined by
 * potentiometer in Analog PIN A0.
 */
void clk(){
  setPulseState(HIGH);
  delay(delayLength);
  setPulseState(LOW);
  delay(delayLength);
}

/*
 * Debounced Halt signal ISR handler
 * Used by processor for halting the system
 * Trigger: Rising edge on PIN 3
 */
void halt(){
  int haltValue = digitalRead(HALT_ISR_PIN);
  static unsigned long last_halt_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_halt_interrupt_time > 200) 
  {
    halted = haltValue == HIGH;
  }
  last_halt_interrupt_time = interrupt_time;
}

/*
 * Debounced Mode button ISR handler
 * Used for toggling between automatic
 * clock and manual pulse modes
 * Trigger: Falling edge on PIN 2
 */
void modeButtonIsPressed(){
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  // If interrupts come faster than 200ms, assume it's a bounce and ignore
  if (interrupt_time - last_interrupt_time > 200) 
  {
    pulseMode = pulseMode == CLOCK ? MANUAL : CLOCK;
  }
  last_interrupt_time = interrupt_time;
}

/*
 * Check if the manual pulse button is pressed
 * Falling edge triggers Pulse HIGH
 * Rising edge triggers Pulse LOW
 */
void readPulseButton() {
  // Read button states every 5 ms (debounce time):
  static unsigned long lastDebounce;
  if (millis() - lastDebounce >= 5) {
    lastDebounce = millis();
    // Falling edge (if switch is pressed)
    if (DFE(digitalRead(PULSE_BTN), pulseButtonFallingState)) {
      setPulseState(HIGH);
    }

    // Rising edge (if switch is released)
    if (DRE(digitalRead(PULSE_BTN), pulseButtonRisingState)) {
      setPulseState(LOW);
    }
  }
}

/*
 * Program loop.
 * skips execution if program is halted
 */
void loop() {
  if(!halted){
    //Detect the delay length;
    delayLength = (floor(analogRead(A0) / 10) * 10) * 2 + 1;
  
    //Automatic CLOCK pulse
    if(pulseMode == CLOCK){
      clk();
    }
    //Manual Pulse (with pin 10 button)
    else{
      readPulseButton();
    } 
  }
  else{
    delay(1);
  }
}
