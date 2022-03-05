#include <SPI.h>
#include <PDLS_EXT3_Basic.h>
//#include "G:/temp/arduino/sketch/pipico_sketch_epaper_bmp/globalupdate_src/demoImageData.h"
#include "G:/temp/arduino/sketch/pipico_sketch_epaper_bmp/globalupdate_src/userimageData.h"

Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_417, boardRaspberryPiPico_RP2040);
//Screen_EPD_EXT3 myScreen(eScreen_EPD_EXT3_417, boardESP8266);
// Prototypes

void wait(uint8_t second)
{
    for (uint8_t i = second; i > 0; i--)
    {
        Serial.print(formatString(" > %i  \r", i));
        delay(1000);
    }
    Serial.print("         \r");
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


void bmpPopulate(uint8_t offsetX, uint8_t offsetY, uint8_t *icon)
{
  myScreen.setOrientation(7);
  //const char check = '1';
  //uint8_t offsetX = 100;
  //uint8_t offsetY =120;
  //uint8_t tpx = 0;
  //uint8_t tpy = 0; 
  
  uint8_t (*a)[128] = ( uint8_t (*)[128]) icon;
   
  for (uint8_t x = 0;  x < 128; x++)
  {
    for(uint8_t y = 0; y < 128; y++)
    {
      //Serial.println(* BW_rain_mono[x][y]);
      //if (* BW_unknown_mono[y][x] == 1)
      if ( a[y][x] == 1)
      {
        //epaperscreen index starts (1,1) top left to (400,300)
        myScreen.point(x+1+offsetX, y+1+offsetY, myColours.black);
                
      }
    }
  }

 myScreen.flush();
   
}



void setup()
{
    delay(500);
    Serial.println();
    Serial.println("=== " __FILE__);
    Serial.println("=== " __DATE__ " " __TIME__);
    Serial.println();

    Serial.print("begin... ");
    myScreen.begin();
    Serial.println(formatString("%s %ix%i", myScreen.WhoAmI().c_str(), myScreen.screenSizeX(), myScreen.screenSizeY()));

    Serial.print("Palettes... ");
    myScreen.clear();
    //displayPalette();
    wait(8);

    Serial.print("White... ");
    myScreen.clear();
    myScreen.flush();
    
    uint16_t offsetX = 100;
    uint16_t offsetY = 120;
    String text1 = "Venus wakeeee uuuup!";
    String text2 = "it's time for coffee.....";
    
   /*

    offsetX = 180;
    offsetY = 120;

    

    offsetX  = 240;
    offsetY = 120;
    */
    myScreen.selectFont(Font_Terminal12x16);
    myScreen.gText(10, 50, text1 , myColours.red);
    myScreen.gText(10, 80, text2 , myColours.black);
    
    //myScreen.flush(); // have to decided what to do as flush sends the whole display memory up to the display???

    Serial.println("=== ");
    Serial.println();

#if defined(ARDUINO_ARCH_PIDUINO)
    exit(0);
#endif

}

// Add loop code
///
/// @brief Loop, empty
///
void loop()
{
     bmpPopulate(90,120,BW_hot_coffee128_mono);
     //bmpPopulate(100,120,BW_bear_toy128_mono);
     //bmpPopulate(200,120,BW_teddy_bear128_mono);
     myScreen.flush();
     Serial.println("bmpPopulate end");
    delay(3000);
    delay(3000);
    delay(3000);
    delay(3000);
    delay(3000);
}

   
