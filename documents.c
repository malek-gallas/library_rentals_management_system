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

DocumentsList* createDocument (DocumentsList *doc_list, int *doc_key){
    printf ("\n\n\t\t\t\t\t***** Create Document *****\n\n");
//////////////////////////// -- Variables -- //////////////////////////////
    DocumentsList *new= NULL;
    new= (DocumentsList *)malloc(sizeof(DocumentsList));
    char  title[STRING_MAX_LENGTH];
    int stock;
    int doc_type;
    char article_author[STRING_MAX_LENGTH];
    Date publish_date;
    char book_author[STRING_MAX_LENGTH];
    char editor[STRING_MAX_LENGTH];
    Date edition_date;
    int freq;
    struct Localisation local;
    int check= 0;
//////////////////////////// -- User Inputs -- //////////////////////////////
    check_string_is_valid("--> Title: ", title, is_print);
    strcpy(new->document.title, title);
////////////////////////////////////////////////////////////////////////////////////////////////////
    do{
        printf("--> Stock: ");
        check = scanf("%d", &stock);
        if (check != 1){
            printf("==> Invalid input! Please enter a number.\n");
            scanf("%*c");
        }
    }while (check != 1);
    new->document.stock= stock;
////////////////////////////////////////////////////////////////////////////////////////////////////
    check= 0;
    do{
        printf("--> Type (1: Article - 2: Book - 3: Magazine): ");
        check = scanf("%d", &doc_type);
        if (check != 1 || doc_type < 1 || doc_type > 3){
            printf("==> Invalid input! Please enter an integer between 1 and 3.\n");
            scanf("%*c");
        }
    }while (check != 1 || doc_type < 1 || doc_type > 3);
    switch (doc_type){
    case 1:
        strcpy (new->document.doc_type, "Article");
    /////////////////////////////////////////////////////////////////////////////////////////////////
        check_string_is_valid("--> Article-Author: ", article_author, is_alpha_space);
        strcpy(new->document.article_author, article_author);
    ////////////////////////////////////////////////////////////////////////////////////////////////////
        printf ("--> Publish-Date: \n");
        check= 0;
        do{
            printf("----> Day: ");
            check = scanf("%d", &publish_date.day);
            if (check != 1){
                printf("==> Invalid input! Please enter a number.\n");
                scanf("%*c");
            }
        }while (check != 1);
        new->document.publish_date.day= publish_date.day;
    ////////////////////////////////////////////////////////////////////////////////////////////////////
        check= 0;
        do{
            printf("----> Month: ");
            check = scanf("%d", &publish_date.month);
            if (check != 1){
                printf("==> Invalid input! Please enter a number.\n");
                scanf("%*c");
            }
        }while (check != 1);
        new->document.publish_date.month= publish_date.month;
    ////////////////////////////////////////////////////////////////////////////////////////////////////
        check= 0;
        do{
            printf("----> Year: ");
            check = scanf("%d", &publish_date.year);
            if (check != 1){
                printf("==> Invalid input! Please enter a number.\n");
                scanf("%*c");
            }
        }while (check != 1);
        new->document.publish_date.year= publish_date.year;
        break;
    case 2:
        strcpy (new->document.doc_type, "Book");
    ////////////////////////////////////////////////////////////////////////////////////////////////////
        check_string_is_valid("--> Book-Author: ", book_author, is_alpha_space);
        strcpy(new->document.book_author, book_author);
    ////////////////////////////////////////////////////////////////////////////////////////////////////
        check_string_is_valid("--> Editor: ", editor, is_alpha_space);
        strcpy(new->document.editor, editor);
    ////////////////////////////////////////////////////////////////////////////////////////////////////
        printf ("--> Edition-Date: \n");
        check= 0;
        do{
            printf("----> Day: ");
            check = scanf("%d", &edition_date.day);
            if (check != 1){
                printf("==> Invalid input! Please enter a number.\n");
                scanf("%*c");
            }
        }while (check != 1);
        new->document.edition_date.day= edition_date.day;
    ////////////////////////////////////////////////////////////////////////////////////////////////////
        check= 0;
        do{
            printf("----> Month: ");
            check = scanf("%d", &edition_date.month);
            if (check != 1){
                printf("==> Invalid input! Please enter a number.\n");
                scanf("%*c");
            }
        }while (check != 1);
        new->document.edition_date.month= edition_date.month;
    ////////////////////////////////////////////////////////////////////////////////////////////////////
        check= 0;
        do{
            printf("----> Year: ");
            check = scanf("%d", &edition_date.year);
            if (check != 1){
                printf("==> Invalid input! Please enter a number.\n");
                scanf("%*c");
            }
        }while (check != 1);
        new->document.edition_date.year= edition_date.year;
        break;
    case 3:
        strcpy (new->document.doc_type, "Magazine");
    ////////////////////////////////////////////////////////////////////////////////////////////////////
        check= 0;
        do{
            printf("--> Published (1: Daily - 2: Weekly - 3: Monthly): ");
            check = scanf("%d", &freq);
            if (check != 1 || freq < 1 || freq > 3){
                printf("==> Invalid input! Please enter an integer between 1 and 3.\n");
                scanf("%*c");
            }
        }while (check != 1 || freq < 1 || freq > 3);
        switch (freq){
        case 1:
            strcpy (new->document.freq, "Daily");
            break;
        case 2:
            strcpy (new->document.freq, "Weekly");
            break;    
        case 3:
            strcpy (new->document.freq, "Monthly");
            break;
        default:
            printf ("Magazine Frequency scanf Error !");
            exit(EXIT_FAILURE);
            break;
        }
    /*default:
        printf ("Document Type scanf Error !");
        exit(EXIT_FAILURE);
        break;*/
    }
////////////////////////////////////////////////////////////////////////////////////////////////////
    check= 0;
    do{
        printf("--> Room: ");
        check = scanf("%d", &local.room);
        if (check != 1){
            printf("==> Invalid input! Please enter a number.\n");
            scanf("%*c");
        }
    }while (check != 1);
    new->document.local.room= local.room;
////////////////////////////////////////////////////////////////////////////////////////////////////
    check= 0;
    do{
        printf("--> Department: ");
        check = scanf("%d", &local.department);
        if (check != 1){
            printf("==> Invalid input! Please enter a number.\n");
            scanf("%*c");
        }
    }while (check != 1);
    new->document.local.department= local.department;
//////////////////////////// -- Statistics -- //////////////////////////////    
    new->document.current_rentals= 0;
    new->document.old_rentals= 0;
    new->document.total_rentals= 0; 
//////////////////////////// -- Key & Pointer -- //////////////////////////////
    new->next= NULL;
    *doc_key= *doc_key+1;
    new->document.code= *doc_key;
//////////////////////////// -- Implementation -- //////////////////////////////    
    if (doc_list == NULL){
        printf ("==> Document Added.\n");
        return (new);
    }
    else{
        DocumentsList *temp= doc_list;
        while (temp->next != NULL){
            temp= temp->next;
        }
        temp->next= new;
        printf ("==> Document Added.\n");
        return (doc_list);
    }
}

void readDocumentsList (DocumentsList *doc_list){
    DocumentsList *temp = doc_list;
    initscr();
    raw();
    //WINDOW *table_win = newwin(getmaxy(stdscr), getmaxx(stdscr), 0, 0);
    WINDOW *table_pad = newpad(getmaxy(stdscr), getmaxx(stdscr));
    // Draw horizontal lines
    mvwhline(table_pad, 0, 2, ACS_HLINE, 119);
    mvwhline(table_pad, 2, 2, ACS_HLINE, 119);
    int num_rows = 2;
    while (temp != NULL){
        mvwhline(table_pad, num_rows+3, 2, ACS_HLINE, 119);
        num_rows = num_rows + 3;
        temp = temp->next;
    }
    // Draw vertical lines
    mvwvline(table_pad, 1, 1, ACS_VLINE, num_rows-1);
    mvwvline(table_pad, 1, 10, ACS_VLINE, num_rows-1);
    mvwvline(table_pad, 1, 27 , ACS_VLINE, num_rows-1);
    mvwvline(table_pad, 1, 44, ACS_VLINE, num_rows-1);
    mvwvline(table_pad, 1, 61, ACS_VLINE, num_rows-1);
    mvwvline(table_pad, 1, 94, ACS_VLINE, num_rows-1);
    mvwvline(table_pad, 1, 103, ACS_VLINE, num_rows-1);
    mvwvline(table_pad, 1, 112, ACS_VLINE, num_rows-1);
    mvwvline(table_pad, 1, 121, ACS_VLINE, num_rows-1);
    // Print the table headers
    mvwprintw(table_pad, 1, 2, "Code");
    mvwprintw(table_pad, 1, 11, "Title");
    mvwprintw(table_pad, 1, 28, "Stock");
    mvwprintw(table_pad, 1, 45, "Type");
    mvwprintw(table_pad, 1, 62, "Infos");
    mvwprintw(table_pad, 1, 95, "Current");
    mvwprintw(table_pad, 1, 104, "Room");
    mvwprintw(table_pad, 1, 113, "Department");
    // Print the table Data
    temp = doc_list;
    int row = 3;
    while (temp != NULL){
        mvwprintw(table_pad, row, 2, "%d", temp->document.code);
        mvwprintw(table_pad, row, 11, "%s", temp->document.title);
        mvwprintw(table_pad, row, 28, "%d", temp->document.stock);
        mvwprintw(table_pad, row, 45, "%s", temp->document.doc_type);
        if (strcmp(temp->document.doc_type, "Article")==0){
            mvwprintw(table_pad, row, 62, "Author: %s", temp->document.article_author);
            mvwprintw(table_pad, row+1, 62, "Publish-Date: %d/%d/%d", temp->document.publish_date.day,
            temp->document.publish_date.month, temp->document.publish_date.year);
        }
        else if (strcmp(temp->document.doc_type, "Book")==0){
            mvwprintw(table_pad, row, 62, "Author: %s", temp->document.book_author);
            mvwprintw(table_pad, row, 75, "-- ");
            mvwprintw(table_pad, row, 79, "Editor: %s", temp->document.editor);
            mvwprintw(table_pad, row+1, 62, "Edition-Date: %d/%d/%d", temp->document.edition_date.day,
            temp->document.edition_date.month, temp->document.edition_date.year);
        }
        else if (strcmp(temp->document.doc_type, "Magazine")==0){
            mvwprintw(table_pad, row, 62, "Published: %s", temp->document.freq);
        }
        mvwprintw(table_pad, row, 95, "%d", temp->document.current_rentals);
        mvwprintw(table_pad, row, 104, "%d", temp->document.local.room);
        mvwprintw(table_pad, row, 113, "%d", temp->document.local.department);
        row += 3;
        temp = temp->next;
    }
    mvwprintw(table_pad, row+1, 2, "====> Press 'ANY' Key To Exit ... ");
    refresh ();
    prefresh(table_pad, 0, 0, 0, 0, LINES - 1, COLS - 1);
    getch();
    endwin();
}

void updateDocument (DocumentsList *doc_list){
//////////////////////////// -- Variables -- //////////////////////////////
    DocumentsList *temp = doc_list;
    int doc_key, found=0;
    char  title[STRING_MAX_LENGTH];
    int stock;
    int doc_type;
    char article_author[STRING_MAX_LENGTH];
    Date publish_date;
    char book_author[STRING_MAX_LENGTH];
    char editor[STRING_MAX_LENGTH];
    Date edition_date;
    int freq;
    struct Localisation{ 
        int room;
        int department;
    }local;
    char user_input[STRING_MAX_LENGTH];
    int valid= 0;
    int check= 0;
    do{
        printf("\n--> Please Enter The Document ID: ");
        check = scanf("%d", &doc_key);
        if (check != 1){
            printf("==> Invalid input! Please enter a number.\n");
            scanf("%*c");
        }
    }while (check != 1);
//////////////////////////// -- User Inputs -- //////////////////////////////
    while (temp != NULL){
        if (temp->document.code == doc_key){
            found++;
            while (!valid) {
                printf("--> Title: ");
                fflush (stdin);
                fgets (user_input, sizeof(user_input), stdin);
                strcpy (title, user_input);
                title[strcspn(title, "\n")] = '\0';
                int len = strlen(title);
                if (len == 0){
                    strcpy(title, temp->document.title);
                    break;
                }  
                if (len >= 2 && len <= 15) {
                    valid = 1;
                    for (int i = 0; i < len; i++) {
                        if (isdigit(title[i]) || ispunct(title[i])) {
                            valid = 0;
                            break;
                        }
                    }
                }
                if (!valid) {
                    printf("Name should be between 2 and 15 characters and contain only alphabetic characters.\n");
                }
            }
            strcpy(temp->document.title, title);

            check= 0;
            do{
                printf("--> Stock: ");
                check = scanf("%d", &stock);
                if (check != 1){
                    printf("==> Invalid input! Please enter a number.\n");
                    scanf("%*c");
                }
            }while (check != 1);
            temp->document.stock= stock;

            check= 0;
            do{
                printf("--> Type (1: Article - 2: Book - 3: Magazine): ");
                check = scanf("%d", &doc_type);
                if (check != 1 || doc_type < 1 || doc_type > 3){
                    printf("==> Invalid input! Please enter an integer between 1 and 3.\n");
                    scanf("%*c");
                }
            }while (check != 1 || doc_type < 1 || doc_type > 3);
            switch (doc_type){
            case 1:
                strcpy (temp->document.doc_type, "Article");
                valid=0 ;
                while (!valid) {
                    printf("--> Article-Author: ");
                    fflush (stdin);
                    fgets (user_input, sizeof(user_input), stdin);
                    strcpy (article_author, user_input);
                    article_author[strcspn(article_author, "\n")] = '\0';
                    int len = strlen(article_author);
                    if (len == 0){
                    strcpy(article_author, temp->document.article_author);
                    break;
                    }  
                    if (len >= 2 && len <= 15) {
                        valid = 1;
                        for (int i = 0; i < len; i++) {
                            if (isdigit(article_author[i]) || ispunct(article_author[i])) {
                                valid = 0;
                                break;
                            }
                        }
                    }
                    if (!valid) {
                        printf("Name should be between 2 and 15 characters and contain only alphabetic characters.\n");
                    }
                }
                strcpy(temp->document.article_author, article_author);
                printf ("--> Publish-Date: \n");
                check= 0;
                do{
                    printf("----> Day: ");
                    check = scanf("%d", &publish_date.day);
                    if (check != 1){
                        printf("==> Invalid input! Please enter a number.\n");
                        scanf("%*c");
                    }
                }while (check != 1);
                temp->document.publish_date.day= publish_date.day;
                check= 0;
                do{
                    printf("----> Month: ");
                    check = scanf("%d", &publish_date.month);
                    if (check != 1){
                        printf("==> Invalid input! Please enter a number.\n");
                        scanf("%*c");
                    }
                }while (check != 1);
                temp->document.publish_date.month= publish_date.month;
                check= 0;
                do{
                    printf("----> Year: ");
                    check = scanf("%d", &publish_date.year);
                    if (check != 1){
                        printf("==> Invalid input! Please enter a number.\n");
                        scanf("%*c");
                    }
                }while (check != 1);
                temp->document.publish_date.year= publish_date.year;
                break;
            case 2:
                strcpy (temp->document.doc_type, "Book");
                valid=0 ;
                while (!valid) {
                    printf("--> Book-Author: ");
                    fflush (stdin);
                    fgets (user_input, sizeof(user_input), stdin);
                    strcpy (book_author, user_input);
                    book_author[strcspn(book_author, "\n")] = '\0';
                    int len = strlen(book_author);
                    if (len == 0){
                    strcpy(book_author, temp->document.book_author);
                    break;
                }  
                    if (len >= 2 && len <= 15) {
                        valid = 1;
                        for (int i = 0; i < len; i++) {
                            if (isdigit(book_author[i]) || ispunct(book_author[i])) {
                                valid = 0;
                                break;
                            }
                        }
                    }
                    if (!valid) {
                        printf("Name should be between 2 and 15 characters and contain only alphabetic characters.\n");
                    }
                }
                strcpy(temp->document.book_author, book_author);
                valid=0 ;
                while (!valid) {
                    printf("--> Editor: ");
                    fflush (stdin);
                    fgets (user_input, sizeof(user_input), stdin);
                    strcpy (editor, user_input);
                    editor[strcspn(editor, "\n")] = '\0';
                    int len = strlen(editor);
                    if (len == 0){
                    strcpy(editor, temp->document.editor);
                    break;
                    }  
                    if (len >= 2 && len <= 15) {
                        valid = 1;
                        for (int i = 0; i < len; i++) {
                            if (isdigit(editor[i]) || ispunct(editor[i])) {
                                valid = 0;
                                break;
                            }
                        }
                    }
                    if (!valid) {
                        printf("Name should be between 2 and 15 characters and contain only alphabetic characters.\n");
                    }
                }
                strcpy(temp->document.editor, editor);
                printf ("--> Edition-Date: \n");
                check= 0;
                do{
                    printf("----> Day: ");
                    check = scanf("%d", &edition_date.day);
                    if (check != 1){
                        printf("==> Invalid input! Please enter a number.\n");
                        scanf("%*c");
                    }
                }while (check != 1);
                temp->document.edition_date.day= edition_date.day;
                check= 0;
                do{
                    printf("----> Month: ");
                    check = scanf("%d", &edition_date.month);
                    if (check != 1){
                        printf("==> Invalid input! Please enter a number.\n");
                        scanf("%*c");
                    }
                }while (check != 1);
                temp->document.edition_date.month= edition_date.month;
                check= 0;
                do{
                    printf("----> Year: ");
                    check = scanf("%d", &edition_date.year);
                    if (check != 1){
                        printf("==> Invalid input! Please enter a number.\n");
                        scanf("%*c");
                    }
                }while (check != 1);
                temp->document.edition_date.year= edition_date.year;
                break;
            case 3:
                strcpy (temp->document.doc_type, "Magazine");
                check= 0;
                do{
                    printf("--> Published (1: Daily - 2: Weekly - 3: Monthly): ");
                    check = scanf("%d", &freq);
                    if (check != 1 || freq < 1 || freq > 3){
                        printf("==> Invalid input! Please enter an integer between 1 and 3.\n");
                        scanf("%*c");
                    }
                }while (check != 1 || freq < 1 || freq > 3);
                switch (freq){
                case 1:
                    strcpy (temp->document.freq, "Daily");
                    break;
                case 2:
                    strcpy (temp->document.freq, "Weekly");
                    break;    
                case 3:
                    strcpy (temp->document.freq, "Monthly");
                    break;
                default:
                    printf ("Magazine Frequency scanf Error !");
                    exit(EXIT_FAILURE);
                    break;
                }
            default:
                printf ("Document Type scanf Error !");
                exit(EXIT_FAILURE);
                break;
            }
            check= 0;
            do{
                printf("--> Room: ");
                check = scanf("%d", &local.room);
                if (check != 1){
                    printf("==> Invalid input! Please enter a number.\n");
                    scanf("%*c");
                }
            }while (check != 1);
            temp->document.local.room= local.room;
            check= 0;
            do{
                printf("--> Department: ");
                check = scanf("%d", &local.department);
                if (check != 1){
                    printf("==> Invalid input! Please enter a number.\n");
                    scanf("%*c");
                }
            }while (check != 1);
            temp->document.local.department= local.department;
            }
            temp = temp->next;
        }
        if (found == 0)
        printf ("\n==> No Match Found.\n");
}

void deleteDocument(DocumentsList **doc_list, int *doc_key){
    int key, found=0;
    int check= 0;
    do{
        printf("\n--> Please Enter The Document ID: ");
        check = scanf("%d", &key);
        if (check != 1){
            printf("==> Invalid input! Please enter a number.\n");
            scanf("%*c");
        }
    }while (check != 1);
    DocumentsList *temp;
    if((*doc_list)->document.code == key){
        found++;
        temp = *doc_list;
        *doc_list = (*doc_list)->next;
        *doc_key= 0;
        free(temp);
        printf ("==> Document Deleted.\n");
    }
    else{
        DocumentsList *current  = *doc_list;
        while(current->next != NULL){
            if(current->next->document.code == key){
                found++;
                temp = current->next;
                current->next = current->next->next;
                free(temp);
                printf ("==> Document Deleted.\n");
                break;
            }
            else
                current = current->next;
        }
    }
    if (found == 0)
        printf ("\n==> No Match Found.\n");
}

void searchDocument(DocumentsList *doc_list){
    int doc_key, found=0;
    int check= 0;
    do{
        printf("\n--> Please Enter The Document ID: ");
        check = scanf("%d", &doc_key);
        if (check != 1){
            printf("==> Invalid input! Please enter a number.\n");
            scanf("%*c");
        }
    }while (check != 1);
    DocumentsList *temp = doc_list;
    while (temp != NULL) {
        if (temp->document.code == doc_key){
            found++;
            printf("\n==> Document Informations: \n");
            printf ("----> ID: %d\n", temp->document.code);
            printf ("----> Title: %s\n", temp->document.title);
            printf ("----> Stock: %d\n", temp->document.stock);
            printf ("----> Document Type: %s\n", temp->document.doc_type);
            if (strcmp(temp->document.doc_type, "Article")==0){
                printf ("------> Article Author: %s\n", temp->document.article_author);
                printf ("------> Publish-Date: %d-", temp->document.publish_date.day);
                printf ("%d-", temp->document.publish_date.month);
                printf ("%d\n", temp->document.publish_date.year);
            }
            else if (strcmp(temp->document.doc_type, "Book")==0){
                printf ("------> Book Author: %s\n", temp->document.book_author);
                printf ("------> Book Editor: %s\n", temp->document.editor);
                printf ("------> Edition-Date: %d-", temp->document.edition_date.day);
                printf ("%d-", temp->document.edition_date.month);
                printf ("%d\n", temp->document.edition_date.year);
            }
            else if (strcmp(temp->document.doc_type, "Magazine")==0){
                printf ("------> Published: %s\n", temp->document.freq);
            }
            printf ("----> Room: %d\n", temp->document.local.room);
            printf ("----> Department: %d\n", temp->document.local.department);
            printf ("----> Current Rentals: %d\n", temp->document.current_rentals);
            printf ("----> Old Rentals: %d\n", temp->document.old_rentals);
            printf ("----> Total Rentals: %d\n", temp->document.total_rentals);
        }
        temp= temp->next ;
    }
    if (found == 0)
        printf ("\n==> No Match Found.\n");
}

void documentCureentRentals (DocumentsList *doc_list, int doc_key, RentalsList *rentals_list){
    RentalsList *temp1 = rentals_list;
    DocumentsList *temp2 = doc_list;
    if (documentsListIsEmpty){
        while (temp2 != NULL) {
            if (temp2->document.code == doc_key){
                temp2->document.current_rentals++;
            }   
        temp2= temp2->next;
        }
    }
    else{
        int count=0 ;
        while (temp1 != NULL){
            if (temp1->rental.document_id == doc_key)
                count++;
            temp1= temp1->next;
        }
        while (temp2 != NULL) {
        if (temp2->document.code == doc_key){
            temp2->document.current_rentals++;
        }   
        temp2= temp2->next;
        }
    }
}

int documentsListIsEmpty (DocumentsList const *doc_list){
    if (doc_list == NULL)
        return (1);
    else
        return (0);
}