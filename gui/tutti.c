#include"headers.h"

int main(int argc, char **argv)
{
  t_window *window;
  window = g_malloc(sizeof(t_window));
  window->me = g_malloc(sizeof(t_me));
  init_CurrentSession(window);
  charger_sauvegarde(window);

  gtk_init(&argc, &argv);

  g_timeout_add(500, (GSourceFunc)On_verif, window);
  g_timeout_add(500, (GSourceFunc)set_etat, window);

  init_fenetrePrincipale(window);

  init_preferences(window);
  
  //  window->pImage = gtk_image_new_from_file(window->logo);
  // gtk_box_pack_start(GTK_BOX(window->pVBox), window->pImage, FALSE, FALSE, 5);

  init_toolbar(window);

  init_list_contact(window);
  
  init_statusBar(window);
  
  gtk_widget_show_all(GTK_WIDGET(window->pWindow));
  
  gtk_main();
  return EXIT_SUCCESS;
}

int init_CurrentSession(t_window * window)
{
  /*netsoul*/
  window->me->online_netsoul = FALSE;
  window->me->nsname = "ugo";
  window->me->nslogin = "jardon_u";
  window->me->nspwd = "JoKqKi^^";
  window->me->formu = malloc(sizeof(nsform));
  window->me->formu->lu = 1;
  window->me->depart = malloc(sizeof(nsform));
  window->me->depart->lu = 1;

  window->logo="./skins/dual/dual";
  window->contacts = NULL;
  return 1;
}


void OnDestroy(GtkWidget *widget, t_window * window)
{
  /* libere liste des contacts */
  t_contact *p;
  t_contact *suiv;

  p = window->contacts;
  while (p!=NULL) {
    suiv = p->next;
    g_free(p);
    p = suiv;
  }
  widget=widget;

  /* libere window */
  if (window!=NULL)
    {
      g_free(window->me);
      g_free(window);
      window = NULL;
      gtk_main_quit();
    }
}

gboolean set_etat(t_window * window)
{
  // char * s = g_malloc(8);
  //char * tmp ; 
  //  g_strconcat(window->logo, s);
  //s[0] =  window->me->online_p2p + '0';
  //s[1] =  window->me->online_msn + '0';
  /* s[2] =  window->me->online_netsoul + '0'; */
/*   s[3] ='.'; */
/*   s[4] ='p'; */
/*   s[5] ='n'; */
/*   s[6] ='g'; */
/*   s[7] =0; */
  //g_strconcat(window->logo,s);
  //tmp = g_strconcat(window->logo,s,0);
  //gtk_image_set_from_file(GTK_IMAGE(window->pImage), tmp);
  //g_free(tmp);
  //  g_free(s);
  return TRUE;
}

void OnPress_netsoul(GtkWidget *widget, t_window * window)
{
  widget=widget;
  while(gtk_events_pending())
    gtk_main_iteration();

  tt_nsconnect("ns-server.epita.fr", 4242, window->me->nspwd, window->me->nslogin);
  window->me->online_netsoul = TRUE ;
  gtk_statusbar_push (GTK_STATUSBAR (window->pStatusBar), GPOINTER_TO_INT(window->icid1), "Netsoul online");
}

gboolean On_verif(t_window * window)
{
  t_contact *p;
  t_window_d * window_d;
  gchar *sUtf8;
  gchar tmp[255];
  GtkTextIter iEnd_view;
  GtkTextBuffer * pTextBuffer_view_d;
  GtkTextMark* mark;
  
  if (window->me->online_netsoul){
    tt_nsverif(window->me->formu, window->me->depart); 
    if (!window->me->formu->lu)
      {
	/* recherche du contact*/
	p = window->contacts;
	while ( (p != NULL) && strcmp(window->me->formu->login, p->login) ){
	  p = p->next;
	}
	if (p!=NULL){ /* contact connu */
	  if (!p->open_diag){ /* pas de fenetre ouverte */
	    /* creation fenetre */
	    window_d = g_malloc(sizeof(t_window_d));
	    window_d->contact = p;
	    p->window_d = window_d;
	    init_dialogue(window_d, window);
	  }
	} else { /* contact inconnu : creation contact et ouverture fenetre */
	  window_d = g_malloc(sizeof(t_window_d));
	  window_d->contact = ajouter_contact(window->me->formu->login,
					      window->me->formu->login,
					      "temp.jpg", window);
	  window_d->contact->mode = NETSOUL;
	  window_d->contact->window_d = window_d;
	  p = window_d->contact;
	  init_dialogue(window_d, window);
	}
	/* mode */
	window_d->mode = NETSOUL;
	
	/* affichage message */
	pTextBuffer_view_d = gtk_text_view_get_buffer(GTK_TEXT_VIEW(p->window_d->pTextView_d));
	gtk_text_buffer_get_end_iter(pTextBuffer_view_d, &iEnd_view);
	
	strcpy(tmp, g_strconcat(p->name," :\n  ",window->me->formu->msg,"\n",'\0') );
	
	sUtf8 = g_locale_to_utf8(tmp, -1, NULL, NULL, NULL);
	
	gtk_text_buffer_insert(pTextBuffer_view_d,
			       &iEnd_view,
			       sUtf8,
			       -1);
	mark = gtk_text_buffer_get_insert (pTextBuffer_view_d);
	gtk_text_view_scroll_to_mark(GTK_TEXT_VIEW(p->window_d->pTextView_d), mark, 0, FALSE, 1, 1);
	
	g_free(sUtf8);
	
	window->me->formu->lu = 1;
      }
  } 
  
  return TRUE;
}

void OnButton_null(GtkWidget *pWidget, gpointer data)
{
  pWidget = pWidget;
  data = data;
}


