/***************************************************
  This is our GFX example for the Adafruit ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651
  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!
  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/


#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

 // For the Adafruit shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

void setup() {
	Serial.begin(9600);
	Serial.println("ILI9341 Test!");

	tft.begin();
}



void loop() {
	tft.fillScreen(ILI9341_WHITE);
	yield();
	tft.fillScreen(ILI9341_BLACK);
	yield();
}

unsigned long ePilepSie() {
	tft.fillScreen(ILI9341_BLACK);
	yield();
}

unsigned long testFillScreen() {
	unsigned long start = micros();
	tft.fillScreen(ILI9341_BLACK);
	yield();
	tft.fillScreen(ILI9341_RED);
	yield();
	tft.fillScreen(ILI9341_GREEN);
	yield();
	tft.fillScreen(ILI9341_BLUE);
	yield();
	tft.fillScreen(ILI9341_BLACK);
	yield();
	return micros() - start;
}

unsigned long testText() {
	unsigned long start = micros();
	tft.setCursor(0, 0);
	tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(1);
	tft.println("Henk");
	tft.setTextColor(ILI9341_YELLOW); tft.setTextSize(2);
	tft.println(1337);
	tft.setTextColor(ILI9341_RED);    tft.setTextSize(3);
	tft.println();
	tft.setTextColor(ILI9341_GREEN);
	tft.setTextSize(5);
	tft.println("Harry");
	tft.setTextSize(2);
	tft.println("Dingen");
	tft.setTextSize(1);
	tft.println("Andere dingen");
	tft.println("Nog meer andere dingen");
	return micros() - start;
}

unsigned long testLines(uint16_t color) {
	unsigned long start, t;
	int           x1, y1, x2, y2,
		w = tft.width(),
		h = tft.height();

	tft.fillScreen(ILI9341_BLACK);
	yield();

	x1 = y1 = 0;
	y2 = h - 1;
	start = micros();
	for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
	x2 = w - 1;
	for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
	t = micros() - start; // fillScreen doesn't count against timing

	yield();
	tft.fillScreen(ILI9341_BLACK);
	yield();

	x1 = w - 1;
	y1 = 0;
	y2 = h - 1;
	start = micros();
	for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
	x2 = 0;
	for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
	t += micros() - start;

	yield();
	tft.fillScreen(ILI9341_BLACK);
	yield();

	x1 = 0;
	y1 = h - 1;
	y2 = 0;
	start = micros();
	for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
	x2 = w - 1;
	for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
	t += micros() - start;

	yield();
	tft.fillScreen(ILI9341_BLACK);
	yield();

	x1 = w - 1;
	y1 = h - 1;
	y2 = 0;
	start = micros();
	for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
	x2 = 0;
	for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);

	yield();
	return micros() - start;
}

unsigned long testFastLines(uint16_t color1, uint16_t color2) {
	int           x, y, w = tft.width(), h = tft.height();

	tft.fillScreen(ILI9341_BLACK);
	
	for (y = 0; y < h; y += 24) tft.drawFastHLine(0, y, w, color1);
	for (x = 0; x < w; x += 24) tft.drawFastVLine(x, 0, h, color2);

	
}

unsigned long testRects(uint16_t color) {
	unsigned long start;
	int           n, i, i2,
		cx = tft.width() / 5,
		cy = tft.height() / 2;

	tft.fillScreen(ILI9341_GREEN);
	n = min(tft.width(), tft.height());
	start = micros();
	for (i = 2; i < n; i += 6) {
		i2 = i / 2;
		tft.drawRect(cx - i2, cy - i2, i, i, color);
	}

	return micros() - start;
}

unsigned long testFilledRects(uint16_t color1, uint16_t color2) {
	unsigned long start, t = 0;
	int           n, i, i2,
		cx = tft.width() / 2 - 1,
		cy = tft.height() / 2 - 1;

	tft.fillScreen(ILI9341_BLACK);
	n = min(tft.width(), tft.height());
	for (i = n; i > 0; i -= 6) {
		i2 = i / 2;
		start = micros();
		tft.fillRect(cx - i2, cy - i2, i, i, color1);
		t += micros() - start;
		// Outlines are not included in timing results
		tft.drawRect(cx - i2, cy - i2, i, i, color2);
		yield();
	}

	return t;
}

unsigned long testFilledCircles(uint8_t radius, uint16_t color) {
	unsigned long start;
	int x, y, w = tft.width(), h = tft.height(), r2 = radius * 2;

	tft.fillScreen(ILI9341_BLACK);
	start = micros();
	for (x = radius; x < w; x += r2) {
		for (y = radius; y < h; y += r2) {
			tft.fillCircle(x, y, radius, color);
		}
	}

	return micros() - start;
}

unsigned long testCircles(uint8_t radius, uint16_t color) {
	unsigned long start;
	int           x, y, r2 = radius * 2,
		w = tft.width() + radius,
		h = tft.height() + radius;

	// Screen is not cleared for this one -- this is
	// intentional and does not affect the reported time.
	start = micros();
	for (x = 0; x < w; x += r2) {
		for (y = 0; y < h; y += r2) {
			tft.drawCircle(x, y, radius, color);
		}
	}

	return micros() - start;
}

unsigned long testTriangles() {
	unsigned long start;
	int           n, i, cx = tft.width() / 2 - 1,
		cy = tft.height() / 2 - 1;

	tft.fillScreen(ILI9341_BLACK);
	n = min(cx, cy);
	start = micros();
	for (i = 0; i < n; i += 5) {
		tft.drawTriangle(
			cx, cy - i, // peak
			cx - i, cy + i, // bottom left
			cx + i, cy + i, // bottom right
			tft.color565(i, i, i));
	}

	return micros() - start;
}

unsigned long testFilledTriangles() {
	unsigned long start, t = 0;
	int           i, cx = tft.width() / 2 - 1,
		cy = tft.height() / 2 - 1;

	tft.fillScreen(ILI9341_BLACK);
	start = micros();
	for (i = min(cx, cy); i > 10; i -= 5) {
		start = micros();
		tft.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
			tft.color565(0, i * 10, i * 10));
		t += micros() - start;
		tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
			tft.color565(i * 10, i * 10, 0));
		yield();
	}

	return t;
}

unsigned long testRoundRects() {
	unsigned long start;
	int           w, i, i2,
		cx = tft.width() / 2 - 1,
		cy = tft.height() / 2 - 1;

	tft.fillScreen(ILI9341_BLACK);
	w = min(tft.width(), tft.height());
	start = micros();
	for (i = 0; i < w; i += 6) {
		i2 = i / 2;
		tft.drawRoundRect(cx - i2, cy - i2, i, i, i / 8, tft.color565(i, 0, 0));
	}

	return micros() - start;
}

unsigned long testFilledRoundRects() {
	unsigned long start;
	int           i, i2,
		cx = tft.width() / 2 - 1,
		cy = tft.height() / 2 - 1;

	tft.fillScreen(ILI9341_BLACK);
	start = micros();
	for (i = min(tft.width(), tft.height()); i > 20; i -= 6) {
		i2 = i / 2;
		tft.fillRoundRect(cx - i2, cy - i2, i, i, i / 8, tft.color565(0, i, 0));
		yield();
	}

	return micros() - start;
}
