#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct{
    
    char name[64];
    char description[256];
    int type; // 0 = MAIN MEAL, 1 = SIDE MEAL, 2 = SNACK, 3 = DESSERT, 4 = BEVERAGE
    int cals;    
}Meal;

typedef struct{

    Meal meal;
    int time;
}Entry;

typedef struct{
    
    Entry *entries_array;
    size_t count;
    size_t capacity;     
}Entries;
    
Meal create_meal();
void add(Entries *entries);
void print_array(Entries *entries);


int main(void){
    
    int running = true;
    Entries entries = {0};
        
    while(running){
        
        int menu_select;
        printf("select: 1 to add entries, 2 to remove entries, or 3 to quit.\n> ");
        scanf("%d", &menu_select);
        
        if(menu_select == 3){
            
            printf("\ngoodbye.\n");
            running = false;
        }
        
        else if(menu_select == 1){
            
            system("clear");
            printf("you chose to add\n\n");
            add(&entries);
            
            system("clear");
            print_array(&entries);
        }
        
        else if(menu_select == 2){
            
            printf("you chose to remove\n\n");
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


Meal create_meal(){
    
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
    hold.type = type;
        
    int cals;
    printf("\nHow many calories are in this meal?: ");
    scanf("%d", &cals);
    hold.cals = cals;
    
    return hold;
}

void add(Entries *entries){
    
    //starts dynamic array if size is 0 (zero-initialized)
    const int DEFAULT_CAPACITY = 4;
    if(entries->capacity == 0){
        
        entries->capacity = DEFAULT_CAPACITY;
        entries->entries_array = malloc(entries->capacity * sizeof(Entry));
        printf("new dynamic array created!\n");
    }
    
    size_t new_appends;
    printf("how many entries would you like to add?\n> ");
    scanf("%zu", &new_appends);
    
    //check to see if array must be resized. does so if necessary, then adds new entries_array.
    const size_t RESIZE_VALUE = 2;
    size_t required_capacity = entries->count + new_appends;
    if(required_capacity > entries->capacity){
        
        while(entries->capacity < required_capacity){
            
            entries->capacity *= RESIZE_VALUE;
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

    printf("\n\nThe array currently has %zu elements:\n", entries->count);
    for(size_t i = 0; i < entries->count; i++){
        
        printf("\n%s: %d cals.\ndescription: %s\ntime: %d\n",
        entries->entries_array[i].meal.name, 
        entries->entries_array[i].meal.cals, 
        entries->entries_array[i].meal.description,
        entries->entries_array[i].time);
    }
    
    printf("\n");
}





