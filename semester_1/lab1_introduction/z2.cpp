#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int p = 1, sum = 0;
    for (int i = 1; i <= n; i++){
        if (i % 2 == 0)
            sum += i;
        else
            p *= i;
    }
    cout << sum << ' ' << p;
}
