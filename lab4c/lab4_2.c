#include <stdio.h>
#include <stdlib.h>
int* queue;
int front = -1, rear = -1, max_size = 10;;

void queue_full(){
    printf("queue_full\n");
}

void queue_empty(){
    printf("queue_empty\n");
}

void add_q(int item){
    //printf("top : %d \t", top);
    queue[++rear] = item;
    if (rear != -1 && ((rear+1) % 10 ) == 0){// -1
        queue_full();   
        //exit(1);
    }
    //printf("stack[top] : %d", top);
    //printf("MAX_SIZE-1 : %d\n",-1);
 }

 int delete_q(){
    if (front == rear){
        queue_empty();
        exit(1);
    }
    return queue[++front];
 }

int main(void){
    queue = (int *)malloc(max_size * sizeof(int));
    //printf("size : %d\n", size);
    printf("큐\n");
    while(1){
        int item = 0, num;
        printf("큐 \t 1.addQ 2.deleteQ : ");
        scanf("%d", &num);
        if (num == 1){
            printf("addQ item : ");
            scanf("%d", &item);
            add_q(item);
        }
        else if (num == 2){
            printf("deleteQ item : ");
            scanf("%d", &item);
            delete_q();
        }
        else if (num == -1){
            break;
        }
        printf("    index :     item\n");
        for (int i=front+1; i<=rear; i++){
            printf("\t%d : \t%d\n", i, queue[i]);
        }
        printf("\n");
        //printf("top: %d\n", top);
        if (rear != -1 && ((rear + 1) == max_size))
        {
            max_size *= 2;
            printf("realloc %d\n", max_size);
            queue = (int *)realloc(queue, max_size * sizeof(int));
        }
    }
}