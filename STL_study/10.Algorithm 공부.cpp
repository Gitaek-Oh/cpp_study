#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <set>
#include <algorithm>

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	/* 자료구조와 알고리즘
	자료구조: 데이터를 저장하는 구조
	알고리즘: 데이터를 어떻게 사용할 것인가??

	find
	find_if

	count
	count_if
	all_of
	any_of
	none_of
	for_each
	remove
	remove_if
	*/

	vector<int> v;

	// Q1) number라는 숫자가 벡터에 체크하는 기능 (bool, 첫 등장 iterator)
	{
		int number = 50;

		bool found = false;
		vector<int>::iterator it = v.end();

		for (unsigned int i = 0; i < v.size(); ++i)
		{
			int data = v[i];
			if (data == number)
			{
				found = true;
				it = v.begin() + i;
				break;
			}
		}
		/*위에 코드는 가독성이 좋지가 않다, 따라서 알고리즘을 사용해보자!
		위에 코드랑 똑같음, iterator를 반환함
		vector가 아니라 list(list는 임의접근을 막아서 못쓴다)로 바꾸더라도 사용가능하다.*/
		vector<int>::iterator itFind = find(v.begin(), v.end(), number);

		if (itFind == v.end())
			cout << "못찾음" << endl;
		else
			cout << "찾음" << endl;
	}

	// Q2) 11로 나뉘는 숫자가 벡터에 있는지 체크하는 기능 (bool, 첫 등장 iterator)
	{
		bool found = false;
		vector<int>::iterator it = v.end();

		for (unsigned int i = 0; i < v.size(); ++i)
		{
			int data = v[i];
			if (data % 11 == 0)
			{
				found = true;
				it = v.begin() + i;
				break;
			}
		}

		struct CanDiviedBy11
		{
			bool operator()(int n)
			{
				return (n % 11) == 0;
			}
		};

		vector<int>::iterator itFind = std::find_if(v.begin(), v.end(), CanDiviedBy11());

		if (itFind == v.end())
			cout << "못찾음" << endl;
		else
			cout << "찾음" << endl;
	}

	// Q3) 홀수인 숫자의 개수는? (count)
	{
		int count = 0;

		for (unsigned int i = 0; i < v.size(); i++)
		{
			int data = v[i];
			if ((data % 2) != 0) count++;
		}

		struct IsOdd
		{
			bool operator()(int n)
			{
				return (n % 2) != 0;
			}
		};

		int n = std::count_if(v.begin(), v.end(), IsOdd());

		bool b1 = std::all_of(v.begin(), v.end(), IsOdd()); // 모든 데이터가 홀수입니까?
		bool b2 = std::any_of(v.begin(), v.end(), IsOdd()); // 홀수인 데이터가 하나라도 있습니까?
		bool b3 = std::none_of(v.begin(), v.end(), IsOdd()); // 모든 데이터가 홀수가 아닙니까?
	}

	// Q4) 벡터에 들어가 있는 모든 숫자들에 3을 곱해주세요!
	{
		for (unsigned int i = 0; i < v.size(); ++i)
		{
			v[i] *= 3;
		}

		struct MultiplyBy3
		{
			void operator()(int& n)
			{
				n = n * 3;
			}
		};

		std::for_each(v.begin(), v.end(), MultiplyBy3());
	}

	// Q5) 홀수인 데이터를 일괄 삭제
	{
		for (vector<int>::iterator it = v.begin(); it != v.end();)
		{
			if ((*it % 2) != 0)
				it = v.erase(it);
			else
				++it;
			// 이런 방식으로 하면 매번 홀수를 찾을 때마다 삭제를 하고 다른 데이터들을 움직여야한다....
		}

		struct IsOdd
		{
			bool operator()(int n)
			{
				return (n % 2) != 0;
			}
		};

		v.clear();

		v.push_back(1);
		v.push_back(4);
		v.push_back(3);
		v.push_back(5);
		v.push_back(8);
		v.push_back(2);
		//std::remove(v.begin(), v.end(), 4); // 4를 삭제하고 싶다!

		//std::remove_if(v.begin(), v.end(), IsOdd());

		// 위의 remove_if를 쓰면 다음과 같이 나온다
		// 1 4 3 5 8 2 (원본)
		// 4 8 2 5 8 2 - ??? 왜이렇게 나올까?

		/* remove_if는 다음과 같이 되어있다.
		template<class ForwardIt, class UnaryPredicate>
		ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPredicate p)
		{
		first = std::find_if(first, last, p);
		if (first != last)
		for (ForwardIt i = first; ++i != last; )
		if (!p(*i))
		*first++ = std::move(*i);
		return first;

		위에 코드는 남겨줘야될 데이터를 찾아준 후 복사해서 붙여넣어준다!
		원본) 1 4 3 5 8 2
		1) 4 4 3 5 8 2 -> 4 데이터를 남겨줘야겠다! 복사해서 붙여넣어준다 [0]
		2) 4 8 3 5 8 2 -> 8 데이터를 남겨줘야겠다! 복사해서 붙여넣어준다 [1]
		3) 4 8 2 5 8 2 -> 2 데이터를 남겨줘야겠다! 복사해서 붙여넣어준다 [2]

		결국 필요한 데이터만 앞당겨서 보내준거랑 다름없다...

		그래서 remove_if를 사용할 때는 조심해서 사용해야 한다!,
		아래 코드처럼 사용하면 해결된다!
		}*/

		vector<int>::iterator it = std::remove_if(v.begin(), v.end(), IsOdd());
		v.erase(it, v.end()); // 4 8 2 를 제외하고 모두 날려준다!


		v.erase(remove_if(v.begin(), v.end(), IsOdd()), v.end()); // 이런식으로 쓰면 위의 코드와 같아진다.
		int a = 3;
	}
	return 0;
}