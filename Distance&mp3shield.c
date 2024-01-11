#include <SPI.h>
#include <SdFat.h>
#include <SFEMP3Shield.h>
// Pin definitions
const int TRIGGER_PIN = 10;
const int ECHO_PIN = 5;
// Global variables
SdFat sd;
SFEMP3Shield mp3Player;
long randomNumber;
unsigned long lastWaveTime = 0;
const unsigned long waveDelay = 500; // Minimum delay between wave detections
float lastDistance = 0.0;
const float waveThreshold = 10.0; // Change in cm to detect a wave
byte currentVolume = 10;
const byte volumeChangeStep = 2; // Amount of volume change per loop iteration
void setup() {
// Initialize serial communication
Serial.begin(115200);
// Set pin modes
pinMode(TRIGGER_PIN, OUTPUT);
pinMode(ECHO_PIN, INPUT);
// Initialize the SD card and MP3 shield
if (!sd.begin(9, SPI_HALF_SPEED)) {
sd.initErrorHalt();
}
if (!sd.chdir("/")) {
sd.errorHalt("sd.chdir");
}

// Print a welcome message
Serial.println(F("Ultrasonic mode activated"));
// Seed the random number generator
randomSeed(analogRead(0));
// Play the first track

}
void loop() {
// Measure distance using ultrasonic sensor
digitalWrite(TRIGGER_PIN, LOW);
delayMicroseconds(2);
digitalWrite(TRIGGER_PIN, HIGH);
delayMicroseconds(10);
digitalWrite(TRIGGER_PIN, LOW);
long duration = pulseIn(ECHO_PIN, HIGH);
float distance = duration * 0.034 / 2; // Convert duration to distance in cm
Serial.println(distance);
// mp3Player.begin();
// mp3Player.setVolume(currentVolume, currentVolume);
// mp3Player.playTrack(003);
if (distance < 50) {
mp3Player.begin();
mp3Player.setVolume(currentVolume, currentVolume);
mp3Player.playTrack(002);
delay(5000);
mp3Player.playTrack(005);
}

delay(1000);
}
