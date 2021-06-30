#include <string>
#include <vector>
#include <iostream>
using namespace std;
int a[9] = { 0 };


bool dup(void)
{
    bool jump = false;
    for (int i = 0; i < 8; i++)
    {
        if (jump)
            break;
        for (int j = i + 1; j < 9; j++)
        {
            if (a[i] == 0)
            {
                jump = true;
                break;
            }
            if (a[i] == a[j])
                return true;
        }
    }
    return false;
}

void nested_loop(int n)
{
    if (n == 0)
    {
        for (a[n] = 1; a[n] <= 9; a[n]++)
        {
            if (dup())  continue;
            if ((a[8] * 10000 + a[7] * 1000 + a[6] * 100 + a[5] * 10 + a[4] * 1) - (a[3] * 1000 + a[2] * 100 + a[1] * 10 + a[0] * 1) == 33333)
            {
                cout << a[8] << a[7] << a[6] << a[5] << a[4] << endl;
                cout << '-' << a[3] << a[2] << a[1] << a[0] << endl;
                cout << "-----" << endl;
                cout << "33333" << endl;

                exit(EXIT_SUCCESS);
            }
        }
        return;
    }
    for (a[n] = 1; a[n] <= 9; a[n]++)
    {
        nested_loop(n - 1);
    }
}

int main()
{
    cout << "layer? " << endl;
    int x;
    cin >> x;
    cout << endl;
    nested_loop(x);

    return 0;
}