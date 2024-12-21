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

struct HashTable {
    vector<node*> table;
    int size;

    HashTable(int s) : size(s) {
        table.resize(s, nullptr);
    }
};

int tableSize = 100;
node *root = nullptr;
char choice, kembali;

//Fungsi-Fungsi untuk Hash Table
int hashFunction(int id, int tableSize);
void insertToHashTable(HashTable& table, node* event);
void deleteFromHashTable(HashTable& table, int id);
vector<node*> searchByMonth(HashTable& table, int month);
void displayHashTable(HashTable& table);
void displaySearchResults(const vector<node*>& events);

void history();
void insertHistory(node *& root, Event dataEvent);
void historyInOrder(node* root);
void historyPostOrder(node* root);
void historyPreOrder(node* root);


int main() {
    do
    {
        system("cls");
        cout << "Menu\n";
        cout << "[1] Tambah jadwal acara\n";
        cout << "[2] Tampilkan jadwal acara\n";
        cout << "[3] Cari jadwal acara\n";
        cout << "[4] Riwayat jadwal acara\n";
        cout << "[5] Keluar\n";
        cout << "Pilih menu > "; cin >> choice;

        switch (choice)
        {
        case '1':
            system("cls");
            
            break;
        case '2':
            system("cls");

            break;
        case '3':
            system("cls");

            break;
        case '4':
            system("cls");
            history();
            break;
        case '5':
            cout << "Terima kasih";
            exit(0);
            break;
        default:
            cout << "Pilihan menu tidak tersedia";
            break;
        }
        cout << "\n\nKembali ke menu utama? (y/n) > "; cin >> kembali;
    } while (kembali == 'y');
    
    
}

int hashFunction(int id, int tableSize) {
    return id % tableSize;
}

void insertToHashTable(HashTable& table, node* event) {
    int index = hashFunction(event->info.id, table.size);
    event->right = table.table[index];
    table.table[index] = event;
    cout << "Event dengan ID " << event->info.id << " berhasil ditambahkan ke hash table.\n";
}

void deleteFromHashTable(HashTable& table, int id) {
    int index = hashFunction(id, table.size);
    node* current = table.table[index];
    node* prev = nullptr;

    while (current != nullptr) {
        if (current->info.id == id) {
            if (prev == nullptr) {
                table.table[index] = current->right;
            } else {
                prev->right = current->right;
            }
            cout << "Event dengan ID " << id << " berhasil dihapus dari hash table.\n";
            delete current;
            return;
        }
        prev = current;
        current = current->right;
    }
    cout << "Event dengan ID " << id << " tidak ditemukan di hash table.\n";
}

vector<node*> searchByMonth(HashTable& table, int month) {
    vector<node*> result;
    for (int i = 0; i < table.size; i++) {
        node* current = table.table[i];
        while (current != nullptr) {
            int eventMonth = stoi(current->info.date.substr(3, 2));
            if (eventMonth == month) {
                result.push_back(current);
            }
            current = current->right;
        }
    }
    return result;
}

void displayHashTable(HashTable& table) {
    for (int i = 0; i < table.size; i++) {
        cout << "Index " << i << ": ";
        node* current = table.table[i];
        while (current != nullptr) {
            cout << "[ID: " << current->info.id << ", Name: " << current->info.name << ", Date: " << current->info.date << "] -> ";
            current = current->right;
        }
        cout << "nullptr\n";
    }
}

void displaySearchResults(const vector<node*>& events) {
    if (events.empty()) {
        cout << "Tidak ada acara yang ditemukan untuk bulan yang diberikan.\n";
        return;
    }
    for (const auto& event : events) {
        cout << "[ID: " << event->info.id << ", Name: " << event->info.name << ", Date: " << event->info.date << "]\n";
    }
}


void history(){
    do
    {   
        cout << "History berdasarkan";
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
            cout << "Pilihan menu tidak tersedia";
            break;
        }
        cout << "\n\nKembali ke menu history? (y/n) > "; cin >> kembali;
    } while (kembali == 'y');
    
    
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