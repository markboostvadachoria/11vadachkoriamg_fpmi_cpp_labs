#include <iostream>

using namespace std;

void dv(int x)
{
    if (x == 0)
        return;
    dv(x / 2);
    cout << x % 2;

}

void sh(int x)
{
    if (x == 0)
        return;
    sh(x / 16);
    if (x % 16 > 9)
        cout << char('A' + (x % 16) % 10);
    else
        cout << x % 16;


}

int main()
{
    int x;
    cin >> x;
    dv(x);
    cout << '\n';
    sh(x);
    return 0;
}


