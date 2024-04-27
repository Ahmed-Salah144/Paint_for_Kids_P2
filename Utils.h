#pragma once

#include "CMUgraphicsLib\CMUgraphics.h"

enum LoadColor
{
	lOAD_BLACK,
	LOAD_YELLOW,
	LOAD_ORANGE,
	LOAD_RED,
	LOAD_GREEN,
	LOAD_BLUE,
	LOAD_NO_FILL
};

inline LoadColor ParseColor(char* input)
{
	if (strcmp(input, "BLACK") == 0)
		return lOAD_BLACK;
	else if (strcmp(input, "YELLOW") == 0)
		return LOAD_YELLOW;
	else if (strcmp(input, "ORANGE") == 0)
		return LOAD_ORANGE;
	else if (strcmp(input, "RED") == 0)
		return LOAD_RED;
	else if (strcmp(input, "GREEN") == 0)
		return LOAD_GREEN;
	else if (strcmp(input, "BLUE") ==  0)
		return LOAD_BLUE;
	else if (strcmp(input, "NO_FILL") == 0)
		return LOAD_NO_FILL;

}