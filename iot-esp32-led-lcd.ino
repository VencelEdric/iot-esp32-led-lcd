// Define Pin Allocations
#define TRIG_PIN    5   // Connects to HC-SR04 Trig
#define ECHO_PIN    18  // Connects to HC-SR04 Echo
#define BUZZER_PIN  12  // Connects to Buzzer

// Configuration Settings
#define DISTANCE_THRESHOLD 50  // Alarm distance trigger in centimeters (approx. 20 inches)
#define TONE_FREQ          2000 // Sound frequency for passive buzzer

void setup() {
  Serial.begin(115200);
  
  // Configure pin behaviors
  pinMode(TRIG_PIN, OUTPUT); 
  pinMode(ECHO_PIN, INPUT);  
  pinMode(BUZZER_PIN, OUTPUT);
  
  Serial.println("Ultrasonic Distance Alarm System Active!");
}

void loop() {
  // Clear the trigger pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  // Set the trigger pin HIGH for 10 microseconds to send sonic pulse
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Measure the duration of the incoming echo pulse in microseconds
  long duration = pulseIn(ECHO_PIN, HIGH);
  
  // Calculate the distance in centimeters (Speed of sound = 0.0343 cm/us)
  float distance = duration * 0.0343 / 2;
  
  // Print distance to Serial Monitor (ignoring out-of-range readings)
  if (distance > 0 && distance < 400) {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
    
    // Check if the object is closer than your limit
    if (distance < DISTANCE_THRESHOLD) {
      Serial.println("🚨 Threshold Breached! Alarm ON.");
      tone(BUZZER_PIN, TONE_FREQ); // Turn alarm sound on
    } else {
      noTone(BUZZER_PIN);          // Turn alarm sound off
    }
  }

  delay(200); // Wait 200ms before taking the next reading
}
