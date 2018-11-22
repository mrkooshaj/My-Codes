#include <iostream>
#include <vector>

using namespace std;

class Line
{
public:
    
    int startpoint;
    int endpoint;
    char in_out = ',';
    
    Line(int start,int end)
    {
        this->startpoint = start;
        this->endpoint = end;
    }
};

int line_collide(Line in1,Line in2,int n)
{
    int start1 = in1.startpoint;
    int start2 = in2.startpoint;
    int end1 = in1.endpoint;
    int end2 = in2.endpoint;
    
    if ((start1 < start2 && start2 < end1 && end1 < end2) || (start1 < end2 && end2 < end1 && end1 < start2) || (end1 < start2 && start2 < start1 && start1 < end2) || (end1 < end2 && end2 < start1 && start1 < start2) || (start2 < start1 && start1 < end2 && end2 < end1) || (start2 < end1 && end1 < end2 && end2 < start1) || (end2 < start1 && start1 < start2 && start2 < end1) || (end2 < end1 && end1 < start2 && start2 < start1))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main ()
{
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n,m;
    cin>>n>>m;
    
    int strt,nd;
    
    vector <Line> inputs;
    
    for (int i = 0; i < m; i++)
    {
        cin>>strt>>nd;
        Line x = Line(strt,nd);
        inputs.push_back(x);
    }
    
    int bank = 1;
    
    inputs[0].in_out = 'I';
    
    
    int flag = 1;
    
    int prevbank = 0;
    
    while (bank != m)
    {
        if (bank == prevbank)
        {
            for (int i = 0; i < inputs.size(); i++)
            {
                if(inputs[i].in_out == ',')
                {
                    inputs[i].in_out = 'I';
                    bank++;
                    break;
                }
            }
        }
        
        prevbank = bank;
        if (flag == 1) //outsiders
        {
            for (int j = 0; j < inputs.size(); j++)
            {
                if (inputs[j].in_out == 'I')
                {
                    for (int i = 0; i < inputs.size(); i++)
                    {
                        if (inputs[i].in_out == ',')
                        {
                            if (line_collide(inputs[j],inputs[i],n) == 1)
                            {
                                inputs[i].in_out = 'O';
                                bank++;
                            }
                        }
                    }
                }
            }
            flag = 0;
        }
        if (flag == 0)
        {
            for (int j = 0; j < inputs.size(); j++)
            {
                if (inputs[j].in_out == 'O')
                {
                    for (int i = 0; i < inputs.size(); i++)
                    {
                        if(inputs[i].in_out == ',')
                        {
                            if (line_collide(inputs[j],inputs[i],n) == 1)
                            {
                                inputs[i].in_out = 'I';
                                bank++;
                            }
                        }
                    }
                }
            }
            flag = 1;
        }
        
        
    }
    
    for (int i = 0; i < inputs.size(); i++)
    {
        for (int j = 0; j < inputs.size(); j++)
        {
            if (inputs[j].in_out == inputs[i].in_out)
            {
                if (line_collide(inputs[j],inputs[i],n) == 1)
                {
                    cout<<"Impossible"<<endl;
                    return 0;
                }
            }
        }
    }
    
    for (int j = 0; j < inputs.size(); j++)
    {
        cout<<inputs[j].in_out;
    }
    
}
