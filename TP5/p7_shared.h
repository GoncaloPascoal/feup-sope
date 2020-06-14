
#define NUM_OPS 4

const char operations[] = {'+', '-', '*', '/'};

typedef struct {
    int a, b;
} Request;

typedef enum {
    INVALID = -1,
    INT,
    FLOAT
} ResultType;

typedef struct {
    ResultType type;
    union {
        int intResult;
        float floatResult;
    };
} Result;
