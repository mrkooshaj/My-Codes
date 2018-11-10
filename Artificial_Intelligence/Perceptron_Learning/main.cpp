#include <iostream>
#define SIZE_OF_INPUT 1010000


using namespace std;

int abss(int a)
{
    if (a > 0)
    {
        return a;
    }
    else
    {
        return -a;
    }
}

int hexadecimal_to_decimal(string s)
{
    int result = 0;
    int multiplier = 1;
    for (int i = s.size() - 1; i > -1 ; i--)
    {
        if (s[i] == '0')
        {
            result = result + (0 * multiplier);
        }
        if (s[i] == '1')
        {
            result = result + (1 * multiplier);
        }
        if (s[i] == '2')
        {
            result = result + (2 * multiplier);
        }
        if (s[i] == '3')
        {
            result = result + (3 * multiplier);
        }
        if (s[i] == '4')
        {
            result = result + (4 * multiplier);
        }
        if (s[i] == '5')
        {
            result = result + (5 * multiplier);
        }
        if (s[i] == '6')
        {
            result = result + (6 * multiplier);
        }
        if (s[i] == '7')
        {
            result = result + (7 * multiplier);
        }
        if (s[i] == '8')
        {
            result = result + (8 * multiplier);
        }
        if (s[i] == '9')
        {
            result = result + (9 * multiplier);
        }
        if (s[i] == 'a')
        {
            result = result + (10 * multiplier);
        }
        if (s[i] == 'b')
        {
            result = result + (11 * multiplier);
        }
        if (s[i] == 'c')
        {
            result = result + (12 * multiplier);
        }
        if (s[i] == 'd')
        {
            result = result + (13 * multiplier);
        }
        if (s[i] == 'e')
        {
            result = result + (14 * multiplier);
        }
        if (s[i] == 'f')
        {
            result = result + (15 * multiplier);
        }
        multiplier = multiplier * 16;
    }
    return result;
}



int main()
{
    int weights[163][25];
    int results[25];
    for (int i = 0; i < 163; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            weights[i][j] = 0;
            results[j] = -1;
        }
    }

    results[0] = 1;

    //string pc[SIZE_OF_INPUT];
    //int branch_result[SIZE_OF_INPUT];

    string* pc = new string[SIZE_OF_INPUT];
    int *branch_result = new int[SIZE_OF_INPUT];

    for(int i = 0; i < SIZE_OF_INPUT; i++)
    {
        cin>>pc[i]>>branch_result[i];
    }

    for (int s = 0; s < 1000000; s++)
    {
        int index = hexadecimal_to_decimal(pc[s]) % 163;
        int sum = 0;
        for (int t = 0; t < 25; t++)
        {
            sum = sum + results[t] * weights[index][t];
        }

        int predicted;

        if (sum >= 0)
        {
            predicted = 1;
        }
        else
        {
            predicted = 0;
        }

        if (predicted != branch_result[s] || abss(sum) < 61)
        {
            for (int v = 0; v < 25; v++)
            {
                if (branch_result[s] == 0)
                {
                    weights[index][v] += -1 * results[v];
                }
                else
                {
                    weights[index][v] += results[v];
                }
            }
        }

        for (int j = 23; j > 0; j--)
        {
            results[j+1] = results[j];
        }

        if (branch_result[s] == 0)
        {
            results[1] = -1;
        }
        else
        {
            results[1] = 1;
        }
    }


    int counter = 0;

    for (int s = 1000000; s < 1010000; s++)
    {
        int index = hexadecimal_to_decimal(pc[s]) % 163;
        int sum = 0;
        for (int t = 0; t < 25; t++)
        {
            sum = sum + results[t] * weights[index][t];
        }

        int predicted;

        if (sum >= 0)
        {
            predicted = 1;
        }
        else
        {
            predicted = 0;
        }

        cout<<predicted<<endl;

        if (predicted == branch_result[s])
        {
            counter++;
        }

        if (predicted != branch_result[s] || abss(sum) < 61)
        {
            for (int v = 0; v < 25; v++)
            {
                if (branch_result[s] == 0)
                {
                    weights[index][v] += -1 * results[v];
                }
                else
                {
                    weights[index][v] += results[v];
                }
            }
        }

        for (int j = 23; j > 0; j--)
        {
            results[j+1] = results[j];
        }

        if (branch_result[s] == 0)
        {
            results[1] = -1;
        }
        else
        {
            results[1] = 1;
        }

    }

    double accuracy = (double)counter / 100.0;

    cout<<"Accuracy: "<<accuracy<<"%"<<endl;
}
