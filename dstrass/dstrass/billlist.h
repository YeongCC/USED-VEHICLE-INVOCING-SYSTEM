#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


struct Billing {
    int id;
    double price;
    string remarkid;
    string customer;
    Billing* next;
};

struct BillingtList {
    Billing* head;
    int size;
    int id;
    BillingtList() {
        this->size = 0;
        this->head = nullptr;
    }

    void insertAtLast(double price,string remarkid,string customer)
    {
        Billing* newBill = new Billing;
        newBill->id = size;
        newBill->price = price;
        newBill->remarkid = remarkid;
        newBill->customer = customer;
        newBill->next = head;
        newBill->next = nullptr;

        if (head == nullptr) {
            head = newBill;
        }
        else {
            Billing* last = head;
            while (last->next != nullptr) {
                last = last->next;
            }
            last->next = newBill;
        }
        size++;
        id++;
    }

    bool removeBillById(int id) {
        if (head == nullptr) return false;
        Billing* current = head, * prev = nullptr;
        while (current != nullptr && current->id != id) {
            prev = current;
            current = current->next;
        }
        if (current == nullptr) return false;
        if (prev == nullptr) head = current->next;
        else prev->next = current->next;
        delete current;
        size = size - 1;
        return true;
    }

    //linear search
    Billing* searchReportByCarId(string billingid) {
        Billing* current = head;
        while (current != nullptr) {
            if (current->id == stoi(billingid)) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    //selection sort
    void selectionSortByPrice() {
        Billing* current = head;
        Billing* minNode = NULL;
        Billing* prev = NULL;

        while (current != NULL) {
            // Find the node with the minimum price
            minNode = current;
            for (Billing* temp = current->next; temp != NULL; temp = temp->next) {
                if (temp->price < minNode->price) {
                    minNode = temp;
                }
            }
            // Swap the current node with the node with the minimum price
            if (current != minNode) {
                double tempPrice = current->price;
                current->price = minNode->price;
                minNode->price = tempPrice;
            }

            prev = current;
            current = current->next;
        }

        Billing* curr = head;
        cout << "----------------------------------------------------------------------" << endl;
        cout << "			 Billing Report		" << endl;
        cout << "----------------------------------------------------------------------" << endl;
        if (size == 0) {
            cout << "----------------------------------------------------------------------" << endl;
            cout << "			 No Billing Report		" << endl;
            cout << "----------------------------------------------------------------------" << endl;
        }
        else {
            double totalamount = 0;
            while (curr != NULL) {
                cout << "Price Amount: £" << curr->price << endl;
                cout << "----------------------------------" << endl;
                cout << "|| Id: " << curr->id << " || Customer Name: " << curr->customer << " || Price Amount: £" << curr->price << " ||" << endl;
                cout << "----------------------------------------------------------------------" << endl;
                totalamount += curr->price;
                curr = curr->next;
            }
            cout << "Total Amount: £" << totalamount << endl;
            cout << "----------------------------------------------------------------------" << endl;
        }

    }

};