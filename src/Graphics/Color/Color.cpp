#include "Color.hpp"

/*
Conversions between HS? and RGB were taken from Algorithms 8.6.{1-4} in
Agoston's book, "Computer Graphics and Geometric Modeling" 
*/

//---------------------------------------------------------------------------//
// ColorHSV
//---------------------------------------------------------------------------//

// --- Standard Functions --- //
ColorHSV::ColorHSV(): h(-1), s(0), v(0) { }

ColorHSV::ColorHSV(const float& _h, const float& _s, const float& _v):
	h(_h), s(_s), v(_v)
{ }

ColorHSV::ColorHSV(const Color& color) {
	*this = ColorHSV::getConst(color);
}

ColorHSV::ColorHSV(const ColorHSV& rhs):
	h(rhs.h), s(rhs.s), v(rhs.v)
{ }

ColorHSV::~ColorHSV() { }

ColorHSV& ColorHSV::operator=(const ColorHSV& rhs) {
	this->h = rhs.h;
	this->s = rhs.s;
	this->v = rhs.v;
	return *this;
}

// --- Conversions --- //
ColorHSL ColorHSV::toHSL() const {
	return this->toRGB().toHSL();
}

ColorRGB ColorHSV::toRGB() const {
	float H = this->h;
	float S = this->s;
	float V = this->v;
	float fract, p, q, t;
	int sextant;
	ColorRGB ret = {0, 0, 0};

	if(this->v == 0.0) return ret;

	const bool H_NDEF = (H < 0.0 || 360.0 < H);

	if(this->s == 0.0) {
		if(H_NDEF) {
			ret = {V, V, V};
		}
		else {
			std::cerr << "Invalid HSV to convert to RGB\n";
			return ret;
		}
	}
	else {
		H = (H == 360.0) ? (0.0) : (H / 60.0);
		sextant = floor(H);
		fract = H - (float)sextant;
		p = V * (1 - S);
		q = V * (1 - (S * fract));
		t = V * (1 - (S * (1 - fract)));
		switch(sextant) {
		case 0: ret = {v, t, p}; break;
		case 1: ret = {q, v, p}; break;
		case 2: ret = {p, v, t}; break;
		case 3: ret = {p, q, v}; break;
		case 4: ret = {t, p, v}; break;
		case 5: ret = {v, p, q}; break;
		default: std::cerr << "Invalid HSV to convert to RGB\n";
		}
	}
	return ret;
}

ColorRGBc ColorHSV::toRGBc() const {
	return this->toRGB().toRGBc();
}

// --- Other --- //
ColorHSV ColorHSV::getConst(const Color& color) {
	ColorHSV ret = {0,0,0};
	switch(color) {
	case Red: ret = {0,1,1}; break;
	case Orange: ret = {30,1,1}; break;
	case Yellow: ret = {60,1,1}; break;
	case Green: ret = {120,1,1}; break;
	case Cyan: ret = {180,1,1}; break;
	case Blue: ret = {240,1,1}; break;
	case Purple: ret = {270,1,1}; break;
	case Magenta: ret = {300,1,1}; break;
	case Black: ret = {-1,0,0}; break;
	case White: ret = {-1,0,1}; break;
	default: ret = ColorHSV::getConst(Black); break;
	}
	return ret;
}

std::ostream& operator<<(std::ostream& os, const ColorHSV& c) {
	return os << "{" << c.h << "," << c.s << "," << c.v << "}";
}

//---------------------------------------------------------------------------//
// ColorHSL
//---------------------------------------------------------------------------//

// --- Standard Functions --- //
ColorHSL::ColorHSL(): h(-1), s(0), l(0) { }

ColorHSL::ColorHSL(const float& _h, const float& _s, const float& _l):
	h(_h), s(_s), l(_l)
{ }

ColorHSL::ColorHSL(const Color& color) {
	*this = ColorHSL::getConst(color);
}

ColorHSL::ColorHSL(const ColorHSL& rhs):
	h(rhs.h), s(rhs.s), l(rhs.l)
{ }

ColorHSL::~ColorHSL() { }

ColorHSL& ColorHSL::operator=(const ColorHSL& rhs) {
	this->h = rhs.h;
	this->s = rhs.s;
	this->l = rhs.l;
	return *this;
}

// --- Conversions --- //
ColorHSV ColorHSL::toHSV() const {
	return this->toRGB().toHSV();
}

ColorRGB ColorHSL::toRGB() const {
	float H = this->h;
	float S = this->s;
	float L = this->l;
	float v, min, sv, fract, vsf, mid1, mid2;
	int sextant;

	ColorRGB ret = {0, 0, 0};

	const bool H_NDEF = (H < 0.0 || 360.0 < H);

	if(S == 0.0) {
		if(H_NDEF) {
			ret = {L, L, L};
			return ret;
		}
		else {
			std::cerr << "Invalid HSL to convert to RGB: "
				<< (*this) <<"\n";
			return ret;
		}
	}
	v = (L <= 0.5) ? (L * (1 + S)) : (L + S - L * S);
	if(v == 0.0) {
		ret = {0, 0, 0};
	}
	else {
		min = 2 * L - v;
		sv = (v - min) / v;
		H = (H == 360.0) ? (0.0) : (H / 60.0);
		sextant = floor(H);
		fract = H - (float)sextant;
		vsf = v * sv * fract;
		mid1 = min + vsf;
		mid2 = v - vsf;
		switch(sextant) {
		case 0: ret = {v, mid1, min}; break;
		case 1: ret = {mid2, v, min}; break;
		case 2: ret = {min, v, mid1}; break;
		case 3: ret = {min, mid2, v}; break;
		case 4: ret = {mid1, min, v}; break;
		case 5: ret = {v, min, mid2}; break;
		default:
			std::cerr << "Invalid HSL to convert to RGB: "
				<< (*this) <<"\n";
		}
	}
	return ret;
}

ColorRGBc ColorHSL::toRGBc() const {
	return this->toRGB().toRGBc();
}

// --- Other --- //
ColorHSL ColorHSL::getConst(const Color& color) {
	return ColorHSV::getConst(color).toHSL();
}

std::ostream& operator<<(std::ostream& os, const ColorHSL& c) {
	return os << "{" << c.h << "," << c.s << "," << c.l << "}";
}

// --- Other --- //
ColorHSL ColorHSL::illuminate(
	const ColorHSL& color,
	const float& illuCoef
) {
	ColorHSL ret(color);
	ret.l = std::min(ret.l * illuCoef, (float)1.0);
	return ret;
}

//---------------------------------------------------------------------------//
// ColorRGB
//---------------------------------------------------------------------------//

// --- Standard Functions --- //
ColorRGB::ColorRGB(): r(0), g(0), b(0) { }

ColorRGB::ColorRGB(const float& _r, const float& _g, const float& _b):
	r(_r), g(_g), b(_b)
{ }

ColorRGB::ColorRGB(const Color& color) {
	*this = ColorRGB::getConst(color);
}

ColorRGB::ColorRGB(const ColorRGB& rhs):
	r(rhs.r), g(rhs.g), b(rhs.b)
{ }

ColorRGB::~ColorRGB() { }

ColorRGB& ColorRGB::operator=(const ColorRGB& rhs) {
	this->r = rhs.r;
	this->g = rhs.g;
	this->b = rhs.b;
	return *this;
}

// --- Conversions --- //
ColorHSV ColorRGB::toHSV() const {
	float max, min, d;
	ColorHSV ret = {0, 0, 0};

	max = std::max(this->r, std::max(this->g, this->b));
	min = std::min(this->r, std::min(this->g, this->b));
	d = max - min;

	ret.v = max;
	ret.s = (max == 0.0) ? (0.0) : d / max;
	if(ret.s == 0.0) {
		ret.h = -1.0;
	}
	else {
		if(this->r == max)
			ret.h = (this->g - this->b) / d;
		else if(this->g == max)
			ret.h = 2.0 + (this->b - this->r) / d;
		else if(this->b == max)
			ret.h = 4.0 + (this->r - this->g) / d;
		ret.h *= 60;
		if(ret.h < 0.0) ret.h += 360.0;
	}

	return ret;
}

ColorHSL ColorRGB::toHSL() const {
	float max, min, d, a;
	ColorHSL ret = {0, 0, 0};

	max = std::max(this->r, std::max(this->g, this->b));
	min = std::min(this->r, std::min(this->g, this->b));

	a = max + min;

	ret.l = a / 2;
	if(max == min) {
		ret.s = 0.0;
		ret.h = -1.0;
	}
	else {
		d = max - min;

		ret.s = d / ((ret.l <= 0.5) ? a : (2 - a));

		if(this->r == max)
			ret.h = (this->g - this->b) / d;
		else if(this->g == max)
			ret.h = 2.0 + (this->b - this->r) / d;
		else if(this->b == max)
			ret.h = 4.0 + (this->r - this->g) / d;
		ret.h *= 60;
		if(ret.h < 0.0) ret.h += 360.0;
	}

	return ret;
}

ColorRGBc ColorRGB::toRGBc() const {
	ColorRGBc ret = {
		(unsigned char)(this->r * (float)255),
		(unsigned char)(this->g * (float)255),
		(unsigned char)(this->b * (float)255)
	};
	return ret;
}

// --- Combining --- //
ColorRGB ColorRGB::combine(
	const float* weights,
	const ColorRGB* colors,
	const size_t& colorCount
) {
	float newR = 0.0;
	float newG = 0.0;
	float newB = 0.0;
	register float tempW = 0.0;
	for(size_t i = 0;i < colorCount;++i) {
		tempW = weights[i];
		newR += tempW * colors[i].r;
		newG += tempW * colors[i].g;
		newB += tempW * colors[i].b;
	}
	return ColorRGB(newR, newG, newB);
}

// --- Other --- //
ColorRGB ColorRGB::getConst(const Color& color) {
	return ColorHSV::getConst(color).toRGB();
}

std::ostream& operator<<(std::ostream& os, const ColorRGB& c) {
	return os << "{" << c.r << "," << c.g << "," << c.b << "}";
}

//---------------------------------------------------------------------------//
// ColorRGBc
//---------------------------------------------------------------------------//

// --- Standard Functions --- //
ColorRGBc::ColorRGBc(): r(0), g(0), b(0) { }

ColorRGBc::ColorRGBc(
	const unsigned char& _r,
	const unsigned char& _g,
	const unsigned char& _b
):
	r(_r), g(_g), b(_b)
{ }

ColorRGBc::ColorRGBc(const Color& color) {
	*this = ColorRGBc::getConst(color);
}

ColorRGBc::ColorRGBc(const ColorRGBc& rhs):
	r(rhs.r), g(rhs.g), b(rhs.b)
{ }

ColorRGBc::~ColorRGBc() { }

ColorRGBc& ColorRGBc::operator=(const ColorRGBc& rhs) {
	this->r = rhs.r;
	this->g = rhs.g;
	this->b = rhs.b;
	return *this;
}

// --- Conversions --- //
ColorHSV ColorRGBc::toHSV() const {
	return this->toRGB().toHSV();
}

ColorHSL ColorRGBc::toHSL() const {
	return this->toRGB().toHSL();
}

ColorRGB ColorRGBc::toRGB() const {
	ColorRGB ret = {
		(float)this->r / (float)225,
		(float)this->g / (float)225,
		(float)this->b / (float)225
	};
	return ret;
}

// --- Other --- //
ColorRGBc ColorRGBc::getConst(const Color& color) {
	return ColorHSV::getConst(color).toRGBc();
}

void ColorRGBc::print(std::ostream& os) const {
	os << this->r << this->g << this->b;
}

std::ostream& operator<<(std::ostream& os, const ColorRGBc& c) {
	return os << "{" << (int)c.r << "," << (int)c.g << "," << (int)c.b << "}";
}
