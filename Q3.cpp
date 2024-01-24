#include <iostream>
#include <string>
#include <cmath>   // for log10 and other mathematical functions
#include <utility> // for std::pair

int get_daily_calories(double age, std::string gender, std::string lifestyle)
{
    int cal; //calories 
    

    // Group conditions by age range then gender
    if (age >= 19 && age <= 30)
    {

        if (gender == "male")
        {

            if (lifestyle == "sedentary"){ cal = 2400;}
            else if (lifestyle == " moderate"){ cal = 2700;}
            else {cal = 3000;}
        
        }
        if (gender == "female")
        {

            if (lifestyle == "sedentary")
            {
                cal = 2000;
            }
            else if (lifestyle == " moderate")
            {
                cal = 2100;
            }
            else
            {
                cal = 2400;
            }
        }
    }

    return cal; 
}

int main()
{
    // test cases for function performance
    // auto result = get_bfp(80, 40, 170, 90, "Male", 30);
    auto result = get_bfp(80, 40, 170, 90, "female", 30);
    std::cout << "Body Fat Percentage: " << result.first << "%, Category: " << result.second << std::endl;

    return 0;
}
