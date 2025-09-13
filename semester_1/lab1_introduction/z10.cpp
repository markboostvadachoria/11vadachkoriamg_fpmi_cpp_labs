#include <iostream>

using namespace std;

int main()
{
    int x;
    cin >> x;
    int sl = x % 10 + (x / 10) % 10 + (x / 100) % 10;
    x /= 1000;
    int sf = x % 10 + (x / 10) % 10 + (x / 100) % 10;

    if (sf == sl)
        cout << "YES";
    else
        cout << "NO";
    return 0;
}
