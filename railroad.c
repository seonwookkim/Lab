#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
int
main()
{
    int n, m, num, elem, p, w;
    p = 0 ;
    elem = 0 ;   
    scanf("%d %d", &n, &m) ;
    
    stack * out = create_stack(n, sizeof(int)) ;
    stack * station = create_stack(n, sizeof(int)) ;
    stack * in = create_stack(n, sizeof(int)) ;

    for(int i = 0 ; i < n ; i++) {
        scanf("%d", &num) ;
        push(out, &num) ;
    }

    while(n > 0) {
        while(!(n == elem)) {
            pop(out, &elem) ;
                if(n == elem) break ;                
                else {
                    while(station->top < m+1){
                        if(station->top > m) break ;
                            push(out, &elem) ;
                            pop(station, &elem) ;
                                if(n == elem) break ;
                                    push(station, &elem) ;
                                    pop(out, &elem) ;
                                    push(station, &elem) ;
                                    break;
                    }
                }
                if(station->top > m) break ;
            }            
            if(station->top > m) break ;
            else {
                push(in, &elem) ;
                n -= 1 ;
                elem = 0 ;
            }
    }

    if(is_full(in))
        printf("true") ;
    else
    {
        printf("false") ;
    }
}
