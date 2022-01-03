//
// Created by Fed on 02.11.2021.
//

#include "MyQueue.h"
MyQueue::MyQueue() {
    Size = 0;
    head = nullptr;
}


void MyQueue::pop_front() {
    Node * temp = head;

    delete [] head->data;

    head = head->pNext;

    delete temp;

    Size--;
}

void MyQueue::push_back(char *data) {
    if (head == nullptr)
    {
        head = new Node(data);
    }
    else
    {
        Node *current = this->head;

        while (current->pNext != nullptr)
        {
            current = current->pNext;
        }
        current->pNext = new Node(data);

    }

    Size++;
}

MyQueue::~MyQueue() {
    clear();
}

void MyQueue::clear() {
    while (Size)
    {
        pop_front();
    }
}

char * MyQueue::operator[](int index) {
    int counter = 0;

    Node *current = this->head;

    while (current != nullptr)
    {
        if (counter == index)
        {
            return current->data;
        }
        current = current->pNext;
        counter++;
    }
}
