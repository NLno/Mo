#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

vector<int> input;
vector<int> output_goal;
vector<int> output;
vector<int> output_show;

int emptyPlace[3];
int places = 0;
int present;
bool whether_inbox = 1;
bool whether_emptyPlace[3] = {1, 1, 1};
bool whether_present_zero;
string level_complete = "FFFF";

bool exist(int num)
{
    if (num < 0 || num > places - 1)
        return true;
    else
        return false;
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
    output_show.insert(output_show.begin(), present);
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
    whether_inbox = 0;
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

void level_msg(int level)
{
    switch (level)
    {
    case 1:
    {
        output.reserve(2);
        int input_tmp[2] = {1, 2};
        vector<int> in(input_tmp, input_tmp + 2);
        input.swap(in);
        int output_tmp[2] = {1, 2};
        vector<int> out(output_tmp, output_tmp + 2);
        output_goal.swap(out);
        places = 0;
        break;
    }
    case 2:
    {
        output.reserve(8);
        int input_tmp[8] = {3, 9, 5, 1, -2, -2, 9, -9};
        vector<int> in(input_tmp, input_tmp + 8);
        input.swap(in);
        int output_tmp[8] = {-6, 6, 4, -4, 0, 0, 18, -18};
        vector<int> out(output_tmp, output_tmp + 8);
        output_goal.swap(out);
        places = 3;
        break;
    }
    case 3:
    {
        output.reserve(2);
        int input_tmp[8] = {6, 2, 7, 7, -9, 3, -3, -3};
        vector<int> in(input_tmp, input_tmp + 8);
        input.swap(in);
        int output_tmp[2] = {7, -3};
        vector<int> out(output_tmp, output_tmp + 2);
        output_goal.swap(out);
        places = 3;
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
    int numOforder[4] = {2, 8, 8, 2};
    int level;
    cin >> level;
    level_msg(level);
    int number_order;
    cin >> number_order;
    cmd cmd[number_order];
    for (int i = 0; i < number_order; i++)
    {
        cin >> cmd[i].name;
        int cnt = 0;
        for (int j = 0; j < numOforder[level - 1]; j++)
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
            return 0;
        }
    }
    for (int i = 0; i < number_order; i++)
    {
        int msg = cmd[i].func(cmd[i].num);
        if (cmd[i].order == 6)
        {
            if (msg < 1 || msg > number_order)
            {
                cout << "Error on instruction " << i + 1 << endl;
                return 0;
            }
            else
            {
                i = msg - 2;
                continue;
            }
        }
        if (cmd[i].order == 7)
        {
            if (msg < 1 || msg > number_order)
            {
                cout << "Error on instruction " << i + 1 << endl;
                return 0;
            }
            else
            {
                if (whether_present_zero)
                {
                    i = msg - 2;
                }
                else
                    continue;
            }
        }
        if (msg == 404)
        {
            cout << "Error on instruction " << i + 1 << endl;
            return 0;
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
