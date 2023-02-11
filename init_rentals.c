#include <stdio.h>
#include <stdlib.h>
#include "headers.h"
#include "structs.h"

RentalsList *readNextFromRentalsFile(RentalsList *rentals_list, FILE *rentals_file){
    if (rentals_list == NULL){
        rentals_list= malloc(sizeof(RentalsList));
        fread(rentals_list, sizeof(RentalsList), 1, rentals_file);
        rentals_list->next= NULL;
    }else{
        RentalsList *index= rentals_list;
        RentalsList *new= malloc(sizeof(RentalsList));
        while (index->next != NULL){
            index= index->next;
        }
        fread(new, sizeof(RentalsList), 1, rentals_file);
        index->next= new;
        new->next= NULL;
    }
    return (rentals_list);
}

RentalsList *readRentalsFile(RentalsList *rentals_list, int *rentals_key){
    FILE *rentals_file = fopen("rentals_list.bin", "rb");
    if (rentals_file != NULL){
        rentals_list= NULL;
        fseek(rentals_file, 0, SEEK_END);
        long fileSize= ftell(rentals_file);
        rewind(rentals_file);
        int num= (int)(fileSize/sizeof(RentalsList));
        for (int i=0; i<num; i++){
            fseek(rentals_file, (sizeof(RentalsList)*i),SEEK_SET);
            rentals_list= readNextFromRentalsFile(rentals_list, rentals_file);
        }
    }
    else
        printf("Error! Opening File.\n");
    return (rentals_list);
}

void writeRentalsFile(RentalsList *rentals_list){
    FILE *rentals_file = fopen("rentals_list.bin", "wb");
    if (rentals_file != NULL){
        RentalsList *temp = rentals_list;
        RentalsList *holdNext = NULL;
        while(temp != NULL){
            holdNext = temp->next;
            temp->next = NULL;
            fseek(rentals_file, 0, SEEK_END);
            fwrite(temp, sizeof(RentalsList), 1, rentals_file);
            temp->next = holdNext;
            holdNext = NULL;
            temp= temp->next;
        }
        fclose(rentals_file);
        rentals_file= NULL;
    }
    else
        printf("Error! Opening File.\n");
}

int readRentalsKey(){
    FILE *fptr;
    int key=0;
    if ((fptr = fopen("rentals_key.bin","rb")) == NULL){
    printf("Error! Opening File.\n");
    }
    else{
        fread(&key, sizeof(int), 1, fptr);
        fclose(fptr);
    } 
    return (key);
}

void writeRentalsKey(int rental_key){
    int key= rental_key;
    FILE *fptr;
    if ((fptr = fopen("rentals_key.bin","wb")) == NULL){
        printf("Error! Opening File.\n");
    }
    else{
        fwrite(&key, sizeof(int), 1, fptr); 
        fclose(fptr); 
    }
}

