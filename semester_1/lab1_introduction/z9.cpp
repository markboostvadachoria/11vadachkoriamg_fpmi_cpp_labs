#include <iostream>

using namespace std;

int main()
{
    int x;
    cin >> x;

    if (x % 10 == x / 1000 && (x / 10) % 10 == (x / 100) % 10)
        cout << "YES";
    else
        cout << "NO";
    return 0;
}
