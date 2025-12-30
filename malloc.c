#include <stdio.h>
#include <stdlib.h>

void add(int *size_pointer, int **numbers);
void rid_of(int *size_pointer, int**numbers);

int main(){
    
    int going = 1;
    int *numbers = NULL;
    int size = 0;
    
    
    
    while(going){
        
        int menu_select;
        printf("select: 1 to add numbers, 2 to remove numbers, or 3 to quit.\n> ");
        scanf("%d", &menu_select);
        
        if(menu_select == 3){
            going = 0;
        }
        
        else if(menu_select == 1){
            printf("you chose to add\n\n");
            int *size_pointer = &size;
            add(size_pointer, &numbers);
            
            printf("The array now has the numbers: ");
            for(int i = 0; i < *size_pointer; i++){
                printf("%d, ", numbers[i]);
            }
            
            printf("\n");
        }
        
        else if(menu_select == 2){
            printf("you chose to remove\n\n");
            int *size_pointer = &size;
            rid_of(size_pointer, &numbers);
            
            printf("The array now has the numbers: ");
            for(int i = 0; i < *size_pointer; i++){
                printf("%d, ", numbers[i]);
            }
            
            if(*size_pointer == 0){
                printf("none. que lastima.");
            }
            
            printf("\n");
        }
        
        else{
            printf("invalid selection.\n\n");
        }
        
        
    }
    
    return 0;
}


void add(int *size_pointer, int **numbers){
    int numof_new_nums;
    printf("\nHow many numbers would you like to add?\n> ");
    scanf("%d", &numof_new_nums);
    
    if(*numbers == NULL){
        *size_pointer = numof_new_nums;
        *numbers = malloc(*size_pointer * sizeof(int));
        
        if(*numbers == NULL){
            printf("bad malloc!");
        }
        
        else{
            for(int i = 0; i < *size_pointer; i++){
                int hold;
                printf("\nenter the value of slot %d: ", i);
                scanf("%d", &hold);
                (*numbers)[i] = hold;
            }
        }
    }
    
    else{
        int start = *size_pointer;
        *size_pointer += numof_new_nums;
        int *temp = realloc(*numbers, (sizeof(int)) * (*size_pointer));
        if(temp == NULL){
            printf("bad realloc!");
        }
        
        else{
            *numbers = temp;
            
            for(int i = 0; i < numof_new_nums; i++){
                int hold;
                printf("\nenter the value of slot %d: ", i + start);
                scanf("%d", &hold);
                (*numbers)[i+start] = hold;
            }
        }     
    }
    
    printf("\n\nnumbers now has %d slots, stored at %p\n", *size_pointer, (void *)numbers);
}


void rid_of(int *size_pointer, int **numbers){
    
    if(*numbers == NULL){
        printf("there aren't any numbers to remove!\n");
    }
    
    else{
        int numof_removed_nums;
        printf("How many numbers would you like to have removed?\n> ");
        scanf("%d", &numof_removed_nums);
        
        if(numof_removed_nums > *size_pointer){
            printf("you can't delete more numbers than there are in the list. i'll just blow away the whole thing.\n");
            free(*numbers);
            *size_pointer = 0; 
        }
        
        else{
            *size_pointer -= numof_removed_nums;
            int *temp = realloc(*numbers, (sizeof(int) * (*size_pointer)));
            if(temp == NULL && *size_pointer > 0){
                printf("bad realloc!\n");
                *size_pointer += numof_removed_nums;
            }
            
            else{
                *numbers = temp;
                printf("removed %d numbers.\n", numof_removed_nums);
            }
        }        
    }
}



































