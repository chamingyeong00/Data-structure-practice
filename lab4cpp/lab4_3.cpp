#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

template <typename T>
class cqueue_C{
    private:
        int front;
        int rear;
        int max_size;
        T* cqueue;
        T *temp;
    public:
        cqueue_C(){
            front = 4;
            rear = 4;
            max_size = 10;
            cqueue = (int*)malloc(max_size * sizeof(int));
        }
        ~cqueue_C(){
            free(cqueue);
        }
    
    void cqueue_full() {
        cout << "cqueue_full" << endl;
    }

    void cqueue_empty() {
        cout << "cqueue_empty" << endl;
    }

    void increase_memory() {
        int cnt = 0;
        temp = (int*)malloc((max_size * 2) * sizeof(int));
        for (int i = front; i < max_size; i++) {
            temp[cnt] = cqueue[i];
            cnt++;
        }
        for (int i = 0; i < rear; i++) {
            temp[cnt] = cqueue[i];
            cnt++;
        }
        front = 0;
        rear = max_size;
        cqueue = (int*)realloc(cqueue, (max_size * 2) * sizeof(int));
        max_size *= 2;
        memcpy(cqueue, temp, max_size * sizeof(int));
        cout << "realloc " << max_size << endl;
    }

    void add_cq(int item) {
        rear = (rear) % max_size; 
        cqueue[rear] = item;
        rear++;
        if (rear == front) {
            cqueue_full();
            increase_memory();
        }
    }

    int delete_cq() {
        if (front == rear) {
            cqueue_empty();
            exit(1);
        }
        front = (front) % max_size;
        return cqueue[front++];
    }
    
    void print(){
        cout << "    index :     item" << endl;
        if (front <= rear) {
            for (int i = front; i < rear; i++) {
                cout << "\t" << i << " : \t" << cqueue[i] << endl;
            }
        } else {
            for (int i = front; i < max_size; i++) {
                cout << "\t" << i << " : \t" << cqueue[i] << endl;
            }
            for (int i = 0; i < rear; i++) {
                cout << "\t" << i << " : \t" << cqueue[i] << endl;
            }
        }
        cout << endl;
    }
};

int main() {
    cqueue_C<int> cqueue;

    cout << "원형큐" << endl;
    while (true) {
        int item = 0, num;
        cout << "큐 \t 1.addCQ 2.deleteCQ : ";
        cin >> num;
        if (num == 1) {
            cout << "addCQ item : ";
            cin >> item;
            cqueue.add_cq(item);
        }
        else if (num == 2) {
            cout << "deleteCQ item : ";
            cin >> item;
            cqueue.delete_cq();
        }
        else if (num == -1)
            break;
        
        cqueue.print();
    }
}