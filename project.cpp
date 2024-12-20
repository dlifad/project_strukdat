#include <bits/stdc++.h>
using namespace std;

struct Event {
    int id;
    string name;
    string description;
    string date;
};

struct node
{
    Event info;
    node *left;
    node *right;
};

node *root = nullptr;
char choice;

void history();
void insertHistory(node *& root, Event dataEvent);
void historyInOrder(node* root);
void historyPostOrder(node* root);
void historyPreOrder(node* root);

int main() {
    history();
}

void history(){
    cout << "Berdasarkan";
    cout << "\n[1] In-Order";
    cout << "\n[2] Post-Order";
    cout << "\n[3] Pre-Order";
    cout << "\nPilih menu > "; cin >> choice;

    switch (choice)
    {
    case '1':
        system("cls");
        cout << "History jadwal (In-Order)\n\n";
        historyInOrder(root);
        break;
    case '2':
        system("cls");
        cout << "History jadwal (Post-Order)\n\n";
        historyPostOrder(root);
        break;
    case '3':
        system("cls");
        cout << "History jadwal (Pre-Order)\n\n";
        historyPreOrder(root);
        break;
    
    default:
        break;
    }
}

void insertHistory(node *& root, Event dataEvent) {
    if(root == nullptr) {
        root = new node;
        root->info = dataEvent;
        root->left = nullptr;
        root->right = nullptr;
    } else if (dataEvent.id < root->info.id) {
        insertHistory(root->left, dataEvent);
    } else {
        insertHistory(root->right, dataEvent);
    }
}

void historyInOrder(node* root){
    if (root == nullptr) {
        return;
    }

    historyInOrder(root->left);

    cout << "ID: " << root->info.id << ", Name: " << root->info.name <<
    ", Description: " << root->info.description << ", Date: " << root->info.date << endl;

    historyInOrder(root->right);
}

void historyPostOrder(node* root){
    if(root == nullptr) {
        return;
    }

    historyPostOrder(root->left);

    historyPostOrder(root->right);

    cout << "ID: " << root->info.id << ", Name: " << root->info.name <<
    ", Description: " << root->info.description << ", Date: " << root->info.date << endl;
}

void historyPreOrder(node* root){
    if(root == nullptr) {
        return;
    }

    cout << "ID: " << root->info.id << ", Name: " << root->info.name <<
    ", Description: " << root->info.description << ", Date: " << root->info.date << endl;

     historyPostOrder(root->left);

    historyPostOrder(root->right);
}