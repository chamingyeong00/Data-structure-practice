#include <iostream>
#include <cstdlib>
using namespace std;

template <typename T>
class queue_C{
    private:
        int front;
        int rear;
        int max_size;
        T *queue;
    public : 
        queue_C(){
            front = -1;
            rear = -1;
            max_size = 10;
            queue = (int*)malloc(max_size * sizeof(int));
        }
        ~queue_C(){
            free(queue);
        }

    void queue_full(){
        cout << "queue_full" << endl;
    }

    void queue_empty(){
        cout << "queue_empty" << endl;
    }

    void increase_memory(){
        if (rear != -1 && ((rear + 1) == max_size)){
            max_size *= 2;
            cout << "realloc " << max_size << endl;
            queue = (int*)realloc(queue, max_size * sizeof(int));
        }
    }

    void add_q(int item){
        queue[++rear] = item;
        if (rear != -1 && ((rear + 1) % 10) == 0){
            queue_full(); 
            increase_memory();  
        }
    }

    int delete_q(){
        if (front == rear){
            queue_empty();
            exit(1);
        }
        return queue[++front];
    }

    void print(){
        cout << "    index :     item" << endl;
        for (int i = front + 1; i <= rear; i++){
            cout << "\t" << i << " : \t" << queue[i] << endl;
        }
        cout << endl;
    }
};

int main(void){
    queue_C<int> queue;
    cout << "큐" << endl;
    while(1){
        int item = 0, num;
        cout << "큐 \t 1.addQ 2.deleteQ : ";
        cin >> num;
        if (num == 1){
            cout << "addQ item : ";
            cin >> item;
            queue.add_q(item);
        }
        else if (num == 2){
            cout << "deleteQ item : ";
            cin >> item;
            queue.delete_q();
        }
        else if (num == -1){
            break;
        }
        queue.print();
    }
}