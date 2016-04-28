#include "MovieTree.h"
#include <sstream>
#include <fstream>
#include <string>
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::stringstream;
using std::ofstream;

MovieTree::MovieTree()
{
    //ctor
    root=NULL;

    ifstream in("Users.txt"); //Checks if file is empty so it does not overwrite
    if(in.is_open()){
        in.seekg(0,std::ios::end);
        size_t size = in.tellg();
        if( size == 0){
            head = new User;
            head->username = "Master";
            head->pass = "Master";
            head->pos = 1;
            head->next = NULL;
            cout << "initial" << endl;
        }
    }
}

MovieTree::~MovieTree()
{
    //dtor
    DeleteAll(root);
}



void MovieTree::printMovieInventory(){
    printMovieInventory(root);
}

int MovieTree::countMovieNodes(){
    int counter;
    counter = countMovieNodes(root);
    cout<<"Tree contains: "<<counter<<" movies."<< endl;
}

void MovieTree::deleteMovieNode(std::string title){
    MovieNode *node = search(title);
    MovieNode *mini=new MovieNode;
    MovieNode *x=new MovieNode;
    if(node != root){
        if(node->leftChild == NULL and node->rightChild == NULL){   //NO Children
            if(node->parent->leftChild==node){
                node->parent->leftChild=NULL;
            }
            else{
                node->parent->rightChild=NULL;
            }
        }
        else if(node->leftChild != NULL and node->rightChild != NULL){  //2 children
            mini = treeMinimum(node->rightChild);
            if(mini==node->rightChild){
                node->parent->leftChild = mini;
                mini->parent = node->parent;
                delete node;
            }
            else{
                mini->parent->leftChild = mini->rightChild;
                mini->parent = node->parent;
                mini->rightChild->parent = mini->parent;
                node->parent->leftChild=mini;
                mini->leftChild=node->leftChild;
                mini->rightChild=node->rightChild;
                node->rightChild->parent = mini;
                node->leftChild->parent=mini;
                delete node;
            }
            if(node->parent->leftChild==node){
                node->parent->leftChild=NULL;
            }
            else{
                node->parent->rightChild=NULL;
            }
        }
        else if(node->leftChild != NULL and node->rightChild == NULL){   //1 child on left
            if(node->parent->leftChild==node){
                x=node->leftChild;
                node->parent->leftChild=x;
                x->parent=node->parent;
            }
            else{
                x=node->leftChild;
                node->parent->rightChild=x;
                x->parent=node->parent;
            }
        }
        else if(node->rightChild != NULL and node->leftChild == NULL){
            if(node->parent->rightChild==node){
                x=node->rightChild;
                node->parent->rightChild=x;
                x->parent=node->parent;
            }
            else{
                x=node->rightChild;
                node->parent->leftChild=x;
                x->parent=node->parent;
            }
        }
    }
}

void MovieTree::addMovieNode(int ranking, std::string title, int releaseYear, int quantity){
        MovieNode *tmp=root;
        MovieNode *node=new MovieNode;
        MovieNode *Parent=NULL;
        node->ranking = ranking;
        node->title = title;
        node->year=releaseYear;
        node->quantity=quantity;
        node->parent=NULL;
        node->leftChild=NULL;
        node->rightChild=NULL;
        while(tmp != NULL){
            Parent = tmp;
            if(node->title.compare(tmp->title) < 0 ){
                tmp = tmp->leftChild;
            }
            else{
                tmp = tmp->rightChild;
            }
        }
        if (Parent == NULL){
            root = node;
        }
        else if(node->title.compare(Parent->title) < 0){
            Parent->leftChild = node;
            node->parent = Parent;
        }
        else{
            Parent->rightChild = node;
            node->parent = Parent;
        }
}

void MovieTree::findMovie(std::string title){
    MovieNode *Title = search(title);
    if(Title==NULL){
        cout << "Movie not found." << endl;
    }
    else{
        cout << "Movie Info:" << endl;
        cout << "===========" << endl;
        cout << "Ranking:" << Title->ranking << endl;
        cout << "Title:" << Title->title << endl;
        cout << "Year:" << Title->year << endl;
        cout << "Quantity:" << Title->quantity << endl;
    }
}

void MovieTree::rentMovie(std::string title, std::string username){
    //If movie is in stock
    MovieNode *foundMovie = search(title);
    if(foundMovie==NULL){
        cout << "Movie not found." << endl;
    }
    else{
        if(foundMovie->quantity==0){
            cout << "Movie out of stock." << endl;
        }
        else{
            foundMovie->quantity=foundMovie->quantity-1;
            cout << "Movie has been rented." << endl;
            cout << "Movie Info:" << endl;
            cout << "===========" << endl;
            cout << "Ranking:" << foundMovie->ranking << endl;
            cout << "Title:" << foundMovie->title << endl;
            cout << "Year:" << foundMovie->year << endl;
            cout << "Quantity:" << foundMovie->quantity << endl;
        }
    }
}

void MovieTree::DeleteAll(MovieNode * node){
    if(node != NULL){
        if(node->leftChild) DeleteAll(node->leftChild);
        if(node->rightChild) DeleteAll(node->rightChild);
        if(node->quantity!=0){
            cout<<"Deleting: "<<node->title<<endl;
            delete node;
        }
    }
    else return;
}

void MovieTree::printMovieInventory(MovieNode * node){
    if(node->leftChild != NULL){
        printMovieInventory(node->leftChild);
    }
    cout<<"Movie: "<<node->title<<" "<<node->quantity<<endl;
    if(node->rightChild != NULL){
        printMovieInventory(node->rightChild);
    }
}

int MovieTree::countMovieNodes(MovieNode *node){
    if(node == NULL){
        return 0;
    }
    else{
        return countMovieNodes(node->leftChild) + countMovieNodes(node->rightChild) + 1;
    }
}

MovieNode* MovieTree::search(std::string title){
    MovieNode *node=root;
    while(node!=NULL){
        if(node->title.compare(title)>0){
            node=node->leftChild;
        }
        else if(node->title.compare(title)<0){
            node=node->rightChild;
        }
        else{
            return node;
        }
    }
    return NULL;
}

MovieNode* MovieTree::treeMinimum(MovieNode *node){
    while(node->leftChild != NULL){
        node = node->leftChild;
    }
    return node;
}

void MovieTree::buildLogins(){
    string users[]= {"Master", "Maintenance"};
    string passwords[]={"Master", "Maintenance pass"};
    User* current=head;
    int i = 1;
    while(i < 2){
        User *temp = new User;
        temp->username = users[i];
        temp->pass = passwords[i];
        temp->pos = 0;
        temp->next = NULL;
        current->next = temp;
        current = current->next;
        i++;
    }
    User *temp = head;

    ofstream myfile("Users.txt");
    if(myfile.is_open()){
        while(temp!=NULL){
            myfile << temp->username << "; " << temp->pass << "; " << temp->pos;
            temp=temp->next;
            myfile << char(13) << endl;
        }
        myfile.close();
    }
    else{
        cout << "Unable to open file" << endl;
    }
}

bool MovieTree::check(std::string username, std::string pass){
    User* temp=head;
    bool found = false;
    while(!found & temp!=NULL){
        if(temp->username==username and temp->pass==pass){
            return true;
        }
        else{
            temp=temp->next;
        }
    }
    return false;
}

void MovieTree::addUser(std::string username, std::string pass){
    User* test = head;
    User* temp=new User;
    User* New=head;
    temp->username=username;
    temp->pass=pass;
    temp->pos=0;
    while(New->next!=NULL){
        New=New->next;
    }
    New->next=temp;
    temp->next=NULL;
    std::ofstream out;
    out.open("Users.txt", std::ios::app);
    out << temp->username << "; " << temp->pass << "; " << temp->pos;
    out << char(13) << endl;

    while(test!= NULL){
        cout << test->username << test->pass << endl;
        test=test->next;
    }
}
