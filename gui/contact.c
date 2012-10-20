#include"headers.h"

t_contact *ajouter_contact(char* name,
			   char* login,
			   char* pic,
			   t_window *window)
{
  char *sUtf8;
  t_contact * p = g_malloc(sizeof(t_contact));
  
  sUtf8 = g_locale_to_utf8(name, -1, NULL, NULL, NULL);
  strcpy(p->name, sUtf8);
  g_free(sUtf8);

  sUtf8 = g_locale_to_utf8(login, -1, NULL, NULL, NULL);
  strcpy(p->login, sUtf8);
  g_free(sUtf8);

  sUtf8 = g_locale_to_utf8(pic, -1, NULL, NULL, NULL);
  strcpy(p->pic, sUtf8);
  g_free(sUtf8);
  
  p->open_diag = FALSE;
  p->socket = -1;
  p->mode= RIEN;
  strcpy(p->ip, "192.168.0.106");
  p->next = window->contacts;
  window->contacts = p;
  return p;
}

void OnDPress_contact(GtkTreeView       *tree_view,
		      GtkTreePath       *path,
		      GtkTreeViewColumn *column,
		      t_window *window)
{   
  column = column;
  tree_view = tree_view;

  t_window_d * window_d = g_malloc(sizeof(t_window_d));
  
  window_d->contact = identite_contact(path, window);
  
  if (window_d->contact != NULL){
    window_d->contact->open_diag = TRUE;
    window_d->contact->window_d  = window_d;

    init_dialogue(window_d, window);
    window_d->window = window ;
  }
  
}

t_contact *identite_contact(GtkTreePath *path, t_window *window)
{
  char *tmp ;
  GtkTreeIter iter;
  t_contact *p;
  
  /* nom du contact 2clique */
  
  gtk_tree_model_get_iter (GTK_TREE_MODEL(window->pListstore),
                           &iter,
                           path);
  gtk_tree_model_get(GTK_TREE_MODEL(window->pListstore),
		     &iter,
		     TEXT_COLUMN,
		     &tmp,
		     -1);

  /* recherche ds les contacts */
  p = window->contacts;
  while ( (p != NULL) && strcmp(tmp, p->name) ){
    p = p->next;
  }
  return p;
}

int charger_sauvegarde(t_window * window)
{
  /* contacts */
  /*user login pic*/
  FILE *contacts;
  int c ;
  char tab[3][30];
  int i=0;
  int j=0;

  if ((contacts = fopen("./contacts.tut","r+")) != NULL) {
    c = fgetc(contacts);
    while( !feof(contacts) ){
      if (c == ' '){
	tab[i][j]='\0';
	i++;
	j=0;
      } else {
	if (c=='\n'){
	  tab[i][j]='\0';
	  ajouter_contact( tab[0], 
			   tab[1],
			   tab[2],
			   window);
	  i=0;
	  j=0;
	} else {
	  tab[i][j] = c ;
	  j++;
	}
      }	
      c = fgetc(contacts);
    }
  
    fclose(contacts);
  } else {
    return 0;
  }
  return 1;
}

int init_list_contact(t_window * window)
{
  /* Creation de la barre de defilement*/
  window->pScrollbar = gtk_scrolled_window_new(NULL, NULL);
  gtk_box_pack_start(GTK_BOX(window->pVBox), window->pScrollbar, TRUE, TRUE, 0);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(window->pScrollbar), 
				 GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
  /* Creation de la liste*/
  window->pListstore = gtk_list_store_new(N_COLUMN, 
					  GDK_TYPE_PIXBUF,
					  G_TYPE_STRING);
  
  /*** Insertion contact ***/
  GdkPixbuf *pPixBufA;
  GtkTreeIter pIter;
  t_contact *p;

  p = window->contacts;
  while (p!= NULL){
    gtk_list_store_append(window->pListstore, &pIter);
    if(/*p->online_msn*/1){
      pPixBufA = gdk_pixbuf_new_from_file(p->pic, NULL);
    }else{
      pPixBufA = gdk_pixbuf_new_from_file("offline.jpg", NULL);
    }
    gtk_list_store_set(window->pListstore, &pIter,
		       PIX_COLUMN, pPixBufA,
		       TEXT_COLUMN, p->name,
		       -1);
    p = p->next;
  }
  /**************************/
  
  /* Creation de la vue */
  window->pListView = gtk_tree_view_new_with_model(GTK_TREE_MODEL(window->pListstore));
  
  /* Creation de la premiere colonne */
  window->pCellRenderer = gtk_cell_renderer_pixbuf_new();
  window->pColumn = gtk_tree_view_column_new_with_attributes("B",
							     window->pCellRenderer,
							     "pixbuf", PIX_COLUMN,
							     NULL);
  
  /* Ajout de la colonne à la vue */
  gtk_tree_view_append_column(GTK_TREE_VIEW(window->pListView), window->pColumn);
  
  /* Creation de la deuxieme colonne */
  window->pCellRenderer = gtk_cell_renderer_text_new();
  window->pColumn = gtk_tree_view_column_new_with_attributes("login",
							     window->pCellRenderer,
							     "text", TEXT_COLUMN,
							     NULL);
  
  /* Ajout de la colonne à la vue*/ 
  gtk_tree_view_append_column(GTK_TREE_VIEW(window->pListView), window->pColumn);
 
  /*Si on veut gtk_tree_view_set_headers_visible(window->pListView,FALSE);*/
  
  g_signal_connect(window->pListView,
		   "row-activated",
		   G_CALLBACK(OnDPress_contact),
		   window);
  
  gtk_container_add(GTK_CONTAINER(window->pScrollbar), window->pListView);

  return 1;
}

void OnBok_enreg_con(GtkWidget *widget,  t_window * window)
{
  widget = widget;
  gpointer **pEntries = window->pEntries;
  FILE *contacts;

  if ((contacts = fopen("./contacts.tut","a+")) != NULL) {
    fputs( gtk_entry_get_text(GTK_ENTRY(pEntries[0])), contacts);
    fputs(" ", contacts);
    fputs( gtk_entry_get_text(GTK_ENTRY(pEntries[1])), contacts);
    fputs(" ", contacts);
    fputs( gtk_entry_get_text(GTK_ENTRY(pEntries[2])), contacts);
    fputs("\n", contacts);
    g_free(pEntries);
    fclose(contacts);
  } else{
    
  }
  gtk_widget_destroy(GTK_WIDGET(window->pWin_ajouter));
}

void OnButton_contact_ajouter(GtkWidget *widget, t_window * window)
{
  GtkWidget **pEntries ;
  GtkWidget *pEntry ;
  pEntries = g_malloc(3*sizeof(GtkWidget *));
  pEntry = gtk_entry_new_with_max_length(15);
  pEntries[0] =  pEntry; /* nom */
  pEntry = gtk_entry_new_with_max_length(15);
  pEntries[1] =  pEntry; /* login */
  pEntry = gtk_entry_new_with_max_length(15);
  pEntries[2] =  pEntry; /* image */
  GtkWidget *label;
  
  widget=widget;

  GtkWidget * win_ajouter = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(win_ajouter),
		       "Ajouter Contact");
  gtk_window_set_position(GTK_WINDOW(win_ajouter),
			  GTK_WIN_POS_NONE );
  gtk_window_set_default_size(GTK_WINDOW(win_ajouter),200 , 200);
  g_signal_connect(G_OBJECT(win_ajouter),
		   "destroy",
		   G_CALLBACK(OnKill_con),
		   NULL);
  g_signal_connect(G_OBJECT(win_ajouter),
		   "delete_event",
		   G_CALLBACK(OnKill_con),
		   NULL);   
  GtkWidget *pVBox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(win_ajouter), pVBox);
  GtkWidget *pTable = gtk_table_new(5, 5, TRUE);
  gtk_box_pack_start(GTK_BOX(pVBox),
		     pTable,
		     TRUE, TRUE, 0);

  label = gtk_label_new("  Ajouter un contact  ");
  gtk_table_attach_defaults(GTK_TABLE(pTable),
			    label,
			    1,4,
			    0,1);

  label = gtk_label_new("  Nom / Pseudo :");
  gtk_table_attach_defaults(GTK_TABLE(pTable),
			    label,
			    0,1,
			    1,2);
  gtk_table_attach_defaults(GTK_TABLE(pTable),
			    pEntries[0],
			    1,4,
			    1,2);

  label = gtk_label_new("  login :");
  gtk_table_attach_defaults(GTK_TABLE(pTable),
			    label,
			    0,1,
			    2,3);
  gtk_table_attach_defaults(GTK_TABLE(pTable),
			    pEntries[1],
			    1,4,
			    2,3);

  label = gtk_label_new("  Image :");
  gtk_table_attach_defaults(GTK_TABLE(pTable),
			    label,
			    0,1,
			    3,4);
  gtk_table_attach_defaults(GTK_TABLE(pTable),
			    pEntries[2],
			    1,4,
			    3,4);
  
  GtkWidget *pBok = gtk_button_new_with_label("Valider");
  gtk_table_attach_defaults(GTK_TABLE(pTable),
			    pBok,
			    4,5,
			    2,3);
  window->pWin_ajouter = GTK_WINDOW(win_ajouter);
  window->pEntries = pEntries;

  g_signal_connect(G_OBJECT(pBok),
		   "clicked",
		   G_CALLBACK(OnBok_enreg_con),
		   window);
  
  gtk_widget_show_all(win_ajouter);
}

void OnButton_contact_supprimer(GtkWidget *widget, t_window * window)
{
  widget=widget;
  window= window;
}

void OnKill_con(GtkWidget *widget, t_window * window)
{
  window= window;
  gtk_widget_destroy(widget);
}

void OnButton_contact_modifier(GtkWidget *widget, t_window * window)
{
  widget=widget;
  window= window;
}
