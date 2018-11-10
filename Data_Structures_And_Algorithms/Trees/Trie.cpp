#include <iostream>

using namespace std;

typedef struct node
{
    int childs;
    
    int value;
    
    struct node* next[10];
}nd;

class trie
{
public:
    
    nd* root;
    
    trie()
    {
        this->root = new nd;
        
        this->root->childs = 0;
        
        for (int j = 0; j < 10; j++)
        {
            this->root->next[j] = NULL;
        }
    }
    
    void insert(int n)
    {
        
        int firstn = n;
        
        nd* it = this->root;
        
        int s = 10000000;
        
        for (int j = 6; j >= 0; j--)
        {
            s = s / 10;
            
            int temp;
            
            temp = n/s;
            
            n = n - (temp * s);
            
            if (it->next[temp] == NULL)
            {
                it->next[temp] = new nd;
                
                it->next[temp]->childs = 0;
                
                for (int k = 0; k < 10; k++)
                {
                    it->next[temp]->next[k] = NULL;
                }
            }
            
            it->childs++;
            
            it = it->next[temp];
            
        }
        
        it->value = firstn;
        
        it->childs++;
    }
    
    void remove(int n)
    {
        nd* it = this->root;
        
        int s = 10000000;
        
        for (int j = 6; j >= 0; j--)
        {
            s = s / 10;
            
            int temp = n / s;
            
            n = n - (temp*s);
            
            it->childs--;
            
            it = it->next[temp];
            
        }
        
        it->childs--;
        
    }
    
    int find(int n,nd* root)
    {
        int cnt = 0;
        for (int j = 0; j < 10; j++)
        {
            if (root->next[j] == NULL)
            {
                cnt++;
            }
        }
        
        if(cnt == 10)
        {
            return root->value;
        }
        
        for (int j = 0; j < 10; j++)
        {
            if (root->next[j] != NULL)
            {
                if (root->next[j]->childs >= n)
                {
                    return find(n,root->next[j]);
                }
                n = n - root->next[j]->childs;
            }
        }
        
        
    }
    
    int median()
    {
        int size = this->root->childs;
        
        if (size%2 == 0)
        {
            return (find(size/2,this->root) + find(size/2 + 1,this->root)) / 2;
        }
        else
        {
            return (find((size+1)/2,this->root));
        }
    }
    
};

int main ()
{
    ios_base::sync_with_stdio(false);
    
    trie test;
    
    int n;
    
    cin>>n;
    
    int a,b;
    
    int isrepeat = 0;
    
    int tempor;
    
    for (int j = 1; j < n+1; j++)
    {
        cin>>a;
        
        if (a == 1)
        {
            cin>>b;
            test.insert(b);
            isrepeat = 0;
        }
        
        if (a == 2)
        {
            cin>>b;
            test.remove(b);
            isrepeat = 0;
        }
        
        if (a == 3)
        {
            if (isrepeat == 1)
            {
                cout<<tempor<<endl;
                isrepeat = 1;
            }
            else
            {
                tempor = test.median();
                cout<<tempor<<endl;	
            }
        }
    }
}
