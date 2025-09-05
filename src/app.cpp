#include <app.hpp>
#include <iostream>

PowerMenuApp::PowerMenuApp() {
    app = gtk_application_new("com.gtk4.PowerMenu", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate_static), this);
}

int PowerMenuApp::run(int argc, char **argv) {
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}

void PowerMenuApp::on_activate_static(GtkApplication* app, gpointer user_data) {
    PowerMenuApp* self = static_cast<PowerMenuApp*>(user_data);

    // LOADING UI FROM BUILT RESOURCES
    gchar *config_path = g_build_filename(
        g_get_user_config_dir(),
        "0xCr4sh_powermenu",
        "interface.xml",
        NULL
    );

    GtkBuilder* builder = gtk_builder_new_from_file(config_path);
    g_free(config_path);

    // Loading window
    GtkWidget *main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    gtk_window_set_application(GTK_WINDOW(main_window), app);
    self->window = main_window;

    // Loading buttons
    GtkWidget* poweroff_btn  = GTK_WIDGET(gtk_builder_get_object(builder, "poweroff_button"));
    g_signal_connect(poweroff_btn, "clicked", G_CALLBACK(on_poweroff_clicked), NULL);

    GtkWidget* reboot_btn    = GTK_WIDGET(gtk_builder_get_object(builder, "reboot_button"));
    g_signal_connect(reboot_btn, "clicked", G_CALLBACK(on_reboot_clicked), NULL);

    GtkWidget* suspend_btn   = GTK_WIDGET(gtk_builder_get_object(builder, "suspend_button"));
    g_signal_connect(suspend_btn, "clicked", G_CALLBACK(on_suspend_clicked), NULL);

    GtkWidget* hibernate_btn = GTK_WIDGET(gtk_builder_get_object(builder, "hibernate_button"));
    g_signal_connect(hibernate_btn, "clicked", G_CALLBACK(on_hibernate_clicked), NULL);

    GtkWidget* logout_btn    = GTK_WIDGET(gtk_builder_get_object(builder, "logout_button"));
    g_signal_connect(logout_btn, "clicked", G_CALLBACK(on_logout_clicked), NULL);

    GtkWidget* cancel_btn    = GTK_WIDGET(gtk_builder_get_object(builder, "cancel_button"));

    if (cancel_btn) {
        g_signal_connect(cancel_btn, "clicked", G_CALLBACK(+[] (GtkButton*, gpointer win) {
            gtk_window_close(GTK_WINDOW(win));
        }), main_window);
    }

    // Show the window
    gtk_widget_show(main_window);

    // Clean up builder (we don’t need it anymore)
    g_object_unref(builder);
}

void PowerMenuApp::on_poweroff_clicked(GtkButton* btn, gpointer user_data) {
    std::system("poweroff");
}

void PowerMenuApp::on_reboot_clicked(GtkButton* btn, gpointer user_data) {
    std::system("reboot");
}

void PowerMenuApp::on_suspend_clicked(GtkButton* btn, gpointer user_data) {
    std::system("bash -c 'sleep 1; systemctl suspend &'");
    exit(0); 
}

void PowerMenuApp::on_hibernate_clicked(GtkButton* btn, gpointer user_data) {
    std::system("bash -c 'sleep 1; systemctl suspend &'");
    exit(0); 
}

void PowerMenuApp::on_logout_clicked(GtkButton* btn, gpointer user_data) {
    std::system("loginctl terminate-user $USER");
}
