#include "headers/Database.h"
#include "headers/Menu.h"

int main(){
    Database database;
    Menu menu(database);
    menu.showDataSelectionMenu();
    return 0;
}