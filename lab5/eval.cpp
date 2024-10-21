#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100
int top = -1;
int stack[MAX_STACK_SIZE];
char expr[MAX_EXPR_SIZE];
char new_expr[MAX_EXPR_SIZE];

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

void ft_print(int *str, int n)
{
    printf("   ");
    for (int i=0; i<n; i++)
    {
        printf("%d ", str[i]);
    }
}

int eval(char *expr, char * new_expr){
    precedence token;
    int n = 0;
    char symbol;
    token = get_token(expr, &symbol, &n);
    while (token != eos){
        if (token == operand)
            push(symbol - '0');
        else{
            int op2 = pop();
            int op1 = pop();
            switch (token){
                case plus :
                    push(op1 + op2);
                    break;
                case minus:
                    push(op1 - op2);
                    break;
                case times:
                    push(op1 * op2);
                    break;
                case divide:
                    push(op1 / op2);
                    break;
                case mod:
                    push(op1 % op2);
                    break;
                default:
                    continue;
            }
        }
        printf("\t%c   |", symbol);
        ft_print(stack, top+1);
        printf("\t  |  %d\n", top-1);
        token = get_token(expr, &symbol, &n); //
    }
    new_expr[0] = pop();
    return new_expr[0];
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
    printf("postfix : ");
    scanf("%s", expr);
    printf("Eval to Postfix : \n");
    printf("     Token  |    Stack    |  Top\n");
    printf("Eval : %d\n", eval(expr, new_expr));
    return 0;
}