#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dbus/dbus.h>

//use this command to compile " gcc -o dbus_connection_name -Wall main.c `pkg-config --cflags dbus-1` `pkg-config --libs dbus-1` "


int main() {
    DBusConnection *connection = NULL;
    DBusError error;
     //char buffer[1024];
 
    //init error 
    dbus_error_init(&error);
    //get connection to bus
    connection = dbus_bus_get(DBUS_BUS_SESSION, &error);
    //if error, print error and exit
    if (dbus_error_is_set(&error)) {
        fprintf(stderr, "%s", error.message);
        abort();
    }

    puts("This is my unique name");
    //print out unique bus name
    puts(dbus_bus_get_unique_name(connection));
    
    //close bus connections(good practice)
    //dbus_connection_close(connection);
     

    return 0;
}
