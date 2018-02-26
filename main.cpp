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
//this will show up on the screen
void printMenu() {
    cout << "    ------------------------------------------------" << endl;
    cout << "    |  1. Login                                    |" << endl;
    cout << "    |  2. Signup                                   |" << endl;
    cout << "    |  3. Exit                                     |" << endl;
    cout << "    ------------------------------------------------" << endl;
    cout << endl << "    Option: ";
}
//I made a function to connect the database
void connectToDatabase() {
    connection = mysql_init(0);
    //this will connect to the database
    mysql_real_connect(connection,"server1.jesseprescott.co.uk","jessepre","Mazeraider123?","jessepre_mazeraider",0,NULL,0);
    //if connection successful it will successfully connect to the database
    if(connection){
        cout << "Successfully connected to database." << endl;
    } else {
        //if not it will say it didn't connect to do database and exit from the application
        cout << "Failed to connect to the database." << endl;
        exit(0);
    }
}

void loginUser() {
    string username,password;
    cout << endl << "   ------------------------------------------------------------------" << endl;
    //user basically need insert username and password because it has cin
    cout << "   Username: "; cin >> username;
    cout << "   Password: "; cin>>password;

    //link the database using sql query
    string query="select customer_id from information where username='"+username+"' and password='"+password+"';";

    int queryResult = mysql_query(connection, query.c_str());
    MYSQL_RES* result = mysql_store_result(connection);
    MYSQL_ROW row;
    //if there is a row or multiple rows it will allow you to go to the Level manager(actual game)
    if ((row = mysql_fetch_row(result)) != NULL) {
        new LevelManager(atoi(row[0]));
    } else {
        //if it is not matching it will say incorrect username or password
        cout << "Incorrect username or password." << endl;
        system("pause");
    }
}

void registerUser() {
    //these usename and first name and password will show up on the screen
    string name,username,password;
    cout<<"First Name: "; cin>>name;
    cout<<"Username: "; cin>>username;
    cout<<"Password: "; cin>>password;
    //then we will link the database using insert into the database. I use insert because it will store data in the database.
    //Then it will check the values of the database then once user put values in database will automatically store the information.
    string register_users="insert into information(name,username,password) values('"+name+"','"+username+"','"+password+"')";
    const char* q = register_users.c_str();
    int querystate = mysql_query(connection,q);
    //If it allow you to register it will say register successful
    if(!querystate) {
        cout<<"Registration successful" << endl;
        system("pause");
        cin;
    } else {
        //if it failed to do it; it will send you an error message with the reason why
        cout<<"Failed to register, error: " << mysql_error(connection) << endl;
        system("pause");
    }
}

int main() {
    //this will put screen to full screen
    setFullScreen();

    //we are using function to connect to the database
    connectToDatabase();

    while (1) {
        clearScreen();
        printLogo();
        printMenu();
        char choice;
        cin >> choice;
        //when user press one it will call login function
        if (choice == '1') {
            loginUser();
            //when user press 2 it will clear the screen and call the register user function
        } else if (choice == '2'){
            clearScreen();
            registerUser();
        } else if (choice == '3'){
            //if user press 3 it will exit from the game
            exit(0);
        } else {
            //if user put a invalid input it will show up an message and wait for user input
            clearScreen();
            cout << "Invalid input." << endl;
            system("pause");
        }
    }
}
