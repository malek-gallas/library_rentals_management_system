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

void createLateList(LateList **late_list, RentalsList *rentals_list){
    RentalsList *temp1= rentals_list;
    time_t now= time(NULL);
    while (temp1 != NULL){
        if ((now+(24*60*60)) >= temp1->rental.real_return_date){
            LateList *new= (LateList *)malloc(sizeof(LateList));
            new->rental= temp1->rental;
            new->next= NULL;
            if (*late_list == NULL){
            *late_list= new;
            }
            else{
                LateList *temp2= *late_list;
                while (temp2->next != NULL){
                    temp2= temp2->next;
                }
            temp2->next= new;
            }
        }
        temp1= temp1->next;    
    }
}

void readLateList (LateList *late_list){
    LateList *temp = late_list;
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
    temp = late_list;
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

void searchLate(LateList *late_list){
    int late_key, found=0;
    int check= 0;
    do{
        printf("\n--> Please Enter The Member ID: ");
        check = scanf("%d", &late_key);
        if (check != 1){
            printf("==> Invalid input! Please enter a number.\n");
            scanf("%*c");
        }
    }while (check != 1);
    LateList *temp = late_list;
    while (temp != NULL) {
        if (temp->rental.member_id == late_key){
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

int lateListIsEmpty (LateList const *late_list){
    if (late_list == NULL)
        return (1);
    else
        return (0);
}