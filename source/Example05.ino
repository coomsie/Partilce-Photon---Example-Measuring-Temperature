// -----------------------------------
// Example - 05: Measuring Temperature
// -----------------------------------
#include "application.h"
#include <math.h>
#include "TM1637.h"
#include "SparkFunPhant.h"
#include "HttpClient.h"
#include "function_pulseIn.h"
/*#include "thethingsiOClient.h"*/

//#include "rgb_lcd.h"

#include "SeeedOLED.h"

const char server[] = "data.sparkfun.com"; // Phant destination server
const char publicKey[] = "JxLvQJ656JuJDm5gW9y3"; // Phant public key
const char privateKey[] = "gzJG1qwXwqfega7ndmXK"; // Phant private key
Phant phant(server, publicKey, privateKey); // Create a Phant object

/*thethingsiOClient thing("iDASYVfno4IwLrKy6G-Au2rRjddUhwiAPDJ-wFZ3P4I");*/

#define VARIABLE_ID "55ec2e357625420f56e10070"
#define TOKEN "xNKVRzWkBi0wFlsWhRARYQIC5kRlwT"

#define xivelyAPIKEY "NgBy45gL6dhhN3J6jQyRZJQUsmiNprBGDSiOXvlYIheQeKEH"

#define LOGGING true

HttpClient http;

// Headers currently need to be set at init, useful for API keys etc.
http_header_t headers[] = {
    //  { "Content-Type", "application/json" },
    //  { "Accept" , "application/json" },
    { "Content-Type", "application/json" },
    { "X-Auth-Token" , TOKEN },
    {"X-ApiKey" , xivelyAPIKEY },
    // { "Accept" , "*/*"},
     { "Accept" , "application/json" },
    { NULL, NULL } // NOTE: Always terminate headers with NULL
};

http_request_t request;
http_response_t response;

/*/// LCD Stuff
rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;
//end of lcd*/


//oled stuff
static unsigned char SeeedLogo[]={
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x60, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0xfc, 0xff, 0x87, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03,
0xff, 0xfc, 0x00, 0x00, 0x00, 0x80, 0xf0, 0x20, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0x60, 0xe0, 0xc0,
0xc0, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0x60, 0xe0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x80, 0xc0,
0xc0, 0xe0, 0x60, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0x60, 0xe0, 0xc0, 0xc0,
0x80, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xe0, 0xe0, 0xc0, 0xc0, 0xf8, 0xf8, 0x00, 0x00, 0x00, 0x00,
0x00, 0xc0, 0xc0, 0xe0, 0x60, 0xc0, 0xc0, 0x80, 0x00, 0xc0, 0xf0, 0xf0, 0xf0, 0xc0, 0x00, 0xc0,
0xc0, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xe0, 0xe0, 0xc0, 0xc0,
0xf8, 0xf8, 0x00, 0xd8, 0xd8, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xe0, 0x60, 0xc0, 0xc0, 0x80, 0x00,
0x00, 0x03, 0x0f, 0x1e, 0x3c, 0x70, 0xe3, 0xcf, 0x9f, 0x30, 0x00, 0x00, 0x00, 0x00, 0x70, 0xbf,
0xcf, 0xe3, 0x70, 0x78, 0x3e, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x33, 0x77, 0x66, 0x66, 0x66, 0x6c,
0x7d, 0x18, 0x00, 0x1f, 0x3f, 0x76, 0x66, 0x66, 0x66, 0x76, 0x37, 0x07, 0x00, 0x0f, 0x3f, 0x7f,
0x66, 0x66, 0x66, 0x66, 0x77, 0x27, 0x07, 0x00, 0x1f, 0x3f, 0x76, 0x66, 0x66, 0x66, 0x76, 0x37,
0x07, 0x00, 0x0f, 0x3f, 0x71, 0x60, 0x60, 0x60, 0x60, 0x31, 0x7f, 0x7f, 0x00, 0x00, 0x00, 0x00,
0x11, 0x37, 0x67, 0x66, 0x66, 0x6c, 0x7d, 0x38, 0x00, 0x00, 0x3f, 0x7f, 0x3f, 0x00, 0x00, 0x1f,
0x3f, 0x70, 0x60, 0x60, 0x70, 0x7f, 0x7f, 0x00, 0x0f, 0x3f, 0x71, 0x60, 0x60, 0x60, 0x60, 0x31,
0x7f, 0x7f, 0x00, 0x7f, 0x7f, 0x00, 0x06, 0x1f, 0x3b, 0x60, 0x60, 0x60, 0x60, 0x71, 0x3f, 0x1f,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01,
0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x48, 0x48, 0x48, 0xb0, 0x00, 0xc0, 0x20,
0x20, 0x20, 0xc0, 0x00, 0xc0, 0x20, 0x20, 0x20, 0xc0, 0x00, 0x40, 0xa0, 0xa0, 0xa0, 0x20, 0x00,
0x00, 0x20, 0xf0, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0xf8, 0x08,
0x08, 0x00, 0xc0, 0x20, 0x20, 0x20, 0xf8, 0x00, 0xc0, 0xa0, 0xa0, 0xa0, 0xc0, 0x00, 0x20, 0xa0,
0xa0, 0xa0, 0xc0, 0x00, 0x40, 0xa0, 0xa0, 0xa0, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x48, 0x48, 0x48, 0x08, 0x00, 0x20, 0x40, 0x80, 0x40,
0x20, 0x00, 0x00, 0x20, 0xf0, 0x20, 0x20, 0x00, 0xc0, 0xa0, 0xa0, 0xa0, 0xc0, 0x00, 0xe0, 0x00,
0x20, 0x20, 0xc0, 0x00, 0xc0, 0x20, 0x20, 0x20, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02, 0x02, 0x02, 0x01, 0x00, 0x01, 0x02,
0x02, 0x02, 0x01, 0x00, 0x01, 0x02, 0x02, 0x02, 0x01, 0x00, 0x02, 0x02, 0x02, 0x02, 0x01, 0x00,
0x00, 0x00, 0x01, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x03, 0x02,
0x02, 0x00, 0x01, 0x02, 0x02, 0x02, 0x03, 0x00, 0x01, 0x02, 0x02, 0x02, 0x00, 0x00, 0x01, 0x02,
0x02, 0x02, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x00, 0x00, 0x08, 0x06, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x02, 0x02, 0x82, 0x02, 0x00, 0x02, 0x01, 0x01, 0x01,
0x02, 0x00, 0x00, 0x00, 0x01, 0x02, 0x02, 0x00, 0x01, 0x02, 0x02, 0x02, 0x00, 0x00, 0x03, 0x00,
0x00, 0x00, 0x03, 0x00, 0x01, 0x02, 0x02, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x82, 0x8c, 0x60, 0x1c, 0x02, 0x00, 0x1c, 0x22, 0x22, 0x22, 0x1c, 0x00, 0x1e,
0x20, 0x20, 0x00, 0x3e, 0x00, 0x00, 0x3e, 0x04, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3e, 0x04, 0x02, 0x02, 0x00, 0x1c, 0x2a, 0x2a, 0x2a, 0x0c, 0x00, 0x12, 0x2a, 0x2a,
0x2a, 0x1c, 0x20, 0x1c, 0x22, 0x22, 0x22, 0x14, 0x00, 0x3f, 0x00, 0x02, 0x02, 0x3c, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


//oled end

void dispNum(unsigned int num);

// name the pins
#define CLK D4
#define DIO D5
TM1637 tm1637(CLK,DIO);
#define TEMPPIN A4


//declare Air Quality pins
#define P1 D2 ///Small Particle (pm2.5)
#define P2 D3 //Large Particle (pm10)

int PIN_P1 = P1;
int PIN_P2 = P2;

String _pm10="0";
String _pm25 = "0";
String _pm10Display = "...";
String _pm25Display = "...";
unsigned long durationP1;
unsigned long durationP2;
unsigned long starttime;
unsigned long sampletime_ms = 30000;//sampe 30s ;
unsigned long lowpulseoccupancyP1 = 0;
unsigned long lowpulseoccupancyP2 = 0;
float ratioP1 = 0;
float concentrationP1 = 0;
float ratioP2 = 0;
float concentrationP2 = 0;




String Org = "Campion";
String Disp = "Campion";
String Locn = "Heathcote";

int lcd_start_pt = 4;

long previousMillis = 0;        // will store last time was updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 30000;           // interval at which to send data to internet (milliseconds)

///FOR TESTING DIGIT display
String inputString = ""; // a string to hold incoming data
char x1 = 0; // char to attribute to 2nd digit of the display

//temp variables
String tempC = "0";
String tempCDisplay = "...";

bool debugMode = true;

// This routine runs only once upon reset
void setup()
{
  /*//lcd stufff
  // set up the LCD's number of columns and rows:
   lcd.begin(16, 2);

   lcd.setRGB(colorR, colorG, colorB);

   // Print a message to the LCD.
   lcd.print("hello, world!");

//end of lcd*/

//oled stuff
Wire.begin();
  SeeedOled.init();  //initialze SEEED OLED display

  /*SeeedOled.setInverseDisplay();          // Set Display to inverse mode
  SeeedOled.clearDisplay();               // clear the screen and set start position to top left corner
  SeeedOled.drawBitmap(SeeedLogo,1024);   // 1024 = 128 Pixels * 64 Pixels / 8
  SeeedOled.setHorizontalScrollProperties(Scroll_Left,0,7,Scroll_5Frames);  //Set the properties of Horizontal Scrool
  SeeedOled.activateScroll();             // Activate Scroll*/
///end of oled

  //temp stuff
  tm1637.set();                                 // cofig TM1637
  tm1637.init();                                // clear the display
  Serial.begin(9600);                           // init serial port on USB interface

  //display startup message HEL0
  int8_t Disp[] = {0x01,0x02,0x03,0x04};
  Disp[0]=72;
  Disp[1]=14;
  Disp[2]=76;
  Disp[3]=48;
  tm1637.display(Disp);
  delay(1000);

  //start pins
  pinMode(D3,INPUT);
  pinMode(D2,INPUT);
  starttime = millis();//get the current time;

}

// This routine loops forever
void loop()
{
// oled screen

SeeedOled.clearDisplay();          //clear the screen and set start position to top left corner
SeeedOled.setNormalDisplay();      //Set display to normal mode (i.e non-inverse mode)
//SeeedOled.setInverseDisplay();          // Set inverse display
SeeedOled.setPageMode();           //Set addressing mode to Page Mode
SeeedOled.setTextXY(0,0);          //Set the cursor to Xth Page, Yth Column
SeeedOled.putString("Temp: " + tempCDisplay.substring(0,tempCDisplay.lastIndexOf(".")+2) + "(c)");
SeeedOled.setTextXY(2,0);          //Set the cursor to Xth Page, Yth Column
SeeedOled.putString("PM10: " + _pm10Display.substring(0,_pm10Display.lastIndexOf(".")+2) + "ug/m3");
SeeedOled.setTextXY(4,0);          //Set the cursor to Xth Page, Yth Column
SeeedOled.putString("PM2.5: " + _pm25Display.substring(0,_pm25Display.lastIndexOf(".")+2) + "ug/m3"); //Print the String
  //oled end

  char payload[255];

//air Quality
//pm10
durationP2 = pulseIn(PIN_P2, LOW);
lowpulseoccupancyP2 = lowpulseoccupancyP2+durationP2;
durationP1 = pulseIn(PIN_P1, LOW);
lowpulseoccupancyP1 = lowpulseoccupancyP1+durationP1;
if ((millis()-starttime) > sampletime_ms)//if the sampel time == 30s
  {
    ratioP2 = lowpulseoccupancyP2/(sampletime_ms*10.0);  // Integer percentage 0=>100
    concentrationP2 = 1.1*pow(ratioP2,3)-3.8*pow(ratioP2,2)+520*ratioP2+0.62; // using spec sheet curve
    Serial.print("pm10concentration = ");
    Serial.print(concentrationP2);
    Serial.println(" pcs/0.01cf");
    Serial.println("\n");
    lowpulseoccupancyP2 = 0;

    //publish online
    _pm10  = (String) concentrationP2;
    _pm10Display = (String) (roundf(concentrationP2 * 100) / 100);  /* = 37.777779; Result: 37.78 */
    Spark.publish("pm10",_pm10);


  //pm10
      ratioP1 = lowpulseoccupancyP1/(sampletime_ms*10.0);  // Integer percentage 0=>100
      concentrationP1 = 1.1*pow(ratioP1,3)-3.8*pow(ratioP1,2)+520*ratioP1+0.62; // using spec sheet curve
      Serial.print("pm25concentration = ");
      Serial.print(concentrationP1);
      Serial.println(" pcs/0.01cf");
      Serial.println("\n");
      lowpulseoccupancyP1 = 0;


      starttime = millis();

      //publish online
      _pm25 = (String) (concentrationP1 - concentrationP2);
      _pm25Display = (String) (roundf( (concentrationP1 - concentrationP2) * 100) / 100);
      Spark.publish("pm25",_pm25);
    }
    ///end of Quality

  //for debuging the LED
  /*if (Serial.available() > 0) {
    // get the new byte:
    char inChar = (char)Serial.read();

    // add it to the inputString:
    inputString += inChar;

    // if the incoming character is a newline,
    if (inChar == '\n') {
    // if the incoming character is a newline,
      Serial.print("string ");
      Serial.println(inputString); //print string

      x1 = inputString[1]; // attach x1 to the second char in the string created
      Serial.print("digit ");
      Serial.println(x1); // print that second char to check if everything is ok
      tm1637.display(2,x1-'0');// display the char attached to x1 on the second digit
      tm1637.display(3,12);
      tm1637.display(0,14);
      inputString = "";
    }
  }*/


  int B = 3975;                                 // B value of the thermistor



  int analogValue = analogRead(TEMPPIN);        // read rotary pin
  float resistance=(float)(4095-analogValue)*10000/analogValue;   //get the resistance of the sensor
  float temperature=1/(log(resistance/10000)/B+1/298.15)-273.15;  //convert to temperature via datasheet
  if (debugMode){
  /*Serial.print("analogValue: ");
  Serial.println(analogValue);
  Serial.print("resistance: ");
  Serial.println(resistance);*/
  Serial.print("temperature: ");
  Serial.println(temperature);
  Serial.println("");
}
  dispNum((unsigned int) (temperature + 0.5));  // display the voltage
  tempC = ((String) (temperature + 0.5));
  tempCDisplay = (String) (roundf((temperature + 0.5) * 100) / 100);

  //// if connected to cloud then
  if (Spark.connected()){
    //ONLY PUBLISH EVERY X Time
    // difference between the current time and last time you blinked
      // the LED is bigger than the interval at which you want to
      // blink the LED.

      unsigned long currentMillis = millis();

      if(currentMillis - previousMillis > interval) {
        // save the last time you blinked the LED
        previousMillis = currentMillis;
        Spark.publish("temperature",tempC);

      ///snprintf(payload, sizeof(payload), "{ \"s\":\"wthr\", \"u\":\"F\",\"l\":\"%s\",\"m\":\"Temp\",\"o\":\"%s\",\"v\": %s,\"d\":\"%s\" }", Locn, Org,tempC, Disp);

      //String azurePayload = "{ \"s\":\"wthr\", \"u\":\"C\",\"l\":\"" + Locn +"\",\"m\":\"Temp\",\"o\":\"" + Org + "\",\"v\": " + tempC + ",\"d\":\"" + Disp + "\" }";
      //Spark.publish("ConnectTheDots", azurePayload);

      //publish to spark fun data hub
      postToPhant(tempC);

      // thing speak
      String _t = "{ \"t\" : " + tempC + "}";
      String _thingspeak = "{ \"t\" : " + tempC + "," + "\"pm25\" : " + _pm25 + "," + "\"pm10\" : " + _pm10 + "}";
      Spark.publish("ThingSpeak",_thingspeak);


      /*thing.addValue("temp",tempC);*/
      /*thing.send();*/

      //send via http client to ubidots
      // Request path and body can be set at runtime or at setup.
      request.hostname = "things.ubidots.com";
      request.port = 80;
      request.path = "/api/v1.6/variables/"VARIABLE_ID"/values";

      // The library also supports sending a body with your request:
      //request.body = "{\"key\":\"value\"}";

      // Send to Ubidots
      String resultstr;
      resultstr ="{\"value\": " + tempC + "}";

      Serial.print(" Ubidots : POST json\t" );
      Serial.println(resultstr);

      // Get request
      //http.get(request, response, headers);
      request.body = resultstr;
      http.post(request,response,headers);

      /*Serial.print("Application>\tResponse status: ");
      Serial.println(response.status);*/

      /*Serial.print("Application>\tHTTP Response Body: ");
      Serial.println(response.body);*/

//xively

/*Parameters
Method	PUT
Base URL	https://api.xively.com
API Endpoint	/v2/feeds/FEED_ID_HERE
Headers
X-ApiKey	API_KEY_HERE  NgBy45gL6dhhN3J6jQyRZJQUsmiNprBGDSiOXvlYIheQeKEH */
//payload
//<key>, <value> for csv type/

request.hostname = "api.xively.com";
request.port = 80;
request.path = "/v2/feeds/1211611330.json";

String sensorStr = "{\"version\":\"1.0.0\",\"datastreams\" : [ {\"id\" : \"temp\",\"current_value\" : " + tempC + "},{ \"id\" : \"pm10\",\"current_value\" : " + _pm10 + "},{ \"id\" : \"pm25\",\"current_value\" : " + _pm25 + "}]}";

request.body = sensorStr;
http.put(request,response,headers);

    }
  }
};

// display a integer value less then 10000
void dispNum(unsigned int num)
{

  ///if ((millis()-starttime) > sampletime_ms)//if the sampel time == 30s

  int8_t TimeDisp[] = {0x01,0x02,0x03,0x04};    // limit the maximum number
  tm1637.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  if(num > 9999) num = 9999;
  /*TimeDisp[0] = num / 1000;
  TimeDisp[1] = num % 1000 / 100;
  TimeDisp[2] = num % 100 / 10;
  TimeDisp[3] = num % 10;
  */
  //make the positions all blank ...
  int lcdchars[] = {16,16,16,16};
  lcdchars[0] = num % 100 / 10;
  lcdchars[1] = num % 10;
  lcdchars[2] = 12;
  lcdchars[3] = 16;

  uint8_t i,count1 = 0;
  for(i=0;i<7;i++){
    //assign the positions...
    if(i == 0){
      TimeDisp[0] = lcdchars[0];
      TimeDisp[1] = lcdchars[1];
      TimeDisp[2] = lcdchars[2];
      TimeDisp[3] = lcdchars[3];
    }
    if(i == 1){
      TimeDisp[0] = 16;
      TimeDisp[1] = lcdchars[0];
      TimeDisp[2] = lcdchars[1];
      TimeDisp[3] = lcdchars[2];
    }
    if(i == 2){
      TimeDisp[0] = 16;
      TimeDisp[1] = 16;
      TimeDisp[2] = lcdchars[0];
      TimeDisp[3] = lcdchars[1];
    }
    if(i == 3){
      TimeDisp[0] = 16;
      TimeDisp[1] = 16;
      TimeDisp[2] = 16;
      TimeDisp[3] = lcdchars[0];
    }
    if(i == 4){
      TimeDisp[0] = 16;
      TimeDisp[1] = 16;
      TimeDisp[2] = 16;
      TimeDisp[3] = 16;
    }
    if(i == 5){
      TimeDisp[0] = lcdchars[2];
      TimeDisp[1] = lcdchars[3];
      TimeDisp[2] = 16;
      TimeDisp[3] = 16;
    }
    if(i == 6){
      TimeDisp[0] = lcdchars[1];
      TimeDisp[1] = lcdchars[2];
      TimeDisp[2] = lcdchars[3];
      TimeDisp[3] = 16;
    }
    /*tm1637.clearDisplay();*/
    tm1637.display(TimeDisp);
    delay(500);
  }


};


//POST TO SPARK FUN DATA HUB
int postToPhant(String tempC)
{
phant.add("temp", tempC );

TCPClient client;
char response[512];
int i = 0;
int retVal = 0;

if (client.connect(server, 80)) // Connect to the server
{
// Post message to indicate connect success
  /*Serial.println("Posting!");*/

// phant.post() will return a string formatted as an HTTP POST.
// It'll include all of the field/data values we added before.
// Use client.print() to send that string to the server.
  client.print(phant.post());
  delay(1000);
// Now we'll do some simple checking to see what (if any) response
// the server gives us.
  while (client.available())
  {
      char c = client.read();
      /*Serial.print(c);	// Print the response for debugging help.*/
      if (i < 512)
          response[i++] = c; // Add character to response string
  }
// Search the response string for "200 OK", if that's found the post
// succeeded.
  if (strstr(response, "200 OK"))
  {
      /*Serial.println("Post success!");*/
      retVal = 1;
  }
  else if (strstr(response, "400 Bad Request"))
  {	// "400 Bad Request" means the Phant POST was formatted incorrectly.
// This most commonly ocurrs because a field is either missing,
// duplicated, or misspelled.
      Serial.println("Bad request");
      retVal = -1;
  }
  else
  {
// Otherwise we got a response we weren't looking for.
      retVal = -2;
  }
}
else
{	// If the connection failed, print a message:
  Serial.println("connection failed");
  retVal = -3;
}
client.stop();	// Close the connection to server.
return retVal;	// Return error (or success) code.
};
