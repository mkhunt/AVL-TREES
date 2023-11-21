// Wordlist.h

#pragma once

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : <Ayush Sutariya
// St.# : <301548537>
// Email: <aps20@sfu.ca>
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

//
// Do not use any other #includes
//
#include "Wordlist_base.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

//
// IMPORTANT: no global variables are permitted in this file!
//
// It is okay to define helper functions defined outside the class.
//

class Wordlist : public Wordlist_base
{
    //
    // Use this Node to implement an AVL tree for the word list. You can *add*
    // extra variables/methods/features to this struct if you like, but you must
    // keep its name the same, and also keep the word, count, left, and right
    // variables as defined.
    //
    struct Node
    {
        string word;
        int count;
        Node *left;
        Node *right;
        int height;

        Node (string s) : word(s),left(nullptr), right(nullptr), count(1){}
    };

    Node *root = nullptr;

    void clear(Node* current){
        if(current){
            clear(current -> left);
            clear(current->right);
            delete current;
        }
    }

    public:

    Wordlist(){};

    Wordlist(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string word;
        while (file >> word) {
            add_word(word);
        }

        file.close();
    }

    ~Wordlist() {
        clear(root);
    };

    int get_count(const string &w)const override{
        Node* current = root;
        while (current != nullptr)
        {
            if(current->word == w){
                return current->count;
            } else if(w < current->word){
                current = current->left;
            } else{
                current = current->right;
            }
        }
        return 0;    
    }

    bool contains(const string &w)
    {
        return get_count(w) > 0;
    }

    int inOrder_Transversal_num_different_words(Node* root)const{
        Node* current = root;
        if(current == nullptr){
            return 0;
        }

        int count = 0;
        count += inOrder_Transversal_num_different_words(current->left);
        count++;
        count += inOrder_Transversal_num_different_words(current->right);

        return count;
    }  

    int num_different_words()const override{
        return inOrder_Transversal_num_different_words(root);
    }

    int inOrder_Transversal_Total_Words(Node* root)const{
        if(root == nullptr){
            return 0;
        } 
        int total = 0;
        total += inOrder_Transversal_Total_Words(root->left);
        total += root->count;
        total += inOrder_Transversal_Total_Words(root->right);

        return total;
    }

    int total_words()const override{
        Node* current = root;
        return inOrder_Transversal_Total_Words(current);
    }

    int In_Order_Transversal_singleton(Node* root)const{
        if(root == nullptr){
            return 0;
        }
        int count = 0;
        count += In_Order_Transversal_singleton(root->left);
        if(root->count == 1){
            count++;
        }
        count += In_Order_Transversal_singleton(root->right);

        return count;
    }

    int num_singletons()const override{
        Node* current = root;
        int singleton =  In_Order_Transversal_singleton(root);
        return singleton;
    }

    bool is_valid_avl(Node* current, Node* prev)const{
        if(current == nullptr){
            return true;
        }
        bool left = is_valid_avl(current->left, prev);
        if(prev != nullptr && current->word < prev->word){
            return false;
        }
        prev = current;
        bool right = is_valid_avl(current->right, prev);
        if(left == true && right == true){
            return true;
        } else{
            return false;
        }
    }

    bool is_sorted()const override{
        Node* prev = nullptr;
        return is_valid_avl(root, prev);
    }

    string findMostFrequent(Node* current, string& mostFrequent, int& Max_count)const{
        if(current){
            findMostFrequent(current->left, mostFrequent, Max_count);

            if(current->count > Max_count){
                Max_count = current->count;
                mostFrequent = current->word;
            }

            findMostFrequent(current->right, mostFrequent, Max_count);
        }
        string string_word = to_string(Max_count);
        string total = mostFrequent + " "+string_word;
        return total; 
    }

    string most_frequent()const override{
        string mostFrequent;
        // cout << "most_freqi=uent_called"; 
        int Max_count;
        return findMostFrequent(root,mostFrequent,Max_count);
    }

    int height(Node* root){
        if(root == nullptr){
            return 0;
        }

        return root->height;
    }

    int max(int a, int b)
{
    return (a > b)? a : b;
}

    int get_balance(Node* root){
        if(root == nullptr){
            return 0;
        }
        return height(root->left) - height(root->right);
    }

Node *rotateRight(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;
 
    // Return new root
    return x;
}
 

Node *rotateLeft(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    // Update heights
    x->height = max(height(x->left),   
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;
 
    // Return new root
    return y;
}
 

     Node* insert(Node* current,const string& w){
        if (current==nullptr) {
            return (new Node(w));
        }
        
        if(w < current->word){
            current->left = insert(current->left, w);
        } else if(w > current->word){
            current->right = insert(current->right, w);
        } else{
            current->count++;
            return current;
        }

        current->height = 1 + max(height(current->left),height(current->right));

        int balance = get_balance(current);

        if(balance > 1 && w < current->left->word){
            return rotateRight(current);
        }  if(balance < -1 && w > current->right->word){
            return rotateLeft(current);
        }  if(balance > 1 && w > current->left->word){
            current->left = rotateLeft(current->left);
            return rotateRight(current);
        } if(balance < -1 && w < current->right->word){
            current->right = rotateRight(current->right);
            return rotateLeft(current);
        }

        return current;
     }

    void add_word(const string &w){
        root = insert(root, w);
    }

        void print_stats() const
    {
        cout << "Number of different words: " << num_different_words() << endl;
        cout << "    Total number of words: " << total_words() << endl;
        cout << "       Most frequent word: " << most_frequent() << endl;
        cout << "     Number of singletons: " << num_singletons()
             << setprecision(0) << fixed
             << " (" << 100.0 * num_singletons() / num_different_words() << "%)"
             << endl;
    }

    void inOrderTraversalUtil(Node* root)const {
        if (root == nullptr) {
            return;
        }
        inOrderTraversalUtil(root->left);
        cout << root->word << ": " << root->count << endl;
        inOrderTraversalUtil(root->right);
    }

    void print_words()const override{
        inOrderTraversalUtil(root);
    }

    //
    // IMPORTANT: root is the only variable that can be defined in this class.
    // It should point to the top node of your AVL tree. When root == nullptr,
    // the tree is empty.
    //
    // No variables other than root are permitted!
    //


}; // class Wordlist

//
// Make sure to thoroughly test your code as you go!
//
