#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* queue, *temp;
int front = 0, rear = 0, max_size = 10;;

void cqueue_full(){
    printf("cqueue_full\n");
}

void cqueue_empty(){
    printf("cqueue_empty\n");
}

void increase_memory(){
    int cnt = 0;
    //printf("max_size : %d rear : %d\n", max_size, rear);
    temp = (int *)malloc((max_size*2) * sizeof(int));
    for (int i = front; i < max_size; i++){
        temp[cnt] = queue[i];
        cnt++;
    }
    for (int i = 0; i < rear; i++){
        temp[cnt] = queue[i];
        cnt++;
    }
    front = 0;
    rear = max_size;
    queue = (int *)realloc(queue, (max_size*2) * sizeof(int));
    max_size *= 2;
    memcpy(queue, temp, max_size * sizeof(int));
    printf("realloc %d\n", max_size);
}

void add_cq(int item){
    rear =(rear)%max_size; 
    //printf("front : %d \t", front);
    //printf("rear : %d\n", rear+1);
    queue[rear] = item;
    rear++;
    if (rear == front){// -1
        cqueue_full();
        increase_memory();
        //exit(1);
    }
 }

 int delete_cq(){
    if (front == rear){
        cqueue_empty();
    }
    //front = (front+1)%max_size; 
    //printf("front : %d \t", (front+1)%max_size);
    //printf("rear : %d\n", rear);
    front = (front)%max_size;
    return queue[front++];
 }

int main(void){
    queue = (int *)malloc(max_size * sizeof(int));
    //printf("size : %d\n", size);
    front = 4;
    rear = 4;
    printf("원형큐\n");
    while(1){
        int item = 0, num;
        printf("큐 \t 1.addCQ 2.deleteCQ : ");
        scanf("%d", &num);
        if (num == 1){
            printf("addCQ item : ");
            scanf("%d", &item);
            add_cq(item);
        }
        else if (num == 2){
            printf("deleteCQ item : ");
            scanf("%d", &item);
            delete_cq();
        }
        else if (num == -1){
            break;
        }
        printf("    index :     item\n");
        //printf(" while : front : %d \t", front);
        //printf("rear : %d\n", rear);
        if (front <= rear){
            for (int i=front; i<rear; i++){
                printf("\t%d : \t%d\n", i, queue[i]);
            }
        }
        else{
            for (int i=front; i<max_size; i++){
                printf("\t%d : \t%d\n", i, queue[i]);
            }
            for (int i=0; i<rear; i++){
                printf("\t%d : \t%d\n", i, queue[i]);
            }
        }
        printf("\n");
        //printf("top: %d\n", top);
        /*if ((rear + 1) == max_size)
        {
            max_size *= 2;
            printf("realloc %d\n", max_size);
            queue = (int *)realloc(queue, max_size * sizeof(int));
        }*/
    }
}