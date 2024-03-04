#include <iostream>
#include <string>
#include <limits>
#include <map>
#include <fstream>
#include <sstream>
#include <cmath>


struct UserInfo
{
    std::string gender;
    int age;
    double weight;
    double waist;
    double neck;
    double hip;
    double height;
    std::string lifestyle;
    std::string name; 
    UserInfo* next; 
};

class UserInfoManager {
public:
    UserInfoManager(); //constructor 
    ~UserInfoManager(); // destructor, delete allocated memory

    // This function gets user details from standard input
    void addUserInfo(){

        std::cout << "Please enter your username: \n"; 

        std::cout << "Gender: Please specify your gender, input options: male, female.\n";
        while (true)
        {
            std::getline(std::cin, g_gender);
            if (g_gender == "male" || g_gender == "female")
            {
                break;
            }
            std::cout << "Invalid input. Please specify your gender as male or female: ";
        }

        std::cout << "Age: Enter your age.\n";
        g_age = getValidatedInteger();

        // Check age validity, exit prrogram if age is not within range
        if (g_age < 20 || g_age > 79)
        {
            std::cout << "Sorry, we don't have data for age under 20 or over 79.\n";
            exit(0); // Exit the program
        }

        std::cout << "Weight: Enter your body weight in kilograms.\n";
        g_weight = getValidatedDouble();

        std::cout << "Waist: Input your waist measurement in centimeters.\n";
        g_waist = getValidatedDouble();

        std::cout << "Neck: Provide your neck measurement in centimeters.\n";
        g_neck = getValidatedDouble();

        std::cout << "Height: Input height measurement in centimeters.\n";
        g_height = getValidatedDouble();

        std::cout << "Lifestyle: Provide information about your current lifestyle: sedentary, moderate (moderately active) or active.\n";
        while (true)
        {
            std::getline(std::cin, g_lifestyle);
            if (g_lifestyle == "sedentary" || g_lifestyle == "moderate" || g_lifestyle == "active")
            {
                break;
            }
            std::cout << "Invalid input. Please specify your lifestyle as sedentary, moderate, or active: ";
        }
        if (g_gender == "female") // hip measurement if user is female
        {
            std::cout << "Hip Measurement: Enter your hip measurement in centimeters.\n";
            g_hip = getValidatedDouble();
        }
    };

    void deleteUser(std::string username);
    void readFromFile(std::string filename); //reads and populate list 
    void writeToFile(std::string filename); 
    void display(std::string username); 

private: 
    UserInfo* mylist; // pointer to first element in linked list

    // Function to clear the input buffer
    void clearInputBuffer()
    {
        std::cin.clear();                                                   // Reset any error flags
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore any characters in the input buffer
    };

    // Function to get valid integer input, will keep asking for input until getting valid number
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
    };

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
    };
};


//wrapper methods: getUserDetail, display, serialize, readfromFile, deleteUser 
//Implementations are provided by the UserInfoManager class 
class HealthAssistant {

public:
    // wrapper method that calls addUserInfo in class UserInfoManager
    void getUserDetail(){
        manager.addUserInfo(); 
    };

    void getBfp(std::string username); 
    void getDailyCalories(std::string username){

        int cal = 2400;
        int age;
        std::string gender;
        std::string lifestyle; 


        // Three age ranges, 1,2,3 for each category
        int ageRange = (age >= 19 && age <= 30) ? 0 : (age > 30 && age <= 50) ? 1
                                                    : (age > 50)                ? 2
                                                                                : 0;

        int activity = (lifestyle == "sedentary") ? 0 : (lifestyle == "moderate") ? 1
                                                    : (lifestyle == "active")     ? 2
                                                                                    : 0;

        cal -= 200 * ageRange; // for each age level, subtract 200 cal
        if (gender == "female")
        {
            cal -= 400;            // female threshold 400 less than male threshold
            cal += 200 * activity; // for each activity level, add 200 cal
        }
        else if (gender == "male")
        {
            cal += 300 * activity; // for each activity level, add 300 cal
        }

        
    };


    void getMealPrep(std::string username);
    void display(std::string username); //wrapper method
    void serialize(std::string filename); //wrapper method
    void readFromFile(std::string filename); //wrapper method
    void deleteUser(std::string username); //wrapper method  
private:
    UserInfoManager manager; 

}; 

// Global variables
std::string g_gender;
int g_age;
double g_weight;
double g_waist;
double g_neck;
double g_height;
std::string g_lifestyle;
double g_hip;                          // For female users
std::vector<UserInfo> users;           // For Q7, storing each line in one vector



int main(int argc, char *argv[])
{
    HealthAssistant ha;
    ha.getUserDetail();
};
