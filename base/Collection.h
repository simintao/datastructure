#pragma once
#ifndef _COLLECTION_HH_
#define _COLLECTION_HH_
template<class T>
class Collection {
public:
	virtual bool add(T* e) = 0;
	virtual int contains(T* e) = 0;
	virtual bool isEmpty() = 0;
	virtual bool remove(T* e) = 0;
	virtual int size() = 0;
	virtual ~Collection() {}
};

#endif