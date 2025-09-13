#include <iostream>

using namespace std;

int main()
{
    double n, res = 0;
    cin >> n;
    double tmp;
    cin >> tmp;
    double minn = tmp, maxx = tmp;
    for (int i = 1; i < n; i++)
    {
        double x;
        cin >> x;
        res += x;
        minn = min(minn, x);
        maxx = max(maxx, x);
    }

    cout << res / n << ' ' << minn << ' ' << maxx;
    return 0;
}
