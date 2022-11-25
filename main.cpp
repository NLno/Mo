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
bool whether_inbox = 1;
bool whether_emptyPlace[4] = {1, 1, 1, 1};
bool whether_present_zero;

bool exist(int num)
{
    if (num < 0 || num > places - 1)
        return false;
    else
        return true;
}

int inbox(int num = 0)
{
    if (input.size() == 0)
        return 100;
    present = input[0];
    input.erase(input.begin());
    whether_inbox = 0;
    return 0;
}

int outbox(int num = 0)
{
    if (whether_inbox)
        return 404;
    output.push_back(present);
    whether_inbox = 1;
    return 0;
}

int add(int num)
{
    if (whether_inbox || exist(num) || whether_emptyPlace[num])
        return 404;
    present += emptyPlace[num];
    return 0;
}

int sub(int num)
{
    if (whether_inbox || exist(num) || whether_emptyPlace[num])
        return 404;
    present -= emptyPlace[num];
    return 0;
}

int copyto(int num)
{
    if (whether_inbox || exist(num))
        return 404;
    emptyPlace[num] = present;
    whether_emptyPlace[num] = 0;
    return 0;
}

int copyfrom(int num)
{
    if (exist(num) || whether_emptyPlace[num])
        return 404;
    present = emptyPlace[num];
    return 0;
}

int jump(int num)
{
    return num;
}

int jumpifzero(int num)
{
    if (whether_inbox)
        return 404;
    if (present == 0)
    {
        whether_present_zero = 1;
        return num;
    }
    else
    {
        whether_present_zero = 0;
        return num;
    }
}

char begin()
{
    ifstream level("level.txt");
    bool level_complete[4];
    for (int i = 0; i < 4; i++)
    {
        level >> level_complete[i];
    }
    cout << "please press number 1 - 4 to choose level which you want to try: " << endl;
    char level_choose;
    cin >> level_choose;
    while (level_choose < '1' && level_choose > '4')
    {
        cout << "Only number 1 - 4 is allowed, please reinput a number belong to number 1 - 4." << endl;
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
        if (tmp[0] == level - 1)
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
        {
            cout << "Error on instruction " << i + 1 << endl;
            break;
        }
    }
    for (int i = 0; i < number_order; i++)
    {
        int msg = cmd[i].func(cmd[i].num);
        if (cmd[i].order == 6)
        {
            if (msg < 0 || msg > number_order - 1)
            {
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            else
                i = msg - 1;
        }
        if (cmd[i].order == 7)
        {
            if (msg < -1 || msg > number_order - 1)
            {
                cout << "Error on instruction " << i + 1 << endl;
                break;
            }
            else
            {
                if (whether_present_zero)
                    i = msg - 1;
                else
                    continue;
            }
        }
        if (msg == 404)
        {
            cout << "Error on instruction " << i + 1 << endl;
            break;
        }
        else if (msg == 100)
        {
            break;
        }
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
