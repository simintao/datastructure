#pragma once
#include <iostream>
using namespace std;

template<class T>
class Array
{
public :
	Array(int capacity) {
		cout << "Array的有参构造调用" <<endl;
		this->m_Capacity = capacity;
		this->m_Size = 0;
		this->pAddress = new T[this->m_Capacity];
	}
	
	
	Array(const Array& arr)
	{
		cout << "Array的拷贝构造调用" <<endl;
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		this->pAddress = new T[arr.m_Capacity];
		for (int i = 0; i < this->m_Size; i++) {
			this->pAddress[i] = arr.pAddress[i];
		}
	}
	Array& operator=(const Array& arr) 
	{
		cout << "Array的operator=调用" <<endl;
		if (this->pAddress != NULL) {
			delete[] this->pAddress;
			this->pAddress = NULL;
			this->m_Capacity = 0;
			this->m_Size = 0;
		}
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		this->pAddress = new T[arr.m_Capacity];
		for (int i = 0; i < this->m_Size; i++) {
			this->pAddress[i] = arr.pAddress[i];
		}
		return *this;
	}
	void Push_Back(const T& val) {
		if (this->m_Capacity == this->m_Size) {
			return;
		}
		this->pAddress[this->m_Size] = val;
		this->m_Size++;
	}
	void Pop_Back() {
		if (this->m_Capacity == 0) {
			return;
		}
		this->m_Size--;
	}
	T& operator[](int index) {
		return this->pAddress[index];
	}
	int getCapacity() {
		return this->m_Capacity;
	}
	int getSize() {
		return this->m_Size;
	}

	~Array() {
		if (this->pAddress != NULL) {
			cout << "Array的析构函数构造调用"<<endl;
			delete[] this->pAddress;
			this->pAddress = NULL;
		}
	}
private:
	T* pAddress;
	int m_Capacity;
	int m_Size;
};
