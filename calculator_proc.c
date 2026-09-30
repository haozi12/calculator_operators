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
	enum Operator last_op;
	alignas(long long) int8_unsigned Last_op_1[8];
	alignas(long long) int8_unsigned Last_op_2[8];
	alignas(long long) int8_unsigned Last_result[8];
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
	memset(calc->data->Last_op_1, 0, Calculator_Value_Size);
	memset(calc->data->Last_op_2, 0, Calculator_Value_Size);
	memset(calc->data->Last_result, 0, Calculator_Value_Size);
	calc->data->last_op = NOTHING;
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

int save_Last(calculator_t* calc, value_t op_1, value_t op_2,value_t result, enum Operator op)
{
	int status_code = SUCCESS;
	if (calc == NULL || calc->data == NULL || op_1 == NULL || op_2 == NULL) {
		status_code = NULL_POINTER;
		goto exit;
	}
	calc->data->last_op = op;
	memcpy(calc->data->Last_op_1, op_1,Calculator_Value_Size);
	memcpy(calc->data->Last_op_2, op_2, Calculator_Value_Size);
	memcpy(calc->data->Last_result, result, Calculator_Value_Size);
exit:
	return status_code;
}

int get_Last(calculator_t* calc, value_t op_1 , value_t op_2,value_t result,enum Operator *op) {
	int status_code = SUCCESS;
	if (calc == NULL || calc->data == NULL || op_1 == NULL || op_2 == NULL) {
		status_code = NULL_POINTER;
		goto exit;
	}
	*op = calc->data->last_op;
	memcpy(op_1,calc->data->Last_op_1, Calculator_Value_Size);
	memcpy(op_2,calc->data->Last_op_2, Calculator_Value_Size);
	memcpy(result,calc->data->Last_result,Calculator_Value_Size);
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