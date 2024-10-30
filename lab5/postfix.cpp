#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100
int top = -1;
char stack[MAX_STACK_SIZE];
char expr[MAX_EXPR_SIZE];
char new_expr[MAX_EXPR_SIZE];
int isp[] = {0, 19, 12, 12, 13, 13, 13, 0};
int icp[] = {20, 19, 12, 12, 13, 13, 13, 0};
typedef enum{
    lparen, rparen, plus, minus, times, 
    divide, mod, eos, operand
} precedence;

precedence get_token (char* expr, char *symbol, int *n);


void stack_full(){
    printf("stack_full\n");
}

void stack_empty(){
    printf("stack_empty\n");
}

void push(int item){
    if (top >= MAX_STACK_SIZE - 1)
    {
        stack_full();
        exit(1);
    }
    stack[++top] = item;
}

 int pop(){
    if (top == -1)
    {
        stack_empty();
        exit(1);
    }
    return stack[top--];
 }

void printToken(precedence token){
    switch ((char)token){
        case lparen:
            printf("( ");
            break;
        case rparen:
            printf(") ");
            break;
        case plus:
            printf("+ ");
            break;
        case minus:
            printf("- ");
            break;
        case times:
            printf("* ");
            break;
        case divide:
            printf("/ ");
            break;
        case mod:
            printf("%% ");
            break;
        case eos:
            printf("");
            break;
    }
}

void ft_print(char *str, int n) {
    for (int i = 0; i <= n; i++) {
       if (!(str[i] >= '0' && str[i] <= '9'))
            printToken((precedence)str[i]);
        else
            printf("%c ", str[i]); 
    }
}

void postfix(char *new_expr){
    precedence token;
    int n = 0;
    int new_expr_index = 0;
    char symbol;
    push(eos);
    for (token = get_token(expr, &symbol, &n); token != eos; token = get_token(expr, &symbol, &n))//주소 위치 보내기
    {
        if (token == operand)
        {
            new_expr[new_expr_index++] = symbol;
        }
        else if (token == rparen){
            while (stack[top] != lparen){
                new_expr[new_expr_index++] = pop();
            }
            pop();
        }
        else{
            while (top != 0 && isp[stack[top]] >= icp[token])
                new_expr[new_expr_index++] = pop();
            push(token);    
        }
        if (token != rparen )
        {
            printf("\t%c   |", symbol);
            ft_print(stack, top);
            printf("\t\t|  %d ", top-1);
            printf("\t | ");
            ft_print(new_expr, new_expr_index-1);
            printf("\n");
        }
    }
    printf("\t %c   |", symbol);
    ft_print(stack, top);
    printf("\t\t\t|  %d ", top-2);
    printf("\t | ");
    ft_print(new_expr, new_expr_index-1);
    printf("\n");

    printf("\n");
    new_expr[0] = pop();
}

precedence get_token(char* expr, char *symbol, int *n){
    *symbol = expr[(*n)++]; 
    switch (*symbol){
        case '(':
            return lparen;
        case ')':
            return rparen;
        case '+':
            return plus;
        case '-':
            return minus;
        case '*':
            return times;
        case '/':
            return divide;
        case '%':
            return mod;
        case '\0':
            return eos;
        default :
            return operand;
    }
}

int main(void){
    printf("Infix : ");
    scanf("%s", expr);
    printf("Infix to Postfix : \n");
    printf("     Token  |  Stack\t\t|  Top  | Output\n");
    postfix(new_expr);
    return 0;
}