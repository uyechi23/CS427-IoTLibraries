/**
 * oled_rectangles
 * 
 * This was written for the CS427 class at the University of Portland - Internet of Things.
 * The details of this product can be found below. This example library is based on the
 * ssd1306_128x32_i2c.ino file in the Adafruit SSD1306 examples. It has been reconfigured
 * for the ESP32 using the Wire library to enable the I2C communication protocol.
 *
 * This particular library focuses on how to draw rectangles on the OLED screen.
 * Basic function: display.drawRect(x, y, w, h, color)
 *  x: the x-coordinate of the top-left corner of the rectangle
 *  y: the y-coordinate of the top-left corner of the rectangle
 *  w: the width of the rectangle
 *  h: the height of the rectangle
 *  color: either SSD1306_WHITE, SSD1306_BLACK, or SSD1306_INVERSE (this OLED only handles black and white pixels)
 *
 * Important variables/functions:
 *  display.height() - the height of the screen, in pixels
 *  display.width() - the width of the screen, in pixels
 *  display.clearDisplay() - clear the display buffer (reset the canvas)
 *  display.display() - display the contents of the display buffer (show an image on the OLED)
 *  SSD1306_INVERSE - inverts the colors of anything already on the display. If a rectangle is
 *                    drawn in this color, anything inside that rectangle will swap white and black.
 * 
 * Required Libraries:
 * - Adafruit SSD1306 (by Adafruit)
 */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// define I2C pins
#define SDA 13
#define SCK 14

// define the delay betweeen animations and whole function calls
#define DELAY_MS 20
#define DELAY_GLOBAL 2000

void setup() {
  // begin serial communication on 115200 baud channel
  Serial.begin(115200);

  // setup I2C communication with SDA/SCK
  Wire.begin(SDA, SCK);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    while(true); // break execution if an error occurred when initializing the display
  }

  // clear the display buffer (this should be called before updating a display)
  display.clearDisplay();
}

void loop() {
  // PART 1: filling the screen with either white or black
  blackOut();
  delay(DELAY_GLOBAL);
  whiteOut();
  delay(DELAY_GLOBAL);

  // PART 2: drawing rectangles using default drawRect
  // drawRect draws the rectangle's outline, but does not fill it in
  drawConcentricRect(true);
  delay(DELAY_GLOBAL);
  drawConcentricRect(false);
  delay(DELAY_GLOBAL);

  // PART 3: filling rectangles using fillRect
  fillConcentricRect(true);
  delay(DELAY_GLOBAL);
  fillConcentricRect(false);
  delay(DELAY_GLOBAL);
}

/**
  Blacks out the screen. display.clearDisplay() does the same thing, but this function
  simply combines the display.clearDisplay() and display.display() commands.
*/
void blackOut(void){
  // clear the display buffer
  display.clearDisplay();
  
  // display the cleared display on the OLED
  display.display();
}

/**
  Whites out the screen. While display.clearDisplay() sets the whole screen to black,
  and simply using display.invertDisplay() inverts it to white, it also swaps the
  values of SSD1306_WHITE and SSD1306_BLACK, so while the display is inverted, drawing
  a white rectangle would instead draw a black rectangle. Think about it as rendering
  the OLED's display normally, but swapping black and white pixels just before displaying it.
  This function uses rectangles to white out a screen so that SSD1306_WHITE and SSD1306_BLACK
  work as expected, and the display does not need to be inverted.
*/
void whiteOut(void){
  // clear the display buffer
  display.clearDisplay();

  // draw a white rectangle across the entire screen
  display.fillRect(0, 0, display.width(), display.height(), SSD1306_WHITE);

  // display the white display on the OLED
  display.display();
}

/**
  Draw a set of concentric rectangles, with a boolean determining 
  the direction the rectangles are drawn

  @param isInward - true if the rectangles should be at the outside and be drawn inward
*/
void drawConcentricRect(bool isInward){
  // clear the display; this should leave a black screen
  // when the display.drawRect() calls are made, it will skip every other pixel to print in
  // white, so the result should be concentric rectangles, one pixel apart from each other,
  // alternating in black and white
  display.clearDisplay();

  // for loop to iteratively draw rectangles
  if(isInward){
    // start at the largest possible rectangle and shrink as iteration continues
    for(int i = 0; i < display.height()/2; i+=2){
      display.drawRect(i, i, display.width() - (2 * i), display.height() - (2 * i), SSD1306_WHITE);
      display.display();
      delay(DELAY_MS);
    }
  }else{
    // swap the limits of the previous for loop and invert the iteration step
    for(int i = display.height()/2 - 1; i >= 0; i-=2){
      display.drawRect(i, i, display.width() - (2 * i), display.height() - (2 * i), SSD1306_WHITE);
      display.display();
      delay(DELAY_MS);
    }
  }
}

/**
  Draw a set of rectangles that are filled in. SSD1306_INVERSE inverts the colors of the rectangles
  that are drawn, so the filled-in rectangles don't simply overlap on top of each other.

  @param isInward - true if the rectangles should be drawn from the outside in
*/
void fillConcentricRect(bool isInward){
  // clear the display buffer
  display.clearDisplay();

  // for loop to iteratively fill rectangles
  if(isInward){
    // start at the largest possible rectangle and shrink as iteration continues
    for(int i = 0; i < display.height()/2; i+=3){
      display.fillRect(i, i, display.width() - (2 * i), display.height() - (2 * i), SSD1306_INVERSE);
      display.display();
      delay(DELAY_MS);
    }
  }else{
    // swap the limits of the previous for loop and invert the iteration step
    for(int i = display.height()/2 - 1; i >= 0; i-=3){
      display.fillRect(i, i, display.width() - (2 * i), display.height() - (2 * i), SSD1306_INVERSE);
      display.display();
      delay(DELAY_MS);
    }
  }
}


