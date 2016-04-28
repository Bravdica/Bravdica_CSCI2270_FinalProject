#include <iostream>
#include "MovieTree.h"
#include <sstream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[]){
    MovieTree tree = MovieTree();
    string username;
    string pass;
    int user=0;
    int login=false;
    int account=0;
    ifstream inFile;
    string data;
    inFile.open(argv[1]);
    while(getline(inFile, data)){
        string input = data;
        stringstream ss(data);
        string r;
        getline(ss,r,',');
        string Title;
        getline(ss,Title,',');
        string y;
        getline(ss,y,',');
        string q;
        getline(ss,q,',');
        int ranking = atoi (r.c_str());
        int year = atoi (y.c_str());
        int quant = atoi (q.c_str());
        tree.addMovieNode(ranking, Title, year, quant);
    }
    inFile.close();

    ifstream in("Users.txt"); //Checks if file is empty so it does not overwrite
    if(in.is_open()){
        in.seekg(0,ios::end);
        size_t size = in.tellg();
        if( size == 0){
             tree.buildLogins();
        }
    }

    while(login==false){
        bool check=false;
        cout << "Do you have an account? (0=no, 1=yes): " <<endl;
        cin >> account;
        if(account==1){
            cin.ignore();
            cout << "Please enter your user name: " << endl;
            getline(cin,username);
            cout << "Please enter your password: " << endl;
            getline(cin,pass);
            check = tree.check(username, pass);
            if(check==true){
                cout<< "Welcome "<< username << endl;
                break;
            }
            else{
                cout << "I'm sorry, that username/password does not exist." << endl;
            }
        }
        else{
            cin.ignore();
            string newUser;
            string newPass;
            cout << "Creating an account:" << endl << endl;
            cout << "Please enter a username (no spaces): " << endl;
            getline(cin,newUser);
            cout <<"Please enter a password: " << endl;
            getline(cin,newPass);
            tree.addUser(newUser, newPass);
            cout << "Congratulations! You have successfully created an account!" << endl;
            break;
        }
    }

    while(user!=6){
        cout << "======Main Menu======" << endl;
        cout << "0. Build user network" << endl;
        cout << "1. Find a movie" << endl;
        cout << "2. Rent a movie" << endl;
        cout << "3. Print the inventory" << endl;
        cout << "4. Delete a movie" << endl;
        cout << "5. Count the movies" << endl;
        cout << "6. Quit" << endl;

        cin >> user;

        if(user==0){
            tree.buildLogins();
        }

        if(user==1){    // Find a movie
            cin.ignore();
            string titleWanted;
            cout << "Enter title:" << endl;
            getline(cin,titleWanted);
            tree.findMovie(titleWanted);
        }
        else if(user==2){   //Rent a movie
            cin.ignore();
            string titleRented;
            cout << "Enter title:" << endl;
            getline(cin,titleRented);
            tree.rentMovie(titleRented, username);
        }
        else if(user==3){   //Print the inventory
            tree.printMovieInventory();
        }
        else if(user==4){   //Delete a movie
            cin.ignore();
            string movieToDelete;
            cout << "Enter title:" << endl;
            getline(cin,movieToDelete);
            tree.deleteMovieNode(movieToDelete);
        }
        else if(user==5){   //Count the movies
            tree.countMovieNodes();
        }
        else if(user==6){   //Quit
            break;
        }
    }
    cout << "Goodbye!" << endl;
}
