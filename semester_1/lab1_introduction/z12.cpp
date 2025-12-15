#include <iostream>
#include<iomanip>

using namespace std;

int main()
{
    int k, n;
    cin >> k >> n;

    int cnt = 1, nn = 1;
    while (cnt <= n)
    {
        cout << setw(2) << nn << ' ' << '|' <<  "   ";
        for (int j = 1; j <= 7; j++){
            if (j < k && nn == 1)
                cout << "  " << " ";
            else{
                cout << setw(2) << cnt << ' ';
                cnt++;
                if (cnt > n)
                    break;

            }


        }
        cout << '\n';
        nn ++;


    }
    return 0;
}
