#include <iostream>
using namespace std;
#include <vector>

template<typename T>
class Iterator
{
public:
	Iterator()
	{
		_ptr = nullptr;
	}

	~Iterator(T* ptr)
	{

	}

	Iterator& operator++() // 전위형
	{
		/*
		++a 일 때 참조(&)를 넣는 이유!!
		int a = 1;
		int b = ++(++a);
		-> ++을 앞에 넣어주게 되면 a에다가 1을 증가시킨(자기 자신을 참조로 뱉어주는 형태) 다음 그 값을 b에다가 넣어주기 때문에 &를 쓴다.
		*/
		_ptr++;
		return *this;
	}

	Iterator operator++(int) // 후위형
	{
		/*
		int a = 1;
		int b = (a++);
		-> ++을 뒤에 넣어주게 되면 a를 복사한 이후 b에다가 a를 넣어주고 그 다음 a를 1 증가시켜주기 때문에 &가 필요없다.
		*/
		Iterator temp = *this;
		_ptr++;
		return temp;
	}

	Iterator& operator--() // 전위형
	{
		_ptr++;
		return *this;
	}

	Iterator operator--(int) // 후위형
	{
		Iterator temp = *this;
		_ptr++;
		return temp;
	}

	Iterator operator+(const int count)
	{
		Iterator temp = *this;
		temp._ptr += count;
		return temp;
	}

	Iterator operator-(const int count)
	{
		Iterator temp = *this;
		temp._ptr -= count;
		return temp;
	}

	bool operator==(const Iterator& right)
	{
		return _ptr == right._ptr;
	}

	bool operator!=(const Iterator& right)
	{
		return _ptr != right._ptr;
	}

	T& operator*()
	{
		return *_ptr;
	}

public:
	T* _ptr;
};


template<typename T>
class Vector
{
public:

	Vector()
	{
		_data = nullptr;
		_size = 0;
		_capacity = 0;
	}

	~Vector()
	{
		if (_data) // 0이 아닌지만 체크
			delete[] _data;
	}

	void push_back(const T& val)
	{
		if (_size == _capacity)
		{
			// 증설 작업
			int newCapacity = static_cast<int>(_capacity * 1.5);

			if (newCapacity == _capacity)
				newCapacity++;

			reserve(newCapacity);
		}

		// 데이터 저장([1][2][3][val] 이런 식으로 넣어줘야한다.)
		_data[_size] = val;

		// 데이터 개수 증가
		_size++;
	}

	void reserve(int capacity)
	{
		_capacity = capacity;

		T* newData = new T[_capacity];

		// 데이터 복사
		for (int i = 0; i < _size; i++)
			newData[i] = _data[i];

		// 기존에 있던 데이터를 날린다....
		if (_data)
			delete[] _data;

		// 새집으로 이동
		_data = newData;
	}

	void clear() { _size = 0; }

	T& operator[](const int pos) { return _data[pos]; }
	int size() { return _size; }
	int capacity() { return _capacity; }

public:
	typedef Iterator<T> iterator;
	iterator begin() { return iterator(&_data[0]); }
	iterator end() { return begin() + _size;; }

private:
	T* _data;
	int _size;
	int _capacity;
};

int main()
{
	Vector<int> v;

	v.reserve(100);

	for (int i = 0; i < 100; i++)
	{
		v.push_back(i);
		cout << v.size() << " " << v.capacity() << endl;
	}

	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << endl;
	}

	cout << "_________________" << endl;

	for (Vector<int>::iterator it = v.begin(); it != v.end(); ++it)
	{
		cout << (*it) << endl;
	}

	v.clear();

	return 0;
}