#include <stdio.h>
#include <stdlib.h>
#include "headers.h"
#include "structs.h"

DocumentsList *readNextFromDocumentsFile(DocumentsList *doc_list, FILE *documents_file){
    if (doc_list == NULL){
        doc_list= malloc(sizeof(DocumentsList));
        fread(doc_list, sizeof(DocumentsList), 1, documents_file);
        doc_list->next= NULL;
    }else{
        DocumentsList *index= doc_list;
        DocumentsList *new= malloc(sizeof(DocumentsList));
        while (index->next != NULL){
            index= index->next;
        }
        fread(new, sizeof(DocumentsList), 1, documents_file);
        index->next= new;
        new->next= NULL;
    }
    return (doc_list);
}

DocumentsList *readDocumentsFile(DocumentsList *doc_list, int *doc_key){
    FILE *documents_file = fopen("documents_list.bin", "rb");
    if (documents_file != NULL){
        doc_list= NULL;
        fseek(documents_file, 0, SEEK_END);
        long fileSize= ftell(documents_file);
        rewind(documents_file);
        int num= (int)(fileSize/sizeof(DocumentsList));
        for (int i=0; i<num; i++){
            fseek(documents_file, (sizeof(DocumentsList)*i),SEEK_SET);
            doc_list= readNextFromDocumentsFile(doc_list, documents_file);
        }
    }
    else
        printf("Error! Opening File.\n");
    return (doc_list);
}

void writeDocumentsFile(DocumentsList *doc_list){
    FILE *documents_file = fopen("documents_list.bin", "wb");
    if (documents_file != NULL){
        DocumentsList *temp = doc_list;
        DocumentsList *holdNext = NULL;
        while(temp != NULL){
            holdNext = temp->next;
            temp->next = NULL;
            fseek(documents_file, 0, SEEK_END);
            fwrite(temp, sizeof(DocumentsList), 1, documents_file);
            temp->next = holdNext;
            holdNext = NULL;
            temp= temp->next;
        }
        fclose(documents_file);
        documents_file= NULL;
    }
    else
        printf("Error! Opening File.\n");
}

int readDocumentsKey(){
    FILE *fptr;
    int key=0;
    if ((fptr = fopen("documents_key.bin","rb")) == NULL){
		printf("Error! Opening File.\n");
    }
	else{
		fread(&key, sizeof(int), 1, fptr);
		fclose(fptr); 
	}
    return (key);
}

void writeDocumentsKey(int doc_key){
    int key= doc_key;
    FILE *fptr;
    if ((fptr = fopen("documents_key.bin","wb")) == NULL){
        printf("Error! Opening File.\n");
    }
    else{
        fwrite(&key, sizeof(int), 1, fptr); 
        fclose(fptr); 
    }
}

