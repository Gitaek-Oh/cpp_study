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
	
	/* 동적 배열
		매우 매우 중요한 개념 -> 어떤 마법을 부렸길래 배열을 "유동적으로" 사용한 것인가?
			1) (여유분을 두고) 메모리를 할당한다.
				-> 이것도 메모리를 낭비하는 것 아니야???
			2) 여유분까지 꽉 찼으면 메모리를 증설한다. 
				-> 배열이라 함은 처음에 크기를 지정해서 만들어주는 데 증설한다는 게 가능한 얘기인가???
				-> 기존에 있던 영역을 버리고 새로 만들어준다!!

			Q1) 여유분은 얼만큼이 적당할까?
			Q2) 증설을 얼만큼 해야할까?
			Q3) 기존의 데이터를 어떻게 처리할까?
				-> Q3) 기존의 데이터를 복사해서 새로운 집으로 이사시킨다... 데이터가 점점 많아질 수록 여유분의 크기(1.5배로 늘어나다가 2배로 늘어나듯)가 점점 늘어나게 된다...
	*/
	const int MAX_SIZE = 10;
	int arr[MAX_SIZE] = {};

	/*for (int i = 0; i < MAX_SIZE; i++) arr[i] = i;
		만약에 데이터가 딱 10개만 있는 게 아니라 데이터를 추가로 담고 싶으면 어떻게 될까....?
		MAX 값을 10000으로 두면되지!!! -> 이것도 데이터가 하나만 있다면... 메모리 낭비! -> 동적 배열을 쓰자!!
	*/


	// 동적 배열 (사이즈가 고무줄처럼 늘어났다가 줄어들 수가 있다!!!)
	vector<int> v; // std::생략

	v.resize(1000); // 기존의 사이즈를 1000개로 만들어준다...
	vector<int> v(1000, 0); // 아래처럼 사이즈, 초기값을 명시적으로 설정해 줄 수 있다.
	vector<int> v2 = v; // 기존에 있는 벡터를 복사해서 사용할 수 있다.
	 /* 
	 * size (실제 사용 데이터 개수) *
	 1 2 3 4 5 6 7 ....
	
	* capacity (여유분을 포함한 용량 개수) *
	 1 2 3 4 6 9 13 19 28 42 63 
		-> Q1), Q2) 여유분과 증설량은 현재 capacity에 따라 capacity에 비례한 capacity의 1.5배를 곱한 값  
	 */

	v.reserve(1000); //여유분을 1000개로 미리 만들어주는 역할

	// 면접질문: 왜 reserve를 잡아서 capacity를 조정하느냐..?
	// capacity가 꽉 찼을 때 기존의 데이터를 복사하는 과정을 생략할 수 있기 때문에 더 효율적으로 사용할 수 있게된다!!
	
	for (int i = 0; i < 1000; i++)
	{
		v.push_back(100);
		cout << v.size() << " " << v.capacity() << endl;
	}

	v.pop_back(); // 마지막에 들어간 데이터를 꺼내준다.
	v.back(); // 맨 마지막에 있는 데이터를 보고싶다면 마지막에 있던 데이터를 꺼내준다.
	v.front() // 맨 앞에 있는 데이터를 꺼내준다.

	v.clear(); // 벡터의 모든 값을 날려준다.
	cout << v.size() << " " << v.capacity() << endl; // size는 줄어들어도 capacity의 값이 줄어들지는 않는다! 출력: 0 2250

	//만약 capacity값을 깔끔하게 없애주고 싶으면 어떻게 할까?
	v.clear();
	vector<int>().swap(v); // 임시 벡터를 새로만들어서 swap을 시켜주면 기존에 있던 데이터는 없어지게 된다! 출력: 0 0
	cout << v.size() << " " << v.capacity() << endl;

	return 0;
}
