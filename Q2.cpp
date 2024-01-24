#include <iostream>
#include <string>
#include <cmath>   // for log10 and other mathematical functions
#include <utility> // for std::pair

//Helper funtion to get category 
std::string getCategory( int bfp, int lowThreshold, int normalThreshold, int highThreshold)
{

    if (bfp < lowThreshold)
    {
        return "low";
    }
    else if (bfp < normalThreshold)
    {
        return "normal";
    }
    else if (bfp < highThreshold)
    {
        return "high";
    }

    return "undefined"; // Fallback return statement if none of the conditions are met
}

std::pair<int, std::string> get_bfp(double waist, double neck, double height, double hip, std::string gender, int age)
{
    double bfp;
    std::string category;

    // Calculate BFP based on gender
    if (gender == "male")
    {
        bfp = 495 / (1.0324 - 0.19077 * std::log10(waist - neck) + 0.15456 * std::log10(height)) - 450;
    }
    else if (gender == "female")
    {
        bfp = 495 / (1.29579 - 0.35004 * std::log10(waist + hip - neck) + 0.22100 * std::log10(height)) - 450;
    }
    else
    {
        return std::make_pair(-1, "Invalid gender");
    }

    std::string category;
    //for each age range, use helper function to get category accoring to theresholds


    if (gender == "female"){
        if (age >= 20 && age <= 39){
            category = getCategory(bfp, 21, 33, 39); 
        }
        else if (age <= 59) {
            //no need for lower bound since we don't get input under 20
            category = getCategory(bfp, 23, 34, 40);
        }
        else {
            category = getCategory(bfp, 24, 36, 42);
        }
    }
    else if (gender == "male")
    {
        if (age >= 20 && age <= 39)
        {
            category = getCategory(bfp, 8, 20, 25);
        }
        else if (age <= 59)
        {
            // no need for lower bound since we don't get input under 20
            category = getCategory(bfp, 11, 22, 28);
        }
        else
        {
            category = getCategory(bfp, 13, 25, 30);
        }
    }

    return std::make_pair(static_cast<int>(bfp), category);
}

int main()
{
    // test cases for function performance 
    // auto result = get_bfp(80, 40, 170, 90, "Male", 30);
    auto result = get_bfp(80, 40, 170, 90, "female", 30);
    std::cout << "Body Fat Percentage: " << result.first << "%, Category: " << result.second << std::endl;

    return 0;
}
