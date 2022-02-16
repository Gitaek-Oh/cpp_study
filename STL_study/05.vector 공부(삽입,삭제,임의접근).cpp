#include <iostream>
using namespace std;
#include <vector>

int main()
{
	/* STL (Standard Template Library) 
		프로그래밍할 때 필요한 자료구조/알고리즘들을 템플릿으로 제공하는 라이브러리
		
		컨테이너 (Container) : 데이터를 저장하는 객체 (자료구조 Data Structure)
			1) vector (동적 배열)
				- vector의 동작 원리 (size/capacity)
				- 중간 삽인/삭제
				- 처음/끝 삽입/삭제
				- 임의 접근
		*/
	
	// 반복자(Iterator) : 포인터와 유사한 개념, 컨테이너의 원소(데이터)를 가리키고, 다음/이전 원소로 이동가능
	vector<int> v(10);

	for (vector<int>::size_type i = 0; i < v.size(); i++) // using size_type       = typename _Alty_traits::size_type; (int 대신 사용)
		v[i] = i;

	vector<int>::iterator it; // vector의 클래스타입이란걸 알 수 있다.
	int* ptr;

	it = v.begin();
	ptr = &v[0];

	cout << (*it) << endl; // 0x00918ae8 {0}
	cout << (*ptr) << endl; // 0x00918ae8 {0}
	// 메모리를 까보면 *ptr은 어디에 소속되어 있지 않은데 Iterator는 누군가의 컨테이너에 소속(클래스 타입)되어 있다.
	// Iterator도 ++it, it++ 이런식으로 포인터처럼 활용이 가능하다.

	vector<int>::iterator itBegin = v.begin();
	vector<int>::iterator itEnd = v.end(); // 9, 다음에 쓰레기 값이 들어간다.


	 /*더 복잡해보이는데?
	 다른 컨테이너 v[i]와 같은 인덱스 접근이 안 될 수도 있음
	 iterator 는 vector뿐 아니라, 다른 컨테이너에도 공통적으로 있는 개념*/
	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
	{
		cout << (*it) << endl;
	}
	/* ++it가 성능이 조금 더 좋다고 한다....
	 _Vector_iterator& operator++() noexcept {
        _Mybase::operator++();
        return *this;
    } -> ++it

    _Vector_iterator operator++(int) noexcept {
        _Vector_iterator _Tmp = *this;
        _Mybase::operator++();
        return _Tmp;
    } -> it++ (복사하는 과정이 있다)
	*/

	int* ptrBegin = &v[0]; //v.begin()._Ptr -> _Ptr은 벡터를 까보면 클래스안에 있다는 것을 알 수 있다.
	int* ptrEnd = ptrBegin + 10; // v.end()._Ptr

	for (int* ptr = ptrBegin; ptr != ptrEnd; ++ptr)
	{
		cout << (*ptr) << endl;
	}

	vector<int>::const_iterator cit1 = v.cbegin();
	// *cit1 = 100; const라 수정이 불가능

	// 역방향 반복자도 수행이 가능하다! 사용할 일은 거의 없긴하다....
	for (vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); ++it)
	{
		cout << (*it) << endl;
	}



	/*	중간 삽입 / 삭제 (BAD, 비효율적!!!!!!)
		처음 / 끝 삽입 / 삭제 (BAD / GOOD)
		임의 접근 (Random Access)
		
		vector = 동적 배열 = 동적으로 사이즈가 커지는 배열 -> 배열
		vector는 원소가 하나의 메모리 블록에 연속하게 저장된다!!!

		중간 삽입
		[                     ]
		[0][1][5][2][3][4][ ] 
		-> 중간에 5를 삽입하면 나머지 뒤에 있는 값들이 한칸씩 밀려나게 된다.... 굉장히 비효율적이다!!!

		중간 삭제
		[                     ]
		[0][1][ ][2][3][4][ ]
		-> 삭제하고 끝이 아니다, 연속하게 저장해야되는 이유는 데이터를 쉽게 찾을 수 있기 때문이다....
		   (vector는 원소가 하나의 메모리 블록에 연속하게 저장된다!!!)
		   그래서 나머지 데이터들을 한칸씩 끌어와야한다.... 굉장히 비효율적이다!!!

		처음 삽입 / 삭제
		-> 중간 삽입 / 삭제와 마찬가지로 굉장히 비효율적!!!!

		끝 삽입 / 삭제
		-> 나머지 애들이 가만히 있어도 되기에 효율적이다!!!!
	 */

	v.push_back(1); // 끝 삽입
	v.pop_back(); // 끝 삭제

	//v.push_front(1); 비효율적이기에 애초에 막아둠
	
	/*
		3번째 데이터는 어디 있습니까? (임의 접근)
		v[2] = 3; 
		임의 접근은 데이터들이 연속적으로 있기 때문에 가능하다!
	*/

	// 이렇게 비효율적이라고 설명을 해도 필요한 경우가 있다면...??
	//v.insert(v.begin() + 2, 5); // 세번째 데이터를 5로 대체하고 싶다  ([0][1][2] -> begin=0을 가르킴)
	//v.erase(v.begin() + 2); // 세번째 데이터를 삭제
	//v.erase(v.begin() + 2, v.begin() + 4); // 세번째 데이터부터 네번째 데이터까지 삭제 (마지막에 포함된 애는 삭제가 안됨)

	// insert,erase를 한 다음에 반환하는 값이 있다... (마우스 커서를 갔다대면 using vector<int>::iterator = ~)
	vector<int>::iterator insertIt = v.insert(v.begin() + 2, 5); 
	vector<int>::iterator eraseIt1 = v.erase(v.begin() + 2); 
	vector<int>::iterator eraseIt2 = v.erase(v.begin() + 2, v.begin() + 4); 

	/*
	 쭉~ 스캔을 하면서, 3이라는 데이터가 있으면 일괄 삭제하고 싶다면??????
	 아래와 같이 하면 크래시가 난다
		-> 포인터랑 iterator와 비슷하긴 하지만 iterator는 포인터만 가지고 있는게 아니라 소속된 콘테이너도 가지고 있기 때문이다.
		-> 따라서 소속된 콘테이너가 삭제가 되면 어디에도 소속이 안되기 때문에 data == 3 이후에는 크래시가 나게 된다.
	for (vector<int>::iterator it = v.begin(); it != v.end(); ++it)
	{
		int data = *it;
		if (data == 3)
			v.erase(it); 
	}
	*/
	for (vector<int>::iterator it = v.begin(); it != v.end();)
	{
		int data = *it;
		if (data == 3)
			it = v.erase(it); // 이런식으로 수정해주면 iterator를 갱신시켜주기 때문에 문제가 없어진다....
		else
		{ 
			++it;
			// 여기서 또 문제인게 for(~++it)을 해주게되면 앞으로 땡겨준 다른 데이터들은 체크를 해주지만 3에서 4로 바뀐 데이터 바구니는 체크를 다시 안해주기 때문에
			// 갱신시켜준 it의 바구니 값을 다시 체크해줘야한다!!! -> 와우 어렵다.....ㅠㅠ
			// 예를 들어서 데이터가 3 3으로 연속되어 있는 경우 for(~++it)를 하면 땡겨져 들어온 3이 있음에도 불구하고 다음으로 넘어가버리게 된다.
			// 0x000001 3(삭제)->   3 (3에서 3으로 바뀜, 여기 있는 자리를 다시 체크안해주기 때문이다!!!)
			// 0x000002 3     ->   4 (3에서 4로 바뀜)

		}
			
	}


	return 0;
}
