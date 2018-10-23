#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int vecsum (vector<int> input)
{
    int result = 0;
    for (int j = 0; j < input.size(); j++)
    {
        result = result + input[j];
    }

    return result;
}

void vecdisp(vector <int> input)
{
    for (int j = 0; j < input.size(); j++)
    {
        cout<<input[j]<<",";
    }
    cout<<endl;
}



class node
{
public:
    int g;

    vector <int> soldiers;
    vector <int> money;

    node(int g, vector<int> soldiers, vector<int> money)
    {
        this->g = g;
        this->soldiers = soldiers;
        this->money = money;
    }


    int h()
    {
        int sum = 0;
        for (int ss = 0; ss < soldiers.size(); ss++)
        {
            if(soldiers[ss] > 0)
            {
                sum += soldiers[ss];
            }
        }
        return sum;
    }

    vector <node> childs()
    {
        vector <node> result;

        int j;

        for (j = 0; j < this->soldiers.size(); j++)
        {
            if (this->soldiers[j] > 0)
            {
                break;
            }
        }

        for (int t = 0; t < this->money.size(); t++)
        {
            if (this->money[t] > 0)
            {
                vector <int> tmpsol;
                vector <int> tmpmon;
                int tempg = this->g;
                for (int i = 0; i < this->soldiers.size(); i++)
                {
                    tmpsol.push_back(this->soldiers[i]);
                }
                for (int ii = 0; ii < this->money.size(); ii++)
                {
                    tmpmon.push_back(this->money[ii]);
                }
                tmpsol[j] = this->soldiers[j] - this->money[t];
                tmpmon[t] = 0;
                tempg += this->money[t];
                node newnd(tempg,tmpsol,tmpmon);
                result.push_back(newnd);
            }
        }

        return result;
    }


};

int find (vector <node> input, node s)
{
    for (int j = 0; j < input.size(); j++)
    {
        if (input[j].g == s.g && input[j].soldiers == s.soldiers && input[j].money == s.money)
        {
            return 1;
        }
    }
    return 0;
}

int main ()
{
    vector <int> money;
    vector <int> soldiers;


    string s,t;
    int digit;
    int bank;

    ifstream moneyfile;
    moneyfile.open("money.txt");

    getline(moneyfile,s);

    bank = 0;

    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == ',')
        {
            money.push_back(bank);
            bank = 0;
        }
        else if (s[i] >= '0' && s[i] <= '9')
        {
            digit = s[i] - '0';
            bank = bank * 10 + digit;
            if (i == s.size() - 1)
            {
                money.push_back(bank);
            }
        }
    }

    ifstream soldiersfile;
    soldiersfile.open("soldiers.txt");

    getline(soldiersfile,t);

    bank = 0;

    for (int i = 0; i < t.size(); i++)
    {
        if (t[i] == ',')
        {
            soldiers.push_back(bank);
            bank = 0;
        }
        else if (t[i] >= '0' && t[i] <= '9')
        {
            digit = t[i] - '0';
            bank = bank * 10 + digit;
            if (i == t.size() - 1)
            {
                soldiers.push_back(bank);

            }
        }
    }

    for (int j = 0; j < money.size(); j++)
    {
        for (int i = 0; i < money.size() - 1; i++)
        {
            if (money[i] > money[i+1])
            {
                int temp = money[i+1];
                money[i+1] = money[i];
                money[i] = temp;
            }
        }
    }

    for (int j = 0; j < soldiers.size(); j++)
    {
        for (int i = 0; i < soldiers.size() - 1; i++)
        {
            if (soldiers[i] > soldiers[i+1])
            {
                int temp = soldiers[i+1];
                soldiers[i+1] = soldiers[i];
                soldiers[i] = temp;
            }
        }
    }

    vector <node> frontier;
    vector <node> explored;

    int firstmoney = vecsum(money);
    int firstsold = vecsum(soldiers);

    node startstate(0,soldiers,money);

    frontier.push_back(startstate);

    while (frontier.size() > 0)
    {
        //Choosing best node to expand

        int min = frontier[0].h() + frontier[0].g;
        int index = 0;
        for (int j = 1; j < frontier.size(); j++)
        {
            if (frontier[j].h() + frontier[j].g < min)
            {
                index = j;
                min = frontier[j].h() + frontier[j].g;
            }
        }

        //vecdisp(frontier[index].soldiers);

        //Expand

        if (frontier[index].h() > (vecsum(frontier[index].money)))
        {
            break;
        }

        if (frontier[index].h() == 0)
        {
            cout<<"We Can Do it with "<<frontier[index].g<<" Money. It's "<<frontier[index].g - vecsum(soldiers)<<" Extra!"<<endl;
            cout<<"Money Bags Not Used : ";

            for (int s = 0; s < frontier[index].money.size(); s++)
            {
                if (frontier[index].money[s] > 0)
                {
                    cout<<frontier[index].money[s]<<" ";
                }
            }
            return 0;
        }

        if (find(explored,frontier[index]) == 0)
        {
            vector <node> temp = frontier[index].childs();

            explored.push_back(frontier[index]);

            for (int s = 0; s < temp.size(); s++)
            {
                frontier.push_back(temp[s]);
            }

            frontier.erase(frontier.begin() + index);
            //cout<<frontier.size()<<endl;
        }
        else
        {
            frontier.erase(frontier.begin() + index);
        }




    }

    cout<<"We Can't Pay Soldiers!"<<endl;
    return 0;
}
