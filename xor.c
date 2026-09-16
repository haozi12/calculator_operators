#include "include/operator.h"
int xor_(value_t a,int64_unsigned b,size_t bits,bool is_unsigned,bool is_float,value_t result){
    int status_code = SUCCESS;
    if (a == NULL || result == NULL){
        status_code = NULL_POINTER;
        goto exit;
    }
    if (is_float){
        switch (bits)
        {
        case 32:
            *(int32_unsigned*)result = *(int32_unsigned*)a ^ (int32_unsigned)b;
            goto exit;
            break;
        case 64:
            *(int64_unsigned*)result = *(int64_unsigned*)a ^ (int64_unsigned)b;
            goto exit;
            break;
        default:
            status_code = INVALID_SIZE;
            goto exit;
            break;
        }
    }
    if(is_unsigned){
        switch (bits)
        {
        case 8:
            *(int8_unsigned*)result = *(int8_unsigned*)a ^ (int8_unsigned)b;
            break;
        case 16:
            *(int16_unsigned*)result = *(int16_unsigned*)a ^ (int16_unsigned)b;
            break;
        case 32:
            *(int32_unsigned*)result = *(int32_unsigned*)a ^ (int32_unsigned)b;
            break;
        case 64:
            *(int64_unsigned*)result = *(int64_unsigned*)a ^ (int64_unsigned)b;
            break;
        default:
            status_code = INVALID_SIZE;
            goto exit;
            break;
        }
    }
    else{
        switch (bits)
        {
        case 8:
            *(int8_signed*)result = *(int8_signed*)a ^ (int8_signed)b;
            break;
        case 16:
            *(int16_signed*)result = *(int16_signed*)a ^ (int16_signed)b;
            break;
        case 32:
            *(int32_signed*)result = *(int32_signed*)a ^ (int32_signed)b;
            break;
        case 64:
            *(int64_signed*)result = *(int64_signed*)a ^ (int64_signed)b;
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