# Rangefinder Gun Embedded

This project involves creating a 3D-printed rangefinder gun that uses an ultrasonic sensor to measure distance. The system is powered by an ESP32-S3-WROOM microcontroller, with the measured distance displayed on a 16x2 I2C LCD. For simplicity, some parts of the build are attached using tape.

## Features
- **Ultrasonic Distance Measurement**: Measures the distance to an object using an ultrasonic range finder.
- **LCD Display**: The distance is displayed on a 16x2 I2C LCD.
- **Serial Output**: Outputs the measured distance to the serial monitor for debugging.

## Components
- **ESP32-S3-WROOM**
- **HC-SR04 Ultrasonic Range Finder**
- **16x2 I2C LCD**
- **Wires & Breadboard**
- **3D Printed Gun Frame** (with some parts attached using tape)

## Pin Configuration

| Component                | GPIO Pin      | Function          |
|--------------------------|---------------|-------------------|
| Ultrasonic Sensor Trig    | GPIO 4        | Trigger signal    |
| Ultrasonic Sensor Echo    | GPIO 5        | Echo signal       |
| LCD SDA                   | GPIO 6        | I2C Data Line     |
| LCD SCL                   | GPIO 7        | I2C Clock Line    |

## Circuit Diagram
- Connect the ultrasonic sensor’s Trig pin to GPIO 4 and Echo pin to GPIO 5.
- Connect the I2C LCD's SDA to GPIO 6 and SCL to GPIO 7.

## Code Explanation
The code uses the **LiquidCrystal_I2C** library to display distance measurements on the LCD. The ultrasonic sensor sends out a pulse, and the time it takes for the echo to return is used to calculate the distance to an object. The distance is printed on both the serial monitor and the LCD.

```cpp
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 

// Define pins connected from the ultrasonic sensor to ESP32
const int trigPin = 4;
const int echoPin = 5;

// Initialize the LCD with I2C address 0x27, 16 columns, and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

long pingTime;
float distance;

void setup() {
  Serial.begin(115200);
  
  // Set up the ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize the I2C communication for the LCD
  Wire.begin(6, 7); 
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("System Ready");
  
  delay(2000);  
  lcd.clear();
}

void loop() {
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echo time and calculate the distance
  pingTime = pulseIn(echoPin, HIGH);
  distance = (float)pingTime * 340.0 / 2.0 / 10000.0;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Display the distance on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.setCursor(0, 1);
  lcd.print(" cm");
  
  delay(300);  
}
```

## How to Use
1. **Hardware Setup**:
   - Connect the ultrasonic sensor and LCD according to the pin configuration table.
   - Ensure the 3D-printed parts are securely attached, with any necessary parts taped for simplicity.
2. **Software Setup**:
   - Install the **LiquidCrystal_I2C** library: [LiquidCrystal_I2C Library](https://github.com/johnrickman/LiquidCrystal_I2C).
   - Upload the code to your ESP32-S3-WROOM using the Arduino IDE.
3. **Run the Project**:
   - Open the serial monitor to view the distance measurements.
   - Observe the distance readings on the LCD as you point the rangefinder gun at objects.

## Future Improvements
- Add sound feedback using a buzzer to indicate proximity.
- Implement battery power for portability.
- Improve the design of the 3D-printed frame for a more durable structure.
- Extend the functionality by adding a laser pointer for more accurate targeting.

## License
This project is open-source under the MIT License. Feel free to modify and distribute as needed.
