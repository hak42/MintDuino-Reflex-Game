// MintDuino NoteBook 1 – Reflex Game version 7.0

int ledGameLight = 7; // Digital Pin 7 for LED anode connection
int ledPlayer1 = 5; 
int ledPlayer2 = 6;
int button1 = 4;
int button2 = 3;
int state2 = 0;
int state1 = 0;
int ledWait = 5000;  //Wiat time will be a minimum of 5 seconds

void setup() {
  pinMode(ledGameLight, OUTPUT); 
  pinMode(ledPlayer1, OUTPUT);
  pinMode(ledPlayer2, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  randomSeed(analogRead(1));  // use Analog Pin 1 to generate a random number
}

void loop() {
  state2 = digitalRead(button2); // Read the state of the pushbutton value;
  
  if (state2 == HIGH) {  // Check if the pushbutton is pressed
    digitalWrite(ledPlayer1, LOW);  //Turn LED 1 off;
    digitalWrite(ledPlayer2, LOW);  //Turn LED 2 off;
    delay (2000);
    beginGame();
  }
  else {
    // turn LED on:
    digitalWrite(ledPlayer1, HIGH); // Turn LED 1 on
    digitalWrite(ledPlayer2, HIGH); // Turn LED 2 on
  }
}

void beginGame(){  // Only called when the button state is HIGH (pressed)
  
  // three fast blinks
  for (int count = 0; count < 3; count++) {
    digitalWrite(ledGameLight, HIGH);
    delay(500);
    digitalWrite(ledGameLight, LOW);
    delay(500);
  }
  
  //Now generate a wait time before Game Light turns on
  ledWait = 5000; // reset value to minimum of 5 seconds
  ledWait = ledWait + random(5000); // add random value of 0-5000 milliseconds
  
  //Turn on Game Light after Wait Time expires
  delay(ledWait);
  digitalWrite(ledGameLight, HIGH);
  delay(100);
  digitalWrite(ledGameLight, LOW);
  
  int gameOver = 0;
  
  while (!gameOver) {
    //determine which player button was pressed first
    int button1State = digitalRead(button1);
    int button2State = digitalRead(button2);
    
    if (button1State != button2State) {
      delay(5); // pause, then take another reading
      if (button1State == HIGH && digitalRead(button1) == HIGH) {
        Player1Win();
        gameOver = 1;
      }
      
      if (button2State == HIGH && digitalRead(button2) == HIGH) {
        Player2Win();
        gameOver = 1;
      }
    }
    else {
      if (button1State == HIGH && button2State == HIGH) {
        // tie
        itsATie();
        gameOver = 1;
      }
    }
    
  }
  
  // Start game over
  
}

// Tie
void itsATie() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(ledPlayer1, HIGH);
    digitalWrite(ledPlayer2, HIGH);
    delay(250);
    digitalWrite(ledPlayer1, LOW);
    digitalWrite(ledPlayer2, LOW);
    delay(250);
  }
}

// Player 1 won, light their LED
void Player1Win() {
  digitalWrite(ledPlayer1, HIGH);
  digitalWrite(ledPlayer2, LOW);
  delay(4000);
  digitalWrite(ledPlayer1, LOW);
}

// Player 2 won, light their LED
void Player2Win() {
  digitalWrite(ledPlayer2, HIGH);
  digitalWrite(ledPlayer1, LOW);
  delay(4000);
  digitalWrite(ledPlayer2, LOW);
}

