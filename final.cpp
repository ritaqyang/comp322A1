#include <iostream>
#include <string>
#include <limits>
#include <map>
#include <fstream>
#include <sstream>
#include <cmath> 

// Struct for storing userdata in vectors for Q7
struct UserData
{
    std::string gender;
    int age;
    double weight; 
    double waist;
    double neck;
    double hip;
    double height;
    std::string lifestyle;
};

// Global variables
std::string g_gender;
int g_age;
double g_weight;
double g_waist;
double g_neck;
double g_height;
std::string g_lifestyle;
double g_hip; // For female users
std::map<std::string, int> calorieMap; //global map that suggests calorie intake
std::vector<UserData> users; //for Q7, storing each line in one vector 

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

//Function to make string-format key for calorie map
std::string makeKey(const std::string &gender, const std::string &lifestyle, int ageRange)
{
    return gender + "_" + lifestyle + "_" + std::to_string(ageRange);
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
//stores best calorie info in global variable calorieMap
void updateCalorieMap(){
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
}

//----------------------------------------------------------------
// Q1 function starts here 
void getUserDetails()
{
    //This function gets user detais from standard input 
    //also populates calorie map for future use
    updateCalorieMap();

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
        if (g_lifestyle == "sedentary" || g_lifestyle  == "moderate" || g_lifestyle == "active")
        {
            break;
        }
        std::cout << "Invalid input. Please specify your lifestyle as sedentary, moderate, or active: ";
    }

    //hip measurement if user is female 
    if (g_gender == "female")
    {
        std::cout << "Hip Measurement: Enter your hip measurement in centimeters.\n";
        g_hip = getValidatedDouble();
    }
}


//----------------------------------------------------------------
// Q2: get body fat percentage
// The function returns back the body fat percentage value together with the associated group(low, normal, high, very high)

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

    // Instead of the strucutre if .... then getcategory(bfp,21,33,39)

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

//----------------------------------------------------------------
// Q3: get daily calories
int get_daily_calories(double age, std::string gender, std::string lifestyle)
{
    int cal; // calories
    int ageRange = (age >= 19 && age <= 30) ? 1 : (age > 30 && age <= 50) ? 2
                                              : (age > 50)                ? 3
                                                                          : 0;
    std::string key = makeKey(gender, lifestyle, ageRange);
    cal = calorieMap[key]; // use populated data in global variable calorieMap

    return cal;
}

//----------------------------------------------------------------
// Q4: Macronutrient Breakdown (use references to return back multiple values)
// The function will return three values corresponding for the amount in grams of carbs, amount in grams of protein and amount in grams of fat 
void meal_prep(int calories_input, double &carbs_output, double &protein_output, double &fat_output)
{
    // Calculate the caloric intake for each macronutrient
    double calories_for_carbs = 0.50 * calories_input;   // 50% of total calories
    double calories_for_protein = 0.30 * calories_input; // 30% of total calories
    double calories_for_fat = 0.20 * calories_input;     // 20% of total calories

    // Convert the caloric intake into grams for each macronutrient
    carbs_output = calories_for_carbs / 4;     // 1 gram of carbs = 4 calories
    protein_output = calories_for_protein / 4; // 1 gram of protein = 4 calories
    fat_output = calories_for_fat / 9;         // 1 gram of fat = 9 calories
}
//----------------------------------------------------------------
//Q5: display funcion 
void display()
{
    std::cout << "User Input Data\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Gender: " << g_gender << "\n";
    std::cout << "Age: " << g_age << " years\n";
    std::cout << "Weight: " << g_weight << " kg\n";
    std::cout << "Waist: " << g_waist << " cm\n";
    std::cout << "Neck: " << g_neck << " cm\n";
    std::cout << "Height: " << g_height << " cm\n";
    std::cout << "Lifestyle: " << g_lifestyle << "\n";

    if (g_gender == "Female" || g_gender == "female")
    {
        std::cout << "Hip: " << g_hip << " cm\n";
    }
    std::cout << "----------------------------------------\n";
    std::cout << "User Health Profile\n";
    std::cout << "----------------------------------------\n";
    // Calculate body fat percentage
    std::pair<int, std::string> bfpResult = get_bfp(g_waist, g_neck, g_height, g_hip,
                                                    g_gender, g_age);
    std::cout << "Body Fat Percentage: " << bfpResult.first << "% (" << bfpResult.second << ")" << std::endl;
    // Calculate daily calorie intake
    int dailyCalories = get_daily_calories(g_age, g_gender,
                                           g_lifestyle);
    std::cout << "Daily Caloric Intake Suggestion: " << dailyCalories << " calories " << std::endl;
    // Calculate macronutrient brekdown

    double carbs, protein, fat;
    meal_prep(dailyCalories, carbs, protein, fat);
    std::cout << "Macronutrient Breakdown:\n";
    std::cout << "Carbs: " << carbs << "g, Protein: " << protein << "g, Fat : " << fat << " g " << std::endl;
}


//----------------------------------------------------------------
//Q6: Persistence 
//Function take filename and record user data across multiple program executions 
void serialize(const std::string &filename)
{
    std::ofstream file;

    // Open the file in append mode
    file.open(filename, std::ios_base::app);

    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << "\n";
        return;
    }

    file << g_gender << ", "
         << g_age << ", "
         << g_weight << ", "
         << g_waist << ", "
         << g_neck << ", ";

    // Conditionally add hip measurement for females
    if (g_gender == "female")
    {
        file << g_hip << ", ";
    }
    else
    {
        file << ", "; // Leave hip empty for males
    }

    file << g_height << ", "
         << g_lifestyle << "\n";

    file.close();
}


//----------------------------------------------------------------
//Q7: Read from file
//Generate vectors for each line in the csv file 
void readFromFile(const std::string &filename){
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
        UserData user; //new user 

        // CSV columns are ordered as gender, age, weight, waist, neck, hip, height, lifestyle
        getline(lineStream, user.gender, ',');

        getline(lineStream, cell, ',');
        try
        {
            user.age = std::stoi(cell);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Conversion error for age: '" << cell << "': " << e.what() << std::endl;
            
        }
        
        getline(lineStream, cell, ',');
        try{
            user.weight = std::stod(cell);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Conversion error for weight: '" << cell << "': " << e.what() << std::endl;
        }

        getline(lineStream, cell, ',');
        try
        {
            user.waist = std::stod(cell);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Conversion error for waist : '" << cell << "': " << e.what() << std::endl;
        }
        getline(lineStream, cell, ',');
        try
        {
            user.neck = std::stod(cell);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Conversion error for neck: '" << cell << "': " << e.what() << std::endl;
        }

        getline(lineStream, cell, ',');
        try
        {
            user.hip = std::stod(cell);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Conversion error for neck: '" << cell << "': " << e.what() << std::endl;
            user.hip = 0; 
        }
        getline(lineStream, cell, ',');
        try
        {
            user.height = std::stod(cell);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Conversion error for height: '" << cell << "': " << e.what() << std::endl;
        }
        getline(lineStream, user.lifestyle, ',');

        // Add the user to the vector
        users.push_back(user);
    }

    file.close();
}


int main(int argc, char *argv[])
{
    // Check if a filename is provided as an argument
    if (argc > 1)
    {
        // Load existing user data from the specified CSV file
        readFromFile(argv[1]);

        // Test for vectors in global vector<UserData> users 
        for (size_t i = 0; i < users.size(); ++i)
        {
            UserData &user = users[i];
            
    
            std::cout << "Gender: " << user.gender
                      << ", Age: " << user.age
                      << ", Height: " << user.height
                      << ", Waist: " << user.waist
                      << ", Neck: " << user.neck
                      << ", Hip: " << user.hip 
                    << std::endl;
        }
    }
    else
    {
        getUserDetails();
        // Display user information
        display(); //other functions are ran within the display function 
        // Save user data to a CSV file
        serialize("user_data.csv");
    }
    return 0;
}
