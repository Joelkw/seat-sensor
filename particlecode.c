const int THRESH = 15;

int inPin = A0;
int sitCount = 0;
int standCount = 0;
int state = 0;
int publicState = 0;
//String data;

void setup() {
    pinMode(inPin, INPUT);
   // Particle.variable("mydata", data);
  Serial.begin(9600);
  Particle.variable("publicState", publicState);
  Serial.print("Starting up now!");
}

void loop() {
    // first keep track of number of readings in a row
    if (analogRead(inPin) > 2000)
    {
        sitCount++;
        standCount = 0;
    }
    else if (analogRead(inPin) < 2000)
    {
        sitCount = 0;
        standCount++;
    }
    
    if (sitCount >= THRESH)
    {
        // do something, someone is sitting, change from state or resend
        if (state == 0)
        {
            publicState = 1;
            //Particle.publish("Sitting", "1");
            Serial.println("PUBLISHED SITTING WAS 1");
        }
        // prevent integer overflow eventually 
        sitCount = THRESH;
        state = 1;
    }
    else if (standCount >= THRESH)
    {
        // do something else, someone is not sitting
        if (state == 1)
        {
            publicState = 0;
            //Particle.publish("Sitting", "0");
            Serial.println("PUBLISHED SITTING WAS 0");
        }
        // prevent integer overflow
        standCount = THRESH;
        state = 0;
    }
    Serial.println(analogRead(inPin));
    delay(20);
}