#include <iostream>
using namespace std;
#include <vector>
#include <list>


class Node
{
public:
	Node* _next; // 주소값을 갖는 바구니
	Node* _prev; // 이것을 추가해주면 이중 연결리스트가 된다!
	int _data;
};
// -> [ data(4) next( data(4) next( data() next(...)) ) ] 최종 사이즈는 Node[ data(4), next(4/8) ] 이다.
int main()
{
	/*
	vector 와 list 차이
	- vector: 동적배열
	- list : 연결리스트 (노드방식 -> [1]과 같이 칸 단위이다.)
	1) 단일 연결리스트
	순차적으로 데이터를 저장하는 방식은 같으나 연속적으로 배치를 하지는 않고 데이터를 가르키는 방식으로 저장된다.
	[1]           ->         [2]  -> [3] ->[4]
	2) 이중 연결리스트
	단일 연결리스트와 큰 차이는 없고 앞뒤로 연결되어있다.
	[1]           <->         [2]  <-> [3] <->[4]
	2) 원형 연결리스트
	이중 연결리스트에서 마지막 데이터가 초기 데이터를 가르킨다.
	[1]           <->         [2]  <-> [3] <->[4] <-> [1]

	list (연결 리스트)
	- list의 동작원리
	- 중간 삽입/삭제 , 처음/끝 삽입/삭제 (GOOD)
	->next와 prev가 가르키는 것을 확인하고 값을 바꿔주면 다른 데이터를 건드리지 않아도 되기 때문에 효율적이다.
	- 임의 접근 (i번째 데이터는 어디 있습니까? BAD)
	-> vector의 경우 연속적으로 저장되어 있기 때문에 바로 찾는 것이 가능했다 ex) v[3]
	-> list의 경우 연속되지 않고 분리되어 있는 형태이다. (앞 뒤의 포인터 값만 저장한다)
	-> 따라서 0번 부터 시작해서 직접 워프를 타고 접근해야 하기 때문에 비효율적이다!!!

	*/
	list<int> li;

	for (int i = 0; i < 100; i++)
	{
		li.push_back(i);
	}

	// list를 한번 살펴볼까??
	// li.push_front(10); // 맨 앞에 넣는 것 가능
	// vector는 비효율적이라 push_front를 막아뒀지만 list는 왜 풀어줬을까??
	// -> 처음에 데이터를 삽입하는게 아무런 부담이 없기 때문이다

	int size = li.size();
	// li.capacity(); list는 동적배열이 아니기때문에 없다...
	// -> 뭔가 여유공간을 잡아가지고 만들어주는 개념이 아니라 필요할 때마다 노드연결해서 만들어주는 개념이기에 없다!!!

	int front = li.front();
	int last = li.back();
	// li[10000000000000000] = 10; 임의 접근이 막혀있다... 동적배열이 아니기 때문?
	// -> 포인터를 타고타고타고 해야하기 때문에 굉장히 비효율적이다.

	list<int>::iterator itBegin = li.begin();
	list<int>::iterator itEnd = li.end();

	/*
	0x0125D718  0125d7c0 ? ? % . -> _next ( 주소 값을 찾아가면 밑에 3개로 나온다)
	0x0125D71C  0125d248  H ? % . -> _prev
	0x0125D720  00000001  .... -> _data

	0x0125D7C0  0125d8a0  ??%. -> _next
	0x0125D7C4  0125d718  .?%. -> _prev
	0x0125D7C8  00000002  .... -> _data

	메모리를 까보면
	[처음값: 0] <-> ~ <-> [마지마값: 99 (16진수)] <-> [cdcdcdcd(_Myhead : end()) ] 이런식으로 나온다....
	가상의 노드를 하나 만들어줘서 유효 범위인지 아닌지 판단을 해주는 값이 마지막에 들어간다!!!!
	-> 따라서 list.end() 값을 활용해서는 안된다.
	*/

	// list<int>::iterator itTest = --itBegin;
	// list<int>::iterator itTest = ++itEnd;
	// -> 더미 값을 가르키게 하는 것은 오류가 난다 -> 더미의 값은 잘못된 값을 가르키게 하는 것을 잡아주기 위해서 넣어줬다고 알 수 있다.
	list<int>::iterator itTest = --itEnd;

	int* ptrBegin = &(li.front());
	int* ptrEnd = &(li.back());

	for (list<int>::iterator it = li.begin(); it != li.end(); ++it)
	{
		cout << (*it) << endl;
	}
	/*
	li.insert(itBegin, 100);
	li.erase(li.begin());
	li.pop_front(); // 위의 내용과 같다(맨 앞 삭제)

	li.remove(10); // 10의 value를 가지고 있는 데이터는 모두 삭제한다.
	// 노드를 삭제하고 가르키는 방향만 설정해주기 때문에 사용할 수 있다! (Vector는 비효율적으로 데이터들을 움직여야하기에 막혀있다.)
	*/



	/*
	중간 삽입/삭제는 데이터를 찾아서 next와 prev를 수정하는 과정이고 임의접근도 데이터를 찾는 것은 똑같은데
	임의 접근은 안된다고 했고 중간 삽입/삭제는 빠르다고 했을까?????

	ex) 50번 인덱스에 있는 데이터를 삭제!!!
	list<int>::iterator it = li.begin();
	for (int i = 0; i < 50; i++) ++it;// li.erase(li.begin() + 50)의 과정
	li.erase(it);

	이 식 자체로만 보면 임의접근과 중간 삽입/삭제하는 과정은 별다를바가 없다....
	그러나 아래와 같이 데이터를 찾는 과정과 중간 삽입/삭제 과정을 분류해 놓으면

	list<int>::iterator it = li.begin();
	for (int i = 0; i < 50; i++) ++it;// li.erase(li.begin() + 50)의 과정


	li.erase(it);

	데이터를 찾는 과정은 똑같이 오래걸리지만 삭제하는 과정은 매우 빠르다는 것을 알 수 있다!!! (두 과정을 따로 분류해서 봐야한다!!!!!! 기어...억해 제발******************************)
	그러기 때문에 중간 삽입/삭제가 빠르다는 것이다!!!
	*/



	return 0;

}