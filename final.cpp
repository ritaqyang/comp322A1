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
    double calories; 
    double carbs;
    double protein;
    double fat; 
    std::string lifestyle;
    std::string name; 
    UserInfo* next; 
};

class UserInfoManager {

public:
    UserInfoManager(){
        mylist = nullptr; 
    }; // constructor 
    ~UserInfoManager(){
        UserInfo* current = mylist; 
        while(current != nullptr){
            UserInfo* next = current->next; 
            delete current; 
            current = next; 
        }
    }; // destructor, delete allocated memory

    //--------------------------------------------------add user info --------------------------------------------------------------------------
    void addUserInfo(){

        UserInfo* newUser = new UserInfo(); // create new userInfo object

        std::cout << "Please enter your username: \n"; 

        std::cout << "Gender: Please specify your gender, input options: male, female.\n";
        while (true)
        {
            std::getline(std::cin, newUser->gender);
            if (newUser->gender == "male" || newUser->gender == "female")
            {
                break;
            }
            std::cout << "Invalid input. Please specify your gender as male or female: ";
        }

        std::cout << "Age: Enter your age.\n";
        newUser->age = getValidatedInteger();

        // Check age validity, exit prrogram if age is not within range
        if (newUser->age < 20 || newUser->age > 79)
        {
            std::cout << "Sorry, we don't have data for age under 20 or over 79.\n";
            exit(0); // Exit the program
        }

        std::cout << "Weight: Enter your body weight in kilograms.\n";
        newUser->weight = getValidatedDouble();

        std::cout << "Waist: Input your waist measurement in centimeters.\n";
        newUser->waist = getValidatedDouble();

        std::cout << "Neck: Provide your neck measurement in centimeters.\n";
        newUser->neck = getValidatedDouble();

        std::cout << "Height: Input height measurement in centimeters.\n";
        newUser->height = getValidatedDouble();

        std::cout << "Lifestyle: Provide information about your current lifestyle: sedentary, moderate (moderately active) or active.\n";
        while (true)
        {
            std::getline(std::cin, newUser->lifestyle);
            if (newUser->lifestyle == "sedentary" || newUser->lifestyle == "moderate" ||newUser->lifestyle == "active")
            {
                break;
            }
            std::cout << "Invalid input. Please specify your lifestyle as sedentary, moderate, or active: ";
        }
        if (newUser->gender == "female") // hip measurement if user is female
        {
            std::cout << "Hip Measurement: Enter your hip measurement in centimeters.\n";
            newUser->hip = getValidatedDouble();
        }
    };

    
    void deleteUser(std::string username)
    {
        UserInfo* current = mylist; 
        UserInfo* prev = nullptr; 
        while(current != nullptr){
            if(current->name == username){
                if(prev == nullptr){
                    mylist = current->next; 
                } else {
                    prev->next = current->next; 
                }
                delete current;
                break;
            }
            prev = current; 
            current = current->next; 
        }
    };

    UserInfo* findUser(std::string username){
        UserInfo* current = mylist; 
        while(current != nullptr){
            if(current->name == username){
                return current; 
            }
            current = current->next; 
        }
        return nullptr;
        
    };
    
    //----------------------------------------------------display user info --------------------------------------------------------------
    void display(std::string username)
    {

        UserInfo *current = mylist;
        while (current != nullptr)
        {
            if (current->name == username)
            {
                std::cout << "User Input Data\n";
                std::cout << "----------------------------------------\n";
                std::cout << "Gender: " << current->gender << "\n";
                std::cout << "Age: " << current->age << " years\n";
                std::cout << "Weight: " << current->weight << " kg\n";
                std::cout << "Waist: " << current->waist << " cm\n";
                std::cout << "Neck: " << current->neck << " cm\n";
                std::cout << "Height: " << current->height << " cm\n";
                std::cout << "Lifestyle: " << current->lifestyle << "\n";
                break;
            }
            current = current->next;
        }
    };
    //-------------------------------------------read from file -----------------------------------------------------------------------------------
    void readFromFile(std::string filename){
        
        std::ifstream file(filename);
        std::string line;

        if (!file.is_open())
        {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        while (getline(file, line))
        {
            std::stringstream lineStream(line);
            std::string cell;
            UserInfo *newNode = new UserInfo(); 

            // CSV columns are ordered as gender, age, weight, waist, neck, hip, height, lifestyle
            // Use try and catch blocks to handle possible exceptions
            getline(lineStream, newNode->gender, ',');
            
            
            //get age 
            getline(lineStream, cell, ',');
            try
            {
                newNode->age = std::stoi(cell);
            }
            catch (const std::exception &e)
            {
                std::cerr << "Conversion error for age: '" << cell << "': " << e.what() << std::endl;
            }

            //get weight
            getline(lineStream, cell, ',');
            try
            {
                newNode->weight = std::stod(cell);
            }
            catch (const std::exception &e)
            {
                std::cerr << "Conversion error for weight: '" << cell << "': " << e.what() << std::endl;
            }


            //get waist 
            getline(lineStream, cell, ',');
            try
            {
                newNode->waist = std::stod(cell);
            }
            catch (const std::exception &e)
            {
                std::cerr << "Conversion error for waist : '" << cell << "': " << e.what() << std::endl;
            }

            //get neck
            getline(lineStream, cell, ',');
            try
            {
                newNode->neck = std::stod(cell);
            }
            catch (const std::exception &e)
            {
                std::cerr << "Conversion error for neck: '" << cell << "': " << e.what() << std::endl;
            }


            //get hip 
            getline(lineStream, cell, ',');
            try
            {
                newNode->hip = std::stod(cell);
            }
            catch (const std::exception &e)
            {
                std::cerr << "Conversion error for hip '" << cell << "': " << e.what() << std::endl;
                newNode->hip = 0; // assign default 0 for male users
            }

            //get height 
            getline(lineStream, cell, ',');
            try
            {
                newNode->height = std::stod(cell);
            }
            catch (const std::exception &e)
            {
                std::cerr << "Conversion error for height: '" << cell << "': " << e.what() << std::endl;
            }

            //get lifestyle 
            getline(lineStream, newNode->lifestyle, ',');

            // add the new node to the end of the linked list 
            newNode->next = nullptr;
            if (mylist == nullptr)
            {
                mylist = newNode;
                tail = newNode;
            }
            else
            {
                tail->next = newNode;
                tail = newNode;
            }
        }

        file.close();
    }; 


//------------------------------------------------------write to file ----------------------------------------------------------------
    void writeToFile(std::string filename)
    {
        std::ofstream file;

        // Open the file in append mode
        file.open(filename, std::ios_base::app);

        if (!file.is_open())
        {
            std::cerr << "Error opening file: " << filename << "\n";
            return;
        }

        UserInfo *current = mylist;
        while (current != nullptr){

            file << current->gender << ", "
                << current->age << ", "
                << current->weight << ", "
                << current->waist << ", "
                << current->neck << ", ";

            // Conditionally add hip measurement for female users
            if (current->gender == "female")
            {
                file << current->hip << ", ";
            }
            else
            {
                file << ", "; // Leave hip empty for male users
            }

            file << current->height << ", "
                << current->lifestyle << "\n";

            current = current->next;
        }

        file.close();
    }; 



    //todo: other stuff to print 


private: 
    UserInfo*  mylist; // pointer to first element in linked list
    UserInfo*  tail; // pointer to last element in linked list

//----------------------------------------------------helper methods for gathering user input ------------------------------------------------
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

    HealthAssistant(){
    }; //constructor
    
    //-----------------------wrapper methods ----------------------------------------------------------------
    

    void getUserDetail(){
        manager.addUserInfo();
    };

    void serialize(std::string filename){
        manager.writeToFile(filename);
    }; //wrapper method

    void display(std::string username){
        manager.display(username);
    }; //wrapper method
    
    
    void deleteUser(std::string username){
        manager.deleteUser(username);
    };


    //------------------------------getBFP ----------------------------------------------------------------

    void getBfp(std::string username){
        UserInfo *user = manager.findUser(username);
        if (user == nullptr)
        {
            std::cout << "User not found\n";
            return;
        }

        std::pair<int, std::string> bfp = get_bfp(user->waist, user->neck, user->height, user->hip,user->gender,user->age); 
    }; 


    //-------------------------get daily calories------------------------------------------------------------

    void getDailyCalories(const std::string username)
    {
        UserInfo *user = manager.findUser(username);
        if (user == nullptr)
        {
            std::cout << "User not found\n";
            return;
        }

        int cal = 2400;                          // Default calorie requirement
        int age = user->age;                     // Extract age from user information
        std::string gender = user->gender;       // Extract gender from user information
        std::string lifestyle = user->lifestyle; // Extract lifestyle from user information

        // Three age ranges, 1, 2, 3 for each category
        int ageRange = (age >= 19 && age <= 30) ? 0 : (age > 30 && age <= 50) ? 1
                                                  : (age > 50)                ? 2
                                                                              : 0;

        int activity = (lifestyle == "sedentary") ? 0 : (lifestyle == "moderate") ? 1
                                                    : (lifestyle == "active")     ? 2
                                                                                  : 0;

        cal -= 200 * ageRange; // For each age level, subtract 200 cal
        if (gender == "female")
        {
            cal -= 400;            // Female threshold 400 less than male threshold
            cal += 200 * activity; // For each activity level, add 200 cal
        }
        else if (gender == "male")
        {
            cal += 300 * activity; // For each activity level, add 300 cal
        }

        user->calories = cal; 

        std::cout << "Daily calorie requirement for " << username << " is: " << cal << " calories\n";

    }


    //------------------------------meal prep --------------------------------------------------------------

    void getMealPrep(std::string username){

        UserInfo *user = manager.findUser(username);
        if (user == nullptr)
        {
            std::cout << "User not found\n";
            return;
        }

        int calories_input = user->calories; // Default calorie requirement
        // Calculate the caloric intake for each macronutrient
        double calories_for_carbs = 0.50 * calories_input;   // 50% of total calories
        double calories_for_protein = 0.30 * calories_input; // 30% of total calories
        double calories_for_fat = 0.20 * calories_input;     // 20% of total calories

        // Convert the caloric intake into grams for each macronutrient
        user->carbs = calories_for_carbs / 4;     // 1 gram of carbs = 4 calories
        user->protein = calories_for_protein / 4; // 1 gram of protein = 4 calories
        user->fat = calories_for_fat / 9;         // 1 gram of fat = 9 calories

    
    };


private:
    UserInfoManager manager; 

    //--------------------------------------------helper methods--------------------------------
    std::pair<int, std::string> get_bfp(double waist, double neck, double height, double hip, std::string gender, int age)
    {
        double bfp;
        std::string category;

        // Calculate BFP based on gender
        if (gender == "male")
        {
            bfp = 495 / (1.0324 - 0.19077 * std::log10(waist - neck) + 0.15456 * std::log10(height)) - 450;
        }
        else
        { // female (inputs were already validated when entering, so only female and male inputs)
            bfp = 495 / (1.29579 - 0.35004 * std::log10(waist + hip - neck) + 0.22100 * std::log10(height)) - 450;
        }
        // For each age range, use helper function to get category according to threshholds

        // Get the thresholds first as variables, so it's more visualy clear for future uses and changes to the data

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
        else
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
    // Helper funtion to get category for BFP thresholds
    std::string getCategory(double bfp, int lowThreshold, int normalThreshold, int highThreshold)
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

        return "undefined";
    }
};

int main()
{
    HealthAssistant ha;
    ha.getUserDetail();
}; 
