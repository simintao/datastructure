#pragma once
#ifndef _LIST_HH_
#define _LIST_HH_
#include "Collection.h"

template<class T>
class List :public Collection<T> {
public:
	virtual void add(int index, T* e) = 0;
	virtual T* get(int index) = 0;
	virtual T* remove(int index) = 0;
	virtual ~List() {}

};




#endif 