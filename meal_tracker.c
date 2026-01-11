#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


typedef enum{
    MAIN_MEAL, SIDE_MEAL, SNACK, DESSERT, BEVERAGE
}MealType;

typedef struct{
    
    char name[64];
    char description[256];
    MealType type; // 0 = MAIN MEAL, 1 = SIDE MEAL, 2 = SNACK, 3 = DESSERT, 4 = BEVERAGE
    int cals;    
}Meal;

typedef struct{

    Meal meal;
    int time; //TODO will need to be updated for time.h
}Entry;

typedef struct{
    
    Entry *entries_array;
    size_t count;
    size_t capacity;     
}Entries;
    
Meal create_meal();
void add_entry(Entries *entries);
void print_array(Entries *entries);
void write_changes(Entries *entries);
void read_file(Entries *entries);

const char* ENTRY_FORMAT_OUT = "(%d|%s|%s|%d|%d)\n"; //TODO check this, change to reflect value from time.h.
const char* ENTRY_FORMAT_IN = "(%d|%65[^|]|%257[^|]|%d|%d)\n";
const int ARRAY_DEFAULT_CAPACITY = 4;
const size_t ARRAY_RESIZE_VALUE = 2;


int main(void){
    
    int running = true;
    Entries entries = {0};
    entries.capacity = ARRAY_DEFAULT_CAPACITY;
    entries.entries_array = malloc(entries.capacity * sizeof(Entry));
    read_file(&entries);
        
    while(running){
        
        int menu_select;
        printf("select: 1 to add entries, 2 to write data, or 3 to quit.\n> ");
        scanf("%d", &menu_select);
        
        if(menu_select == 3){
            
            printf("\ngoodbye.\n");
            running = false;
        }
        
        else if(menu_select == 1){
            
            system("clear");
            printf("you chose to add a new food.\n\n");
            add_entry(&entries);
            
            system("clear");
            print_array(&entries);
        }
        
        else if(menu_select == 2){
            
            printf("Writing new data: \n");
            print_array(&entries);
            write_changes(&entries);
        }
        
        else{
            
            printf("invalid selection.\n\n");
        }    
    }
    
    free(entries.entries_array);
    entries.entries_array = NULL;
    entries.count = 0;
    entries.capacity = 0;
    
    return 0;
}


Meal create_meal(void){
    
    char buffer[256];
    Meal hold;
        
    getchar();
    
    printf("\nEnter the name of the meal: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strncpy(hold.name, buffer, sizeof(hold.name) - 1);
    hold.name[sizeof(hold.name) - 1] = '\0';
        
    buffer[0] = '\0'; 
        
    printf("\nEnter the description of the meal: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strncpy(hold.description, buffer, sizeof(hold.description) - 1);
    hold.description[sizeof(hold.description) - 1] = '\0';
        
    buffer[0] = '\0';
        
    int type;
    printf("\nWhat type of meal is this? (0 = main meal, 1 = side meal, 2 = snack, 3 = dessert, 4 = beverage)\n> ");
    scanf("%d", &type);
    while (type < 0 || type > 4) {
        printf("Invalid. Enter 0-4: ");
        scanf("%d", &type);
    }
    hold.type = type;
        
    int cals;
    printf("\nHow many calories are in this meal?: ");
    scanf("%d", &cals);
    hold.cals = cals;
    
    return hold;
}

void add_entry(Entries *entries){
    
    size_t new_appends;
    printf("how many entries would you like to add?\n> ");
    scanf("%zu", &new_appends);
    
    //check to see if array must be resized. does so if necessary, then adds new entries_array.
    size_t required_capacity = entries->count + new_appends;
    if(required_capacity > entries->capacity){
        
        while(entries->capacity < required_capacity){
            
            entries->capacity *= ARRAY_RESIZE_VALUE;
        }
        
        entries->entries_array = realloc(entries->entries_array, entries->capacity * sizeof(Entry));
        printf("\nmax capacity reached. resized to %zu.\n", entries->capacity);
    }
    
    for(size_t i = 0; i < new_appends; i++){
    
        Meal hold = create_meal();
        
        Entry entry;
        entry.meal = hold;
        entry.time = 1; //TODO implement time.h
        entries->entries_array[entries->count+i] = entry; 
    }
    
    entries->count += new_appends;
}


void print_array(Entries *entries){

    printf("\nThe array currently has %zu elements:\n", entries->count);
    for(size_t i = 0; i < entries->count; i++){
        
        printf("\n%s: %d cals.\ndescription: %s\ntime: %d\n",
        entries->entries_array[i].meal.name, 
        entries->entries_array[i].meal.cals, 
        entries->entries_array[i].meal.description,
        entries->entries_array[i].time);
    }
    
    printf("\n");
}


void write_changes(Entries *entries){

    //const char* ENTRY_FORMAT_OUT = "(%d|%s|%s|%d|%d)\n"; TODO check this, change to reflect value from time.h.
    
    FILE *file_food_entries;
    file_food_entries = fopen("food_entries.txt", "w");
    
    Entry temp_entry;
    Meal temp_meal;

    for(size_t i = 0; i < entries->count; i++){
        
        temp_entry = entries->entries_array[i];
        temp_meal = temp_entry.meal;
        
        fprintf(file_food_entries, ENTRY_FORMAT_OUT,
        temp_entry.time, 
        temp_meal.name,
        temp_meal.description,
        temp_meal.type,
        temp_meal.cals
        );
    }
    
    fclose(file_food_entries);
    printf("write successful.\n");
}


void read_file(Entries *entries){

    FILE *file_food_entries;
    file_food_entries = fopen("food_entries.txt", "r");    
    if(file_food_entries){      

        Entry temp_entry;
        Meal *temp_meal = &temp_entry.meal;
        
        while(fscanf(file_food_entries, ENTRY_FORMAT_IN,
        &temp_entry.time,
        temp_meal->name,
        temp_meal->description,
        &temp_meal->type,
        &temp_meal->cals) != EOF){
                
            if(entries->count >= entries->capacity){
                
                entries->capacity *= ARRAY_RESIZE_VALUE;
                entries->entries_array = realloc(entries->entries_array, entries->capacity * sizeof(Entry));
            }
            
            entries->entries_array[entries->count++] = temp_entry;
        }
    
        fclose(file_food_entries);
        printf("read from file successfully.\n");
        print_array(entries);
    }
}












