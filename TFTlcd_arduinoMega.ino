#include <UTouch.h>
#include <UTouchCD.h>
#define TOUCH_ORIENTATION  LANDSCAPE

#include <UTFT_Buttons.h>

#include <UTFT.h>
#include <avr/pgmspace.h>
#include <SoftwareSerial.h>
long int bdata;

extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

int button1on = 0; // this will be used as a flag for button1 
int button2on = 0;// this will be used as a flag for button2 and so on
int button3on = 0; 
int button4on = 0;

int alert1 = 0; // this will be used as a flag


int relay1 = 13;
int relay2 = 12; 
int relay3 = 11; 
int relay4 = 10; 


int sensor1 = A1; // Sensor connected with A0 of the Mega

int x, y;

char stCurrent[20]="";
int stCurrentLen=0;
char stLast[20]="";

int bg[] = {
  0, 0, 255};

int fg[] = {
  255, 255, 255};
UTFT myGLCD(ITDB50, 38,39,40,41);   // Remember to change the model parameter to suit your display module!
UTouch        myTouch(6,5,4,3,2);

extern unsigned int a0[0x76C];
extern unsigned int a1[0x76C];
extern unsigned int a2[0x76C];
extern unsigned int a3[0x76C];
extern unsigned int a4[0x76C];
extern unsigned int a5[0x76C];
extern unsigned int a6[0x76C];
extern unsigned int a7[0x76C];
extern unsigned int a8[0x76C];
extern unsigned int a9[0x76C];


int scale = 3; // for the pic size to make it large or small

// for specifying the upper left x coordinates and y coordinates for buttons. 
// as the buttons will be displayed in the same row so the x values will be different and the y values will be the same. 
int imagex = 100; //for digit1
int imagey = 200; // for digit1

int imagex2 = 250; // for digit 2
int imagey2 = 200; // for digit2

int imagex3 = 400;// for digit 3
int imagey3 = 200;// for digit 3





// for button1 
int button1x1 = 10; // 90
int button1y1 = 20; // 180
int button1x2 = 140; // 220
int button1y2 = 80; // 230

// for button2 
int button2x1 = 160; // 160
int button2y1 = 20; // 20
int button2x2 = 290; // 290
int button2y2 = 80; // 80

// for button3 
int button3x1 = 310; // 310
int button3y1 = 20; // 20
int button3x2 = 450; // 450
int button3y2 = 80; // 80

// for button4 
int button4x1 = 470; // 160
int button4y1 = 20; // 20
int button4x2 = 610; // 290
int button4y2 = 80; // 80


int data1 = 0;

// new code

// on off codes for device1 
long int password1 = 555;// to on 
long int password2 = 551;// to off 
//device2
long int password3 = 777; // TO TURN ON
long int password31 = 222; // to turn off
//device3
long int password4 = 221; // to turn on 
long int password41 = 444; // to turn off
//device4
long int password5 = 441; // to turn on 
long int password51 = 888; // to turn off
// new code end

// Finally we set up UTFT_Buttons :)
void drawButtons()
{
// Draw the upper row of buttons
   myGLCD.setColor(bg[0], bg[1], bg[2]);
  myGLCD.fillRoundRect (button1x1, button1y1, button1x2, button1y2);
  myGLCD.setColor(fg[0], fg[1], fg[2]);
  myGLCD.drawRoundRect (button1x1, button1y1, button1x2, button1y2);
  myGLCD.print(" ON", 50, 40); // 115, 195
  myGLCD.setBackColor (0, 0, 255);
  
  // button2 codding
    myGLCD.setColor(bg[0], bg[1], bg[2]);
  myGLCD.fillRoundRect (button2x1, button2y1, button2x2, button2y2);
  myGLCD.setColor(fg[0], fg[1], fg[2]);
  myGLCD.drawRoundRect (button2x1, button2y1, button2x2, button2y2);
  myGLCD.print(" ON", 200, 40); // 115, 195
  myGLCD.setBackColor (0, 0, 255); 
  
    // button3 codding
    myGLCD.setColor(bg[0], bg[1], bg[2]);
  myGLCD.fillRoundRect (button3x1, button3y1, button3x2, button3y2);
  myGLCD.setColor(fg[0], fg[1], fg[2]);
  myGLCD.drawRoundRect (button3x1, button3y1, button3x2, button3y2);
  myGLCD.print(" ON", 350, 40); // 115, 195
  myGLCD.setBackColor (0, 0, 255); 
  
      // button4 codding
    myGLCD.setColor(bg[0], bg[1], bg[2]);
  myGLCD.fillRoundRect (button4x1, button4y1, button4x2, button4y2);
  myGLCD.setColor(fg[0], fg[1], fg[2]);
  myGLCD.drawRoundRect (button4x1, button4y1, button4x2, button4y2);
  myGLCD.print(" ON", 500, 40); // 115, 195
  myGLCD.setBackColor (0, 0, 255); 

myGLCD.setColor(fg[1], fg[3], fg[6]);
 myGLCD.setBackColor (0, 0, 0); 
  myGLCD.print("Device1", 10, 100);
  myGLCD.print("Device2", 160, 100);
  myGLCD.print("Device3", 310, 100);
  myGLCD.print("Device4", 470, 100);
// for line   
  myGLCD.drawRect(10, 120, 610, 124);
  myGLCD.setColor(fg[0], fg[1], fg[2]); // white
  myGLCD.fillRect(10, 120, 610, 124);
  
// for large rectangle 

  myGLCD.drawRect(10, 130, 610, 450);
  myGLCD.setColor(fg[255], fg[255], fg[255]);
  myGLCD.fillRect(10, 130, 610, 450);
  
  // for right side rectangle for Alerts display
  myGLCD.drawRect(615, 10, 800, 450);
  myGLCD.setColor(fg[50], fg[1], fg[2]);
  myGLCD.fillRect(615, 10, 800, 450); 
 myGLCD.print("A L E R T S", 620, 20);
  
// rooms making 

myGLCD.drawBitmap (imagex, imagey, 50, 38, a0, scale); // first digit
myGLCD.drawBitmap (imagex2, imagey2, 50, 38, a0, scale); // second digit
myGLCD.drawBitmap (imagex3, imagey3, 50, 38, a0, scale); // second digit


}

void setup()
{
  
  Serial.begin(9600);
  Serial3.begin(9600); // bluetooth module connected here
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  pinMode(relay4,OUTPUT);
  
  // keep all the relays off 
  
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay4, LOW);
  
  
  pinMode(sensor1, INPUT);
// Initial setup
  myGLCD.InitLCD();
  myGLCD.clrScr();

  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);

  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(0, 0, 255);
  drawButtons(); 
  
}

void loop()
{
   while (true)
  {

    if (myTouch.dataAvailable())
    {
      myTouch.read();
      x=myTouch.getX();
      y=myTouch.getY();
      
    // FOR BUTTON1   
        if ((x>=button1x1 && x<=button1x2 && y >=button1y1 && y<=button1y2)&&(button1on == 0)  )  // Button: Enter
    {
      waitForIt(button1x1, button1y1, button1x2, button1y2); 
        myGLCD.setColor(bg[0], bg[1], bg[2]);
  myGLCD.fillRoundRect (button1x1, button1y1, button1x2, button1y2);
  myGLCD.setColor(fg[0], fg[1], fg[2]);
  myGLCD.drawRoundRect (button1x1, button1y1, button1x2, button1y2);
  myGLCD.print(" OFF", 50, 40);
  myGLCD.setBackColor (0, 0, 255); 
  Serial.println("Device1 ON");
    Serial3.println("Device1 ON");
   digitalWrite(relay1,HIGH);
   button1on = 1;
   x=0;
   y=0;
   
   delay(1000);
    } 
            if ((x>=button1x1 && x<=button1x2 && y >=button1y1 && y<=button1y2)&&(button1on == 1)  )  // Button: Enter
    {
      waitForIt(button1x1, button1y1, button1x2, button1y2); 
        myGLCD.setColor(bg[0], bg[1], bg[2]);
  myGLCD.fillRoundRect (button1x1, button1y1, button1x2, button1y2);
  myGLCD.setColor(fg[0], fg[1], fg[2]);
  myGLCD.drawRoundRect (button1x1, button1y1, button1x2, button1y2);
  myGLCD.print(" ON", 50, 40);
  myGLCD.setBackColor (0, 0, 255); 
   Serial.println("Device1 off");
     Serial3.println("Device1 off");
   digitalWrite(relay1,LOW);
   button1on = 0;
   x=0;
   y=0;
   
   delay(1000);
    }
// for button2 

        if ((x>=button2x1 && x<=button2x2 && y >=button2y1 && y<=button2y2)&&(button2on == 0)  )  // Button: Enter
    {
      waitForIt(button2x1, button2y1, button2x2, button2y2); 
        myGLCD.setColor(bg[0], bg[1], bg[2]);
  myGLCD.fillRoundRect (button2x1, button2y1, button2x2, button2y2);
  myGLCD.setColor(fg[0], fg[1], fg[2]);
  myGLCD.drawRoundRect (button2x1, button2y1, button2x2, button2y2);
  myGLCD.print(" OFF", 200, 40);
  myGLCD.setBackColor (0, 0, 255); 
   Serial.println("Device2 ON");
   digitalWrite(relay2,HIGH);
   button2on = 1;
   x=0;
   y=0;
   
   delay(1000);
    }
              if ((x>=button2x1 && x<=button2x2 && y >=button2y1 && y<=button2y2)&&(button2on == 1)  )  // Button: Enter
    {
      waitForIt(button2x1, button2y1, button2x2, button2y2); 
        myGLCD.setColor(bg[0], bg[1], bg[2]);
  myGLCD.fillRoundRect (button2x1, button2y1, button2x2, button2y2);
  myGLCD.setColor(fg[0], fg[1], fg[2]);
  myGLCD.drawRoundRect (button2x1, button2y1, button2x2, button2y2);
  myGLCD.print(" ON", 200, 40);
  myGLCD.setBackColor (0, 0, 255); 
   Serial.println("Device2 off");
   digitalWrite(relay2,LOW);
   button2on = 0;
   x=0;
   y=0;
   
   delay(1000);
    }
  
  // for button3 

        if ((x>=button3x1 && x<=button3x2 && y >=button3y1 && y<=button3y2)&&(button3on == 0)  )  // Button: Enter
    {
      waitForIt(button3x1, button3y1, button3x2, button3y2); 
        myGLCD.setColor(bg[0], bg[1], bg[2]);
  myGLCD.fillRoundRect (button3x1, button3y1, button3x2, button3y2);
  myGLCD.setColor(fg[0], fg[1], fg[2]);
  myGLCD.drawRoundRect (button3x1, button3y1, button3x2, button3y2);
  myGLCD.print(" OFF", 350, 40);
  myGLCD.setBackColor (0, 0, 255); 
   Serial.println("Device3 ON");
   digitalWrite(relay3,HIGH);
   button3on = 1;
   x=0;
   y=0;
   
   delay(1000);
    }
              if ((x>=button3x1 && x<=button3x2 && y >=button3y1 && y<=button3y2)&&(button3on == 1)  )  // Button: Enter
    {
      waitForIt(button3x1, button3y1, button3x2, button3y2); 
        myGLCD.setColor(bg[0], bg[1], bg[2]);
  myGLCD.fillRoundRect (button3x1, button3y1, button3x2, button3y2);
  myGLCD.setColor(fg[0], fg[1], fg[2]);
  myGLCD.drawRoundRect (button3x1, button3y1, button3x2, button3y2);
  myGLCD.print(" ON", 350, 40);
  myGLCD.setBackColor (0, 0, 255); 
   Serial.println("Device3 off");
   digitalWrite(relay3,LOW);
   button3on = 0;
   x=0;
   y=0;
   
   delay(1000);
    }
    
    // for button4 

        if ((x>=button4x1 && x<=button4x2 && y >=button4y1 && y<=button4y2)&&(button4on == 0)  )  // Button: Enter
    {
      waitForIt(button4x1, button4y1, button4x2, button4y2); 
        myGLCD.setColor(bg[0], bg[1], bg[2]);
  myGLCD.fillRoundRect (button4x1, button4y1, button4x2, button4y2);
  myGLCD.setColor(fg[0], fg[1], fg[2]);
  myGLCD.drawRoundRect (button4x1, button4y1, button4x2, button4y2);
  myGLCD.print(" OFF", 500, 40);
  myGLCD.setBackColor (0, 0, 255); 
   Serial.println("Device4 ON");
   digitalWrite(relay4,HIGH);
   button4on = 1;
   x=0;
   y=0;
   
   delay(1000);
    }
          if ((x>=button4x1 && x<=button4x2 && y >=button4y1 && y<=button4y2)&&(button4on == 1)  )  // Button: Enter
    {
      waitForIt(button4x1, button4y1, button4x2, button4y2); 
        myGLCD.setColor(bg[0], bg[1], bg[2]);
  myGLCD.fillRoundRect (button4x1, button4y1, button4x2, button4y2);
  myGLCD.setColor(fg[0], fg[1], fg[2]);
  myGLCD.drawRoundRect (button4x1, button4y1, button4x2, button4y2);
  myGLCD.print(" ON", 500, 40);
  myGLCD.setBackColor (0, 0, 255); 
   Serial.println("Device4 Off");
   digitalWrite(relay4,LOW);
   button4on = 0;
   x=0;
   y=0;
   
   delay(1000);
    }
             
    
 
 
    }
    

int sensor, data, d1,d2,d3; 
sensor = analogRead(sensor1); // any sensor 
// new code from here 
myGLCD.setBackColor(0,0,0);
    myGLCD.setColor(fg[0], fg[1], fg[2]); // for white color
  if( sensor > 600  &&  alert1 == 1 ) 
  { 
    myGLCD.print("Sensor1:", 620, 80);
    myGLCD.print("exceeded", 640, 100);
    alert1 = 0;
  }
    if( sensor < 600  &&  alert1 == 0 ) 
  { 
    myGLCD.print("Sensor1:", 620, 80);
    myGLCD.print("Normal  ", 640, 100);
    alert1 = 1;
  }
Serial.println(sensor); // send sensor value to bluetooth
Serial3.println(sensor); 
// new code end here
data = sensor / 10;
d3 = sensor % 10;
d2 = data % 10;
d1 = data / 10;

// for digit3
if ( d3 == 0)
myGLCD.drawBitmap (imagex3, imagey3, 50, 38, a0, scale); 
if ( d3 == 1)
myGLCD.drawBitmap (imagex3, imagey3, 50, 38, a1, scale); 
if ( d3 == 2)
myGLCD.drawBitmap (imagex3, imagey3, 50, 38, a2, scale); 
if ( d3 == 3)
myGLCD.drawBitmap (imagex3, imagey3, 50, 38, a3, scale);
if ( d3 == 4)
myGLCD.drawBitmap (imagex3, imagey3, 50, 38, a4, scale); 
if ( d3 == 5)
myGLCD.drawBitmap (imagex3, imagey3, 50, 38, a5, scale); 
if ( d3 == 6)
myGLCD.drawBitmap (imagex3, imagey3, 50, 38, a6, scale); 
if ( d3 == 7)
myGLCD.drawBitmap (imagex3, imagey3, 50, 38, a7, scale); 
if ( d3 == 8)
myGLCD.drawBitmap (imagex3, imagey3, 50, 38, a8, scale); 
if ( d3 == 9)
myGLCD.drawBitmap (imagex3, imagey3, 50, 38, a9, scale); 

// for 2nd digit


if ( d2 == 0)
myGLCD.drawBitmap (imagex2, imagey2, 50, 38, a0, scale); // second digit
if ( d2 == 1)
myGLCD.drawBitmap (imagex2, imagey2, 50, 38, a1, scale); // second digit
if ( d2 == 2)
myGLCD.drawBitmap (imagex2, imagey2, 50, 38, a2, scale); // second digit
if ( d2 == 3)
myGLCD.drawBitmap (imagex2, imagey2, 50, 38, a3, scale); // second digit
if ( d2 == 4)
myGLCD.drawBitmap (imagex2, imagey2, 50, 38, a4, scale); // second digit
if ( d2 == 5)
myGLCD.drawBitmap (imagex2, imagey2, 50, 38, a5, scale); // second digit
if ( d2 == 6)
myGLCD.drawBitmap (imagex2, imagey2, 50, 38, a6, scale); // second digit
if ( d2 == 7)
myGLCD.drawBitmap (imagex2, imagey2, 50, 38, a7, scale); // second digit
if ( d2 == 8)
myGLCD.drawBitmap (imagex2, imagey2, 50, 38, a8, scale); // second digit
if ( d2 == 9)
myGLCD.drawBitmap (imagex2, imagey2, 50, 38, a9, scale); // second digit

// for the first digit
if ( d1 == 0)
myGLCD.drawBitmap (imagex, imagey, 50, 38, a0, scale); 
if ( d1 == 1)
myGLCD.drawBitmap (imagex, imagey, 50, 38, a1, scale); 
if ( d1 == 2)
myGLCD.drawBitmap (imagex, imagey, 50, 38, a2, scale); 
if ( d1 == 3)
myGLCD.drawBitmap (imagex, imagey, 50, 38, a3, scale); 
if ( d1 == 4)
myGLCD.drawBitmap (imagex, imagey, 50, 38, a4, scale); 
if ( d1 == 5)
myGLCD.drawBitmap (imagex, imagey, 50, 38, a5, scale); 
if ( d1 == 6)
myGLCD.drawBitmap (imagex, imagey, 50, 38, a6, scale);
if ( d1 == 7)
myGLCD.drawBitmap (imagex, imagey, 50, 38, a7, scale); 
if ( d1 == 8)
myGLCD.drawBitmap (imagex, imagey, 50, 38, a8, scale); 
if ( d1 == 9)
myGLCD.drawBitmap (imagex, imagey, 50, 38, a9, scale);

 if(Serial3.available()>0) 
{
bdata = Serial3.parseInt();

//delay(200);
Serial.print(bdata);

if (bdata == password1)
{
      waitForIt(button1x1, button1y1, button1x2, button1y2); 
        myGLCD.setColor(bg[0], bg[1], bg[2]);
  myGLCD.fillRoundRect (button1x1, button1y1, button1x2, button1y2);
  myGLCD.setColor(fg[0], fg[1], fg[2]);
  myGLCD.drawRoundRect (button1x1, button1y1, button1x2, button1y2);
  myGLCD.print(" OFF", 50, 40);
  myGLCD.setBackColor (0, 0, 255); 
  Serial.println("Device1 ON");
    Serial3.println("Device1 ON");
   digitalWrite(relay1,HIGH);
   button1on = 1;
   x=0;
   y=0;
   
   delay(1000);

   }
   
   if( bdata == password2)
   {
      waitForIt(button1x1, button1y1, button1x2, button1y2); 
        myGLCD.setColor(bg[0], bg[1], bg[2]);
  myGLCD.fillRoundRect (button1x1, button1y1, button1x2, button1y2);
  myGLCD.setColor(fg[0], fg[1], fg[2]);
  myGLCD.drawRoundRect (button1x1, button1y1, button1x2, button1y2);
  myGLCD.print(" ON", 50, 40);
  myGLCD.setBackColor (0, 0, 255); 
   Serial.println("Device1 off");
     Serial3.println("Device1 off");
   digitalWrite(relay1,LOW);
   button1on = 0;
   x=0;
   y=0;
   
   delay(1000);
   } 

 if (bdata == password3  )  // Button: Enter
    {
      waitForIt(button2x1, button2y1, button2x2, button2y2); 
        myGLCD.setColor(bg[0], bg[1], bg[2]);
  myGLCD.fillRoundRect (button2x1, button2y1, button2x2, button2y2);
  myGLCD.setColor(fg[0], fg[1], fg[2]);
  myGLCD.drawRoundRect (button2x1, button2y1, button2x2, button2y2);
  myGLCD.print(" OFF", 200, 40);
  myGLCD.setBackColor (0, 0, 255); 
   Serial.println("Device2 ON");
   Serial3.println("Device2 ON"); 
   digitalWrite(relay2,HIGH);
   button2on = 1;
   x=0;
   y=0;
   
   delay(1000);
    }
              if (bdata == password31  )  // Button: Enter
    {
      waitForIt(button2x1, button2y1, button2x2, button2y2); 
        myGLCD.setColor(bg[0], bg[1], bg[2]);
  myGLCD.fillRoundRect (button2x1, button2y1, button2x2, button2y2);
  myGLCD.setColor(fg[0], fg[1], fg[2]);
  myGLCD.drawRoundRect (button2x1, button2y1, button2x2, button2y2);
  myGLCD.print(" ON", 200, 40);
  myGLCD.setBackColor (0, 0, 255); 
   Serial.println("Device2 off");
   Serial3.println("Device2 off"); 
   digitalWrite(relay2,LOW);
   button2on = 0;
   x=0;
   y=0;
   
   delay(1000);
    }
  
  // for button3 

        if (bdata == password4 )  // Button: Enter
    {
      waitForIt(button3x1, button3y1, button3x2, button3y2); 
        myGLCD.setColor(bg[0], bg[1], bg[2]);
  myGLCD.fillRoundRect (button3x1, button3y1, button3x2, button3y2);
  myGLCD.setColor(fg[0], fg[1], fg[2]);
  myGLCD.drawRoundRect (button3x1, button3y1, button3x2, button3y2);
  myGLCD.print(" OFF", 350, 40);
  myGLCD.setBackColor (0, 0, 255); 
   Serial.println("Device3 ON");
   Serial3.println("Device3 ON"); 
   digitalWrite(relay3,HIGH);
   button3on = 1;
   x=0;
   y=0;
   
   delay(1000);
    }
              if (bdata == password41 )  // Button: Enter
    {
      waitForIt(button3x1, button3y1, button3x2, button3y2); 
        myGLCD.setColor(bg[0], bg[1], bg[2]);
  myGLCD.fillRoundRect (button3x1, button3y1, button3x2, button3y2);
  myGLCD.setColor(fg[0], fg[1], fg[2]);
  myGLCD.drawRoundRect (button3x1, button3y1, button3x2, button3y2);
  myGLCD.print(" ON", 350, 40);
  myGLCD.setBackColor (0, 0, 255); 
   Serial.println("Device3 off");
   Serial.println("Device3 Off");
   digitalWrite(relay3,LOW);
   button3on = 0;
   x=0;
   y=0;
   
   delay(1000);
    }
    
    // for button4 

        if (bdata == password5 )  // Button: Enter
    {
      waitForIt(button4x1, button4y1, button4x2, button4y2); 
        myGLCD.setColor(bg[0], bg[1], bg[2]);
  myGLCD.fillRoundRect (button4x1, button4y1, button4x2, button4y2);
  myGLCD.setColor(fg[0], fg[1], fg[2]);
  myGLCD.drawRoundRect (button4x1, button4y1, button4x2, button4y2);
  myGLCD.print(" OFF", 500, 40);
  myGLCD.setBackColor (0, 0, 255); 
   Serial.println("Device4 ON");
   Serial.println("Device4 ON");
   digitalWrite(relay4,HIGH);
   button4on = 1;
   x=0;
   y=0;
   
   delay(1000);
    }
          if (bdata == password51  )  // Button: Enter
    {
      waitForIt(button4x1, button4y1, button4x2, button4y2); 
        myGLCD.setColor(bg[0], bg[1], bg[2]);
  myGLCD.fillRoundRect (button4x1, button4y1, button4x2, button4y2);
  myGLCD.setColor(fg[0], fg[1], fg[2]);
  myGLCD.drawRoundRect (button4x1, button4y1, button4x2, button4y2);
  myGLCD.print(" ON", 500, 40);
  myGLCD.setBackColor (0, 0, 255); 
   Serial.println("Device4 Off");
   Serial.println("Device4 Off");
   digitalWrite(relay4,LOW);
   button4on = 0;
   x=0;
   y=0;
   
   delay(1000);
    }
             
   
   
}

    } 
    
}




void waitForIt(int x1, int y1, int x2, int y2)
{
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  while (myTouch.dataAvailable()){
  }
  delay(20);

  
  // list all files in the card with date and size

  myGLCD.setColor(fg[0], fg[1], fg[2]);
  myGLCD.drawRoundRect (x1, y1, x2, y2); 
}
