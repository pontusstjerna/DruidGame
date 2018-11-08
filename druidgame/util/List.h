#pragma once
template <typename T> class List
{
	public:
		List<T>(int size);
		List<T>();
		~List<T>();

		void Add(T elem);
		T Get(int index);
		//void Delete(int index);
		bool Contains(T elem);
		int Size();

	private:
		T Type;
		T* Array;
		int NumItems = 0;
		int ArraySize = 0;

};