#include <iostream>
#include <stack>
#include <string>

using namespace std;

struct Node {
    int data;
    string name, nim, complaint;
    Node* next;
    Node(int d, string n, string nm, string c) : data(d), name(n), nim(nm), complaint(c), next(NULL) {}
};

class LinkedList {
    Node* head;
public:
    LinkedList() : head(NULL) {}
    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void enqueue(int data, const string& name, const string& nim, const string& complaint) {
        Node* newNode = new Node(data, name, nim, complaint);
        if (!head) head = newNode;
        else {
            Node* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newNode;
        }
    }
    void dequeue() {
        if (!head) {
            cout << "Antrian kosong!" << endl;
            return;
        }
        Node* temp = head;
        head = head->next;
        cout << "Pasien dengan ID " << temp->data << ", Nama: " << temp->name 
             << ", NIM: " << temp->nim << ", Keluhan: " << temp->complaint << " telah dilayani." << endl;
        delete temp;
    }
    void display() const {
        if (!head) {
            cout << "Antrian kosong!" << endl;
            return;
        }
        for (Node* temp = head; temp; temp = temp->next)
            cout << "ID: " << temp->data << ", Nama: " << temp->name 
                 << ", NIM: " << temp->nim << ", Keluhan: " << temp->complaint << endl;
    }
    bool isEmpty() const { return !head; }
    Node* front() const { return head; }
};

struct HistoryNode {
    int data;
    string name, nim, complaint;
};

int main() {
    LinkedList queue;
    stack<HistoryNode> history;
    int choice, data;
    string name, nim, complaint;

    while (true) {
        cout << "1. Tambah Pasien ke Antrian\n2. Layani Pasien\n3. Tampilkan Antrian\n4. Tampilkan History\n5. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "Masukkan ID Pasien: ";
            cin >> data;
            cin.ignore();
            cout << "Masukkan Nama Pasien: ";
            getline(cin, name);
            cout << "Masukkan NIM Pasien: ";
            getline(cin, nim);
            cout << "Masukkan Keluhan Pasien: ";
            getline(cin, complaint);
            queue.enqueue(data, name, nim, complaint);
        } else if (choice == 2) {
            if (queue.isEmpty()) {
                cout << "Antrian kosong!" << endl;
            } else {
                Node* front = queue.front();
                history.push({front->data, front->name, front->nim, front->complaint});
                queue.dequeue();
            }
        } else if (choice == 3) {
            queue.display();
        } else if (choice == 4) {
            if (history.empty()) {
                cout << "History kosong!" << endl;
            } else {
                cout << "History antrian yang telah dilayani: ";
                stack<HistoryNode> temp = history;
                while (!temp.empty()) {
                    HistoryNode histNode = temp.top();
                    cout << "\nID: " << histNode.data << ", Nama: " << histNode.name 
                         << ", NIM: " << histNode.nim << ", Keluhan: " << histNode.complaint;
                    temp.pop();
                }
                cout << endl;
            }
        } else if (choice == 5) {
            cout << "Program selesai." << endl;
            break;
        } else {
            cout << "Opsi tidak valid!" << endl;
        }
    }

    return 0;
}
