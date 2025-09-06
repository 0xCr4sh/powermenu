#include <app.hpp>
#include <iostream>

PowerMenuApp::PowerMenuApp() {
    app = gtk_application_new("com.powermenu.app", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate_static), this);
}

int PowerMenuApp::run(int argc, char **argv) {
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}

void PowerMenuApp::on_activate_static(GtkApplication* app, gpointer user_data) {
    // LOADING UI FROM BUILT RESOURCES
    gchar *xml_path = g_build_filename(
        g_get_user_config_dir(),
        "0xCr4sh-powermenu",
        "interface.xml",
        NULL
    );

    gchar *css_path = g_build_filename(
        g_get_user_config_dir(),
        "0xCr4sh-powermenu",
        "style.css",
        NULL
    );

    GtkBuilder* builder = gtk_builder_new_from_file(xml_path);
    g_free(xml_path);

    // Loading window
    GtkWidget *main_window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    gtk_window_set_application(GTK_WINDOW(main_window), app);

    // Set window properties
    gtk_window_set_decorated(GTK_WINDOW(main_window), FALSE);


    //gtk_window_fullscreen(GTK_WINDOW(main_window));

    // Loading buttons
    GtkWidget* poweroff_btn  = GTK_WIDGET(gtk_builder_get_object(builder, "poweroff_button"));
    if (poweroff_btn) g_signal_connect(poweroff_btn, "clicked", G_CALLBACK(on_poweroff_clicked), NULL);

    GtkWidget* reboot_btn    = GTK_WIDGET(gtk_builder_get_object(builder, "reboot_button"));
    if (reboot_btn) g_signal_connect(reboot_btn, "clicked", G_CALLBACK(on_reboot_clicked), NULL);

    GtkWidget* suspend_btn   = GTK_WIDGET(gtk_builder_get_object(builder, "suspend_button"));
    if (suspend_btn) g_signal_connect(suspend_btn, "clicked", G_CALLBACK(on_suspend_clicked), NULL);

    GtkWidget* hibernate_btn = GTK_WIDGET(gtk_builder_get_object(builder, "hibernate_button"));
    if (hibernate_btn) g_signal_connect(hibernate_btn, "clicked", G_CALLBACK(on_hibernate_clicked), NULL);

    GtkWidget* logout_btn    = GTK_WIDGET(gtk_builder_get_object(builder, "logout_button"));
    if (logout_btn) g_signal_connect(logout_btn, "clicked", G_CALLBACK(on_logout_clicked), NULL);

    GtkWidget* cancel_btn    = GTK_WIDGET(gtk_builder_get_object(builder, "cancel_button"));

    if (cancel_btn) g_signal_connect(cancel_btn, "clicked", G_CALLBACK(+[] (GtkButton*, gpointer win) {
            gtk_window_close(GTK_WINDOW(win));
    }), main_window);
    
    // Load and apply CSS
    GtkCssProvider* css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(css_provider, css_path);
    g_free(css_path);

    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),         // the display
        GTK_STYLE_PROVIDER(css_provider),  // your CSS provider
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION // priority
    );

    // Show the window
    gtk_widget_show(main_window);

    // Clean up css provider (we don’t need it anymore)
    g_object_unref(css_provider);

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
