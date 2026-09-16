#pragma once
#ifndef C_TYPES_H
#define C_TYPES_H

typedef signed char int8_signed;
typedef unsigned char int8_unsigned;
typedef signed short int16_signed;
typedef unsigned short int16_unsigned;
typedef signed int int32_signed;
typedef unsigned int int32_unsigned;

#ifdef _WIN32

typedef signed long long int64_signed;
typedef unsigned long long int64_unsigned;

#else

typedef signed long int64_signed;
typedef unsigned long int64_unsigned;

#endif

typedef float float32;
typedef double float64;

#endif