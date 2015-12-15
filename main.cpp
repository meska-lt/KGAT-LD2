/**
	KGAT-15 LD1
	main.cpp
	Purpose: draw author's initials (character symbols have to be filled with gradient).

	@author: Robertas Kvietkauskas
	@version: 0.2.0

 */

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include "BMP24.h"

#define RESULT_IMAGE_WIDTH 1000
#define RESULT_IMAGE_HEIGHT 1000
#define RESULT_FILENAME "result.bmp"
#define BORDER_WIDTH 50
#define CENTER_HORIZONTAL RESULT_IMAGE_WIDTH / 2
#define CENTER_VERTICAL RESULT_IMAGE_HEIGHT / 2

struct Point {
	int x;
	int y;
};

struct Color {
	char r;
	char g;
	char b;
};

bool pointInsideTriangle(Point s, Point a, Point b, Point c) {
	int as_x = s.x - a.x;
	int as_y = s.y - a.y;
	bool s_ab = (((b.x - a.x) * as_y) - ((b.y - a.y) * as_x)) > 0;
	bool result = false;

	if (((c.x - a.x) * as_y) - ((c.y - a.y) * as_x) > 0 == s_ab)
		result = true;

	if (((c.x - b.x) * (s.y - b.y)) - ((c.y-b.y) * (s.x-b.x)) > 0 != s_ab)
		result = true;

	return result;
}

void drawTriangleInBitmap(BMP24 &bitmap, int c1x, int c1y, int c2x, int c2y, int c3x, int c3y, Color color) {
	// std::cout << "void drawTriangleInBitmap(BMP24, int, int, int, int, int, int);\n";
	std::cout << "void drawTriangleInBitmap(BMP24, " << c1x << ", " << c1y << ", " << c2x << ", " << c2y << ", " << c3x << ", " << c3y << ");\n";

	for (int x = 0; x < bitmap.plotis; x++) {
		for (int y = 0; y < bitmap.aukstis; y++) {
			Point p = {x, y};
			Point p1 = {c1x, c1y};
			Point p2 = {c2x, c2y};
			Point p3 = {c3x, c3y};

			if(!pointInsideTriangle(p, p1, p2, p3))
				bitmap.dekTaska(x, y, color.r, color.g, color.b);
		}
	}
}

void drawTriangleInBitmapWithCornerPoints(BMP24 &bitmap, Point c1, Point c2, Point c3, Color color) {
	drawTriangleInBitmap(bitmap, c1.x, c1.y, c2.x, c2.y, c3.x, c3.y, color);
}

void fillBitmapWithGradient(BMP24 &bitmap) {
	std::cout << "void fillBitmapWithGradient(BMP24);\n";

	for (int x = 0; x < bitmap.plotis; x++) {
		for (int y = 0; y < bitmap.aukstis; y++) {
			char redValue = 255-255.0 * y / RESULT_IMAGE_HEIGHT;
			char greenValue = 255-255.0 * y / RESULT_IMAGE_WIDTH;
			char blueValue = 0 + (255.0 * y / RESULT_IMAGE_WIDTH);

			bitmap.dekTaska(x, y, redValue, greenValue, blueValue);
		}
	}
}

void fillBitmapWithColor(BMP24 &bitmap, Color color) {
	std::cout << "void fillBackgroundWithSolidInBitmap(BMP24, Color);\n";

	for (int x = 0; x < bitmap.plotis; x++) {
		for (int y = 0; y < bitmap.aukstis; y++) {
			bitmap.dekTaska(x, y, color.r, color.g, color.b);
		}
	}
}

void drawCissoidOfDioclesInBitmapWithGridColumnWidth(BMP24 &bitmap, int columnWidth, Color color) {
	std::cout << "void drawCissoidOfDioclesInBitmapWithColor(BMP24, Color);\n";

	int pseudoCenterHorizontal = (bitmap.plotis - (bitmap.plotis % columnWidth)) / 2;
	int pseudoCenterVertical = (bitmap.aukstis - (bitmap.aukstis % columnWidth)) / 2;

	int a = 48*3;

	for (int x = pseudoCenterHorizontal; x < pseudoCenterHorizontal + a; x++) {
		int y = sqrt(x^3 / (2*a - x));

		bitmap.dekTaska(x, pseudoCenterVertical + y, color.r, color.g, color.b);
		bitmap.dekTaska(x, pseudoCenterVertical - y, color.r, color.g, color.b);
	}
}

void drawCoordinateAxleArrowsInBitmapWithColor(BMP24 &bitmap, int columnWidth, int axleWidth, Color color) {
	std::cout << "void drawCoordinateAxleArrowsInBitmapWithColor(BMP24, int, int, Color);\n";

	int pseudoCenterHorizontal = (bitmap.plotis - (bitmap.plotis % columnWidth)) / 2;
	int pseudoCenterVertical = (bitmap.aukstis - (bitmap.aukstis % columnWidth)) / 2;

	Point c1 = {pseudoCenterHorizontal, 0};
	Point c2 = {(pseudoCenterHorizontal - axleWidth*3), axleWidth*3};
	Point c3 = {(pseudoCenterHorizontal + axleWidth*3), axleWidth*3};

	drawTriangleInBitmapWithCornerPoints(bitmap, c1, c2, c3, color);

	c1.x = pseudoCenterHorizontal;
	c1.y = bitmap.aukstis - 1;
	c2.x = pseudoCenterHorizontal - axleWidth*3;
	c2.y = bitmap.aukstis - 1 - axleWidth*3;
	c3.x = pseudoCenterHorizontal + axleWidth*3;
	c3.y = bitmap.aukstis - 1 - axleWidth*3;

	drawTriangleInBitmapWithCornerPoints(bitmap, c1, c2, c3, color);

	c1.x = 0;
	c1.y = pseudoCenterHorizontal;
	c2.x = axleWidth*3;
	c2.y = pseudoCenterHorizontal - 1 - axleWidth*3;
	c3.x = axleWidth*3;
	c3.y = pseudoCenterHorizontal - 1 + axleWidth*3;

	drawTriangleInBitmapWithCornerPoints(bitmap, c1, c2, c3, color);

	c1.x = bitmap.plotis - 1;
	c1.y = pseudoCenterHorizontal;
	c2.x = bitmap.plotis - 1 - axleWidth*3;
	c2.y = pseudoCenterHorizontal - 1 - axleWidth*3;
	c3.x = bitmap.plotis - 1 - axleWidth*3;
	c3.y = pseudoCenterHorizontal - 1 + axleWidth*3;

	drawTriangleInBitmapWithCornerPoints(bitmap, c1, c2, c3, color);
}

void drawCoordinateAxlesInBitmapWithColor(BMP24 &bitmap, int columnWidth, int axleWidth, Color color) {
	std::cout << "void drawCoordinateAxlesInBitmapWithColor(BMP24, int, int, Color);\n";

	int pseudoCenterHorizontal = (bitmap.plotis - (bitmap.plotis % columnWidth)) / 2;
	int pseudoCenterVertical = (bitmap.aukstis - (bitmap.aukstis % columnWidth)) / 2;

	for (int x = axleWidth*2; x < bitmap.plotis - axleWidth*2; x++) {
		for (int y = pseudoCenterVertical - (axleWidth / 2); y < pseudoCenterVertical + (axleWidth / 2); y++) {
			bitmap.dekTaska(x, y, color.r, color.g, color.b);
		}
	}

	for (int y = axleWidth*2; y < bitmap.aukstis - axleWidth*2; y++) {
		for (int x = pseudoCenterHorizontal - (axleWidth / 2); x < pseudoCenterHorizontal + (axleWidth / 2); x++) {
			bitmap.dekTaska(x, y, color.r, color.g, color.b);
		}
	}

	drawCoordinateAxleArrowsInBitmapWithColor(bitmap, columnWidth, axleWidth, color);
}

void drawGridWithColumnWidthAndColorInBitmap(BMP24 &bitmap, int columnWidth, Color color) {
	std::cout << "void drawGridWithColumnWidthAndColorInBitmap(BMP24, int, Color);\n";

	// FIXME this is probably the dumbest way to draw a grid. Should get optimized I guess.

	for (int x = 0; x < bitmap.plotis; x++) {
		for (int y = 0; y < bitmap.aukstis; y += columnWidth) {
			bitmap.dekTaska(x, y, color.r, color.g, color.b);
		}
	}

	for (int x = 0; x < bitmap.plotis; x += columnWidth) {
		for (int y = 0; y < bitmap.aukstis; y++) {
			bitmap.dekTaska(x, y, color.r, color.g, color.b);
		}
	}
}

void openResultOnMac() {
	const char *command = "open ";
	const char *result = new char[strlen(command) + strlen(RESULT_FILENAME)+1];

	strcpy(const_cast<char*>(result), command);
	strcat(const_cast<char*>(result), RESULT_FILENAME);

	system(result);
}

void openResultOnLinux() {
	const char *command = "xdg-open ";
	const char *result = new char[strlen(command) + strlen(RESULT_FILENAME)+1];

	strcpy(const_cast<char*>(result), command);
	strcat(const_cast<char*>(result), RESULT_FILENAME);

	system(result);
}

void openResult() {
	#ifdef __APPLE__
		openResultOnMac();
	#else
  		#ifdef __linux__
  			openResultOnLinux();
  		#endif
	#endif
}

int main() {
	std::cout << "Programa darbą pradėjo.\n";

	BMP24 resultImage = BMP24(RESULT_IMAGE_WIDTH,RESULT_IMAGE_HEIGHT);
	Color backgroundColor = {255, 255, 255};
	Color gridColor = {150, 150, 150};
	Color axlesColor = {0, 0, 0};
	Color curveColor = {64, 128, 192};

	int columnWidth = 48;
	int axleWidth = 4;

	fillBitmapWithColor(resultImage, backgroundColor);
	drawGridWithColumnWidthAndColorInBitmap(resultImage, columnWidth, gridColor);
	drawCoordinateAxlesInBitmapWithColor(resultImage, columnWidth, axleWidth, axlesColor);
	drawCissoidOfDioclesInBitmapWithGridColumnWidth(resultImage, columnWidth, curveColor);

	resultImage.rasykIByla(RESULT_FILENAME);

	openResult();

	std::cout << "Programa darbą baigė.\n";
}