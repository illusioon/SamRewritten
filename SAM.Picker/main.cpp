/**
 * Please read the license before modifying or distributing any of the code from
 * this project. Thank you.
 */

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <gtk/gtk.h>
#include <gmodule.h>
#include "MySteam.h"
#include "MainPickerWindow.h"

int launcher_main();

//Globals
//Reason for the globals is that it's easier to access
//in GTK callbacks
MySteam *g_steam = nullptr; // The Model
MainPickerWindow *g_main_gui = nullptr; // The view

int 
main(int argc, char *argv[])
{
    if(!g_module_supported()) {
        std::cerr << "Sorry, but gmodules are not supported on your platform :(. Try installing as many gnome libs as you can maybe.." << std::endl;
        exit(EXIT_FAILURE);
    }
    
    gtk_init(&argc, &argv);
    
    launcher_main();
    return 0;
}

int 
launcher_main() {

    g_main_gui = new MainPickerWindow();

    gtk_widget_show(g_main_gui->get_main_window());
    gtk_main();

    //steam->launch_game("368230");

    //steam->quit_game();

    

    return 0;
}

//Gtk Callbacks
//Controller
extern "C" 
{
    // When you click on the close button if steam is not running
    void 
    on_close_button_clicked() {
        gtk_main_quit();
        std::cerr << "Gtk did main quit" << std::endl;
        delete g_main_gui;
        g_main_gui = nullptr;
    }

    void 
    on_ask_game_refresh() {
        std::cerr << "Game refresh started." << std::endl;
        g_main_gui->reset_game_list();

        //Only call that here so that the constructor is executed when the 
        //window is already showing.
        g_steam = MySteam::get_instance();
        g_steam->refresh_owned_apps();

        g_main_gui->add_to_game_list("My Game name");

    }

    void 
    on_main_window_show() {
        on_ask_game_refresh();
    }
}