/***************************************************************************************
****************************************************************************************

Project: DMX WS2811 Lights

Description: Controls a WS2811 based strands of LEDs via DMX input

DMX uses 3 inputs, default starting channel is 1:

 Channel 1 - Brightness
 Channel 2 - Pattern
 Channel 3 - Speed
    
Connections:

  Arduino:
    GND -> GND
    VIN -> VCC 

  WS2811:
    GND -> GND
    VCC -> VCC  
    DAT -> Digital 6
    
  MAX485 Module:
    DE/RE -> GND
    RO -> RX
    VCC -> 5V
    GND -> GND
  
  XLR/DMX Connections:
    1 - Signal   (A)
    2 - Inverted (B)
    3 - Ground   (GND)
  
Change log: 

Version 1.6.1 
  10/6/22 - Brian - Patched for Simplex overflow

Version 1.6
  7/4/29  - Brian - Ported back to DMX

Version 1.5
	6/15/19 - Brian - Smoothing of things :)
						Fixed several small glitches
						More fade control patterns 
						This was sent to Rob McAllister

Version 1.4
	6/13/19 - Matt/Brian - Refined programs, added robust speed knob support

Version 1.3 
	6/10/19 - Brian - Support for 150 pixels with Scaling

Version 1.2
	2/4/19 - Brian - Converted back to Rotary encoder/knobs
									 more color programs
									configurable SPEED knob (see config)
									STRAND TYPE IS BELOW CONFIG! GRB OR RGB

Version 1.1
  9/1/18 - Matt/Brian - More better functions

Version 1.0
  9/1/18 - Brian - Changed to DMX
				Patched overflow on Simplex Noise function (xoffset/yoffset)

Version 0.9
  12/10/16 - Matt/Brian - Created baseline code to interface with rotary encoder
                          and potentiometer. Ported simplex noise code and created
                          basic color changers and hues.
                          
Version 0.9.1                        
  12/13/16 - Matt       - Added more colors and refined rainbow/noise flows.

Version 0.9.2
  12/15/16 - Brian      - Optimized output code for higher frame rate    

Future Improvements:

  
  
****************************************************************************************
***************************************************************************************/

/***************************************************************************************
  Libraries
***************************************************************************************/
/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Adafruit_NeoPixel.h>	//WS type strips
#include <EEPROM.h>        		//Persistent Memory
#include <DMXSerial.h>			//DMX

/***************************************************************************************
  !!!! >>>>> LOOK HERE <<<<<< !!!! ------ S   E   T    U   P
***************************************************************************************/
#define maxPixels 105 	//Number of Pixels (add 1 extra for each level of upscaling)
#define upsample 2  	//1 = No Upsampling, up to maximum of 4
#define PIN 6			//Pin WS28XX strips are connected to
#define DMX_Channel 1

// >>>> ADVANCED STRIP AND COLOR ORDER SETTINGS <<<<<
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

// Example for RGB Ping Pong Balls:
Adafruit_NeoPixel strip = Adafruit_NeoPixel(maxPixels, PIN, NEO_RGB + NEO_KHZ800);

// Example for RGB Strip/Reel:
//	Adafruit_NeoPixel strip = Adafruit_NeoPixel(maxPixels, PIN, NEO_GRB + NEO_KHZ800);



/***************************************************************************************
  General Variables
***************************************************************************************/
int currBrightness = 0;
int tempValue = 0;
int brightnessValue = 0;
int currSpeed = 4;
int currProgram = 2;
int currFade = 0;
int currFadeStep = 0;
int currStep = 0;
int tempStepEffect = 0;
int tempProgram = 2;
int antiBounce = 0;
long brightnessTotal = 0;
int brightnessCount = 0;
byte tempStepDirection = 0;

int fadeDirection = 0; // 1 or 0, positive or negative
int fadeDirection2 = 0; // 1 or 0, positive or negative
int fadeDirectionHTemp = .5; // 1 or 0, positive or negative

unsigned long fpsMillis = 0;
unsigned long effectMillis = 0;
unsigned long currMillis = 0;
unsigned long antiSpam = 0;
int brightnessRead = 0;


/***********************************************************
  Simplex Noise Variable Declaration
***********************************************************/
//Define simplex noise node for each LED
const int LEDs_in_strip = (maxPixels / upsample)+1;
const int LEDs_for_simplex = 6;

// Extra fake LED at the end, to avoid fencepost problem.
// It is used by simplex node and interpolation code.
float LED_array_red[LEDs_in_strip+1];
float LED_array_green[LEDs_in_strip+1];
float LED_array_blue[LEDs_in_strip+1];
int node_spacing = LEDs_in_strip / LEDs_for_simplex;

// Math variables
int i, j, k, A[] = {0, 0, 0};
float x1,y1,x2,y2;
float u, v, w, s, h;
float hTemp = .420;
float hOld = .0;
static float onethird = 0.333333333;
static float onesixth = 0.166666667;
int T[] = {0x15, 0x38, 0x32, 0x2c, 0x0d, 0x13, 0x07, 0x2a};

// Simplex noise parameters:
float timeinc = 0.0025;
float spaceinc = 0.05;
int intensity_r = 734;
int intensity_g = 734;
int intensity_b = 734;
float yoffset = 0.0;
float xoffset = 0.0;
float saturation = 1.0;
int red, green, blue;
int red2, green2, blue2;  //used in HSV color functions 
int red3, green3, blue3;
int tempStep = 0;

/***************************************************************************************
  Other Variables
***************************************************************************************/


/***************************************************************************************
  Setup
***************************************************************************************/
void setup()
{
  /***************************************************************************************
    General Setup
  ***************************************************************************************/

	//Randomize the Simplex Noise values for lava lamp style patterns
	//Create a random seed by reading nearby electric noise on the analog ports
	randomSeed(analogRead(A6) + analogRead(A2) + analogRead(A3) + analogRead(A4) + analogRead (A5));
	
 	//Randomish x and y offset for simplex noise
 	yoffset = analogRead(A4) + analogRead (A5);
 	xoffset = analogRead(A5) + analogRead(A3);
	
 /***************************************************************************************
    DMX Setup
  ***************************************************************************************/
	DMXSerial.init(DMXProbe);
	DMXSerial.maxChannel(4);


 /***************************************************************************************
    Other Setup
  ***************************************************************************************/
	//Initialize up the LED strip
	strip.begin();
	
	//Display one frame to the the strip, to start they are all 'off'
	strip.show();

}

/***************************************************************************************
  Main Loop
***************************************************************************************/
void loop()
{

	//Framerate Control
	if (fpsMillis < millis())
  	{
		//1 second = 1000 millis. 1000 millis / 60 fps = 16 millis between frames
		fpsMillis = millis() + 16;

		readPots();
	
		// display appropriate pattern
		callColorFunction();
		
		//Transmit one frame of data out
		strip.show();
	}
}

void callColorFunction()
{
	// select color
  switch (currProgram) {
	  	case 0:
			Red();
			break;
		case 1:
			Amber();
			break;
		case 2:
			Amber2();
			break;
		case 3:
			Amber3();
			break;
		case 4:           //Single Color (1-6)
			Amber4();
			break;
		case 5:
			Amber5();
			break;
		case 6:
			WarmWhite();
			break;
		case 7:
			NeutralWhite();
			break;
		case 8:
			White();
			break;
		case 9:
			Green();
			break;
		case 10:
			Blue();
			break;
		case 11:           
			Teal();
			break;
		case 12:
			Purple();
			break;
		case 13:
			RainbowOneYoffset();
			break;
		case 14:
			SparkleBlueGreen();
			break;
		case 15:
			RainbowTwoYoffset();
			break;
		case 16:
			rainbowFlag();
			break;
		case 17://Two Colors (12-15)
			AmberWhite();
			break;
		case 18:
			RedGreen();
			break;
		case 19:
			PurpleBlue();
			break;
		case 20:
			BlueWhite();
			break;
		case 21:
			GreenBlue();
			break;
		case 22:
			BlueAmber();
			break;
		case 23:
			RainbowFlow();
			break;
		case 24:   
			DualColorFlow();
			break;
		case 25:   
			DualColorFlowFat();
			break;
		case 26:
			RainbowMovingPiece();
			break;
		case 27:
			RainbowHsvSlow();
			break;
		case 28:
			RainbowHsvFast();
			break;
		case 29:
			DualColorFlowGreenFast();
			break;
		case 30:
			DualColorFlowFast();
			break;
		case 31:
			TwinkleRainbow();
			break;
		case 32:
			rastaFlag();
			break;
		case 33:
			RainbowHsvTight();
			break;
		case 34:
			PurpleGold();
			break;
		case 35:
			sparkleRasta();
			break;
		case 36:
			triFlag();
			break;
		case 37:
			waterFlag();
			break;
		case 38:
			waterFlow();
			break;
		case 39:
			PurpleGreen();
			break;
		case 40:
			DualColorFlowFast2();
			break;
		case 41:
			DualColorFlowFast3();
			break;
		case 42:
			RainbowThreeXoffset();
			break;
		case 43:
			RainbowFourXoffset();
  			break;
		case 44:
			colorWipe();
			break;
		case 45:
			colorWipeBounce();
  			break;
		case 46:
			RainbowBigYoffset();			
			break;
		case 47:
			RainbowBigXoffset();
			break;
		case 48:
			GlowingAmber();
			break;
		case 49:
			GlowingAmberWhite();
			break;
		case 50:
			GlowingBlue();
			break;
		case 51:
			GlowingBlue();
			break;
	}
}
