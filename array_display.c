#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "array_display.h"

void print_array_verbose(Entries *entries, ArrayFilter filter){
    
    
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
    
    
    //TODO LOOK HERE
    //TODO FIX THIS. flipping the order of scanning the array has caused a ghost entry to appear (december 31st 1969). why?
    printf(" \nThe array currently has %zu elements:\n---------------------------\n", entries->count);
    for(size_t i = entries->count; i > 0; i--){
        
        time_t entry_time = entries->entries_array[i].time;
        if(entry_time >= filtered_time){
            
            char *string_entry_time = ctime(&entry_time);        
            total_cals += entries->entries_array[i].meal.cals;                
            
            char* meal_type;
            switch(entries->entries_array[i].meal.type){
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
            entries->entries_array[i].meal.name,
            entries->entries_array[i].meal.cals, 
            entries->entries_array[i].meal.description,
            meal_type); 
        }
        
        
    }
    
    printf("\n---------------------------\nTotal calories: %d cals\n", total_cals);
    char ok;
    puts("\npress any key to continue.");
    getchar();
    scanf("%c",&ok);
    system("clear");
    
}
