#include <stdio.h>
#include <stdlib.h>
#include "headers.h" 
#include "structs.h"

void menu(MembersList *mem_list, int mem_key, DocumentsList *doc_list, int doc_key, RentalsList *rentals_list, int rental_key, LateList *late_list){
    system (CLEAR);
    printf("\n\n\t\t\t\t\t***** Library Management System *****\n\n");
    printf("\t\t1* Members Management.\n");
    printf("\t\t2* Documents Management.\n");
    printf("\t\t3* Rentals Management.\n");
    printf("\t\t4* Laters List.\n");
    printf("\t\t0* Exit.\n\n"); 
    int c1= -1;
    int check=0 ; 
    do {
    printf("--> Choice: ");
    check = scanf("%d", &c1);
    if (check != 1 || c1 < 0 || c1 > 4) {
        printf("==> Invalid input! Please enter an integer between 0 and 4.\n");
        scanf("%*c");
    }
    } while (check != 1 || c1 < 0 || c1 > 4);
    switch (c1){
        case 0:
            system (CLEAR);
            writeMembersKey(mem_key);
            writeDocumentsKey(doc_key);
            writeRentalsKey(rental_key);
            writeMembersFile(mem_list);
            writeDocumentsFile(doc_list);
            writeRentalsFile(rentals_list);
            exit(EXIT_SUCCESS);
            break;
        case 1:
            system (CLEAR);
            membersMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
            break;
        case 2:
            system (CLEAR);
            documentsMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
            break;
        case 3:
            system (CLEAR);
            rentalsMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
            break;
        case 4:
            system (CLEAR);
            lateMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
            break;
        default:
            system (CLEAR);
            printf ("================================= SYSTEM CRASH ======================================");
            exit(EXIT_FAILURE);
            break;
    }
}

void membersMenu(MembersList *mem_list, int mem_key, DocumentsList *doc_list, int doc_key, RentalsList *rentals_list, int rental_key, LateList *late_list){
    printf ("\n\n\t\t\t\t\t***** Members Management *****\n\n");
    printf("\t\t1* Create Member.\n");
    printf("\t\t2* Update Member.\n");
    printf("\t\t3* Delete Member.\n");
    printf("\t\t4* Search Member.\n");
    printf("\t\t5* Read Members List.\n");
    printf("\t\t0* Home Page.\n\n");
    int c2= -1;
    int check= 0;
    do {
    printf("--> Choice: ");
    check = scanf("%d", &c2);
    if (check != 1 || c2 < 0 || c2 > 5) {
        printf("==> Invalid input! Please enter an integer between 0 and 5.\n");
        scanf("%*c"); 
    }
    } while (check != 1 || c2 < 0 || c2 > 5);
    switch (c2)
    {
    case 0:
        system (CLEAR);
        menu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        break;
    case 1:
        system (CLEAR);
        mem_list= createMember(mem_list, &mem_key);
        membersMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        break;
    case 2:
        system (CLEAR);
        if (membersListIsEmpty(mem_list)){
            printf ("==> List Is Empty.\n");
            membersMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        }
        else{
            updateMember(mem_list);
            membersMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        }
        break;
    case 3:
        system (CLEAR);
        if (membersListIsEmpty(mem_list)){
            printf ("==> List Is Empty.\n");
            membersMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        }
        else{
            deleteMember(&mem_list, &mem_key);
            membersMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        }
        break;
    case 4:
        system (CLEAR);
        if (membersListIsEmpty(mem_list)){
            printf ("==> List Is Empty.\n");
            membersMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        }
        else{
            searchMember(mem_list);
            membersMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        }
        break;
    case 5:
        system (CLEAR);
        if (membersListIsEmpty(mem_list)){
            printf ("==> List Is Empty.\n");
            membersMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        }
        else{
            readMembersList(mem_list);
            membersMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        }
        break;                
    default:
        system (CLEAR);
        printf ("================================= SYSTEM CRASH ======================================");
        exit(EXIT_FAILURE);
        break;
    }
}

void documentsMenu(MembersList *mem_list, int mem_key, DocumentsList *doc_list, int doc_key, RentalsList *rentals_list, int rental_key, LateList *late_list){
    printf ("\n\n\t\t\t\t\t***** Documents Management *****\n\n");
    printf("\t\t1* Create Document.\n");
    printf("\t\t2* Update Document.\n");
    printf("\t\t3* Delete Document.\n");
    printf("\t\t4* Search Document.\n");
    printf("\t\t5* Read Documents List.\n");
    printf("\t\t0* Home Page.\n\n");
    int c3= -1;
    int check= 0;
    do {
    printf("--> Choice: ");
    check = scanf("%d", &c3);
    if (check != 1 || c3 < 0 || c3 > 5) {
        printf("==> Invalid input! Please enter an integer between 0 and 5.\n");
        scanf("%*c");
    }
    } while (check != 1 || c3 < 0 || c3 > 5);
    switch (c3)
    {
    case 0:
        system (CLEAR);
        menu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        break;
    case 1:
        system (CLEAR);
        doc_list= createDocument(doc_list, &doc_key);
        documentsMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        break;
    case 2:
        system (CLEAR);
        if (documentsListIsEmpty(doc_list)){
            printf ("==> List Is Empty.\n");
            documentsMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        }
        else{
            updateDocument(doc_list);
            documentsMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        }
        break;
    case 3:
        system (CLEAR);
        if (documentsListIsEmpty(doc_list)){
            printf ("==> List Is Empty.\n");
            documentsMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        }
        else{
            deleteDocument(&doc_list, &doc_key);
            documentsMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        }
        break;
    case 4:
        system (CLEAR);
        if (documentsListIsEmpty(doc_list)){
            printf ("==> List Is Empty.\n");
            documentsMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        }
        else{
            searchDocument(doc_list);
            documentsMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        }
        break;
    case 5:
        system (CLEAR);
        if (documentsListIsEmpty(doc_list)){
            printf ("==> List Is Empty.\n");
            documentsMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        }
        else{
            readDocumentsList(doc_list);
            documentsMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        }
        break;
    default:
        system (CLEAR);
        printf ("================================= SYSTEM CRASH ======================================");
        exit(EXIT_FAILURE);
        break;
    }
}

void rentalsMenu(MembersList *mem_list, int mem_key, DocumentsList *doc_list, int doc_key, RentalsList *rentals_list, int rental_key, LateList *late_list){
    printf ("\n\n\t\t\t\t\t***** Rentals Management *****\n\n");
    printf("\t\t1* Create Rental.\n");
    printf("\t\t2* Update Rental.\n");
    printf("\t\t3* Delete Rental.\n");
    printf("\t\t4* Search Rental.\n");
    printf("\t\t5* Read Rentals List.\n");
    printf("\t\t0* Home Page.\n\n");
    int c4= -1;
    int check= 0;
    do {
    printf("--> Choice: ");
    check = scanf("%d", &c4);
    if (check != 1 || c4 < 0 || c4 > 5) {
        printf("==> Invalid input! Please enter an integer between 0 and 5.\n");
        scanf("%*c");
    }
    } while (check != 1 || c4 < 0 || c4 > 5);
    switch (c4)
    {
    case 0:
        system (CLEAR);
        menu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        break;
    case 1:
        system (CLEAR);
        rentals_list= createRental(rentals_list, &rental_key, mem_list, doc_list, late_list);
        rentalsMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        break;
    case 2:
        system (CLEAR);
        if (rentalsListIsEmpty(rentals_list)){
            printf ("==> List Is Empty.\n");
            rentalsMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        }
        else{
            updateRental(rentals_list, mem_list, doc_list, late_list);
            rentalsMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        }
        break;
    case 3:
        system (CLEAR);
        if (rentalsListIsEmpty(rentals_list)){
            printf ("==> List Is Empty.\n");
            rentalsMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        }
        else{
            deleteRental(&rentals_list, mem_list, doc_list, &rental_key);
            rentalsMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        }
        break;
    case 4:
        system (CLEAR);
        if (rentalsListIsEmpty(rentals_list)){
            printf ("==> List Is Empty.\n");
            rentalsMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        }
        else{
            searchRental(rentals_list);
            rentalsMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        }
        break;
    case 5:
        system (CLEAR);
        if (rentalsListIsEmpty(rentals_list)){
            printf ("==> List Is Empty.\n");
            rentalsMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        }
        else{
            readRentalsList(rentals_list);
            rentalsMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        }
        break;
    default:
        system (CLEAR);
        printf ("================================= SYSTEM CRASH ======================================");
        exit(EXIT_FAILURE);
        break;
    }
}

void lateMenu(MembersList *mem_list, int mem_key, DocumentsList *doc_list, int doc_key, RentalsList *rentals_list, int rental_key, LateList *late_list){
    printf ("\n\n\t\t\t\t\t*** Late Rentals List ***\n\n");
    printf("\t\t1* Read Late Rentals List.\n");
    printf("\t\t2* Search Member.\n");
    printf("\t\t0* Home Page.\n\n");
    int c5= -1;
    int check= 0;
    do {
    printf("--> Choice: ");
    check = scanf("%d", &c5);
    if (check != 1 || c5 < 0 || c5 > 2) {
        printf("==> Invalid input! Please enter an integer between 0 and 2.\n");
        scanf("%*c");
    }
    } while (check != 1 || c5 < 0 || c5 > 2);
    switch (c5)
    {
    case 0:
        system (CLEAR);
        menu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        break;
    case 1:
        system (CLEAR);
        if (lateListIsEmpty(late_list)){
            printf ("==> List Is Empty.\n");
            lateMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        }
        else{
            readLateList(late_list);
            lateMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        }
        break;
    case 2:
        system (CLEAR);
        if (lateListIsEmpty(late_list)){
            printf ("==> List Is Empty.\n");
            lateMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        }
        else{
            searchLate(late_list);
            lateMenu(mem_list, mem_key, doc_list, doc_key, rentals_list, rental_key, late_list);
        }
        break;
    default:
        system (CLEAR);
        printf ("================================= SYSTEM CRASH ======================================");
        exit(EXIT_FAILURE);
        break;
    }
}

