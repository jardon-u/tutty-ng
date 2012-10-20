#include <string.h> /* FIXME */
#include "tut_window.h"

void OnDestroy(GtkWidget *widget, t_window * window)
{
  /* libere liste des contacts */
  s_contact *p;
  s_contact *suiv;

  p = window->session->contacts;
  while (p != NULL) {
    suiv = p->next;
    g_free(p);
    p = suiv;
  }
  widget=widget;

  /* libere window */
  if (window!=NULL)
    {
      g_free(window->session);
      g_free(window);
      window = NULL;
      gtk_main_quit();
    }
}

/// main window

void init_main_window(t_window* window)
{
  window->pWindow = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
  gtk_window_set_title(GTK_WINDOW(window->pWindow), "mini-tutti");
  gtk_window_set_position(GTK_WINDOW(window->pWindow), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(window->pWindow, 150, 200);
  gtk_widget_set_size_request(GTK_WIDGET(window->pWindow), 150, 200);
  gtk_window_set_resizable(window->pWindow, TRUE);
  g_signal_connect(G_OBJECT(window->pWindow),
		   "destroy",
		   G_CALLBACK(OnDestroy),window);
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
   
  return 1 ;
}

void OnDPress_rub(GtkTreeView       *tree_view,
		  GtkTreePath       *path,
		  GtkTreeViewColumn *column,
		  t_window          *window)
{
  tree_view = tree_view;
  path = path;
  column = column;
  window = window;
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

void OnPress_netsoul(GtkWidget *widget, t_window * window)
{
  widget = widget;

  while (gtk_events_pending())
    gtk_main_iteration();

  tt_nsconnect("ns-server.epita.fr", 4242,
	       window->session->ns_pwd,
	       window->session->ns_login);
  window->session->online = TRUE ;
  gtk_statusbar_push (GTK_STATUSBAR (window->pStatusBar),
		      GPOINTER_TO_INT(window->icid1), "Netsoul online");
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
			   GTK_STOCK_CONNECT,
			   "NETSOUL",
			   NULL,
			   G_CALLBACK(OnPress_netsoul),
			   window,
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
