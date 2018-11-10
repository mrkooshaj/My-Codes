#include <iostream>

#define BASE 761

using namespace std;


int hashltr[2000001];

int hashrtl[2000001];

int basepowers[2000001];

int ceil2 (int n)
{
    return (n+1) / 2;
}

int floor2 (int n)
{
    return n/2;
}

inline int hashleft(int i,int j)
{
    int s1 = hashltr[j];
    int s2 = hashltr[i];
    s2 = s2 * basepowers[j-i];
    return s1 - s2;
}

inline int hashright(int i, int j)
{
    int s1 = hashrtl[i];
    int s2 = hashrtl[j];
    s2 = s2 * basepowers[j-i];
    return s1 - s2;
}

inline int ispalin(int i,int j)
{
    return (hashright(i,j) == hashleft(i,j));
}

inline int ispalince(int center, int end)
{
    return ispalin (center * 2 - end, end);
}

string addstar (string input)
{
    string output = "";
    for (int i = 0; i < input.size(); i++)
    {
        output += "*";
        output += input[i];
    }
    
    output = output + "*";
    return output;
}

int main()
{
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    basepowers[0] = 1;
    for (int j = 1; j < 2000001; j++)
    {
        basepowers[j] = basepowers[j-1] * BASE;
    }
    
    string input;
    getline(cin,input);
    
    int finalsub = input.size() + 1;
    input = addstar(input);
    int length = input.size();
    
    
    for (int i = 0; i < length; i++)
    {
        long long int temp = input[i];
        if (i == 0)
        {
            hashltr[i] = temp;
        }
        else
        {
            hashltr[i] = (hashltr[i-1] * BASE) + temp;
        }
    }
    
    for (int i = length; i >= 0; i--)
    {
        long long int temp = input[i];
        if (i == length)
        {
            hashrtl[i] = temp;
        }
        else
        {
            hashrtl[i] = (hashrtl[i+1]*BASE) + temp;
        }
    }
    
    long long int cnt = 0;
    
    int end;
    for (int center = 0; center < length; center++)
    {
        if (center * 2 >= length)
        {
            end = length;
        }
        else
        {
            end = center * 2;
        }
        int it1 = center;
        int it2 = end + 1;
        while (1 == 1)
        {
            if (it1 == it2)
            {
                break;
            }
            else if (it2 - it1 == 1)
            {
                break;
            }
            else
            {
                int mid = (it1 + it2) / 2;
                if (ispalince(center,mid) == 1)
                {
                    it1 = mid;
                }
                else
                {
                    it2 = mid;
                }
            }
        }
        if (input[center] == '*')
        {
            cnt = cnt + (floor2(it1 - center));
        }
        else
        {
            cnt = cnt + (ceil2(it1-center));
        }
    }
    
    cout<<cnt<<endl;
}
