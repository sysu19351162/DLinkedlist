#pragma once
#include<iostream>
#include<istream>
#include<fstream>
#include<vector>
#include<string>
#include<memory>
#include<sstream>
#include <algorithm>
#include"Node.h"

using std::cout;
using std::endl;
using std::string;


template<class T>
class DLinkedList
{
public:
	DLinkedList(std::string Filename);

	~DLinkedList();
	

	int size()const;

	bool empty()const;

	Node<T> remove(int n);

	Node<T> first()const;

	Node<T> last()const;

	void insertAsFirst(Node<T>*);//��ǰ����

	void insertAsLast(Node<T>*);//������

	Node<T> find(T data);//����

	void sort();//��data��С����

	void reverse();//����ת����

	void merge(DLinkedList<T>);//�ϲ���һ��������

	void show()const;//������ӡ����
protected:
	void init();//��������ʱ��ʼ��������������нڵ㣨ͷβ�ս����⣩

	void init(Node<T>*, int n);

	

private:
	Node<T>* head_;//ͷ�ڵ�

	Node<T>* end_;//β�ڵ�

	int size_;

	bool flag_ = false;//��Ϊ�Ƿ��ʼ���ı�ʶ��

};

template<class T>
DLinkedList<T>::DLinkedList(string Filename)
{

	std::fstream is(Filename);
	
	init();
	string text;
	string num;

	int k = 0;
	int n;
	while (getline(is, text))
	{
		if (text[0] == 'd')
		{
			auto start = text.find_first_of(":") + 1;
			num = string(text, start);
			n = stod(num);
			Node<int>*temp=new Node<int>(n);
			insertAsLast(temp);
			k++;
			end_->pred = temp;
		}
	}

	size_ = k;
	
}


template<class T>
DLinkedList<T>::~DLinkedList()
{
	Node<T>* node=head_->succ;

	while (node != end_&&node!=nullptr)
	{
		node = node->succ;

		delete node->pred;
	}

	cout << "calling the DLinkedList destructor" << endl;
}


template<class T>
void DLinkedList<T>::init()//��������ʱ��ʼ��������������нڵ㣨ͷβ�ս����⣩
{

	if (flag_ == false)//�ڹ��캯���е���
	{
		head_ = new Node<T>;

		end_ = new Node<T>;

		head_->pred = nullptr;

		end_->succ = nullptr;

		head_->succ = end_;

		end_->pred = head_;

		flag_ = true;
	}
	else
	{
		Node<T>* node = head_->succ;

		do
		{
			node = node->succ;

			delete node->pred;
		} while (node != end_);

		head_->succ = end_;

		end_->pred = head_;
	}

	size_= 0;
}


template<class T>
void DLinkedList<T>::init(Node<T>* node1, int n)//��ʼ��Ϊ��n����node��ͬ�Ľڵ������
{
	Node<T> node = head_->succ;

	//�������
	do
	{
		node = node->succ;

		delete node->pred;
	} while (node != end_);

	head_->succ = end_;

	end_->pred = head_;

	node = head_->succ;

	for (int i = 0; i < n; i++)
	{
		Node<T> temp = new Node<T>(node1);

		node->pred = temp;

		temp->succ = node;
	}

	size = n;
}


template<class T>
int DLinkedList<T>::size()const
{
	int size = size_;

	return size;
}


template<class T>
bool DLinkedList<T>::empty()const
{
	if (head_->succ == end_)
		return true;
	else
		return false;
}


template<class T>
Node<T> DLinkedList<T>::remove(int n)//����ɹ����أ�ʹ��remove��ǵ�delete
{
	if (size_ >= n)
	{
		size_--;

		Node<T> *node=head_;

		for (int i = 0; i < n; i++)
		{
			node = node->succ;
		}


		Node<T>* target=node;//Ϊ�����޸ģ�ɾ���Ķ�����targetָ��

		Node<T>* temp = target->pred;//��Ŀ��ǰ���ڵ��β�˽���Ŀ��󷽽ڵ�

		temp->succ = target->succ;

		temp = target->succ;//��Ŀ��󷽽ڵ��β�˽���Ŀ��ǰ���ڵ�

		temp->pred = target->pred;

		return *target;
	}
	else
	{
		cout << "remove wrongly" << endl;

		return *(new Node<T>);
	}
}


template<class T>
Node<T> DLinkedList<T>::first()const
{
	if (head_->succ == end_)
		cout << "Empty!!!" << endl;

	return *head_->succ;
}


template<class T>
Node<T> DLinkedList<T>::last()const
{
	if (end_->pred == head_)
		cout << "Empty!!!" << endl;

	return *end_->pred;
}


template<class T>
void DLinkedList<T>::insertAsFirst(Node<T>* n)
{
	n->succ = head_->succ;

	(head_->succ)->pred = n;

	n->pred = head_;

	head_->succ = n;

	size_++;
}


template<class T>
void DLinkedList<T>::insertAsLast(Node<T>* n)
{
	n->succ = end_;

	n->pred = end_->pred;

	(end_->pred)->succ = n;

	end_->pred = n;

	size_++;
}


template<class T>
Node<T> DLinkedList<T>::find(T data)//���ص�һ������ֵ�Ľڵ�
{
	Node<T>* node=head_->succ;

	bool flag = false;

	while (node != end_ && flag == false)//���ҵ�����Ҫ��Ľڵ���������нڵ���δ�ҵ�ʱ����ѭ��
	{
		if (node->data_ == data)
		{
			flag = true;
		}
	}

	if (flag = true)
	{
		cout << "Found successfully" << endl;


		return node;
	}
	else
	{
		cout << "can't find" << endl;
		return NULL;
	}
}


template<class T>
void DLinkedList<T>::sort()
{
	int i = 0, j = 0;
	int s = size();
	Node<T>* node;
	for (i = 1; i <= s - 1; i++)
	{
		node = head_;
		node = node->succ;
		for (j = 1; j <= s - i; j++)
		{
			if (node->getdata() >= (node->succ->getdata()))
			{
				bool flag = 0;
				if (node->succ->succ != nullptr)//���������¸���ַ
				{
					Node<T>* csuc = node->succ;//��һ���ڵ��ַ
					Node<T>* cpred = node->pred;//��һ���ڵ��ַ
					Node<T>* csucsuc = node->succ->succ;//���¸��ڵ��ַ
					Node<T>* node1 = node;//�˽ڵ��ַ
					cpred->succ = (csuc);
					node1->succ = (csucsuc);
					node1->pred = (csuc);
					csuc->succ = (node1);
					csuc->pred = (cpred);
					csucsuc->pred = (node1);
				}
				else//����û�����¸���ַ
				{

					Node<T>* csuc = node->succ;
					Node<T>* cpred = node->pred;
					Node<T>* node1 = node;
					cpred->succ = (csuc);
					node1->succ = (end_);
					node1->pred = (csuc);
					csuc->succ = (node1);
					csuc->pred = (cpred);
					end_->pred = node1;
				}
			}
			else
			{
				node = node->succ;
			}
		}
	}
}


template<class T>
void DLinkedList<T>::reverse()//����ת
{
	Node<T>* node;

	Node<T>* temp1=new Node<T>;

	Node<T>* temp2 = head_->succ;

	node = end_->pred;

	head_->succ = end_->pred;

	node->succ = node->pred;

	node->pred = head_;

	while (node !=temp2)//���е�ת
	{
		temp1 = node->succ;

		temp1->succ = temp1->pred;

		temp1->pred = node;

		node = node->succ;
	}

	node->pred = node->succ;

	node->succ=end_;

}


template<class T>
void DLinkedList<T>::merge(DLinkedList<T> list)//ע�⣬���ϲ��������Լ��ᱻ���
{
	(end_->pred)->succ = (list.head_)->succ;

	((list.head_)->succ)->pred = end_->pred;

	((list.end_)->pred)->succ = end_;

	end_->pred = (list.end_)->pred;

	list.head_->succ = list.end_;

	list.end_->pred = list.head_;

	size_ = size_ + list.size_;

	list.size_ = 0;
}


template<class T>
void DLinkedList<T>::show()const
{
	Node<T>* node = head_->succ;

	int i = 1;

	while (node != end_)
	{
		cout << "No." << i << ":" << node->data_ << endl;

		node = node->succ;

		i++;
	}
}