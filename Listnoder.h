#include<iostream>



//������ ����� �����������, �������� ������ ������ ����� ������� ��������� ��� ������� � �������, ������ ��� ���������������???


using namespace std;
template <typename T> class list;
template <typename T> class node //����� node �������� ������ ������
{
	friend class list<T>;
public:
	node* next; //��������� �� ��������� ������� � ������
	node* prev;
	T* val; //������ ������
	node(T* data, node* P = 0, node* N = 0) { val = data, prev = P; next = N; }
	node(){}
	virtual~node() {
		delete val; 
	}
};

template <typename T> class nodeWD : public  node<T>
{
public:
	nodeWD(T* data, node<T>* P = 0, node<T>* N = 0){ this->val = data, this->prev = P; this->next = N; }
	~nodeWD() override { this->val = 0; }
};
template <typename T> class listV;
template <typename T> class nodeV //����� node �������� ������ ������
{
	friend class listV<T>;
public:
	nodeV* next; //��������� �� ��������� ������� � ������
	nodeV* prev;
	T val; //������ ������
	nodeV(T data, nodeV* P = 0, nodeV* N = 0) { val = data, prev = P; next = N; }
	~nodeV() {}
};
template <typename T> class listV
{
public:
	nodeV<T>* head; //��������� �� ������ ������
	int count; //���������� ��������� � ������
public:
	listV() : head(NULL), count(0) {}
	~listV() {
		Clear(); //������� ����������� ������, ������������ ��� �������� ������
	}
	int Add(T data)//���������� �������� � ����� ������. ���������� ���������� ��������� � ������
	{
		if (count == 0) {//���� � ������ ��� ���������
			nodeV<T>* to_add = new nodeV<T>(data);
			head = to_add;
			head->next = head;
			head->prev = head;
		}
		else
		{
			nodeV<T>* temp = head->prev;
			nodeV<T>* to_add = new nodeV<T>(data, temp, head);
			head->prev = to_add;
			temp->next = to_add;
		}
		count++;
		return count;
	}
	int Del(nodeV<T>* temp) //�������� ���� �� ������. ���������� ���������� ��������� � ������. 
	{
		count--;
		if (head == temp)
			head = head->next;
		nodeV<T> * N = temp->next, *P = temp->prev;
		N->prev = P;
		P->next = N;
		delete temp;
		return count;
	}
	void Clear() //������� ������
	{
		if (count != 0) {
			nodeV<T>* current = head;
			for (int i = count; i > 0; i--) {
				nodeV<T>* DEL = current;
				current = current->next;
				delete DEL;
			}
			head = NULL;
			count = 0;
		}
	}
};
template <typename T> class list
{
public:
	node<T>* head; //��������� �� ������ ������
	int count; //���������� ��������� � ������
public:
	list() : head(NULL), count(0) {}
	~list() {
		Clear(); //������� ����������� ������, ������������ ��� �������� ������
	}
	int Add(T* data)//���������� �������� � ����� ������. ���������� ���������� ��������� � ������
	{
		if (count == 0) {//���� � ������ ��� ���������
			node<T>* to_add = new node<T>(data);
			head = to_add;
			head->next = head;
			head->prev = head;
		}
		else
		{
			node<T>* temp = head->prev;
			node<T>* to_add = new node<T>(data, temp, head);
			head->prev = to_add;
			temp->next = to_add;
		}
		count++;
		return count;
	}
	int AddWD(T* data)//
	{
		if (count == 0) {//���� � ������ ��� ���������
			node<T>* to_add = new nodeWD<T>(data);
			head = to_add;
			head->next = head;
			head->prev = head;
		}
		else
		{
			node<T>* temp = head->prev;
			node<T>* to_add = new nodeWD<T>(data, temp, head);
			head->prev = to_add;
			temp->next = to_add;
		}
		count++;
		return count;
	}
	int Del(node<T>* temp) //�������� ���� �� ������. ���������� ���������� ��������� � ������. 
	{
		count--;
		if (head == temp)
			head = head->next;
		node<T> * N = temp->next, *P = temp->prev;
		N->prev = P;
		P->next = N;
		delete temp;
		return count;
	}
	void Clear() //������� ������
	{
		if (count!= 0) {
			node<T>* current = head;
			for (int i = count; i > 0; i--) {
				node<T>* DEL = current;
				current = current->next;
				delete DEL;
			}
			head = NULL;
			count = 0;
		}
	}
};