#include <iostream>
#include <string>
#include <cmath>   // for log10 and other mathematical functions
#include <utility> // for std::pair

std::pair<int, std::string> get_bfp(double waist, double neck, double height, double hip, std::string gender, int age)
{
    double bfp;
    std::string category;

    // Calculate BFP based on gender
    if (gender == "male" || gender == "Male")
    {
        bfp = 495 / (1.0324 - 0.19077 * std::log10(waist - neck) + 0.15456 * std::log10(height)) - 450;
    }
    else if (gender == "female" || gender == "Female")
    {
        bfp = 495 / (1.29579 - 0.35004 * std::log10(waist + hip - neck) + 0.22100 * std::log10(height)) - 450;
    }
    else
    {
        return std::make_pair(-1, "Invalid gender");
    }

    // Determine the associated group


    if (gender == "")
    {
        category = "low";
    }
    else if (bfp >= 18.5 && bfp < 24.9)
    {
        category = "normal";
    }
    else if (bfp >= 25 && bfp < 29.9)
    {
        category = "high";
    }
    else
    {
        category = "very high";
    }

    return std::make_pair(static_cast<int>(bfp), category);
}

int main()
{
    // Example usage
    auto result = get_bfp(80, 40, 170, 90, "Male", 30);
    std::cout << "Body Fat Percentage: " << result.first << "%, Category: " << result.second << std::endl;

    return 0;
}
