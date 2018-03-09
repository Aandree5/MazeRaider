#include "UIHelpers.h"
#include "LevelManager.h"
#include <iostream>
#include <tuple>
#include <mmsystem.h>
#include <string>
#include <windows.h>
#include <mysql.h>
#include <cstdlib>
#include <conio.h>

using namespace std;
using namespace UIHelpers;

/**
 * Main.
 *
 * @author Jesse
 * @author Vihan
 */

MYSQL *connection;

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
    cout << "    |  3. Admin                                    |" << endl;
    cout << "    |  4. Exit                                     |" << endl;
    cout << "    ------------------------------------------------" << endl;
    cout << endl;
}

void printadmin() {
    cout << "    ------------------------------------------------------" << endl;
    cout << "    |  1. User update                                    |" << endl;
    cout << "    |  2. User delete                                    |" << endl;
    cout << "    |  3. Exit to Main menu                              |" << endl;
    cout << "    ------------------------------------------------------" << endl;
    cout << endl;
}
//this is how we connect to the database
void connectToDatabase() {
    connection = mysql_init(0);
    //tell where is our database is
    mysql_real_connect(connection,"server1.jesseprescott.co.uk","jessepre","Mazeraider123?","MazeRaider_DB",0,NULL,0);
    if(connection){
            //when successfully connected it will say connected
        cout << "Successfully connected to database." << endl;
    } else {
        //if unsuccessful it will say failed
        cout << "Failed to connect to the database." << endl;
        exit(0);
    }
}
//login
void loginUser() {
    string username,password;
    cout << endl << "   ------------------------------------------------------------------" << endl;
    //it will show up as username and password
    username = requestFromUser<string>("Username: ");
    password = requestFromUser<string>("Password: ");

    // this is when user put username and password go to the UserInfo table and check if information right or wrong.
    //I add placeholders in
    string query=SQLPrepare("select userID from UserInfo where username = '%?' and password = '%?'", username, password);
    //This will check the if user information right or wrong
    int queryResult = mysql_query(connection, query.c_str());
    MYSQL_RES *result = mysql_store_result(connection);
    MYSQL_ROW row;
    //when user sucessfully login it will go to the level manager
    if ((row = mysql_fetch_row(result)) != NULL) {

        shared_ptr<LevelManager> lvlManager = make_shared<LevelManager>(atoi(row[0]));
        lvlManager->BuildLevel();

    } else {
        //if not it will show the error message
        cout << "Incorrect username or password." << endl;
    }
}
//register
void registerUser() {
    string name,username,password;
    //this is where user put information
    cout<<"First Name: "; cin>>name;
    cout<<"Username: "; cin>>username;
    cout<<"Password: "; cin>>password;
    //When user put information it will insert data into UserInfo table and it will store as a string
    string register_users = SQLPrepare("insert into UserInfo(name,username,password) values('%?','%?','%?')", name, username, password);
    int querystate = mysql_query(connection, register_users.c_str());
    //Then if it worked it will say register successful
    if(!querystate) {
        cout<<"Registration successful" << endl;
        system("pause");
        cin;
    } else {
        //if not it will say register failed
        cout<<"Failed to register, error: " << mysql_error(connection) << endl;
        system("pause");
    }
}

void deleteusers(){
    int userID;

    cout<<"ID: "; cin>>userID;
    //When user put information it will delete data in UserInfo table and it will store as a string
    string delete_char = SQLPrepare("DELETE FROM PlayerChar WHERE playerID=%?", userID);

    if(mysql_query(connection, delete_char.c_str()))
        cout << mysql_error(connection) << endl;

    string delete_user = SQLPrepare("DELETE FROM UserInfo WHERE userID=%?", userID);

    if(mysql_query(connection, delete_user.c_str()))
        cout << mysql_error(connection) << endl;

}

void showuser(){

    int query;
    MYSQL_ROW row;
    MYSQL_RES *results;

    //Now we are linking tables in the database.

    string showdata = UIHelpers::SQLPrepare("SELECT * FROM UserInfo");

    //this will allow get the data as a sting
    query = mysql_query(connection, showdata.c_str());
    if(!query){
        //this will allow you to show up the results
        results = mysql_store_result(connection);

        //this will allow to show the number of their rank.
        //rows represent the actual able rows and we will cout them to show up in the actual game.
        while((row = mysql_fetch_row(results)))
        {
            //This is the layout of the highscore system.
            cout<< "   ||   "<<row[0]<<  "   ||   "<<row[1]<< "   ||   "<<row[2]<<"   ||   "<<row[3]<<" "<<endl;
            cout<<endl;
        }


}
}
void update(){
    string name, password, username, userID;

    cout<<"name: "; cin>>name;
    cout<<"password: "; cin>>password;
    cout<<"username: "; cin>>username;
    cout<<"userID: "; cin>>userID;

    string updateuser = SQLPrepare("UPDATE UserInfo SET name ='%?', username = '%?', password = '%?' WHERE userID = '%?'",name,username, password, userID);
    int querystate = mysql_query(connection, updateuser.c_str());

    if(!querystate) {
        cout<<"update successful" << endl;
        system("pause");
        cin;
    } else {
        //if not it will say update failed
        cout<<"Failed to update, error: " << mysql_error(connection) << endl;
        system("pause");
    }


}
void admin(){

    printLogo();

    cout<<"Welcome to the Admin\n"<<endl;

    string name, password;

    //it will show up as name and password
    name = requestFromUser<string>("Name: ");
    password = requestFromUser<string>("Password: ");

    // this is when user put name and password go to the UserInfo table and check if Admin right or wrong.
    //I add placeholders in
    string query=SQLPrepare("select adminID from Admin where name = '%?' and password = '%?'", name, password);
    //This will check the if user Admin right or wrong
    int queryResult = mysql_query(connection, query.c_str());
    MYSQL_RES *result = mysql_store_result(connection);
    MYSQL_ROW row;
    //when user sucessfully login it will go to the level manager
    if ((row = mysql_fetch_row(result)) != NULL) {
            clearScreen();
            printLogo();
            printadmin();

            //This will show up the choose option when user put an option it will call the function
            char choice = requestFromUser<char>("Choose an option: ", 1, 4);


            if (choice == '1') {
                clearScreen();
                cout<<"     user id     name        username    password"<<endl;
                cout<<"   _______________________________________________"<<endl;
                showuser();

                update();

            } else if (choice == '2'){
                clearScreen();
                cout<<"     user id     name        username    password"<<endl;
                cout<<"   _______________________________________________"<<endl;
                showuser();
                deleteusers();

            } else if (choice == '3'){
                clearScreen();
                printMenu();

            } else {
                //If user put a invalid character it will say invalid input.
                clearScreen();
                cout << "Invalid input." << endl;
                system("pause");
            }


        } else {
            //if not it will show the error message
            cout << "Incorrect username or password." << endl;
            system("pause");
        }
}

int main() {

    waveOutSetVolume(0, -1);
    //This is where we put full screen
    SetFullScreen();
    //We are using connect to the database
    connectToDatabase();

    while (true) {
            //This is where we put music in for the game. This will play the main menu song
        PlaySound(TEXT("sounds/musics/MainMenu.wav"),NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        //This will clear the screen
        clearScreen();
        //This will print the logo
        printLogo();
        //This will print the menu
        printMenu();
        //This will show up the choose option when user put an option it will call the function
        char choice = requestFromUser<char>("Choose an option: ", 1, 5);


        if (choice == '1') {
            loginUser();
        } else if (choice == '2'){
            clearScreen();
            registerUser();
        } else if (choice == '3'){
            clearScreen();
            admin();
        } else if (choice == '4'){
            exit(1);
        } else {
            //If user put a invalid character it will say invalid input.
            clearScreen();
            cout << "Invalid input." << endl;
            system("pause");

}
    }

}

