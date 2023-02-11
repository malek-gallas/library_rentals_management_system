#include <stdio.h>
#include "headers.h"

int main(int argc, char *argv[]){
//////////////////////////// -- ID's Initialisation -- //////////////////////////////
    int mem_key= 0;
    int doc_key= 0;
    int rental_key= 0;
    mem_key= readMembersKey();
    doc_key= readDocumentsKey();
    rental_key= readRentalsKey();
//////////////////////////// -- Lists Initialisation -- //////////////////////////////
    MembersList *mem_list= NULL;
    DocumentsList *doc_list= NULL;
    RentalsList *rentals_list= NULL;
    LateList *late_list= NULL;
    mem_list= readMembersFile(mem_list, &mem_key);
    doc_list= readDocumentsFile(doc_list, &doc_key);
    rentals_list= readRentalsFile(rentals_list, &rental_key);
    createLateList(&late_list, rentals_list);
//////////////*/////////////// -- User Interface -- //////////////////////////////////
    menu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
    return (0);
}