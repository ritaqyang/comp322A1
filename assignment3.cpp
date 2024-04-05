#include <iostream>
#include <string>
#include <limits>
#include <map>
#include <fstream>
#include <sstream>
#include <cmath>
// Assignment2 enhanced version
// Implemented code changes to ensure that all instances of HealthAssitant class share the same linkedlist managed by UserInfoManager
struct UserInfo
{
    std::string gender;
    int age;
    double weight;
    double waist;
    double neck;
    double hip;
    double height;
    double bfp;
    std::string bfp_category;
    double calories;
    double carbs;
    double protein;
    double fat;
    std::string lifestyle;
    std::string name;
    UserInfo *next;
};

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>

class UserInfoManager
{
private:
    std::vector<UserInfo *> userList; //UserInfo is private member 

    // Private constructor to enforce singleton pattern
    UserInfoManager() {}
    UserInfoManager(UserInfoManager &);           // private copy constructor
    UserInfoManager operator=(UserInfoManager &); // private assignment operator
    // Private destructor, delete allocated memory
    ~UserInfoManager()
    {
        for (auto user : userList)
        {
            delete user;
        }
    }

public:
    // Static method to get the singleton instance
    static UserInfoManager &getInstance()
    {
        static UserInfoManager instance;
        return instance;
    }

    // Getter method for userList
    std::vector<UserInfo *> &getUserList()
    {
        return userList;
    }


    // -----------------------------------------------------Find user by username--------------------------------------------------------
    UserInfo *findUserByUsername( const std::string &username)
    {
        auto it = std::find_if(userList.begin(), userList.end(), [&](const UserInfo *user)
                               { return user->name == username; });

        if (it != userList.end())
        {
            return *it; // Return pointer to the found user
        }
        else
        {
            return nullptr; // Return nullptr if user not found
        }
    }

    //--------------------------------------------------add user info --------------------------------------------------------------------------
    void addUserInfo()
    {

        UserInfo *newUser = new UserInfo(); // create new userInfo object

        try
        {
            std::cout << "Please enter your username: \n";
            std::string username;
            std::getline(std::cin, username);
            // Check if the username contains only alphanumeric characters
            if (!std::regex_match(username, std::regex("^[a-zA-Z0-9]+$")))
            {
                throw std::invalid_argument("Username must contain only alphanumeric characters.");
            }
            newUser->name = username;
        }
        catch (const std::exception &e)
        {
            std::cerr << "UserName Error: " << e.what() << std::endl;
            
        }

        try{
            std::cout << "Gender: Please specify your gender, input options: male, female.\n";
            std::string input; 
            std::getline(std::cin, input);
            if (input == "male" || input == "female"){
                newUser->gender = input;
                if (newUser->gender == "female") {
                    std::cout << "Hip Measurement: Enter your hip measurement in centimeters.\n";
                    newUser->hip = getValidatedDouble();
                } else{
                    newUser->hip = 0;
                } // assign default 0
            }
            else{ //invalid inputs, throw exception 

                throw std::invalid_argument("Invalid input. Gender must be 'male' or 'female'.");
            }
        
            std::cout << "Age: Enter your age.\n";
            newUser->age = getValidatedInteger();
            // Check age validity, throw exception if age is not within range
            if (newUser->age < 20 || newUser->age > 79)
            {
                throw std::out_of_range("Age must be within the range 20 to 79.");
            }

            std::cout << "Weight: Enter your body weight in kilograms.\n";
            newUser->weight = getValidatedDouble();

            std::cout << "Waist: Input your waist measurement in centimeters.\n";
            newUser->waist = getValidatedDouble();

            std::cout << "Neck: Provide your neck measurement in centimeters.\n";
            newUser->neck = getValidatedDouble();

            std::cout << "Height: Input height measurement in centimeters.\n";
            newUser->height = getValidatedDouble();
        }
        catch (const std::exception &e)
        {
            std::cerr <<"Error with your previous input:" <<  e.what() << std::endl;
        } 

        try
        {
            std::string lifestyle;
            std::cout << "Lifestyle: Provide information about your current lifestyle: sedentary, moderate, or active.\n";
            std::getline(std::cin, lifestyle);
            if (lifestyle == "sedentary" || lifestyle == "moderate" || lifestyle == "active")
            {
                newUser->lifestyle = lifestyle;
            }
            else
            {
                throw std::invalid_argument("Invalid input. Please specify your lifestyle as sedentary, moderate, or active.");
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << std::endl;
        }

        userList.push_back(newUser);
    };

    //----------------------------------------------- delete user -----------------------------------------------------------
    void deleteUser(const std::string &username)
    {
        for (auto i = userList.begin(); i != userList.end(); ++i) // iterate through the list
        {
            if ((*i)->name == username)
            {
                delete *i;
                userList.erase(i);
                std::cout << "*************************DELETE USER *********************************\n";
                std::cout << "                User: " << username << " is deleted                 \n";
                return;
            }
        }
        std::cout << "User not found!\n";
    };

    //-----------------------------------------display user info -------------------------------
    void display(const std::string &username)
    {
        if (username == "all")
        {
            std::cout << "\n*************************DISPLAYING ALL USERS**********************\n\n";
            for (const auto &user : userList)
            {
                printUserInfo(user);
            }
            std::cout << "\n*************************END OF DISPLAY OF ALL USERS***************\n\n";
            return;
        }

        for (const auto &user : userList)
        {
            if (user->name == username)
            {
                std::cout << "\n*************************DISPLAYING SELECTED USER*******************\n\n";
                printUserInfo(user);
                std::cout << "\n**********************END OF DISPLAY OF SELECTED USER***************\n\n";
                return;
            }
        }

        std::cout << "User not found!\n";
    };

    //-----------------------------------read from file ----------------------------------------------
    void readFromFile(const std::string &filename)
    {
        // Clear existing user data
        for (auto &user : userList)
        {
            delete user;
        }
        userList.clear();

        try{
            std::ifstream file(filename);
            if (!file.is_open())
            {
                throw std::runtime_error("Error opening file: " + filename);
            }

            std::string line;
            while (getline(file, line))
            {
                std::stringstream lineStream(line);
                std::string cell;
                UserInfo *user = new UserInfo();

                std::vector<std::string> cells;
                while (std::getline(lineStream, cell, ','))
                {
                    cells.push_back(cell);
                }

                // Assign values to UserInfo object
                if (cells.size() >= 15)
                {
                    user->name = cells[0];
                    user->gender = cells[1];
                    user->age = std::stoi(cells[2]);
                    user->weight = std::stod(cells[3]);
                    user->waist = std::stod(cells[4]);
                    user->neck = std::stod(cells[5]);
                    user->hip = std::stod(cells[6]);
                    user->height = std::stod(cells[7]);
                    user->lifestyle = cells[8];
                    user->bfp = std::stod(cells[9]);
                    user->bfp_category = cells[10];
                    user->calories = std::stod(cells[11]);
                    user->carbs = std::stod(cells[12]);
                    user->protein = std::stod(cells[13]);
                    user->fat = std::stod(cells[14]);
                }

                userList.push_back(user);
            }

            file.close();
        }

        catch (const std::exception &e)
        {
            std::cerr << "Error occured while calling readFromFile function in UserInfoManager, Error msg: " << e.what() << std::endl;
        }

        
    };

    //------------------------------------------------------write to file ----------------------------------------------------------------
    void writeToFile(const std::string &filename)
    {
        

        try
        {   
            std::ofstream file;
            file.open(filename, std::ios_base::trunc); // overwrite
            if (!file.is_open())
            {
                throw std::runtime_error("Error opening file: " + filename);
            }
            

            for (const auto &user : userList)
            {
                file << user->name << ","
                     << user->gender << ","
                     << user->age << ","
                     << user->weight << ","
                     << user->waist << ","
                     << user->neck << ","
                     << user->hip << ","
                     << user->height << ","
                     << user->lifestyle << ","
                     << user->bfp << ","
                     << user->bfp_category << ","
                     << user->calories << ","
                     << user->carbs << ","
                     << user->protein << ","
                     << user->fat << "\n";
            }

            file.close();
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error occured while calling writeToFile function in UserInfoManager, Error msg: "<< e.what() << std::endl;
        }
    }

    //--------------------------------------------helper method for display ----------------------------

    void printUserInfo(UserInfo *current)
    {
        std::cout << "------------------------------------------------\n";
        std::cout << "         Health Profile for " << current->name << "\n";
        std::cout << "------------------------------------------------\n";
        std::cout << "Username: " << current->name << "\n";
        std::cout << "Gender: " << current->gender << "\n";
        std::cout << "Age: " << current->age << " years\n";
        std::cout << "Weight: " << current->weight << " kg\n";
        std::cout << "Waist: " << current->waist << " cm\n";
        std::cout << "Neck: " << current->neck << " cm\n";
        std::cout << "Height: " << current->height << " cm\n";
        std::cout << "Lifestyle: " << current->lifestyle << "\n";

        if (current->gender == "female")
        {
            std::cout << "Hip: " << current->hip << " cm\n";
        }

        std::cout << "Body Fat Percentage: " << current->bfp << "% (bfp-category: " << current->bfp_category << ")" << std::endl;

        std::cout << "Daily Caloric Intake Suggestion: " << current->calories << " cal " << std::endl;

        std::cout << "Macronutrient Breakdown:\n";
        std::cout << "Carbs: " << current->carbs << "g, Protein: " << current->protein << "g, Fat : " << current->fat << " g " << std::endl;
        std::cout << "------------------------------------------------\n";
    };

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
        std::cin.exceptions(std::ios_base::failbit);
        try
        {
            std::cin >> value;
            clearInputBuffer();
            return value;
        }
        catch (const std::ios_base::failure &e)
        {
            clearInputBuffer();
            throw std::invalid_argument("Invalid input. Please enter a valid integer.");
        }
    }

    // Function to get validated double input

    double getValidatedDouble()
    {
        double value;
        std::cin.exceptions(std::ios_base::failbit);
        try
        {
            std::cin >> value;
            clearInputBuffer();
            return value;
        }
        catch (const std::ios_base::failure &e)
        {
            clearInputBuffer();
            throw std::invalid_argument("Invalid input. Please enter a valid number.");
        }
    }
};


// HealthAssistant class
// wrapper methods: getUserDetail, display, serialize, readfromFile, deleteUser
// Implementations are provided by the UserInfoManager class
// making HealthAssistant class an abstract base class, all subclasses must implement getBfp; 

class HealthAssistant
{

public:
    HealthAssistant() : manager(UserInfoManager::getInstance()){}; // constructor obtains singleton instance of UserInfoManager
    virtual ~HealthAssistant(){};                                  // virtual since the class will be inherited 

    //-----------------------wrapper methods ----------------------------------------------------------------

    void getUserDetail()
    {
        manager.addUserInfo();
    };

    void serialize(std::string filename)
    {
        manager.writeToFile(filename);
    }; // wrapper method

    void display(std::string username)
    {
        manager.display(username);
    }; // wrapper method

    void deleteUser(std::string username)
    {
        manager.deleteUser(username);
    };

    void readFromFile(std::string filename)
    {
        manager.readFromFile(filename);
    };

    // //------------------------------getBFP ---------------------------------------------------------------

    virtual void getBfp(std::string username) = 0; // pure virtual function, must be implemented by derived classes

    //-------------------------get daily calories------------------------------------------------------------

    void getDailyCalories(const std::string username)
    {
        UserInfo *user = manager.findUserByUsername(username);
        
        if (user == nullptr){std::cout << "User not found!\n";}
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

        // std::cout << "Daily calorie requirement for " << username << " is: " << cal << " calories\n";
    }

    //------------------------------meal prep --------------------------------------------------------------

    void getMealPrep(std::string username)
    {

        UserInfo *user = manager.findUserByUsername(username);
        if (user == nullptr)
        {
            std::cout << "User not found\n";
            return;
        }

        double calories_input = user->calories; // Default calorie requirement
        // Calculate the caloric intake for each macronutrient
        double calories_for_carbs = 0.50 * calories_input;   // 50% of total calories
        double calories_for_protein = 0.30 * calories_input; // 30% of total calories
        double calories_for_fat = 0.20 * calories_input;     // 20% of total calories

        // Convert the caloric intake into grams for each macronutrient
        user->carbs = calories_for_carbs / 4;     // 1 gram of carbs = 4 calories
        user->protein = calories_for_protein / 4; // 1 gram of protein = 4 calories
        user->fat = calories_for_fat / 9;         // 1 gram of fat = 9 calories
    };

    //------------------------------Mass Load and Compute --------------------------------------------------------------
    void massLoadAndCompute(std::string filename)
    {
        manager.readFromFile(filename);
        std::vector<UserInfo *> &userList = manager.getUserList();
        for (auto current : userList)
        {
            getBfp(current->name);
            getDailyCalories(current->name);
            getMealPrep(current->name);
        }
    };

protected:
    UserInfoManager &manager;

    //--------------------------------------------helper methods--------------------------------
    //US Navy BFP method helper function 
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


    // BMI BFP helper function 
    std::pair<int, std::string> get_bfp_bmi(double weight, double height, std::string gender, int age)
    {

        double h = height / 100; //height in meter 
        double bfp = weight / (h * h); //using bmi for calculating bfp
        std::string category;

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
        else if (bfp >= highThreshold)
        {
            return "very high";
        }

        return "undefined";
    }
};


class USNavyMethod : public HealthAssistant
{
public:
  
    void getBfp(std::string username) {
        UserInfo *user = manager.findUserByUsername(username);
        if (user == nullptr)
        {
            std::cout << "User not found\n";
            return;
        }

        std::pair<int, std::string> bfp = get_bfp(user->waist, user->neck, user->height, user->hip,user->gender,user->age); 
        user->bfp = bfp.first;
        user->bfp_category = bfp.second;
    };
    
}; 

class BmiMethod : public HealthAssistant
{
public:
   
    //Alternative implementation of getBfp, using BMI formula 
    void getBfp(std::string username)
    {
        UserInfo* user = manager.findUserByUsername(username);
        if (user == nullptr)
        {
            std::cout << "User not found\n";
            return;
        }
        std::pair<int, std::string> bfp = get_bfp_bmi(user->weight, user->height, user->gender, user->age); 
        user->bfp = bfp.first;
        user->bfp_category = bfp.second;
    }
    
}; 
               



int main()
    {
        HealthAssistant* ha = new USNavyMethod(); 
        ha->getUserDetail();
        ha->getUserDetail();
        ha->getUserDetail();
        std::cout << "\n>displaying john's health profile\n\n";
        ha->display("john");

        std::cout << "\n>>displaying all user health profile\n\n";
        ha->display("all");
        ha->serialize("user_data.csv");

        std::cout << "\n>getting john, jack, mary's bfp, daily calories, mealprep info\n\n";
        ha->getBfp("john");
        ha->getDailyCalories("john");
        ha->getMealPrep("john");
        ha->getBfp("jack");
        ha->getDailyCalories("jack");
        ha->getMealPrep("jack");
        ha->getBfp("mary");
        ha->getDailyCalories("mary");
        ha->getMealPrep("mary");

        std::cout << "\n>storing current info to user_data2.csv\n\n";
        ha->serialize("user_data2.csv");

    
}
