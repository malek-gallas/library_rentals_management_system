#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
  #include <ncurses\ncurses.h>
#else
  #include <ncurses.h>
#endif
#include "headers.h"
#include "structs.h"

RentalsList* createRental(RentalsList *rentals_list, int *rental_key, MembersList *mem_list, DocumentsList *doc_list, LateList *late_list){
    printf ("\n\n\t\t\t\t\t***** Rental Details *****\n\n");
//////////////////////////// -- Variables -- //////////////////////////////
    MembersList *temp1= mem_list;
    DocumentsList *temp2= doc_list;                   
    int member_id;
    int document_id;
    int max_duration= 0;
    int condition1=0, condition2=0, condition3=1, condition4=0, condition5=0;    
    int check= 0;
//////////////////////////// -- User Inputs  -- //////////////////////////////
    do{
        printf("\n--> Member ID: ");
        check = scanf("%d", &member_id);
        if (check != 1){
            printf("==> Invalid input! Please enter a number.\n");
            scanf("%*c");
        }
    }while (check != 1);
    while (temp1 != NULL){
        if (temp1->member.id == member_id){
            condition1= 1;
            max_duration= temp1->member.max_duration;
            if (temp1->member.current_rentals < temp1->member.max_rentals)
                condition2= 1;
            LateList *temp3= late_list;
            if (temp3 == NULL)
                condition3 = 1;
            else{
                while (temp3 != NULL){
                    if (temp3->rental.member_id == member_id)
                        condition3 = 0;
                    temp3= temp3->next;
                }
                
            }
        }
        temp1= temp1->next;
    }
    check= 0;
    do{
        printf("\n--> Document ID: ");
        check = scanf("%d", &document_id);
        if (check != 1){
            printf("==> Invalid input! Please enter a number.\n");
            scanf("%*c");
        }
    }while (check != 1);
    while (temp2 != NULL){
        if (temp2->document.code == document_id){
            condition4= 1;
            if (temp2->document.current_rentals < temp2->document.stock)
                condition5= 1;
        }
        temp2= temp2->next;
    }
    //printf ("==> Conditions: %d-%d-%d-%d-%d\n", condition1, condition2, condition3, condition4, condition5);
    if (condition1 == 0){
        printf ("==> This Member Do Not Exist.\n");
        return (rentals_list);
    }
    if (condition2 == 0){
        printf ("==> This Member Attained Maximum Rentals.\n");
        return (rentals_list);
    }
    if (condition3 == 0){
        printf ("==> This Member Has Rentals In Late.\n");
        return (rentals_list);
    }
    if (condition4 == 0){
        printf ("==> This Document Do Not Exist.\n");
        return (rentals_list);
    }
    if (condition5 == 0){
        printf ("==> Low Stock.\n");
        return (rentals_list);
    }
    if (condition1==1 && condition2==1 && condition3==1 && condition4==1 && condition5==1){
        RentalsList *new= NULL;
        new= (RentalsList *)malloc(sizeof(RentalsList));
        new->rental.member_id= member_id;
        new->rental.document_id= document_id;
//////////////////////////// -- Key & Pointer -- //////////////////////////////
        *rental_key= *rental_key+1;
        new->rental.operation_id= *rental_key;
        new->next= NULL;
//////////////////////////////////////Date Manipulation////////////////////////////////////
        time_t now= time(NULL);
        struct tm* t1=localtime(&now);
        new->rental.rental_date.day= t1->tm_mday;
        new->rental.rental_date.month= t1->tm_mon+1;
        new->rental.rental_date.year= t1->tm_year+1900;
        time_t future= mktime(t1);
        future= future + (max_duration*7)*24*60*60;
        new->rental.real_return_date= future;
        struct tm* t2= localtime(&future);
        new->rental.return_date.day= t2->tm_mday;
        new->rental.return_date.month= t2->tm_mon+1;
        new->rental.return_date.year= t2->tm_year+1900;
//////////////////////////// -- Implementation -- //////////////////////////////   
        if (rentals_list == NULL){
            printf ("==> Rental Added.\n");
            memberCureentRentals (mem_list, member_id, rentals_list);
            documentCureentRentals(doc_list, document_id, rentals_list);
            return (new);
        }
        else{
            RentalsList *temp= rentals_list;
            while (temp->next != NULL){
                temp= temp->next;
            }
            temp->next= new;
            printf ("==> Rental Added.\n");
            memberCureentRentals (mem_list, member_id, rentals_list);
            documentCureentRentals(doc_list, document_id, rentals_list);
            return (rentals_list);
        }
    }
    else
        printf ("Unknown Error !");    
		return (rentals_list);
}

void readRentalsList (RentalsList *rentals_list){
    RentalsList *temp = rentals_list;
    initscr();
    raw();
    //WINDOW *table_win = newwin(getmaxy(stdscr), getmaxx(stdscr), 0, 0);
    WINDOW *table_pad = newpad(getmaxy(stdscr), getmaxx(stdscr));
    // Draw horizontal lines
    mvwhline(table_pad, 0, 2, ACS_HLINE, 73);
    mvwhline(table_pad, 2, 2, ACS_HLINE, 73);
    int num_rows = 2;
    while (temp != NULL){
        mvwhline(table_pad, num_rows+3, 2, ACS_HLINE, 73);
        num_rows = num_rows + 3;
        temp = temp->next;
    }
    // Draw vertical lines
    mvwvline(table_pad, 1, 1, ACS_VLINE, num_rows-1);
    mvwvline(table_pad, 1, 10, ACS_VLINE, num_rows-1);
    mvwvline(table_pad, 1, 27 , ACS_VLINE, num_rows-1);
    mvwvline(table_pad, 1, 43, ACS_VLINE, num_rows-1);
    mvwvline(table_pad, 1, 59, ACS_VLINE, num_rows-1);
    mvwvline(table_pad, 1, 75, ACS_VLINE, num_rows-1);
    // Print the table headers
    mvwprintw(table_pad, 1, 2, "Code");
    mvwprintw(table_pad, 1, 11, "Member ID");
    mvwprintw(table_pad, 1, 28, "Document ID");
    mvwprintw(table_pad, 1, 44, "Rental Date");
    mvwprintw(table_pad, 1, 60, "Return Date");
    // Print the table Data
    temp = rentals_list;
    int row = 3;
    while (temp != NULL){
        mvwprintw(table_pad, row, 2, "%d", temp->rental.operation_id);
        mvwprintw(table_pad, row, 11, "%d", temp->rental.member_id);
        mvwprintw(table_pad, row, 28, "%d", temp->rental.document_id);
        mvwprintw(table_pad, row, 44, "%d/%d/%d", temp->rental.rental_date.day, temp->rental.rental_date.month, temp->rental.rental_date.year);
        mvwprintw(table_pad, row, 60, "%d/%d/%d", temp->rental.return_date);
        row += 3;
        temp = temp->next;
    }
    mvwprintw(table_pad, row+1, 2, "====> Press 'ANY' Key To Exit ... ");
    refresh ();
    prefresh(table_pad, 0, 0, 0, 0, LINES - 1, COLS - 1);
    getch();
    endwin();
}

void updateRental (RentalsList *rentals_list, MembersList *mem_list, DocumentsList *doc_list, LateList *late_list){
    int rental_key, found=0;
    int check= 0;
    do{
        printf("\n--> Please Enter The Rental Member: ");
        check = scanf("%d", &rental_key);
        if (check != 1){
            printf("==> Invalid input! Please enter a number.\n");
            scanf("%*c");
        }
    }while (check != 1);
    MembersList *temp1= mem_list;
    DocumentsList *temp2= doc_list;           
    int member_id;
    int document_id;
    int condition1=0, condition2=0, condition3=1, condition4=0, condition5=0;    
    check= 0;
    do{
        printf("\n--> Member ID: ");
        check = scanf("%d", &member_id);
        if (check != 1){
            printf("==> Invalid input! Please enter a number.\n");
            scanf("%*c");
        }
    }while (check != 1);
    while (temp1 != NULL){
        if (temp1->member.id == member_id){
            condition1= 1;
            if (temp1->member.current_rentals < temp1->member.max_rentals)
                condition2= 1;
            LateList *temp3= late_list;
            if (temp3 == NULL)
                condition3 = 1;
            else{
                while (temp3 != NULL){
                    if (temp3->rental.member_id == member_id)
                        condition3 = 0;
                    temp3= temp3->next;    
                }
            }
        }
        temp1= temp1->next;
    }
    check= 0;
    do{
        printf("\n--> Document ID: ");
        check = scanf("%d", &document_id);
        if (check != 1){
            printf("==> Invalid input! Please enter a number.\n");
            scanf("%*c");
        }
    }while (check != 1);
    while (temp2 != NULL){
        if (temp2->document.code == document_id){
            condition4= 1;
            if (temp2->document.current_rentals < temp2->document.stock)
                condition5= 1;
        }
        temp2= temp2->next;
    }
    //printf ("==> Conditions: %d-%d-%d-%d-%d\n", condition1, condition2, condition3, condition4, condition5);
    if (condition1 == 0){
        printf ("==> This Member Do Not Exist.\n");
    }
    if (condition2 == 0){
        printf ("==> This Member Attained Maximum Rentals.\n");
    }
    if (condition3 == 0){
        printf ("==> This Member Has Rentals In Late.\n");
    }
    if (condition4 == 0){
        printf ("==> This Document Do Not Exist.\n");
    }
    if (condition5 == 0){
        printf ("==> Low Stock.\n");
    }
    if (condition1==1 && condition2==1 && condition3==1 && condition4==1 && condition5==1){
        RentalsList *temp4 = rentals_list;
        while (temp4 != NULL){
            if (temp4->rental.operation_id == rental_key){
                found++;
                temp4->rental.member_id= member_id;
                temp4->rental.document_id= document_id;
            }
            temp4= temp4->next;
        }
    }
    if (found == 0)
        printf ("\n==> No Match Found.\n");
}

void deleteRental(RentalsList **rentals_list, MembersList *mem_list, DocumentsList *doc_list, int *rental_key){
    int key, found=0;
    MembersList *temp1= mem_list;
    DocumentsList *temp2= doc_list;
    int check= 0;
    do{
        printf("\n--> Please Enter The Rental Member: ");
        check = scanf("%d", &key);
        if (check != 1){
            printf("==> Invalid input! Please enter a number.\n");
            scanf("%*c");
        }
    }while (check != 1);
    RentalsList *temp;
    if((*rentals_list)->rental.operation_id == key){
        found++;
        while (temp1 != NULL){
            if (temp1->member.id == (*rentals_list)->rental.member_id)
                temp1->member.current_rentals--;
            temp1= temp1->next;
        }
        while (temp2 != NULL){
            if (temp2->document.code == (*rentals_list)->rental.document_id)
                temp2->document.current_rentals--;
            temp2= temp2->next;
        }
        temp = *rentals_list;
        *rentals_list = (*rentals_list)->next;
        *rental_key= 0;
        free(temp);
        printf ("==> Rental Deleted.\n");
    }
    else{
        RentalsList *current  = *rentals_list;
        while(current->next != NULL){
            if(current->next->rental.operation_id == key){
                found++;
                while (temp1 != NULL){
                    if (temp1->member.id == current->next->rental.member_id)
                        temp1->member.current_rentals--;
                    temp1= temp1->next;
                }
                while (temp2 != NULL){
                    if (temp2->document.code == current->next->rental.document_id)
                        temp2->document.current_rentals--;
                    temp2= temp2->next;
                }
                temp = current->next;
                current->next = current->next->next;
                free(temp);
                printf ("==> Rental Deleted.\n");
                break;
            }
            else
                current = current->next;
        }
    }
    if (found == 0)
        printf ("\n==> No Match Found.\n");
}

void searchRental(RentalsList *rentals_list){
    int rental_key, found=0;
    int check= 0;
    do{
        printf("\n--> Please Enter The Rental Member: ");
        check = scanf("%d", &rental_key);
        if (check != 1){
            printf("==> Invalid input! Please enter a number.\n");
            scanf("%*c");
        }
    }while (check != 1);
    RentalsList *temp = rentals_list;
    while (temp != NULL) {
        if (temp->rental.operation_id == rental_key){
            found++;
            printf("\n==> Rental Informations: \n");
            printf ("----> Rental Number: %d\n", temp->rental.operation_id);
            printf ("----> Member ID: %d\n", temp->rental.member_id);
            printf ("----> Document ID: %d\n", temp->rental.document_id);
            printf ("------> Rental-Date: %d-", temp->rental.rental_date.day);
            printf ("%d-", temp->rental.rental_date.month);
            printf ("%d\n", temp->rental.rental_date.year);
            printf ("------> Return-Date: %d-", temp->rental.return_date.day);
            printf ("%d-", temp->rental.return_date.month);
            printf ("%d\n", temp->rental.return_date.year);
        }   
        temp= temp->next;
    }
    if (found == 0)
        printf ("\n==> No Match Found.\n");
}

int rentalsListIsEmpty (RentalsList const *rentals_list){
    if (rentals_list == NULL)
        return (1);
    else
        return (0);
}