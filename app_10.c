// app_10.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_WARNINGS
#include "include/workspace.h"
#include "include/calculator.h"
#include "include/memory_view.h"
#include <stdalign.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

enum Operator {
	NOTHING,
	OP_XOR,
	OP_AND,
	OP_OR,
	OP_NOT,
	OP_SHIFT_LEFT,
	OP_SHIFT_RIGHT,
	OP_ADD,
	OP_SUBTRACT,
	OP_MULTIPLY,
	OP_DIVIDE,
	OP_MODULO
};

typedef struct calc_app_t calc_app_t;

typedef int (*app_function)(calc_app_t* app);

typedef struct calc_app_t{
	value_slot oprand_1;
	value_slot oprand_2;
	value_slot result;
	calculator_t* calc;
	size_t max_shift;
	enum Mode mode;
	enum Size size;
	enum Operator current_operator;
	bool unsigned_flag;
	app_function value_display;
	app_function calculate;
	FILE* output_stream;
	int (*set_oprands)(calc_app_t* app, value_t oprand_1, value_t oprand_2);
	int (*app_save_value)(calc_app_t* app, value_t value);
	int (*get_saved_value)(calc_app_t* app, value_t value);
	int (*switch_operator)(calc_app_t* app, enum Operator op);
	int (*switch_mode)(calc_app_t* app, enum Mode mode, enum Size size, bool unsigned_flag);
}calc_app_t;

calc_app_t* new_calc_app(enum Mode mode, enum Size size, bool unsigned_flag,FILE* out_stream);
int calc_app_destroy(calc_app_t* app);
int app_value_display(calc_app_t* app);
int app_save_value(calc_app_t* app, value_t value);
int app_get_saved_value(calc_app_t* app, value_t value);
int switch_calc_app_mode(calc_app_t* app, enum Mode mode, enum Size size, bool unsigned_flag);
int app_calculate(calc_app_t* app);
int app_set_oprands(calc_app_t* app,value_t oprand_1,value_t oprand_2);
int app_switch_operator(calc_app_t* app, enum Operator op);
int run_app(int argc,char** argv);


calc_app_t* new_calc_app(enum Mode mode, enum Size size, bool unsigned_flag,FILE* out_stream) {
	calc_app_t* app = (calc_app_t*)malloc(sizeof(calc_app_t));
	if (app == NULL || out_stream == NULL) {
		return NULL;
	}
	app->calc = new_calculator(mode, size, unsigned_flag);
	if (app->calc == NULL) {
		free(app);
		return NULL;
	}
	memset(app->oprand_1.value, 0, sizeof(app->oprand_1.value));
	memset(app->oprand_2.value, 0, sizeof(app->oprand_2.value));
	memset(app->result.value, 0, sizeof(app->result.value));
	app->output_stream = out_stream;
	app->mode = mode;
	app->size = size;
	app->set_oprands = app_set_oprands;
	app->unsigned_flag = unsigned_flag;
	app->max_shift = (size_t)size - 1;
	app->current_operator = OP_ADD;
	app->calculate = app_calculate;
	app->value_display = app_value_display;
	app->app_save_value = app_save_value;
	app->get_saved_value = app_get_saved_value;
	app->switch_mode = switch_calc_app_mode;
	app->switch_operator = app_switch_operator;

	return app;
}

int calc_app_destroy(calc_app_t* app) {
	if (app == NULL) {
		return NULL_POINTER;
	}
	calculator_destroy(app->calc);
	free(app);
	return SUCCESS;
}

int app_save_value(calc_app_t* app, value_t value) {
	if (app == NULL || value == NULL) {
		return NULL_POINTER;
	}
	return save_value_to_calculator(app->calc, value);
}

int app_get_saved_value(calc_app_t* app, value_t value) {
	if (app == NULL || value == NULL) {
		return NULL_POINTER;
	}
	return get_value_from_calculator(app->calc, value);
}

int switch_calc_app_mode(calc_app_t* app, enum Mode mode, enum Size size, bool unsigned_flag) {
	int status_code = SUCCESS;
	if (app == NULL) {
		status_code = NULL_POINTER;
		goto exit;
	}
	status_code = calculator_switch_mode(app->calc, mode, size, unsigned_flag);
	if (status_code != SUCCESS) {
		goto exit;
	}
	app->mode = mode;
	app->size = size;
	app->unsigned_flag = unsigned_flag;
	app->max_shift = (size_t)size - 1;
exit:
	return status_code;
}

int app_value_display(calc_app_t* app) {
	int status_code = SUCCESS;
	if (app == NULL) {
		status_code = NULL_POINTER;
		goto exit;
	}
	if (app->mode == float_mode) {
		switch (app->size) {
		case 32:
			fprintf(app->output_stream, "oprand_1: %f\n", get_float32_value(app->oprand_1.value));
			switch (app->current_operator) {
			case OP_AND:
			case OP_OR:
			case OP_NOT:
			case OP_XOR:
			case OP_SHIFT_LEFT:
			case OP_SHIFT_RIGHT:
				fprintf(app->output_stream, "oprand_2: %llu\n", get_int64_unsigned_value(app->oprand_2.value));
				break;
			default:
				fprintf(app->output_stream, "oprand_2: %f\n", get_float32_value(app->oprand_2.value));
				break;
			}
			fprintf(app->output_stream, "result: %f\n", get_float32_value(app->result.value));
			memory_view(app->result.value, 32, app->output_stream);
			break;
		case 64:
			fprintf(app->output_stream, "oprand_1: %lf\n", get_float64_value(app->oprand_1.value));
			switch (app->current_operator) {
			case OP_AND:
			case OP_OR:
			case OP_NOT:
			case OP_XOR:
			case OP_SHIFT_LEFT:
			case OP_SHIFT_RIGHT:
				fprintf(app->output_stream, "oprand_2: %llu\n", get_int64_unsigned_value(app->oprand_2.value));
				break;
			default:
				fprintf(app->output_stream, "oprand_2: %lf\n", get_float64_value(app->oprand_2.value));
				break;
			}
			fprintf(app->output_stream, "result: %lf\n", get_float64_value(app->result.value));
			memory_view(app->result.value, 64, app->output_stream);
			break;
		default:
			status_code = INVALID_SIZE;
			goto exit;
		}
	}
	if (app->mode == int_mode) {
		if (app->unsigned_flag) {
			switch (app->size) {
			case 8:
				fprintf(app->output_stream, "oprand_1: %u\n", get_int8_unsigned_value(app->oprand_1.value));
				fprintf(app->output_stream, "oprand_2: %u\n", get_int8_unsigned_value(app->oprand_2.value));
				fprintf(app->output_stream, "result: %u\n", get_int8_unsigned_value(app->result.value));
				memory_view(app->result.value, 8, app->output_stream);
				break;
			case 16:
				fprintf(app->output_stream, "oprand_1: %u\n", get_int16_unsigned_value(app->oprand_1.value));
				fprintf(app->output_stream, "oprand_2: %u\n", get_int16_unsigned_value(app->oprand_2.value));
				fprintf(app->output_stream, "result: %u\n", get_int16_unsigned_value(app->result.value));
				memory_view(app->result.value, 16, app->output_stream);
				break;
			case 32:
				fprintf(app->output_stream, "oprand_1: %u\n", get_int32_unsigned_value(app->oprand_1.value));
				fprintf(app->output_stream, "oprand_2: %u\n", get_int32_unsigned_value(app->oprand_2.value));
				fprintf(app->output_stream, "result: %u\n", get_int32_unsigned_value(app->result.value));
				memory_view(app->result.value, 32, app->output_stream);
				break;
			case 64:
				fprintf(app->output_stream, "oprand_1: %llu\n", get_int64_unsigned_value(app->oprand_1.value));
				fprintf(app->output_stream, "oprand_2: %llu\n", get_int64_unsigned_value(app->oprand_2.value));
				fprintf(app->output_stream, "result: %llu\n", get_int64_unsigned_value(app->result.value));
				memory_view(app->result.value, 64, app->output_stream);
				break;
			default:
				status_code = INVALID_SIZE;
				goto exit;
			}
		}
		else {
			switch (app->size) {
			case 8:
				fprintf(app->output_stream, "oprand_1: %d\n", get_int8_signed_value(app->oprand_1.value));
				fprintf(app->output_stream, "oprand_2: %d\n", get_int8_signed_value(app->oprand_2.value));
				fprintf(app->output_stream, "result: %d\n", get_int8_signed_value(app->result.value));
				memory_view(app->result.value, 8, app->output_stream);
				break;
			case 16:
				fprintf(app->output_stream, "oprand_1: %d\n", get_int16_signed_value(app->oprand_1.value));
				fprintf(app->output_stream, "oprand_2: %d\n", get_int16_signed_value(app->oprand_2.value));
				fprintf(app->output_stream, "result: %d\n", get_int16_signed_value(app->result.value));
				memory_view(app->result.value, 16, app->output_stream);
				break;
			case 32:
				fprintf(app->output_stream, "oprand_1: %d\n", get_int32_signed_value(app->oprand_1.value));
				fprintf(app->output_stream, "oprand_2: %d\n", get_int32_signed_value(app->oprand_2.value));
				fprintf(app->output_stream, "result: %d\n", get_int32_signed_value(app->result.value));
				memory_view(app->result.value, 32, app->output_stream);
				break;

			case 64:
				fprintf(app->output_stream, "oprand_1: %lld\n", get_int64_signed_value(app->oprand_1.value));
				fprintf(app->output_stream, "oprand_2: %lld\n", get_int64_signed_value(app->oprand_2.value));
				fprintf(app->output_stream, "result: %lld\n", get_int64_signed_value(app->result.value));
				memory_view(app->result.value, 64, app->output_stream);
				break;
			default:
				status_code = INVALID_SIZE;
				goto exit;
			}
		}
	}
exit:
	return status_code;
}

int app_calculate(calc_app_t* app) {
	int status_code = SUCCESS;
	if (app == NULL) {
		status_code = NULL_POINTER;
		goto exit;
	}
	switch (app->current_operator) {
	case OP_XOR:
		status_code = app->calc->xor(app->calc, app->oprand_1.value, app->oprand_2.value, app->result.value);
		break;
	case OP_AND:
		status_code = app->calc->and(app->calc, app->oprand_1.value, app->oprand_2.value, app->result.value);
		break;
	case OP_OR:
		status_code = app->calc->or(app->calc, app->oprand_1.value, app->oprand_2.value, app->result.value);
		break;
	case OP_NOT:
		status_code = app->calc->not(app->calc, app->oprand_1.value, app->oprand_2.value, app->result.value);
		break;
	case OP_SHIFT_LEFT:
		if (*(int64_unsigned*)app->oprand_2.value > app->max_shift) {
			status_code = SHIFT_OVERFLOWED;
			goto exit;
		}
		status_code = app->calc->shift_left(app->calc, app->oprand_1.value, app->oprand_2.value, app->result.value);
		break;
	case OP_SHIFT_RIGHT:
		if (*(int64_unsigned*)app->oprand_2.value > app->max_shift) {
			status_code = SHIFT_OVERFLOWED;
			goto exit;
		}
		status_code = app->calc->shift_right(app->calc, app->oprand_1.value, app->oprand_2.value, app->result.value);
		break;
	case OP_ADD:
		status_code = app->calc->add(app->calc, app->oprand_1.value, app->oprand_2.value, app->result.value);
		break;
	case OP_SUBTRACT:
		status_code = app->calc->subtract(app->calc, app->oprand_1.value, app->oprand_2.value, app->result.value);
		break;
	case OP_MULTIPLY:
		status_code = app->calc->multiply(app->calc, app->oprand_1.value, app->oprand_2.value, app->result.value);
		break;
	case OP_DIVIDE:
		status_code = app->calc->divide(app->calc, app->oprand_1.value, app->oprand_2.value, app->result.value);
		break;
	case OP_MODULO:
		status_code = app->calc->modulo(app->calc, app->oprand_1.value, app->oprand_2.value, app->result.value);
		break;
	default:
		status_code = INVALID_SIZE;
		goto exit;
	}
exit:
	return status_code;
}

int app_set_oprands(calc_app_t* app, value_t oprand_1, value_t oprand_2) {
	int status_code = SUCCESS;
	if (app == NULL || oprand_1 == NULL || oprand_2 == NULL) {
		status_code = NULL_POINTER;
		goto exit;
	}
	memset(app->oprand_1.value,0,sizeof(app->oprand_1.value));
	memset(app->oprand_2.value, 0, sizeof(app->oprand_2.value));
	if (app->mode == int_mode) {
		switch (app->size) {
		case 8:
			*(int8_unsigned*)app->oprand_1.value = *(int8_unsigned*)oprand_1;
			*(int8_unsigned*)app->oprand_2.value = *(int8_unsigned*)oprand_2;
			break;
		case 16:
			*(int16_unsigned*)app->oprand_1.value = *(int16_unsigned*)oprand_1;
			*(int16_unsigned*)app->oprand_2.value = *(int16_unsigned*)oprand_2;
			break;
		case 32:
			*(int32_unsigned*)app->oprand_1.value = *(int32_unsigned*)oprand_1;
			*(int32_unsigned*)app->oprand_2.value = *(int32_unsigned*)oprand_2;
			break;
		case 64:
			*(int64_unsigned*)app->oprand_1.value = *(int64_unsigned*)oprand_1;
			*(int64_unsigned*)app->oprand_2.value = *(int64_unsigned*)oprand_2;
			break;
		default:
			status_code = INVALID_SIZE;
			goto exit;
			break;
		}
	}
	if (app->mode == float_mode) {
		switch (app->size) {
		case 32:
			switch (app->current_operator) {
			case OP_AND:
			case OP_OR:
			case OP_NOT:
			case OP_XOR:
			case OP_SHIFT_LEFT:
			case OP_SHIFT_RIGHT:
				*(float32*)app->oprand_1.value = *(float32*)oprand_1;
				*(int64_unsigned*)app->oprand_2.value = (int64_unsigned)*(float32*)oprand_2;
				break;
			default:
				*(float32*)app->oprand_1.value = *(float32*)oprand_1;
				*(float32*)app->oprand_2.value = *(float32*)oprand_2;
				break;
			}
			break;
		case 64:
			switch (app->current_operator) {
			case OP_AND:
			case OP_OR:
			case OP_NOT:
			case OP_XOR:
			case OP_SHIFT_LEFT:
			case OP_SHIFT_RIGHT:
				*(float64*)app->oprand_1.value = *(float64*)oprand_1;
				*(int64_unsigned*)app->oprand_2.value = (int64_unsigned)*(float64*)oprand_2;
				break;
			default:
				*(float64*)app->oprand_1.value = *(float64*)oprand_1;
				*(float64*)app->oprand_2.value = *(float64*)oprand_2;
				break;
			}
			break;
		default:
			status_code = INVALID_SIZE;
			goto exit;
			break;
		}
	}
exit:
	return status_code;
}

int app_switch_operator(calc_app_t* app, enum Operator op) {
	int status_code = SUCCESS;
	if (app == NULL) {
		status_code = NULL_POINTER;
		goto exit;
	}
	switch (op) {
	case OP_XOR:
	case OP_AND:
	case OP_OR:
	case OP_NOT:
	case OP_SHIFT_LEFT:
	case OP_SHIFT_RIGHT:
	case OP_ADD:
	case OP_SUBTRACT:
	case OP_MULTIPLY:
	case OP_DIVIDE:
	case OP_MODULO:
		app->current_operator = op;
		break;
	default:
		status_code = INVALID_SIZE;
		goto exit;
	}
exit:
	return status_code;
}

static int write_oprand_value(calc_app_t* app, value_t slot, const char* text) {
	int status_code = SUCCESS;
	if (app == NULL || slot == NULL || text == NULL) {
		status_code = NULL_POINTER;
		goto exit;
	}
	memset(slot, 0, Calculator_Value_Size);
	if (app->mode == int_mode) {
		if (app->unsigned_flag) {
			switch (app->size) {
			case 8:
				status_code = write_int8_unsigned_value(slot, (int8_unsigned)strtoull(text, NULL, 10));
				break;
			case 16:
				status_code = write_int16_unsigned_value(slot, (int16_unsigned)strtoull(text, NULL, 10));
				break;
			case 32:
				status_code = write_int32_unsigned_value(slot, (int32_unsigned)strtoull(text, NULL, 10));
				break;
			case 64:
				status_code = write_int64_unsigned_value(slot, (int64_unsigned)strtoull(text, NULL, 10));
				break;
			default:
				status_code = INVALID_SIZE;
				break;
			}
		}
		else {
			switch (app->size) {
			case 8:
				status_code = write_int8_signed_value(slot, (int8_signed)strtoll(text, NULL, 10));
				break;
			case 16:
				status_code = write_int16_signed_value(slot, (int16_signed)strtoll(text, NULL, 10));
				break;
			case 32:
				status_code = write_int32_signed_value(slot, (int32_signed)strtoll(text, NULL, 10));
				break;
			case 64:
				status_code = write_int64_signed_value(slot, (int64_signed)strtoll(text, NULL, 10));
				break;
			default:
				status_code = INVALID_SIZE;
				break;
			}
		}
	}
	if (app->mode == float_mode) {
		switch (app->size) {
		case 32:
			status_code = write_float32_value(slot, (float32)atof(text));
			break;
		case 64:
			status_code = write_float64_value(slot, (float64)atof(text));
			break;
		default:
			status_code = INVALID_SIZE;
			break;
		}
	}
exit:
	return status_code;
}

int app_main_loop(FILE* in_stream,FILE* out_stream){
	int status_code = SUCCESS;
	char* stream_state = NULL;
	char switch_[16] = {0};
	char mode_[16] = {0};
	char unsigned_[16] = {0};
	const int max_retry_count = 3;
	int try_count = 0;
	char input_buffer[128] = {0};
	enum Operator next_op = NOTHING;
	enum Size next_size = size_32;
	enum Mode next_mode = int_mode;
	bool unsigned_flag = false;
	int size_value = size_32;
	value_slot oprand_1 = {0};
	value_slot oprand_2 = {0};
	calc_app_t* app = NULL;
	if (in_stream == NULL || out_stream == NULL){
		status_code = NULL_POINTER;
		goto exit;
	}
entry:
	calc_app_destroy(app);
	app = new_calc_app(int_mode,size_32,false,out_stream);
	if (app == NULL ){
		status_code = NULL_POINTER;
	}
	else{
		status_code = SUCCESS;
	}
	try_count++;
	if (try_count == max_retry_count){
		goto exit;
	}
swith_mode:
	if (status_code != NULL_POINTER){
		status_code = app->switch_mode(app,next_mode,next_size,unsigned_flag);
		if (status_code != SUCCESS){
			goto error_treat;
		}
		if (next_op != NOTHING){
			status_code = app->switch_operator(app,next_op);
			if (status_code != SUCCESS){
				goto error_treat;
			}
		}
		if (app->mode == float_mode){
			fprintf(app->output_stream,">[mode] float %d\n",(int)app->size);
		}
		else{
			if (app->unsigned_flag){
				fprintf(app->output_stream,">[mode] int %d unsigned\n",(int)app->size);
			}
			else{
				fprintf(app->output_stream,">[mode] int %d signed\n",(int)app->size);
			}
		}
	}
	else{
		goto error_treat;
	}
app_calculation:
	fprintf(app->output_stream,">oprand_1:");
	stream_state = fgets(input_buffer,sizeof(input_buffer),in_stream);
	if (stream_state == NULL){
		goto exit;
	}
	if (input_buffer[0] == '?'){
		goto command;
	}
	status_code = write_oprand_value(app,oprand_1.value,input_buffer);
	if (status_code != SUCCESS){
		goto error_treat;
	}
	fprintf(app->output_stream,">oprand_2:");
	stream_state = fgets(input_buffer,sizeof(input_buffer),in_stream);
	if (stream_state == NULL){
		goto exit;
	}
	if (input_buffer[0] == '?'){
		goto command;
	}
	status_code = write_oprand_value(app,oprand_2.value,input_buffer);
	if (status_code != SUCCESS){
		goto error_treat;
	}
	fprintf(app->output_stream,">operator:");
	stream_state = fgets(input_buffer,sizeof(input_buffer),in_stream);
	if (stream_state == NULL){
		goto exit;
	}
	if (input_buffer[0] == '?'){
		goto command;
	}
	if (strncmp(input_buffer,"xor",(size_t)3) == 0){
		next_op = OP_XOR;
	}
	else if (strncmp(input_buffer,"and",(size_t)3) == 0){
		next_op = OP_AND;
	}
	else if (strncmp(input_buffer,"or",(size_t)2) == 0){
		next_op = OP_OR;
	}
	else if (strncmp(input_buffer,"not",(size_t)3) == 0){
		next_op = OP_NOT;
	}
	else if (strncmp(input_buffer,"shl",(size_t)3) == 0){
		next_op = OP_SHIFT_LEFT;
	}
	else if (strncmp(input_buffer,"shr",(size_t)3) == 0){
		next_op = OP_SHIFT_RIGHT;
	}
	else if (strncmp(input_buffer,"add",(size_t)3) == 0){
		next_op = OP_ADD;
	}
	else if (strncmp(input_buffer,"sub",(size_t)3) == 0){
		next_op = OP_SUBTRACT;
	}
	else if (strncmp(input_buffer,"mul",(size_t)3) == 0){
		next_op = OP_MULTIPLY;
	}
	else if (strncmp(input_buffer,"div",(size_t)3) == 0){
		next_op = OP_DIVIDE;
	}
	else if (strncmp(input_buffer,"mod",(size_t)3) == 0){
		next_op = OP_MODULO;
	}
	else{
		next_op = NOTHING;
	}
	status_code = app->switch_operator(app,next_op);
	if (status_code != SUCCESS){
		goto error_treat;
	}
	status_code = app->set_oprands(app,oprand_1.value,oprand_2.value);
	if (status_code != SUCCESS){
		goto error_treat;
	}
	status_code = app->calculate(app);
	if (status_code != SUCCESS){
		goto error_treat;
	}
	status_code = app->value_display(app);
	goto error_treat;
command:
	fprintf(app->output_stream,">command:");
	stream_state = fgets(input_buffer,sizeof(input_buffer),in_stream);
	if (stream_state == NULL){
		goto exit;
	}
	sscanf(input_buffer,"%15s %15s %d",switch_,mode_,&size_value);
	next_size = (enum Size)size_value;
	if (strcmp(switch_, "exit") == 0) {
		goto exit;
	}
	if (strcmp(switch_, "quit") == 0) {
		goto exit;
	}
	if (strcmp(switch_, "switch") != 0) {
		status_code = INVALID_SIZE;
		goto error_treat;
	}
	if (strcmp(mode_,"float") == 0){
		next_mode = float_mode;
	}
	else if (strcmp(mode_,"int") == 0){
		next_mode = int_mode;
		fprintf(app->output_stream,">unsigned?:");
		stream_state = fgets(input_buffer,sizeof(input_buffer),in_stream);
		if (stream_state == NULL){
			goto exit;
		}
		sscanf(input_buffer,"%15s",unsigned_);
		if (strcmp(unsigned_,"true") == 0){
			unsigned_flag = true;
		}
		else if (strcmp(unsigned_,"false") == 0){
			unsigned_flag = false;
		}
		else{
			status_code = INVALID_SIZE;
			goto error_treat;
		}
	}
	else{
		status_code = INVALID_SIZE;
		goto error_treat;
	}
	goto swith_mode;
error_treat:
	switch(status_code){
	case NULL_POINTER:
		goto entry;
		break;
	case SUCCESS:
		goto app_calculation;
	case INVALID_SIZE:
		fprintf(app->output_stream,">[invalid command] %s",input_buffer);
		goto command;
	case INTEGER_ZERO_DIVISION:
		fprintf(app->output_stream,">[error] zero division in integer mode\nLast:\n");
		app->value_display(app);
		goto app_calculation;
	case SHIFT_OVERFLOWED:
		fprintf(app->output_stream,">[error] shift count overflowed\nLast:\n");
		app->value_display(app);
		goto app_calculation;
	default:
		break;
	}
exit:
	return status_code;
}

int run_app(int argc,char** argv) {
	int status_code = SUCCESS;
	FILE* in_stream = NULL;
	FILE* out_stream = NULL;
	char* in_path = NULL;
	char* out_path = NULL;
	if (argc <= 1) {
		in_stream = stdin;
		out_stream = stdout;
		goto main_loop;
	}
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i],"-in") == 0) {
			if (i + 1 < argc && argv[i + 1][0] != '\0') {
				in_path = argv[i + 1];
				i++;
			}
		}
		if (strcmp(argv[i],"-out") == 0) {
			if (i + 1 < argc && argv[i + 1][0] != '\0') {
				out_path = argv[i + 1];
				i++;
			}
		}
	}
	if (in_path == NULL && out_path == NULL) {
		fprintf(stderr, "Please enter file name after -in and -out\n");
		goto exit;
	}
	in_stream = stdin;
	out_stream = stdout;
	if (in_path != NULL) {
		in_stream = fopen(in_path,"r");
		if (in_stream == NULL) {
			status_code = NULL_POINTER;
			goto exit;
		}
	}
	if (out_path != NULL) {
		out_stream = fopen(out_path,"w");
		if (out_stream == NULL) {
			status_code = NULL_POINTER;
			goto exit;
		}
	}
main_loop:
	status_code = app_main_loop(in_stream,out_stream);
exit:
	if (in_stream != NULL && in_stream != stdin) {
		fclose(in_stream);
	}
	if (out_stream != NULL && out_stream != stdout) {
		fclose(out_stream);
	}
	return status_code;
}

int main(int argc,char** argv) {
	return run_app(argc,argv);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件



// value_slot oprand_1 = { 0 };
// 	value_slot oprand_2 = { 0 };
// 	value_slot result = { 0 };
// 	calculator_t* calc = new_calculator(int_mode, size_32, false);
// 	if (calc == NULL) {
// 		printf("Failed to create calculator.\n");
// 		return -1;
// 	}
// 	write_int32_signed_value(oprand_1.value, 0x80000000);
// 	write_int32_signed_value(oprand_2.value, -2);
// 	if (calc->divide(calc, oprand_1.value, oprand_2.value, result.value) == INTEGER_ZERO_DIVISION) {
// 		printf("Error:Integer division by zero.\nLast ");
// 	}
// 	printf("Result: value = %d\n", get_int32_signed_value(result.value));
// 	save_value_to_calculator(calc, result.value);
// 	memory_view(result.value, 32, stdout);
// 	value_slot	value_from_calculator = { 0 };
// 	get_value_from_calculator(calc, value_from_calculator.value);
// 	printf("Calculator value: %d", get_int32_signed_value(value_from_calculator.value));
// 	calculator_destroy(calc);