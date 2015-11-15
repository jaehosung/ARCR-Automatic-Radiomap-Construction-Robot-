#define numSensor 2 // Number of Sensors
#define LEDPin 13 // Onboard LED

#define echoPin1 7 // Echo Pin of Sensor1
#define trigPin1 8 // Trigger Pin of Sensor1
#define echoPin2 9// Echo Pin of Sensor2
#define trigPin2 10// Trigger Pin of Sensor2

#define resetPin A0


int echoArr[numSensor] = {echoPin1,echoPin2};
int trigArr[numSensor] = {trigPin1,trigPin2};
long durationArr[numSensor];
long distanceArr[numSensor];

int minimumRange = 0; // Minimum range needed
int maximumRange = 200; // Minimum range needed
long duration1,duration2, distance1,distance2; // Duration used to calculate distance

void setup() {
    int i;
    Serial.begin (9600);
    for(i=0;i<numSensor;i++){
        pinMode(trigArr[i],OUTPUT);
        pinMode(echoArr[i],INPUT);
    }
}

void loop() {
    getDistance();
    printDistance();
//    checkReset();

    delay(50);

}

// CheckReset
void checkReset(){
    int i, check=-1;
    for(i=0;i<numSensor;i++){
        if(distanceArr[i]==0) resetArduino();
    }
}
// Using Analog Input Reset Arduino
void resetArduino(){
        analogWrite(resetPin,0);
        analogWrite(resetPin,1024);
}

// Make the value of duration to Distance
long durationToDistance(long duration)
{
    //Calculate the distance (in cm) based on the speed of sound.
    return duration/58.2;
}

// Get the echo duration
void getDistance(){
    long distance;
    long duration;
    int i;

    for(i = 0;i<numSensor;i++){
        digitalWrite(trigArr[i], LOW);
        delayMicroseconds(10); 
        digitalWrite(trigArr[i], HIGH);
        duration = pulseIn(echoArr[i], HIGH);
        distance = durationToDistance(duration);
        if(distance<maximumRange) distanceArr[i] = distance; else distanceArr[i]=0;
    }
}

// Serial print the value of Distance
void printDistance(){
    int i;
    for(i=0;i<numSensor;i++){
        Serial.print(distanceArr[i]);
        Serial.print("\t");
    }
    Serial.print("\n");
}
