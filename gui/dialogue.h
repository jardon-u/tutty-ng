#ifndef H_DIALOGUE
#define H_DIALOGUE

void OnButton_send(GtkWidget *pWidget, t_window_d * window_d);
void OnKill_d(GtkWidget *widget, t_window_d *window_d);
int init_dialogue(t_window_d * window_d, t_window * window);
void OnButton_send_file(GtkWidget *pWidget, gpointer data);
void OnButton_p2p(GtkWidget *pWidget,  t_window_d * window_d);

#endif
