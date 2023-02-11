#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#ifdef _WIN32
  #include <ncurses\ncurses.h>
#else
  #include <ncurses.h>
#endif

#include "headers.h"
#include "structs.h"

MembersList *createMember(MembersList *mem_list, int *mem_key){
    printf("\n\n\t\t\t\t\t\t***** Create Member *****\n\n");
//////////////////////////// -- Variables -- //////////////////////////////
    MembersList *new = NULL;
    new = (MembersList *)malloc(sizeof(MembersList));
    char first_name[STRING_MAX_LENGTH];
    char last_name[STRING_MAX_LENGTH];
    char address[STRING_MAX_LENGTH];
    int member_type;  
    int check= 0;
//////////////////////////// -- User Inputs  -- //////////////////////////////
    check_string_is_valid("--> First-Name: ", first_name, is_alpha_space);
    strcpy(new->member.first_name, first_name);
    check_string_is_valid("--> Last-Name: ", last_name, is_alpha_space);
    strcpy(new->member.last_name, last_name);
    check_string_is_valid("--> Address: ", address, is_print);
    strcpy(new->member.address, address);
    do{
        printf("--> Type (1: Student - 2: Teacher - 3: Visitor): ");
        check = scanf("%d", &member_type);
        if (check != 1 || member_type < 1 || member_type > 3){
            printf("==> Invalid input! Please enter an integer between 1 and 3.\n");
            scanf("%*c");
        }
    }while (check != 1 || member_type < 1 || member_type > 3);
    switch (member_type){
    case 1:
        strcpy(new->member.member_type, "Student");
        new->member.max_rentals = 2;
        new->member.max_duration = 2;
        break;
    case 2:
        strcpy(new->member.member_type, "Teacher");
        new->member.max_rentals = 4;
        new->member.max_duration = 3;
        break;
    case 3:
        strcpy(new->member.member_type, "Teacher");
        new->member.max_rentals = 4;
        new->member.max_duration = 3;
        break;
    default:
        printf ("Member Type scanf Error !");
        exit(EXIT_FAILURE);
        break;
    }
//////////////////////////// -- Statistics -- //////////////////////////////    
    new->member.current_rentals = 0;
    new->member.old_rentals = 0;
    new->member.total_rentals = 0;
//////////////////////////// -- Key & Pointer -- //////////////////////////////
    new->next = NULL;
    *mem_key = *mem_key + 1;
    new->member.id = *mem_key;
//////////////////////////// -- Implementation -- //////////////////////////////   
    if (mem_list == NULL){
        printf("==> Member Created.\n");
        return (new);
    }
    else{
        MembersList *temp = mem_list;
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = new;
        printf("==> Member Created.\n");
        return (mem_list);
    }
}

void readMembersList(MembersList *mem_list){
    MembersList *temp = mem_list;
    initscr();
    clear();
    //WINDOW *table_win = newwin(getmaxy(stdscr), getmaxx(stdscr), 0, 0);
    WINDOW *table_pad = newpad(getmaxy(stdscr), getmaxx(stdscr));
    // Draw horizontal lines
    mvwhline(table_pad, 0, 2, ACS_HLINE, 118);
    mvwhline(table_pad, 2, 2, ACS_HLINE, 118);
    int num_rows = 2;
    while (temp != NULL){
        mvwhline(table_pad, num_rows+3, 2, ACS_HLINE, 118);
        num_rows = num_rows + 3;
        temp = temp->next;
    }
    // Draw vertical lines
    mvwvline(table_pad, 1, 1, ACS_VLINE, num_rows-1);
    mvwvline(table_pad, 1, 10, ACS_VLINE, num_rows-1);
    mvwvline(table_pad, 1, 27 , ACS_VLINE, num_rows-1);
    mvwvline(table_pad, 1, 43, ACS_VLINE, num_rows-1);
    mvwvline(table_pad, 1, 76, ACS_VLINE, num_rows-1);
    mvwvline(table_pad, 1, 93, ACS_VLINE, num_rows-1);
    mvwvline(table_pad, 1, 102, ACS_VLINE, num_rows-1);
    mvwvline(table_pad, 1, 111, ACS_VLINE, num_rows-1);
    mvwvline(table_pad, 1, 120, ACS_VLINE, num_rows-1);
    // Print the table headers
    mvwprintw(table_pad, 1, 2, "ID");
    mvwprintw(table_pad, 1, 11, "First Name");
    mvwprintw(table_pad, 1, 28, "Last Name");
    mvwprintw(table_pad, 1, 44, "Address");
    mvwprintw(table_pad, 1, 77, "Type");
    mvwprintw(table_pad, 1, 94, "Current");
    mvwprintw(table_pad, 1, 103, "Old");
    mvwprintw(table_pad, 1, 112, "Total");
    // Print the table Data
    temp = mem_list;
    int row = 3;
    while (temp != NULL){
        mvwprintw(table_pad, row, 2, "%d", temp->member.id);
        mvwprintw(table_pad, row, 11, "%s", temp->member.first_name);
        mvwprintw(table_pad, row, 28, "%s", temp->member.last_name);
        mvwprintw(table_pad, row, 44, "%s", temp->member.address);
        mvwprintw(table_pad, row, 77, "%s", temp->member.member_type);
        mvwprintw(table_pad, row, 94, "%d", temp->member.current_rentals);
        mvwprintw(table_pad, row, 103, "%d", temp->member.old_rentals);
        mvwprintw(table_pad, row, 112, "%d", temp->member.total_rentals);
        row += 3;
        temp = temp->next;
    }
    mvwprintw(table_pad, row+1, 2, "====> Press 'ANY' Key To Exit ... ");
    refresh ();
    prefresh(table_pad, 0, 0, 0, 0, LINES - 1, COLS - 1);
    getch();
    endwin();
}

void updateMember(MembersList *mem_list){
//////////////////////////// -- Variables -- //////////////////////////////    
    MembersList *temp = mem_list;
    char first_name[STRING_MAX_LENGTH];
    char last_name[STRING_MAX_LENGTH];
    char address[STRING_MAX_LENGTH];
    int member_type;
    char user_input[BUFFER_SIZE];
    int valid= 0;
    int check= 0;
    int mem_key, found = 0;
    do{
        printf("\n--> Please Enter The Member ID: ");
        check = scanf("%d", &mem_key);
        if (check != 1){
            printf("==> Invalid input! Please enter a number.\n");
            scanf("%*c");
        }
    }while (check != 1);
//////////////////////////// -- User Inputs  -- //////////////////////////////
    while (temp != NULL){
        if (temp->member.id == mem_key){
            found++;
            while (!valid){
                printf("--> First-Name: ");
                fflush (stdin);
                fgets (user_input, sizeof(user_input), stdin);
                strcpy (first_name, user_input);
                first_name[strcspn(first_name, "\n")] = '\0';
                int len = strlen(first_name);
                if (len == 0){
                    strcpy(first_name, temp->member.first_name);
                    break;
                }  
                if (len >= 2 && len <= 15) {
                    valid = 1;
                    for (int i = 0; i < len; i++) {
                        if (isdigit(first_name[i]) || ispunct(first_name[i])) {
                            valid = 0;
                            break;
                        }
                    }
                }
                if (!valid) {
                    printf("Name should be between 2 and 15 characters and contain only alphabetic characters.\n");
                }
            }
            strcpy(temp->member.first_name, first_name);

        valid = 0;
        while (!valid) {
            printf("--> Last-Name: ");
            fflush (stdin);
            fgets (user_input, sizeof(user_input), stdin);
            strcpy (last_name, user_input);
            last_name[strcspn(last_name, "\n")] = '\0';
            int len = strlen(last_name);
            if (len == 0){
                strcpy(last_name, temp->member.last_name);
                break;
            }              
            if (len >= 2 && len <= 15) {
                valid = 1;
                for (int i = 0; i < len; i++) {
                    if (isdigit(last_name[i]) || ispunct(last_name[i])) {
                        valid = 0;
                        break;
                    }
                }
            }
            if (!valid) {
                printf("Name should be between 2 and 15 characters and contain only alphabetic characters.\n");
            }
        }
        strcpy(temp->member.last_name, last_name);

        valid = 0;
        while (!valid) {
            printf("--> Address: ");
            fflush (stdin);
            fgets (user_input, sizeof(user_input), stdin);
            strcpy (address, user_input);
            address[strcspn(address, "\n")] = '\0';
            int len = strlen(address);
            if (len == 0){
            strcpy(address, temp->member.address);
            break;
            }  
            if (len >= 2 && len <= 15) {
                valid = 1;
                for (int i = 0; i < len; i++) {
                    if (!isprint(address[i])) {
                        valid = 0;
                        break;
                    }
                }
            }
            if (!valid) {
                printf("Address should be between 2 and 15 characters and contain only printable characters.\n");
            }
        }
        strcpy(temp->member.address, address);
        
        do{
            printf("--> Type (1: Student - 2: Teacher - 3: Visitor): ");
            check = scanf("%d", &member_type);
            if (check != 1 || member_type < 1 || member_type > 3){
                printf("==> Invalid input! Please enter an integer between 1 and 3.\n");
                scanf("%*c");
            }
        }while (check != 1 || member_type < 1 || member_type > 3);
        switch (member_type){
            case 1:
                strcpy(temp->member.member_type, "Student");
                temp->member.max_rentals = 2;
                temp->member.max_duration = 2;
                break;
            case 2:
                strcpy(temp->member.member_type, "Teacher");
                temp->member.max_rentals = 4;
                temp->member.max_duration = 3;
                break;
            case 3:
                strcpy(temp->member.member_type, "Teacher");
                temp->member.max_rentals = 4;
                temp->member.max_duration = 3;
                break;
            default:
                printf ("Member Type scanf Error !");
                exit(EXIT_FAILURE);
                break;
            }
        }
        temp = temp->next;
    }
    if (found == 0)
        printf("\n==> No Match Found.\n");
}

void deleteMember(MembersList **mem_list, int *mem_key){
    int key, found = 0;
    int check= 0;
    do{
        printf("\n--> Please Enter The Member ID: ");
        check = scanf("%d", &key);
        if (check != 1){
            printf("==> Invalid input! Please enter a number.\n");
            scanf("%*c");
        }
    }while (check != 1);
    MembersList *temp = NULL;
    if ((*mem_list)->member.id == key){
        found++;
        temp = *mem_list;
        *mem_list = (*mem_list)->next;
        *mem_key = 0;
        free(temp);
        printf("==> Member Deleted.\n");
    }
    else{
        MembersList *current = *mem_list;
        while (current->next != NULL){
            if (current->next->member.id == key){
                found++;
                temp = current->next;
                current->next = current->next->next;
                free(temp);
                printf("==> Member Deleted.\n");
                break;
            }
            else
                current = current->next;
        }
    }
    if (found == 0)
        printf("\n==> No Match Found.\n");
}

void searchMember(MembersList *mem_list){
    int mem_key, found = 0;
    int check= 0;
    do{
        printf("\n--> Please Enter The Member ID: ");
        check = scanf("%d", &mem_key);
        if (check != 1){
            printf("==> Invalid input! Please enter a number.\n");
            scanf("%*c");
        }
    }while (check != 1);
    MembersList *temp = mem_list;
    while (temp != NULL){
        if (temp->member.id == mem_key){
            found++;
            printf("\n==> Member Informations: \n");
            printf("----> ID: %d\n", temp->member.id);
            printf("----> First Name: %s\n", temp->member.first_name);
            printf("----> Last Name: %s\n", temp->member.last_name);
            printf("----> Address: %s\n", temp->member.address);
            printf("----> Member Type: %s\n", temp->member.member_type);
            printf("----> Current Rentals: %d\n", temp->member.current_rentals);
            printf("----> Old Rentals: %d\n", temp->member.old_rentals);
            printf("----> Total Rentals: %d\n", temp->member.total_rentals);
        }
        temp = temp->next;
    }
    if (found == 0)
        printf("\n==> No Match Found.\n");
}

void memberCureentRentals(MembersList *mem_list, int mem_key, RentalsList *rentals_list){
    RentalsList *temp1 = rentals_list;
    MembersList *temp2 = mem_list;
    if (rentalsListIsEmpty){
        while (temp2 != NULL){
            if (temp2->member.id == mem_key){
                temp2->member.current_rentals++;
            }
            temp2 = temp2->next;
        }
    }
    else{
        int count = 0;
        while (temp1 != NULL){
            if (temp1->rental.member_id == mem_key)
                count++;
            temp1 = temp1->next;
        }
        while (temp2 != NULL){
            if (temp2->member.id == mem_key){
                temp2->member.current_rentals++;
            }
            temp2 = temp2->next;
        }
    }
}

int membersListIsEmpty(MembersList const *mem_list){
    if (mem_list == NULL)
        return (1);
    else
        return (0);
}