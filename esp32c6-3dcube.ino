#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>     
#include <Adafruit_ST7735.h> 
#include <Adafruit_ST7789.h>
#include <SPI.h>


#define TFT_CS 14
#define TFT_RST 21
#define TFT_DC 15
#define TFT_MOSI 6  
#define TFT_SCLK 7 
#define TFT_LIGHT 22

#define RGB_LED_PIN 8

//Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
//#include <SPI.h>
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

//Adafruit_NeoPixel pixels(1, RGB_LED_PIN, NEO_GRB + NEO_KHZ800);

float p = 3.1415926;

struct Point3D {
  float x, y, z;
};


void setup(void) {

  Serial.begin(9600);
delay(1000);  // Give time for the serial monitor to connect
Serial.println("Started!");
delay(1000);  // Give time for the serial monitor to connect

  pinMode(TFT_LIGHT, OUTPUT);
  digitalWrite(TFT_LIGHT, HIGH);

  //pixels.begin();
  SPI.begin(TFT_SCLK, -1, TFT_MOSI);
  tft.init(172, 320); 
  tft.setRotation(2);      

  tft.setSPISpeed(20000000);

  Serial.println(F("Initialized"));

  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);
  time = millis() - time;

  Serial.println(time, DEC);
  //pixels.setPixelColor(0, pixels.Color(150, 0, 0));
  //pixels.show();
  delay(500);



  Serial.println("done");
  delay(1000);
}


float angle = 0;
unsigned long lastFrame = 0;

void loop() {
  unsigned long now = millis();
  float deltaTime = (now - lastFrame) / 1000.0; // in seconds
  lastFrame = now;

  angle += 0.5 * deltaTime;  // degrees per second
  drawRotatingCubeColour(angle, angle * 0.8, angle * 0.6);
}
 

void loopX() {

unsigned long now = millis();
  float deltaTime = (now - lastFrame) / 1000.0; // in seconds
  lastFrame = now;

  angle += 0.05 * deltaTime;  // degrees per second
  drawFilledCube(angle, angle * 0.8, angle * 0.6);

 // delay(10);  // Adjust for smoother/faster animation

}




void testlines(uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6) {
    tft.drawLine(0, 0, x, tft.height() - 1, color);
    delay(0);
  }
  for (int16_t y = 0; y < tft.height(); y += 6) {
    tft.drawLine(0, 0, tft.width() - 1, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6) {
    tft.drawLine(tft.width() - 1, 0, x, tft.height() - 1, color);
    delay(0);
  }
  for (int16_t y = 0; y < tft.height(); y += 6) {
    tft.drawLine(tft.width() - 1, 0, 0, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6) {
    tft.drawLine(0, tft.height() - 1, x, 0, color);
    delay(0);
  }
  for (int16_t y = 0; y < tft.height(); y += 6) {
    tft.drawLine(0, tft.height() - 1, tft.width() - 1, y, color);
    delay(0);
  }

  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6) {
    tft.drawLine(tft.width() - 1, tft.height() - 1, x, 0, color);
    delay(0);
  }
  for (int16_t y = 0; y < tft.height(); y += 6) {
    tft.drawLine(tft.width() - 1, tft.height() - 1, 0, y, color);
    delay(0);
  }
}

void testdrawtext(char *text, uint16_t color) {
  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextWrap(true);
  tft.print(text);
}

void testfastlines(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t y = 0; y < tft.height(); y += 5) {
    tft.drawFastHLine(0, y, tft.width(), color1);
  }
  for (int16_t x = 0; x < tft.width(); x += 5) {
    tft.drawFastVLine(x, 0, tft.height(), color2);
  }
}

void testdrawrects(uint16_t color) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6) {
    tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color);
  }
}

void testfillrects(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST77XX_BLACK);
  for (int16_t x = tft.width() - 1; x > 6; x -= 6) {
    tft.fillRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color1);
    tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2, x, x, color2);
  }
}

void testfillcircles(uint8_t radius, uint16_t color) {
  for (int16_t x = radius; x < tft.width(); x += radius * 2) {
    for (int16_t y = radius; y < tft.height(); y += radius * 2) {
      tft.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x = 0; x < tft.width() + radius; x += radius * 2) {
    for (int16_t y = 0; y < tft.height() + radius; y += radius * 2) {
      tft.drawCircle(x, y, radius, color);
    }
  }
}

void testtriangles() {
  tft.fillScreen(ST77XX_BLACK);
  uint16_t color = 0xF800;
  int t;
  int w = tft.width() / 2;
  int x = tft.height() - 1;
  int y = 0;
  int z = tft.width();
  for (t = 0; t <= 15; t++) {
    tft.drawTriangle(w, y, y, x, z, x, color);
    x -= 4;
    y += 4;
    z -= 4;
    color += 100;
  }
}

void testroundrects() {
  tft.fillScreen(ST77XX_BLACK);
  uint16_t color = 100;
  int i;
  int t;
  for (t = 0; t <= 4; t += 1) {
    int x = 0;
    int y = 0;
    int w = tft.width() - 2;
    int h = tft.height() - 2;
    for (i = 0; i <= 16; i += 1) {
      tft.drawRoundRect(x, y, w, h, 5, color);
      x += 2;
      y += 3;
      w -= 4;
      h -= 6;
      color += 1100;
    }
    color += 100;
  }
}

void tftPrintTest() {
  tft.setTextWrap(false);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(3);
  tft.println("Hello World!");
  tft.setTextColor(ST77XX_BLUE);
  tft.setTextSize(4);
  tft.print(1234.567);
  delay(1500);
  tft.setCursor(0, 0);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(0);
  tft.println("Hello World!");
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_GREEN);
  tft.print(p, 6);
  tft.println(" Want pi?");
  tft.println(" ");
  tft.print(8675309, HEX);  // print 8,675,309 out in HEX!
  tft.println(" Print HEX!");
  tft.println(" ");
  tft.setTextColor(ST77XX_WHITE);
  tft.println("Sketch has been");
  tft.println("running for: ");
  tft.setTextColor(ST77XX_MAGENTA);
  tft.print(millis() / 1000);
  tft.setTextColor(ST77XX_WHITE);
  tft.print(" seconds.");
}

void mediabuttons() {
  // play
  tft.fillScreen(ST77XX_BLACK);
  tft.fillRoundRect(25, 10, 78, 60, 8, ST77XX_WHITE);
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_RED);
  delay(500);
  // pause
  tft.fillRoundRect(25, 90, 78, 60, 8, ST77XX_WHITE);
  tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_GREEN);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_GREEN);
  delay(500);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_BLUE);
  delay(50);
  // pause color
  tft.fillRoundRect(39, 98, 20, 45, 5, ST77XX_RED);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST77XX_RED);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST77XX_GREEN);
}



// Project 3D point to 2D screen
void projectPoint(Point3D pt, int &x2d, int &y2d, float angleX, float angleY, float angleZ, float scale, int xOffset, int yOffset) {
  // Rotation around X axis
  float cosX = cos(angleX), sinX = sin(angleX);
  float y1 = pt.y * cosX - pt.z * sinX;
  float z1 = pt.y * sinX + pt.z * cosX;

  // Rotation around Y axis
  float cosY = cos(angleY), sinY = sin(angleY);
  float x2 = pt.x * cosY + z1 * sinY;
  float z2 = -pt.x * sinY + z1 * cosY;

  // Rotation around Z axis
  float cosZ = cos(angleZ), sinZ = sin(angleZ);
  float x3 = x2 * cosZ - y1 * sinZ;
  float y3 = x2 * sinZ + y1 * cosZ;

  // Perspective projection (optional)
  float perspective = 1 / (z2 * 0.02 + 2);  // Avoid divide-by-zero

  x2d = xOffset + x3 * scale * perspective;
  y2d = yOffset + y3 * scale * perspective;
}

// Draw and rotate a cube
void drawRotatingCube(float angleX, float angleY, float angleZ) {
  // Define 8 cube vertices
  Point3D cube[8] = {
    {-1, -1, -1}, { 1, -1, -1}, { 1,  1, -1}, {-1,  1, -1},
    {-1, -1,  1}, { 1, -1,  1}, { 1,  1,  1}, {-1,  1,  1}
  };

  // Projected 2D points
  int px[8], py[8];

  // Project all points
  for (int i = 0; i < 8; i++) {
    projectPoint(cube[i], px[i], py[i], angleX, angleY, angleZ, 50, tft.width()/2, tft.height()/2);
  }

  // Draw lines between cube edges
  tft.fillScreen(ST77XX_BLACK);

  int edges[12][2] = {
    {0,1},{1,2},{2,3},{3,0},
    {4,5},{5,6},{6,7},{7,4},
    {0,4},{1,5},{2,6},{3,7}
  };

  for (int i = 0; i < 12; i++) {
    tft.drawLine(px[edges[i][0]], py[edges[i][0]], px[edges[i][1]], py[edges[i][1]], ST77XX_WHITE);
  }
}

void drawRotatingCubeColour(float angleX, float angleY, float angleZ) {
  // Define cube vertices
  Point3D cube[8] = {
    {-1, -1, -1}, { 1, -1, -1}, { 1,  1, -1}, {-1,  1, -1},
    {-1, -1,  1}, { 1, -1,  1}, { 1,  1,  1}, {-1,  1,  1}
  };

  // Define 12 edges: each pair indexes into `cube`
  int edges[12][2] = {
    {0,1}, {1,2}, {2,3}, {3,0}, // back face
    {4,5}, {5,6}, {6,7}, {7,4}, // front face
    {0,4}, {1,5}, {2,6}, {3,7}  // connecting sides
  };

  // Colors per face group (4 edges each)
  uint16_t edgeColors[12] = {
    ST77XX_RED, ST77XX_RED, ST77XX_RED, ST77XX_RED,       // back face
    ST77XX_GREEN, ST77XX_GREEN, ST77XX_GREEN, ST77XX_GREEN, // front face
    ST77XX_BLUE, ST77XX_BLUE, ST77XX_BLUE, ST77XX_BLUE    // side edges
  };

  // Projected 2D points
  int px[8], py[8];

  // Project each vertex
  for (int i = 0; i < 8; i++) {
    projectPoint(cube[i], px[i], py[i],
                 angleX, angleY, angleZ,
                 50, tft.width() / 2, tft.height() / 2);
  }

  // Clear screen
  tft.fillScreen(ST77XX_BLACK);

  // Draw colored edges
  for (int i = 0; i < 12; i++) {
    int a = edges[i][0];
    int b = edges[i][1];
    tft.drawLine(px[a], py[a], px[b], py[b], edgeColors[i]);
  }
}

// Define cube faces using vertex indices (each face has 4 corners)
const int faces[6][4] = {
  {0, 1, 2, 3},  // back
  {4, 5, 6, 7},  // front
  {0, 1, 5, 4},  // bottom
  {2, 3, 7, 6},  // top
  {0, 3, 7, 4},  // left
  {1, 2, 6, 5}   // right
};

// One color per face
const uint16_t faceColors[6] = {
  ST77XX_RED, ST77XX_GREEN, ST77XX_BLUE,
  ST77XX_YELLOW, ST77XX_MAGENTA, ST77XX_CYAN
};

void drawFilledCube(float angleX, float angleY, float angleZ) {
  // 3D cube vertices
  Point3D cube[8] = {
    {-1, -1, -1}, { 1, -1, -1}, { 1,  1, -1}, {-1,  1, -1},
    {-1, -1,  1}, { 1, -1,  1}, { 1,  1,  1}, {-1,  1,  1}
  };

  // Projected 2D positions
  int px[8], py[8];
  float pz[8];

  for (int i = 0; i < 8; i++) {
    // Project 3D to 2D and store z for painter’s algorithm
    Point3D pt = cube[i];

    // Rotation: same as before
    float cosX = cos(angleX), sinX = sin(angleX);
    float y1 = pt.y * cosX - pt.z * sinX;
    float z1 = pt.y * sinX + pt.z * cosX;

    float cosY = cos(angleY), sinY = sin(angleY);
    float x2 = pt.x * cosY + z1 * sinY;
    float z2 = -pt.x * sinY + z1 * cosY;

    float cosZ = cos(angleZ), sinZ = sin(angleZ);
    float x3 = x2 * cosZ - y1 * sinZ;
    float y3 = x2 * sinZ + y1 * cosZ;

    float perspective = 1 / (z2 * 0.02 + 2);
    px[i] = tft.width() / 2 + x3 * 50 * perspective;
    py[i] = tft.height() / 2 + y3 * 50 * perspective;
    pz[i] = z2;  // for depth sorting
  }

  // Clear screen
  tft.fillScreen(ST77XX_BLACK);
  //tft.drawTriangle(px[a], py[a], px[b], py[b], px[c], py[c], ST77XX_BLACK);
//tft.drawTriangle(px[a], py[a], px[c], py[c], px[d], py[d], ST77XX_BLACK);


  // Painter's algorithm: draw farthest faces first
  int faceOrder[6] = {0, 1, 2, 3, 4, 5};
  // Sort faces by average depth (simple bubble sort)
  for (int i = 0; i < 5; i++) {
    for (int j = i + 1; j < 6; j++) {
      float zi = (pz[faces[faceOrder[i]][0]] + pz[faces[faceOrder[i]][1]] +
                  pz[faces[faceOrder[i]][2]] + pz[faces[faceOrder[i]][3]]) / 4.0;
      float zj = (pz[faces[faceOrder[j]][0]] + pz[faces[faceOrder[j]][1]] +
                  pz[faces[faceOrder[j]][2]] + pz[faces[faceOrder[j]][3]]) / 4.0;
      if (zi < zj) {
        int temp = faceOrder[i];
        faceOrder[i] = faceOrder[j];
        faceOrder[j] = temp;
      }
    }
  }

  // Draw faces in order
  for (int f = 0; f < 6; f++) {
    int i = faceOrder[f];
    int a = faces[i][0], b = faces[i][1], c = faces[i][2], d = faces[i][3];
    uint16_t color = faceColors[i];

    // Split quad into two triangles: ABC and ACD
    tft.fillTriangle(px[a], py[a], px[b], py[b], px[c], py[c], color);
    tft.fillTriangle(px[a], py[a], px[c], py[c], px[d], py[d], color);
  }
}
