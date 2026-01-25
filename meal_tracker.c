#include "types.h"
#include "meal_io.h"
#include "array_manip.h"
#include "array_display.h"

#include <stdlib.h>
#include <stdio.h>

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
        printf("The foods you have entered today are:");
        print_array_verbose(&entries, DAY, SKIP_OK);
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
            
            puts("\ngoodbye.\n");
            running = false;
        }
        
        else if(menu_select == 1){
            
            system("clear");
            puts("you chose to add a new food.\n");
            add_entry(&entries);
        }
        
        else if(menu_select == 2){
            
            print_array_concise(&entries, NO_FILTER, DONT_SKIP_OK);            
        }
        
        else{
        
            system("clear");
            puts("invalid selection.\n\n");
        }    
    }
    
    free(entries.entries_array);
    entries.entries_array = NULL;
    entries.count = 0;
    entries.capacity = 0;
    
    return 0;
}













