#include<gtk/gtk.h>

#ifndef H_TUTTI
#define H_TUTTI

/* utilisateur */
typedef struct
{
  char *name;
  char *msnname;
  char *msnlogin;
  char *msnpwd;
  char *nsname;
  char *nslogin;
  char *nspwd;
  gboolean online_msn;
  gboolean online_netsoul;
  gboolean online_p2p;
  nsform *formu, *depart;
} t_me;

struct window_d;

/* fiche contact */
typedef struct _contact
{
  int		socket;
  char		name[30];
  char		login[30];
  char		pic[30];
  int		mode;
  gboolean	open_diag;
  char		ip[15];
  struct window_d* window_d;
  struct _contact* next;
}		t_contact;

/* fenetre principale */
typedef struct
{
  /* users */
  t_contact *contacts;
  t_me *me;

  /* main window */
  GtkWindow *pWindow;
  GtkWidget *pScrollbar;
  GtkWidget *pVBox;

  GtkWidget *pImage;
  GtkWidget *pToolbar;
  GtkWidget *pBtn_preferences;
  GtkListStore* pListstore;
  GtkWidget *pListView;
  GtkCellRenderer *pCellRenderer;
  GtkTreeViewColumn *pColumn;
  GtkWidget *pStatusBar;
  guint icid1;
  guint icid2;

  /* Preferences */
  GtkWindow *pWindow_p;
  GtkWidget *pHBox_p;
  GtkWidget *pScrollbar_p;
  GtkTreeStore *pTreeStore_p;
  GtkWidget *pTreeView_p;
  GtkCellRenderer *pCellRenderer_p;
  GtkTreeViewColumn *pColumn_p;
  
  GtkWidget *pBox_rub_p; 
  GtkWidget *pBox_aff_p;

  gpointer pEntries;
  GtkWindow *pWin_ajouter;
  char* logo;

} t_window ;

/* fenetre de dialogue */
typedef struct _window_d
{
  int mode ;
  t_contact *contact;
  GtkWindow *pWindow_d; 
  GtkWidget *pVBox_d;
  GtkWidget *pMenuBar;
  GtkWidget *pMenu;
  GtkWidget *pMenuItem;
  GtkWidget *pTextView_d;
  GtkWidget *pScrollbar_TV_d;
  GtkWidget *pToolbar_d;
  GtkWidget *pTextEdit_d;
  GtkWidget *pScrollbar_TE_d;
  GtkWidget *pBtn_Send_d;
  GtkWidget *pHBox_d;
  GtkWidget *pStatusBar_d;
  t_window  *window;
} t_window_d ;

enum {/* Colonnes contacts */
  PIX_COLUMN,
  TEXT_COLUMN,
  N_COLUMN
};

enum {
  RIEN,
  MSN,
  NETSOUL,
  P2P
};

void gtk_init(int *argc, char ***argv);

int init_CurrentSession(t_window * window);
void OnPress_msn(GtkWidget *widget, t_window * window);
void OnPress_netsoul(GtkWidget *widget, t_window * window);
void OnButton_p2p(GtkWidget *pWidget,  t_window_d * window_d);

gboolean On_verif(t_window * window);
gboolean set_etat(t_window * window);

t_contact *identite_contact(GtkTreePath *path, t_window *window);
int init_dialogue(t_window_d * window_d, t_window * window);
void OnDPress_contact(GtkTreeView       *tree_view,
		      GtkTreePath       *path,
		      GtkTreeViewColumn *column,
		      t_window *window);
void OnButton_send_file(GtkWidget *pWidget, gpointer data);
void OnButton_send(GtkWidget *pWidget, t_window_d * window_d);
void OnDestroy(GtkWidget *widget, t_window * window);
void OnButton_null(GtkWidget *pWidget, gpointer data);

#endif
