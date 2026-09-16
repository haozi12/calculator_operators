#include "include/operator.h"
int not_(value_t a, size_t bits, value_t result){
    int status_code = SUCCESS;
    if (a == NULL || result == NULL){
        status_code = NULL_POINTER;
        goto exit;
    }
    switch (bits)
    {
    case 8:
        *(int8_unsigned*)result = ~*(int8_unsigned*)a;
        break;
    case 16:
        *(int16_unsigned*)result = ~*(int16_unsigned*)a;
        break;
    case 32:
        *(int32_unsigned*)result = ~*(int32_unsigned*)a;
        break;
    case 64:
        *(int64_unsigned*)result = ~*(int64_unsigned*)a;
        break;
    default:
        status_code = INVALID_SIZE;
        goto exit;
        break;
    }
exit:
    return status_code;
}