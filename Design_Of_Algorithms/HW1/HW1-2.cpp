#include <iostream>
#include <vector>

using namespace std;

float abs (float a)
{
    if (a > 0.0)
    {
        return a;
    }
    else
    {
        return -a;
    }
}

int n,k;
int power = 1;

class Vertex
{
public:
    int x;
    int y;
    float shib;
    int start_index;
    int out_num = -1;
};

float shib(int base_x,int base_y,int point_x,int point_y)
{
    int delta_y = point_y - base_y;
    int delta_x = point_x - base_x;
    
    if (delta_x == 0)
    {
        if (base_y > point_y)
        {
            return 2000000001.0;
        }
        else
        {
            return -2000000001.0;
        }
    }
    else
    {
        return (float)delta_y / (float)delta_x;
    }
}

void merge(Vertex input[], int start, int middle, int end,int whichone)
{
    vector <Vertex> temp1, temp2;
    
    for (int i = 0; i < middle - start + 1; i++)
    {
        temp1.push_back(input[start + i]);
    }
    for (int j = 0; j < end - middle; j++)
    {
        temp2.push_back(input[middle + j + 1]);
    }
    
    int temp1_it = 0, temp2_it = 0, final_it = start;
    
    while (temp1_it < middle - start + 1 && temp2_it < end - middle)
    {
        if (whichone == 0)
        {
            if (temp1[temp1_it].x <= temp2[temp2_it].x)
            {
                input[final_it] = temp1[temp1_it];
                temp1_it++;
            }
            else
            {
                input[final_it] = temp2[temp2_it];
                temp2_it++;
            }
            final_it++;
        }
        else if (whichone == 1)
        {
            if (temp1[temp1_it].shib <= temp2[temp2_it].shib)
            {
                input[final_it] = temp1[temp1_it];
                temp1_it++;
            }
            else
            {
                input[final_it] = temp2[temp2_it];
                temp2_it++;
            }
            final_it++;
        }
        else
        {
            if (temp1[temp1_it].start_index <= temp2[temp2_it].start_index)
            {
                input[final_it] = temp1[temp1_it];
                temp1_it++;
            }
            else
            {
                input[final_it] = temp2[temp2_it];
                temp2_it++;
            }
            final_it++;
        }
    }
    
    while (temp1_it < middle - start + 1)
    {
        input[final_it] = temp1[temp1_it];
        temp1_it++;
        final_it++;
    }
    while (temp2_it < end - middle)
    {
        input[final_it] = temp2[temp2_it];
        temp2_it++;
        final_it++;
    }
}

void merge_sort(Vertex input[],int start_index, int end_index, int whichone) //0:x 1:shib 2:startindex)
{
    if (start_index < end_index)
    {
        int middle_index = start_index + (end_index - start_index) / 2;
        merge_sort(input,start_index,middle_index,whichone);
        merge_sort(input,middle_index+1,end_index,whichone);
        merge(input,start_index,middle_index,end_index,whichone);
    }
}

void solve(Vertex input[],int start_index, int end_index, int root_index,int assigned_num)
{
    
    if (assigned_num > power)
    {
        input[root_index].out_num = 0;
    }
    else
    {
        input[root_index].out_num = assigned_num;
    }
    
    if (start_index == end_index)
    {
        return;
    }
    
    if (start_index == end_index - 1)
    {
        if (root_index == start_index)
        {
            solve(input,end_index,end_index,end_index,assigned_num * 2);
        }
        else
        {
            solve(input,start_index,start_index,start_index,assigned_num * 2);
        }
        return;
    }
    
    for (int ss = start_index + 1 ; ss < end_index + 1; ss++)
    {
        input[ss].shib = shib(input[start_index].x,input[start_index].y,input[ss].x,input[ss].y);
    }
    
    merge_sort(input,start_index+1,end_index,1);
    
    int middle_index = (start_index + end_index + 1) / 2;
    
    merge_sort(input,start_index + 1, middle_index,0);
    merge_sort(input,middle_index + 1, end_index,0);
    
    solve(input,start_index+1,middle_index,start_index+1,assigned_num * 2);
    solve(input,middle_index + 1,end_index,middle_index + 1, assigned_num * 2 + 1);
    
}

int main()
{
    
    cin>>n>>k;
    
    for (int j = 0; j < k+1; j++)
    {
        power = power * 2;
    }
    
    power--;
    
    Vertex dots[n];
    
    for (int j = 0; j < n; j++)
    {
        cin>>dots[j].x>>dots[j].y;
        dots[j].start_index = j;
    }
    
    if (power > n)
    {
        cout<<-1<<endl;
        return 0;
    }
    
    merge_sort(dots,0,n-1,0);
    
    solve(dots,0,n-1,0,1);
    
    merge_sort(dots,0,n-1,2);
    
    for (int j = 0; j < n; j++)
    {
        cout<<dots[j].out_num<<endl;
    }
}
