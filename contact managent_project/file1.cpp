#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Contact;
Contact* head = nullptr;

class Contact {
private:
    string name;
    string contact_number;
    string email;
    Contact* next;

public:
    Contact() {
        next = nullptr;
    }

    // Add contact function
    void add_contact() {
        Contact* newContact = new Contact;
        cout << "Enter Name: ";
        getline(cin, newContact->name);
        cout << "Enter Phone: ";
        getline(cin, newContact->contact_number);
        cout << "Enter Email: ";
        getline(cin, newContact->email);

        if (!head || newContact->name < head->name) {
            newContact->next = head;
            head = newContact;
        } else {
            Contact* temp = head;
            while (temp->next && temp->next->name < newContact->name) {
                temp = temp->next;
            }
            newContact->next = temp->next;
            temp->next = newContact;
        }

        save_to_file();
        cout << "Contact added successfully!\n";
    }

    // Search contact
    void search_contact() {
        Contact* temp = head;
        string name;
        cout << "Enter name to search the contact: ";
        getline(cin,name);

        while (temp != nullptr) {
            if (temp->name == name) {
                cout << "Contact found:\n";
                cout << "Name: " << temp->name << endl;
                cout << "Phone: " << temp->contact_number << endl;
                cout << "Email: " << temp->email << endl;
                return;
            }
            temp = temp->next;
        }

        cout << "Contact not found.\n";
    }

    // Update contact
    void update_contact() {
        Contact* temp = head;
        string name;
        cout << "Enter name to update the contact: ";
        getline(cin,name);
        while (temp) {
            if (temp->name == name) {
                cout << "Updating contact for " << name << endl;
                cout << "Enter new Phone: ";
                getline(cin, temp->contact_number);
                cout << "Enter new Email: ";
                getline(cin, temp->email);
                save_to_file();
                cout << "Contact updated successfully!\n";
                return;
            }
            temp = temp->next;
        }

        cout << "Contact not found to update.\n";
    }

    // Display contacts
    void display() {
        if (!head) {
            cout << "No contacts available.\n";
            return;
        }

        Contact* temp = head;
        cout << "Contacts List:\n";
        while (temp) {
            cout << "Name: " << temp->name << endl;
            cout << "Phone: " << temp->contact_number << endl;
            cout << "Email: " << temp->email << endl;
            temp = temp->next;
        }
    }

    // Delete contact
    void delete_contact() {
        if (!head) {
            cout << "No contacts available to delete.\n";
            return;
        }

        string name;
        cout << "Enter the name of the contact to delete: ";
        getline(cin,name);
        cin.ignore();

        if (head->name == name) {
            Contact* temp2 = head;
            head = head->next;
            delete temp2;
            save_to_file();
            cout << "Contact deleted successfully!\n";
            return;
        }

        Contact* temp = head;
        while (temp->next && temp->next->name != name) {
            temp = temp->next;
        }

        if (temp->next) {
            Contact* temp2 = temp->next;
            temp->next = temp->next->next;
            delete temp2;
            save_to_file();
            cout << "Contact deleted successfully!\n";
        } else {
            cout << "Contact not found.\n";
        }
    }

    // Save contacts to file
    void save_to_file() {
        ofstream file("contacts.txt");
        if (file.is_open()) {
            Contact* temp = head;
            while (temp) {
                file << temp->name << "\n";
                file << temp->contact_number << "\n";
                file << temp->email << "\n";
                temp = temp->next;
            }
            file.close();
        }
    }

    // Load contacts from file
    void load_from_file() {
        ifstream file("contacts.txt");
        if (file.is_open()) {
            string name, phone, email;
            while (getline(file, name)) {
                getline(file, phone);
                getline(file, email);
                Contact* newContact = new Contact;
                newContact->name = name;
                newContact->contact_number = phone;
                newContact->email = email;

                if (!head || newContact->name < head->name) {
                    newContact->next = head;
                    head = newContact;
                } else {
                    Contact* temp = head;
                    while (temp->next && temp->next->name < newContact->name) {
                        temp = temp->next;
                    }
                    newContact->next = temp->next;
                    temp->next = newContact;
                }
            }
            file.close();
        }
    }
};

int main() {
    Contact obj;
    obj.load_from_file(); // Load existing contacts from file
    int choice;

    do {
        cout << "\n--- Contact Management System ---\n";
        cout << "1. Add Contact\n";
        cout << "2. Display Contacts\n";
        cout << "3. Search Contact\n";
        cout << "4. Update Contact\n";
        cout << "5. Delete Contact\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                obj.add_contact();
                break;
            case 2:
                obj.display();
                break;
            case 3:
                obj.search_contact();
                break;
            case 4:
                obj.update_contact();
                break;
            case 5:
                obj.delete_contact();
                break;
            case 6:
                cout << "Exiting the Contact Management System. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Please enter a valid option.\n";
        }
    } while (choice != 6);

    return 0;
}
