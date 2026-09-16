#include "include/workspace.h"
float32 get_float32_value(value_t value) {
	return (value == NULL) ? 0.0f : *(float32*)value;
}

float64 get_float64_value(value_t value) {
	return (value == NULL) ? 0.0 : *(float64*)value;
}

int8_signed get_int8_signed_value(value_t value) {
	return (value == NULL) ? 0 : *(int8_signed*)value;
}

int8_unsigned get_int8_unsigned_value(value_t value) {
	return (value == NULL) ? 0 : *(int8_unsigned*)value;
}

int16_signed get_int16_signed_value(value_t value) {
	return (value == NULL) ? 0 : *(int16_signed*)value;
}

int16_unsigned get_int16_unsigned_value(value_t value) {
	return (value == NULL) ? 0 : *(int16_unsigned*)value;
}

int32_signed get_int32_signed_value(value_t value) {
	return (value == NULL) ? 0 : *(int32_signed*)value;
}
int32_unsigned get_int32_unsigned_value(value_t value) {
	return (value == NULL) ? 0 : *(int32_unsigned*)value;
}
int64_signed get_int64_signed_value(value_t value) {
	return (value == NULL) ? 0 : *(int64_signed*)value;
}
int64_unsigned get_int64_unsigned_value(value_t value) {
	return (value == NULL) ? 0 : *(int64_unsigned*)value;
}

int write_float32_value(value_t value_slot, float32 value) {
	if (value_slot == NULL) {
		return NULL_POINTER;
	}
	*(float32*)value_slot = value;
	return SUCCESS;
}

int write_float64_value(value_t value_slot, float64 value) {
	if (value_slot == NULL) {
		return NULL_POINTER;
	}
	*(float64*)value_slot = value;
	return SUCCESS;
}

int write_int8_signed_value(value_t value_slot, int8_signed value) {
	if (value_slot == NULL) {
		return NULL_POINTER;
	}
	*(int8_signed*)value_slot = value;
	return SUCCESS;
}

int write_int8_unsigned_value(value_t value_slot, int8_unsigned value) {
	if (value_slot == NULL) {
		return NULL_POINTER;
	}
	*(int8_unsigned*)value_slot = value;
	return SUCCESS;
}

int write_int16_signed_value(value_t value_slot, int16_signed value) {
	if (value_slot == NULL) {
		return NULL_POINTER;
	}
	*(int16_signed*)value_slot = value;
	return SUCCESS;
}

int write_int16_unsigned_value(value_t value_slot, int16_unsigned value) {
	if (value_slot == NULL) {
		return NULL_POINTER;
	}
	*(int16_unsigned*)value_slot = value;
	return SUCCESS;
}

int write_int32_signed_value(value_t value_slot, int32_signed value) {
	if (value_slot == NULL) {
		return NULL_POINTER;
	}
	*(int32_signed*)value_slot = value;
	return SUCCESS;
}
int write_int32_unsigned_value(value_t value_slot, int32_unsigned value) {
	if (value_slot == NULL) {
		return NULL_POINTER;
	}
	*(int32_unsigned*)value_slot = value;
	return SUCCESS;
}
int write_int64_signed_value(value_t value_slot, int64_signed value) {
	if (value_slot == NULL) {
		return NULL_POINTER;
	}
	*(int64_signed*)value_slot = value;
	return SUCCESS;
}
int write_int64_unsigned_value(value_t value_slot, int64_unsigned value) {
	if (value_slot == NULL) {
		return NULL_POINTER;
	}
	*(int64_unsigned*)value_slot = value;
	return SUCCESS;
} 