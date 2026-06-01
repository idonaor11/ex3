/******************
Name: ido naor

Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define INITIALIZE_CUBE -1
#define addOne  1
#define addAll  2  
#define stats  3
#define print  4
#define insights  5
#define deltas  6
#define done  7
#define TYPE_0 0
#define TYPE_1 1
#define TYPE_2 2
#define TYPE_3 3
#define ARRAY_DAY 1

char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};
// Function to print the main menu.
void printMenu(){
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}
// This function initializes the cube 3D array  with -1 values.
void setMinusOne(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    for (int i = 0; i < DAYS_IN_YEAR; i++) {
        for (int j = 0; j < NUM_OF_BRANDS; j++) {
            for (int d = 0; d < NUM_OF_TYPES; d++) {
                cube[i][j][d] = INITIALIZE_CUBE ; // Set all elements to -1
            }
        }
    }
}
// Helper function to check if any brands are missing data and display the appropriate message
void withOutValue(int setBrand[NUM_OF_BRANDS],char brands[NUM_OF_BRANDS][BRANDS_NAMES]) {
    int sum1 =0,sum2 =0;
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        if (setBrand[i] == 0) {
            sum2++;
            sum1++;
        }
    }
    if (sum2>0) {
        printf ("No data for brands");
        for (int i = 0; i < NUM_OF_BRANDS; i++) {
            if (setBrand[i] == 0) {
                printf(" %s", brands[i]);// Print brands with missing data
            }
        }
        printf("\nPlease complete the data \n");
    }
}
// Function to clear the 'setBrand' array (reset all brands to no data entered)
void clearSetBrand(int setBrand[NUM_OF_BRANDS]) {
    for (int i = 0; i < NUM_OF_BRANDS; i++)
        setBrand[i] = 0;// Reset all brands to 0, to allow entering values for the next day
}
// Function to enter sales data for a specific brand on a specific day
void enterBrandSales(
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],
    int days[NUM_OF_BRANDS],
    int brandIndex,
    int day,
    int setBrand[NUM_OF_BRANDS]) {

    int suv, sedan, coupe, gt;
    // get sales data for each car type from the user
    int count=scanf("%d %d %d %d %d", &brandIndex, &suv, &sedan, &coupe, &gt);
    // Read the sales data for each car type
    if (count != NUM_OF_BRANDS) {
        printf("This brand is not valid\n");
        withOutValue(setBrand,brands);// Show brands with missing data
        return;
    }
    // Checking if the brand data has already been entered today
    if(setBrand[brandIndex]==addOne) {
        printf("This brand is not valid\n");
        withOutValue(setBrand,brands);// Show brands with missing data
        return;
    }
    // Checking if the brand index is valid
    if((brandIndex >= NUM_OF_BRANDS)|| (brandIndex < 0)) {
        printf("This brand is not valid\n");
        withOutValue(setBrand,brands);// Show brands with missing data
        return;
    }
    // Check if there is space for more data (i.e., the year has not ended)
    if (days[brandIndex] >= DAYS_IN_YEAR) {
        printf("No more days available for this brand.\n");
        return;
    }
    // Updating the cube
    setBrand[brandIndex] = addOne;
    cube[day][brandIndex][TYPE_0] = suv;
    cube[day][brandIndex][TYPE_1] = sedan;
    cube[day][brandIndex][TYPE_2] = coupe;
    cube[day][brandIndex][TYPE_3] = gt;
    withOutValue(setBrand,brands); // Show brands with missing data
    days[brandIndex]++; // move to the next
}


// Function to calculate total sales for a specific day across all brands and types
int totalSalesPerDay(int day, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    int sum1 =0;
    for (int i = 0; i <NUM_OF_BRANDS ; i++) {
        for (int j = 0; j < NUM_OF_TYPES; j++) {
            sum1+=cube[day][i][j]; // Add sales for each type of car for all brands
        }
    }
    return sum1; // Return total sales for that day
}
// Function to calculate the total sales for a specific brand on a specific day
int dayBrandSales(int day ,int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int brandIndex) {
    int totalSales = 0;
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        totalSales += cube[day][brandIndex][i];// Add sales for all car types of the brand
    }
    return totalSales; // Return total brand sales for that day
}
// Function to calculate the total sales for a specific car brand type on a specific day
int dayTypeSales(int day, int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES], int typeIndex) {
    int totalSales = 0;
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        totalSales += cube[day][i][typeIndex]; // Add sales for the specific car type across all brands
    }
    return totalSales;// Return total type sales for that day
}
// Function to determine and print the best-selling brand on a specific day
void bestSoldBrand(
    int day,
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],
    char brands[NUM_OF_BRANDS][BRANDS_NAMES]){
    int max=0, biggestBrandIndex=0;
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        // using the function to get total sales for the brand on the given day
        int brandSales = dayBrandSales(day, cube, i);
        if (brandSales  > max) {// check which brand has the max sales
            max = brandSales ;
            biggestBrandIndex = i; // Update the index of the best-selling brand
        }
    }
    printf("\nThe best sold brand with %d sales was %s\n", max, brands[biggestBrandIndex]);
}
// Function to determine and print the best-selling car type on a specific day
void bestSoldType(
    int day,
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],
    char types[NUM_OF_TYPES][TYPES_NAMES]){
    int max=0,biggerTypeIndex=0;
    for (int i = 0; i < NUM_OF_TYPES; i++) {
        // using the function to get total sales for the brand type on the given day
        int typeSales = dayTypeSales(day, cube, i);
        if (typeSales > max) {// check which brand type has the max sales
            max = typeSales;
            biggerTypeIndex= i; // Update the index of the best-selling type
        }
    }
    printf("\nThe best sold type with %d sales was %s\n" ,max,types[biggerTypeIndex]);
}
// Function to print all sales data for all brands up to the current day
void printer(int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int day) {
    for (int i = 0; i < NUM_OF_BRANDS; i++) {
        printf("Sales for %s:\n",brands[i]); // Print the brand name
        for (int j = 0; j <= day; j++) {
            // Print the sales data for each car type on a specific day (SUV, Sedan, Coupe, GT)
            printf("Day %d- SUV: %d Sedan: %d Coupe: %d GT: %d\n",
                j+ARRAY_DAY,
                cube[j][i][TYPE_0],
                cube[j][i][TYPE_1],
                cube[j][i][TYPE_2],
                cube[j][i][TYPE_3]);
        }
    }
}
// Function to print the most sold car brand overall
void mostSoldBrand(int day,
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],
    char brands[NUM_OF_BRANDS][BRANDS_NAMES]){
    // Array to store total sales for each brand
    int brandSales[NUM_OF_BRANDS]={0};
    int max=0, pos=0;
    for (int k = 0;k < day; k++) {
        for (int i = 0; i < NUM_OF_BRANDS; i++) {
            // Add the sales for the specific brand on day
            brandSales[i]+=(dayBrandSales(k,cube,i));
        }
    }
    // Loop through the brand sales to find the most sold brand
    for (int j = 0; j < NUM_OF_TYPES; j++) {
        if (brandSales[j] > max) {
            max = brandSales[j];// Update the maximum sales value
            pos = j; // Store the position (brand) of the most sold brand
        }
    }
    printf("The best-selling brand overall is %s: %d$  \n",brands[pos] ,max);
}
// Function to print the most sold car type overall
void mostSoldType(
    int day,
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],
    char types[NUM_OF_TYPES][TYPES_NAMES]){
    // Array to store total sales for each type
    int typeSales[NUM_OF_TYPES]={0};
    int max=0,pos=0;
    for (int k = 0;k < day; k++) {
        for (int i = 0; i < NUM_OF_TYPES; i++) {
            // Add the sales for the specific type on day
            typeSales[i]+=(dayTypeSales(k,cube,i));
        }
    }
    // Loop through the type sales to find the most sold brand
    for (int j = 0; j < NUM_OF_TYPES; j++) {
        if (typeSales[j] > max) {
            max = typeSales[j];// Update the maximum sales value
            pos = j; // Store the position (type) of the most sold brand
        }
    }
    printf("The best-selling type of car is %s: %d$  \n",types[pos],max);
}
// Function to print the most profitable day
void mostProfitableDay(int day,int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]) {
    int dayProfit1 =0;
    int max=0,pos=0;
    for (int k = 0;k < day; k++) {
        // Get the total sales for day
        dayProfit1=totalSalesPerDay(k,cube);
        // If the total sales for day is higher than the current max, update max and pos
        if (dayProfit1 > max) {
            max = dayProfit1;
            pos++;
        }
    }
    printf("The most profitable day was day number %d: %d$  \n",pos,max);
}
// Function to calculate the average delta (change in sales) for a specific brand
float deltaAverageProvider(
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],
    int day,
    int brandIndex){
    int todayProfit=0,yesterdayProfit=0;
    float avg=0;
    int denominator=0;
    for (int k = ARRAY_DAY;k <= day; k++) {
        int yesterday=k-ARRAY_DAY;
        yesterdayProfit=dayBrandSales(yesterday,cube,brandIndex); // Get the sales for yesterday
        todayProfit=dayBrandSales(k,cube,brandIndex); // Get the sales for that day
        avg+= (todayProfit- yesterdayProfit); // Calculate the difference in sales and add it to avg
        denominator++;// Count the number of days for which we have data
    }
    avg=avg/denominator;// Calculate the average delta by dividing the total change by the number of days
    return avg;
}

int main() {
    int cube[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    int days[NUM_OF_BRANDS] = {0};
    int setBrand[NUM_OF_BRANDS]= {0};
    int choice;
    int day=0,day1=0,day2=0,day3=0,day4=0,day5=0;
    setMinusOne(cube);
    printMenu(); // Display the main menu
    scanf("%d", &choice);
    //If the user enters a number that does not appear in the login menu
    if ((choice < addOne)||(choice > done)) {
        printf("Invalid Choice\n");
        printMenu();        // Display the menu and get user input
        scanf("%d", &choice);
    }
    while(choice != done){
        switch(choice) {
            case addAll: {
                withOutValue(setBrand,brands); // Show brands with missing data
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    while (setBrand[i] == 0) {
                        // If sales data is missing for this brand, prompt user to enter the data
                        enterBrandSales(cube,days,i,day,setBrand);
                    }
                }
                clearSetBrand(setBrand); // Clear the setBrand array after entering data for all brands
                day++; // move to the next day
                break;
            }
            case stats: {
                printf("What day would you like to analyze?\n");
                scanf("%d", &day1);
                // Validate the day input to ensure it's within valid range
                while(day1>DAYS_IN_YEAR||(day1<0)||(day1>day)) {
                    printf("Please enter a valid day.\n");
                    printf("What day would you like to analyze?\n");
                    scanf("%d", &day1);
                }
                day2=day1-ARRAY_DAY;// Adjust the day based on the array offset
                printf("In day number %d:\n",day1);
                printf("The sales total was %d\n",totalSalesPerDay(day2,cube));// Print the total sales for the day
                bestSoldBrand(day2,cube,brands);// Print the best-selling brand for that day
                bestSoldType(day2,cube,types);// Print the best-selling car type for that day
                break;
            }
            case print:{
                printf("*****************************************\n");
                day3= day-ARRAY_DAY;// Adjust the day based on the array offset
                printer(cube,day3);// print the sales data
                printf("*****************************************\n");
                break;
            }
            case insights: {
                day4=day-ARRAY_DAY;// Adjust the day based on the array offset
                mostSoldBrand(day,cube,brands);// Print the most sold brand
                mostSoldType(day,cube,types);// Print the most sold type
                mostProfitableDay(day4,cube);// Print the most profitable day
                break;
            }
            case deltas: {
                day5=day-ARRAY_DAY;// Adjust the day based on the array offset
                for (int i = 0; i < NUM_OF_BRANDS; i++) {
                    //print the average sales delta
                    printf("Brand: %s, Average Delta: %f\n",brands[i],deltaAverageProvider(cube,day5,i));
                }
                break;
            }
            default:
                printf("Invalid input\n");
            }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}


