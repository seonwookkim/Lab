#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef
        struct {
                void * buffer ;
                int unit ;
                int capacity ;
                int top ;
        }
        stack ;

stack *
create_stack (int capacity, int unit) ;

void
delete_stack (stack * stack) ;

int
push (stack * stack, void * elem) ;

int
pop (stack * stack, void * elem) ;

int
is_empty (stack * stack) ;

int
is_full (stack * stack) ;

int
get_size (stack * stack) ;

int
get_element (stack * stack, int index, void * elem) ;
//
stack *
create_stack (int capacity, int unit)
{
        stack * st = malloc(sizeof(stack)) ;
        st->capacity = capacity ;
        st->unit = unit ;
        st->top = 0 ;
        st->buffer = calloc(capacity, unit) ;
        return st ;
}

void
delete_stack (stack * st)
{
        if (st->buffer != 0x0)
                free(st->buffer) ;
        free(st) ;
}

int
push (stack * st, void * elem)
{
        if (is_full(st))
                return 1 ;

        memcpy(st->buffer + ((st->top) * (st->unit)), elem, st->unit) ;
        st->top += 1 ;

        return 0 ;
}

int
pop (stack * st, void * elem)
{
        if (is_empty(st))
                return 1 ;

        memcpy(elem, st->buffer + (st->top - 1) * st->unit, st->unit) ;
        st->top -= 1 ;
        return 0;
}

int
is_empty (stack * st)
{
        return (st->top == 0) ;
}

int
is_full (stack * st)
{
        return (st->top == st->capacity) ;
}

int
get_size (stack * st)
{
        return st->top ;
}

int
get_element (stack * st, int index, void * elem)
{
        if (st->top <= index)
                return 1 ;

        memcpy(elem, st->buffer + index * st->unit, st->unit) ;
        return 0 ;
}
//
typedef enum { Result, Value, Molecular, Open } token_type ;

typedef struct {
        int value ;
        token_type type ;
} token_t ;

int
main()
{
        stack* input = create_stack(100, sizeof(token_t)) ;
        stack* calculator = create_stack(100, sizeof(token_t)) ;
        token_t size, elem ;
        size.value = 0 ;
        char formular[100] ;

        scanf("%s", formular) ;
        for(int i = 0 ; formular[i] != 0 ; i++) {
                size.value += 1 ;
        }
        for(int i = 0 ; i < size.value ; i++) {
                push(calculator, &(formular[i])) ;
        }
        for(int i = 0 ; i < size.value ; i++) {
                pop(calculator, &elem) ;
                push(input, &elem) ;
        }

        do {
                char elem ;

                pop(input, &elem) ;
                if(isdigit(elem)) {
                        token_t num, result, tok ;
                        result.type = Result ;
                        num.type = Value ;
                        num.value = atoi(&elem) ;

                        if(calculator->top == 0){
                                push(calculator, &num) ;
                                continue ;
                        }
                
                        pop(calculator, &tok) ;
                        if(calculator->top == 0 || tok.type == Open) {
                                if(tok.type == Result) {
                                        result.value = tok.value ;
                                        result.value = tok.value * num.value ;

                                        push(calculator, &result) ;
                                }
                                else if(tok.type == Molecular) {
                                        result.value = tok.value ;
                                        result.value = tok.value * num.value ;

                                        push(calculator, &result) ;
                                }
                                else {
                                        push(calculator, &tok) ;
                                        push(calculator, &num) ;
                                }
                        }
                        
                        else if(tok.type == Molecular || tok.type == Result) {
                                if(tok.type == Result) {
                                        result.value = tok.value ;
                                        result.value = tok.value * num.value ;
                                }
                                else
                                        result.value = tok.value * num.value ;

                                push(calculator, &result) ;
                        }
                }
                else {
                        switch(elem) {
                                case '(' : {
                                        token_t tok ;
                                        tok.type = Open ;
                                        push(calculator, &tok) ;
                                        break ;
                                }
                                case ')' : {
                                        token_t tok, tok2, result ;
                                        result.type = Result ;
                                        stack* temporary = create_stack(100, sizeof(token_t)) ;
                                        do {
                                                pop(calculator, &tok) ;
                                                if(tok.type == Molecular || tok.type == Open) {
                                                        if(tok.type == Open) {
                                                                result.value = 0 ;
                                                                do {
                                                                        pop(temporary, &tok2) ;
                                                                        result.value += tok2.value ;
                                                                } while(!(temporary->top == 0)) ;
                                                                push(calculator, &result) ;
                                                        }
                                                        else
                                                                push(temporary, &tok) ;
                                                }
                                                else if(tok.type == Result) {
                                                        push(temporary, &tok) ;
                                                }
                                        } while(tok.type != Open) ;
                                        break ;
                                }
                                case 'C' : {
                                        token_t t1, t2, result ;
                                        result.type = Result ;
                                        t1.type = Molecular ;
                                        t1.value = 12 ;
                                        if(calculator->top !=0) {
                                                pop(calculator, &t2) ;
                                                if(t2.type == Value) {
                                                        result.value = 0 ;
                                                        result.value = t2.value * t1.value ;
                                                        push(calculator, &result) ;
                                                        break ;
                                                }
                                                else
                                                push(calculator, &t2) ;
                                        }
                                        push(calculator, &t1) ;
                                        if(is_empty(input)) {
                                                result.value = 0 ;
                                                do {
                                                        pop(calculator, &t2) ;
                                                        result.value += t2.value ;
                                                } while(!(calculator->top == 0)) ;
                                                        push(calculator, &result) ;
                                                break ;
                                        }
                                        break;
                                }
                                case 'H' :{
                                        token_t t1, t2, result ;
                                        result.type = Result ;
                                        t1.type = Molecular ;
                                        t1.value = 1 ;
                                        if(calculator->top !=0 ) {
                                                pop(calculator, &t2) ;
                                                if(t2.type == Value) {
                                                        result.value = 0 ;
                                                        result.value = t2.value * t1.value ;
                                                        push(calculator, &result) ;
                                                        break ;
                                                }
                                                else
                                                push(calculator, &t2) ;
                                        }
                                        push(calculator, &t1) ;
                                        if(is_empty(input)) {
                                                result.value = 0 ;
                                                do {
                                                        pop(calculator, &t2) ;
                                                        result.value += t2.value ;
                                                } while(!(calculator->top == 0)) ;
                                                push(calculator, &result) ;
                                                break ;
                                        }
                                        break ;
                                }
                                case 'O' :{
                                        token_t t1, t2, result ;
                                        result.type = Result ;
                                        t1.type = Molecular ;
                                        t1.value = 16 ;
                                        if(calculator->top !=0 ) {
                                                pop(calculator, &t2) ;
                                                if(t2.type == Value) {
                                                        result.value = 0 ;
                                                        result.value = t2.value * t1.value ;
                                                        push(calculator, &result) ;
                                                        break ;
                                                }
                                                push(calculator, &t2) ;
                                        }
                                        push(calculator, &t1) ;
                                        if(is_empty(input)) {
                                                result.value = 0 ;
                                                do {
                                                        pop(calculator, &t2) ;
                                                        result.value += t2.value ;
                                                } while(!(calculator->top == 0)) ;
                                                push(calculator, &result) ;
                                                break ;
                                        }
                                        break ;
                                }
                        }
                }
        } while(!(is_empty(input))) ;

        token_t result, tok ;
        result.type = Result ;
        pop(calculator, &result) ;

        if(!(is_empty(calculator))) {
            do {
                pop(calculator, &tok) ;
                result.value += tok.value ;
            } while (!(is_empty(calculator))) ;
        }
        printf("%d\n", result.value) ;

        delete_stack(input) ;
        delete_stack(calculator) ;
}
