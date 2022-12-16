/**
 * full_oled
 * 
 * This was written for the CS427 class at the University of Portland - Internet of Things.
 * The details of this product can be found below. This example library is based on the
 * ssd1306_128x32_i2c.ino file in the Adafruit SSD1306 examples. It has been reconfigured
 * for the ESP32 using the Wire library to enable the I2C communication protocol.
 *
 * This particular library focuses on how to draw lines on the OLED screen.
 * Basic function: display.drawLine(x1, y1, x2, y2, color)
 *  x1: the x-coordinate of the first point
 *  y1: the y-coordinate of the first point
 *  x2: the x-coordinate of the second point
 *  y2: the y-coordinate of the second point
 *  color: either SSD1306_WHITE or SSD1306_INVERSE (this OLED only handles black and white pixels)
 *
 * Important properties:
 *  display.height() - the height of the screen, in pixels
 *  display.width() - the width of the screen, in pixels
 *  display.clearDisplay() - clear the display buffer (reset the canvas)
 *  display.display() - display the contents of the display buffer (show an image on the OLED)
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

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// define I2C pins
#define SDA 13
#define SCK 14

// define the delay betweeen animations and whole function calls
#define DELAY_MS 0
#define DELAY_GLOBAL 200

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
  // PART 1: draw a vertical line and a horizontal line
  drawCenterLine(true);
  delay(DELAY_GLOBAL);
  drawCenterLine(false);
  delay(DELAY_GLOBAL);

  // PART 2: fill the screen horizontally and vertically in both directions
  horizontalFill(true);
  horizontalFill(false);
  delay(DELAY_GLOBAL);
  verticalFill(true);
  verticalFill(false);
  delay(DELAY_GLOBAL);

  // PART 3: sweep fill the screen from a corner
  cornerSweep(false, false, false);   // bottom right, counter-clockwise
  cornerSweep(false, false, true);    // bottom right, clockwise
  cornerSweep(false, true, false);    // top right, counter-clockwise
  cornerSweep(false, true, true);     // top right, clockwise
  cornerSweep(true, false, false);    // bottom left, counter-clockwise
  cornerSweep(true, false, true);     // bottom left, clockwise
  cornerSweep(true, true, false);     // top left, counter-clockwise
  cornerSweep(true, true, true);      // top left, clockwise
  delay(DELAY_GLOBAL);

  // PART 4: spinning line
  lineSpin(3);
  delay(DELAY_GLOBAL);
}

/**
  Draw a single line across the screen, centered either vertically or horizontally

  @param isHorizontal - true if the drawn line should be horizontal
*/
void drawCenterLine(bool isHorizontal){
  // clear display buffer
  display.clearDisplay();

  // calculate the center of the screen, depending on if it's horizontal or vertical
  int center = (isHorizontal) ? display.height()/2 : display.width()/2;

  // draw a line across the middle of the screen
  if(isHorizontal){
    display.drawLine(0, center, display.width()-1, center, SSD1306_WHITE);
  }else{
    display.drawLine(center, 0, center, display.height()-1, SSD1306_WHITE);
  }

  // display the line
  display.display();
}

/**
  Fill the screen horizontally (with vertical lines), moving to the left or right

  @param toRight - true if the fill should start at the left and move to the right
*/
void horizontalFill(bool toRight){
  // clear display buffer
  display.clearDisplay();

  // define the ends of the screen
  int horizontalLimit = display.width()-1;
  int verticalLimit = display.height()-1;

  // draw a vertical line at each pixel on the screen's width
  for(int i = 0; i < display.width(); i++){
    // draw the line vertically, updating every 10ms, depending on the input argument
    if(toRight){
      // if the lines should progress toward the right (toRight = true),
      // start lines at 0...
      display.drawLine(i, 0, i, verticalLimit, SSD1306_WHITE);
    }else{
      // ...else, start the lines at the end of the display
      display.drawLine(horizontalLimit-i, 0, horizontalLimit-i, verticalLimit, SSD1306_WHITE);
    }
    display.display();
    delay(DELAY_MS);
  }
}

/**
  Fill the screen vertically (with horizontal lines)

  @param toBottom - true if the fill should start at the top and move downward
*/
void verticalFill(bool toBottom){
  // clear display buffer
  display.clearDisplay();

  // define the ends of the screen
  int horizontalLimit = display.width()-1;
  int verticalLimit = display.height()-1;

  // draw a horizontal line at each pixel on the screen's height
  for(int i = 0; i < display.height(); i++){
    // draw the line horizontally, updating every 10ms, depending on the input argument
    if(toBottom){
      // if the lines should progress toward the bottom (toBottom = true),
      // start lines at 0...
      display.drawLine(0, i, horizontalLimit, i, SSD1306_WHITE);
    }else{
      // ...else, start lines at the end of the display
      display.drawLine(0, verticalLimit-i, horizontalLimit, verticalLimit-i, SSD1306_WHITE);
    }
    display.display();
    delay(DELAY_MS);
  }
}

/**
  Sweep fill the display with diagonal lines, using a starting corner and a direction to sweep in.
  The function takes three booleans, with the first two dictating the starting corner and the
  third determining the direction to sweep in. 

  @param isLeft - true if the corner is on the left two corners of the screen
  @param isTop - true if the corner is on the top two corners of the screen
  @param isClockwise - true if the screen should be filled clockwise
*/
void cornerSweep(bool isLeft, bool isTop, bool isClockwise){
  // clear the display buffer
  display.clearDisplay();

  // define the ends of the screen
  int horizontalLimit = display.width() - 1;
  int verticalLimit = display.height() - 1;

  // set the coordinates of the starting corner
  int xStart = (isLeft) ? 0 : horizontalLimit;
  int yStart = (isTop) ? 0 : verticalLimit;

  // sweeping needs to be done in two parts:
  // once along the vertical edge of the screen, and once along the horizontal edge
  // define the limit of the first and second parts using Boolean algebra
  bool isFirstVertical = (((isLeft ? 1 : 0) + (isTop ? 1 : 0) + (isClockwise ? 1 : 0)) % 2 == 1);
  int firstLimit = (isFirstVertical) ? verticalLimit : horizontalLimit;
  int secondLimit = (isFirstVertical) ? horizontalLimit : verticalLimit;
  
  // starting corners...
  if(isLeft && isTop){
    // top-left starting corner
    for(int i = 0; i <= firstLimit; i++){
      // first sweep
      int firstXEndCoord = (isClockwise) ? horizontalLimit : i;
      int firstYEndCoord = (isClockwise) ? i : verticalLimit;
      display.drawLine(xStart, yStart, firstXEndCoord, firstYEndCoord, SSD1306_WHITE);
      display.display();
      delay(DELAY_MS);
    }
    for(int i = 0; i <= secondLimit; i++){
      // second sweep
      int secondXEndCoord = (isClockwise) ? horizontalLimit-i : horizontalLimit;
      int secondYEndCoord = (isClockwise) ? verticalLimit : verticalLimit-i;
      display.drawLine(xStart, yStart, secondXEndCoord, secondYEndCoord, SSD1306_WHITE);
      display.display();
      delay(DELAY_MS);
    }
  }else if(!isLeft && isTop){
    // top-right starting corner
    for(int i = 0; i <= firstLimit; i++){
      // first sweep
      int firstXEndCoord = (isClockwise) ? horizontalLimit-i : 0;
      int firstYEndCoord = (isClockwise) ? verticalLimit : i;
      display.drawLine(xStart, yStart, firstXEndCoord, firstYEndCoord, SSD1306_WHITE);
      display.display();
      delay(DELAY_MS);
    }
    for(int i = 0; i <= secondLimit; i++){
      // second sweep
      int secondXEndCoord = (isClockwise) ? 0 : i;
      int secondYEndCoord = (isClockwise) ? verticalLimit-i : verticalLimit;
      display.drawLine(xStart, yStart, secondXEndCoord, secondYEndCoord, SSD1306_WHITE);
      display.display();
      delay(DELAY_MS);
    }
  }else if(isLeft && !isTop){
    // bottom-left starting corner
    for(int i = 0; i <= firstLimit; i++){
      // first sweep
      int firstXEndCoord = (isClockwise) ? i : horizontalLimit;
      int firstYEndCoord = (isClockwise) ? 0 : verticalLimit-i;
      display.drawLine(xStart, yStart, firstXEndCoord, firstYEndCoord, SSD1306_WHITE);
      display.display();
      delay(DELAY_MS);
    }
    for(int i = 0; i <= secondLimit; i++){
      // second sweep
      int secondXEndCoord = (isClockwise) ? horizontalLimit : horizontalLimit-i;
      int secondYEndCoord = (isClockwise) ? i : 0;
      display.drawLine(xStart, yStart, secondXEndCoord, secondYEndCoord, SSD1306_WHITE);
      display.display();
      delay(DELAY_MS);
    }
  }else if(!isLeft && !isTop){
    // bottom-right starting corner
    for(int i = 0; i <= firstLimit; i++){
      // first sweep
      int firstXEndCoord = (isClockwise) ? 0 : horizontalLimit-i;
      int firstYEndCoord = (isClockwise) ? verticalLimit-i : 0;
      display.drawLine(xStart, yStart, firstXEndCoord, firstYEndCoord, SSD1306_WHITE);
      display.display();
      delay(DELAY_MS);
    }
    for(int i = 0; i <= secondLimit; i++){
      // second sweep
      int secondXEndCoord = (isClockwise) ? i : 0;
      int secondYEndCoord = (isClockwise) ? 0 : i;
      display.drawLine(xStart, yStart, secondXEndCoord, secondYEndCoord, SSD1306_WHITE);
      display.display();
      delay(DELAY_MS);
    }
  }
}


/**
  Animate a line spinning at the center of the screen

  @param numTimes - the number of rotations for the line to make
*/
void lineSpin(int numTimes){
  // clear display
  display.clearDisplay();

  // a single half-rotation is broken up into two phases:
  // the first along the horizontal edge of the screen, the second along the vertical edge
  // repeat this twice for a full rotation, multiplied by the number of times to rotate
  for(int n = 0; n < (2 * numTimes); n++){
    for(int i = 0; i < display.width(); i++){
      display.clearDisplay();
      display.drawLine(i, display.height()-1, display.width()-1-i, 0, SSD1306_WHITE);
      display.display();
      delay(DELAY_MS);
    }
    for(int i = 0; i < display.height(); i++){
      display.clearDisplay();
      display.drawLine(0, i, display.width()-1, display.height()-1-i, SSD1306_WHITE);
      display.display();
      delay(DELAY_MS);    
    }
  }
}














