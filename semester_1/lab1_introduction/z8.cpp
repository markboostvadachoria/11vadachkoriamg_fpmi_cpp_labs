#include <iostream>

using namespace std;

int main()
{
    double p, n, s;
    cin >> p >> n >> s;
    int cnt = 0;
    if (n < p && n < s)
        cnt++;
    for (int i = 0; i < 7; i++)
    {
        double x;
        cin >> x;
        if (s < n && s < x)
            cnt++;
        n = s;
        s = x;
    }
    cout << cnt;
    return 0;
}
