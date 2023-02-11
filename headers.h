#ifndef HEADERS_H
#define HEADERS_H
#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif
#define BUFFER_SIZE 256
#define STRING_MAX_LENGTH 16
////////////////////////////////////////////// -- Structs -- //////////////////////////////////////////////////////////////////////////////////////////
typedef struct Date Date;
typedef struct MemberData MemberData;
typedef struct MembersList MembersList;
typedef struct DocumentData DocumentData;
typedef struct DocumentsList DocumentsList;
typedef struct RentalData RentalData;
typedef struct RentalsList RentalsList;
typedef struct LateList LateList;
////////////////////////////////////////////// -- Utilities -- //////////////////////////////////////////////////////////////////////////////////////////
int is_alpha_space(int c);
int is_print(int c);
void check_string_is_valid(char *msg, char *data, int (*rule)(int));
////////////////////////////////////////////// -- Members_Initialisation -- //////////////////////////////////////////////////////////////////////////////////////////
void writeMembersFile(MembersList *mem_list);
MembersList *readMembersFile(MembersList *mem_list, int *mem_key);
MembersList *readNextFromMembersFile(MembersList *mem_list, FILE *members_file);
void writeMembersKey(int mem_key);
int readMembersKey();
////////////////////////////////////////////// -- Documents_Initialisation -- //////////////////////////////////////////////////////////////////////////////////////////
void writeDocumentsFile(DocumentsList *doc_list);
DocumentsList *readDocumentsFile(DocumentsList *doc_list, int *doc_key);
DocumentsList *readNextFromDocumentsFile(DocumentsList *doc_list, FILE *documents_file);
void writeDocumentsKey(int doc_key);
int readDocumentsKey();
////////////////////////////////////////////// -- Rentals_Initialisation -- //////////////////////////////////////////////////////////////////////////////////////////
void writeRentalsFile(RentalsList *rentals_list);
RentalsList *readRentalsFile(RentalsList *rentals_list, int *rental_key);
RentalsList *readNextFromRentalsFile(RentalsList *rentals_list, FILE *rentals_file);
void writeRentalsKey(int rental_key);
int readRentalsKey();
////////////////////////////////////////////// -- Menus -- //////////////////////////////////////////////////////////////////////////////////////////
void menu(MembersList *mem_list, int mem_key, DocumentsList *doc_list, int doc_key, RentalsList *rentals_list, int rental_key, LateList *late_list);
void membersMenu(MembersList *mem_list, int mem_key, DocumentsList *doc_list, int doc_key, RentalsList *rentals_list, int rental_key, LateList *late_list);
void documentsMenu(MembersList *mem_list, int mem_key, DocumentsList *doc_list, int doc_key, RentalsList *rentals_list, int rental_key, LateList *late_list);
void rentalsMenu(MembersList *mem_list, int mem_key, DocumentsList *doc_list, int doc_key, RentalsList *rentals_list, int rental_key, LateList *late_list);
void lateMenu(MembersList *mem_list, int mem_key, DocumentsList *doc_list, int doc_key, RentalsList *rentals_list, int rental_key, LateList *late_list);
//////////////////////////////////////////////// -- Members -- /////////////////////////////////////////////////////////////////////////////////////////
MembersList* createMember(MembersList *mem_list, int *mem_key);
void readMembersList(MembersList *mem_list);
void updateMember (MembersList *mem_list);
void deleteMember(MembersList **mem_list, int *mem_key);
void searchMember(MembersList *mem_list);
void memberCureentRentals (MembersList *mem_list, int mem_key, RentalsList *rentals_list);
int membersListIsEmpty(MembersList const *mem_list);
///////////////////////////////////////////////// -- Documents -- ////////////////////////////////////////////////////////////////////////////////////////
DocumentsList* createDocument(DocumentsList *doc_list, int *doc_key);
void readDocumentsList(DocumentsList *doc_list);
void updateDocument (DocumentsList *doc_list);
void deleteDocument(DocumentsList **doc_list, int *doc_key);
void searchDocument(DocumentsList *doc_list);
void documentCureentRentals (DocumentsList *doc_list, int doc_key, RentalsList *rentals_list);
int documentsListIsEmpty(DocumentsList const *doclist);
///////////////////////////////////////////////// -- Rentals -- /////////////////////////////////////////////////////////////////////////////////////////
RentalsList* createRental(RentalsList *rentals_list, int *rental_key, MembersList *mem_list, DocumentsList *doc_list, LateList *late_list);
void readRentalsList(RentalsList *rentals_list);
void updateRental (RentalsList *rentals_list, MembersList *mem_list, DocumentsList *doc_list, LateList *late_list);
void deleteRental(RentalsList **rentals_list, MembersList *mem_list, DocumentsList *doc_list, int *rental_key);
void searchRental(RentalsList *rentals_list);
int rentalsListIsEmpty(RentalsList const *rentals_list);
/////////////////////////////////////////////////// -- Late -- ////////////////////////////////////////////////////////////////////////////////////////////
void createLateList(LateList **late_list, RentalsList *rentals_list);
void readLateList(LateList *late_list);
void searchLate(LateList *late_list);
int lateListIsEmpty(LateList const *late_list);

#endif