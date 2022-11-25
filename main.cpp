#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

vector<int> input;
vector<int> output_goal;
vector<int> output;

int emptyPlace[4];
int places = 0;
int present;

int inbox(int num = 0)
{
    present = input[0];
    return 0;
}

int outbox(int num = 0)
{
    output.push_back(present);
    return 0;
}

int add(int num)
{
    present += emptyPlace[num - 1];
    return 0;
}

int sub(int num)
{
    present -= emptyPlace[num - 1];
    return 0;
}

int copyto(int num)
{
    emptyPlace[num - 1] = present;
    return 0;
}

int copyfrom(int num)
{
    present = emptyPlace[num - 1];
    return 0;
}

int jump(int num)
{
    return num;
}

int jumpifzero(int num)
{
    if (present == 0)
        return num;
    return 0;
}

char begin()
{
    ifstream level("level.txt");
    bool level_complete[4];
    for (int i = 0; i < 4; i++)
    {
        level >> level_complete[i];
    }
    cout << "please press number 0 - 3 to choose level which you want to try: " << endl;
    char level_choose;
    cin >> level_choose;
    while (level_choose < '1' && level_choose > '4')
    {
        cout << "Only number 0 - 3 is allowed, please reinput a number belong to number 0 - 3." << endl;
    }
    return level_choose;
}

void show_level_msg(char level)
{
    ifstream level_msg("level_msg.txt");
    while (!level_msg.eof())
    {
        string tmp;
        getline(level_msg, tmp);
        if (tmp[0] == level)
        {
            getline(level_msg, tmp);
            cout << tmp << endl;
            for (int i = 0; i < tmp.length(); i++)
            {
                if (isdigit(tmp[i]))
                    input.push_back(tmp[i] - '0');
            }
            getline(level_msg, tmp);
            cout << tmp << endl;
            for (int i = 0; i < tmp.length(); i++)
            {
                if (isdigit(tmp[i]))
                    output_goal.push_back(tmp[i] - '0');
            }
            getline(level_msg, tmp);
            cout << tmp << endl;
            places = tmp[7] - '0';
            getline(level_msg, tmp);
            cout << tmp << endl;
            break;
        }
    }
}

struct cmd
{
    string name;
    int num;
    int order;
    int (*func)(int);
};

int main()
{
    int (*func[8])(int) = {inbox, outbox, add, sub, copyto, copyfrom, jump, jumpifzero};
    string name[8] = {"inbox", "outbox", "add", "sub", "copyto", "copyfrom", "jump", "jumpifzero"};
    int numOforder[4] = {2, 8, 8, 2}; // the order you can use.
    char level = begin();
    show_level_msg(level);
    int number_order; // the number of order user uses.
    cin >> number_order;
    cmd cmd[number_order];
    for (int i = 0; i < number_order; i++)
    {
        cin >> cmd[i].name;
        int cnt = 0;
        for (int j = 0; j < numOforder[level]; j++)
        {
            if (cmd[i].name == name[j])
            {
                cmd[i].order = j;
                cmd[i].func = func[j];
                cnt = 1;
                if (j > 1)
                    cin >> cmd[i].num;
                else
                    cmd[i].num = 0;
                break;
            }
        }
        if (cnt == 0)
            cout << "Error on instruction " << i << endl;
    }
    for (int i = 0; i < number_order; i++)
    {
        int msg = cmd[i].func(cmd[i].num);
        if (cmd[i].order == 6 || cmd[i].order == 7)
            i = msg;
    }
    if (output == output_goal)
    {
        cout << "Success" << endl;
    }
    else
    {
        cout << "Fail" << endl;
    }
    return 0;
}
