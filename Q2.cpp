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
    //For each age range, use helper function to get category accoring to theresholds
    //Get the thresholds first as variables, so it's more visualy clear for future uses and changes to the data
    //Instead of the strucutre if .... then getcategory(bfp,21,33,39) 

    int lowThreshold, normalThreshold, highThreshold;

    if (gender == "female")
    {
        if (age <= 39)
        { // 20-39 age range
            lowThreshold = 21;
            normalThreshold = 33;
            highThreshold = 39;
        }
        else if (age <= 59)
        { // 40-59 age range
            lowThreshold = 23;
            normalThreshold = 34;
            highThreshold = 40;
        }
        else
        { // 60+ age range
            lowThreshold = 24;
            normalThreshold = 36;
            highThreshold = 42;
        }
    }
    else if (gender == "male")
    {
        if (age <= 39)
        { // 20-39 age range
            lowThreshold = 8;
            normalThreshold = 20;
            highThreshold = 25;
        }
        else if (age <= 59)
        { // 40-59 age range
            lowThreshold = 11;
            normalThreshold = 22;
            highThreshold = 28;
        }
        else
        { // 60+ age range
            lowThreshold = 13;
            normalThreshold = 25;
            highThreshold = 30;
        }
    }

    category = getCategory(bfp, lowThreshold, normalThreshold, highThreshold);

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
