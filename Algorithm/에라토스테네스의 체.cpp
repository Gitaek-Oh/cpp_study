#include <iostream>
#include <cmath>
using namespace std;

/*
에라토스테네스의 체는 이러한 소수의 개념을 이용한 알고리즘이다.
임의의 수 n 까지의 소수를 구하고자 할 때 2부터 n의 제곱근까지 돌며 모든 배수들을 소수에서 제외시키는 방식이다.
*/
int main()
{
    int begin, end;
    cin >> begin >> end;
    int primeNum[1000001] = {};


    for (int i = 2; i <= end; ++i)
        primeNum[i] = i;

    for (int i = 2; i <= sqrt(end); ++i)
    {
        if (primeNum[i] == 0)
            continue;
        for (int j = i * i; j <= end; j+=i)
        {
            primeNum[j] = 0;
        }
    }

    for (int i = begin; i <= end; ++i)
    {
        if (primeNum[i] != 0)
            cout << i << "\n";
    }

    return 0;
}
