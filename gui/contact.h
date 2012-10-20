#ifndef H_CONTACT
#define H_CONTACT

t_contact *ajouter_contact(char* name,
			   char* login,
			   char* pic,
			   t_window *window);
void OnDPress_contact(GtkTreeView       *tree_view,
		      GtkTreePath       *path,
		      GtkTreeViewColumn *column,
		      t_window *window);
t_contact *identite_contact(GtkTreePath *path, t_window *window);
int init_list_contact(t_window * window);
int charger_sauvegarde(t_window * window);
void OnBok_enreg_con(GtkWidget *widget, t_window * window);
void OnButton_contact_ajouter(GtkWidget *widget, t_window * window);
void OnButton_contact_supprimer(GtkWidget *widget, t_window * window);
void OnButton_contact_modifier(GtkWidget *widget, t_window * window);
void OnKill_con(GtkWidget *widget, t_window * window);
int init_dialogue(t_window_d * window_d, t_window * window);

#endif
