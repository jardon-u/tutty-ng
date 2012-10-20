#include <c-serv/client_lib.h>
#include "tut_dialog.h"

void OnButton_send(GtkWidget *pWidget, t_window_d * window_d)
{
  pWidget = pWidget;
  GtkTextBuffer * pTextBuffer_edit_d;
  GtkTextBuffer * pTextBuffer_view_d;
  GtkTextIter iStart;
  GtkTextIter iEnd;
  GtkTextIter iEnd_view;
  GtkTextMark* mark;
  char* sUtf8 ;
  char* tmp ;

  pTextBuffer_edit_d = gtk_text_view_get_buffer(GTK_TEXT_VIEW(window_d->pTextEdit_d));
  gtk_text_buffer_get_start_iter(pTextBuffer_edit_d, &iStart);
  gtk_text_buffer_get_end_iter(pTextBuffer_edit_d, &iEnd);
  char* stringEdit = gtk_text_buffer_get_text(pTextBuffer_edit_d,
					       &iStart, &iEnd,
					       TRUE);
  pTextBuffer_view_d = gtk_text_view_get_buffer(GTK_TEXT_VIEW(window_d->pTextView_d));

  if (stringEdit && strcmp(stringEdit, ""))
  {
    tmp = g_strconcat(window_d->window->session->name,":\n  ",stringEdit,"\n", NULL); 
    sUtf8 = g_locale_to_utf8(tmp, -1, NULL, NULL, NULL) ;
    gtk_text_buffer_get_end_iter(pTextBuffer_view_d, &iEnd_view);
    gtk_text_buffer_insert(pTextBuffer_view_d, 
			   &iEnd_view, 
			   sUtf8, 
			   -1);
    mark = gtk_text_buffer_get_insert(pTextBuffer_view_d);
    gtk_text_view_scroll_to_mark(GTK_TEXT_VIEW(window_d->pTextView_d), mark, 0, FALSE, 1, 1); 

    //netsoul
    window_d->window->session->depart->lu=0;
    window_d->window->session->depart->login = window_d->contact->login;
    window_d->window->session->depart->msg = stringEdit;
	
    /*	tt_nssendmsg(, stringEdit);*/
  }
  gtk_text_buffer_delete(pTextBuffer_edit_d,
			 &iStart, &iEnd);
}

void OnKill_d(GtkWidget *widget, t_window_d *window_d)
{
  if ( (window_d->contact != NULL)){
    window_d->contact->open_diag = FALSE;
    // netsoul
    tutti_deconnect(window_d->contact->socket); 
  }
  g_free(window_d);
  gtk_widget_destroy(widget);
}

int init_dialog(t_window_d * window_d, t_window * window)
{
  window_d->window = window;
  /*** Creation fenetre dialogue ***/
  window_d->pWindow_d = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
  gtk_window_set_title(GTK_WINDOW(window_d->pWindow_d),
		       window_d->contact->name);
  gtk_window_set_position(GTK_WINDOW(window_d->pWindow_d),
			  GTK_WIN_POS_NONE );
  gtk_window_set_default_size(GTK_WINDOW(window_d->pWindow_d),400 ,200);
  g_signal_connect(G_OBJECT(window_d->pWindow_d),
		   "destroy",
		   G_CALLBACK(OnKill_d),
		   window_d);
  
  /*** TRUC DEDANS ***/
  /* Creation de la box principale */
  window_d->pVBox_d = gtk_vbox_new(FALSE, 0);
  gtk_container_add(GTK_CONTAINER(window_d->pWindow_d), window_d->pVBox_d);

  /* Menu */
  window_d->pMenuBar = gtk_menu_bar_new();

  window_d->pMenu = gtk_menu_new(); /* Fichier */

  /* ss-menu 1 */
  window_d->pMenuItem = gtk_menu_item_new_with_label("Enregistrer");
  gtk_menu_shell_append(GTK_MENU_SHELL(window_d->pMenu), window_d->pMenuItem);
  /* ss-menu 2 */
  window_d->pMenuItem = gtk_menu_item_new_with_label("Effacer");
  gtk_menu_shell_append(GTK_MENU_SHELL(window_d->pMenu), window_d->pMenuItem);
  /* menu fichier */
  window_d->pMenuItem = gtk_menu_item_new_with_label("Fichier");
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(window_d->pMenuItem), window_d->pMenu);
  /* ajout de menu fichier a menubar */
  gtk_menu_shell_append(GTK_MENU_SHELL(window_d->pMenuBar), window_d->pMenuItem);

  gtk_box_pack_start(GTK_BOX(window_d->pVBox_d),
		     window_d->pMenuBar,
		     FALSE, FALSE, 0);

  /** Text view **/
  window_d->pTextView_d = gtk_text_view_new();
  gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(window_d->pTextView_d),
			      GTK_WRAP_WORD_CHAR);
  gtk_text_view_set_editable(GTK_TEXT_VIEW(window_d->pTextView_d), FALSE);
  gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(window_d->pTextView_d), FALSE);
  /*scrollbar*/
  window_d->pScrollbar_TV_d = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(window_d->pScrollbar_TV_d), 
				 GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
  gtk_container_add(GTK_CONTAINER(window_d->pScrollbar_TV_d),
		    window_d->pTextView_d);
  
  gtk_box_pack_start(GTK_BOX(window_d->pVBox_d),
		     window_d->pScrollbar_TV_d, 
		     TRUE, TRUE, 0);

  /* barre d'outil */
  window_d->pToolbar_d = gtk_toolbar_new();

  /* gtk_toolbar_insert_stock deprecated */
  gtk_toolbar_insert_stock(GTK_TOOLBAR(window_d->pToolbar_d),
			   GTK_STOCK_OPEN,
			   "Envoyer un fichier",
			   NULL,
			   G_CALLBACK(OnButton_send_file),
			   window_d->pWindow_d,
			   -1);


  gtk_toolbar_set_icon_size(GTK_TOOLBAR(window_d->pToolbar_d), /* deprecated */
			    GTK_ICON_SIZE_BUTTON);
  gtk_toolbar_set_style(GTK_TOOLBAR(window_d->pToolbar_d),
			GTK_TOOLBAR_ICONS);
  gtk_box_pack_start(GTK_BOX(window_d->pVBox_d),
		     window_d->pToolbar_d,
		     FALSE, FALSE, 0);

  /** Box horizontale **/
  window_d->pHBox_d = gtk_hbox_new(FALSE, 0);
  gtk_box_pack_start(GTK_BOX(window_d->pVBox_d),
		     window_d->pHBox_d,
		     FALSE, FALSE, 0);

  /* text edit */
  window_d->pTextEdit_d = gtk_text_view_new();
  gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(window_d->pTextEdit_d),
			      GTK_WRAP_WORD_CHAR );
  gtk_text_view_set_editable(GTK_TEXT_VIEW(window_d->pTextEdit_d), TRUE);
  gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(window_d->pTextEdit_d), TRUE);
  
  /*scrollbar*/

  window_d->pScrollbar_TE_d = gtk_scrolled_window_new(NULL, NULL);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(window_d->pScrollbar_TE_d), 
				 GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
  gtk_container_add(GTK_CONTAINER(window_d->pScrollbar_TE_d),
		    window_d->pTextEdit_d);
  
  gtk_box_pack_start(GTK_BOX(window_d->pHBox_d),
		     window_d->pScrollbar_TE_d,
		     TRUE, TRUE, 0);
  
  /* send */
  window_d->pBtn_Send_d = gtk_button_new_from_stock(GTK_STOCK_OK);  

  g_signal_connect(G_OBJECT(window_d->pBtn_Send_d),
		   "clicked",
		   G_CALLBACK(OnButton_send),
		   window_d);

  gtk_box_pack_start(GTK_BOX(window_d->pHBox_d),
		     window_d->pBtn_Send_d,
		     FALSE, FALSE, 0); 
  GTK_WIDGET_SET_FLAGS(window_d->pBtn_Send_d, GTK_CAN_DEFAULT);

  /* Creation de la barre d'etat */
  window_d->pStatusBar_d = gtk_statusbar_new();
  gtk_box_pack_start(GTK_BOX(window_d->pVBox_d),
		     window_d->pStatusBar_d,
		     FALSE, FALSE, 0);

  window_d->contact->open_diag = TRUE;
  gtk_widget_show_all(GTK_WIDGET(window_d->pWindow_d));
  return 1;
}

void OnButton_send_file(GtkWidget *pWidget, gpointer data)
{
  GtkWidget *pFileSelection;
  GtkWidget *pDialog;
  GtkWidget *pParent;
  gchar *sChemin;
  
  pWidget = pWidget;
  pParent = GTK_WIDGET(data);
  
  /* Creation de la fenetre de selection */
  pFileSelection = gtk_file_chooser_dialog_new("Ouvrir...",
					       GTK_WINDOW(pParent),
					       GTK_FILE_CHOOSER_ACTION_OPEN,
					       GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
					       GTK_STOCK_OPEN, GTK_RESPONSE_OK,
					       NULL);
  /* On limite les actions a cette fenetre */
  gtk_window_set_modal(GTK_WINDOW(pFileSelection), TRUE);
  
  /* Affichage fenetre */
  switch(gtk_dialog_run(GTK_DIALOG(pFileSelection)))
    {
    case GTK_RESPONSE_OK:
      /* Recuperation du chemin */
      sChemin = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(pFileSelection));
      pDialog = gtk_message_dialog_new(GTK_WINDOW(pFileSelection),
				       GTK_DIALOG_MODAL,
				       GTK_MESSAGE_INFO,
				       GTK_BUTTONS_OK,
				       "Chemin du fichier :\n%s", sChemin);
      gtk_dialog_run(GTK_DIALOG(pDialog));
      gtk_widget_destroy(pDialog);
      g_free(sChemin);
      break;
    default:
      break;
    }
  gtk_widget_destroy(pFileSelection);
}
