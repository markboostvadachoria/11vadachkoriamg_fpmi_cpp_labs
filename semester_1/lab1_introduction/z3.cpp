#include <iostream>
#include<limits.h>
using namespace std;
typedef unsigned long long ull;

ull st(ull a, ull n)
{
    if (n == 0)
        return 1;
    if (n % 2 == 0)
        return st(a * a, n / 2);
    if (n % 2 != 0)
        return a * st(a, n - 1);

}



int main()
{
    ull n;
    cin >> n;
    ull res = 0;

    for (ull i = 1; i <= n; i++)
        res += st(i, i);
    cout << res;
    // при n > 5000 происходит перполнение типа unsigned long long
    return 0;
}
