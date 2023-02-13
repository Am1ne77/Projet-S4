#include "interpretor.h"
#include <stddef.h>
#include <string.h>

Stack* shunting_yard (Array* input)
{
    Stack *result = stack_new(input->len+1); 
    Stack *s = stack_new(input->len+1);

    for(size_t i = 0; i < input->len; i++)
    {
        Token* cur = input->start[i];
        if(cur->tokentype == other)
            stack_push(result, cur);

        else
        {
            if(stack_is_empty(s))
                stack_push(s, cur);
            
            else
            {
                Token* aux = stack_pop(s);
                if(cur->prioroty > aux->prioroty)
                {
                    stack_push(s, aux);
                    stack_push(s, cur);
                }
                
                else
                {
                    stack_push(result, aux);
                    stack_push(s, cur);
                }
            }
        }
    }

    while(! stack_is_empty(s))
        stack_push(result,stack_pop(s));

    return result;
}
