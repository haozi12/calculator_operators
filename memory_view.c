#include "include/memory_view.h"
#include "include/workspace.h"
#include <stdio.h>
int memory_view(value_t source,size_t bits){
    int status_code = SUCCESS;
    if (source == NULL){
        status_code = NULL_POINTER;
        goto exit;
    }
    if (bits % 8 != 0){
        status_code = INVALID_SIZE;
        goto exit;
    }
    size_t bytes = bits / 8;
    int8_unsigned* temp = (int8_unsigned*)source;
    printf("Hex:");
    for (size_t i = bytes; i > 0; i--){
        if (i != bytes){
            printf(" ");
        }
        printf("%02X",(int8_unsigned)temp[i - 1]);
    }
    printf("\n");
    printf("Oct:");
    for (size_t i = bytes; i > 0; i--){
        if (i != bytes){
            printf(" ");
        }
        printf("%03o",(int8_unsigned)temp[i - 1]);
    }
    printf("\n");
    printf("Bin:");
    for (size_t i = bytes; i > 0; i--){
        if (i != bytes){
            printf(" ");
        }
        for (int j = 7; j >= 0; j--){
            printf("%u",((int8_unsigned)temp[i - 1] >> j) & 1);
        }
    }
    printf("\n");
exit:
    return status_code;
}