#define LED_PIN 13
#define BUT_PIN 2
#define BUT_PIN_2 3

int state;
unsigned long blinkBefore;
unsigned long firstPress;
unsigned long secondPress;
bool pressed1 = false;
bool pressed2 = false;
int blinkTime = 1000;

void setup() 
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUT_PIN, INPUT);
  pinMode(BUT_PIN_2, INPUT);
  state = 0;
  blinkBefore = millis();
  Serial.begin(9600);
}

void loop() 
{
  unsigned long blinkNow = millis();
  digitalWrite(LED_PIN, state);
  
  if(blinkNow >= blinkBefore + blinkTime)
  {
    blinkBefore = blinkNow;
    state = !state; 
  }
  
  int but1 = digitalRead(BUT_PIN);
  int but2 = digitalRead(BUT_PIN_2);
  
  if (but1 == LOW)
  {
    pressed1 = true;
    
    if(pressed2)
    {
      secondPress = millis();
      
      if(secondPress < firstPress + 500)
      {
        while(1);
      }
      else
      {
        pressed2 = false;
      }
    }
    else
    {
      firstPress = millis();
    }
    
    if(blinkTime >= 100)
    {
    	blinkTime -= 100;
    }
  }
  
  if(but2 == LOW)
  {
    pressed2 = true;
    
    if(pressed1)
    {
      secondPress = millis();
      
      if(secondPress < firstPress + 500)
      {
        while(1);
      }
      else
      {
        pressed1 = false;
      }
    }
    else
    {
      firstPress = millis();
    }
    
    blinkTime += 100;
  }
  
  Serial.println(blinkTime);
}