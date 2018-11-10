#include <iostream>

using namespace std;

int postfix[10000001];

int prefix[10000001];


void write (int posts,int poste, int pres)
{
    
    if (posts == poste)
    {
        prefix[pres] = postfix[poste];
        
        return;
    }
    
    if (posts > poste)
    {
        return;
    }
    
    if (posts <= 0 || poste <= 0)
    {
        return;
    }
    
    prefix[pres] = postfix[poste];
    
    int acc;
    
    int cnt = 0;
    
    for (int i = posts; i < poste; i++)
    {
        if (postfix[i] > postfix[poste])
        {
            acc = i;
            cnt = 1;
            break;
        }
    }
    
    if (cnt == 0)
    {
        acc = poste;
    }
    
    write(posts,acc-1, pres+1);
    
    write(acc,poste-1,pres + acc + 1 - posts);
}


int main ()
{
    int n;
    
    cin>>n;
    
    for (int j = 1; j < n+1; j++)
    {
        cin>>postfix[j];
    }
    
    write(1,n,1);
    
    for (int j = 1; j < n+1; j++)
    {
        cout<<prefix[j]<<" ";
    }
    
}
