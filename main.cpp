#include<iostream>
#include"Node.h"
#include"DLinkedList.h"

using namespace std;

int main()
{
	string list1 = "IntegerData.txt";

	string list2 = "Merge.txt";

	Node<int>* node1=new Node<int>(1);

	Node<int>* node2=new Node<int>(2);

	DLinkedList<int> list_1(list1);

	DLinkedList<int> list_2(list2);

	cout << list_1.empty()<<endl;

	list_1.show();

	cout<<"size:"<<list_1.size();

	list_1.insertAsFirst(node1);

	list_1.insertAsLast(node2);

	list_1.show();

	cout << "list_1_first:" << list_1.first().getdata() << endl;

	cout << "list_1_last:" << list_1.last().getdata() << endl;

	list_2.show();

	list_1.merge(list_2);

	list_1.show();

	list_1.sort();

	list_1.show();

	list_1.reverse();

	list_1.show();

	return 0;

}