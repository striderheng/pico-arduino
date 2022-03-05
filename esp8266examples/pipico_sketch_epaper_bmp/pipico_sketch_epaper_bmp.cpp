#include <Arduino.h>
//#include <PDLS_EXT3_Basic.h> //don't need since included under the pico-arduino umbrella of libraries to be included, see cmake list files
#include "globalupdate_src/demoImageData.h"
#include <time.h>

Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_417, boardRaspberryPiPico_RP2040);

// Prototypes

// Utilities
///
/// @brief Wait with countdown
/// @param second duration, s
///
void wait(uint8_t second)
{
    for (uint8_t i = second; i > 0; i--)
    {
        Serial.print(formatString(" > %i  \r", i));
        delay(1000);
    }
    Serial.print("         \r");
    Serial.println(" ");
}

// Functions
///
/// @brief Characters test screen
/// @param flag true = default = perform flush, otherwise no
///
/// @image html T2_CHARA.jpg
/// @image latex T2_CHARA.PDF width=10cm
///
void displayCharacters(bool flag = true)
{
    myScreen.setOrientation(7);
    uint16_t x = myScreen.screenSizeX(); // 17
    uint16_t y = myScreen.screenSizeY(); // 14

    // #if (USE_FONT_MODE == USE_FONT_TERMINAL)
    myScreen.selectFont(Font_Terminal8x12);
    // #elif (USE_FONT_MODE == USE_FONT_HEADER)
    //
    // #elif (USE_FONT_MODE == USE_FONT_FLASH)
    //
    // #else
    // #error USE_FONT_MODE not defined
    // #endif

    uint8_t k;
    String text;
    uint16_t dx;

    for (uint8_t i = 1; i < 17; i++)
    {
        myScreen.gText(i * x / 17, 0, formatString(".%x", (i - 1)), myColours.red);
    }
    for (uint8_t j = 2; j < 16; j++)
    {
        myScreen.gText(0, (j - 1)*y / 15, formatString("%x.", (j)), myColours.red);
    }

    for (uint16_t i = 1; i < 17; i++)
    {
        for (uint8_t j = 2; j < 16; j++)
        {
            k = (i - 1) + j * 16;

            text = (String)char(k);
            
            dx = i * x / 17 + (x / 17 - myScreen.stringSizeX(text)) / 2;
            myScreen.gText(dx, (j - 1)*y / 15, text, myColours.black);
        }
    }

    myScreen.flush();
}

void displayFonts(bool flag = true)
{
    uint16_t y = 10;
    myScreen.setOrientation(7);

    // #if (USE_FONT_MODE == USE_FONT_TERMINAL)
    myScreen.selectFont(Font_Terminal12x16);

    myScreen.gText(10, y, myScreen.WhoAmI(), myColours.red);
    y += myScreen.characterSizeY();
    myScreen.gText(10, y, formatString("%i x %i", myScreen.screenSizeX(), myScreen.screenSizeY()), myColours.red);
    y += myScreen.characterSizeY();
    y += myScreen.characterSizeY();

    myScreen.selectFont(Font_Terminal6x8);
    myScreen.gText(10, y, "Terminal6x8");
    y += myScreen.characterSizeY();

    myScreen.selectFont(Font_Terminal8x12);
    myScreen.gText(10, y, "Terminal8x12");
    y += myScreen.characterSizeY();

    myScreen.selectFont(Font_Terminal12x16);
    myScreen.gText(10, y, "Terminal12x16");
    y += myScreen.characterSizeY();

    myScreen.selectFont(Font_Terminal16x24);
    myScreen.gText(10, y, "Terminal16x24");
    y += myScreen.characterSizeY();

    // #elif (USE_FONT_MODE == USE_FONT_HEADER)
    //
    // #elif (USE_FONT_MODE == USE_FONT_FLASH)
    //
    // #else
    // #error USE_FONT_MODE not defined
    // #endif

    myScreen.flush();
}

void displayPalette(bool flag = true)
{
    myScreen.setOrientation(7);

    uint16_t x0, y0, dx, dy, maxSize, colour;
    maxSize = min((myScreen.screenSizeX() * 10 / 50), (myScreen.screenSizeY() * 10 / 35));
    dx = (myScreen.screenSizeX() - maxSize * 50 / 10) / 2;
    dy = (myScreen.screenSizeY() - maxSize * 35 / 10) / 2;

    y0 = dy + maxSize / 2;
    x0 = dx + maxSize / 2;
    myScreen.dRectangle(x0 - 2, y0 - 2, maxSize + 4, maxSize + 4, myColours.red);
    x0 = dx + maxSize * 4 / 2;
    myScreen.dRectangle(x0 - 2, y0 - 2, maxSize + 4, maxSize + 4, myColours.red);
    x0 = dx + maxSize * 7 / 2;
    myScreen.dRectangle(x0 - 2, y0 - 2, maxSize + 4, maxSize + 4, myColours.red);

    y0 = dy + maxSize * 4 / 2;
    x0 = dx + maxSize / 2;
    myScreen.dRectangle(x0 - 2, y0 - 2, maxSize + 4, maxSize + 4, myColours.black);
    x0 = dx + maxSize * 4 / 2;
    myScreen.dRectangle(x0 - 2, y0 - 2, maxSize + 4, maxSize + 4, myColours.black);
    x0 = dx + maxSize * 7 / 2;
    myScreen.dRectangle(x0 - 2, y0 - 2, maxSize + 4, maxSize + 4, myColours.black);

    myScreen.setPenSolid();
    myScreen.selectFont(Font_Terminal6x8);

    x0 = dx + maxSize / 2;
    y0 = dy + maxSize / 2;
    // Light red
    myScreen.dRectangle(x0, y0, maxSize, maxSize, myColours.lightRed);
    myScreen.gText(x0, y0 + maxSize + 6, "light", myColours.red);

    x0 = dx + maxSize * 4 / 2;
    y0 = dy + maxSize / 2;
    // Red
    myScreen.dRectangle(x0, y0, maxSize, maxSize, myColours.red);
    myScreen.gText(x0, y0 + maxSize + 6, "red", myColours.red);

    x0 = dx + maxSize * 7 / 2;
    y0 = dy + maxSize / 2;
    // Dark-red
    myScreen.dRectangle(x0, y0, maxSize, maxSize, myColours.darkRed);
    myScreen.gText(x0, y0 + maxSize + 6, "dark", myColours.red);

    x0 = dx + maxSize / 2;
    y0 = dy + maxSize * 4 / 2;
    // White
    myScreen.dRectangle(x0, y0, maxSize, maxSize, myColours.white);
    myScreen.gText(x0, y0 + maxSize + 6, "white", myColours.black);

    x0 = dx + maxSize * 4 / 2;
    y0 = dy + maxSize * 4 / 2;
    // Grey
    myScreen.dRectangle(x0, y0, maxSize, maxSize, myColours.grey);
    myScreen.gText(x0, y0 + maxSize + 6, "grey", myColours.black);

    x0 = dx + maxSize * 7 / 2;
    y0 = dy + maxSize * 4 / 2;
    // Black
    myScreen.dRectangle(x0, y0, maxSize, maxSize, myColours.black);
    myScreen.gText(x0, y0 + maxSize + 6, "black", myColours.black);

    myScreen.selectFont(Font_Terminal8x12);
    myScreen.gText(0, 0, myScreen.WhoAmI(), myColours.black);

    myScreen.flush();
}

void displayForms(bool flag = true)
{
    myScreen.setOrientation(6);

    uint16_t x = myScreen.screenSizeX();
    uint16_t y = myScreen.screenSizeY();
    uint16_t z = min(x, y);

    myScreen.setPenSolid(false);
    myScreen.dRectangle(0, 0, x, y, myColours.black);
    myScreen.dLine(0, 0, x, y, myColours.red);

    myScreen.setPenSolid(true);
    myScreen.circle(x / 3, y / 3, z / 4, myColours.grey);
    // myScreen.triangle(x*2/3, y/3, x/2, y*2/3, x*3/4, y*2/3-10, myColours.black);
    myScreen.triangle(x * 2 / 3, y / 3, x * 3 / 4, y * 2 / 3 - 10, x - 10, 10, myColours.black);
    myScreen.dRectangle(x / 3, y * 2 / 3, x / 3, y / 4, myColours.red);

    myScreen.flush();
}


void displaychar(bool flag = true)
{
    myScreen.setOrientation(7);
    uint16_t x = myScreen.screenSizeX(); // 17
    uint16_t y = myScreen.screenSizeY(); // 14

    myScreen.selectFont(Font_Terminal12x16);

    uint8_t i;
    String text;
    String text1 = "VENUS, FEEEEEED MEEEEEE!!!!";
    String text2 = " Who wants dumplings or semla";
    String text2b = "  or even char siew mee???";
    String text3 = "Reserve  with venus@gothenberg :)";
    String text4 = " come eat good food from CHEF VENUS!!";
    
    i = 1;
    /*myScreen.gText(i * x/17, 0, formatString(".%x", i), myColours.red);
    myScreen.gText(30, 0, text1 , myColours.red);
    myScreen.selectFont(Font_Terminal12x16);
    myScreen.gText(30, 30, text1 , myColours.red);
    myScreen.selectFont(Font_Terminal16x24);
    myScreen.gText(10, 60, text1 , myColours.red);
    */
    myScreen.selectFont(Font_Terminal12x16);
    myScreen.gText(5, 50, text2 , myColours.red);
    myScreen.gText(5, 80, text2b , myColours.red);
    myScreen.selectFont(Font_Terminal8x12);
    myScreen.gText(10, 120, text3 , myColours.lightRed);
    myScreen.gText(16, 200, text4 , myColours.black);

    
    text = (String)char(1);
    Serial.println(text);
    Serial.println(1 * x / 17);
    Serial.println(2 * x / 17);
    Serial.println(3 * x / 17);


    myScreen.flush();

}

void bmpPopulate(bool flag = true)
{
  const char check = '1';
  uint8_t offsetX = 100;
  uint8_t offsetY =120;
  
  for (uint8_t x = 0; x < 64; x++)
  {
    for(uint8_t y = 0; y < 64; y++)
    {
      //Serial.println(* BW_rain_mono[x][y]);
      if (* BW_rain_mono[x][y] == 1)
      {
        //epaperscreen index starts (1,1) top left to (400,300)
        myScreen.point(x+1+offsetX, y+1+offsetY, myColours.black);
        
        //uint8_t tpx = x + 100;
        //uint8_t tpy = y + 120; 
        //Serial.print("coord_X: ");
        //Serial.print(tpx);
        //Serial.print(" , coord_Y: ");
        //Serial.println(tpy);
      }
    }
  }

 myScreen.flush();
   
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(500);
  Serial.println("=== " __FILE__);
  Serial.println("=== " __DATE__ " " __TIME__);
  Serial.println();

  Serial.println("begin... ");
  myScreen.begin();
  Serial.println(formatString("%s %ix%i", myScreen.WhoAmI().c_str(), myScreen.screenSizeX(), myScreen.screenSizeY()));

  //Serial.println("Characters... ");
  //myScreen.clear();
  //displayCharacters();
  //wait(10);

  //Serial.println("White... ");
  myScreen.clear();
  //displaychar();
  myScreen.sendbmp(BW_martenBuffer, BW_0x00Buffer);
  //delay(1000);
  wait(10);
  myScreen.flush();
  

  //Serial.println("=== ");
  //Serial.println();

}


void loop() {
  // put your main code here, to run repeatedly:
  //delay(1000); //arduino fcn
  wait(30);  //inbuild func
  Serial.println("Loop start... ");
  /*myScreen.clear();
  Serial.println("Characters...");
  displayCharacters();
  wait(30);
  myScreen.clear();
  myScreen.flush();
  Serial.println("Fonts....");
  displayFonts();
  wait(30);
  myScreen.clear();
  myScreen.flush();
  Serial.println("Palette...");
  displayPalette();
  wait(30);
  myScreen.clear();
  myScreen.flush(); 
  Serial.println("Forms...");
  displayForms();
  wait(30);
  myScreen.clear();
  myScreen.flush(); 
  */
  //displaychar();
  //wait(30);
  //myScreen.clear();

  
  myScreen.clear();
  myScreen.flush();
  myScreen.sendbmp(BW_rolpiggyBuffer, BW_0x00Buffer);
  wait(30);
  myScreen.clear();
  myScreen.flush();
  myScreen.sendbmp(BW_martenBuffer, BW_0x00Buffer);
  
  Serial.println("looping...");

}
