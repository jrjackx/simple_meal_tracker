#ifndef TYPES_H
#define TYPES_H

#define ARRAY_RESIZE_VALUE 2
#define ARRAY_DEFAULT_CAPACITY 4;

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum{
    MAIN_MEAL, SIDE_MEAL, SNACK, DESSERT, BEVERAGE
}MealType;

typedef enum{
    NO_FILTER, DAY, WEEK, MONTH, YEAR
}ArrayFilter;

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

static inline void clear_screen(void){
    
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


#endif
