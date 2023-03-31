#include "interpretor.h"
#include <stddef.h>
#include <stdio.h>
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

        else if(cur->tokentype == close_parentheses)
        {
            //Token* aux = stack_pop(s);
            while (cur->tokentype != open_parentheses)
            {
                cur = stack_pop(s);
                stack_push(result, cur);
            }
            stack_pop(result);
        }

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
        printf("Stack %lu: \n", i);
        print_token(cur, i);
        stack_display(s);
        stack_display(result);
    }

    while(! stack_is_empty(s))
        stack_push(result,stack_pop(s));

    return result;
}
