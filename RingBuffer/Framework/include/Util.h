/**
 * @file	Util.h
 * @brief
 *
 *	(c) Copyright JinWoo Lee 2012
 */

#ifndef UTIL_H
#define UTIL_H

template<unsigned SCALE>
struct Size
{
	static const long value = 2 * Size<SCALE-1>::value;
	static const long mask = 2 * Size<SCALE-1>::value - 1;
};

template<>
struct Size<3>
{
	static const long value = 8;
	static const long mask = 7;
};

#endif // UTIL_H

