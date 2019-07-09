#ifndef CODEGENERATORPACK_HPP
#define CODEGENERATORPACK_HPP

namespace wic
{
    typedef enum
    {
        EAX,
        EBX,
        ECX,
        EDX,
        ESI,
        EDI,
        ESP,
        EBP,
        XMM0,
        XMM1,
        XMM2,
        XMM3,
        NONE
    } cpu_registers;

    typedef struct fstream_p
    {
        long data_p;
        long code_p;
    } fstream_p;

    typedef enum
    {
        DATA,
        CODE,
        FUNCTION_CODE,
        LABEL_FLOAT
    } section_enum;

    typedef struct label_c
    {
        long code_l;
        long data_l;
        long float_l;
    } label_c;
}

#endif
