#include <iostream>
#include <string>
#include <limits>
#include <map>
#include <sstream>
#include <cmath>
#include <vector>
#include <fstream>
#include <regex>
#include <unordered_set>

// g++ -std=c++11 assignment3.cpp -o c3
// Assignment 3 Improvements:
//  1. Using vector instead of linkedlist to manage users
//  2. Exception handling for user inputs / age range / reading + writing file (file not found, empty file)
//  3. HealthAssitant interface, 2 implmenting subclasses (different BFP methods)
//  4. new class UserStats that provide stats about users' health

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


class UserInfoManager
{
private:
    std::vector<UserInfo *> userList; //UserInfo is private member 


public:
    UserInfoManager(){};
    ~UserInfoManager()
    {
        for (auto user : userList)
        {
            delete user;
        }
        userList.clear();
    }
    std::vector<UserInfo *> &getUserList()
    {
        return userList;
    }


    // -----------------------------------------------------Find user by username--------------------------------------------------------
    UserInfo *findUserByUsername( const std::string &username)
    {
        for (auto it = userList.begin(); it != userList.end(); ++it){
            if ((*it)->name == username){
                return *it;
            }
        }
        
        return nullptr; // Return nullptr if user not found
       
    }; 

    //--------------------------------------------------add user info --------------------------------------------------------------------------
    void addUserInfo(){

    try{

            UserInfo *newUser = new UserInfo();
            std::string input; 

            std::cout << "Please enter your username: \n";
            std::getline(std::cin, input);
            newUser->name = input;

            std::cout << "Gender: Please specify your gender, input options: male, female.\n";
            std::getline(std::cin, input);
            if (input != "male" && input != "female")
                throw std::invalid_argument("Invalid input. Gender must be 'male' or 'female'.");
            newUser->gender = input;

            if (newUser->gender == "female")
            {
                std::cout << "Hip Measurement: Enter your hip measurement in centimeters.\n";
                std::getline(std::cin, input);
                newUser->hip = std::stod(input);
            }
            else
            {
                newUser->hip = 0;
            }

            std::cout << "Age: Enter your age.\n";
            std::string age_input;
            std::getline(std::cin, age_input);
            newUser->age = std::stoi(age_input);
            if (newUser->age < 20 || newUser->age > 79)
                throw std::out_of_range("Age must be within the range 20 to 79.");

            std::cout << "Weight: Enter your body weight in kilograms.\n";
            std::string weight_input;
            std::getline(std::cin, weight_input);
            newUser->weight = std::stod(weight_input);

            std::cout << "Waist: Input your waist measurement in centimeters.\n";
            std::string waist_input;
            std::getline(std::cin, waist_input);
            newUser->waist = std::stod(waist_input);

            std::cout << "Neck: Input your neck measurement in centimeters.\n";
            std::string neck_input;
            std::getline(std::cin, neck_input);
            newUser->neck = std::stod(neck_input);

            std::cout << "Height: Input height measurement in centimeters.\n";
            std::string height_input;
            std::getline(std::cin, height_input);
            newUser->height = std::stod(height_input);

            std::cout << "Lifestyle: Provide information about your current lifestyle: sedentary, moderate, or active.\n";
            std::string lifestyle_input;
            std::getline(std::cin, lifestyle_input);
            if (lifestyle_input != "sedentary" && lifestyle_input != "moderate" && lifestyle_input != "active")
                throw std::invalid_argument("Invalid input. Please specify your lifestyle as sedentary, moderate, or active.");
            newUser->lifestyle = lifestyle_input;

            userList.push_back(newUser);
            std::cout << "User information added successfully!\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error occured while calling addUserInfo function in UserInfoManager, Error msg: " << e.what() << std::endl;
        exit(1);

    }
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

            // Check if the file is empty
            file.seekg(0, std::ios::end);
            if (file.tellg() == 0)
            {
                throw std::runtime_error("Error: File is empty: " + filename);
            }
            // Reset the file position to the beginning
            file.seekg(0, std::ios::beg);

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
            exit(1); 
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


}; //end of UserInfoManager class


// HealthAssistant class
// wrapper methods: getUserDetail, display, serialize, readfromFile, deleteUser
// Implementations are provided by the UserInfoManager class
// making HealthAssistant class an abstract base class, all subclasses must implement getBfp; 

class HealthAssistant
{

public:
   
    HealthAssistant(){};
    virtual ~HealthAssistant(){
        std::cout << "Destructor called for HealthAssistant\n";
    };                                  // virtual since the class will be inherited
    // Getter method to access UserManager object
    UserInfoManager &getUserManager()
    {
        return manager;
    }

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

    //--------------------------------Mass Compute --------------------------------------------------------------
    void massCompute()
    {
        std::vector<UserInfo *> &userList = manager.getUserList();
        for (auto current : userList)
        {
            getBfp(current->name);
            getDailyCalories(current->name);
            getMealPrep(current->name);
        }
    };

protected:
    UserInfoManager manager;

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
    USNavyMethod(){};
    ~USNavyMethod(){};
  
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
   BmiMethod(){};
   ~BmiMethod(){
    std::cout << "Destructor called for BmiMethod\n";
   };
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
    };
}; 
               

//UserStats class 
//Methods: GetHealthyUsers, GetUnfitUsers, GetFullStats

class UserStats
{

public:
    UserStats(){}; 
    ~UserStats(){};

    // -----------------------------------GetHealthyUsers -------------------------------------------
    //returns a vector contaitning all normal bfp 
    //method can be US army or bmi, if "all" then both methods should output healthy
    
    std::vector<std::string> getHealthyUsers(const std::string &method, const std::string &gender)
    {
        std::pair<std::vector<std::string>, std::vector<std::string> > Navy; 
        std::pair<std::vector<std::string>, std::vector<std::string> > Bmi;
        std::vector<std::string> result;
        std::cout << "Getting healthy users...Method: " << method << "Gender :" << gender << std::endl;

        if (method == "all"){
            Navy = getHealthyBFPUsersByMethod("USArmy");
            Bmi = getHealthyBFPUsersByMethod("bmi");
            if (gender ==  "female"){
                result = intersect (Navy.first, Bmi.first); 
            }
            else if (gender == "male"){
                result = intersect (Navy.second, Bmi.second);
            }
            else if (gender.empty()) {
                result = combine(intersect (Navy.first, Bmi.first), intersect (Navy.second, Bmi.second));
            }
            else{
                throw std::invalid_argument("Unknown gender");
            }
        }

        else if (method == "USArmy" || method == "bmi"){
            result = genderFilter(getHealthyBFPUsersByMethod(method), gender);
        }
        else{
            throw std::invalid_argument("Invalid method, please enter 'USArmy' or 'bmi' or 'all' \n");
        }

        std::cout << "healthy users are below: " << std::endl;
        for (const std::string &str : result)
        {
            std::cout << str << std::endl;
        }

        return result;
    };

    // ------------------------------------GetUnfitUsers method ---------------------------------------------------------------
    std::vector<std::string> getUnfitUsers(const std::string &method, const std::string &gender){
        std::pair<std::vector<std::string>, std::vector<std::string> > Navy;
        std::pair<std::vector<std::string>, std::vector<std::string> > Bmi;
        std::vector<std::string> result;

        std::cout << "Getting unfit users...Method: " << method  << "Gender :" << gender <<std::endl;

        if (method == "all"){
            Navy = getUnHealthyBFPUsersByMethod("USArmy"); //use helper method twice for both methods
            Bmi = getUnHealthyBFPUsersByMethod("bmi");
            if (gender == "female")
            {
                result = intersect(Navy.first, Bmi.first);
            }
            else if (gender == "male")
            {
                result = intersect(Navy.second, Bmi.second);
            }
            else if (gender.empty())
            {
                result = combine(intersect(Navy.first, Bmi.first), intersect(Navy.second, Bmi.second));
            }
            else
            {
                throw std::invalid_argument("Unknown gender");
            }
        }

        else if (method == "USArmy" || method == "bmi") //if just one method, only run the helper once on either option
        {
            result = genderFilter(getUnHealthyBFPUsersByMethod(method), gender);
        }
        else //method is not either 3 options
        {
            throw std::invalid_argument("Invalid method, please enter 'USArmy' or 'bmi' or 'all' \n");
        }

        return result;

    }; 

    // -------------------------------------------GetFullStats method-------------------------------------------------
    void getFullStats(){
        
        int totalMaleUsers = 0;
        int totalFemaleUsers = 0;
        std::pair<std::vector<std::string>, std::vector<std::string> > Navy = getHealthyBFPUsersByMethod("UsArmy"); 
        std::pair<std::vector<std::string>, std::vector<std::string> > Bmi = getHealthyBFPUsersByMethod("bmi");

        
        int totalHealthyFemalesBmi = Bmi.first.size(); 
        int totalHealthyMalesBmi = Bmi.second.size();
        int totalHealthyFemalesUsArmy = Navy.first.size();
        int totalHealthyMalesUsArmy = Navy.second.size();

        int totalHealthyUsersBmi = totalHealthyFemalesBmi  + totalHealthyMalesBmi;
        int totalHealthyUsersUsArmy = totalHealthyFemalesUsArmy + totalHealthyMalesUsArmy;

        HealthAssistant *ha;
        ha = new USNavyMethod();
        ha->massLoadAndCompute("us_user_data.csv");
        
        // Calculate statistics
        for (const auto *user : ha->getUserManager().getUserList())
        {
            (user->gender == "male")? totalMaleUsers += 1 : totalFemaleUsers += 1;
            
        }
        int totalUsers = totalMaleUsers + totalFemaleUsers;

        delete ha; 

        // Calculate percentages
        double percentageMaleUsers = static_cast<double>(totalMaleUsers) / totalUsers * 100;
        double percentageFemaleUsers = static_cast<double>(totalFemaleUsers) / totalUsers * 100;
        double percentageHealthyUsersBmi = static_cast<double>(totalHealthyUsersBmi) / totalUsers * 100;
        double percentageHealthyUsersUsArmy = static_cast<double>(totalHealthyUsersUsArmy) / totalUsers * 100;
        double percentageHealthyFemalesBmi = static_cast<double>(totalHealthyFemalesBmi) / totalFemaleUsers * 100;
        double percentageHealthyMalesBmi = static_cast<double>(totalHealthyMalesBmi) / totalMaleUsers * 100;
        double percentageHealthyFemalesUsArmy = static_cast<double>(totalHealthyFemalesUsArmy) / totalFemaleUsers * 100;
        double percentageHealthyMalesUsArmy = static_cast<double>(totalHealthyMalesUsArmy) / totalMaleUsers * 100;

        // Display stats 
        std::cout << "Total number of users: " << totalUsers << std::endl;
        std::cout << "Percentage of male users: " << std::setw(5) << std::fixed << std::setprecision(2) << percentageMaleUsers << "%" << std::endl;
        std::cout << "Percentage of female users: " << std::setw(5) << std::fixed << std::setprecision(2) << percentageFemaleUsers << "%" << std::endl;
        std::cout << "Percentage of healthy users according to BMI method: " << std::setw(5) << std::fixed << std::setprecision(2) << percentageHealthyUsersBmi << "%" << std::endl;
        std::cout << "Percentage of healthy users according to US Army method: " << std::setw(5) << std::fixed << std::setprecision(2) << percentageHealthyUsersUsArmy << "%" << std::endl;
        std::cout << "Percentage of healthy females according to BMI method: " << std::setw(5) << std::fixed << std::setprecision(2) << percentageHealthyFemalesBmi << "%" << std::endl;
        std::cout << "Percentage of healthy males according to BMI method: " << std::setw(5) << std::fixed << std::setprecision(2) << percentageHealthyMalesBmi << "%" << std::endl;
        std::cout << "Percentage of healthy females according to US Army method: " << std::setw(5) << std::fixed << std::setprecision(2) << percentageHealthyFemalesUsArmy << "%" << std::endl;
        std::cout << "Percentage of healthy males according to US Army method: " << std::setw(5) << std::fixed << std::setprecision(2) << percentageHealthyMalesUsArmy << "%" << std::endl;
    };

private:
    //--------------------------------helper methods for UserStats class --------------------------------

    // ---------------------------Method to get the intersection of two vectors--------------------------------
    std::vector<std::string> intersect(const std::vector<std::string> &vec1, const std::vector<std::string> &vec2)
    {
        std::unordered_set<std::string> set1(vec1.begin(), vec1.end());

        std::vector<std::string> result;
        for (const auto &str : vec2)
        {
            if (set1.find(str) != set1.end())
            {
                result.push_back(str);
            }
        }
        return result;
    };

    //  ----------------------------Method to combine two vector of strings ----------------------------
    std::vector<std::string> combine(const std::vector<std::string> &vec1, const std::vector<std::string> &vec2)
    {
        std::vector<std::string> combinedVec;

        // Add elements from vec1
        for (const auto &str : vec1)
        {
            combinedVec.push_back(str);
        }

        // Add elements from vec2
        for (const auto &str : vec2)
        {
            combinedVec.push_back(str);
        }

        return combinedVec;
    };

    std::vector<std::string> genderFilter(const std::pair<std::vector<std::string>, std::vector<std::string> > &vec, const std::string &gender)
    {
        std::vector<std::string> result;
        if (gender == "female")
        {
            result = vec.first;
        }
        else if (gender == "male")
        {
            result = vec.second;
        }
        else if (gender.empty())
        {
            result = combine(vec.first, vec.second);
        }
        else
        {
            throw std::invalid_argument("Unknown gender");
        }
        return result;
    };

    //method returns a pair of list of names of healthy users <female, male> 
    std::pair <std::vector < std::string>, std::vector<std::string> > getHealthyBFPUsersByMethod(const std::string &method)
    {

        std::cout << "getHealthyBFPUsers Helper method is called with method: " << method << std::endl;
        HealthAssistant*  ha; 

        if (method == "USArmy"){
            ha = new USNavyMethod();
            ha->massLoadAndCompute("us_user_data.csv");
        }
        else if (method == "bmi"){
            ha = new BmiMethod();
            ha->massLoadAndCompute("bmi_user_data.csv");
        }

        std::vector<std::string> healthyFemaleUsers;
        std::vector<std::string> healthyMaleUsers;
        std::pair<std::vector<std::string>, std::vector<std::string> > healthyUsers;

        if (ha ==nullptr) {
            std::cout << "Error: Ha is null pointer" << std::endl;
        }
        std::vector<UserInfo *> &userList = ha->getUserManager().getUserList();
        for (auto current : userList)
        {
            if (current->bfp_category == "normal" && current->gender == "male")
            {
                healthyMaleUsers.push_back(current->name);
            }
            else if (current->bfp_category == "normal" && current->gender == "female")
            {
                healthyFemaleUsers.push_back(current->name);
            }
        }
        healthyUsers = std::make_pair(healthyFemaleUsers, healthyMaleUsers);
        delete ha;

        return healthyUsers;
    }
    // method returns a pair of list of names of UNhealthy users <female, male>
    std::pair<std::vector<std::string>, std::vector<std::string> > getUnHealthyBFPUsersByMethod(const std::string &method)
    {
        HealthAssistant *ha;

        if (method == "USArmy")
        {
            ha = new USNavyMethod();
        }
        else if (method == "bmi")
        {
            ha = new BmiMethod();
        }
    

        std::vector<std::string> unHealthyFemaleUsers;
        std::vector<std::string> unHealthyMaleUsers;
        std::pair<std::vector<std::string>, std::vector<std::string> > unHealthyUsers;

        std::vector<UserInfo *> &userList = ha->getUserManager().getUserList();
        for (auto current : userList)
        {
            if (current->bfp_category == "high" || current->bfp_category == "very high"){
                if (current-> gender == "female") {
                    unHealthyFemaleUsers.push_back(current->name);
                }
                else {
                    unHealthyMaleUsers.push_back(current->name);
                
                }
            }
            
        }
        
        unHealthyUsers = std::make_pair(unHealthyFemaleUsers, unHealthyFemaleUsers); 
        delete ha;

        return unHealthyUsers;
    }

};

int main()
    {
        std::cout << "\n>Creating a new instance of USNavyMethod\n\n";
        HealthAssistant* ha = new USNavyMethod();
        std::string userInput; 

        std::cout << "\n>Getting user input from std until exit \n\n";
        while (true){
            ha->getUserDetail();
            std::getline(std::cin, userInput);
            if(userInput == "exit"){break; }
        }


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

        ha->display("all");

        std::cout << "\n> mass computing all users\n\n";
        ha->massCompute();
        std::cout << "\n>storing current info to us_user_data.csv before any deletion \n\n";
        ha->serialize("us_user_data.csv");

        std::cout << "\n> Deletion test:  displaying all users before deleting john, jack, mary\n\n";

        ha->display("all");

        ha->deleteUser("john");
        ha->deleteUser("jack");
        ha->deleteUser("mary");

        std::cout << "\n> Displaying all users after deleting john, jack, mary\n\n";
        ha->display("all");

        
        delete ha; 




        std::cout << "\n > Creating a new instance of BmiMethod\n\n";
        ha = new BmiMethod();

        std::cout << "\n>Getting user input from std until exit \n\n";
        while (true){
            ha->getUserDetail();
            std::getline(std::cin, userInput);
            if(userInput == "exit"){break; }
        }


        std::cout << "\n> mass computing all users\n\n";
        ha->massCompute();
        std::cout << "\n>storing current info to bmi_user_data.csv before any deletion \n\n";
        ha->serialize("bmi_user_data.csv");

        std::cout << "\n> Deletion test:  displaying all users before deleting jack\n\n";

        ha->display("all");

        ha->deleteUser("jack");

        std::cout << "\n> Displaying all users after deleting jack\n\n";
        ha->display("all");

        
        delete ha; 

        std::cout << "\n>Creating a new instance of UserStats\n\n";

        UserStats stat; 
        stat.getHealthyUsers("bmi", "female");
        stat.getHealthyUsers("USArmy", "female");
        //stat.getHealthyUsers("all", "female"); 
        //stat.getUnfitUsers("USArmy", "female");
        //stat.getFullStats();
    }

