#pragma once
#ifndef OPERATOR_H
#define OPERATOR_H

#include "workspace.h"

typedef int(*uni_bits_operator)(value_t a, int64_unsigned b, size_t bits, bool is_unsigned, bool is_float, value_t result);
typedef int(*uni_alogrid_operator)(value_t a, value_t b, size_t bits, bool is_unsigned, bool is_float, value_t result);
typedef int(*uni_not_operator)(value_t a, size_t bits, value_t result);

int xor_(value_t a,int64_unsigned b,size_t bits,bool is_unsigned,bool is_float,value_t result);
int and_(value_t a, int64_unsigned b, size_t bits, bool is_unsigned, bool is_float, value_t result);
int or_(value_t a, int64_unsigned b, size_t bits, bool is_unsigned, bool is_float, value_t result);
int not_(value_t a, size_t bits, value_t result);
int shift_left(value_t a, int64_unsigned b, size_t bits, bool is_unsigned, bool is_float, value_t result);
int shift_right(value_t a, int64_unsigned b, size_t bits, bool is_unsigned, bool is_float, value_t result);


int add(value_t a, value_t b, size_t bits, bool is_unsigned, bool is_float, value_t result);
int subtract(value_t a, value_t b, size_t bits, bool is_unsigned, bool is_float, value_t result);
int multiply(value_t a, value_t b, size_t bits, bool is_unsigned, bool is_float, value_t result);
int divide(value_t a, value_t b, size_t bits, bool is_unsigned, bool is_float, value_t result);
int modulo(value_t a, value_t b, size_t bits, bool is_unsigned, bool is_float, value_t result);

#endif
