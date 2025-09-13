#include<iostream>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    cout << 1 << ' ';
    for (int i = 2; i * i <= min(n, m); i++)
        if ((n % i == 0) && (m % i == 0))
            if (i != n / i)
                cout << i << ' ' << n / i << ' ';
            else
                cout << i << ' ';

    return 0;
}
