#include <iostream>
using namespace std;

double getRatio(double a, double b){
    if (b == 0 ){
        throw "warning: division by zero"; 
    }
    return a / b; 
}

double getRatioStringWarning(double a, double b)
{
    if (b == 0)
    {
        string msg = "warning: division by zero";
        throw msg; 
    }
    return a / b;
}

class ZeroException : public exception{
    virtual const char* what() const throw(){
        return "warning: division by zero";
    }
}; 

ZeroException divideByZeroException;

class SomeOtherException : public exception{
    virtual const char* what() const throw(){
        return "Some other exception";
    }
};

SomeOtherException someOtherException; 

double getRatioException(double a, double b){
    if (b == 0){
        throw divideByZeroException; 
    }
    return a / b; 
}

int main()
{
    //default implementation
    try {
        cout << "The ratio is " << getRatio(5, 0) << endl;
    } catch (const char* msg){
        cout << msg << endl;
    }

    //using string message 
    try {
        cout << "The ratio is " << getRatioStringWarning(5, 0) << endl;
    } catch (string msg){
        cout << msg << endl;
    }

    //using exception 
    try {
        cout << "The ratio is " << getRatioException(5, 0) << endl;
    } catch (exception& e){
        cout << e.what() << endl;
    }

    //nested try blocks 
    cout << "--------------------------------nested try blocks-------------" << endl;
    try{
        try{
            getRatioException(5, 0);
        }
        catch (exception& e) {
            cout << e.what() << endl;
            cout << "Inner catch: " << endl;
            throw someOtherException; 
        }

    } catch(exception& e) {
        cout << "Outer catch: " << e.what() << endl;
    }

    // nested try blocks2
    cout << "--------------------------------nested try blocks 2-------------" << endl;
    try
    {
        try
        {
            getRatioException(5, 40);
        }
        catch (exception &e)
        {
            cout << e.what() << endl;
            cout << "Inner catch: " << endl;
            
        }
    }
    catch (exception &e)
    {
        cout << "Outer catch: " << e.what() << endl;
        throw divideByZeroException; 
    }

    // nested try blocks3 
    cout << "--------------------------------nested try blocks 3-------------" << endl;
    try
    {
        try
        {
            getRatioException(5, 0);
        }
        catch (exception &e)
        {
            
            cout << "Inner catch: " << e.what() << endl;
            throw divideByZeroException; 
        }
    }
    catch (exception &e)
    {
        cout << "Outer catch: " << e.what() << endl;
        throw divideByZeroException; 
//         Inner catch: warning: division by zero
// Outer catch: warning: division by zero
// libc++abi: terminating due to uncaught exception of type ZeroException: warning: division by zero
// zsh: abort      ./exceptions
    }
}