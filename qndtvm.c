#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define DEBUG 0
enum flags{
    POSITIVE
    ZERO,
    NEGATIVE
}flag;

enum modes{
    INT8,
    INT16,
    INT32,
    INT64,

    UINT8,
    UINT16,
    UINT32,
    UINT64,

    FLOAT32,
    FLOAT64
}mode;

enum instructions{
    HALT,
    NOP,
    SET,
    STR,
    LD,
    COPY,
    JMP,
    JEQ,
    JNEQ,
    JZ,
    JNZ,
    CALL,
    CALLEQ,
    CALLNEQ,
    CALLZ,
    CALLNZ,
    RET,
    POP,
    PUSH,
    NOT,
    OR,
    AND,
    XOR,
    LSHIFT,
    RSHIFT,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD
};

union reg_t{
    int8_t value_int8;
    int16_t value_int16;
    int32_t value_int32;
    int64_t value_int64;

    uint8_t value_uint8;
    uint16_t value_uint16;
    uint32_t value_uint32;
    uint64_t value_uint64;

    float value_float32;
    double value_float64;

    uint8_t * ptr8;
    uint16_t * ptr16;
    uint32_t * ptr32;
    uint64_t * ptr64;
};


size_t memsize, filesize;
union reg_t memory, registers[8], program_counter, stack, interruption;
FILE* memfile;

int main(int argc, char* argv[]){
    if(argc < 2){
        printf("FATAL ERROR: There isn't any file specified.\n");
        return EXIT_FAILURE;
    }

    memfile = fopen(argv[1], "r");

    if(!memfile){
        printf("FATAL ERROR: There was a error opening the file.\n");
        return EXIT_FAILURE;
    }

    fseek(memfile, 0, SEEK_END);
    filesize = ftell(memfile);

    if(argc == 3){
        if(sscanf(argv[2], "%zu", &memsize) == EOF){
            printf("FATAL ERROR: The value introduced is not a valid number.\n");
            return EXIT_FAILURE;
        }
    }
    else{
        memsize = filesize;
    }

    memory.ptr64 = (uint64_t *) calloc(memsize, sizeof(uint64_t));

    if(!memory.ptr64){
        printf("FATAL ERROR: There was an error allocating memory.\n");
        return EXIT_FAILURE;
    }
    program_counter.ptr8 = memory.ptr8;
    while(*program_counter.ptr8 != HALT){
        switch(*program_counter.ptr8){
            default:
                if(DEBUG){
                    printf("Invalid opcode: %u\n", (unsigned int) *program_counter.ptr8);
                }
                continue;
        }
    }
    return 0;
}