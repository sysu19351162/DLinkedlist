#pragma once

using std::cout;
using std::endl;

template<class T>
class Node
{
	
public:
	Node();

	Node(T data);

	Node(Node<T>& n);

	T getdata();

	~Node()
	{
		cout << "calling the Node destructor" << endl;
	}

	T data_;
	template <class D> friend class DLinkedlist;	

	Node* pred;

	Node* succ;

	
};


template<class T>
Node<T>::Node()
{
	cout << "calling the Node constructor" << endl;
}


template<class T>
Node<T>::Node(T data):data_(data)
{
	cout << "calling the Node constructor" << endl;
}


template<class T>
Node<T>::Node(Node<T>& n):data_(n.data_)
{
	cout << "calling the Node constructor" << endl;
}


template<class T>
T Node<T>::getdata()
{
	T data=data_;

	return data;
}