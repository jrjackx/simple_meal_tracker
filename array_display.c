#include "types.h"
#include "array_display.h"


void print_array_verbose(Entries *entries, ArrayFilter filter, Skip skip_ok){
    
    if(skip_ok == DONT_SKIP_OK){clear_screen();}
    
    int total_cals = 0;
    
    time_t now = time(NULL);
    struct tm *filter_time_struct = localtime(&now);
    time_t filtered_time;
    switch(filter){
        case 0: filtered_time = 0; break;
        case 1: filter_time_struct->tm_mday -= 1; filtered_time = mktime(filter_time_struct); break;
        case 2: filter_time_struct->tm_mday -= 7; filtered_time = mktime(filter_time_struct); break;
        case 3: filter_time_struct->tm_mon -= 1; filtered_time = mktime(filter_time_struct); break;
        case 4: filter_time_struct->tm_year -= 1; filtered_time = mktime(filter_time_struct); break;
    }
    
    
    //TODO change "array has" message to have specific logic for understanding day, month, etc.
    printf("\n\n---------------------------\n");
    for(size_t i = entries->count; i > 0; i--){
        
        time_t entry_time = entries->entries_array[i-1].time;
        if(entry_time >= filtered_time){
            
            char *string_entry_time = ctime(&entry_time);        
            total_cals += entries->entries_array[i-1].meal.cals;                
            
            char* meal_type;
            switch(entries->entries_array[i-1].meal.type){
                case 0: meal_type = "main meal"; break;
                case 1: meal_type = "side meal"; break;
                case 2: meal_type = "snack"; break;
                case 3: meal_type = "dessert"; break;
                case 4: meal_type = "beverage"; break;
                default: meal_type = "BROKEN!!!"; break;
            }        
            
            //time, name, calories, description, type
            printf("\n-------------\n%s\n%s: %d cals.\n%s\n%s\n-------------\n",
            string_entry_time,
            entries->entries_array[i-1].meal.name,
            entries->entries_array[i-1].meal.cals, 
            entries->entries_array[i-1].meal.description,
            meal_type); 
        }
        
        
    }
    
    printf("\n---------------------------\nTotal calories: %d cals\n", total_cals);
    
    if(skip_ok == DONT_SKIP_OK){
        char ok;
        puts("\npress any key to continue.");
        getchar();
        scanf("%c",&ok);
        clear_screen();
    }
    
}

void print_array_concise(Entries *entries, ArrayFilter filter, Skip skip_ok){

    if(skip_ok == DONT_SKIP_OK){clear_screen();}
    
    int total_cals = 0;
    
    time_t now = time(NULL);
    struct tm *filter_time_struct = localtime(&now);
    time_t filtered_time;
    switch(filter){
        case 0: filtered_time = 0; break;
        case 1: filter_time_struct->tm_mday -= 1; filtered_time = mktime(filter_time_struct); break;
        case 2: filter_time_struct->tm_mday -= 7; filtered_time = mktime(filter_time_struct); break;
        case 3: filter_time_struct->tm_mon -= 1; filtered_time = mktime(filter_time_struct); break;
        case 4: filter_time_struct->tm_year -= 1; filtered_time = mktime(filter_time_struct); break;
    }
    
    
    //TODO change "array has" message to have specific logic for understanding day, month, etc.
    printf("\n---------------------------\n");
    for(size_t i = entries->count; i > 0; i--){
        
        time_t entry_time = entries->entries_array[i-1].time;
        struct tm *entry_time_struct = localtime(&entry_time);
        char concise_date[16];
        
        if(entry_time >= filtered_time){
            
            strftime(concise_date, 16, "%x: ", entry_time_struct);
            printf("\n%s%s | %d cals.", concise_date, entries->entries_array[i-1].meal.name,
            entries->entries_array[i-1].meal.cals);
      
            total_cals += entries->entries_array[i-1].meal.cals;                            
        }   
    }
    
    printf("\n\n---------------------------\nTotal calories: %d cals\n", total_cals);
    
    if(skip_ok == DONT_SKIP_OK){
        char ok;
        puts("\npress any key to continue.");
        getchar();
        scanf("%c",&ok);
        clear_screen();
    }
}











