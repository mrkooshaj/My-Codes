#include <iostream>

using namespace std;

long long int fact (int n)
{
    long long int result = 1;
    for (int j = 1; j < n+1; j++)
    {
        result = result * j;
    }
    return result;
}


int main ()
{
    long long int facts[21];
    for (int i = 1; i < 21; i++)
    {
        facts[i] = fact(i);
    }
    long long int n;
    cin>>n;
    if (n == 0)
    {
        cout<<0;
        return 0;
    }
    int start = 0;
    for (int j = 20; j > 0; j--)
    {
        if (n >= facts[j])
        {
            start = 1;
            int q = n / facts[j];
            if (q < 10)
            {
                cout<<q;
            }
            else
            {
                cout<<char('a' + (q - 10));
            }
            n = n - (q* facts[j]);
        }
        else
        {
            if (start == 1)
            {
                cout<<0;
            }
        }
    }
}
