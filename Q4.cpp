#include <iostream>

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

int main()
{
    // Example usage
    int total_calories = 2500; // Example total daily caloric need
    double carbs, protein, fat;

    meal_prep(total_calories, carbs, protein, fat);

    std::cout << "Carbs (g): " << carbs << "\n";
    std::cout << "Protein (g): " << protein << "\n";
    std::cout << "Fat (g): " << fat << "\n";

    return 0;
}
