#include "LevelManager.h"
#include <iostream>
#include <tuple>
#include <string>
#include <windows.h>
#include <mysql.h>
#include <cstdlib>


using namespace std;


int main()
{
    cout<<"                                   _                    _        _ _ _ _ _ _ _ _                                                                                 _    \n"
        <<"                                   _ _                _ _        _             _                                                                                 _    \n"
        <<"                                   _   _            _   _        _             _                                                                                 _    \n"
        <<"                                   _     _        _     _        _             _                                                                                 _    \n"
        <<"                                   _       _    _       _        _             _                                                                                 _    \n"
        <<"                                   _         __         _        _ _ _ _ _ _ _ _                                                                                 _    \n"
        <<"                                   _                    _        _     _                                                                                         _    \n"
        <<"                                   _                    _        _       _                                                                                       _    \n"
        <<"                                   _                    _        _         _            __   ___   ___    __     ___   __    ___        __     __                _    \n"
        <<"                                   _                    _        _           _         |__  |   | |  __  |__    |   | |__   |    |     ____   |__  |__|          _    \n"
        <<"                                   _                    _        _             _       |__  |___| |___|| |__    |___| |     |___ |__  _______  __| |  |          _    \n"
        <<"__________________________________________________________________________________________________________________________________________________________________\n\n\n";

    while (1){
        char choice[2];

        cout
            <<" 1. Login \n\n"
            <<" 2. Sign up \n\n"
            <<" 3. Exit \n\n"
            <<"\n\n"
            <<"Option: \n";

            cin >> choice;

            if (choice[0] == '1'){

            MYSQL* connection;

            connection = mysql_init(0);

            connection = mysql_real_connect(connection,"server1.jesseprescott.co.uk","jessepre","Mazeraider123?","jessepre_mazeraider",0,NULL,0);

        if(connection){
        cout<<"Connected\n"<<endl;

        string username,password;
        cout<<"enter username: \n"<<endl; cin>>username;
        cout<<"enter password: \n"<<endl; cin>>password;

        string query="select * from information where username='"+username+"' and password='"+password+"';";

        int queryResult = mysql_query(connection, query.c_str());
        MYSQL_RES* result = mysql_store_result(connection);

        if (mysql_num_rows(result) >= 1)
        {
            cout<<"Welcome to the game"<<endl;
            new LevelManager();
        }
        else{
            cout<<"Please try again"<<endl;
            cout<<"---------------------------------------------------------------------------------------------------------\n\n"<<endl;
        }

    }

}
        else if (choice[0] == '2'){

        MYSQL* connection;

        int qstate;

     connection = mysql_init(0);

     connection = mysql_real_connect(connection,"server1.jesseprescott.co.uk","jessepre","Mazeraider123?","jessepre_mazeraider",0,NULL,0);

     if(connection){
        cout<<"Connected to the database\n\n"<<endl;

        string name,username,password;
        cout<<"enter name: \n"<<endl; cin>>name;
        cout<<"enter username: \n"<<endl; cin>>username;
        cout<<"enter password: \n"<<endl; cin>>password;


        string query="insert into information(name,username,password) values('"+name+"','"+username+"','"+password+"')";


        const char* q = query.c_str();

        qstate = mysql_query(connection,q);

        if(!qstate)
            cout<<"Register successful\n\n"
                <<"---------------------------------------------------------------------------------------------------------\n\n"<<endl;
        else
            cout<<"Sorry try it again \n\n"<<mysql_error(connection)<<endl;
            }

        }
        if (choice[0] == '3'){
            exit(0);

        }

        else if (choice [0] > '3' || choice[0] < '1'){

         cout << "Invalid input\n\n";
         cout << "Please try again\n\n";

        }
    }
}
