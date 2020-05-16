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
typedef enum { Value, Operator } token_type ;

typedef struct {
	int value ;
	char operator ;
	token_type type ;
} token_t ;


void
print_stack (stack * st)
{
	int i ;
	token_t t ;
	for (i = 0 ; i < get_size(st) ; i++) {
		token_t num ;
		get_element(st, i, &num) ;
		printf("[%d]", num.value) ;
	}
	printf("\n") ;
}


int
main ()
{
	stack * st ;
	token_t t ;
	st = create_stack(100, sizeof(token_t)) ;

	char tok[8] ;
	do {
		//print_stack(st) ;

		scanf("%s", tok) ;

		if (tok[0] == ';') 
			break ;

		if (isdigit(tok[0])) {
			t.value = atoi(tok) ;
			t.type = Value ;
			push(st, &t) ;
		}
		else {
			switch (tok[0]) {
				case '+' : {
					t.operator = tok[0] ;
					t.type = Operator ;

					token_t n1, n2, res ;
					res.type = Value ;
					pop(st, &n2) ;
					pop(st, &n1) ;

					if(n1.type != Value) {
						printf("invalid\n") ;
						return 0 ;
					}

					res.value = n1.value + n2.value ;
					push(st, &res) ;
					break ;
				} 

				case '-' : {
					t.operator = tok[0] ;
					t.type = Operator ;

					token_t n1, n2, res ;
					res.type = Value ;
					pop(st, &n2) ;
					pop(st, &n1) ;

					if(n1.type != Value) {
						printf("invalid\n") ;
						return 0 ;
					}

					res.value = n1.value - n2.value ;
					push(st, &res) ;
					break ;
				}

				case '*' : {
					t.operator = tok[0] ;
					t.type = Operator ;

					token_t n1, n2, res ;
					res.type = Value ;
					pop(st, &n2) ;
					pop(st, &n1) ;

					if(n1.type != Value) {
						printf("invalid\n") ;
						return 0 ;
					}

					res.value = n1.value * n2.value ;
					push(st, &res) ;
					break ;
				}

				case '/' : {
					t.operator = tok[0] ;
					t.type = Operator ;

					token_t n1, n2, res ;
					res.type = Value ;
					pop(st, &n2) ;
					pop(st, &n1) ;

					if(n1.type != Value) {
						printf("invalid\n") ;
						return 0 ;
					}

					if(n2.value == 0) {
						printf("undefined\n") ;
						return 0 ;
					}
					res.value = n1.value / n2.value ;
					push(st, &res) ;
					break ;
				}

				case '^' : {
					t.operator = tok[0] ;
					t.type = Operator ;

					token_t n1, n2, res ;
					res.type = Value ;
					res.value = 1 ;
					pop(st, &n2) ;
					pop(st, &n1) ;

					if(n1.type != Value) {
						printf("invalid\n") ;
						return 0 ;
					}

					if(n2.value < 0) {
						printf("undefined\n") ;
						return 0 ;
					}
					for(int i = 0 ; i < n2.value ; i++) {
						res.value *= n1.value ;
					}
					push(st, &res) ;
					break ;
				}

				case '~' : {
					t.operator = tok[0] ;
					t.type = Operator ;

					token_t n ;
					pop(st, &n) ;

					if(n.type != Value) {
						printf("invalid\n") ;
						return 0 ;
					}

					n.value = -n.value ; 
					push(st, &n) ;
					break ;
				}
				default :
					printf("invalid\n") ;
					return 0 ;
			}
		}
	} while (tok[0] != ';') ;

	token_t result ;
	result.type = Value ;
	pop(st, &result) ;

	if(!is_empty(st))
		printf("invalid\n") ;

	else
		printf("%d\n", result.value) ;

	delete_stack(st) ;
	return 0 ;
}
