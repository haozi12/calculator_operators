#include "include/memory_view.h"
#include "include/workspace.h"
int memory_view(value_t source,size_t bits,FILE* stream){
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
    fprintf(stream,"Hex:");
    for (size_t i = bytes; i > 0; i--){
        if (i != bytes){
            fprintf(stream," ");
        }
        fprintf(stream,"%02X",(int8_unsigned)temp[i - 1]);
    }
    fprintf(stream,"\n");
    fprintf(stream,"Oct:");
    for (size_t i = bytes; i > 0; i--){
        if (i != bytes){
            fprintf(stream," ");
        }
        fprintf(stream,"%03o",(int8_unsigned)temp[i - 1]);
    }
    fprintf(stream,"\n");
    fprintf(stream,"Bin:");
    for (size_t i = bytes; i > 0; i--){
        if (i != bytes){
            fprintf(stream," ");
        }
        for (int j = 7; j >= 0; j--){
            fprintf(stream,"%u",((int8_unsigned)temp[i - 1] >> j) & 1);
        }
    }
    fprintf(stream,"\n");
exit:
    return status_code;
}