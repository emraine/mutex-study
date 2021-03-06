#include <mutex>

using namespace std;

class Llist_node {
public:
    Llist_node(int d) {
        data = d;
        next = NULL;
    }

    int data;
    Llist_node *next;
};

class CSE113_Stack {
public:

    CSE113_Stack() {
        start = NULL;
    }

    int pop() {
        lock.lock();

        if (start == NULL) {
            lock.unlock();
            return -1;
        }

        if (start->next == NULL) {
            int ret = start->data;
            delete start;
            start = NULL;
            lock.unlock();
            return ret;
        }

        Llist_node *current = start->next;
        Llist_node *previous = start;
        while (current->next != NULL) {
            previous = current;
            current = current->next;
        }

        int ret = current->data;
        previous->next = NULL;
        delete current;

        lock.unlock();

        return ret;
    }


    int peek() {
        lock.lock();
        if (start == NULL) {
            lock.unlock();
            return -1;
        }

        Llist_node *current = start;
        while (current->next != NULL) {
            current = current->next;
        }
        int d = current->data;
        lock.unlock();
        return d;
    }

    void push(int p) {
        lock.lock();

        if (start == NULL) {

            start = new Llist_node(p);
            lock.unlock();
            return;
        }
        Llist_node *current = start;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new Llist_node(p);
        lock.unlock();
    }

private:
    Llist_node *start;
    mutex lock;
};

