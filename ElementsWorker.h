#pragma once
#include <vector>
#include <list>
using namespace std;
template <class T>
class ElementsWorker
{
	static void Swap(T& t1, T& t2);

	static void DeleteFromVector(vector<T>& vect, T& delElement);

	static void DeleteFromList(list<T>& l, T& delElement);
};

template<class T>
void ElementsWorker<T>::Swap(T& t1, T& t2)
{
	T temp = t1;
	t1 = t2;
	t2 = temp;
}

template<class T>
void ElementsWorker<T>::DeleteFromVector(vector<T>& vect, T& delElement)
{
	vect.erase(find(vect.begin(), vect.end(), delElement));
}

template<class T>
void ElementsWorker<T>::DeleteFromList(list<T>& l, T& delElement)
{
	l.erase(find(l.begin(), l.end(), delElement));
}
