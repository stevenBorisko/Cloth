/*
Color???: Different mathematical representations of color
Copyright (C) 2018 Steven Borisko
License: Duality/LICENSE
*/

#ifndef COLOR_H
#define COLOR_H

#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iostream>

//---------------------------------------------------------------------------//
// Structure Declarations
//---------------------------------------------------------------------------//

/*
Color in HSV/HSB format

(float) values have ranges:
	h : [0,360]; s : [0,1]; v : [0,1]
*/
struct ColorHSV;

/*
Color in HSL format

(float) values have ranges:
	h : [0,360]; s : [0,1]; l : [0,1]
*/
struct ColorHSL;

/*
Color in RGB format

(float) values have ranges:
	r : [0,1]; g : [0,1]; b : [0,1]
*/
struct ColorRGB;

/*
Color in RGB format

(unsigned char) values have ranges:
	r : [0,255]; g : [0,255]; b : [0,255]
*/
struct ColorRGBc;

// Array of HSV colors
struct ColorHSVArray;

enum Color {
	Red, Orange, Yellow, Green, Cyan, Blue, Purple, Magenta, Black, White
};

//---------------------------------------------------------------------------//
// Structure Definitions
//---------------------------------------------------------------------------//

struct ColorHSV {
	float h, s, v;

	// Standard Functions
	ColorHSV();
	ColorHSV(const float& _h, const float& _s, const float& _v);
	ColorHSV(const Color& color);
	ColorHSV(const ColorHSV& rhs);
	~ColorHSV();
	ColorHSV& operator=(const ColorHSV& rhs);

	// Conversions
	ColorHSL toHSL() const;
	ColorRGB toRGB() const;
	ColorRGBc toRGBc() const;

	// Other
	static ColorHSV getConst(const Color& color);
	// {h,s,v}
	friend std::ostream& operator<<(std::ostream& os, const ColorHSV& c);
};

struct ColorHSL {
	float h, s, l;

	// Standard Functions
	ColorHSL();
	ColorHSL(const float& _h, const float& _s, const float& _l);
	ColorHSL(const Color& color);
	ColorHSL(const ColorHSL& rhs);
	~ColorHSL();
	ColorHSL& operator=(const ColorHSL& rhs);

	// Conversions
	ColorHSV toHSV() const;
	ColorRGB toRGB() const;
	ColorRGBc toRGBc() const;

	// Other
	static ColorHSL getConst(const Color& color);
	// {h,s,l}
	friend std::ostream& operator<<(std::ostream& os, const ColorHSL& c);

	// Combining/manipulate colors
	static ColorHSL illuminate(
		const ColorHSL& color,
		const float& illuCoef
	);

};

struct ColorRGB {
	float r, g, b;

	// Standard Functions
	ColorRGB();
	ColorRGB(const float& _r, const float& _g, const float& _b);
	ColorRGB(const Color& color);
	ColorRGB(const ColorRGB& rhs);
	~ColorRGB();
	ColorRGB& operator=(const ColorRGB& rhs);

	// Conversions
	ColorHSV toHSV() const;
	ColorHSL toHSL() const;
	ColorRGBc toRGBc() const;

	// Combining
	static ColorRGB combine(
		const float* weights,
		const ColorRGB* colors,
		const size_t& colorCount
	);

	// Other
	static ColorRGB getConst(const Color& color);
	// {r,g,b}
	friend std::ostream& operator<<(std::ostream& os, const ColorRGB& c);
};

struct ColorRGBc {
	unsigned char r, g, b;

	// Standard Functions
	ColorRGBc();
	ColorRGBc(
		const unsigned char& _r,
		const unsigned char& _g,
		const unsigned char& _b
	);
	ColorRGBc(const Color& color);
	ColorRGBc(const ColorRGBc& rhs);
	~ColorRGBc();
	ColorRGBc& operator=(const ColorRGBc& rhs);

	// Conversions
	ColorHSV toHSV() const;
	ColorHSL toHSL() const;
	ColorRGB toRGB() const;

	// Other
	static ColorRGBc getConst(const Color& color);
	// print the three unsigned characters in a row (no spaces)
	// used for printing to a ppm
	void print(std::ostream& os) const;
	// print in decimal the color on the screen
	// {r,g,b}
	friend std::ostream& operator<<(std::ostream& os, const ColorRGBc& c);
};

#endif
