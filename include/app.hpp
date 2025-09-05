#include <gtk/gtk.h>
#include <cstdlib>
#include <thread>

class PowerMenuApp {
public:
    PowerMenuApp();
    int run(int argc, char **argv);

private:
    static void on_activate_static(GtkApplication* app, gpointer user_data);
    
    static void on_poweroff_clicked(GtkButton* btn, gpointer user_data);
    static void on_reboot_clicked(GtkButton* btn, gpointer user_data);
    static void on_suspend_clicked(GtkButton* btn, gpointer user_data);
    static void on_hibernate_clicked(GtkButton* btn, gpointer user_data);
    static void on_logout_clicked(GtkButton* btn, gpointer user_data);

    GtkApplication* app;
    GtkWidget *window;
};