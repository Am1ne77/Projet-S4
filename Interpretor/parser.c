#include "interpretor.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <err.h>

Stack* shunting_yard (Array* input)
{
    Stack *res = stack_new(input->len+1);
    Stack *ope_stack = stack_new(input->len+1);

    while(!queue_is_empty(input->q))
    {
        Token* t = array_dequeue(input);
        switch(t->tokentype)
        {
            case other:
                stack_push(res,t);
                break;

            case open_parentheses:
                stack_push(ope_stack,t);
                break;

            case close_parentheses:
                if(stack_is_empty(ope_stack))
                    errx(EXIT_FAILURE,"parser : mismatched parenthesis");

                Token* ope = (Token*)stack_pop(ope_stack);
                while(ope->tokentype != open_parentheses)
                {
                    if(stack_is_empty(ope_stack))
                        errx(EXIT_FAILURE,"parser: mismatched parenthesis");
                    stack_push(res,ope);
                    ope = (Token*)stack_pop(ope_stack);
                }
                break;

            default:
                while(!stack_is_empty(ope_stack) &&
                        ((Token*)stack_peek(ope_stack))->tokentype != open_parentheses &&
                        t->prioroty <= ((Token*)stack_peek(ope_stack))->prioroty)
                     stack_push(res,stack_pop(ope_stack));

                stack_push(ope_stack,t);
        }
    }

    while(!stack_is_empty(ope_stack))
        stack_push(res,stack_pop(ope_stack));

    return res;
}
