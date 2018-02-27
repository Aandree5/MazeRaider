#include "UIHelpers.h"
#include "LevelManager.h"
#include <iostream>
#include <tuple>
#include <string>
#include <windows.h>
#include <mysql.h>
#include <cstdlib>
#include <windows.h>

using namespace std;
using namespace UIHelpers;

/**
 * Main.
 *
 * @author Jesse
 * @author Vihan
 */

MYSQL* connection;

void printLogo() {
    cout<<"  __  __                 _____       _     _                   \n"
            <<" |  \\/  |               |  __ \\     (_)   | |            \n"
            <<" | \\  / | __ _ _______  | |__) |__ _ _  __| | ___ _ __    \n"
            <<" | |\\/| |/ _` |_  / _ \\ |  _  // _` | |/ _` |/ _ \\ '__| \n"
            <<" | |  | | (_| |/ /  __/ | | \\ \\ (_| | | (_| |  __/ |     \n"
            <<" |_|  |_|\\__,_/___\\___| |_|  \\_\\__,_|_|\\__,_|\\___|_| \n"
            << endl;
}

void printMenu() {
    cout << "    ------------------------------------------------" << endl;
    cout << "    |  1. Login                                    |" << endl;
    cout << "    |  2. Signup                                   |" << endl;
    cout << "    |  3. Exit                                     |" << endl;
    cout << "    ------------------------------------------------" << endl;
    cout << endl << "    Option: ";
}

void connectToDatabase() {
    cout << "Connecting to database..." << endl;
    connection = mysql_init(0);
    mysql_real_connect(connection,"server1.jesseprescott.co.uk","jessepre","Mazeraider123?","jessepre_mazeraider",0,NULL,0);
    if(connection){
        cout << "Successfully connected to database." << endl;
    } else {
        cout << "Failed to connect to the database." << endl;
        exit(0);
    }
}

void loginUser() {
    string username,password;
    cout << endl << "   ------------------------------------------------------------------" << endl;
    cout << "   Username: "; cin >> username;
    cout << "   Password: "; cin>>password;

    // TODO: Fix SQL Injection.
    string query="select customer_id from information where username='"+username+"' and password='"+password+"';";

    int queryResult = mysql_query(connection, query.c_str());
    MYSQL_RES* result = mysql_store_result(connection);

    if (mysql_num_rows(result) >= 1) {
        MYSQL_ROW row = mysql_fetch_row(result);

        delete result;
        result = nullptr;
        delete connection;
        connection = nullptr;

        LevelManager *lvlManager = new LevelManager(atoi(row[0]));

        delete lvlManager;
        lvlManager = nullptr;
    } else {
        cout << "Incorrect username or password." << endl;
        system("pause");
    }
}

void registerUser() {
    string name,username,password;
    cout<<"First Name: "; cin>>name;
    cout<<"Username: "; cin>>username;
    cout<<"Password: "; cin>>password;

    string register_users="insert into information(name,username,password) values('"+name+"','"+username+"','"+password+"')";
    int querystate = mysql_query(connection, register_users.c_str());

    if(!querystate) {
        cout<<"Registration successful" << endl;
        system("pause");
        cin;
    } else {
        cout<<"Failed to register, error: " << mysql_error(connection) << endl;
        system("pause");
    }
}

int main() {
    setFullScreen();


    connectToDatabase();

    while (1) {
        clearScreen();
        printLogo();
        printMenu();
        char choice;
        cin >> choice;

        if (choice == '1') {
            loginUser();
        } else if (choice == '2'){
            clearScreen();
            registerUser();
        } else if (choice == '3'){
            exit(0);
        } else {
            clearScreen();
            cout << "Invalid input." << endl;
            system("pause");
        }
    }
}
