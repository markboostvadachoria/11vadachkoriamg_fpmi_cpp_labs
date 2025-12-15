#include<iostream>

using namespace std;

int main()
{
    int k;
    cin >> k;
    int res = 1;
    if (k % 2 == 0)
        for (int i = 2; i <= k; i += 2)
            res *= i;
    else
        for (int i = 1; i <= k; i += 2)
            res *= i;
    cout << res;

    return 0;
}
