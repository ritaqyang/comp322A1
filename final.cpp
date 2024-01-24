#include <iostream>
#include <string>
#include <limits>

// Global variables
std::string gender;
int age;
double weight;
double waist;
double neck;
double height;
std::string lifestyle;
double hip; // For female users


// Function to clear the input buffer

void clearInputBuffer()
{
    std::cin.clear();                                                   // Reset any error flags
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore any characters in the input buffer
}

// Function to get validated integer input
int getValidatedInteger()
{
    int value;
    while (!(std::cin >> value))
    {
        std::cout << "Invalid input. Please enter a valid number: ";
        clearInputBuffer();
    }
    clearInputBuffer();
    return value;
}

// Function to get validated double input
double getValidatedDouble()
{
    double value;
    while (!(std::cin >> value))
    {
        std::cout << "Invalid input. Please enter a valid number: ";
        clearInputBuffer();
    }
    clearInputBuffer();
    return value;
}


void getUserDetails()
{
    // Prompt for gender
    std::cout << "Gender: Please specify your gender, input options: male, female.\n";
    while (true)
    {
        std::getline(std::cin, gender);
        if (gender == "male" || gender == "female")
        {
            break;
        }
        std::cout << "Invalid input. Please specify your gender as male or female: ";
    }

    // Prompt for age
    std::cout << "Age: Enter your age.\n";
    age = getValidatedInteger();

    // Check age validity
    if (age < 20 || age > 79)
    {
        std::cout << "Sorry, we don't have data for age under 20 or over 79.\n";
        exit(0); // Exit the program
    }

    // Prompt for weight
    std::cout << "Weight: Enter your body weight in kilograms.\n";
    weight = getValidatedDouble();

    // Prompt for waist measurement
    std::cout << "Waist: Input your waist measurement in centimeters.\n";
    waist = getValidatedDouble();

    // Prompt for neck measurement
    std::cout << "Neck: Provide your neck measurement in centimeters.\n";
    neck = getValidatedDouble();

    // Prompt for height
    std::cout << "Height: Input height measurement in centimeters.\n";
    height = getValidatedDouble();

    // Prompt for lifestyle
    std::cout << "Lifestyle: Provide information about your current lifestyle: sedentary, moderate (moderately active) or active.\n";
    while (true)
    {
        std::getline(std::cin, lifestyle);
        if (lifestyle == "sedentary" || lifestyle == "moderate" || lifestyle == "active")
        {
            break;
        }
        std::cout << "Invalid input. Please specify your lifestyle as sedentary, moderate, or active: ";
    }

    // Additional prompt for female users
    if (gender == "female")
    {
        std::cout << "Hip Measurement: Enter your hip measurement in centimeters.\n";
        hip = getValidatedDouble();
    }
}





int main()
{
    // Call the function to get user details
    getUserDetails();
    return 0;
}
