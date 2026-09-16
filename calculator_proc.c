#include "include/calculator.h"
#include "include/operator.h"
#include "include/memory_view.h"
#include <stdlib.h>
#include <string.h>
#include <stdalign.h>
struct calculator_data
{
	bool is_float;
	bool is_int_mode;
	bool is_unsigned;
	alignas(long long) int8_unsigned value[8];
	enum Size size;
};


static int op_xor_(calculator_t* calc, value_t a, value_t b,value_t result)
{
	return xor_(a, *(int64_unsigned*)b, calc->data->size, calc->data->is_unsigned, calc->data->is_float, result);
}

static int op_and_(calculator_t* calc, value_t a, value_t b, value_t result)
{
	return and_(a, *(int64_unsigned*)b, calc->data->size, calc->data->is_unsigned, calc->data->is_float, result);
}

static int op_or_(calculator_t* calc, value_t a, value_t b, value_t result)
{
	return or_(a, *(int64_unsigned*)b, calc->data->size, calc->data->is_unsigned, calc->data->is_float, result);
}

static int op_not_(calculator_t* calc, value_t a,value_t b, value_t result)
{
	(void)b;//ignore b,not needed in not operation
	return not_(a, calc->data->size, result);
}

static int op_shift_left_(calculator_t* calc, value_t a, value_t b, value_t result)
{
	return shift_left(a, *(int64_unsigned*)b, calc->data->size, calc->data->is_unsigned, calc->data->is_float, result);
}

static int op_shift_right_(calculator_t* calc, value_t a, value_t b, value_t result)
{
	return shift_right(a, *(int64_unsigned*)b, calc->data->size, calc->data->is_unsigned, calc->data->is_float, result);
}

static int op_add_(calculator_t* calc, value_t a, value_t b, value_t result)
{
	return add(a, b, calc->data->size, calc->data->is_unsigned, calc->data->is_float, result);
}

static int op_subtract_(calculator_t* calc, value_t a, value_t b, value_t result)
{
	return subtract(a, b, calc->data->size, calc->data->is_unsigned, calc->data->is_float, result);
}

static int op_multiply_(calculator_t* calc, value_t a, value_t b, value_t result)
{
	return multiply(a, b, calc->data->size, calc->data->is_unsigned, calc->data->is_float, result);
}

static int op_divide_(calculator_t* calc, value_t a, value_t b, value_t result)
{
	return divide(a, b, calc->data->size, calc->data->is_unsigned, calc->data->is_float, result);
}

static int op_modulo_(calculator_t* calc, value_t a, value_t b, value_t result)
{
	return modulo(a, b, calc->data->size, calc->data->is_unsigned, calc->data->is_float, result);
}

calculator_t* new_calculator(enum Mode mode, enum Size size,bool unsigned_flag)
{
	calculator_t* calc = (calculator_t*)malloc(sizeof(calculator_t));
	if (calc == NULL)
	{
		return NULL;
	}
	calc->data = (calculator_data_t*)malloc(sizeof(calculator_data_t));
	if (calc->data == NULL)
	{
		free(calc);
		return NULL;
	}
	calc->data->is_float = (mode == float_mode) ? true : false;
	calc->data->is_int_mode = (mode == int_mode) ? true : false;
	calc->data->is_unsigned = unsigned_flag;
	if (mode == int_mode){
		switch (size) {
		case 8:

		case 16:

		case 32:

		case 64:
			calc->data->size = size;
			break;
		default:
			calc->data->size = 32;
		}
	}
	else {
		switch (size) {
		case 32:

		case 64:
			calc->data->size = size;
			break;
		default:
			calc->data->size = 32;
		}
	}
	memset(calc->data->value, 0, sizeof(calc->data->value));
	calc-> xor = op_xor_;
	calc-> and = op_and_;
	calc-> or = op_or_;
	calc-> not = op_not_;
	calc-> shift_left = op_shift_left_;
	calc-> shift_right = op_shift_right_;
	calc-> add = op_add_;
	calc-> subtract = op_subtract_;
	calc-> multiply = op_multiply_;
	calc-> divide = op_divide_;
	calc-> modulo = op_modulo_;
	return calc;
}

int calculator_switch_mode(calculator_t* calc, enum Mode mode, enum Size size,bool unsigned_flag) {
	int status_code = SUCCESS;
	if (calc == NULL || calc->data == NULL) {
		status_code = NULL_POINTER;
		goto exit;
	}
	if (mode == int_mode) {
		switch (size) {
		case 8:

		case 16:

		case 32:

		case 64:
			calc->data->size = size;
			break;
		default:
			status_code = INVALID_SIZE;
			goto exit;
		}
	}
	else {
		switch (size) {
		case 32:

		case 64:
			calc->data->size = size;
			break;
		default:
			status_code = INVALID_SIZE;
			goto exit;
		}
	}
	calc->data->is_float = (mode == float_mode) ? true : false;
	calc->data->is_int_mode = (mode == int_mode) ? true : false;
	calc->data->is_unsigned = unsigned_flag;
exit:
	return status_code;
}

int save_value_to_calculator(calculator_t* calc, value_t value) {
	int status_code = SUCCESS;
	if (calc == NULL || calc->data == NULL || value == NULL) {
		status_code = NULL_POINTER;
		goto exit;
	}
	memcpy(calc->data->value, value, sizeof(calc->data->value));
exit:
	return status_code;
}

int get_value_from_calculator(calculator_t* calc, value_t value) {
	int status_code = SUCCESS;
	if (calc == NULL || calc->data == NULL || value == NULL) {
		status_code = NULL_POINTER;
		goto exit;
	}
	memcpy(value, calc->data->value, sizeof(calc->data->value));
exit:
	return status_code;
}

void calculator_destroy(calculator_t* calc) {
	if (calc != NULL) {
		if (calc->data != NULL) {
			free(calc->data);
		}
		free(calc);
	}
}