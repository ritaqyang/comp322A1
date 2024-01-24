#include <iostream>
#include <string>

// Global variables
std::string gender;
int age;
double weight;
double waist;
double neck;
double height;
std::string lifestyle;
double hip; // For female users

void getUserDetails()
{
    // Prompt for gender
    std::cout << "Gender: Please specify your gender, input options: male, female.\n";
    std::cin >> gender;

    // Prompt for age
    std::cout << "Age: Enter your age.\n";
    std::cin >> age;

    // Prompt for weight
    std::cout << "Weight: Enter your body weight in kilograms.\n";
    std::cin >> weight;

    // Prompt for waist measurement
    std::cout << "Waist: Input your waist measurement in centimeters.\n";
    std::cin >> waist;

    // Prompt for neck measurement
    std::cout << "Neck: Provide your neck measurement in centimeters.\n";
    std::cin >> neck;

    // Prompt for height
    std::cout << "Height: Input height measurement in centimeters.\n";
    std::cin >> height;

    // Prompt for lifestyle
    std::cout << "Lifestyle: Provide information about your current lifestyle: sedentary, moderate (moderately active) or active.\n";
    std::cin.ignore(); // To clear the newline character from the buffer
    std::getline(std::cin, lifestyle);

    // Additional prompt for female users
    if (gender == "female")
    {
        std::cout << "Hip Measurement: Enter your hip measurement in centimeters.\n";
        std::cin >> hip;
    }
}

int main()
{
    // Call the function to get user details
    getUserDetails();
    return 0;
}
