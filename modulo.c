#include "include/operator.h"
#include <math.h>
int modulo(value_t a, value_t b, size_t bits, bool is_unsigned, bool is_float, value_t result) {
	int status_code = SUCCESS;
	if (a == NULL || b == NULL || result == NULL) {
		status_code = NULL_POINTER;
		goto exit;
	}
	if (is_float) {
		switch (bits)
		{
		case 32:
			*(float32*)result = fmodf(*(float32*)a, *(float32*)b);
			goto exit;
			break;
		case 64:
			*(float64*)result = fmod(*(float64*)a, *(float64*)b);
			goto exit;
			break;
		default:
			status_code = INVALID_SIZE;
			goto exit;
		}
	}
	if (is_unsigned) {
		switch (bits)
		{
		case 8:
			if (*(int8_unsigned*)b == 0) {
				status_code = INTEGER_ZERO_DIVISION;
				goto exit;
			}
			*(int8_unsigned*)result = *(int8_unsigned*)a % *(int8_unsigned*)b;
			goto exit;
			break;
		case 16:
			if (*(int16_unsigned*)b == 0) {
				status_code = INTEGER_ZERO_DIVISION;
				goto exit;
			}
			*(int16_unsigned*)result = *(int16_unsigned*)a % *(int16_unsigned*)b;
			goto exit;
			break;
		case 32:
			if (*(int32_unsigned*)b == 0) {
				status_code = INTEGER_ZERO_DIVISION;
				goto exit;
			}
			*(int32_unsigned*)result = *(int32_unsigned*)a % *(int32_unsigned*)b;
			goto exit;
			break;
		case 64:
			if (*(int64_unsigned*)b == 0) {
				status_code = INTEGER_ZERO_DIVISION;
				goto exit;
			}
			*(int64_unsigned*)result = *(int64_unsigned*)a % *(int64_unsigned*)b;
			goto exit;
			break;
		default:
			status_code = INVALID_SIZE;
			break;
		}
	}
	else {
		switch (bits)
		{
		case 8:
			if (*(int8_signed*)b == 0) {
				status_code = INTEGER_ZERO_DIVISION;
				goto exit;
			}
			*(int8_signed*)result = *(int8_signed*)a % *(int8_signed*)b;
			goto exit;
			break;
		case 16:
			if (*(int16_signed*)b == 0) {
				status_code = INTEGER_ZERO_DIVISION;
				goto exit;
			}
			*(int16_signed*)result = *(int16_signed*)a % *(int16_signed*)b;
			goto exit;
			break;
		case 32:
			if (*(int32_signed*)b == 0) {
				status_code = INTEGER_ZERO_DIVISION;
				goto exit;
			}
			*(int32_signed*)result = *(int32_signed*)a % *(int32_signed*)b;
			goto exit;
			break;
		case 64:
			if (*(int64_signed*)b == 0) {
				status_code = INTEGER_ZERO_DIVISION;
				goto exit;
			}
			*(int64_signed*)result = *(int64_signed*)a % *(int64_signed*)b;
			goto exit;
			break;
		default:
			status_code = INVALID_SIZE;
			break;
		}
	}
exit:
	return status_code;
}