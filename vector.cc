/*
- Vectors are part of STL. Vectors in C++ are sequence containers representing arrays that can change their size during runtime. 

*/

#include<vector>
#include<iostream>
using namespace std;
int main()
{
    vector<int> vec_int = {123, 456, 789};
   // int* ptr = &vec_int[0];
    //*ptr++ == 123; // is true
    //*ptr++ == 456; // is true
    //*ptr++ == 789; // is true
    
    struct S
    {
        char temp[10];
    };
    vector<S> vec_char = {"yeu","quai"};
    S *ptr = &vec_char[0];
    for (int i = 0; i < 3 ; i++)
    {
        cout << *(ptr + i)->temp << endl;
    }

}
