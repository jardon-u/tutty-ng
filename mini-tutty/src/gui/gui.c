/*
** gui.c
** 
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

#include <types.h>
#include <netsoul/netsoul.h>
#include <c-serv/client_lib.h>
#include <gui/tut_dialog.h>
#include <gui/tut_window.h>

/// On


/// contact_identity

s_contact *contact_identity(GtkTreePath *path,
			    t_window *window)
{
  char *tmp ;
  GtkTreeIter iter;
  s_contact *p;
  
  /* nom du contact 2clique */
  
  gtk_tree_model_get_iter (GTK_TREE_MODEL(window->pListstore),
                           &iter,
                           path);
  gtk_tree_model_get(GTK_TREE_MODEL(window->pListstore),
		     &iter,
		     1,
		     &tmp,
		     -1);

  /* recherche ds les contacts */
  p = window->session->contacts;
  while ( (p != NULL) && strcmp(tmp, p->name) ){
    p = p->next;
  }
  return p;
}

/// dbclick

void OnDPress_contact(GtkTreeView       *tree_view,
		      GtkTreePath       *path,
		      GtkTreeViewColumn *column,
		      t_window *window)
{   
  column = column;
  tree_view = tree_view;

  t_window_d * window_d = malloc( sizeof(t_window_d) );
  
  window_d->contact = contact_identity(path, window);
  
  if (window_d->contact != NULL){
    window_d->contact->open_diag = TRUE;
    window_d->contact->window_d  = window_d;

    init_dialog(window_d, window);
    window_d->window = window ;
  }
  
}

/// init contact

int init_list_contact(t_window * window)
{
  /* Creation de la barre de defilement */
  window->pScrollbar = gtk_scrolled_window_new(NULL, NULL);
  gtk_box_pack_start(GTK_BOX(window->pVBox), window->pScrollbar, TRUE, TRUE, 0);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(window->pScrollbar), 
				 GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
  /* Creation de la liste */
  window->pListstore = gtk_list_store_new(1, G_TYPE_STRING);
  
  /*** Insertion contact ***/
  GdkPixbuf   *pPixBufA;
  GtkTreeIter pIter;
  s_contact *p = window->session->contacts;

  while (p!= NULL){
    gtk_list_store_append(window->pListstore, &pIter);
    if(p->online){
      pPixBufA = gdk_pixbuf_new_from_file("online.jpg", NULL);
    } else {
      pPixBufA = gdk_pixbuf_new_from_file("offline.jpg", NULL);
    }
    gtk_list_store_set(window->pListstore, &pIter,
		       0, p->name,
		       -1);
    p = p->next;
  }
  /**************************/
  
  /* Creation de la vue */
  window->pListView =
    gtk_tree_view_new_with_model(GTK_TREE_MODEL(window->pListstore));
  
  /* Creation de la colonne */
  window->pCellRenderer = gtk_cell_renderer_text_new();
  window->pColumn =
    gtk_tree_view_column_new_with_attributes("login",
					     window->pCellRenderer,
					     "text", 0,
					     NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(window->pListView), window->pColumn);
  //  gtk_tree_view_set_headers_visible(window->pListView, FALSE);
  
  g_signal_connect(window->pListView,
		   "row-activated",
		   G_CALLBACK(OnDPress_contact),
		   window);
  gtk_container_add(GTK_CONTAINER(window->pScrollbar), window->pListView);

  return 1;
}


// init win

t_window *init_window(s_session* session)
{
  t_window *window = malloc(sizeof (t_window));
  window->session = session;

  return window;
}

///gui

int gui(int    argc,
	char** argv,
	s_session* session)
{
  t_window* window = init_window(session);

  gtk_init(&argc, &argv);

  init_main_window(window);
  init_toolbar(window);
  init_statusBar(window);
  init_list_contact(window);

  gtk_widget_show_all(GTK_WIDGET(window->pWindow));

  gtk_main();
  return EXIT_SUCCESS;
}
