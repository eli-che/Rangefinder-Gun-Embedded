#include <Wire.h> 
#include <LiquidCrystal_I2C.h> // For I2C version of LCD

// Define pins connected from the ultrasonic sensor to esp32
const int trigPin = 4;
const int echoPin = 5;

//Define LCD
// Initialize the LCD with I2C address 0x27, 16 columns, and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variables to store distance and pingTime.
long pingTime;
float distance;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  //Set the input pins for range finger.
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //Wiring for lcd
  Wire.begin(6, 7); // SDA on GPIO 6, SCL on GPIO 7
  
  //LCD setup
  lcd.begin(16, 2); // Specify the dimensions of the LCD (16 columns, 2 rows)
  lcd.backlight();  // Turn on the LCD backlight
  lcd.setCursor(0, 0);
  lcd.print("System Ready");
  
  delay(2000); // Pause for 2 seconds
  lcd.clear(); // Clear the LCD after the intro message
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, HIGH); // send 10us high level to trigPin
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  pingTime = pulseIn(echoPin, HIGH); // read pulse time of echoPin
  distance = (float)pingTime * 340.0 / 2.0 / 10000.0;  // calculate distance with sound speed 340m/s

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Display the distance on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");  // Print the text "Distance: "
  lcd.print(distance);      // Print the variable 'distance'
  lcd.setCursor(0, 1);      // Set the cursor to the second row, first column
  lcd.print(" cm");         // Print the text " cm"
  
  // Add a delay before next measurement
  delay(300);
}
