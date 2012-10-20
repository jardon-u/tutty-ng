#include"headers.h"

void init_fenetrePrincipale(t_window * window)
{
  /*** Creation de la fenetre principale ***/
  window->pWindow = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
  gtk_window_set_title(GTK_WINDOW(window->pWindow), "TUTTI 0.1");
  gtk_window_set_position(GTK_WINDOW(window->pWindow), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(window->pWindow, 150, 200);
  gtk_widget_set_size_request(GTK_WIDGET(window->pWindow), 150, 200);
  gtk_window_set_resizable(window->pWindow, TRUE);
  g_signal_connect(G_OBJECT(window->pWindow),
		   "destroy",
		   G_CALLBACK(OnDestroy),
		   window);
  /* Creation de la box principale */
  window->pVBox = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(window->pWindow), window->pVBox);
}

void OnKill_p(GtkWidget *widget)
{
  gtk_widget_hide_all(widget);
}

int init_preferences(t_window * window)
{
  /* INIT Fenetre Gestion */
  window->pWindow_p = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
  gtk_window_set_title(GTK_WINDOW(window->pWindow_p),
		       "TUTTI 0.1 : Gestion");
  gtk_window_set_position(GTK_WINDOW(window->pWindow_p),
			  GTK_WIN_POS_NONE );
  gtk_window_set_default_size(GTK_WINDOW(window->pWindow_p),600 , 500);
  g_signal_connect(G_OBJECT(window->pWindow_p),
		   "destroy",
		   G_CALLBACK(OnKill_p),
		   NULL);
  g_signal_connect(G_OBJECT(window->pWindow_p),
		   "delete_event",
		   G_CALLBACK(OnKill_p),
		   NULL);
  
  /* box principale */
  window->pHBox_p = gtk_hbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(window->pWindow_p), window->pHBox_p);
  
  /* Creation de l arbre des parametres */
  window->pTreeStore_p = gtk_tree_store_new( 1, G_TYPE_STRING);

  int i;
  int j;

  char titres[5][20];
  char ssmenu[5][3][20];

  g_sprintf(titres[0], "Generale");
  g_sprintf(ssmenu[0][0], "prop 1");
  g_sprintf(ssmenu[0][1], "prop 2");
  g_sprintf(ssmenu[0][2], "0");
  g_sprintf(titres[1], "Apparence");
  g_sprintf(ssmenu[1][0], "0");
  g_sprintf(titres[2], "Contacts");
  g_sprintf(ssmenu[2][0], "0");
  g_sprintf(titres[3], "Connexion");  
  g_sprintf(ssmenu[3][0], "prop 1");
  g_sprintf(ssmenu[3][1], "prop 2");
  g_sprintf(ssmenu[3][2], "0");
  g_sprintf(titres[4], "0");

  GtkTreeIter pIter_p;
  GtkTreeIter pIter2_p;

  i=0;
  while (strcmp(titres[i],"0")){
    gtk_tree_store_append(window->pTreeStore_p, &pIter_p, NULL);
    gtk_tree_store_set(window->pTreeStore_p, &pIter_p,
		       0, titres[i],
		       -1);
    j = 0;
    while (strcmp(ssmenu[i][j], "0")){
      gtk_tree_store_append(window->pTreeStore_p, &pIter2_p, &pIter_p );
      gtk_tree_store_set(window->pTreeStore_p, &pIter2_p,
			 0,  ssmenu[i][j],
			 -1);
      j++;
    }
    i++;
  }

  /* creation de la vue */
  window->pTreeView_p = gtk_tree_view_new_with_model(GTK_TREE_MODEL(window->pTreeStore_p));
  
  /* Creation de la colonne */
  window->pCellRenderer_p = gtk_cell_renderer_text_new();
  window->pColumn_p = gtk_tree_view_column_new_with_attributes("Rubriques                     ~",
							       window->pCellRenderer_p,
							       "text", 0,
							       NULL);
  
  /* Ajout de la colonne à la vue */
  gtk_tree_view_append_column(GTK_TREE_VIEW(window->pTreeView_p), window->pColumn_p);
  
  /* Creation scrollbar contenant la liste des contacts */
  window->pScrollbar_p = gtk_scrolled_window_new(NULL, NULL);
  gtk_box_pack_start(GTK_BOX(window->pHBox_p), window->pScrollbar_p, FALSE, TRUE, 0);
  
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(window->pScrollbar_p), 
				 GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
  
  /* ajout de la vue a la ScrollBar */
  gtk_container_add(GTK_CONTAINER(window->pScrollbar_p), window->pTreeView_p);
  
  /* Creation des rubriques */
  window->pBox_rub_p = gtk_vbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(window->pHBox_p), window->pBox_rub_p, TRUE, TRUE, 0);

  /* contenue des rubriques */
  window->pBox_aff_p = gtk_hbox_new(FALSE, 0);
  gtk_box_pack_end(GTK_BOX(window->pHBox_p), window->pBox_aff_p, TRUE, TRUE, 0);

  g_signal_connect(window->pTreeView_p,
		   "row-activated",
		   G_CALLBACK(OnDPress_rub),
		   window);
  
  return 1 ;
}

void OnDPress_rub(GtkTreeView       *tree_view,
		  GtkTreePath       *path,
		  GtkTreeViewColumn *column,
		  t_window          *window)
{
  column = column;
  tree_view = tree_view;

  char *tmp ;
  GtkTreeIter iter;

  /* Clear zone d affichage */
  gtk_container_foreach(GTK_CONTAINER(window->pBox_aff_p),
			(GtkCallback)OnClear_HBox_p,
			window);

  GtkWidget *pTable = gtk_table_new(5, 5, TRUE);
  gtk_box_pack_start(GTK_BOX(window->pBox_aff_p),
		     pTable,
		     TRUE, TRUE, 0);
  
  /* nom de la rub 2clique */
  gtk_tree_model_get_iter (GTK_TREE_MODEL(window->pTreeStore_p),
                           &iter,
                           path);
  gtk_tree_model_get(GTK_TREE_MODEL(window->pTreeStore_p),
		     &iter,
		     0,
		     &tmp,
		     -1);
  
  if (!strcmp(tmp,"Contacts")) {
    GtkListStore* pListstore;
    GtkWidget *pListView;
    GtkCellRenderer *pCellRenderer;
    GtkTreeViewColumn *pColumn;
    GtkWidget *pScrollbar;
    
    pListstore = gtk_list_store_new(N_COLUMN, 
				    GDK_TYPE_PIXBUF,
				    G_TYPE_STRING);
    /*** Insertion contact ***/
    GdkPixbuf *pPixBufA;
    GtkTreeIter pIter;
    t_contact *p;
    
    p = window->contacts;
    while (p!= NULL){
      gtk_list_store_append(pListstore, &pIter);
      pPixBufA = gdk_pixbuf_new_from_file(p->pic, NULL);
      gtk_list_store_set(pListstore, &pIter,
			 PIX_COLUMN, pPixBufA,
			 TEXT_COLUMN, p->name,
			 -1);
      p = p->next;
    }
    /**************************/
    /* Creation de la vue */
    pListView = gtk_tree_view_new_with_model(GTK_TREE_MODEL(pListstore));
    /* Creation de la premiere colonne */
    pCellRenderer = gtk_cell_renderer_pixbuf_new();
    pColumn = gtk_tree_view_column_new_with_attributes("B",
						       pCellRenderer,
						       "pixbuf", PIX_COLUMN,
						       NULL);
    /* Ajout de la colonne à la vue */
    gtk_tree_view_append_column(GTK_TREE_VIEW(pListView), pColumn);
    /* Creation de la deuxieme colonne */
    pCellRenderer = gtk_cell_renderer_text_new();
    pColumn = gtk_tree_view_column_new_with_attributes("login",
						       pCellRenderer,
						       "text", TEXT_COLUMN,
						       NULL);
    /* Ajout de la colonne à la vue*/ 
    gtk_tree_view_append_column(GTK_TREE_VIEW(pListView), pColumn);
    /* scrollbar */
    pScrollbar = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(pScrollbar), pListView);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(pScrollbar), 
				   GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
    /*BOUTONS*/
    GtkWidget *pVBox = gtk_vbox_new(FALSE, 0);

    /* ajouter*/
    GtkWidget *pBajouter = gtk_button_new_with_label("Ajouter");
    g_signal_connect(G_OBJECT(pBajouter),
		     "clicked",
		     G_CALLBACK(OnButton_contact_ajouter),
		     window);
    gtk_box_pack_start(GTK_BOX(pVBox),
		       pBajouter,
		       FALSE, FALSE, 0); 
    /*supprimer*/
    GtkWidget *pBsupprimer = gtk_button_new_with_label("Supprimer");
    g_signal_connect(G_OBJECT(pBsupprimer),
		     "clicked",
		     G_CALLBACK(OnButton_contact_supprimer),
		     window);
    gtk_box_pack_start(GTK_BOX(pVBox),
		       pBsupprimer,
		       FALSE, FALSE, 0); 
    /*modifier*/
    GtkWidget *pBmodifier = gtk_button_new_with_label("Modifier");
    g_signal_connect(G_OBJECT(pBmodifier),
		     "clicked",
		     G_CALLBACK(OnButton_contact_modifier),
		     window);
    gtk_box_pack_start(GTK_BOX(pVBox),
		       pBmodifier,
		       FALSE, FALSE, 0);
    
    /* mis dans la zone d affichage */
    GtkWidget *label;
    label = gtk_label_new("  Gestion des contacts  ");
    gtk_table_attach_defaults(GTK_TABLE(pTable),
			      label,
			      1,4,
			      0,1);
    gtk_table_attach_defaults(GTK_TABLE(pTable),
			      pScrollbar,
			      0,4,
			      1,5);
    gtk_table_attach_defaults(GTK_TABLE(pTable),
			      pVBox,
			      4,5,
			      1,5);

    /*affichage */
    gtk_widget_show_all(GTK_WIDGET(window->pHBox_p));
  }
  
  if (!strcmp(tmp,"Apparence")) {
    GtkWidget *label;
    label = gtk_label_new("  Choisir un theme : ");
    gtk_table_attach_defaults(GTK_TABLE(pTable),
			      label,
			      0,2,
			      0,1);

    GtkWidget *pbred = gtk_button_new_with_label("red");
    gtk_table_attach_defaults(GTK_TABLE(pTable),
			      pbred,
			      0,1,
			      1,2);
    g_signal_connect(G_OBJECT(pbred),
		     "clicked",
		     G_CALLBACK(OnButton_red),
		     window);

    GtkWidget *pbdual = gtk_button_new_with_label("dual");
    gtk_table_attach_defaults(GTK_TABLE(pTable),
			     pbdual,
			     1,2,
			     1,2);
    g_signal_connect(G_OBJECT(pbdual),
		     "clicked",
		     G_CALLBACK(OnButton_dual),
		     window);
   
   GtkWidget *pblogo = gtk_button_new_with_label("logo");
   gtk_table_attach_defaults(GTK_TABLE(pTable),
			     pblogo,
			     2,3,
			     1,2);
    g_signal_connect(G_OBJECT(pblogo),
		     "clicked",
		     G_CALLBACK(OnButton_logo),
		     window);
   
   gtk_widget_show_all(GTK_WIDGET(window->pHBox_p));
  }
  
}

void OnButton_logo(GtkWidget *widget, t_window * window)
{
  widget = widget;
  window->logo = "./skins/logo/logo";
}

void OnButton_red(GtkWidget *widget, t_window * window)
{
  widget = widget;
  window->logo = "./skins/red/red";    
}

void OnButton_dual(GtkWidget *widget, t_window * window)
{
  widget = widget;
  window->logo = "./skins/dual/dual";
}

void OnClear_HBox_p(GtkWidget *widget, t_window * window)
{
  gtk_container_remove(GTK_CONTAINER(window->pBox_aff_p), 
		       widget);
}

void init_statusBar(t_window * window)
{
  window->pStatusBar = gtk_statusbar_new();
  gtk_box_pack_start(GTK_BOX(window->pVBox),
		     window->pStatusBar,
		     FALSE, FALSE, 0);
  window->icid1 = gtk_statusbar_get_context_id(GTK_STATUSBAR(window->pStatusBar), "ExitMsg");
  window->icid2 = gtk_statusbar_get_context_id(GTK_STATUSBAR(window->pStatusBar), "AboutMsg");
  /*MSN*/
  gtk_statusbar_push (GTK_STATUSBAR (window->pStatusBar), GPOINTER_TO_INT(window->icid2), "MSN offline");
}

/* Creation de la Fenetre de gestion */
void OnPress_preferences(GtkWidget *widget, t_window * window)
{
  widget = widget; 
  gtk_widget_show_all(GTK_WIDGET(window->pWindow_p));
}

int init_toolbar(t_window * window)
{
  window->pToolbar = gtk_toolbar_new();

  /* Ajout des elements de la barre d outil */
  gtk_toolbar_insert_stock(GTK_TOOLBAR(window->pToolbar),
			   GTK_STOCK_PREFERENCES,
			   "Gestion",
			   NULL,
			   G_CALLBACK(OnPress_preferences),
			   window,
			   -1);
  gtk_toolbar_insert_stock(GTK_TOOLBAR(window->pToolbar),
			   GTK_STOCK_GOTO_BOTTOM,
			   "NETSOUL",
			   NULL,
			   G_CALLBACK(OnPress_netsoul),
			   window,
			   -1);
  gtk_toolbar_insert_stock(GTK_TOOLBAR(window->pToolbar),
			   GTK_STOCK_REFRESH,
			   "Actualiser",
			   NULL,
			   G_CALLBACK(OnButton_null),
			   NULL,
			   -1);
  
  /* Modification de la taille des icones */
  gtk_toolbar_set_icon_size(GTK_TOOLBAR(window->pToolbar),
			    GTK_ICON_SIZE_BUTTON);
  /* Affichage uniquement des icones */
  gtk_toolbar_set_style(GTK_TOOLBAR(window->pToolbar),
			GTK_TOOLBAR_ICONS);
  
  gtk_box_pack_start(GTK_BOX(window->pVBox), 
		     window->pToolbar, 
		     FALSE, FALSE, 0);
  
  return 1;
}
