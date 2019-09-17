#include <gtk/gtk.h>

void toggle_statusbar(GtkWidget *widget, gpointer statusbar) {

	if (gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(widget))) {

		gtk_widget_show(statusbar);
	} else {

		gtk_widget_hide(statusbar);
	}
}

void show_about(GtkWidget *widget, gpointer about) {

	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("battery.png", NULL);

	GtkWidget *dialog = gtk_about_dialog_new();
	gtk_about_dialog_set_name(GTK_ABOUT_DIALOG(dialog), "Battery");
	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), "0.9"); 
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog),"(c) Jan Bodnar");
	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), 
			"Battery is a simple tool for battery checking.");
	gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog), 
			"http://www.batteryhq.net");
	gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), pixbuf);
	g_object_unref(pixbuf), pixbuf = NULL;
	gtk_dialog_run(GTK_DIALOG (dialog));
	gtk_widget_destroy(dialog);
}


int main(int argc, char *argv[]) {

	GtkWidget *window;
	GtkWidget *vbox;

	GtkWidget *menubar;
	GtkWidget *viewmenu;
	GtkWidget *view;
	GtkWidget *statusbar;
	GtkWidget *aboutmenu;
	GtkWidget *about;
	GtkWidget *tog_stat;
	GdkPixbuf *battery;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
	gtk_window_set_title(GTK_WINDOW(window), "About");

	gtk_container_set_border_width(GTK_CONTAINER(window), 15);

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	menubar = gtk_menu_bar_new();
	viewmenu = gtk_menu_new();

	view = gtk_menu_item_new_with_label("View");
	tog_stat = gtk_check_menu_item_new_with_label("View statusbar");
	about = gtk_menu_item_new_with_label("About");
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(tog_stat), TRUE);

	gtk_menu_item_set_submenu(GTK_MENU_ITEM(view), viewmenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(viewmenu), tog_stat);
	gtk_menu_shell_append(GTK_MENU_SHELL(viewmenu), about);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), view);
	gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 0);

	statusbar = gtk_statusbar_new();
	gtk_box_pack_end(GTK_BOX(vbox), statusbar, FALSE, TRUE, 0);

	g_signal_connect(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);

	g_signal_connect(G_OBJECT(tog_stat), "activate",
			G_CALLBACK(toggle_statusbar), statusbar);

	g_signal_connect(G_OBJECT(window), "clicked",
			G_CALLBACK(show_about), about);

	gtk_widget_show_all(window);

	gtk_main();

	return 0;

}
