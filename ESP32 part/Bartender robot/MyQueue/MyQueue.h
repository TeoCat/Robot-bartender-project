//
// Created by Fed on 02.11.2021.
//
#ifndef MYQUEUE_H
#define MYQUEUE_H
#include <cstring>


class MyQueue {
public:
    MyQueue();
    ~MyQueue();

    //удаление первого элемента в списке
    void pop_front();

    //добавление элемента в конец списка
    void push_back(char * data);

    // очистить список
    void clear();

    // перегруженный оператор []
    char * operator[](int index);

    // получить количество елементов в списке
    int GetSize() { return Size; }

private:

    class Node
    {
    public:
        Node * pNext;
        char * data = nullptr;

        Node(char * data = nullptr, Node *pNext = nullptr)
        {
            if (data != nullptr){
                char * new_data = new char [10];
                strncpy(new_data, data, 10);
                this->data = new_data;
            }
            this->pNext = pNext;
        }
    };
    int Size;
    Node * head;
};


#endif //MYQUEUE_H
