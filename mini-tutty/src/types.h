/*
** types.h
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

#ifndef   	TYPES_H_
# define   	TYPES_H_

#include <gtk/gtk.h>
#include <netsoul/netsoul.h>

typedef struct		contact
{
  char			name[30];
  char			login[30];
  int			network;
  int		        id;
  int			online;
  int			open_diag;
  int			socket;
  struct _window_d*     window_d;
  struct contact*	next;
}			s_contact;

/* store user information including name contact list.. */
typedef struct	session
{
  char*		name;
  char*		ns_name;
  char*		ns_login;
  char*		ns_pwd;
  int		online;
  s_contact*	contacts;

  nsform*	formu;
  nsform*	depart;
}		s_session;



typedef struct
{
  /* users */
  s_session* session;

  /* main window */
  GtkWindow* pWindow;
  GtkWidget* pScrollbar;
  GtkWidget* pVBox;

  GtkWidget* pImage;
  GtkWidget* pToolbar;
  GtkWidget* pBtn_preferences;
  GtkWidget* pStatusBar;
  GtkWidget* pListView;
  
  GtkListStore*      pListstore;
  GtkCellRenderer*   pCellRenderer;
  GtkTreeViewColumn* pColumn;

  /* Preferences */
  GtkWindow* pWindow_p;
  GtkWidget* pHBox_p;
  GtkWidget* pScrollbar_p;
  GtkWidget* pTreeView_p;
  GtkTreeStore*      pTreeStore_p;
  GtkCellRenderer*   pCellRenderer_p;
  GtkTreeViewColumn* pColumn_p;

  GtkWidget* pBox_rub_p; 
  GtkWidget* pBox_aff_p;

  gpointer   pEntries;
  GtkWindow* pWin_ajouter;

  guint icid1;
  guint icid2;

} t_window ;

typedef struct _window_d
{
  int mode ;
  s_contact *contact;
  GtkWindow* pWindow_d; 
  GtkWidget* pVBox_d;
  GtkWidget* pMenuBar;
  GtkWidget* pMenu;
  GtkWidget* pMenuItem;
  GtkWidget* pTextView_d;
  GtkWidget* pScrollbar_TV_d;
  GtkWidget* pToolbar_d;
  GtkWidget* pTextEdit_d;
  GtkWidget* pScrollbar_TE_d;
  GtkWidget* pBtn_Send_d;
  GtkWidget* pHBox_d;
  GtkWidget* pStatusBar_d;

  t_window*  window;
} t_window_d;


#endif 	    /* !TYPES_H_ */
