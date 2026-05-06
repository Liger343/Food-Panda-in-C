#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <mmsystem.h>
#include "functions.c"

#define MAX_RESTAURANTS 50
#define MAX_FOOD_ITEMS 5
#define DATABASE "restaurant_database.dat"
#define ATTEMPT 5
#define USD_PHP 59.76
#define YEN_PHP 0.38
#define YUAN_PHP 8.75
#define TAIWAN_PHP 1.89

//Global Variables
Restaurant_Info restaurants[MAX_RESTAURANTS] = {0}; //Admin Mode / Database Array of Structs
Restaurant_Info r;
int resto_count = 0; 
int search_mode = 0; //1 -> Simple, 2 -> Multiple 
int simple_search_type = 0; 

//Non Unique Criteria Variables
int resto_indices[MAX_RESTAURANTS] = {0};
int index_count = 0;

void load_default_restos()
{
    resto_count = 0;

    //First Element Information of the Array of Structs
    strcpy(restaurants[resto_count].resto_name, "JPJ Sisig Haus");
    strcpy(restaurants[resto_count].location, "Pegasus, Manila");
    strcpy(restaurants[resto_count].contact_number, "091767696969");
    
    strcpy(restaurants[resto_count].serving_mode[0], "Yes");
    strcpy(restaurants[resto_count].serving_mode[1], "No");

    strcpy(restaurants[resto_count].payment_mode[0], "Yes");
    strcpy(restaurants[resto_count].payment_mode[1], "No");

    strcpy(restaurants[resto_count].store_status, "Open");
    restaurants[resto_count].minPrice = 150;
    restaurants[resto_count].maxPrice = 350;
    strcpy(restaurants[resto_count].food_category, "Filipino");

    strcpy(restaurants[resto_count].popular_foods[0], "Monster Sisig");
    strcpy(restaurants[resto_count].popular_foods[1], "Crispy Chicharon Sisig");
    strcpy(restaurants[resto_count].popular_foods[2], "NA");   
    
    resto_count++;

    //Second Element Information of the Array of Structs
    strcpy(restaurants[resto_count].resto_name, "Natty's Ice Cream");
    strcpy(restaurants[resto_count].location, "Telibert, Paranaque");
    strcpy(restaurants[resto_count].contact_number, "0923123987");
    
    strcpy(restaurants[resto_count].serving_mode[0], "Yes");
    strcpy(restaurants[resto_count].serving_mode[1], "Yes");

    strcpy(restaurants[resto_count].payment_mode[0], "No");
    strcpy(restaurants[resto_count].payment_mode[1], "Yes");

    strcpy(restaurants[resto_count].store_status, "Closed");
    restaurants[resto_count].minPrice = 50;
    restaurants[resto_count].maxPrice = 900;
    strcpy(restaurants[resto_count].food_category, "Italian");

    strcpy(restaurants[resto_count].popular_foods[0], "Sticky Gelato");
    strcpy(restaurants[resto_count].popular_foods[1], "Banana Split");
    strcpy(restaurants[resto_count].popular_foods[2], "Cheng's Cheesecake");
    strcpy(restaurants[resto_count].popular_foods[3], "NA");   

    resto_count++;

    //Third Element Information of the Array of Structs
    strcpy(restaurants[resto_count].resto_name, "MunaRamen");
    strcpy(restaurants[resto_count].location, "Ver, Makati");
    strcpy(restaurants[resto_count].contact_number, "0967123456");
    
    strcpy(restaurants[resto_count].serving_mode[0], "No");
    strcpy(restaurants[resto_count].serving_mode[1], "Yes");

    strcpy(restaurants[resto_count].payment_mode[0], "Yes");
    strcpy(restaurants[resto_count].payment_mode[1], "Yes");

    strcpy(restaurants[resto_count].store_status, "Open");
    restaurants[resto_count].minPrice = 230;
    restaurants[resto_count].maxPrice = 500;
    strcpy(restaurants[resto_count].food_category, "Japanese");

    strcpy(restaurants[resto_count].popular_foods[0], "Munar's Soy Ramen");
    strcpy(restaurants[resto_count].popular_foods[1], "Aaronian Gyoza");
    strcpy(restaurants[resto_count].popular_foods[2], "Casta Fried Rice");
    strcpy(restaurants[resto_count].popular_foods[3], "De Lusty Pork Ramen");
    strcpy(restaurants[resto_count].popular_foods[4], "NA");

    resto_count++;

    //Fourth Element Information of the Array of Structs
    strcpy(restaurants[resto_count].resto_name, "Dangcazesty");
    strcpy(restaurants[resto_count].location, "Flores, Muntilupa");
    strcpy(restaurants[resto_count].contact_number, "81234576");
    
    strcpy(restaurants[resto_count].serving_mode[0], "Yes");
    strcpy(restaurants[resto_count].serving_mode[1], "Yes");

    strcpy(restaurants[resto_count].payment_mode[0], "Yes");
    strcpy(restaurants[resto_count].payment_mode[1], "No");

    strcpy(restaurants[resto_count].store_status, "Closed");
    restaurants[resto_count].minPrice = 300;
    restaurants[resto_count].maxPrice = 650;
    strcpy(restaurants[resto_count].food_category, "Korean");

    strcpy(restaurants[resto_count].popular_foods[0], "Zesty Galbi Jim");
    strcpy(restaurants[resto_count].popular_foods[1], "Hard Kimbaps");
    strcpy(restaurants[resto_count].popular_foods[2], "Dangca Fried Rice");
    strcpy(restaurants[resto_count].popular_foods[3], "NA");

    resto_count++;

    //Fifth Element Information of the Array of Structs
    strcpy(restaurants[resto_count].resto_name, "KLJ Seafood Buffet");
    strcpy(restaurants[resto_count].location, "Pegasus, Manila");
    strcpy(restaurants[resto_count].contact_number, "09122567877");
    
    strcpy(restaurants[resto_count].serving_mode[0], "Yes");
    strcpy(restaurants[resto_count].serving_mode[1], "Yes");

    strcpy(restaurants[resto_count].payment_mode[0], "Yes");
    strcpy(restaurants[resto_count].payment_mode[1], "Yes");

    strcpy(restaurants[resto_count].store_status, "Open");
    restaurants[resto_count].minPrice = 400;
    restaurants[resto_count].maxPrice = 800;
    strcpy(restaurants[resto_count].food_category, "Chinese");

    strcpy(restaurants[resto_count].popular_foods[0], "Yuri's Creamy Crabs");
    strcpy(restaurants[resto_count].popular_foods[1], "Buttered Oysters");
    strcpy(restaurants[resto_count].popular_foods[2], "Sticky Fried Rice");
    strcpy(restaurants[resto_count].popular_foods[3], "Lucious A5 Pork");
    strcpy(restaurants[resto_count].popular_foods[4], "Kya Seafood Pasta");

    resto_count++;

    //Default Admin Mode Username, Password, and Music
    strcpy(restaurants[0].admin_username, "Creamy Shit");
    strcpy(restaurants[0].admin_password, "Apex Legends Sucks");
    restaurants[0].play_music = 1;

}

int load_database_file()
{
    FILE *fp = fopen(DATABASE, "rb");
    long fileSize;
    if (fp == NULL)
    {
        printf("Error: File Not Detected\n");
        return 1;
    }

    size_t count = fread(restaurants, sizeof(Restaurant_Info), MAX_RESTAURANTS, fp); //Valid number of records
    fclose(fp);

    //Load in the data into the Directory (Array of Structs)
    resto_count = count;
    return 0;
}

void load_directory()
{
    // For now, load the database locally
    FILE *database_file;

    database_file = fopen(DATABASE, "rb");
    if (database_file)
    {
        printf("Loading Database\n");
        load_database_file();
    }
    else
    {
        printf("No Database File Detected. Loading Preset Restaurants\n");
        load_default_restos();
    }
}

void user_mode_menu()
{
    /* Load Pre-Existing Database for the Directory
        1. If file is NOT found -> Access function that has contains the pre-existing Data
        2. If file is found -> Access file and store it in struct Restaurant_Info
    */
    String user_input;
    Restaurant_Info temp;
    int index;
    while (1)
    {
        printf("Welcome to the MS FOOD Directory User Mode\n");
        printf("Available Choices: \n");
        printf("[1] Simple Search\n");
        printf("[2] Multiple Search\n");
        printf("[3] Load All Restaurants\n");
        printf("[0] Exit to Main Menu\n");
        printf("Your Choice: ");
        fgets(user_input, sizeof(user_input), stdin);
        user_input[strcspn(user_input, "\n")] = '\0';

        if (strlen(user_input) > 0)
        {
            if (strcasecmp(user_input, "1") == 0 || strcasecmp(user_input, "Simple") == 0 || strcasecmp(user_input, "Simple Search") == 0)
            {
                search_mode = 1;
                simple_search_type = simple_search(temp);
                index = simple_searching_algorithm(simple_search_type);
                display_applicable_restaurants(index);
                break;
            }
            else if (strcasecmp(user_input, "2") == 0 || strcasecmp(user_input, "Multiple") == 0 || strcasecmp(user_input, "Multiple Search") == 0)
            {
                search_mode = 2;
                multiple_search_menu();
                break;
            }
            else if (strcasecmp(user_input, "3") == 0 || strcasecmp(user_input, "Load") == 0)
            {
                search_mode = 3;
                display_all_restaurants();
                break;
            }
            else if (strcasecmp(user_input, "0") == 0 || strcasecmp(user_input, "Exit") == 0)
            {
                printf("Exiting to Main Menu\n");
                break;
            }
            else
            {
                printf("Error: Invalid Choice Selected\n");
            }

        }
        else
        {
            printf("Error: No Choice Detected\n");
        }
    }
}

int simple_search(Restaurant_Info r)
{
    char user_choice[3];
    
    while (1)
    {
        printf("Welcome to MS Food Directory: Simple Search Category\n");
        printf("[1] Restaurant Name\n[2] Location\n[3] Contact Number\n[4] Serving Mode\n[5] Payment Mode\n[6] Food Category\n[7] Store Status\n[8] Price Range\n");
        printf("Your Choice: ");
        fgets (user_choice, sizeof(user_choice), stdin);
        user_choice[strcspn(user_choice, "\n")] = '\0';

        if (sscanf(user_choice, "%d", &r.searching_criteria) == 1)
        {
            if (r.searching_criteria >= 1 && r.searching_criteria <= 8)
            {
                break;
            }
            else
            {
                printf("Error: Invalid Choice Detected\n");
            }
        }
        else
        {
            printf("Error: No Input Detected\n");

        }
    }

    return r.searching_criteria;
}

int simple_searching_algorithm(int searching_criteria)
{   
    //Target Information
    String target_resto_name;
    String target_location;
    String_contact target_contact_number;
    String target_food_category;
    String price_range_string;

    float minPrice, maxPrice;

    String target_serving_mode, final_targetservingmode[2];
    String store_status;
    String target_payment_mode, final_targetpaymentmode[2];

    int index = -999; //Only for parameters that are unique to all restaraunts (Name, Contact Number)
    int count = 0;


    switch (searching_criteria)
    {
        case 1: //Search by Restaurant Name (Unique Search Criteria)
        {
            resto_info:
            printf("Enter Restaurant Name: ");
            fgets(target_resto_name, sizeof(target_resto_name), stdin);
            target_resto_name[strcspn(target_resto_name, "\n")] = '\0';

            simple_search_type = 1;

            if (strlen(target_resto_name) == 0)
            {
                printf("Error: No Restaurant Name\n");
                goto resto_info;
            }

            for (int i = 0; i < resto_count; i++)
            {
                if (strcasecmp(target_resto_name, restaurants[i].resto_name) == 0)
                {
                    index = i;
                    return index;
                }
            }

            break;
        }
        case 2: //Search by Location (Non Unique Search Criteria)
        {
            location_info:
            printf("Enter Location: ");
            fgets(target_location, sizeof(target_location), stdin);
            target_location[strcspn(target_location, "\n")] = '\0';

            simple_search_type = 2;

            if (strlen(target_location) == 0)
            {
                printf("Error: No Location\n");
                goto location_info;
            }

            for (int i = 0; i < resto_count; i++)
            {
                if (strcasecmp(target_location, restaurants[i].location) == 0)
                {
                    resto_indices[count] = i;
                    count++;
                }
            }
            index_count = count;
            break;
        }
        case 3: //Search by Contact Number (Unique Search Criteria)
        {
            contact_number_info:
            printf("Enter Restaurant Contact Number: ");
            fgets(target_contact_number, sizeof(target_contact_number), stdin);
            target_contact_number[strcspn(target_contact_number, "\n")] = '\0';

            simple_search_type = 3;
            
            if (strlen(target_contact_number) == 0)
            {
                printf("Error: No Contact Number\n");
                goto contact_number_info;
            }
            if (strlen(target_contact_number) == 8 || strlen(target_contact_number) == 11)
            {
                for (int i = 0; i < resto_count; i++)
                {
                    if (strcasecmp(target_contact_number, restaurants[i].contact_number) == 0)
                    {
                        index = i;
                        return index;
                    }
                }
            }

            break;
        }
        case 4: //Search by Serving Mode (Non Unique Search Criteria)
        {
            serving_combo:
            printf("Dine - In and Take - Out combo: ");
            fgets(target_serving_mode, sizeof(target_serving_mode), stdin);
            target_serving_mode[strcspn(target_serving_mode, "\n")] = '\0';

            simple_search_type = 4;
            
            if (sscanf(target_serving_mode, "%s %s", final_targetservingmode[0], final_targetservingmode[1]) == 2)
            {
                for (int i = 0; i < resto_count; i++)
                {
                    if (strcasecmp(final_targetservingmode[0], restaurants[i].serving_mode[0]) == 0 && strcasecmp(final_targetservingmode[1], restaurants[i].serving_mode[1]) == 0)
                    {
                        resto_indices[count] = i;
                        count++;
                    }
                }
                index_count = count;
                break;
            }
            else
            {
                printf("Error: Incomplete Information\n");
                goto serving_combo;
            }
            break;
        }
        case 5: //Search by Payment Mode (Non Unique Search Criteria)
        {
            simple_search_type = 5;
            payment_info:
            printf("Payment Combo: ");
            fgets(target_payment_mode, sizeof(target_payment_mode), stdin);
            target_payment_mode[strcspn(target_payment_mode, "\n")] = '\0';

            if (sscanf(target_payment_mode, "%s %s", final_targetpaymentmode[0], final_targetpaymentmode[1]) == 2)
            {
                for (int i = 0; i < resto_count; i++)
                {
                    if (strcasecmp(final_targetpaymentmode[0], restaurants[i].payment_mode[0]) == 0 && strcasecmp(final_targetpaymentmode[1], restaurants[i].payment_mode[1]) == 0)
                    {
                        resto_indices[count] = i;
                        count++;
                    }
                }
                index_count = count;
                break;
            }
            else
            {
                printf("Error: Incomplete Inofrmation\n");
                goto payment_info;
            }   
            break;
        }
        case 6: //Search by Food Category (Non - Unique Searching Criteria)
        {
            simple_search_type = 6;
            category_info:
            printf("Food Category: ");
            fgets(target_food_category, sizeof(target_food_category), stdin);
            target_food_category[strcspn(target_food_category, "\n")] = '\0';

            if (strlen(target_food_category) > 0)
            {
                for (int i = 0; i < resto_count; i++)
                {
                    if (strcasecmp(target_food_category, restaurants[i].food_category) == 0)
                    {
                        resto_indices[count] = i;
                        count++;
                    }
                }
                index_count = count;
                break;
            }
            else
            {
                printf("Error: No Food Category Detected\n");
                goto category_info;
            }
            break;
        }
        case 7: //Search by Store Status (Non - Unique Searching Criteria)
        {
            simple_search_type = 7;
            status_info:
            printf("Store Status: ");
            fgets(store_status, sizeof(store_status), stdin);
            store_status[strcspn(store_status, "\n")] = '\0';

            if (strcasecmp(store_status, "Open") == 0 || strcasecmp(store_status, "A") == 0 || strcasecmp(store_status, "Closed") == 0 || strcasecmp(store_status, "B") == 0 || strcasecmp(store_status, "Defunct") == 0 || strcasecmp(store_status, "C") == 0)
            {
                for (int i = 0; i < resto_count; i++)
                {
                    if (strcasecmp(store_status, restaurants[i].store_status) == 0)
                    {
                        resto_indices[count] = i;
                        count++;
                    }
                }
                index_count = count;
                break;
            }
        }
        case 8: //Search by Price Range (Non - Unique Searching Criteria)
        {
            simple_search_type = 8;
            price_info:
            printf("Enter Minimum and Maximum Price Range: ");
            fgets(price_range_string, sizeof(price_range_string), stdin);
            price_range_string[strcspn(price_range_string, "\n")] = '\0';
            
            if (sscanf(price_range_string, "%f %f", &minPrice, &maxPrice) == 2)
            {
                if (minPrice >= maxPrice)
                {
                    printf("Error: Invalid Price Range\n");
                    goto price_info;
                }
                else
                {
                    for (int i = 0; i < resto_count; i++)
                    {
                        if (minPrice == restaurants[i].minPrice && maxPrice == restaurants[i].maxPrice)
                        {
                            resto_indices[count] = i;
                            count++;
                        }
                    }
                    index_count = count;
                    break;
                }
            }
            else
            {
                printf("Error: Incomplete Price Range\n");
                goto price_info;
            }

        }
    } //End of Main Switch Statement

    return index;
}

void display_applicable_restaurants(int index)
{
    String decision; //Expand Restaurant in a Unique Search Criteria

    //Non Unique Search Criteria
    String back_to_row_list; //Go back to row satisfying Non Unique Search Criteria
    char row_edit[3]; //Row to expand in string 
    int row_edit_val = 0; //Row to expand in integer form

    if (simple_search_type == 1 || simple_search_type == 3) //Unique Search Criteria
    {
        if (index != -999)
        {
            printf("Restaurant: %s Located\n", restaurants[index].resto_name);
            printf("Expand Information? [Yes] [No]: ");
            fgets(decision, sizeof(decision), stdin);
            decision[strcspn(decision, "\n")] = '\0';

            printf("%45s\n", "=============================================");

            if (strcasecmp(decision, "Yes") == 0)
            {
                printf("Restaurant Name: %s\n", restaurants[index]. resto_name);
                printf("Location: %s\n", restaurants[index].location);
                printf("Contact Number: %s\n", restaurants[index].contact_number);
                printf("Dine - In: %s || Take - Out: %s\n", restaurants[index].serving_mode[0], restaurants[index].serving_mode[1]);
                printf("Cash: %s || E - Cash: %s\n", restaurants[index].payment_mode[0], restaurants[index].payment_mode[1]);
                printf("Food Category: %s\n", restaurants[index].food_category);
                printf("Price Range: %.2f - %.2f PHP\n", restaurants[index].minPrice, restaurants[index].maxPrice);
                printf("Store Status: %s\n", restaurants[index].store_status);
                printf("Popular Foods\n");

                for (int j = 0; strcasecmp(restaurants[index].popular_foods[j], "NA") != 0 && j < MAX_FOOD_ITEMS; j++)
                {
                    printf("[%d] %s\n", j+1, restaurants[index].popular_foods[j]);
                }
            }
            else 
            {
                printf("Thank you for searching!\n");
            }
        }
        else
        {
            printf("Error: Restaurant not Found\n");
        }
    }
    else //Non Unique Search Criteria
    {
        if (index_count != 0)
        {
            row_list: 
            for (int i = 0; i < index_count; i++)
            {
                printf("[%d] %s\n", i+1, restaurants[resto_indices[i]].resto_name);
            }
            
            do
            {
                printf("Choose Row to Expand: ");
                fgets(row_edit, sizeof(row_edit), stdin);
                row_edit[strcspn(row_edit, "\n")] = '\0';

                printf("%45s\n", "=============================================");

                if (sscanf(row_edit, "%d", &row_edit_val) == 1)
                {
                    if (row_edit_val >= 1 && row_edit_val <= index_count)
                    {
                        printf("Restaurant Name: %s\n", restaurants[resto_indices[row_edit_val - 1]]. resto_name);
                        printf("Location: %s\n", restaurants[resto_indices[row_edit_val - 1]].location);
                        printf("Contact Number: %s\n", restaurants[resto_indices[row_edit_val - 1]].contact_number);
                        printf("Dine - In: %s || Take - Out: %s\n", restaurants[resto_indices[row_edit_val - 1]].serving_mode[0], restaurants[resto_indices[row_edit_val - 1]].serving_mode[1]);
                        printf("Cash: %s || E - Cash: %s\n", restaurants[resto_indices[row_edit_val - 1]].payment_mode[0], restaurants[resto_indices[row_edit_val - 1]].payment_mode[1]);
                        printf("Food Category: %s\n", restaurants[resto_indices[row_edit_val - 1]].food_category);
                        printf("Price Range: %.2f - %.2f PHP\n", restaurants[resto_indices[row_edit_val - 1]].minPrice, restaurants[resto_indices[row_edit_val - 1]].maxPrice);
                        printf("Store Status: %s\n", restaurants[resto_indices[row_edit_val - 1]].store_status);
                        printf("Popular Foods\n");

                        for (int j = 0; strcasecmp(restaurants[resto_indices[row_edit_val - 1]].popular_foods[j], "NA") != 0 && j < MAX_FOOD_ITEMS; j++)
                        {
                            printf("[%d] %s\n", j+1, restaurants[resto_indices[row_edit_val - 1]].popular_foods[j]);
                        }

                    }
                    else
                    {
                        printf("Error: Invalid Row to Expand\n");
                    }
                }
                else
                {
                    printf("Error: No Row Detected to Expand\n");
                }
            } while (sscanf(row_edit, "%d", &row_edit_val) != 1 || row_edit_val < 1 || row_edit_val > index_count + 1);

            //Explore other detected restaurants
            printf("Go back to Restaurants Row? [Yes] [No]: ");
            fgets(back_to_row_list, sizeof(back_to_row_list), stdin);
            back_to_row_list[strcspn(back_to_row_list, "\n")] = '\0';

            if (strcasecmp(back_to_row_list, "Yes") == 0)
            {
                row_edit_val = -999;
                goto row_list;
            }
            else
            {
                printf("Exiting to Main Menu\n");
            }

            
        }
        else 
        {
            printf("Error: Restaurant not Found\n");
        }
    }
}

void display_all_restaurants()
{
    String expand_row, decision;
    int isValid = 0, row_num, stop_loop = 0;
    printf("Total No. of Restaurants: %d\n", resto_count);
    
    do
    {
        for (int i = 0; i < resto_count; i++)
        {
            printf("[%d]: %s\n", i+1, restaurants[i].resto_name);
        }
        
        printf("Select Row to Expand [1 - %d]: ", resto_count);
        fgets(expand_row, sizeof(expand_row), stdin);
        expand_row[strcspn(expand_row, "\n")] = '\0';

        if (sscanf(expand_row, "%d", &row_num) == 1)
        {
            if (row_num == 0)
            {
                printf("Exiting Restaurants Row....\n");
                isValid = 1;
            }
            else if (row_num >= 1 && row_num <= resto_count)
            {
                printf("Entry Number: %d\n", row_num);
                printf("Name: %s\n", restaurants[row_num - 1].resto_name);
                printf("Location: %s\n", restaurants[row_num - 1].location);
                printf("Contact Number: %s\n", restaurants[row_num - 1].contact_number);
                printf("Dine In: %s || Take Out: %s\n", restaurants[row_num - 1].serving_mode[0], restaurants[row_num - 1].serving_mode[1]);
                printf("Cash: %s || E-Cash: %s\n", restaurants[row_num - 1].payment_mode[0], restaurants[row_num - 1].payment_mode[1]);
                printf("Food Category: %s\n", restaurants[row_num - 1].food_category);
                printf("Price Range: %.2f - %.2f PHP\n", restaurants[row_num - 1].minPrice, restaurants[row_num - 1].maxPrice);
                printf("Store Status: %s\n", restaurants[row_num - 1].store_status);

                for (int i = 0; !stop_loop; i++)
                {
                    if (i == MAX_FOOD_ITEMS || strcasecmp(restaurants[row_num - 1].popular_foods[i], "NA") == 0)
                    {
                        stop_loop = 1;
                    }
                    else
                    {
                        printf("Popular Food [%d]: %s\n", i+1, restaurants[row_num - 1].popular_foods[i]);
                    }
                }

                printf("Go Back to Restaurants Row? ");
                fgets(decision, sizeof(decision), stdin);
                decision[strcspn(decision, "\n")] = '\0';

                if (strcasecmp(decision, "No") == 0 || strstr(decision, "N"))
                {
                    printf("Exiting Restaurants Row....\n");
                    isValid = 1;
                }

                stop_loop = 0;
            }
            else
            {
                printf("Error: Invalid Row\n");
            }
        }
        else
        {
            printf("Error: No Row Selected\n");
        }

    } while (!isValid);
    
}

void multiple_search_menu()
{
    String location, price, store_status, currency;
    float minPrice, maxPrice;
    int isValid = 0, currency_int = 0;

    printf("MS FOOD Directory: Multiple Search Mode\n");

    do
    {
        printf("Enter Location: ");
        fgets(location, sizeof(location), stdin);
        location[strcspn(location, "\n")] = '\0';

        printf("Enter Price Range: ");
        fgets(price, sizeof(price), stdin);

        printf("Store Status [A] Open [B] Closed [C] Defunct: ");
        fgets(store_status, sizeof(store_status), stdin);
        store_status[strcspn(store_status, "\n")] = '\0';

        if (strlen(location) > 0 && strlen(price) > 0 && strlen(store_status))
        {
            if (sscanf(price, "%f %f", &minPrice, &maxPrice) == 2)
            {
                if (minPrice >= maxPrice)
                {
                    printf("Error: Invalid Price Range\n");
                }
                else
                {
                    printf("Supported Currencies: [1] USD, [2] YUAN, [3] YEN, [4] NTD\n");
                    printf("Enter Currency: ");
                    fgets(currency, sizeof(currency), stdin);
                    currency[strcspn(currency, "\n")] = '\0';

                    if (strlen(currency) > 0 || sscanf(currency, "%d", &currency_int) == 1)
                    {
                        if (strcasecmp(currency, "USD") == 0 || currency_int == 1)
                        {
                             
                        }
                        else if (strcasecmp(currency, "Yuan") == 0 || currency_int == 2)
                        {

                        }
                        else if (strcasecmp(currency, "Yen") == 0 || currency_int == 3)
                        {

                        }

                        //Searching Algorithm
                    }
                    else
                    {
                        printf("No Currency Detected. Defaulting to PHP as Currency\n");
                    }
                }
            }
            else
            {
                printf("Error: Price Range is NOT complete\n");
            }
        }
        else
        {
            printf("Exiting Multiple Search....\n");
            isValid = 1;
        }

    } while (!isValid);
    
}

//End of User Mode Functions
/*============================================================================================================================================================*/

//Admin Mode Functions
void admin_mode_menu(int login_attempt)
{
    String admin_username, admin_password, settings_decision;
    String edit_login_choice;
    String admin_mode_type; 
    int admin_mode_type_int = 0; //1 -> Create Entry, 2 -> Edit Entry, 3 -> Delete Entry, 4 -> Settings Menu
    int isValid = 0;
    for (int i = 0; i < ATTEMPT; i++)
    {
        if (!login_attempt)
        {
            printf("Enter Admin Username: ");
            fgets(admin_username, sizeof(admin_username), stdin);
            admin_username[strcspn(admin_username, "\n")] = '\0';

            printf("Enter Admin Password: ");
            fgets(admin_password, sizeof(admin_password), stdin);
            admin_password[strcspn(admin_password, "\n")] = '\0';

            if (strcmp(admin_username, restaurants[0].admin_username) != 0 || strcmp(admin_password, restaurants[0].admin_password) != 0)
            {
                printf("Error: Invalid Username or Password\n");
                printf("%d attempts remaining\n", ATTEMPT - (i + 1));

                if (i == 2)
                {
                    printf("Change Username and Password [Yes] [No]: ");
                    fgets(settings_decision, sizeof(settings_decision), stdin);
                    settings_decision[strcspn(settings_decision, "\n")] = '\0';

                    if (strlen(settings_decision) > 0)
                    {
                        if (strcasecmp(settings_decision, "Yes") == 0 || strstr(settings_decision, "Y") || strcasecmp(settings_decision, "1") == 0)
                        {
                            settings_menu();
                        }
                    }

                }
            }
            else
            {
                isValid = 1;
                break;
            }
        }
        else //Admin already logged in before hand
        {
            isValid = 1;
            break;
        }
    }

    if (isValid)
    {
        printf("Welcome to MS FOOD Directory Admin Mode!\n");

        while (admin_mode_type_int < 1 || admin_mode_type_int > 5)
        {
            printf("[1] Create Entry\n[2] Update Entry\n[3] Delete Entry\n[4] File Saving\n[5] Settings Menu\n[6] Exit to Main Menu\nType: ");
            fgets(admin_mode_type, sizeof(admin_mode_type), stdin);
            admin_mode_type[strcspn(admin_mode_type, "\n")] = '\0';

            if (sscanf(admin_mode_type, "%d", &admin_mode_type_int) == 1)
            {
                if (admin_mode_type_int < 1 || admin_mode_type_int > 6)
                {
                    printf("Error: Invalid Type selected\n");
                }
            }
            else
            {
                printf("Error: No Type selected\n");
            }

        }

        switch (admin_mode_type_int)
        {
            case 1:
            {
                if (resto_count < MAX_RESTAURANTS)
                {
                    create_restaurant();
                }
                else
                {
                    printf("Error: Database is already Full\n");
                }
                
                break;
            }
            case 2:
            {
                update_restaurant();
                break;
            }
            case 3:
            {
                delete_restaurant();
                break;
            }
            case 4:
            {
                file_saving();
                break;
            }
            case 5:
            {
                settings_menu();
                break;
            }
            default:
            {
                printf("Leaving Admin Mode...\n");
                break;
            }
        }
    }
    else
    {
        printf("Exiting to Admin Main Menu...\n");
    }
}

/*Create Restaurant Entry Code Segment*/
void create_name (Restaurant_Info *r) 
{
    int i = 0;
    int isValid = 0, detect_same_name;
    String new_restaurant_name;

    do
    {
        detect_same_name = 0;
        printf("Enter Restaurant Name: ");
        fgets(new_restaurant_name, sizeof(new_restaurant_name), stdin);
        new_restaurant_name[strcspn(new_restaurant_name, "\n")] = '\0';

        for (int j = 0; j < resto_count && !detect_same_name; j++)
        {
            if (strcasecmp(new_restaurant_name, restaurants[j].resto_name) == 0)
            {
                printf("Error: Restaurant Name: %s, already exists\n", new_restaurant_name);
                detect_same_name = 1;

            }
            else
            {
                strncpy(r->resto_name, new_restaurant_name, strlen(new_restaurant_name));
                isValid = 1;
            }
        }

    } while (!isValid);

    printf("Restaurant Name: %s has been sucessfully created\n", new_restaurant_name);
    
}
void create_location (Restaurant_Info *r)
{
    printf("Enter Location: ");
    fgets(r->location, sizeof(r->location), stdin);
    r->location[strcspn(r->location, "\n")] = '\0';

    printf("Restaurant Location: %s has been sucessfully created\n", r->location);
}
void create_contact_number(Restaurant_Info *r)
{
    String_contact number; //Contact Number as a string (8 or 11 digits)
    long long contact_number; //Contact Number as an integer (long long as numbers in the Philippines go beyond the range of a standard 32 bit integer)
    int num_valid = 0;
    int first_digits = 0; 

    do
    {
        printf("Enter Contact Number: ");
        fgets(number, sizeof(number), stdin);
        number[strcspn(number, "\n")] = '\0';

        if (sscanf(number, "%lld", &contact_number) != 1)
        {
            printf("Error: No Contact Number Detected\n");
        }
        else
        {
            if (strlen(number) < 8 || strlen(number) > 11)
            {
                printf("Error: Invalid Contact Number\n");
            }
            else
            {
                first_digits = contact_number / 10000000;
                if (strlen(number) == 8)
                {
                    if (first_digits == 3 || first_digits == 5 || first_digits == 6 || first_digits == 7 || first_digits == 8)
                    {
                        num_valid = 1;
                    }
                }
                else if (strlen(number) == 11)
                {
                    if (first_digits >= 905 || first_digits <= 999)
                    {
                        num_valid = 1;
                    }
                }
            }

            if (num_valid)
            {
                printf("Restaurant Contact Number: %s has been successfully created\n", number);
                strcpy(r->contact_number, number);
            }
            else if (!num_valid)
            {
                printf("Error: Invalid Contact Number\n");
            }
        }

    } while (!num_valid);
    
}
void create_serving_mode (Restaurant_Info *r, int count) 
{
    String create_serving_mode;
    char temp;
    int isValid_mode = 0;

    //Initialize state of Dine In and Take Out Support of Restaurant
    strcpy(r->serving_mode[0], "No"); //Serving Mode 1: Dine In 
    strcpy(r->serving_mode[1], "No"); //Serving Mode 2: Take Out 

    do
    {   
        starting_info:
        printf("Dine In: [A] Yes [B] No: ");
        fgets(create_serving_mode, sizeof(create_serving_mode), stdin);
        create_serving_mode[strcspn(create_serving_mode, "\n")] = '\0';

        if (sscanf(create_serving_mode, "%c", &temp) == 1)
        {
            temp = toupper(temp);
            switch (temp)
            {
                case 'A':
                {
                    strcpy(r->serving_mode[0], "Yes");
                    break;
                }
                case 'B':
                {
                    break;
                }
                default:
                {
                    printf("Error: Invalid Serving Mode 1\n");
                    goto starting_info;
                    break;
                }

            }

            printf("Take Out: [A] Yes [B] No: ");
            fgets(create_serving_mode, sizeof(create_serving_mode), stdin);
            create_serving_mode[strcspn(create_serving_mode, "\n")] = '\0';

            if (sscanf(create_serving_mode, "%c", &temp) == 1)
            {
                temp = toupper(temp);
                switch (temp)
                {
                    case 'A':
                    {
                        strcpy(r->serving_mode[1], "Yes");
                        isValid_mode = 1;
                        break;
                    }
                    case 'B':
                    {
                        isValid_mode = 1;
                        break;
                    }
                    default:
                    {
                        printf("Error: Invalid Serving Mode 2\n");
                        break;
                    }
                }
            }
            else
            {
                printf("Error: No Input for Serving Mode 2\n");
            }
        }
        else
        {
            printf("Error: No Input for Serving Mode 1\n");
        }

    } while (!isValid_mode);   
}
void create_payment_mode (Restaurant_Info *r, int count)
{
    String create_payment_mode;
    char temp;
    int isValid = 0;

    //Initialize States of Payment Modes
    strcpy(r->payment_mode[0], "No");
    strcpy(r->payment_mode[1], "No");

    do
    {
        starting_payment_info:
        printf("Cash [A] Yes [B] No: ");
        fgets(create_payment_mode, sizeof(create_payment_mode), stdin);
        create_payment_mode[strcspn(create_payment_mode, "\n")] = '\0';

        if (sscanf(create_payment_mode, "%c", &temp) == 1)
        {
            temp = toupper(temp);
            switch (temp)
            {
                case 'A':
                {
                    strcpy(r->payment_mode[0], "Yes");
                    isValid = 1;
                    break;
                }
                case 'B':
                {
                    isValid = 1;
                    break;
                }
                default:
                {
                    printf("Error: Invalid Serving Mode 1\n");
                    goto starting_payment_info;
                    break;
                }
            }

            printf("E-Cash [A] Yes [B] No: ");
            fgets(create_payment_mode, sizeof(create_payment_mode), stdin);
            create_payment_mode[strcspn(create_payment_mode, "\n")] = '\0';

            if (sscanf(create_payment_mode, "%c", &temp) == 1)
            {
                temp = toupper(temp);
                switch (temp)
                {
                    case 'A':
                    {
                        strcpy(r->payment_mode[1], "Yes");
                        isValid = 1;
                        break;
                    }
                    case 'B':
                    {
                        isValid = 1;
                        break;
                    }
                    default:
                    {
                        printf("Error: Invalid Serving Mode 2\n");
                        break;
                    }
                }
            }
            else
            {
                printf("Error: No Input for Payment Mode 2\n");
            }
        }
        else
        {
            printf("Error: No Input for Payment Mode 1\n");
        }
    } while (!isValid);
    
}
void create_food_category (Restaurant_Info *r)
{
   int isValid = 0;
   
    do
    {
        printf("Enter Food Category: ");
        fgets(r->food_category, sizeof(r->food_category), stdin);
        r->food_category[strcspn(r->food_category, "\n")] = '\0';

        if (strlen(r->food_category) == 0)
        {
            printf("Error: No Food Category Inputted\n");
        }
        else
        {
            isValid = 1;
        }
    } while (!isValid);
   


}
void price_range (Restaurant_Info *r)
{
    String price_range, currency;
    float minPrice = 0, maxPrice = 0;

    do
    {
        printf("Enter Currency: ");
        fgets(currency, sizeof(currency), stdin);
        currency[strcspn(currency, "\n")] = '\0';

        printf("Enter Price Range: ");
        fgets(price_range, sizeof(price_range), stdin);
        price_range[strcspn(price_range, "\n")] = '\0';

        if (sscanf(price_range, "%f %f", &minPrice, &maxPrice) == 2)
        {
            //Check Currency
            if (strcasecmp(currency, "USD") == 0) //US Dollars to Philippine Peso
            {
                minPrice = minPrice * USD_PHP;
                maxPrice = maxPrice * USD_PHP;
            }
            else if (strcasecmp(currency, "YEN") == 0) //Japanese Yen to Philippine Peso
            {
                minPrice = minPrice * YEN_PHP;
                maxPrice = maxPrice * YEN_PHP;
            }
            else if (strcasecmp(currency, "YUAN") == 0) //Chinese Yuan to Philippine Peso
            {
                minPrice = minPrice * YUAN_PHP;
                maxPrice = maxPrice * YUAN_PHP;
            }
            else if (strcasecmp(currency, "TAIWAN DOLLARS") == 0 || strstr(currency, "TAI") || strcasecmp(currency, "TD") == 0) //Taiwan Dollars to Philippine Peso
            {
                minPrice = minPrice * TAIWAN_PHP;
                maxPrice = maxPrice * TAIWAN_PHP;
            }

            //Check Validity of Price Range
            if (minPrice >= maxPrice)
            {
                printf("Error: Invalid Price Range\n");
            }
        }
        else
        {
            printf("Error: Incomplete Price Range\n");
        }
    } while (minPrice >= maxPrice);

    //Store Inputs
    r->minPrice = minPrice;
    r->maxPrice = maxPrice;
}
void create_popular_foods (Restaurant_Info *r)
{
    String popular_food_name;
    String temp_array_strings[5]; //Temporary Array of Strings
    int keep_adding = 1, count = 0; //keep_adding -> Flag Variable (Always has a value of 1 until NA is typed as Popular Food Name), count -> counting variable (Must be less than 5)
    int i = 0;
    do
    {
        int stop_loop = 0;
        printf("Enter Popular Food %d: ", count + 1);
        fgets(popular_food_name, sizeof(popular_food_name), stdin);
        popular_food_name[strcspn(popular_food_name, "\n")] = '\0';

        if (strlen(popular_food_name) > 0)
        {
            //Check for Duplicate Popular Food Names
            for (int i = 0; i < count && !stop_loop; i++)
            {
                if (strcasecmp(popular_food_name, r->popular_foods[i]) == 0)
                {
                    printf("Error: Popular Food Name [%s] already exists at selection %d\n", r->popular_foods[i], r->popular_foods[count]);
                    stop_loop = 1;
                }
                else if (strcasecmp(popular_food_name, "NA") == 0)
                {
                    i = count; //Stops Inner For Loop
                    keep_adding = 0; //Stops Outer do-while loop
                }
            }
        }
        else
        {
            printf("Error: No Popular Food Input\n");
        }

        if (!stop_loop)
        {
            strcpy(r->popular_foods[count], popular_food_name);
            count++;
        }
    } while (keep_adding && count < 5);

    printf("Number of Popular Foods: %d\n", count);
}
void create_store_status (Restaurant_Info *r)
{
    String store_status;
    int stop_loop = 0;

    do
    {
        printf("Enter Store Status [A] Open [B] Closed [C] Defunct: ");
        fgets(store_status, sizeof(store_status), stdin);
        store_status[strcspn(store_status, "\n")] = '\0';

        if (strlen(store_status) > 0)
        {
            if (strcasecmp(store_status, "Open") == 0 || strcasecmp(store_status, "A") == 0 || strstr(store_status, "Op"))
            {
                strcpy(r->store_status, "Open");
                stop_loop = 1;
            }
            else if (strcasecmp(store_status, "Closed") == 0 || strcasecmp(store_status, "B") == 0 || strstr(store_status, "Cl"))
            {
                strcpy(r->store_status, "Closed");
                stop_loop = 1;
            }
            else if (strcasecmp(store_status, "Defunct") == 0 || strcasecmp(store_status, "C") == 0 || strstr(store_status, "De"))
            {
                strcpy(r->store_status, "Defunct");
                stop_loop = 1;
            }
            else
            {
                printf("Error: Invalid Status\n");
            }
        }
        else
        {
            printf("Error: No Store Status Inputted\n");
        }
    } while (!stop_loop);
    

}
void create_restaurant()
{
    Restaurant_Info temp; //Temporary Struct Variable
    String decision;

    int stop_loop = 0;

    printf("ADMIN MODE: CREATE RESTAURANT\n");
    do
    {
        printf("Entry Number: %d\n", resto_count + 1);
        create_name(&temp);
        create_location (&temp);
        create_contact_number (&temp);
        create_serving_mode (&temp, resto_count);
        create_payment_mode (&temp, resto_count);
        create_food_category(&temp);
        price_range(&temp);
        create_popular_foods(&temp);

        restaurants[resto_count] = temp; //Save the Created Restaurant in an element (resto_count) within the Array of Structs: restaurants
        resto_count++; //Add One more to the total restaurant count to save new entry

        //Review Entry Information
        printf("Collected Entry Information\n");
        printf("Name: %s\n", temp.resto_name);
        printf("Location: %s\n", temp.location);
        printf("Contact Number: %s\n", temp.contact_number);
        printf("Dine In: %s || Take Out: %s\n", temp.serving_mode[0], temp.serving_mode[1]);
        printf("Cash: %s || E-Cash: %s\n", temp.payment_mode[0], temp.payment_mode[1]);
        printf("Food Category: %s\n", temp.food_category);
        printf("Price Range: %.2f PHP - %.2f PHP\n", temp.minPrice, temp.maxPrice);

        for (int i = 0; i < MAX_FOOD_ITEMS && !stop_loop; i++)
        {
            if (strcasecmp(temp.popular_foods[i], "NA") == 0)
            {
                stop_loop = 1;
            }
            else
            {
                printf("Popular Food %d: %s\n", i+1, temp.popular_foods[i]);
            }
        }

        printf("Continue Creating Entries [Yes] [No]: ");
        fgets(decision, sizeof(decision), stdin);
        decision[strcspn(decision, "\n")] = '\0';

        if (strcasecmp(decision, "No") == 0)
        {
            printf("Exiting Create Restaurant....\n");
        }
    } while (strcasecmp(decision, "No") != 0);
    
    printf("Number of Records: %d\n", resto_count);  

}

/*Update Restaurant Entry Code Segment*/
void update_restaurant()
{
    String row, detail; 
    Decision continue_update_string;

    int row_select = 0, continue_updates = 1, detail_select, stop_outer_loop = 0;
    int stop_loop = 0;

    printf("ADMIN MODE: UPDATE RESTAURANT\n");
    printf("Restaurant Entries: \n");
    do
    {
        for (int i = 0; i < resto_count; i++)
        {
            printf("[%d] %s\n", i+1, restaurants[i].resto_name);
        }

        printf("Enter Row to Expand: ");
        fgets(row, sizeof(row), stdin);
        row[strcspn(row, "\n")] = '\0';

        if (sscanf(row, "%d", &row_select) == 1)
        {
            if (row_select <= 0 || row_select > resto_count)
            {
                printf("Error: Row %d is out of bounds\n", row_select);
            }
            else
            {
                printf("Available Details\n[1] Name [2] Location [3] Contact Number [4] Serving Mode [5] Payment Mode [6] Food Category [7] Payment Mode [8] Store Status [9] Popular Foods\n");
                printf("%s\n", "=================================================");
                printf("Select Detail: ");
                fgets(detail, sizeof(detail), stdin);
                detail[strcspn(detail, "\n")] = '\0';

                if (sscanf(detail, "%d", &detail_select) == 1)
                {
                    if (detail_select < 1 || detail_select > 9)
                    {
                        printf("Error: Invalid Restaurant Detail\n");
                    }
                    else
                    {
                        switch (detail_select)
                        {
                            case 1:
                            {
                                update_name(row_select);
                                break;
                            }
                            case 2:
                            {
                                update_location(row_select);
                                break;
                            }
                            case 3:
                            {
                                update_contact_number(row_select);
                                break;
                            }
                            case 4:
                            {
                                update_serving_mode(row_select);
                                break;
                            }
                            case 5:
                            {
                                update_payment_mode(row_select);
                                break;
                            }
                            case 6:
                            {
                                update_food_category(row_select);
                                break;
                            }
                            case 7:
                            {
                                update_price_range(row_select);
                                break;
                            }
                            case 8:
                            {
                                update_store_status (row_select);
                                break;
                            }
                            case 9:
                            {
                                update_popular_foods(row_select);
                                break;
                            }
                        }
                    }
                }
                else
                {
                    printf("Error: No Restaurant Detail Selected\n");
                }
            }
        }
        else if (sscanf(detail, "%d", &detail_select) != 1)
        {
            printf("Error: No Row selected\n");
        }

        printf("Continue Updates [1] Yes [2] No: ");
        fgets(continue_update_string, sizeof(continue_update_string), stdin);
        continue_update_string[strcspn(continue_update_string, "\n")] = '\0';

        if (sscanf(continue_update_string, "%d", &continue_updates) == 1 || strlen(continue_update_string) > 0)
        {
            if (continue_updates >= 2 || strcasecmp(continue_update_string, "No") == 0 || strstr(continue_update_string, "N"))
            {
                printf("Exiting Update Restaurant Entry....\n");
                stop_outer_loop = 1;
            }
        }

    } while (!stop_outer_loop);

}

void update_name(int entry)
{
    String new_resto_name;
    int i = 0; //Inner Loop Counter
    int isValid = 0, stop_inner_loop = 0;

    do
    {
        printf("Enter New Restaurant Name: ");
        fgets(new_resto_name, sizeof(new_resto_name), stdin);
        new_resto_name[strcspn(new_resto_name, "\n")] = '\0';

        if (strlen(new_resto_name) > 0)
        {
           do
           {
                if (strcasecmp(new_resto_name, restaurants[i].resto_name) == 0)
                {
                    printf("Error: Restaurant Name %s already exists\n", new_resto_name);
                    stop_inner_loop = 1;
                }
                else
                {
                    isValid = 1;
                }

                i++;
           } while (!stop_inner_loop && i < resto_count);
           
        }
        else
        {
            printf("Error: No New Restaurant Name Detected\n");
        }
    } while (!isValid);

    if (isValid)
    {
        printf("Restaurant Name: %s has been successfully updated\n", new_resto_name);
        strcpy(restaurants[entry - 1].resto_name, new_resto_name);
    }
    
}

void update_location(int entry)
{
    String new_resto_location;
    int i = 0;
    int isValid = 0, stop_inner_loop = 0;

    do
    {
        printf("Enter New Restaurant Location: ");
        fgets(new_resto_location, sizeof(new_resto_location), stdin);
        new_resto_location[strcspn(new_resto_location, "\n")] = '\0';

        if (strlen(new_resto_location) > 0)
        {
            do
            {
                if (strcasecmp(new_resto_location, restaurants[i].location) == 0)
                {
                    printf("Error: Restaurant Location %s already exists\n", new_resto_location);
                    stop_inner_loop = 1;
                }
                else
                {
                    isValid = 1;
                }

                i++;             
            } while (!stop_inner_loop && i < resto_count);
            
        }
        else
        {
            printf("Error: No New Restaurant Location Detected\n");
        }
    } while (!isValid);

    if (isValid)
    {
        printf("Restaurant Location: %s has been successfully updated\n", new_resto_location);
        strcpy(restaurants[entry - 1].location, new_resto_location);
    }
    
}

void update_contact_number(int entry)
{
    String_contact new_contact_number;
    int i = 0;
    int isValid = 0, stop_inner_loop = 0, leading_digits;
    long long new_contact_num;

    do
    {
        printf("New Restaurant Number [8 or 11 Digits]: ");
        fgets(new_contact_number, sizeof(new_contact_number), stdin);
        new_contact_number[strcspn(new_contact_number, "\n")] = '\0';

        if (strlen(new_contact_number) > 0 && sscanf(new_contact_number, "%lld", &new_contact_num) == 1)
        {
            if (strlen(new_contact_number) == 8 || strlen(new_contact_number) == 11)
            {       
                leading_digits = new_contact_num / 10000000;
                if (strlen(new_contact_number) == 8)
                {
                    if (leading_digits == 3 || leading_digits == 5 || leading_digits == 6 || leading_digits == 7 || leading_digits == 8)
                    {
                        do
                        {
                            if (strcasecmp(new_contact_number, restaurants[i].contact_number) == 0)
                            {
                                printf("Error: Contact Number %s already exists\n", new_contact_number);
                                stop_inner_loop = 1;
                            }
                            else
                            {
                                isValid = 1;
                            }
                            i++;
                        } while (!stop_inner_loop && i < resto_count);
                        
                    }
                    else
                    {
                        printf("Error: Invalid Phone Number\n");
                    }    
                }
                else if (strlen(new_contact_number) == 11)
                {
                    if (leading_digits >= 905 || leading_digits <= 999)
                    {
                        do
                        {
                            if (strcasecmp(new_contact_number, restaurants[i].contact_number) == 0)
                            {
                                printf("Error: Contact Number %s already exists\n", new_contact_number);
                                stop_inner_loop = 1;
                            }
                            else
                            {
                                isValid = 1;
                            }
                            i++;
                        } while (!stop_inner_loop && i < resto_count);
                    }
                    else
                    {
                        printf("Error: Invalid Phone Number\n");
                    }
                }
                   
            }
            else
            {
                printf("Error: Invalid Contact Number Length\n");
            }
        }
        else
        {
            printf("Error: No new Contact Number Detected\n");
        }
    } while (!isValid);

    if (isValid)
    {
        printf("Restaurant Contact Number: %s has been successfully updated\n", new_contact_number);
        strcpy(restaurants[entry - 1].contact_number, new_contact_number);
    }
    
}

void update_serving_mode (int entry)
{
    String new_serving_mode, decision;
    char temp;
    int isValid = 0, isValid1 = 0, isValid2 = 0;

    do
    {   
        //Serving Mode 1
        printf("Dine In [A] Yes [B] No: ");
        fgets(new_serving_mode, sizeof(new_serving_mode), stdin);
        new_serving_mode[strcspn(new_serving_mode, "\n")] = '\0';

        if (sscanf(new_serving_mode, "%c", &temp) == 1 || strlen(new_serving_mode) > 0)
        {
            if (temp == 'A' || strcasecmp(new_serving_mode, "Yes") == 0 || strstr(new_serving_mode, "Y"))
            {
                printf("Updating Dine In Support to Yes\n");
                strcpy(restaurants[entry - 1].serving_mode[0], "Yes");
                isValid1 = 1;
            }
            else
            {
                printf("Updating Dine in Support to No\n");
                strcpy(restaurants[entry - 1].serving_mode[0], "No");
                isValid1 = 1;
            }
        }
        else
        {
            printf("Error: No Serving Mode 1 Detected\n");
        }

        //Serving Mode 2
        if (isValid1)
        {
            printf("Take Out [A] Yes [B] No: ");
            fgets(new_serving_mode, sizeof(new_serving_mode), stdin);
            new_serving_mode[strcspn(new_serving_mode, "\n")] = '\0';

            if (sscanf(new_serving_mode, "%c", &temp) || strlen(new_serving_mode) > 0)
            {
                if (temp == 'A' || strcasecmp(new_serving_mode, "Yes") == 0 || strstr(new_serving_mode, "Y"))
                {
                    printf("Updating Take Out Support to Yes\n");
                    strcpy(restaurants[entry - 1].serving_mode[1], "Yes");
                    isValid2 = 1;
                }
                else
                {
                    printf("Updating Dine in Support to No\n");
                    strcpy(restaurants[entry - 1].serving_mode[1], "No");
                    isValid2 = 1;
                }
            }
        }
        else
        {
            printf("Error: No Serving Mode 2 Detected\n");
        }

        //Confirm both Inputs are Valid
        if (isValid1 && isValid2)
        {
            isValid = 1;
        }

    } while (!isValid);
    
}

void update_payment_mode(int entry)
{
    String new_payment_mode, decision;
    char temp; 
    int isValid = 0, isValid1 = 0, isValid2 = 0;

    do
    {
        //Payment Mode 1
        printf("Cash [A] Yes [B] No: ");
        fgets(new_payment_mode, sizeof(new_payment_mode), stdin);
        new_payment_mode[strcspn(new_payment_mode, "\n")] = '\0';

        if (sscanf(new_payment_mode, "%c", &temp) == 1 || strlen (new_payment_mode) > 0)
        {
            if (temp == 'A' || strcasecmp(new_payment_mode, "Yes") == 0 || strstr(new_payment_mode, "Y"))
            {
                printf("Updating Cash Support to Yes\n");
                strcpy(restaurants[entry - 1].payment_mode[0], "Yes");
                isValid1 = 1;
            }
            else 
            {
                printf("Updating Cash Support to No\n");
                strcpy(restaurants[entry - 1].payment_mode[0], "No");
                isValid1 = 1;
            }
        }
        else
        {
            printf("Error: No Payment Mode 1 Detected\n");
        }

        //Payment Mode 2
        if (isValid1)
        {
            printf("E-Cash [A] Yes [B] No: ");
            fgets(new_payment_mode, sizeof(new_payment_mode), stdin);
            new_payment_mode[strcspn(new_payment_mode, "\n")] = '\0';

            if (sscanf(new_payment_mode, "%c", &temp) == 1 || strlen(new_payment_mode) > 0)
            {
                if (temp == 'A' || strcasecmp(new_payment_mode, "Yes") == 0 || strstr(new_payment_mode, "Y"))
                {
                    printf("Updating E-Cash Support to Yes\n");
                    strcpy(restaurants[entry - 1].payment_mode[1], "Yes");
                    isValid2 = 1;
                }
                else
                {
                    printf("Updating E-Cash Support to No\n");
                    strcpy(restaurants[entry - 1].payment_mode[1], "No");
                    isValid2 = 1;
                }
            }
            else
            {
                printf("Error: No Payment Mode 2 Detected\n");
            }
        }

        //Confirm if Both are Valid
        if (isValid1 && isValid2)
        {
            isValid = 1;
        }

    
    } while (!isValid);
    
}

void update_food_category (int entry)
{
    String new_food_category, decision;
    int isValid = 0;

    do
    {
        printf("Enter New Food Category: ");
        fgets(new_food_category, sizeof(new_food_category), stdin);
        new_food_category[strcspn(new_food_category, "\n")] = '\0';

        if (strlen(new_food_category) > 0)
        {
            if (strcasecmp(new_food_category, restaurants[entry - 1].food_category) == 0)
            {
                printf("No Update to Food Category\n");
                if (strcasecmp(decision, "No") == 0 || strstr(decision, "N") || strstr(decision, "Na"))
                {
                    printf("Exiting Update Food Category....\n");
                    isValid = 1;
                }
            }
            else
            {
                printf("Updating Food Category to: %s\n", new_food_category);
                strcpy(restaurants[entry - 1].food_category, new_food_category);
                isValid = 1;
            }
        }
        else
        {
            printf("No Update to Food Category\n");
            printf("Continue? [Yes] [No]: ");
            fgets(decision, sizeof(decision), stdin);
            decision[strcspn(decision, "\n")] = '\0';

            if (strcasecmp(decision, "No") == 0 || strstr(decision, "N") || strstr(decision, "Na"))
            {
                printf("Exiting Update Food Category....\n");
                isValid = 1;
            }

        }
    } while (!isValid);
    
}

void update_price_range (int entry)
{
    String currency, price_range;
    float minPrice, maxPrice;
    int isValid = 0, type_currency = 0; //1 -> USD, 2 -> Japanese Yen, 3 -> Chinese Yuan, 4 -> New Taiwan Dollars, 5 -> Philippine Peso (Include Unsupported Currency which is automatically converted to PHP)

    do
    {
        printf("Enter Currency: ");
        fgets(currency, sizeof(currency), stdin);
        currency[strcspn(currency, "\n")] = '\0';

        if (strlen(currency) > 0 && !prevent_digits(currency))
        {
            //Identify Initial Currency
            if (strcasecmp(currency, "USD") == 0 || strstr(currency, "US") || strcasecmp(currency, "USA") == 0)
            {
                type_currency = 1;
            }
            else if (strcasecmp(currency, "Yen") == 0 || strstr(currency, "Japan") || strstr(currency, "JAP"))
            {
                type_currency = 2;
            }
            else if (strcasecmp(currency, "Yuan") == 0 || strstr(currency, "Chinese") || strstr(currency, "CHI"))
            {
                type_currency = 3;
            }
            else if (strcasecmp(currency, "New Taiwan Dollars") == 0 || strstr(currency, "Taiwan") || strstr(currency, "TAI"))
            {
                type_currency = 4;
            }
            else
            {
                type_currency = 5;
            }

            printf("Enter Price Range: ");
            fgets(price_range, sizeof(price_range), stdin);
            price_range[strcspn(price_range, "\n")] = '\0';

            if (sscanf(price_range, "%f %f", &minPrice, &maxPrice) == 2 && minPrice < maxPrice)
            {
                //Convert to Philippine Peso
                switch (type_currency)
                {
                    case 1: //USD to PHP
                    {
                        minPrice = minPrice * USD_PHP;
                        maxPrice = maxPrice * USD_PHP;
                        break;
                    }
                    case 2: //JPY to PHP
                    {
                        minPrice = minPrice * YEN_PHP;
                        maxPrice = maxPrice * YEN_PHP;
                        break;
                    }
                    case 3: //YUAN to PHP
                    {
                        minPrice = minPrice * YUAN_PHP;
                        maxPrice = maxPrice * YUAN_PHP;
                        break;
                    }
                    case 4: //NTD to PHP
                    {
                        minPrice = minPrice * TAIWAN_PHP;
                        maxPrice = maxPrice * TAIWAN_PHP;
                        break;
                    }
                }

                restaurants[entry - 1].minPrice = minPrice;
                restaurants[entry - 1].maxPrice = maxPrice;

                printf("Updated Price Range in PHP: %.2f - %.2f PHP\n", restaurants[entry - 1].minPrice, restaurants[entry - 1].maxPrice);
                isValid = 1;
            }
            else
            {   
                if (minPrice >= maxPrice)
                {
                    printf("Error: Invalid Price Range\n");
                }
                else
                {
                    printf("Error: Incomplete Price Range");
                }
            }
        }   
        else
        {
            printf("Error: No Currency Inputted\n");
        }
    } while (!isValid);
    
}
void update_store_status (int entry)
{
    String store_status;
    int stop_loop = 0;

    do
    {
        printf("Enter Store Status [A] Open [B] Closed [C] Defunct: ");
        fgets(store_status, sizeof(store_status), stdin);
        store_status[strcspn(store_status, "\n")] = '\0';

        if (strlen(store_status) > 0)
        {
            if (strcasecmp(store_status, "Open") == 0 || strcasecmp (store_status, "A") == 0 || strstr(store_status, "Op"))
            {
                strcpy(restaurants[entry - 1].store_status, "Open");
                stop_loop = 1;
            }
            else if (strcasecmp(store_status, "Closed") == 0 || strcasecmp(store_status, "B") == 0 || strstr(store_status, "Cl"))
            {
                strcpy(restaurants[entry - 1].store_status, "Closed");
                stop_loop = 1;
            } 
            else if (strcasecmp(store_status, "Defunct") == 0 || strcasecmp(store_status, "C") == 0 || strstr(store_status, "De"))
            {
                strcpy(restaurants[entry - 1].store_status, "Defunct");
                stop_loop = 1;
            }
            else
            {
                printf("Error: No Valid Store Status Detected\n");
            }
        }
        else
        {
            printf("Exiting Update Store Status...\n");
            stop_loop = 1;
        }
    } while (!stop_loop);
    
}
void update_popular_foods (int entry)
{
    String row_select, new_popularfood_name, decision;
    
    int stop_outer_loop = 0, stop_inner_loop = 0, flag_existing_name = 0;
    int row_select_integer;

    printf("%s\n", "=================================================");
    do
    {
        //Display Current Popular Food Names
        for (int i = 0; !stop_inner_loop; i++)
        {
            if (i == MAX_FOOD_ITEMS || strcasecmp(restaurants[entry - 1].popular_foods[i], "NA") == 0)
            {
                stop_inner_loop = 1;
            }
            else
            {
                printf("Popular Food [%d]: %s\n", i + 1, restaurants[entry - 1].popular_foods[i]);
            }
        }

        printf("Select Popular Food Item: ");
        fgets(row_select, sizeof(row_select), stdin);
        row_select[strcspn(row_select, "\n")] = '\0';

        if (sscanf(row_select, "%d", &row_select_integer) == 1)
        {
            if (row_select_integer >= 1 && row_select_integer <= 5)
            {
                printf("Enter New Popular Food Name: ");
                fgets(new_popularfood_name, sizeof(new_popularfood_name), stdin);
                new_popularfood_name[strcspn(new_popularfood_name, "\n")] = '\0';

                //Check if the name already exists
                for (int i = 0; !flag_existing_name && i < MAX_FOOD_ITEMS; i++)
                {
                    if (strcasecmp(new_popularfood_name, restaurants[entry - 1].popular_foods[i]) == 0)
                    {
                        flag_existing_name = 1;
                    }
                }

                //Check if the updated popular food name wasn't flagged as existing
                if (!flag_existing_name)
                {
                    printf("Successfully updated Popular Food [%d] to %s\n", row_select_integer, new_popularfood_name);
                    strcpy(restaurants[entry - 1].popular_foods[row_select_integer - 1], new_popularfood_name);
                }

                printf("Continue Updating [1] Yes [2] No: ");
                fgets(decision, sizeof(decision), stdin);
                decision[strcspn(decision, "\n")] = '\0';

                if (strcasecmp(decision, "No") == 0 || strcasecmp(decision, "2") == 0 || strstr(decision, "N"))
                {
                    printf("Exiting Update Popular Foods....\n");
                    stop_outer_loop = 1;
                }

            }
            else
            {
                printf("Error: Invalid Item\n");
            }
        }
        else
        {
            printf("Exiting Update Popular Foods....\n");
            stop_outer_loop = 1;
        }
    } while (!stop_outer_loop);
}

void delete_restaurant()
{
    String entry_select, decision, continue_delete;
    int isValid = 0, entry_number, found_index = -1;

    do
    {
        //Show all Restaurant Entries by Nme
        for (int i = 0; i < resto_count; i++)
        {
            printf("Restaurant Entry [%d]: %s\n", i+1, restaurants[i].resto_name);
        }

        printf("Enter Entry Number: ");
        fgets(entry_select, sizeof(entry_select), stdin);
        entry_select[strcspn(entry_select, "\n")] = '\0';

        if (sscanf(entry_select, "%d", &entry_number) == 1)
        {
            if (entry_number >= 1 && entry_number <= resto_count + 1 && resto_count != 0)
            {
                //Shift all elements from the entry number by one to the left to begin deleting process
                printf("Do you wish to Delete: %s [Yes] [No]: ", restaurants[entry_number - 1].resto_name);
                fgets(continue_delete, sizeof(continue_delete), stdin);
                continue_delete[strcspn(continue_delete, "\n")] = '\0';

                if (strcasecmp(continue_delete, "Yes") == 0 || strcasecmp(continue_delete, "1") == 0 || strstr(continue_delete, "Y"))
                {
                    int continue_algo_loop = 1;
                    printf("Deleting Entry....\n");
                    //Deleting Algorithm
                    //Linear Search Algorithm by Name to find which element the Entry is at in the Array of Structs
                    for (int i = 0; found_index == -1 && continue_algo_loop; i++)
                    {
                        if (i == resto_count || strcasecmp(restaurants[i].resto_name, restaurants[entry_number - 1].resto_name) == 0)
                        {
                            if (strcasecmp(restaurants[i].resto_name, restaurants[entry_number - 1].resto_name) == 0)
                            {
                                found_index = i;
                                continue_algo_loop = 0;
                            }
                        }

                    }

                    if (found_index == -1)
                    {
                        printf("Error: Restaurant is NOT part of entry list\n");
                    }
                    else
                    {
                        for (int j = found_index; j < sizeof(restaurants)/sizeof(restaurants[0]); j++)
                        {
                            restaurants[j] = restaurants[j + 1];
                        }
                        resto_count--;
                    }

                    //Decision
                    printf("Continue Deleting [Yes] [No]: ");
                    fgets(decision, sizeof(decision), stdin);
                    decision[strcspn(decision, "\n")] = '\0';

                    if (strcasecmp(decision, "No") == 0 || strcasecmp(decision, "2") == 0 || strstr(decision, "N"))
                    {
                        printf("Exiting Delete Restaurant....\n");
                        isValid = 1;
                    }
                    else
                    {
                        found_index = -1;
                    }
                }
            }
            else
            {
                if (resto_count == 0)
                {
                    printf("Error: No More Entries to Delete\n");
                    printf("Exiting Delete Restaurant....\n");
                    isValid = 1;
                }
                else
                {
                    printf("Error: Invalid Restaurant Entry\n");
                }
            }
        }
        else
        {
            printf("Exiting Delete Restaurant....\n");
            isValid = 1;
        }

    } while (!isValid);
    
}

void file_saving()
{
    String decision;
    FILE *database_file;

    database_file = fopen(DATABASE, "rb");
    if (database_file)
    {
        printf("Database already exists....\n");
        printf("Overwrite File [Yes] [No]: ");
        fgets(decision, sizeof(decision), stdin);
        decision[strcspn(decision, "\n")] = '\0';

        if (strcasecmp(decision, "Yes") == 0 || strstr(decision, "Y") || strcasecmp(decision, "1") == 0)
        {
            fclose(database_file);
            database_file = fopen(DATABASE, "wb");
            printf("Overwriting File....\n");
            fwrite(restaurants, sizeof(Restaurant_Info), resto_count, database_file);
            fclose(database_file);
        }
    }
    else
    {
        fclose(database_file);
        database_file = fopen(DATABASE, "wb");
        fwrite(restaurants, sizeof(Restaurant_Info), resto_count, database_file);
        fclose(database_file);
        printf("File Saved....\n");
    }

    printf("Exiting File Saving....\n");
}

void settings_menu()
{
    String menu_choice, Username, Password, decision, music_volume;
    int isValid = 0; 

    do
    {
        printf("Choose Settings: [1] Change Username [2] Change Password [3] Background Music: ");
        fgets(menu_choice, sizeof(menu_choice), stdin);
        menu_choice[strcspn(menu_choice, "\n")] = '\0';

        if (strlen(menu_choice) > 0)
        {
            if (strcasecmp(menu_choice, "Username") == 0 || strstr(menu_choice, "User") || strcasecmp(menu_choice, "1") == 0)
            {
                printf("Enter New Username: ");
                fgets(Username, sizeof(Username), stdin);
                Username[strcspn(Username, "\n")] = '\0';

                if (strcasecmp(Username, restaurants[0].admin_username) == 0)
                {
                    printf("Error: Username is the same\n");
                }
                else
                {
                    strcpy(restaurants[0].admin_username, Username);
                    printf("Successfully Updated Username to: %s\n", restaurants[0].admin_username);
                }

            }
            else if (strcasecmp(menu_choice, "Password") == 0 || strstr(menu_choice, "Pass") || strcasecmp(menu_choice, "2") == 0)
            {
                printf("Enter New Password: ");
                fgets(Password, sizeof(Password), stdin);
                Password[strcspn(Password, "\n")] = '\0';

                if (strcasecmp(Password, restaurants[0].admin_password) == 0)
                {
                    printf("Error: Password is the same\n");
                }
                else
                {
                    strcpy(restaurants[0].admin_password, Password);
                    printf("Successfully Updated Password to: %s\n", restaurants[0].admin_password);
                }
            }
            else if (strcasecmp(menu_choice, "Background Music") == 0 || strstr(menu_choice, "B") || strcasecmp(menu_choice, "3") == 0)
            {   
                if (restaurants[0].play_music)
                {
                    printf("Stop Background Music [1] Yes [2] No: ");
                    fgets(music_volume, sizeof(music_volume), stdin);
                    music_volume[strcspn(music_volume, "\n")] = '\0';

                    if (strlen(music_volume) > 0)
                    {
                        if (strcasecmp(music_volume, "Yes") == 0 || strstr(music_volume, "Y") || strcasecmp(music_volume, "1") == 0)
                        {
                            printf("Stopping Music....\n");
                            PlaySound(NULL, NULL, 0);
                            restaurants[0].play_music = 0;
                        }

                    }
                    else
                    {
                        printf("Stopping Music....\n");
                        PlaySound(NULL, NULL, 0);
                        restaurants[0].play_music = 0;
                    }
                }
                else
                {
                    printf("Play Background Music [1] Yes [2] No: ");
                    fgets(music_volume, sizeof(music_volume), stdin);
                    music_volume[strcspn(music_volume, "\n")] = '\0';

                    if (strlen(music_volume) > 0)
                    {
                        if (strcasecmp(music_volume, "Yes") == 0 || strstr(music_volume, "Y") || strcasecmp(music_volume, "1") == 0)
                        {
                            printf("Playing Music....\n");
                            play_music();
                            restaurants[0].play_music = 1;
                        }
                        else
                        {
                            printf("Background Music Remains Off....\n");
                        }

                    }
                    else
                    {
                        printf("Playing Music....\n");
                        play_music();
                        restaurants[0].play_music = 1;
                    }
                }
            }
            else
            {
                printf("Error: Invalid Settings\n");
            }

            printf("Continue Settings Edit [Yes] [No]: ");
            fgets(decision, sizeof(decision), stdin);
            decision[strcspn(decision, "\n")] = '\0';

            if (strlen(decision) > 0)
            {
                if (strcasecmp(decision, "No") == 0 || strstr(decision, "N") || strcasecmp(decision, "2") == 0)
                {
                    printf("Exiting Settings Menu....\n");
                    isValid = 1;
                }
            }
            else
            {
                printf("Exiting Settings Menu....\n");
                isValid = 1;
            }
        }
        else
        {
            printf("Exiting Settings Menu....\n");
            isValid = 1;
        }
    } while (!isValid);
    
}

void play_music()
{
    PlaySound(TEXT("Can't Feel My Face.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

/*End of Admin Mode Functions*/
/*================================================================================================================================================================*/


/*Helper Functions*/
int prevent_digits (char currency[])
{
    for (int i = 0; i < strlen(currency); i++)
    {
        if (isdigit(currency[i]))
        {
            return 1;
        }
    }

    return 0;
}

/*End of Helper Functions*/
/*================================================================================================================================================================*/

#pragma comment(lib, "winnm.lib");

int main()
{
    String user_input, continue_use;
    int target_index = 0, login_attempt = 0;

    load_directory();
    printf("Number of Entries: %d\n", resto_count);

    if (restaurants[0].play_music) //Background Music Engaged by Default
    {
        play_music();
    }

    while (1)
    {
        printf("Welcome to MS FOOD Directory\n");
        printf("Please Select Mode: ");
        printf("[1] User Mode [2] Admin Mode [3] Exit: ");
        fgets(user_input, sizeof(user_input), stdin);
        user_input[strcspn(user_input, "\n")] = '\0';

        if (strlen(user_input) > 0)
        {
            if (strcasecmp(user_input, "1") == 0 || strcasecmp(user_input, "User Mode") == 0 || strcasecmp(user_input, "User") == 0)
            {
                do 
                {
                    user_mode_menu();
                    printf("Continue with User Mode? [Yes] [No]: ");
                    fgets(continue_use, sizeof(continue_use), stdin);
                    continue_use[strcspn(continue_use, "\n")] = '\0';
                } while (strcasecmp(continue_use, "Yes") == 0);
                
                printf("Returning to Starting Menu\n");
            }
            else if (strcasecmp(user_input, "2") == 0 || strcasecmp(user_input, "Admin Mode") == 0 || strcasecmp(user_input, "Admin") == 0)
            {
                do
                {
                    admin_mode_menu(login_attempt);
                    printf("Continue with Admin Mode? [Yes] [No]: ");
                    fgets(continue_use, sizeof(continue_use), stdin);
                    continue_use[strcspn(continue_use, "\n")] = '\0';

                    if (strcasecmp(continue_use, "Yes") == 0)
                    {
                        login_attempt++;
                    }
                } while (strcasecmp(continue_use, "Yes") == 0);
                
                printf("Returning to Starting Menu\n");
            }
            else if (strcasecmp(user_input, "3") == 0 || strcasecmp(user_input, "Exit") == 0)
            {
                printf("Thank you for using MS Food Directory\nExiting......\n");
                break;
            }
            else
            {
                printf("Error: Invalid Mode Selected\n");
            }
        }
        else
        {
            printf("Error: No Mode Selected\n");
        }
    }
    return 0;
}
