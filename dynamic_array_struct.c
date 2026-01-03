#include <stdlib.h>
#include <stdio.h>

typedef struct{
    
    int *items;
    size_t count;
    size_t capacity;     
} Numbers;
    
void add(Numbers *xs);
void print_array(Numbers *xs);


int main(void){
    
    int going = 1;
    Numbers xs = {0};
        
    while(going){
        
        int menu_select;
        printf("select: 1 to add numbers, 2 to remove numbers, or 3 to quit.\n> ");
        scanf("%d", &menu_select);
        
        if(menu_select == 3){
            
            printf("\ngoodbye.");
            going = 0;
        }
        
        else if(menu_select == 1){
            
            printf("you chose to add\n\n");
            add(&xs);
            print_array(&xs);
        }
        
        else if(menu_select == 2){
            
            printf("you chose to remove\n\n");
        }
        
        else{
            
            printf("invalid selection.\n\n");
        }    
    }
    
    free(xs.items);
    xs.items = NULL;
    xs.count = 0;
    xs.capacity = 0;
    
    return 0;
}


void add(Numbers *xs){
    
    //starts dynamic array if size is 0 (zero-initialized)
    const int DEFAULT_CAPACITY = 4;
    if(xs->capacity == 0){
        
        xs->capacity = DEFAULT_CAPACITY;
        xs->items = malloc(xs->capacity * sizeof(int));
        printf("new dynamic array created!\n");
    }
    
    size_t new_nums;
    printf("how many numbers would you like to add?\n> ");
    scanf("%zu", &new_nums);
    
    //check to see if array must be resized. does so if necessary, then adds new items.
    const size_t RESIZE_VALUE = 2;
    size_t required_capacity = xs->count + new_nums;
    if(required_capacity > xs->capacity){
        
        while(xs->capacity < required_capacity){
            
            xs->capacity *= RESIZE_VALUE;
        }
        
        xs->items = realloc(xs->items, xs->capacity * sizeof(int));
        printf("\nmax capacity reached. resized to %zu.\n", xs->capacity);
    }
    
    for(size_t i = 0; i < new_nums; i++){
    
        int hold;
        printf("\nenter the value of slot %zu: ", xs->count+i);
        scanf("%d", &hold);
        xs->items[xs->count+i] = hold;        
    }
    
    xs->count += new_nums;
}


void print_array(Numbers *xs){

    printf("\n\nThe array currently has %zu elements:\n", xs->count);
    for(size_t i = 0; i < xs->count; i++){
        
        printf("%d, ", xs->items[i]);
    }
    
    printf("\n");
}





