#include <stdio.h>
#include <stdlib.h>
#include "headers.h"
#include "structs.h"

MembersList *readNextFromMembersFile(MembersList *mem_list, FILE *members_file){
    if (mem_list == NULL){
        mem_list= malloc(sizeof(MembersList));
        fread(mem_list, sizeof(MembersList), 1, members_file);
        mem_list->next= NULL;
    }else{
        MembersList *index= mem_list;
        MembersList *new= malloc(sizeof(MembersList));
        while (index->next != NULL){
            index= index->next;
        }
        fread(new, sizeof(MembersList), 1, members_file);
        index->next= new;
        new->next= NULL;
    }
    return (mem_list);
}

MembersList *readMembersFile(MembersList *mem_list, int *mem_key){
    FILE *members_file = fopen("members_list.bin", "rb");
    if (members_file != NULL){
        mem_list= NULL;
        fseek(members_file, 0, SEEK_END);
        long fileSize= ftell(members_file);
        rewind(members_file);
        int num= (int)(fileSize/sizeof(MembersList));
        for (int i=0; i<num; i++){
            fseek(members_file, (sizeof(MembersList)*i),SEEK_SET);
            mem_list= readNextFromMembersFile(mem_list, members_file);
        }
    }
    else
        printf("Error! Opening File.\n");
    return (mem_list);
}

void writeMembersFile(MembersList *mem_list){
    FILE *members_file = fopen("members_list.bin", "wb");
    if (members_file != NULL){
        MembersList *temp = mem_list;
        MembersList *holdNext = NULL;
        while(temp != NULL){
            holdNext = temp->next;
            temp->next = NULL;
            fseek(members_file, 0, SEEK_END);
            fwrite(temp, sizeof(MembersList), 1, members_file);
            temp->next = holdNext;
            holdNext = NULL;
            temp= temp->next;
        }
        fclose(members_file);
        members_file= NULL;
    }
    else
        printf("Error! Opening File.\n");
}

int readMembersKey(){
    FILE *fptr;
    int key=0;
    if ((fptr = fopen("members_key.bin","rb")) == NULL){
    printf("Error! Opening File.\n");
    }
    else{
        fread(&key, sizeof(int), 1, fptr);
        fclose(fptr); 
    }
    return (key);
}

void writeMembersKey(int mem_key){
    int key= mem_key;
    FILE *fptr;
    if ((fptr = fopen("members_key.bin","wb")) == NULL){
        printf("Error! Opening File.\n");
    }
    else{
        fwrite(&key, sizeof(int), 1, fptr); 
        fclose(fptr); 
    }
}

