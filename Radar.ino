      // Includes the Servo library
      #include <Servo.h>. 
      
      // Defines Tirg and Echo pins of the Ultrasonic Sensor
      const int trigPin = 10;
      const int echoPin = 11;
      
      // Variables for the duration and the distance
      long duration;
      int distance;
      
      // Creates a servo object for controlling the servo motor
      #define servoPin3 7
      Servo servo3;

      void setup() 
      {
        pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
        pinMode(echoPin, INPUT); // Sets the echoPin as an Input
        Serial.begin(9600);
        servo3.attach(servoPin3); // Defines on which pin is the servo motor attached
      }
      
      void loop() 
      {
        // servo of radar
        // rotates the servo motor for from 65 to 135 degrees
        for(int i=65;i<=135;)
        {  
          servo3.write(i);
          delay(30);
          distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
          i += 5;
          Serial.print(i); // Sends the current degree into the Serial Port
          Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
          Serial.print(distance); // Sends the distance value into the Serial Port
          Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
        }
        // Repeats the previous lines from 135 to 65 degrees
        for(int i=135;i>65;)
        {  
          servo3.write(i);
          delay(30);
          distance = calculateDistance();
          i -= 5;
          Serial.print(i);
          Serial.print(",");
          Serial.print(distance);
          Serial.print(".");
        }
      }
      
      // Function for calculating the distance measured by the Ultrasonic sensor
      int calculateDistance()
      { 
        digitalWrite(trigPin, LOW); 
        delayMicroseconds(2);
        // Sets the trigPin on HIGH state for 10 micro seconds
        digitalWrite(trigPin, HIGH); 
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
        delay(500);
        distance= duration*0.034/2;
        return distance;
      }
