#include <iostream>
using namespace std;
#include <vector>
#include <list>

template<typename T>
class Node
{
public:
	Node()
	{
		_next = nullptr;
		_prev = nullptr;
		_data = T();
	}

	Node(const T& value)
	{
		_next = nullptr;
		_prev = nullptr;
		_data = value;
	}
public:
	Node* _next;
	Node* _prev;
	T _data;
};

template<typename T>
class Iterator
{
public:
	Iterator()
	{
		_node = nullptr;
	}

	Iterator(Node<T>* node)
	{
		_node = node;
	}

	// ++it
	Iterator& operator++()
	{
		_node = _node->_next;
		return *this;
	}
	// it++
	Iterator operator++(int)
	{
		Iterator<T> temp = *this;
		_node = _node->_next;
		return temp;
	}
	// --it
	Iterator& operator--()
	{
		_node = _node->_prev;
		return *this;
	}
	// it--
	Iterator operator--(int)
	{
		Iterator<T> temp = *this;
		_node = _node->_prev;
		return temp;
	}

	T& operator*()
	{
		return _node->_data;
	}
	bool operator==(const Iterator& right)
	{
		return _node == right._node;
	}

	bool operator!=(const Iterator& right)
	{
		return _node != right._node;
	}

public:
	Node<T>* _node;
};

template<typename T>
class List
{
public:
	List()
	{
		// [1] <-> [2] <-> [header] <->
		// <-> [header] <->
		_size = 0;
		_header = new Node<T>();
		_header->_next = _header;
		_header->_prev = _header;
	}
	~List()
	{
		// TODO: 메모리를 해제시켜주는 작업이 필요하다
		while (_size > 0)
			pop_back();

		delete _header;
	}

	void push_back(const T& value)
	{
		AddNode(_header, value);
	}

	void pop_back()
	{
		// [1] <-> [2] <-> [3](이거 삭제) <-> [header] <->
		RemoveNode(_header->_prev);
	}
	// <-> [header] <->
	// [1] <-> [2] - [value] - [before] <-> [header] <->
	Node<T>* AddNode(Node<T>* before, const T& value)
	{
		// [1] <-> [2] - [value] - [before] <-> [header] <->
		Node<T>* node = new Node<T>(value);

		//[1] <-> [prevNode] <-> [node] - [before] <-> [header] <->
		Node<T>* prevNode = before->_prev;
		prevNode->_next = node;
		node->_prev = prevNode;

		//[1] <-> [prevNode] <-> [node] <-> [before] <-> [header] <->
		node->_next = before;
		before->_prev = node;

		_size++;

		return node;
	}

	Node<T>* RemoveNode(Node<T>* node)
	{
		// [1] <-> [node] <-> [3] <-> [header] <->
		// [prevNode] <-> (삭제) <-> [nextNode] <-> [header] <->
		Node<T>* prevNode = node->_prev;
		Node<T>* nextNode = node->_next;

		prevNode->_next = nextNode;
		nextNode->_prev = prevNode;

		delete node;

		_size--;

		// node를 삭제했으면 다음 주소를 반환해줘야한다.
		return nextNode;
	}

	int size() { return _size; }

public:
	typedef Iterator<T> iterator;

	iterator begin() { return iterator(_header->_next); }
	iterator end() { return iterator(_header); }

	iterator insert(iterator it, const T& value)
	{
		Node<T>* node = AddNode(it._node, value);
		return iterator(node);
	}

	iterator erase(iterator it)
	{
		Node<T>* node = RemoveNode(it._node);
		return iterator(node);
	}
public:
	Node<T>* _header;
	int _size;
};

int main()
{
	List<int> li;

	List<int>::iterator eraseIt;

	for (int i = 0; i < 10; i++)
	{
		if (i == 5)
		{
			eraseIt = li.insert(li.end(), i);
		}
		else
		{
			li.push_back(i);
		}
	}

	li.pop_back();

	li.erase(eraseIt);

	for (List<int>::iterator it = li.begin(); it != li.end(); ++it)
	{
		cout << (*it) << endl;
	}

	return 0;
}