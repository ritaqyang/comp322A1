// #include <iostream>
// #include <string>
// #include <cmath>   
// #include <utility> 
// #include <map>
// #include <tuple>


// int get_daily_calories(double age, std::string gender, std::string lifestyle)
// {
//     int cal; //calories


//     // Define a struct or use a tuple for the key
//     using Key = std::tuple<std::string, std::string, int>; // gender, lifestyle, age range(identified by 1,2,3)

//     std::map<Key, int> calorieMap = {
//         // need to change specific numbers 
//         // Age range 19-30
//         {std::make_tuple("male", "sedentary", 1), 2400},
//         {std::make_tuple("male", "moderate", 1), 2700},
//         {std::make_tuple("male", "active", 1), 3000},
//         {std::make_tuple("female", "sedentary", 1), 2000},
//         {std::make_tuple("female", "moderate", 1), 2100},
//         {std::make_tuple("female", "active", 1), 2400},

//         // Age range 31-50
//         {std::make_tuple("male", "sedentary", 2), 2300},
//         {std::make_tuple("male", "moderate", 2), 2600},
//         {std::make_tuple("male", "active", 2), 2900},
//         {std::make_tuple("female", "sedentary", 2), 1900},
//         {std::make_tuple("female", "moderate", 2), 2000},
//         {std::make_tuple("female", "active", 2), 2300},

//         // Age range 51+
//         {std::make_tuple("male", "sedentary", 3), 2200},
//         {std::make_tuple("male", "moderate", 3), 2500},
//         {std::make_tuple("male", "active", 3), 2800},
//         {std::make_tuple("female", "sedentary", 3), 1800},
//         {std::make_tuple("female", "moderate", 3), 1900},
//         {std::make_tuple("female", "active", 3), 2200},

       
//     };

//     // Identify each age range, use 0 for out of range values   
//     int ageRange = (age >= 19 && age <= 30) ? 1 : (age > 30 && age <= 50) ? 2 : (age > 50) ? 3 : 0 ; 
//     Key key = std::make_tuple(gender, lifestyle, ageRange);
//     cal = calorieMap[key];

   
//     return cal; 
// }

// // int main()
// // {
// //     // test cases for function performance
   
// //     auto result = get_daily_calories(20, "female", "moderate");
// //     std::cout << "Daily Calory intake: " << result << std::endl;

// //     return 0;
// // }
