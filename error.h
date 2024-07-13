#ifndef DEF_ERROR
#define DEF_ERROR

typedef enum ErrorCode
{
    SUCCESS = 0,
    MEMORY_ERROR,
    DIMENSION_ERRROR,
    DEFINITION_ERROR,
} ErrorCode;

typedef struct math_object
{
    void* object;
    ErrorCode err;
} Result;

#endif