#include "types.h"
#include "meal_io.h"


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
        (int*)&temp_meal->type,
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
        printf("read from file successfully.\n\n");
    }
}
