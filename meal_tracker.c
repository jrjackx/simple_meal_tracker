#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>


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
    time_t time;
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

const char* ENTRY_FORMAT_OUT = "(%ld|%s|%s|%d|%d)\n";
const char* ENTRY_FORMAT_IN = "(%ld|%65[^|]|%257[^|]|%d|%d)\n";
const int ARRAY_DEFAULT_CAPACITY = 4;
const size_t ARRAY_RESIZE_VALUE = 2;


int main(void){
    
    int running = true;
    Entries entries = {0};
    entries.capacity = ARRAY_DEFAULT_CAPACITY;
    entries.entries_array = malloc(entries.capacity * sizeof(Entry));
    if(!entries.entries_array){
        
        fprintf(stderr, "error: starting memory allocation failed\n");
        return 1;
    }
    read_file(&entries);
        
    while(running){
        
        int menu_select; //TODO make view entries more robust. shows overview information, allows user to select for more detailed info.
        printf("select: 1 to add new entries, 2 to view the entries, or 3 to quit.\n> "); //TODO checks times. prints out entries added on current day.
        scanf("%d", &menu_select);
        
        if(menu_select == 3){
            
            system("clear");            
            char write;
            getchar();
            printf("\nwould you like to write changes? [Y/n]: ");
            scanf("%c", &write);
            if(write == 'y' || write == 'Y'){
                write_changes(&entries);
            }
            
            printf("\ngoodbye.\n");
            running = false;
        }
        
        else if(menu_select == 1){
            
            system("clear");
            printf("you chose to add a new food.\n\n");
            add_entry(&entries);
            
            Entry new_entry = entries.entries_array[entries.count-1];
            char *new_entry_time = ctime(&new_entry.time);
            
            printf("new food added: \n"); //TODO this will be removed when the program displays today's entries automatically in print_array
            printf("\n%s: %d cals.\ndescription: %s\ntime: %s\n\n",
            new_entry.meal.name, 
            new_entry.meal.cals, 
            new_entry.meal.description,
            new_entry_time);
        }
        
        else if(menu_select == 2){
            
            system("clear");
            print_array(&entries);
        }
        
        else{
        
            system("clear");
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
    
    printf("\nenter the name of the meal: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strncpy(hold.name, buffer, sizeof(hold.name) - 1);
    hold.name[sizeof(hold.name) - 1] = '\0';
        
    buffer[0] = '\0'; 
        
    printf("\nenter the description of the meal: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strncpy(hold.description, buffer, sizeof(hold.description) - 1);
    hold.description[sizeof(hold.description) - 1] = '\0';
        
    buffer[0] = '\0';
        
    int type;
    printf("\nwhat type of meal is this? (0 = main meal, 1 = side meal, 2 = snack, 3 = dessert, 4 = beverage)\n> ");
    scanf("%d", &type);
    while (type < 0 || type > 4) {
        printf("invalid. Enter 0-4: ");
        scanf("%d", &type);
    }
    hold.type = type;
        
    int cals;
    printf("\nhow many calories are in this meal?: ");
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
        
        Entry *temp = realloc(entries->entries_array, entries->capacity * sizeof(Entry));
        if(!temp){
            fprintf(stderr, "error: memory reallocation failed\n");
            return;
        }       
        entries->entries_array = temp;
    }
    
    for(size_t i = 0; i < new_appends; i++){
    
        Meal hold = create_meal();
        
        Entry entry;
        entry.meal = hold;
        entry.time = time(NULL);
        entries->entries_array[entries->count+i] = entry; 
    }
    
    entries->count += new_appends;
}


void print_array(Entries *entries){
    
    printf(" \nThe array currently has %zu elements:\n", entries->count);
    for(size_t i = 0; i < entries->count; i++){
        
        time_t now = now = entries->entries_array[i].time;;
        char *string_now = ctime(&now);        
        
        printf("\n%s: %d cals.\ndescription: %s\ntime: %s\n",
        entries->entries_array[i].meal.name, 
        entries->entries_array[i].meal.cals, 
        entries->entries_array[i].meal.description,
        string_now);
    }
    
    printf("\n");
}


void write_changes(Entries *entries){
    
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
                Entry *temp = realloc(entries->entries_array, entries->capacity * sizeof(Entry));
                if(!temp){
                    fprintf(stderr, "error: memory reallocation failed\n");
                    return;
                }       
                entries->entries_array = temp;
            }
            
            entries->entries_array[entries->count++] = temp_entry;
        }
    
        fclose(file_food_entries);
        printf("read from file successfully.\n");
    }
}












