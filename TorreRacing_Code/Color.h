
#pragma once

//More colors http://prideout.net/archive/colors.php

struct Color
{
	float r, g, b, a;
	
	Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f)
	{}

	Color(float r, float g, float b, float a = 1.0f) : r(r), g(g), b(b), a(a)
	{}

	void Set(float r, float g, float b, float a = 1.0f)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	float* operator & ()
	{
		return (float*)this;
	}
};

extern Color Red;
extern Color Orange;
extern Color Yellow;
extern Color Lime;
extern Color Green;
extern Color LightMediumSeaGreeen;
extern Color Cyan;
extern Color Blue;
extern Color DarkBlue;
extern Color Violet;
extern Color Purple;
extern Color Magenta;

extern Color Black;
extern Color Grey;
extern Color White;

//Browns
extern Color Chocolate;
extern Color SaddleBrown;
extern Color Sienna;
extern Color Brown;
extern Color Maroon;

//Reds
extern Color Crimson;
extern Color FireBrick;
extern Color DarkRed;

//Yellows

extern Color LightYellow;