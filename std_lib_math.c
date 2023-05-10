#include "std_lib_math.h"

double std_lib_math_radToDeg(double rad)
{
	return 180 * rad / PIE;
}

double std_lib_math_degToRad(double deg)
{
	return deg * PIE / 180;
}