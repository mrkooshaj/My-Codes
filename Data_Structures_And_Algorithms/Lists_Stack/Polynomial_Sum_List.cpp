#include <iostream>

using namespace std;

int xpow (string input)
{
    return (input[0] - '0');
}

int ypow (string input)
{
    return (input[1] - '0');
}

int zpow (string input)
{
    return (input[2] - '0');
}

int ragham (int n)
{
    int cnt = 0;
    while (n > 0)
    {
        n = n / 10;
        cnt++;
    }
    return cnt;
}

string numtostr (int n)
{
    
    string result = "";
    
    if (n == 0)
    {
        result = "0";
        return result;
    }
    
    int ragh = ragham(n);
    
    for (int j = 1; j <= ragh;j++)
    {
        int yek = n % 10;
        result = char(yek + 48) + result;
        n = n / 10;
    }
    
    return result;
}

int strtonum (string s)
{
    int sum = 0;
    
    int comp = 0;
    
    for (int j = 0; j < s.size(); j++)
    {
        int comp = s[j] - '0';
        for (int t = 1; t < s.size() - j; t++)
        {
            comp = comp * 10;
        }
        
        sum = sum + comp;
    }
    
    return sum;
}

string codedans (int xpower, int ypower, int zpower, int zarib)
{
    string result = "";
    result = result + numtostr(xpower) + numtostr(ypower) + numtostr(zpower) + numtostr(zarib);
    
    return result;
}

int coeff (string input)
{
    string s = input.substr(3,input.size()-1);
    
    int sum = 0;
    
    int adder;
    
    for (int j = 0; j < s.size(); j++)
    {
        adder = (s[j] - '0');
        for (int k = 1; k < s.size() - j; k++)
        {
            adder = adder * 10;
        }
        
        sum = sum + adder;
    }
    
    return sum;
}



struct node
{
    int val;
    
    int coeff;
    
    node * next;
    
    node * down;
};

class list
{
public:
    
    node * head , *tail;
    
    list()
    {
        head = NULL;
        tail = NULL;
    }
    
    void createnext(int value)
    {
        node * temp = new node;
        temp->val = value;
        temp->next = NULL;
        temp->down = NULL;
        if (head == NULL)
        {
            head = temp;
            tail = temp;
            temp = NULL;
        }
        else
        {
            tail->next = temp;
            tail = temp;
        }
    }
    
    void createdown(int value)
    {
        node* temp = new node;
        temp->val = value;
        temp->next = NULL;
        temp->down = NULL;
        tail->next = temp;
        head = temp;
        tail = temp;
        temp = NULL;
    }
    
};

int main ()
{
    
    string input;
    
    
    
    int powerx,powery,powerz,zarib;
    
    list polys;
    
    node * iter = new node;
    
    while (1 == 1)
    {
        cin>>input;
        
        if (input == "end")
        {
            break;
        }
        else if (input != "+")
        {
            iter = polys.head;
            
            if (iter == NULL)
            {
                node * temp = new node;
                
                temp->next = NULL;
                
                temp->val = xpow(input);
                
                temp->down = new node;
                
                temp->down->down = new node;
                
                temp->down->next = NULL;
                
                temp->down->val = ypow(input);
                
                temp->down->down->next = NULL;
                
                temp->down->down->val = zpow(input);
                
                temp->down->down->coeff = coeff(input);
                
                polys.head = temp;
                
                iter = temp;
                
            }
            
            else
            {
                int cnt = 0;
                while (iter != NULL)
                {
                    if (iter->val == xpow(input))
                    {
                        iter = iter->down;
                        while (iter != NULL)
                        {
                            if (iter->val == ypow(input))
                            {
                                iter = iter->down;
                                while (iter != NULL)
                                {
                                    if(iter->val == zpow(input))
                                    {
                                        iter->coeff = iter->coeff + coeff(input);
                                        cnt = 1;
                                        break;
                                    }
                                    
                                    if (iter->next != NULL)
                                    {
                                        iter = iter->next;
                                    }
                                    else
                                    {
                                        break;
                                    }
                                    
                                }
                                if (cnt == 0)
                                {
                                    node * temp = new node;
                                    temp->next = NULL;
                                    temp->val = zpow(input);
                                    temp->coeff = coeff(input);
                                    iter->next = temp;
                                    cnt = 1;
                                }
                            }
                            if (cnt == 1)
                            {
                                break;
                            }
                            
                            if (iter->next != NULL)
                            {
                                iter = iter->next;
                            }
                            else
                            {
                                break;
                            }
                            
                        }
                        if (cnt == 0)
                        {
                            node * temp = new node;
                            temp->next = NULL;
                            temp->val = ypow(input);
                            iter->next = temp;
                            
                            node * temp2 = new node;
                            temp2->next = NULL;
                            temp2->val = zpow(input);
                            temp2->coeff = coeff(input);
                            iter->next->down = temp2;
                            cnt = 1;
                        }
                    }
                    if (cnt == 1)
                    {
                        break;
                    }
                    
                    if (iter->next != NULL)
                    {
                        iter = iter->next;
                    }
                    else
                    {
                        break;
                    }
                    
                }
                
                if (cnt == 0)
                {
                    node * temp = new node;
                    temp->next = NULL;
                    temp->val = xpow(input);
                    iter->next = temp;
                    
                    node * temp1 = new node;
                    temp1->next = NULL;
                    temp1->val = ypow(input);
                    iter->next->down = temp1;
                    
                    node * temp2 = new node;
                    temp2->next = NULL;
                    temp2->val = zpow(input);
                    temp2->coeff = coeff(input);
                    iter->next->down->down = temp2;
                    
                    cnt = 1;
                    
                }
            }
            
        }
    }
    
    node * mopper;
    
    mopper = polys.head;
    
    string finals [10000];
    
    int index = 1;
    
    while (mopper != NULL)
    {
        int x = mopper->val;
        node * mopper2 = mopper->down;
        while(mopper2 != NULL)
        {
            int y = mopper2->val;
            node * mopper3 = mopper2->down;
            while (mopper3 != NULL)
            {
                int z = mopper3->val;
                int c = mopper3->coeff;
                
                if (c != 0)
                {
                    finals[index] = codedans(x,y,z,c);
                    
                    index++;
                }
                
                mopper3 = mopper3->next;
                
            }
            
            mopper2 = mopper2->next;	
        }
        
        mopper = mopper->next;
    }
    
    string tempor;
    
    for (int j = 1; j < index; j++)
    {
        for (int t = 1; t < index - 1; t++)
        {
            if (strtonum(finals[t]) > strtonum(finals[t+1]))
            {
                tempor = finals[t];
                finals[t] = finals[t+1];
                finals[t+1] = tempor;
            }
        }
    }
    
    for (int s = 1; s < index; s++)
    {
        printf("%04d",strtonum(finals[s]));
        cout<<endl;
    }
    
}
