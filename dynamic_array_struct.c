#include <stdlib.h>
#include <stdio.h>

typedef struct{
    
    int *items;
    size_t count;
    size_t capacity;     
} Numbers;
    
void add(Numbers *numbers);
void print_array(Numbers *numbers);


int main(void){
    
    int going = 1;
    Numbers numbers = {0};
        
    while(going){
        
        int menu_select;
        printf("select: 1 to add numbers, 2 to remove numbers, or 3 to quit.\n> ");
        scanf("%d", &menu_select);
        
        if(menu_select == 3){
            
            printf("\ngoodbye.\n");
            going = 0;
        }
        
        else if(menu_select == 1){
            
            printf("you chose to add\n\n");
            add(&numbers);
            print_array(&numbers);
        }
        
        else if(menu_select == 2){
            
            printf("you chose to remove\n\n");
        }
        
        else{
            
            printf("invalid selection.\n\n");
        }    
    }
    
    free(numbers.items);
    numbers.items = NULL;
    numbers.count = 0;
    numbers.capacity = 0;
    
    return 0;
}


void add(Numbers *numbers){
    
    //starts dynamic array if size is 0 (zero-initialized)
    const int DEFAULT_CAPACITY = 4;
    if(numbers->capacity == 0){
        
        numbers->capacity = DEFAULT_CAPACITY;
        numbers->items = malloc(numbers->capacity * sizeof(int));
        printf("new dynamic array created!\n");
    }
    
    size_t new_nums;
    printf("how many numbers would you like to add?\n> ");
    scanf("%zu", &new_nums);
    
    //check to see if array must be resized. does so if necessary, then adds new items.
    const size_t RESIZE_VALUE = 2;
    size_t required_capacity = numbers->count + new_nums;
    if(required_capacity > numbers->capacity){
        
        while(numbers->capacity < required_capacity){
            
            numbers->capacity *= RESIZE_VALUE;
        }
        
        numbers->items = realloc(numbers->items, numbers->capacity * sizeof(int));
        printf("\nmax capacity reached. resized to %zu.\n", numbers->capacity);
    }
    
    for(size_t i = 0; i < new_nums; i++){
    
        int hold;
        printf("\nenter the value of slot %zu: ", numbers->count+i);
        scanf("%d", &hold);
        numbers->items[numbers->count+i] = hold;        
    }
    
    numbers->count += new_nums;
}


void print_array(Numbers *numbers){

    printf("\n\nThe array currently has %zu elements:\n", numbers->count);
    for(size_t i = 0; i < numbers->count; i++){
        
        printf("%d, ", numbers->items[i]);
    }
    
    printf("\n");
}





