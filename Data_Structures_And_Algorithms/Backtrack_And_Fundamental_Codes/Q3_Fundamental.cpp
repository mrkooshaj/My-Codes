#include <iostream>

using namespace std;

int main ()
{
    int mede,shakh;
    cin>>shakh>>mede;
    if (shakh % 2 == 1)
    {
        cout<<0;
        return 0;
    }
    int gav = shakh / 2;
    int possibility = 0;
    for (int v = 0; v < gav; v++)
    {
        if ((mede - 2*v) % (gav - v) == 0 && mede > 2*v)
        {
            possibility++;
        }
    }
    if (mede == 2 * gav)
    {
        possibility++;
    }
    cout<<possibility<<endl;
    if (mede == 2*gav)
    {
        cout<<0<<" ";
    }
    for (int v = gav - 1; v > 0; v--)
    {
        if ((mede - 2*v) % (gav - v) == 0 && mede > 2*v)
        {
            cout<<gav - v<<" ";
        }
    }
    if (mede % gav == 0)
    {
        cout<<gav<<" ";
    }
}
