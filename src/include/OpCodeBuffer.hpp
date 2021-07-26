#ifndef PUBLIC_OP_CODE_BUFFER
#define PUBLIC_OP_CODE_BUFFER

typedef unsigned char byte;
class OpCodeLine
{
private:
    /* data */
public:
    OpCodeLine();
    ~OpCodeLine();
    int line;
};

OpCodeLine::OpCodeLine()
{
}

OpCodeLine::~OpCodeLine()
{
}

/*字节码格式*/
class OpCodeBuffer
{
private:
public:
    OpCodeBuffer();
    ~OpCodeBuffer();
    int pc;
    OpCodeLine *codeLine;
    int opCodelineSize;
    unsigned char *code;
};

OpCodeBuffer::OpCodeBuffer()
{
}

OpCodeBuffer::~OpCodeBuffer()
{
}
#endif