#pragma once
#ifndef WORK_SPACE_H 
#define WORK_SPACE_H
/* 
	created by haozi12
*/
#include <stddef.h>
#include <stdalign.h>
#include "c_types.h"

#ifndef __cplusplus
typedef _Bool bool;
#define true 1
#define false 0
#endif

typedef void* value_t;

enum StatusCode {
	NULL_POINTER = 1,
	INVALID_SIZE = 2,
	INTEGER_ZERO_DIVISION = 3,
	SHIFT_OVERFLOWED = 4,
	SUCCESS = 0,
};

#define Calculator_Value_Size 8

typedef struct {
	alignas(8) int8_unsigned value[Calculator_Value_Size];
}value_slot;

float32 get_float32_value(value_t value);
float64 get_float64_value(value_t value);
int8_signed get_int8_signed_value(value_t value);
int8_unsigned get_int8_unsigned_value(value_t value);
int16_signed get_int16_signed_value(value_t value);
int16_unsigned get_int16_unsigned_value(value_t value);
int32_signed get_int32_signed_value(value_t value);
int32_unsigned get_int32_unsigned_value(value_t value);
int64_signed get_int64_signed_value(value_t value);
int64_unsigned get_int64_unsigned_value(value_t value);

int write_float32_value(value_t value_slot, float32 value);
int write_float64_value(value_t value_slot, float64 value);
int write_int8_signed_value(value_t value_slot, int8_signed value);
int write_int8_unsigned_value(value_t value_slot, int8_unsigned value);
int write_int16_signed_value(value_t value_slot, int16_signed value);
int write_int16_unsigned_value(value_t value_slot, int16_unsigned value);
int write_int32_signed_value(value_t value_slot, int32_signed value);
int write_int32_unsigned_value(value_t value_slot, int32_unsigned value);
int write_int64_signed_value(value_t value_slot, int64_signed value);
int write_int64_unsigned_value(value_t value_slot, int64_unsigned value);


#endif
