#ifndef H_FENETRES
#define H_FENETRES

#include <types.h>

void init_main_window(t_window* window);

void OnKill_p(GtkWidget* widget);

int init_preferences(t_window* window);

void OnDPress_rub(GtkTreeView*       tree_view,
		  GtkTreePath*       path,
		  GtkTreeViewColumn* column,
		  t_window*          window);

void OnClear_HBox_p(GtkWidget* widget,
		    t_window*  window);

void OnPress_preferences(GtkWidget* widget,
			 t_window*  window);

int init_toolbar(t_window* window);

void init_statusBar(t_window* window);

void OnButton_logo(GtkWidget* widget,
		   t_window*  window);

void OnButton_red(GtkWidget* widget,
		  t_window*  window);

void OnButton_dual(GtkWidget* widget,
		   t_window*  window);


#endif
