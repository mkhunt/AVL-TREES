// Wordlist.h

#pragma once

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Miloni Hareshbhai Khunt
// St.# : 301570476
// Email: mhk21@sfu.ca
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

class Wordlist : public Wordlist_base
{
    //
    // Use this Node to implement the singly-linked list for the word list. You
    // can *add* extra variables/methods/features to this struct if you like,
    // but you must keep its name the same, and also keep the word, count, and
    // next variables as defined.
    //
    struct Node
    {
        string word;
        int count;
        Node *next;
    };
    public:
    Node* head;
   
    Wordlist()
    {
        head = NULL;
    }

    Wordlist(const string &filename) :Wordlist()
    {
        // ofstream fout("ExampleOutputFile.txt", ios::app);
        ifstream file(filename,ios::app);
        string word;
        while(!file.eof())
        {
            file>>word;
            add_word(word);
        }

    }
    ~Wordlist() 
    {
        Node *temp;
        while(head != NULL)
        {
            temp = head;
            head = head->next;
            delete temp;
        }
    }

int get_count(const string &w) const override
{
    Node *current = head;
    int count=0;
    while(current != NULL)
    {
        if(current->word == w)
        {
             count++;
        }
        current = current->next;
    }

    return count;
}

bool contains(const string &w) 
    {
        return get_count(w) > 0;
    }

 int num_different_words() const override
{
    Node* current = head;
     int count = 0;
        while (current != nullptr)
        {
            count ++;
            current = current->next;
        }
        return count;
}

int total_words() const override
{
    Node *current = head;
    int count = 0;
    while(current != NULL)
    {
        count += current->count;
        current = current->next;
    }
    return count;
 }

bool is_sorted() const override
    {

        Node* current = head;
        bool flag = false;
        if(head == NULL || head->next == NULL)
            flag = true;
        else       
        {
             while(current->next != NULL)
            {
                if(current->next->word < current->word)
                    flag = false;

                current = current->next;   
            }
            flag = true;
        }    
                     
        return flag;
    }

string most_frequent() const override
{
    Node* current = head;
    int mostFrequent = head->count;                 // assigning first node as most frequent 
    string mostFrequentWord = head->word;

    while (current != NULL)
    {
        if (current->count > mostFrequent)
        {
            mostFrequent = current->count;          // if we find node greater than the first node we would change it
            mostFrequentWord = current->word;
        }
        current = current->next;
    }

    string result = mostFrequentWord + " " + to_string(mostFrequent);

    return result;
}

int num_singletons() const override
{  
    Node *temp = head;
    int count = 0;
        while(temp != NULL)
        {
            if(temp->count == 1)     // if count of word is one we will count++ else traverse the loop
            {
                count++;
            }
            temp = temp->next;
        }
    return count;
 } 

void add_word(const string& w) override
{
    Node* current = head;
    Node* previous = NULL;

    Node* newNode = new Node;
    newNode->word = w;
    newNode->count = 1;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode; // when we add the first element to the linked list
        return; 
    }

    while (current != NULL) 
    {
        if (current->word == w) 
        {
            current->count += 1;   // incrementing it when it is same we are creating new node but not adding it  
            delete newNode;         // so we need to delete it.
            return;
        } 
        else if (current->word < w) 
        {
            previous = current;                 // searching for correct location 
            current = current->next;
        } 
        else 
        {
            break; // here we got correct location where we can add the node
        }
    }

    if (previous == NULL) 
    {
        newNode->next = head;             // Insert at the beginning of the list
        head = newNode;
    } 
    else 
    {
        previous->next = newNode;      // inserting it in between two nodes
        newNode->next = current;
    }
    if (current == NULL) 
    {
        previous->next = newNode;       // When we reachat the end of list and word needs to be inserted
        newNode->next = NULL;           
    }
}

void print_words() const override
{
    Node* current = head;
    int i=1;
    while(current != NULL)
    {
        //{"This", 1}
        cout<< i++ <<". "<<"{"<<current->word <<", "<< current->count<<"}"<<endl;
        current= current->next;
    }
    return ;
}

void print_stats()
{
    cout << "Number of different words: " << num_different_words() << endl;
    cout << "    Total number of words: " << total_words() << endl;
    cout << "       Most frequent word: " << most_frequent() << endl;
    cout << "     Number of singletons: " << num_singletons()
        << setprecision(0) << fixed
        << " (" << 100.0 * num_singletons() / num_different_words() << "%)"
        << endl;
}
    //
    // ... your code goes here ...
    //

    //
    // ... you can write helper methods if you need them ...
    //

    //
    // ... write a default constructor that creates an empty Wordlist ...
    //

}; // class Wordlist

//
// ... you can write helper functions here (or before Wordlist) if you need them
// ...
//

//
// ... write functions to test every method of Wordlist ...
//
