#include <iostream>

#define BASE 761

using namespace std;

long long int treehash[100001];

long long int basepowers[100001];

void merge (int start, int middle, int end)
{
    int size1 = middle - start + 1;
    int size2 = end - middle;
    
    int temp1[size1];
    int temp2[size2];
    
    for (int i = 0; i < size1; i++)
    {
        temp1[i] = treehash[start + i];
    }
    
    for (int i = 0; i < size2; i++)
    {
        temp2[i] = treehash[middle + 1 + i];
    }
    
    int itmerged = start;
    
    int it1 = 0 , it2 = 0;
    
    while (it1 < size1 && it2 < size2)
    {
        if (temp1[it1] <= temp2[it2])
        {
            treehash[itmerged] = temp1[it1];
            it1++;
        }
        else
        {
            treehash[itmerged] = temp2[it2];
            it2++;
        }
        itmerged++;
    }
    
    while (it1 < size1)
    {
        treehash[itmerged] = temp1[it1];
        it1++;
        itmerged++;
    }
    while (it2 < size2)
    {
        treehash[itmerged] = temp2[it2];
        it2++;
        itmerged++;
    }
}

void mergesort (int start, int end)
{
    if (start == end)
    {
        return;
    }
    else
    {
        int middle = start + (end - start) / 2;
        mergesort(start,middle);
        mergesort(middle+1,end);
        merge(start,middle,end);
    }
}



int main()
{
    
    for (int t = 1; t < 100001; t++)
    {
        treehash[t] = 0;
    }
    
    basepowers[0] = 1;
    
    for (int t = 1; t < 100001; t++)
    {
        basepowers[t] = basepowers[t-1] * BASE;
    }
    
    int n,k;
    
    cin>>n>>k;
    
    int father,child;
    
    for (int i = 1; i < n+1; i++)
    {
        for (int j = 1; j < k; j++)
        {
            cin>>father>>child;
            
            treehash[i] += father * basepowers[child];
            
        }
    }
    
    mergesort(1,n);
    
    int cnt = 1;
    
    for (int s = 1; s < n; s++)
    {
        if (treehash[s] != treehash[s+1])
        {
            cnt++;
        }
    }
    
    cout<<cnt;
}
