// #include <iostream>
// #include <fstream>
// #include <string>

// // Global variables
// std::string gender;
// int age;
// double weight;
// double waist;
// double neck;
// double height;
// std::string lifestyle;
// double hip; // For female users

// void serialize(const std::string &filename)
// {
//     std::ofstream file;

//     // Open the file in append mode
//     file.open(filename, std::ios_base::app);

//     if (!file.is_open())
//     {
//         std::cerr << "Error opening file: " << filename << "\n";
//         return;
//     }

//     // Write the data in CSV format
//     file << gender << ", "
//          << age << ", "
//          << weight << ", "
//          << waist << ", "
//          << neck << ", ";

//     // Conditionally add hip measurement for females
//     if (gender == "Female" || gender == "female")
//     {
//         file << hip << ", ";
//     }
//     else
//     {
//         file << ", "; // Leave hip empty for males
//     }

//     file << height << ", "
//          << lifestyle << "\n";

//     file.close();
// }

// int main()
// {
//     gender = "Female";
//     age = 28;
//     weight = 60;
//     waist = 75;
//     neck = 34;
//     height = 165;
//     lifestyle = "Active";
//     hip = 95;

//     serialize("userData.csv");

//     return 0;
// }
