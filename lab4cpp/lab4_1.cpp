#include <iostream>
#include <cstdlib>
using namespace std;

template <typename T>
class stack_C{
    private:
        int top;
        int max_stack_size;
        T *stack;
    public :
        stack_C() {
            top = -1;
            max_stack_size = 10;
            stack = (int*)malloc(max_stack_size * sizeof(int));
        }
        ~stack_C(){
            free(stack);
        }

    void stack_full() {
        cout << "stack_full" << endl;
    }

    void stack_empty() {
        cout << "stack_empty" << endl;
    }

    void increase_memory(){
        if (top != -1 && ((top + 1) % 10) == 0) {
            max_stack_size *= 2;
            cout << "realloc " << max_stack_size << endl;
            stack = (int*)realloc(stack, max_stack_size * sizeof(int));
        }
    }

    void push(int item) {
        stack[++top] = item;
        if (top != -1 && ((top + 1) % 10) == 0) {  // -1
            stack_full();
            increase_memory();
        }
    }

    int pop() {
        if (top <= -1) {
            stack_empty();
            exit(1);
        }
        return stack[top--];
    }

    void print() {
        cout << "    index :     item" << endl;
        for (int i = 0; i <= top; i++) {
            cout << "\t" << i << " : \t" << stack[i] << endl;
        }
        cout << endl;
    }
};

int main() {
    stack_C<int> stack;
    cout << "스택" << endl;
    while (1) {
        int item = 0, num;
        cout << "스택 \t 1.push 2.pop : ";
        cin >> num;
        if (num == 1) {
            cout << "push item : ";
            cin >> item;
            stack.push(item);
        } else if (num == 2) {
            cout << "pop item : ";
            cin >> item;
            stack.pop();
        } else if (num == -1) {
            break;
        }
        stack.print();
    }
}