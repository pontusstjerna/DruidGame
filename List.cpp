#include "List.h"

template<typename T>
List<T>::List(int size) : ArraySize(size)
{
	Array = new T[ArraySize];
}

template<typename T>
List<T>::List() : List<T>(10) {}

template<typename T>
List<T>::~List()
{
	delete Array;
}

template<typename T>
void List<T>::Add(T elem)
{
	if (NumItems == ArraySize)
	{
		T* tmp = new T[ArraySize];

		//Copy the old values to temp
		for (int i = 0; i < ArraySize; i++)
		{
			tmp[i] = Array[i];
		}
		
		//Delete old array but now the stuff in it
		delete[] Array;

		//Double the size
		ArraySize *= 2;

		Array = new T[ArraySize];

		for (int i = 0; i < ArraySize; i++)
		{
			Array[i] = tmp[i];
		}

		delete tmp;
	}

	Array[NumItems] = elem;
	NumItems++;
}

template<typename T>
T List<T>::Get(int index)
{
	return Array[index];
}
//
//template<typename T>
//void List<T>::Delete(int index)
//{
//
//}

template<typename T>
bool List<T>::Contains(T elem)
{
	for (int i = 0; i < NumItems; i++)
	{
		if (Array[i] == elem)
			return true;
	}

	return false;
}

template <typename T>
int List<T>::Size()
{
	return NumItems;
}