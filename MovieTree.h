#ifndef MOVIETREE_H
#define MOVIETREE_H
#include <iostream>

struct User{
    std::string username;
    std::string pass;
    int pos;
    User *next;
};

struct MovieNode{
    int ranking;
    std::string title;
    int year;
    int quantity;
    MovieNode *parent;
    MovieNode *leftChild;
    MovieNode *rightChild;

    MovieNode(){};

    MovieNode(int in_ranking, std::string in_title, int in_year, int in_quantity)
    {
        ranking = in_ranking;
        title = in_title;
        year = in_year;
        quantity = in_quantity;
        parent = NULL;
        leftChild = NULL;
        rightChild = NULL;
    }
};

class MovieTree
{

    public:
        MovieTree();
        ~MovieTree();
        void printMovieInventory();
        int countMovieNodes();
        void deleteMovieNode(std::string title);
        void addMovieNode(int ranking, std::string title, int releaseYear, int quantity);
        void findMovie(std::string title);
        void rentMovie(std::string title, std::string username);

        void buildLogins();
        void addUser(std::string, std::string);
        void pastMovies();
        void addMovie(std::string);
        void printMovies();
        bool check(std::string, std::string);

    protected:

    private:
        void DeleteAll(MovieNode * node); //use this for the post-order traversal deletion of the tree
        void printMovieInventory(MovieNode * node);
        int countMovieNodes(MovieNode *node);
        MovieNode* search(std::string title);
        MovieNode* treeMinimum(MovieNode *node);
        MovieNode *root;
        User* head;
        User* tail;
};

#endif // MOVIETREE_H
