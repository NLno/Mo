#include <iostream>
using namespace std;

//用栈写输入序列，网上copy
class Stack{
private:
    int* data_;//存放栈中的数据
    int max_size_;//栈最大空间
    int top_;//栈顶
    //初始化栈
    void initStack() {
        data_ = new int[max_size_];//分配栈空间
        top_ = -1;//初始化栈顶
    }
    
public:
    //默认空间为10
    Stack() {
        max_size_ = 10;
        initStack();
    }
    //设置最大空间
    Stack(int max_size) {
        max_size_ = max_size;
        initStack();
    }
    ~Stack() {
        delete data_;
    }
    
    //是否栈空
    int isEmpty() {
        return (top_ == -1)?1:0;
    }
    //是否栈满
    int isFull() {
        return (top_ >= max_size_)?1:0;
    }
    //进栈
    int push(int x) {
        if(isFull())
            return 0;
        else
            data_[++top_] = x;
        return 1;
    }
    //出栈
    int pop(int &x) {
        if(isEmpty())
            return 0;
        else
            x = data_[top_--];
        return 1;
    }
    //清除栈
    void clear(){
        top_ = -1;
    }
};


int main(int argc, char const *argv[]) {

    return 0;
}
