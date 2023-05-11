#pragma once
#include <iostream>
template<typename T>
class List {
private:
    struct item {
        T data;
        item* next = nullptr;
        item* prev = nullptr;
    };

    item* first;
    item* last;
    int itemscount;
public:
    List() {
        first = nullptr;
        last = nullptr;
        itemscount = 0;
    }
    int size() {
        return itemscount;
    }
    void pushback(T data) {
        item* newitem = new item();
        newitem->data = data;
        if (itemscount == 0) {
            first = newitem;
            last = newitem;
        }
        else {
            last->next = newitem;
            newitem->prev = last;
            last = newitem;
        }
        itemscount++;
    }
    void removelast() {
        if (itemscount == 0) return;
        if (itemscount == 1) {
            first = nullptr;
            last = nullptr;
        }
        else {
            item* temp = new item();
            temp = last;
            last = last->prev;
            last->next = nullptr;
            delete temp;
        };
        itemscount--;
    }
    void Addbyindex(T data, int index) {
        item* newitem = new item();
        newitem->data = data;
        if (itemscount == 0 or index == itemscount) {
            this->pushback(data);
        }
        else {
            if (index == 0) {
                first->prev = newitem;
                newitem->next = first;
                first = newitem;
            }
            else {
                item* curr = first;
                for (int i = 0; i < index; i++) {
                    curr = curr->next;
                }
                curr->prev->next = newitem;
                newitem->prev = curr->prev;
                curr->prev = newitem;
                newitem->next = curr;
            }
            itemscount++;

        }
    }
    void removebyindex(int index) {
        if (index > itemscount - 1 or index < 0) { std::cout << "Error" << std::endl; }
        if (index == 0) {
            first = first->next;
            itemscount--;
        }
        else {
            item* curr = this->first;
            for (int i = 0; i < index; i++) {
                curr = curr->next;
            }
            item* prev = curr->prev;
            item* next = curr->next;
            prev->next = next;
            if (next) {
                next->prev = prev;
            }
            delete curr;
            itemscount--;
        }
    }
    T* getbyindex(int index) {
        item* curr = this->first;
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
        return &curr->data;
    }
    void printlist() {
        item* temp = this->first;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
    }
  
};
