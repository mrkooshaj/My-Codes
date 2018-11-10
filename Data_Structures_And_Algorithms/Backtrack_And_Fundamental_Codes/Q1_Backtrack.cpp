#include <iostream>

using namespace std;

int matrix [145][145];

int colors[145];

int checker (int vertex, int color)
{
    for (int j = 1; j < 145; j++)
    {
        if (matrix[vertex][j] == 1 && color == colors[j])
        {
            return 0;
        }
    }
    return 1;
}

int colorer (int number_of_colors, int vertex, int bound)
{
    if (vertex == bound*bound + 1)
    {
        return 1;
    }
    
    for (int colour = 1; colour <= number_of_colors; colour++)
    {
        if(checker(vertex,colour) == 1)
        {
            colors[vertex] = colour;
            if (colorer(number_of_colors, vertex+1, bound) == 1)
            {
                return 1;
            }
            colors[vertex] = 0;
        }
    }
    return 0;
}

int main ()
{
    int street, accident;
    cin>>street>>accident;
    
    int onefirst, onesecond , twofirst , twosecond;
    
    int gedges = (street * street);
    
    for (int i = 1; i < 145; i++)
    {
        for (int j = 1; j < 145; j++)
        {
            matrix[i][j] = 0;
        }
    }
    
    for (int i = 1; i < 145; i++)
    {
        colors[i] = 0;
    }
    
    for (int i = 1; i < accident+1 ; i++)
    {
        cin>>onefirst>>onesecond>>twofirst>>twosecond;
        
        int final1 = ((onefirst - 1) * street + onesecond);
        int final2 = ((twofirst - 1) * street + twosecond);
        
        matrix[final1][final2] = 1;
        matrix[final2][final1] = 1;
    }
    
    int rang = 1;
    
    int ispossible = 1;
    
    int cnt;
    
    
    for (int i = 1; i < gedges+1; i++)
    {
        for (int v = 1; v < rang + 1; v++)
        {
            for (int j = 1; j < i; j++)
            {
                if (colors[j] == v && matrix[i][j] == 1)
                {
                    ispossible = 0;
                }
            }
            if (ispossible == 1)
            {
                colors[i] = v;
                break;
            }
            else
            {
                cnt++;
                ispossible = 1;
            }
        }
        if (cnt == rang)
        {
            colors[i] = rang+1;
            rang++;
        }
        cnt = 0;
    }
    
    for (int i = 1; i < rang+1; i++)
    {
        if (colorer(i,1,street) == 1)
        {
            cout<<i;
            return 0;
        }
    }
    
}
