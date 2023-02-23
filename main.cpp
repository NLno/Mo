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

int (*func[8])(int) = {inbox, outbox, add, sub, copyto, copyfrom, jump, jumpifzero};
string name[8] = {"inbox", "outbox", "add", "sub", "copyto", "copyfrom", "jump", "jumpifzero"};
int numOforder[4] = {2, 8, 8, 8}; // the order you can use.

int begin()
{
    ifstream level("level.txt");
    for (int i = 0; i < 4; i++)
    {
        level >> level_complete[i];
    }
    level.close();
    cout << "      press number 1 - 4 to choose level which you want to try " << endl;
    cout << "                       F for fail, W for win" << endl;
    cout << "       +---+           +---+           +---+           +---+" << endl;
    cout << "       | " << level_complete[0] << " |           | " << level_complete[1] << " |           | " << level_complete[2] << " |           | " << level_complete[3] << " |" << endl;
    cout << "       +---+           +---+           +---+           +---+" << endl;
    cout << "         1               2               3               4" << endl;
    string level_choose;
    cin >> level_choose;
    while (level_choose[0] < '1' || level_choose[0] > '4' || level_choose.size() > 1)
    {
        cout << "Only number 1 - 4 is allowed, please reinput a number belong to number 1 - 4." << endl;
        cin >> level_choose;
    }
    return level_choose[0] - '0';
}

void show_level_msg(int level)
{
    switch (level)
    {
    case 1:
    {
        cout << "input: 1 2" << endl;
        cout << "output: 1 2" << endl;
        cout << "place: 0" << endl;
        cout << "order: inbox outbox" << endl;
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
        cout << "input: 3 9 5 1 -2 -2 9 -9" << endl;
        cout << "output: -6 6 4 -4 0 0 18 -18" << endl;
        cout << "place: 3" << endl;
        cout << "order: inbox outbox copyfrom copyto add sub jump jumpifzero" << endl;
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
        cout << "input: 6 2 7 7 -9 3 -3 -3" << endl;
        cout << "output: 7 -3" << endl;
        cout << "place: 3" << endl;
        cout << "order: inbox outbox copyfrom copyto add sub jump jumpifzero" << endl;
        output.reserve(8);
        int input_tmp[8] = {6, 2, 7, 7, -9, 3, -3, -3};
        vector<int> in(input_tmp, input_tmp + 8);
        input.swap(in);
        int output_tmp[2] = {7, -3};
        vector<int> out(output_tmp, output_tmp + 2);
        output_goal.swap(out);
        places = 3;
        break;
    }
    case 4:
    {
        cout << "input: 1 -3 2 0" << endl;
        cout << "output: 8 -24 16 0" << endl;
        cout << "place: 3" << endl;
        cout << "order: inbox outbox copyfrom copyto add sub jump jumpifzero" << endl;
        output.reserve(4);
        int input_tmp[4] = {1, -3, 2, 0};
        vector<int> in(input_tmp, input_tmp + 4);
        input.swap(in);
        int output_tmp[4] = {8, -24, 16, 0};
        vector<int> out(output_tmp, output_tmp + 4);
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

void show_end(cmd cmd[], int i, int b)
{
    if (i < b)
    {
        cout << i + 1 << " " << cmd[i].name;
        if (cmd[i].name != "inbox" && cmd[i].name != "outbox")
            cout << " " << cmd[i].num;
        cout << endl;
    }
    else
        cout << endl;
}

void show_input(int i)
{
    if (input.size() > i)
    {
        if (input[i] > -1 && input[i] < 10)
            cout << " " << input[i];
        else
            cout << input[i];
    }
    else
        cout << "  ";
}

void show_output(int i)
{
    if (output_show.size() > i)
    {
        if (output_show[i] > -1 && output_show[i] < 10)
            cout << " " << output_show[i] << " ";
        else if (output_show[i] < -9)
            cout << output_show[i];
        else
            cout << output_show[i] << " ";
    }
    else
        cout << "   ";
}

void show_empty(int i)
{
    if (!whether_emptyPlace[i])
    {
        if (emptyPlace[i] > -1 && emptyPlace[i] < 10)
            cout << " " << emptyPlace[i];
        else
            cout << emptyPlace[i];
    }
    else
        cout << "  ";
}

void show_present()
{
    if (!whether_inbox)
    {
        if (present > -1 && present < 10)
            cout << " " << present << " ";
        else if (present < -9)
            cout << present;
        else
            cout << present << " ";
    }
    else
    {
        cout << "   ";
    }
}

void show_level(cmd cmd[], int i, int b)
{
    cout << "     +---+           +---+           +---+       | ===== CODE ====" << endl;
    cout << "IN   |";
    show_input(0);
    cout << " |           |";
    show_present();
    cout << "|           |";
    show_output(0);
    cout << "|  OUT  |   ";
    show_end(cmd, i, b);
    cout << "     +---+           +---+           +---+       |   ";
    show_end(cmd, i + 1, b);
    cout << "     +---+           @   @           +---+       |   ";
    show_end(cmd, i + 2, b);
    cout << "     |";
    show_input(1);
    cout << " |           -----           |";
    show_output(1);
    cout << "|       |   ";
    show_end(cmd, i + 3, b);
    cout << "     +---+           |@ @|           +---+       |   ";
    show_end(cmd, i + 4, b);
    cout << "     +---+             +             +---+       |   ";
    show_end(cmd, i + 5, b);
    cout << "     |";
    show_input(2);
    cout << " |           /   \\           |";
    show_output(2);
    cout << "|       |   ";
    show_end(cmd, i + 6, b);
    cout << "     +---+            | |            +---+       |   ";
    show_end(cmd, i + 7, b);
    cout << "     +---+                           +---+       |   ";
    show_end(cmd, i + 8, b);
    cout << "     |";
    show_input(3);
    cout << " |   +---+   +---+   +---+   |";
    show_output(3);
    cout << "|       |   " << endl;
    cout << "     +---+   |";
    show_empty(0);
    cout << " |   |";
    show_empty(1);
    cout << " |   |";
    show_empty(2);
    cout << " |   +---+       |   " << endl;
    cout << "             +---+   +---+   +---+" << endl;
    cout << "               0       1       2" << endl;
    cout << endl;
}

void menu()
{
	output_show.clear();
    input.clear();
    output_goal.clear();
    output.clear();

    present = NULL;
    for(int i=0; i<3; i++)
    {
        whether_emptyPlace[i] = 1;
        emptyPlace[i] = NULL;
    }
    whether_inbox = 1;
    
	cout<<endl;
    int level = begin();
    if(level != 1 && level_complete[level-2] != 'W')
    {
    	cout<<"The level is unlocked. Please pass the previous one."<<endl;
    	menu();
	}
    show_level_msg(level);
    int number_order; // the number of order user uses.
    cout << "input the total number of the order you want to use (no more than 15)" << endl;
    string num_choose;
    cin >> num_choose;
    while ((num_choose.size() == 1 && (num_choose[0] < '1' || num_choose[0] > '9')) || (num_choose.size() == 2 && (num_choose[1] < '0' || num_choose[1] > '5' || num_choose[0] > '1')) || num_choose.size() > 2)
    {
        cout << "Only number 1 - 15 is allowed, please reinput a number." << endl;
        cin >> num_choose;
    }
    number_order = stoi(num_choose.c_str());
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
            menu();
        }
    }
    show_level(cmd, 0, number_order);
    for (int i = 0; i < number_order; i++)
    {
        int msg = cmd[i].func(cmd[i].num);
        if (cmd[i].order == 6)
        {
            if (msg < 1 || msg > number_order)
            {
                cout << "Error on instruction " << i + 1 << endl;
                menu();
            }
            else
            {
                i = msg - 2;
                show_level(cmd, i + 1, number_order);
                continue;
            }
        }
        if (cmd[i].order == 7)
        {
            if (msg < 1 || msg > number_order)
            {
                cout << "Error on instruction " << i + 1 << endl;
                show_level(cmd, i + 1, number_order);
                menu();
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
            menu();
        }
        else if (msg == 100)
        {
            break;
        }
        show_level(cmd, i + 1, number_order);
    }
    if (output == output_goal)
    {
        cout << "Success" << endl;
        level_complete[level - 1] = 'W';
        ofstream level("level.txt");
        for (int i = 0; i < 4; i++)
        {
            level << level_complete[i];
        }
        level.close();
    }
    else
    {
        cout << "Fail" << endl;
    }
    menu();
}

int main()
{
	menu();
    return 0;
}
