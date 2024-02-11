#include <iostream>
#include <string>
#include <limits>
#include <map>
#include <fstream>
#include <sstream>>


struct UserData
{
    std::string gender;
    int age;
    double height;
    double waist;
    double neck;
    double hip;
    double height;
    std::string lifestyle; 
};



void readFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    std::string line;
    std::vector<UserData> users;

    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    while (getline(file, line))
    {
        std::stringstream lineStream(line);
        std::string cell;
        UserData user;

        // Assuming the CSV columns are ordered as gender, age, height, waist, neck, hip
        getline(lineStream, user.gender, ',');

        getline(lineStream, cell, ',');
        user.age = std::stoi(cell);

        getline(lineStream, cell, ',');
        user.height = std::stod(cell);

        getline(lineStream, cell, ',');
        user.waist = std::stod(cell);

        getline(lineStream, cell, ',');
        user.neck = std::stod(cell);

        getline(lineStream, cell, ',');
        user.hip = std::stod(cell);

        // Add the user to the vector
        users.push_back(user);
    }

    file.close();

    // For demonstration: Print the data read from the file
    for (const auto &user : users)
    {
        std::cout << "Gender: " << user.gender
                  << ", Age: " << user.age
                  << ", Height: " << user.height
                  << ", Waist: " << user.waist
                  << ", Neck: " << user.neck
                  << ", Hip: " << user.hip << std::endl;
    }
}

int main(int argc, char *argv[])
{
    // Check if a filename is provided as an argument
    if (argc > 1)
    {
        // Load existing user data from the specified CSV file
        readFromFile(argv[1]);
    }
    else
    {
        std::cout << "No file specified." << std::endl;
    }
    return 0;
}
