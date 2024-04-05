#include <iostream>
using namespace std;

class SomeClass{

};



class AirCraft{
    public:
        AirCraft(){
            cout << "Defualt AirCraft constructor" << endl;
        }
        AirCraft(const AirCraft& other){
            cout << "AirCraft copy constructor" << endl;
        }
        AirCraft& operator=(const AirCraft& other){
            cout << "AirCraft copy assignment operator" << endl;
            return *this;
        }

        AirCraft(int i ){
            cout << "AirCraft constructor with paramenters" << endl;
            capacity = i; 
        }
        virtual ~AirCraft(){
            cout << "AirCraft destructor "<< capacity << endl;
        }

        void setCapacity(int i ){capacity = i; }
        virtual void fly() { cout << "AirCraft is flying at: " << capacity << endl; }

    protected:
        int capacity;
}; 


class Boeing: public AirCraft{
    public:
        Boeing(){
            cout << "Default Boeing constructor" << endl;
        }
        Boeing(int i ){
            cout << "Boeing constructor with int" << endl;
            capacity = i;
        }
        ~Boeing(){
            cout << "Boeing destructor" << capacity << endl;
        }
};

class Boeing2 : public AirCraft
{
public:
    Boeing2()
    {
        cout << "Default Boeing2 constructor" << endl;
    }
    Boeing2(int i): AirCraft(i)
    {
        cout << "Boeing2 constructor inheriting from aircraft with int" << endl;
        capacity = i;
    }
    ~Boeing2()
    {
        cout << "Boeing2 destructor" << capacity << endl;
    }
};

int main(){
    SomeClass myClass1; // default constructor 
    SomeClass myClass2 = myClass1; // copy constructor
    SomeClass myClass3(myClass2);   // copy constructor
    SomeClass myClass4; //defualt constructor
    myClass4 = myClass3; // copy assignment operator 

    cout << "================AirCraft================" << endl; 
    AirCraft a;
    a.setCapacity(100);
    a.fly();


    cout<< "================Boeing================"<<endl;
    Boeing b; 
    b.setCapacity(200);
    b.fly();

    cout << "================Boeing ctor with param not inheriting ================" << endl;
    Boeing b2(150);
    b2.fly();
    

    cout << "================Boeing ctor with param inheriting =================" << endl;
    Boeing2 b3(120);
    b3.fly();

    cout << "================before adding virtual keyword to aircraft destructor =================" << endl;
    AirCraft *pt;
    pt = new Boeing(88);
    pt->fly(); 
    delete pt;

    cout<< "================end of everything ================"<<endl;


 
}
