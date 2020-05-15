#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ZERO_VISITED 2
#define ONE_VISITED 4

typedef 
	struct {
		void * buffer ;
		int unit ;
		int capacity ;
		int front ;
		int rear ;
		int full ;
	} 
	queue ;

queue * 
create_queue (int capacity, int unit) ;

void
delete_queue (queue * que) ;

int 
enqueue (queue * que, void * elem) ;

int
dequeue (queue * que, void * elem) ;

int 
is_empty (queue * que) ;

int 
is_full (queue * que) ;

void
print_queue (queue * que, void (* print_element)(void * element)) ;
//
queue * 
create_queue (int capacity, int unit) 
{
	queue * que = malloc(sizeof(queue)) ;
	que->capacity = capacity ;
	que->unit = unit ;
	que->buffer = calloc(capacity, unit) ;
	que->front = 0 ;
	que->rear = 0 ;
	que->full = 0 ;
	return que ;
}

void
delete_queue (queue * que) 
{
	if (que->buffer != 0x0)
		free(que->buffer) ;
	free(que) ;
}

int 
enqueue (queue * que, void * elem)
{
	if (is_full(que))
		return 1 ;

	memcpy(que->buffer + ((que->rear) * (que->unit)), elem, que->unit) ;
	que->rear = (que->rear + 1) % que->capacity ;

	if (que->rear == que->front)
		que->full = 1 ;

	return 0 ;
}

int
dequeue (queue * que, void * elem)
{
	if (is_empty(que)) 
		return 1 ;
	
	memcpy(elem, que->buffer + que->front * que->unit, que->unit) ;
	que->front = (que->front + 1) % que->capacity ;	
	que->full = 0 ;

	return 0;
}

int 
is_empty (queue * que) 
{
	return (que->front == que->rear) && (que->full == 0) ;
}

int 
is_full (queue * que) 
{
	return que->full ;
}

void
print_queue (queue * que, void (* print_element)(void * elem)) 
{
	int i ;
	if (que->front == que->rear && que->full == 0)
		return ;

	for (i = que->front ; i != que->rear ; i = (i + 1) % (que->capacity)) {
		printf("[") ;
		print_element(que->buffer + i * que->unit) ;
		printf("] ") ;
	}
	printf("\n") ;
}
//
const int d[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}} ;

typedef struct { 
	int w ;
	int h ;
} pos ;

int main() {
    int width, height ;
    scanf("%d %d", &height, &width) ;
    if(!((1 <= height ) && ( height <= 20) || (1 <= width) && ( width < 20))) return 0 ;

    int visit[height][width] ;
    int land_num, max, min, area ;
    land_num = 0 ;
    max = 0 ;
    min = width * height ;
    area = 0 ;
    

    for(int i = 0 ; i < height ; i++) { 
        for(int j = 0 ; j < width ; j++) {
            scanf("%d ", &visit[i][j]) ;
        }
    }

    queue * task ;
    task = create_queue(width * height, sizeof(pos)) ;

    pos curr ;
    curr.h = 0 ; curr.w = 0 ;
    while(!((curr.h == height-1) && (curr.w == width-1))) {
        if(visit[curr.h][curr.w] != 1) {
            if(visit[curr.h][curr.w] == ONE_VISITED || visit[curr.h][curr.w] == ZERO_VISITED) {
                if(curr.w == width-1) {
                    curr.w = 0 ;
                    curr.h += 1 ;
                }
                else {
                    curr.w += 1 ;
                }
            }
            else {
                if(curr.w == width-1) {
                    visit[curr.h][curr.w] = ZERO_VISITED ;
                    curr.w = 0 ;
                    curr.h += 1 ;
                }
                else {
                    visit[curr.h][curr.w] = ZERO_VISITED ;
                    curr.w += 1 ;
                    }
                }
            }

        if(visit[curr.h][curr.w] == 1) {
            visit[curr.h][curr.w] = ONE_VISITED ;
            area += 1 ;
            enqueue(task, &curr) ;
            while(!is_empty(task)) {
                dequeue(task, &curr) ;
                int i_d ;
                for(i_d = 0 ; i_d < 4 ; i_d++) {
                    pos next ;
                    next.h = curr.h + d[i_d][0] ;
                    next.w = curr.w + d[i_d][1] ;
                    if(0 <= next.h && next.h < height) {
                        if(0 <= next.w && next.w < width) {
                            if(visit[next.h][next.w] == 1) {
                                    visit[next.h][next.w] = ONE_VISITED ;
                                    area += 1 ;
                                    enqueue(task, &next) ;
                            }
                        }
                    }
                }
            }
            if(area > 0) land_num += 1 ;
            if(area >= max) max = area ;
            if(land_num == 0) min = 0 ;
            if(area <= min) min = area ;
            curr.h = 0 ; curr.w = 0 ; area = 0 ;
        }
    }

    printf("%d %d %d\n", land_num, min, max) ;
    delete_queue(task) ;
    return 0 ;
}
