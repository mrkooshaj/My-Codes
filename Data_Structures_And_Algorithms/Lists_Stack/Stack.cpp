#include <iostream>

using namespace std;

class Stack
{
public:
    
    string singers[501];
    
    int bala = 0;
    
    string top()
    {
        return this->singers[this->bala];
    }
    
    void pop()
    {
        this->singers[this->bala] = "";
        this->bala = this->bala - 1;
    }
    
    void push (string s)
    {
        this->singers[this->bala + 1] = s;
        this->bala = this->bala + 1;
    }
    
    bool empty()
    {
        if(this->bala == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
};


int main ()
{
    
    Stack input;
    Stack temp1;
    Stack temp2;
    
    int n;
    string singer;
    cin>>n;
    for (int j = 1; j < n+1; j++)
    {
        cin>>singer;
        cin.ignore(1);
        input.push(singer);
    }
    
    string wrongs;
    
    while (1 == 1)
    {
        int ismany = 0;
        
        getline(cin,wrongs);
        
        if (wrongs == "end")
        {
            break;
        }
        
        int sizee = wrongs.size();
        
        for (int j = 0; j < sizee; j++)
        {
            if (wrongs[j] == 32)
            {
                ismany = 1;
            }
        }
        
        if (ismany == 0)
        {
            int cnt = 0;
            while (input.top() != wrongs)
            {
                if (input.empty())
                {
                    cnt = 1;
                    break;
                }
                temp1.push(input.top());
                input.pop();
            }
            
            if (cnt == 0)
            {
                temp1.push(input.top());
                input.pop();
            }
            
            while (!(temp1.empty()))
            {
                temp2.push(temp1.top());
                temp1.pop();
            }
            
            while (!(temp2.empty()))
            {
                input.push(temp2.top());
                temp2.pop();
            }
        }
        
        else
        {
            string temp = "";
            int whereinarray = 1;
            int indexx = 0;
            
            int isfinish = 0;
            
            string badsingers[100001];
            
            int enable = 0;
            
            for (int j = 1; j < 100001; j++)
            {
                badsingers[j] = "";
            }
            
            
            while (wrongs != "")
            {
                int sizee = wrongs.size();
                
                for (int j = 0; j < sizee; j++)
                {
                    if (wrongs[j] == 32)
                    {
                        temp = wrongs.substr(0,j);
                        indexx = j;
                        break;
                    }
                }
                if (temp == "")
                {
                    temp = wrongs;
                    isfinish = 1;
                }
                
                badsingers[whereinarray] = temp;
                
                whereinarray++;
                
                string omit;
                
                for (int k = 0; k < sizee; k++)
                {
                    if (enable == 1)
                    {
                        omit = omit + wrongs[k];
                    }
                    if (wrongs[k] == 32)
                    {
                        enable = 1;
                    }
                }
                
                if (isfinish == 1)
                {
                    wrongs = "";
                }
                else
                {
                    wrongs = wrongs.substr(indexx+1,wrongs.size()-1);
                }				
                
                temp = "";
            }
            
            int breakcounter = 0;
            
            while(!(input.empty()))
            {
                int lstcntr = 0;
                
                string toop = input.top();
                
                for (int k = 1; k < whereinarray; k++)
                {
                    if(badsingers[k] == toop)
                    {
                        input.pop();
                        n = n - 1;
                        lstcntr++;
                        breakcounter++;
                        break;
                    }
                }
                if(lstcntr == 0)
                {
                    temp1.push(toop);
                    input.pop();
                }
                if (breakcounter == whereinarray - 1)
                {
                    break;
                }
                
            }
            while (!(temp1.empty()))
            {
                input.push(temp1.top());
                temp1.pop();
            }
            
        }
        
    }
    for (int j = 1; j < n+1; j++)
    {
        cout<<input.top()<<endl;
        input.pop();
    }
}
