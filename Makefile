app:
	gcc main.c utilities.c menus.c members.c documents.c rentals.c late.c init_members.c init_documents.c init_rentals.c -lncurses -o app
clean: 
	del ".\*.bin"