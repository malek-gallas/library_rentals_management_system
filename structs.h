#ifndef STRUCTS_H
#define STRUCTS_H

struct Date     
{
    int day;
    int month;
    int year;
};
struct MemberData
{
    int id;
    char first_name[STRING_MAX_LENGTH];
    char last_name[STRING_MAX_LENGTH];
    char address[STRING_MAX_LENGTH];
    char member_type[STRING_MAX_LENGTH];
    int max_rentals;
    int max_duration;
    int current_rentals;
    int old_rentals;
    int total_rentals;
};
struct MembersList {
    struct MemberData member;
    struct MembersList *next;
};
struct DocumentData
{
    int code;
    char title[STRING_MAX_LENGTH];
    int stock;
    char doc_type[STRING_MAX_LENGTH];
    char article_author[STRING_MAX_LENGTH];
    Date publish_date;
    char book_author[STRING_MAX_LENGTH];
    char editor[STRING_MAX_LENGTH];
    Date edition_date;
    char freq[STRING_MAX_LENGTH];
    struct Localisation
    { 
        int room;
        int department;
    }local;
    int current_rentals;
    int old_rentals;
    int total_rentals;
};
struct DocumentsList {
    struct DocumentData document;
    struct DocumentsList *next;
};
struct RentalData
{
    int operation_id;
    int member_id;
    int document_id;
    Date rental_date;
    Date return_date;
    int real_return_date;
};
struct RentalsList
{
    struct RentalData rental;
    struct RentalsList *next;
};
struct LateList
{
    struct RentalData rental;
    struct LateList *next;
};

#endif