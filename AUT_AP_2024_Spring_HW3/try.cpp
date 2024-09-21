#include <iostream>
#include <memory>
using namespace std;
int main()
{
    // 裸指针指向堆上的对象
    int *p = new int;       
    shared_ptr<int> ptr1(p);
    shared_ptr<int> ptr2(p);
    //两次打印都是2，析构一次，正确
    cout << "use_count = " <<  ptr1.use_count() << endl;
    cout << "use_count = " << ptr2.use_count() << endl;
   // getchar();
    return 0;
}