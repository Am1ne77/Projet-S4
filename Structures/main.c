#include "vector.h"

int main()
{
    struct vector* v = vector_new();
    for(size_t i = 0; i < 100; i++)
    {
        vector_push(v, i);
    }
    vector_print(v);
    vector_free(v);
    return 0;
}
