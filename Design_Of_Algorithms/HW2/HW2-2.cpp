#include <iostream>
#include <vector>

using namespace std;

class Two_int
{
public:
    long long int a;
    long long int b;
};

class Complete_Weighted_Graph
{
public:
    
    long long int num_of_vertex;
    
    long long int weights[1000][1000];
    
    long long int MST_Min()
    {
        long long int max;
        vector<long long int> vertex;
        vector<long long int> not_vertex;
        for (long long int j = 1; j < num_of_vertex; j++)
        {
            not_vertex.push_back(j);
        }
        vector<Two_int> edges;
        vertex.push_back(0);
        while (vertex.size() < num_of_vertex)
        {
            max = 0;
            long long int iindex,jindex;
            for (long long int j = 0; j < vertex.size(); j++)
            {
                for (long long int i = 0; i < not_vertex.size(); i++)
                {
                    if (weights[not_vertex[i]][vertex[j]] > max)
                    {
                        max = weights[not_vertex[i]][vertex[j]];
                        jindex = vertex[j];
                        iindex = not_vertex[i];
                    }
                }
            }
            Two_int temp;
            temp.a = iindex;
            temp.b = jindex;
            edges.push_back(temp);
            vertex.push_back(iindex);
            for (long long int i = 0; i < not_vertex.size(); i++)
            {
                if (not_vertex[i] == iindex)
                {
                    not_vertex.erase(not_vertex.begin()+ i);
                }
            }
        }
        
        long long int min = max;
        
        for (long long int j = 0; j < edges.size(); j++)
        {
            if (weights[edges[j].a][edges[j].b] < min)
            {
                min = weights[edges[j].a][edges[j].b];
            }
        }
        return min;
    }
    
};

int main()
{
    long long int n,p;
    cin>>n>>p;
    long long int k[1000];
    long long int a[1000][1000];
    for (long long int i = 0; i < n; i++)
    {
        cin>>k[i];
    }
    for (long long int s = 0; s < n; s++)
    {
        for (long long int t = 0; t < n; t++)
        {
            a[s][t] = k[s] ^ k[t];
        }
    }
    
    /*for (int s = 0; s < n; s++)
     {
     for (int t = 0; t < n; t++)
     {
     cout<<a[s][t]<<" ";
     }
     cout<<endl;
     }*/
    
    Complete_Weighted_Graph test;
    
    for (long long int s = 0; s < n; s++)
    {
        for (long long int t = 0; t < n; t++)
        {
            test.weights[s][t] = a[s][t];
        }
    }
    test.num_of_vertex = n;
    cout<<test.MST_Min()<<endl;
}
