#include <bits/stdc++.h>
#include <conio.h>
using namespace std;

struct Event {
    int id;
    string name;
    string description;
    string date;
};

struct node {
    Event info;
    node *left;
    node *right;
};

struct HashTable {
    vector<node *> table;
    int size;

    HashTable(int s) : size(s) {
        table.resize(s, nullptr);
    }
};

HashTable table(20);
node *root = nullptr;
char choice, kembali;

// Fungsi-Fungsi untuk Hash Table
int hashFunction(int id, int tableSize);
void insertToHashTable(HashTable &table, node *event);
void deleteFromHashTable(HashTable &table, int id);
vector<node *> searchByMonth(HashTable &table, int month);
void displayHashTable(HashTable &table);
void displaySearchResults(const vector<node *> &events);

void history();
void insertHistory(node *&root, Event dataEvent);
void historyInOrder(node *root);
void historyPostOrder(node *root);
void historyPreOrder(node *root);

void insertEvent();
void deleteEvent();
void searchEvent();

void title(string text);
bool isValidDate(string &date);
bool isLeapYear(int year);

int main() {
    do {
        title("MENU UTAMA");
        cout << "[1] Tambah Acara\n";
        cout << "[2] Hapus Acara\n";
        cout << "[3] Tampilkan Jadwal\n";
        cout << "[4] Cari Acara\n";
        cout << "[5] Riwayat Acara\n";
        cout << "[6] Keluar\n";
        cout << "Pilih menu > ";
        cin >> choice;

        switch (choice) {
        case '1':
            insertEvent();
            break;
        case '2':
            deleteEvent();
            break;
        case '3':
            displayHashTable(table);
            break;
        case '4':
            searchEvent();
            break;
        case '5':
            history();
            break;
        case '6':
            cout << "Terima kasih\n";
            return 0; 
        default:
            cout << "Pilihan menu tidak tersedia\n";
            break;
        }
        cout << "\n\nKembali ke menu utama? (y/n) > ";
        cin >> kembali;
    } while (kembali == 'y');
}

void insertEvent() {
    int eventID;
    string eventName, eventDesc, eventDate;
    do {
        title("TAMBAH ACARA");
        cout << "ID" << endl << "-> ";
        cin >> eventID;
        cin.ignore();
        cout << "-" << setfill('-') << setw(38) << "-" << endl;
        cout << "Nama Acara" << endl << "-> ";
        getline(cin, eventName);
        cout << "-" << setfill('-') << setw(38) << "-" << endl;
        cout << "Deskripsi Acara" << endl << "-> ";
        getline(cin, eventDesc);
        cout << "-" << setfill('-') << setw(38) << "-" << endl;
        cout << "Tanggal Acara (dd/mm/yy)" << endl << "-> ";
        getline(cin, eventDate);

        if (!isValidDate(eventDate))  {
            cout << "\nFormat tanggal tidak valid.";
            cout << "\nSilahkan masukkan data ulang.";
            _getch();
        }
    } while (!isValidDate(eventDate));

    
    cout << "-" << setfill('-') << setw(38) << "-" << endl << endl;

    node *event = new node;
    event->info.id = eventID;
    event->info.name = eventName;
    event->info.description = eventDesc;
    event->info.date = eventDate;
    event->left = nullptr;
    event->right = nullptr;

    insertToHashTable(table, event);
}

void deleteEvent() {
    int eventID;
    title("HAPUS ACARA");
    cout << "ID" << endl << "-> ";
    cin >> eventID;
    deleteFromHashTable(table, eventID);
}

void searchEvent() {
    vector<node *> events;
    int month;
    do {
        title("CARI ACARA");
        cout << "[1] Berdasarkan Bulan" << endl;
        cout << "[2] Berdasarkan Nama Acara" << endl;
        cout << "Pilih menu > ";
        cin >> choice;
        switch (choice) {
        case '1':
            title("BERDASARKAN BULAN");
            cout << "Bulan (dalam angka)" << endl << "-> ";
            cin >> month;
            events = searchByMonth(table, month);
            displaySearchResults(events);
            break;
        case '2':
            system("cls");
            title("BERDASARKAN ACARA");
            // Implementasi pencarian berdasarkan nama acara perlu ditambahkan
            break;
        default:
            cout << "Pilihan menu tidak tersedia" << endl;
            break;
        }
        cout << "\n\nKembali ke menu history? (y/n) > ";
        cin >> kembali;
    } while (kembali == 'y');
}

int hashFunction(int id, int tableSize) {
    return id % tableSize;
}

void insertToHashTable(HashTable &table, node *event) {
    int index = hashFunction(event->info.id, table.size);
    event->right = table.table[index];
    table.table[index] = event;
    cout << "Acara dengan ID " << event->info.id << " berhasil ditambahkan ke jadwal.\n";
}

void deleteFromHashTable(HashTable &table, int id) {
    int index = hashFunction(id, table.size);
    node *current = table.table[index];
    node *prev = nullptr;

    while (current != nullptr) {
        if (current->info.id == id) {
            insertHistory(root, current->info);
            if (prev == nullptr) {
                table.table[index] = current->right;
            } else {
                prev->right = current->right;
            }
            cout << "Acara dengan ID " << id << " berhasil dihapus.\n";
            delete current;
            return;
        }
        prev = current;
        current = current->right;
    }
    cout << "Event dengan ID " << id << " tidak ditemukan di data jadwal.\n";
}

vector<node *> searchByMonth(HashTable &table, int month) {
    vector<node *> result;
    for (int i = 0; i < table.size; i++) {
        node *current = table.table[i];
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

void displayHashTable(HashTable &table) {
    for (int i = 0; i < table.size; i++) {
        node *current = table.table[i];
        while (current != nullptr) {
            cout << "ID: " << current->info.id << ", Name: " << current->info.name << ", Date: " << current->info.date << endl;
            current = current->right;
        }
    }
}

void displaySearchResults(const vector<node *> &events) {
    if (events.empty()) {
        cout << "Tidak ada acara yang ditemukan untuk bulan yang diberikan.\n";
        return;
    }
    for (const auto &event : events) {
        cout << "[ID: " << event->info.id << ", Name: " << event->info.name << ", Date: " << event->info.date << "]\n";
    }
}

void history() {
    do {
        title("HISTORY");
        cout << "Urutkan berdasarkan";
        cout << "\n[1] In-Order";
        cout << "\n[2] Post-Order";
        cout << "\n[3] Pre-Order";
        cout << "\nPilih menu > ";
        cin >> choice;

        switch (choice) {
        case '1':
            system("cls");
            title("History jadwal (In-Order)");
            historyInOrder(root);
            break;
        case '2':
            system("cls");
            title("History jadwal (Post-Order)");
            historyPostOrder(root);
            break;
        case '3':
            system("cls");
            title("History jadwal (Pre-Order)");
            historyPreOrder(root);
            break;
        default:
 cout << "Pilihan menu tidak tersedia" << endl;
            break;
        }
        cout << "\n\nKembali ke menu history? (y/n) > ";
        cin >> kembali;
    } while (kembali == 'y');
}

void insertHistory(node *&root, Event dataEvent) {
    if (root == nullptr) {
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

void historyInOrder(node *root) {
    if (root == nullptr) {
        return;
    }

    historyInOrder(root->left);

    cout << "ID: " << root->info.id << ", Name: " << root->info.name << ", Description: " << root->info.description << ", Date: " << root->info.date << endl;

    historyInOrder(root->right);
}

void historyPostOrder(node *root) {
    if (root == nullptr) {
        return;
    }

    historyPostOrder(root->left);

    historyPostOrder(root->right);

    cout << "ID: " << root->info.id << ", Name: " << root->info.name << ", Description: " << root->info.description << ", Date: " << root->info.date << endl;
}

void historyPreOrder(node *root) {
    if (root == nullptr) {
        return;
    }

    cout << "ID: " << root->info.id << ", Name: " << root->info.name << ", Description: " << root->info.description << ", Date: " << root->info.date << endl;

    historyPreOrder(root->left); 
    historyPreOrder(root->right); 
}

void title(string text) {
	system("cls");
	cout << "=" << setfill('=') << setw(38) << "=" << endl;
	cout << setfill(' ');
	int panjang = (40 - text.length())/2;
	cout << setw(panjang + text.length()) << right << text << endl;
	cout << "=" << setfill('=') << setw(38) << "=" << endl;
	cout << setfill(' ');
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isValidDate(string &date) {
    int day, month, year;

    // Memisahkan string tanggal menjadi hari, bulan, dan tahun
    char delimiter;
    stringstream ss(date);
    ss >> day >> delimiter >> month >> delimiter >> year;

    // Memeriksa format tanggal
    if (delimiter != '/' || ss.fail() || day < 1 || month < 1 || year < 0) {
        return false;
    }

    // Mengubah tahun dua digit menjadi empat digit
    if (year < 100) {
        year += 2000; // Asumsi tahun 00-99 adalah 2000-2099
    }

    // Memeriksa batasan bulan dan hari
    if (month > 12) {
        return false;
    }

    // Jumlah hari dalam setiap bulan
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Memperbaiki jumlah hari untuk bulan Februari jika tahun kabisat
    if (isLeapYear(year)) {
        daysInMonth[2] = 29;
    }

    // Memeriksa apakah hari valid untuk bulan yang diberikan
    return day <= daysInMonth[month];
}