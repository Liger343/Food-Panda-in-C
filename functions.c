#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_RESTAURANTS 50
#define MAX_FOOD_ITEMS 5

typedef char String[31]; //30 Characters + NULL Terminator
typedef char String_contact[13]; //8 or 11 Characters + NULL Terminator
typedef char Decision[10]; //Decision based Input Strings

//Data Structures
typedef struct 
{
    String resto_name; //Unique
    String location; //Non - Unique
    String_contact contact_number; //Non - Unique
    String food_category; //Non - Unique

    float minPrice, maxPrice; //Price Range

    String serving_mode[2]; //[A] Dine - In [B] Take Out
    String store_status; //[A] Open [B] Closed [C] Defunct
    String payment_mode[2]; //[A] Cash [B] E-Cash
    String popular_foods[MAX_FOOD_ITEMS];

    String admin_username, admin_password;

    int searching_criteria, play_music;

} Restaurant_Info;

//User Mode Function Definitions
int load_database_file();
void load_default_restos();
void load_directory();
void user_mode_menu();
int simple_search();
int simple_searching_algorithm(int simple_search_type);
void display_applicable_restaurants(int index);
void display_all_restaurants();

//Multiple Search Function Definitions
void multiple_search_menu();
void search_location();
void search_price();
void search_store_status();


//Admin Mode Main Menus
void admin_mode_menu(int login_attempt);
void create_restaurant();
void update_restaurant();
void delete_restaurant();
void file_saving();
void settings_menu();
void play_music();


/*create_restaurant() associated functions */
void create_name(Restaurant_Info *r); //Unique
void create_location(Restaurant_Info *r); //No Restrictions
void create_contact_number(Restaurant_Info *r); //Unique
void create_serving_mode (Restaurant_Info *r, int count); //Non - Unique
void create_payment_mode (Restaurant_Info *r, int count); //Non - Unique
void create_food_category (Restaurant_Info *r); //No Restrictions
void price_range(Restaurant_Info *r); //Non - Unique
void create_popular_foods (Restaurant_Info *r); //Unique (Popular Food Names can't be duplicated)
void create_store_status (Restaurant_Info *r); //Non Unique

/*update_restaurant() associated functions*/
void update_name(int entry);
void update_location(int entry);
void update_contact_number (int entry);
void update_serving_mode (int entry);
void update_payment_mode (int entry);
void update_food_category (int entry);
void update_price_range (int entry);
void update_popular_foods (int entry);
void update_store_status (int entry);

/*delete_entry() associated functions*/
/*Helper Functions*/
int prevent_digits(char string[]); //Checks if a string that needs to be only letters contains digits (returns 1 if a character as a digit is detected)
int prevent_letters(char string[]); //Checks if a string that needs to be only digits contains letters (returns 1 if a character as part of the alphabet is detected)


