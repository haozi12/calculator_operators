#pragma once
#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "include/workspace.h"

enum Mode {
	float_mode,
	int_mode
};

enum Size {
	size_8 = 8,
	size_16 = 16,
	size_32 = 32,
	size_64 = 64
};

typedef struct calculator_data calculator_data_t;

typedef struct calculator calculator_t;
typedef int(*cal_operator)(calculator_t* calc, value_t a, value_t b, value_t result);

struct calculator {
	calculator_data_t* data;
	cal_operator xor;
	cal_operator and;
	cal_operator or;
	cal_operator not;
	cal_operator shift_left;
	cal_operator shift_right;
	cal_operator add;
	cal_operator subtract;
	cal_operator multiply;
	cal_operator divide;
	cal_operator modulo;
};

calculator_t* new_calculator(enum Mode mode, enum Size size, bool unsigned_flag);
int calculator_switch_mode(calculator_t* calc, enum Mode mode, enum Size size, bool unsigned_flag);
int save_value_to_calculator(calculator_t* calc, value_t value);
int get_value_from_calculator(calculator_t* calc, value_t value);
void calculator_destroy(calculator_t* calc);

#endif
