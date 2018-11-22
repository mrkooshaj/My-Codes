#include <iostream>

using namespace std;

int main()
{
    long long int result = 0;
    
    long long int perm[10000];
    long long int isgone[10000];
    
    for (int k = 0; k < 10000; k++)
    {
        isgone[k] = 0;
    }
    long long int factmod[10000];
    long long int n;
    cin>>n;
    
    factmod[0] = 1;
    for (int j = 1; j < n+1; j++)
    {
        factmod[j] = (factmod[j-1] * j) % 1000000007;
    }
    
    for (int j = 0; j < n; j++)
    {
        cin>>perm[j];
    }
    
    int temp = 0;
    
    for (int t = 0; t < n; t++)
    {
        int iter = perm[t];
        isgone[iter-1] = 1;
        for (int s = 0; s < iter - 1; s++)
        {
            if (isgone[s] == 0)
            {
                temp++;
            }
        }
        temp = (temp * factmod[n - 1 - t]) % 1000000007;
        result = (result + temp) % 1000000007;
        temp = 0;
    }
    
    cout<<result + 1<<endl;
}
