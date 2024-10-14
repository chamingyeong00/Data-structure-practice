#include <stdio.h>
#include <stdlib.h>
int top = -1, max_stack_size = 10;
int* stack;

void stack_full(){
    printf("stack_full\n");
}

void stack_empty(){
    printf("stack_empty\n");
}

void push(int item){
    //printf("top : %d \t", top);
    stack[++top] = item;
    if (top != -1 && ((top+1) % 10 ) == 0){// -1
        stack_full();   
        //exit(1);
    }
    //printf("stack[top] : %d", top);
    //printf("MAX_SIZE-1 : %d\çn",-1);
 }

 int pop(){
    if (top <= -1){
        stack_empty();
        exit(1);
    }
    return stack[top--];
 }

int main(void){
    stack = (int *)malloc(max_stack_size * sizeof(int));
    //printf("size : %d\n", size);
    printf("스택\n");
    while(1){
        int item = 0, num;
        printf("스택 \t 1.push 2.pop : ");
        scanf("%d", &num);
        if (num == 1){
            printf("push item : ");
            scanf("%d", &item);
            push(item);
        }
        else if (num == 2){
            printf("pop item : ");
            scanf("%d", &item);
            pop();
        }
        else if (num == -1){
            break;
        }
        printf("    index :     item\n");
        for (int i=0; i<=top; i++){
            printf("\t%d : \t%d\n", i, stack[i]);
        }
        printf("\n");
        //printf("top: %d\n", top);
        if (top != -1 && ((top+1) % 10 ) == 0)
        {
            max_stack_size *= 2;
            printf("realloc %d\n", max_stack_size);
            stack = (int *)realloc(stack, max_stack_size * sizeof(int));
        }
    }
}