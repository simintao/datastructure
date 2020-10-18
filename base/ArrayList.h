#pragma once
#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_
#include "List.h"
template<class T, int init = 10> 
class ArrayList : public List<T> { 
    int __size; 
    int __capacity; 
    T** params;
    void grow(); 
    ArrayList(const ArrayList&);
public:
    ArrayList() :
        __size(0), __capacity(init), params(new T* [init]) {
    }
    virtual ~ArrayList();
    bool add(T* e); 
    int contains(T* e); 
    bool isEmpty(); 
    bool remove(T* e); 
    int size(); 
    int capacity(); 
    void add(int index, T* e); 
    T* get(int index); 
    T* remove(int index); 
    class Iterator;
    friend class Iterator;
    class Iterator { 
        ArrayList& al;
        int index;
    public:
        Iterator(ArrayList& list) :
            al(list), index(0) {
        }
        bool hasNext() {
            if (index < al.__size) {
                return true;
            }
            return false;
        }
        T* next() {
            if (hasNext()) {
                return al.params[index++];
            }
            return 0;
        }
    };
};

template<class T, int init>
ArrayList<T, init>::~ArrayList() {
    for (int i = 0; i < __size; i++) {
        delete params[i];
        params[i] = 0;
    }
    delete params; 
}
template<class T, int init>
void ArrayList<T, init>::grow() {
    if (__size == __capacity) {
        __capacity *= 1.5;
        T** newparams = new T * [__capacity];
        for (int i = 0; i < __size; i++)
            newparams[i] = params[i];
        delete[] params; 
        params = newparams;
    }
}
template<class T, int init>
bool ArrayList<T, init>::add(T* e) {
    grow();
    params[__size++] = e;
    return true;
}
template<class T, int init>
int ArrayList<T, init>::contains(T* e) { 
    for (int i = 0; i < __size; i++) {
        if (get(i) == e) {
            return i; 
        }
    }
    return -1;
}
template<class T, int init>
int ArrayList<T, init>::capacity() { 
    return __capacity;
}
template<class T, int init>
int ArrayList<T, init>::size() { 
    return __size;
}
template<class T, int init>
bool ArrayList<T, init>::remove(T* e) { 
    int index = contains(e);
    if (index != -1) {
        remove(index);
        return true;
    }
    return false;
}
template<class T, int init>
bool ArrayList<T, init>::isEmpty() { 
    if (__size == 0) {
        return true;
    }
    else {
        return false;
    }
}
template<class T, int init>
void ArrayList<T, init>::add(int index, T* e) { 
    if (index > __size) return;
    __size = __size + 1;
    grow();
    for (int i = __size - 1; i > index; i--)
    {
        params[i] = params[i - 1];
    }
    params[index] = e;
}
template<class T, int init>
T* ArrayList<T, init>::get(int index) { 
    if (index < 0 || index >= __size) {
        return 0;
    }
    return params[index];
}
template<class T, int init>
T* ArrayList<T, init>::remove(int index) { 
    if (index < 0 || index >= __size) {
        return 0;
    }
    T* result = get(index);
    if(index<(__size-1))
    {
    for (int i = index; i < __size; i++)
    {
        params[i] = params[i + 1];
    }
    }
    params[__size - 1] = nullptr;
    __size = __size - 1;
    return result;
}
#endif /* ARRAYLIST_H_ */