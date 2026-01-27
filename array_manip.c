#include "types.h"
#include "array_manip.h"

#include <string.h>

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
    
    clear_screen();
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
