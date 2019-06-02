//ultrasonicSensorPins
int echo = 4;
int trig = 8;

//floorButtonPins
int ground = 12;
int first = 2;
int second = 3;

//motorPins
int door1 = 9;
int door2 = 10;
int pull1 = 6;
int pull2 = 5;

//other variables
int distance;
long duration;
boolean lastButton = LOW;
boolean currentButton = LOW;




void setup() 
{
  //setting pins as input
  pinMode(ground, INPUT);
  pinMode(first, INPUT);
  pinMode(second, INPUT);
  pinMode(echo, INPUT);

  //setting pins as output
  pinMode(door1, OUTPUT);
  pinMode(door2, OUTPUT);
  pinMode(pull1, OUTPUT);
  pinMode(pull2, OUTPUT);
  pinMode(trig, OUTPUT);

  //interrupt pins
  attachInterrupt(digitalPinToInterrupt(2), firstFloor, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), secondFloor, CHANGE);
 

  //start serial monitor 
  Serial.begin(9600);

}

boolean debounce(boolean last)
{
  boolean current = digitalRead(ground);
  if (last != current)
  {
    delay(5);
    current = digitalRead(ground);
  }
  return current;
}

//ultrasonicSensor
int ultraSonic()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echo, HIGH);
// Calculating the distance
  distance= duration*0.034/2;
//// Prints the distance on the Serial Monitor
//  Serial.print("Distance: ");
 Serial.println(distance);
 return distance;
}

void loop() 

{
  ultraSonic();
   currentButton = debounce(lastButton);
  if (lastButton == LOW && currentButton == HIGH)
  {
    groundFloor();
  }
  lastButton = currentButton;
  
 


}

//groundFloorFunction
void groundFloor()
{
   
   while(distance > 4 )
    {
      ultraSonic();
      analogWrite(pull1,0);
      analogWrite(pull2,255);
      Serial.println("coming_to_ground_floor");
      if((distance > 2) && (distance < 5))
      {
        analogWrite(pull1,0);
        analogWrite(pull2,0);
        Serial.print("stop");
        analogWrite(door1,200);
        analogWrite(door2,0);
        delay(9400);
        analogWrite(door1,0);
        analogWrite(door2,0);
        
        break;
        
        
        
        
        
      }
    }
    while(distance < 4)
    {
      ultraSonic();
      analogWrite(pull1,255);
      analogWrite(pull2,0);
      Serial.println("coming_to_ground_floor");
      if((distance > 2) && (distance < 5))
      {
        analogWrite(pull1,0);
        analogWrite(pull2,0);
        Serial.print("stop");
        analogWrite(door1,200);
        analogWrite(door2,0);
        delay(8500);
        analogWrite(door1,0);
        analogWrite(door2,0);
        
        break;
        
      }
    }
}

//firstFloorFunction
void firstFloor()
{
   
   while(distance > 15 )
    {
      ultraSonic();
      analogWrite(pull1,0);
      analogWrite(pull2,255);
      Serial.println("coming_to_first_floor");
      if((distance > 13) && (distance < 17))
      {
        analogWrite(pull1,0);
        analogWrite(pull2,0);
        Serial.print("stop");

        break;
        
       }
    }
    while(distance < 15)
    {
      ultraSonic();
      analogWrite(pull1,255);
      analogWrite(pull2,0);
      Serial.println("coming_to_first_floor");
      if((distance > 13) && (distance < 17))
      {
        analogWrite(pull1,0);
        analogWrite(pull2,0);
        Serial.print("stop");

        break;
        
      }
    }
}

//secondFloorFunction
void secondFloor()
{
  
  while(distance > 27)
    {
      ultraSonic();
      analogWrite(pull1,0);
      analogWrite(pull2,255);
      Serial.println("coming_to_second_floor");
      if((distance > 26) && (distance < 28))
      {
        analogWrite(pull1,0);
        analogWrite(pull2,0);
        Serial.print("stop");
       
        break;
        
      }
    }
     while(distance < 26)
     {
      ultraSonic();
      analogWrite(pull1,255);
      analogWrite(pull2,0);
      Serial.println("coming_to_second_floor");
      if((distance > 25) && (distance < 27))
      {
        analogWrite(pull1,0);
        analogWrite(pull2,0);
        Serial.print("stop");
        
        break;
        
        
      }
     }
}
