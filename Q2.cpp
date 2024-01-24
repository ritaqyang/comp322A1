#include <iostream>
#include <string>
#include <cmath>   // for log10 and other mathematical functions
#include <utility> // for std::pair


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

    // Determine the associated group
    // need to add more detailed categories for WHO table 

    // Group conditions by age range then gender 
    if (age >= 20 && age <= 39) {

        if (gender  == "female") {

            category = "low";

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
