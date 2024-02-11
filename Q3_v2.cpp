#include <iostream>
#include <string>
#include <map>

std::string makeKey(const std::string &gender, const std::string &lifestyle, int ageRange)
{
    return gender + "_" + lifestyle + "_" + std::to_string(ageRange);
}

int get_daily_calories(double age, const std::string &gender, const std::string &lifestyle)
{
    int cal; // calories

    std::map<std::string, int> calorieMap;
    calorieMap[makeKey("male", "sedentary", 1)] = 2400;
    calorieMap[makeKey("male", "moderate", 1)] = 2700;
    calorieMap[makeKey("male", "active", 1)] = 3000;
    calorieMap[makeKey("female", "sedentary", 1)] = 2000;
    calorieMap[makeKey("female", "moderate", 1)] = 2100;
    calorieMap[makeKey("female", "active", 1)] = 2400;
    calorieMap[makeKey("male", "sedentary", 2)] = 2300;
    calorieMap[makeKey("male", "moderate", 2)] = 2600;
    calorieMap[makeKey("male", "active", 2)] = 2900;
    calorieMap[makeKey("female", "sedentary", 2)] = 1900;
    calorieMap[makeKey("female", "moderate", 2)] = 2000;
    calorieMap[makeKey("female", "active", 2)] = 2300;
    calorieMap[makeKey("male", "sedentary", 3)] = 2200;
    calorieMap[makeKey("male", "moderate", 3)] = 2500;
    calorieMap[makeKey("male", "active", 3)] = 2800;
    calorieMap[makeKey("female", "sedentary", 3)] = 1800;
    calorieMap[makeKey("female", "moderate", 3)] = 1900;
    calorieMap[makeKey("female", "active", 3)] = 2200;

    // Identify the age range
    int ageRange = (age >= 19 && age <= 30) ? 1 : (age > 30 && age <= 50) ? 2
                                              : (age > 50)                ? 3
                                                                          : 0;
    std::string key = makeKey(gender, lifestyle, ageRange);
    cal = calorieMap[key];

    return cal;
}
