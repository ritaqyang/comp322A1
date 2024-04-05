#include <iostream>
using namespace std;
void mult(int x, int& y ){
    y *= x; 
}

float* getPricePointer() {
    float price = 9.99;
    return &price; 
} //price will be automaticlaly destroyed since it's a local var
    //its address will be pointing to invalid memory location 

int main()
    {
        // int *ptr = new int;
        // ptr++;
        // delete ptr;
        // return 0;

        int a = 2, b = 3;
        mult(a, b);
        cout << a << " " << b << endl;

        int value = 100;
        int *pValue = &value;
        cout << "value is equal to " << *pValue << endl;
        cout << "value is " << value << endl;
        cout << "Address is " << pValue << endl;
        cout << "Address is " << &value << endl;

        cout << pValue << endl;

        cout << ++*pValue << endl;
        cout << pValue << endl;

        cout << *++pValue << endl;
        cout << pValue << endl;

        cout << ++pValue << endl;
        cout << pValue << endl;


        

        return 0;
    }