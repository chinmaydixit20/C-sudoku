#include <gtk/gtk.h>
#include "sudoku.h"

//global declarations for simplicity
int **a;
int check_flag = 0, hint_flag = 0, hint_count = 0, save_flag = 0;
static GtkWidget *wid[N][N], *window;
//displays a dialog which displays error messages among others
void open_dialog(const char *str) {
	GtkWidget *dialog, *label, *content_area;
 	GtkDialogFlags flags;

 	flags = GTK_DIALOG_DESTROY_WITH_PARENT;
 	dialog = gtk_dialog_new_with_buttons ("Sudoku!", GTK_WINDOW(window), flags, "_Ok", GTK_RESPONSE_NONE, NULL);
 	content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
 	label = gtk_label_new(str);
	g_signal_connect_swapped (dialog, "response", G_CALLBACK (gtk_widget_destroy), dialog);
	gtk_container_add (GTK_CONTAINER (content_area), label);
 	gtk_widget_show_all (dialog);					     
}
/*
   -> function is called in main when any of the menu options are clicked
   -> Categories within new: easy, moderate, hard
   -> opens a file
   -> saves a file
   -> refreshes the board
*/
static void menu_event(GtkWidget* widget, gpointer data) {
	char str[2];
	enum difficulty diff;
	if(!strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(widget)), "Easy") ||
	   !strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(widget)), "Moderate") ||
	   !strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(widget)), "Hard")) {
	   	if(!strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(widget)), "Easy"))
	   		diff = EASY;
	   	else if(!strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(widget)), "Moderate"))
	   		diff = MODERATE;
	   	else if(!strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(widget)), "Hard"))
	   		diff = HARD;		
		/*if(!generateSudoku(a, diff))
			open_dialog("Bad Puzzle!");*/
		while(1)
			if(generateSudoku(a, diff))
				break;		
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				gtk_entry_set_text(GTK_ENTRY(wid[i][j]), " ");
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				gtk_entry_set_text(GTK_ENTRY(wid[i][j]), " ");
				strcpy(str, "0");
				sprintf(str, "%d", a[i][j]);
				if(strcmp(str, "0\0") != 0)
					gtk_entry_set_text(GTK_ENTRY(wid[i][j]), str);
			}
		}
		hint_flag = 1;
		check_flag = 1;
		hint_count = 0;
	}
	
	else if(!strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(widget)), "Open")) {
		GtkWidget *dialog;
		dialog = gtk_file_chooser_dialog_new("Choose a File", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_OPEN, 
					     "_Cancel", GTK_RESPONSE_CANCEL, "_Ok", GTK_RESPONSE_OK, NULL);
		gtk_widget_show_all(dialog);
		gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
		if(resp == GTK_RESPONSE_OK) {
			resume(a, gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
			sol = (int **)malloc(sizeof(int *) * N);
			for(int i = 0; i < N; i++)
				sol[i] = (int *)malloc(sizeof(int) * N);
			copySol(sol, a);
			if(!solve(sol))
				open_dialog("Incorrect Sudoku!");
			for(int i = 0; i < N; i++)
				for(int j = 0; j < N; j++)
					gtk_entry_set_text(GTK_ENTRY(wid[i][j]), " ");		
			for(int i = 0; i < N; i++) {
				for(int j = 0; j < N; j++) {
					strcpy(str, "0");
					sprintf(str, "%d", a[i][j]);
					if(strcmp(str, "0\0"))
						gtk_entry_set_text(GTK_ENTRY(wid[i][j]), str);
				}
			}
			gtk_widget_destroy(dialog);
			hint_flag = 1;
			check_flag = 1;
			hint_count = 0;
		}
		else if(resp == GTK_RESPONSE_CANCEL) 
			gtk_widget_destroy(dialog);
	}
	
	else if(!strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(widget)), "Save")) {
		GtkWidget *dialog;
		dialog = gtk_file_chooser_dialog_new("Save", GTK_WINDOW(window), GTK_FILE_CHOOSER_ACTION_SAVE, 
					     "_Cancel", GTK_RESPONSE_CANCEL, "_Ok", GTK_RESPONSE_OK, NULL);
		for(int i = 0; i < N; i++) { 
			for(int j = 0; j < N; j++) {
				if(strcmp(gtk_entry_get_text(GTK_ENTRY(wid[i][j])), " ") != 0) {
					save_flag = 1;
					break;	
				}
			}
		}			
		if(save_flag) {			
			gtk_widget_show_all(dialog);
			gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
			if(resp == GTK_RESPONSE_OK) {
				saveSudoku(a, gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
				gtk_widget_destroy(dialog);
			}
			else if(resp == GTK_RESPONSE_CANCEL) 
				gtk_widget_destroy(dialog);
		}
		else 
			open_dialog("Blank file cannot be saved!");		
	}
	else if(!strcmp(gtk_menu_item_get_label(GTK_MENU_ITEM(widget)), "Refresh")) {
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				gtk_entry_set_text(GTK_ENTRY(wid[i][j]), " ");
		hint_flag = 0;
		check_flag = 0;		
	}	
}
//function being used for storing UI data in globally declared array 'a'	
void get_element() {
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			if(!strcmp(gtk_entry_get_text(GTK_ENTRY(wid[i][j])), " "))
				a[i][j] = 0;
			else	
				a[i][j] = atoi(gtk_entry_get_text(GTK_ENTRY(wid[i][j])));
		}
	}						
}
/*function to get hints
  maximum of 4 hints available	
*/
void hint_sudoku(GtkWidget *widget, gpointer data) {
	if(hint_flag && hint_count < 4) {
		get_element();
		getHint(a);
		hint_count++;
		char str[2];
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				gtk_entry_set_text(GTK_ENTRY(wid[i][j]), " ");
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				strcpy(str, "0");
				sprintf(str, "%d", a[i][j]);
				if(strcmp(str, "0\0"))
					gtk_entry_set_text(GTK_ENTRY(wid[i][j]), str);
			}
		}
	}
	if(hint_count >= 4)
		open_dialog("Max. no of Hints exceeded!");	
}
//function to solve user input or generated sudoku
void solve_sudoku(GtkWidget *widget, gpointer data) {
	get_element();
	if(!solve(a))
		open_dialog("Incorrect Sudoku!");
	char str[2];
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			strcpy(str, "0");
			sprintf(str, "%d", a[i][j]);
			gtk_entry_set_text(GTK_ENTRY(wid[i][j]), str);
		}
	}
	hint_flag = check_flag = 0;
}	
//function to cross-check whether solved puzzle is correct
void check_sudoku(GtkWidget *widget, gpointer data) {
	if(check_flag) {
		get_element();
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				if(!a[i][j]) {
					open_dialog("Solve the Sudoku first!");
					return;
				}	
		if(check(a)) {
			open_dialog("Solved Correctly!!");
			hint_flag = 0;
		}	
		else
			open_dialog("Wrong entries");	
	}			
}
	
int main(int argc, char *argv[]) {
	int i, j;
	const char *file[] = {"New", "Open", "Save", "Refresh"};
	const char *new[] = {"Easy", "Moderate", "Hard"};
	
	//initialising 2d array a and allocating memory
	a = (int **)malloc(sizeof(int *) * N);
	for(int i = 0; i < N; i++)
		a[i] = (int *)malloc(sizeof(int) * N);
		
	for(i = 0; i < N; i++) 
		for(j = 0; j < N; j++)
			a[i][j] = 0;
			
	//GtkWidget declarations		
	gtk_init(&argc, &argv);
	GtkWidget *vbox, *hbox, *separator, *button, *file_menu, *menu_bar, *menu_item, *new_menu, *sep;
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(window), "Sudoku!");
	vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	file_menu = gtk_menu_new();
	new_menu = gtk_menu_new();
	menu_bar = gtk_menu_bar_new();
	sep = gtk_separator_menu_item_new();
	
	//process which generates the menu bar visible in the UI
	menu_item = gtk_menu_item_new_with_label("File");
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), file_menu);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu_item);
	for(i = 0; i < 4; i++) {
		menu_item = gtk_menu_item_new_with_label(file[i]);
		gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), menu_item);
		if(i)
			g_signal_connect(menu_item, "activate", G_CALLBACK(menu_event), NULL);
		else
			gtk_menu_item_set_submenu(GTK_MENU_ITEM(menu_item), new_menu);
		if(i == 2)
			gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), sep);		
	}
	
	for(i = 0; i < 3; i++) {
		menu_item = gtk_menu_item_new_with_label(new[i]);
		gtk_menu_shell_append(GTK_MENU_SHELL(new_menu), menu_item);
		g_signal_connect(menu_item, "activate", G_CALLBACK(menu_event), NULL);
	}
	
	//generates the UI main components
	gtk_box_pack_start(GTK_BOX(vbox), menu_bar, 0, 0, 0);
	for(i = 0; i < N; i++) {
		hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
		for(j = 0; j < N; j++) {
			wid[i][j] = gtk_entry_new();
			gtk_entry_set_max_length(GTK_ENTRY(wid[i][j]), 2);
			gtk_entry_set_width_chars(GTK_ENTRY(wid[i][j]), 2);
			gtk_box_pack_start(GTK_BOX(hbox), wid[i][j], 0, 0, 0);
			if(!((j + 1) % 3)) {
				separator = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
				gtk_box_pack_start(GTK_BOX(hbox), separator, 0, 0, 1);
			}	 
		}
		gtk_box_pack_start(GTK_BOX(vbox), hbox, 0,0,0);
		if(!((i + 1) % 3)) {
			separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
			gtk_box_pack_start(GTK_BOX(vbox), separator, 0, 0, 0);
		}
	}
	
	//initialises the wid[][] array
	for(i = 0; i < N; i++)
			for(j = 0; j < N; j++)
				gtk_entry_set_text(GTK_ENTRY(wid[i][j]), " ");	
	
	//various buttons 	
	button = gtk_button_new_with_label("Solve the Sudoku");
	g_signal_connect(button, "clicked", G_CALLBACK(solve_sudoku), NULL);
	gtk_box_pack_start(GTK_BOX(vbox), button, 0, 0, 0);	
	
	button = gtk_button_new_with_label("Check");
	g_signal_connect(button, "clicked", G_CALLBACK(check_sudoku), NULL);
	gtk_box_pack_start(GTK_BOX(vbox), button, 0, 0, 0);
	
	button = gtk_button_new_with_label("Hint");
	g_signal_connect(button, "clicked", G_CALLBACK(hint_sudoku), NULL);
	gtk_box_pack_start(GTK_BOX(vbox), button, 0, 0, 0);
			
	g_signal_connect(window, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
	gtk_container_add(GTK_CONTAINER(window), vbox);
	gtk_widget_show_all(window);
	gtk_main();
		
	return 0;
}			
