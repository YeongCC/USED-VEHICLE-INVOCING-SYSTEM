#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <time.h>
using namespace std;


struct Report {
    int id;
    int carid;
    string customer;
    string remarkid;
    string title;
    double price;
    int registration_date;
    int mileage;
    string fuel_type;
    string transmission;
    string engine_size;
    string doors;
    string colour;
    string body_type;
    string url;
    string sale_date;
    int report_create_time;
    Report* next;
}; 

struct ReportList {
    Report* head;
    int size;
    int id;
    ReportList() {
        this->size = 0;
        this->head = nullptr;
    }

    void insertAtLast(string customer,string remarkid, int carid ,string title, double price, int registration_date, int mileage, string fuel_type, string transmission, string engine_size, string doors, string colour, string body_type, string url, string sale_date)
    {
        auto now = chrono::system_clock::now();
        time_t now_time = chrono::system_clock::to_time_t(now);
        auto t = gmtime(&now_time);
        t->tm_hour += 8;
        int seconds = mktime(t);

        Report* newReport = new Report;
        newReport->id = id;
        newReport->carid = carid;
        newReport->customer = customer;
        newReport->remarkid = remarkid;
        newReport->title = title;
        newReport->price = price;
        newReport->registration_date = registration_date;
        newReport->mileage = mileage;
        newReport->fuel_type = fuel_type;
        newReport->transmission = transmission;
        newReport->engine_size = engine_size;
        newReport->doors = doors;
        newReport->colour = colour;
        newReport->body_type = body_type;
        newReport->url = url;
        newReport->sale_date = sale_date;
        newReport->report_create_time = seconds;
        newReport->next = head;
        newReport->next = nullptr;

        if (head == nullptr) {
            head = newReport;
        }
        else {
            Report* last = head;
            while (last->next != nullptr) {
                last = last->next;
            }
            last->next = newReport;
        }
        size++;
        id++;
    }

    //linear seearch
    Report* searchReportById(int id) {
        Report* current = head;
        while (current != nullptr) {
            if (current->id == id)
                return current;
            current = current->next;
        }
        return nullptr;
    }

    void viewAllOrder() {
        Report* curr = head;
        cout << "----------------------------------------------------------------------" << endl;
        cout << "			 Order		" << endl;
        cout << "----------------------------------------------------------------------" << endl;
        if (size == 0) {
            cout << "----------------------------------------------------------------------" << endl;
            cout << "			 No Order		" << endl;
            cout << "----------------------------------------------------------------------" << endl;
        }
        else {
            while (curr != nullptr)
            {
                time_t t = curr->report_create_time; // convert to time_t   
                cout << "|| Id: " << curr->id << " || Customer Name: " << curr->customer << " || Created Time: " << asctime(localtime(&t)) << " || Car Id: " << curr->carid << " || Car Name: " << curr->title << " || Mileage: " << curr->mileage << " || Price: £" << curr->price << " || Registration Date: " << curr->registration_date << " || Fuel Type: " << curr->fuel_type << " || Transmission: " << curr->transmission << " || Engine Size: " << curr->engine_size << " || Doors: " << curr->doors << " || Colour: " << curr->colour << " || Body Type: " << curr->body_type << " || URL: " << curr->url << " || Sale Date: " << curr->sale_date << " ||" << endl;
                cout << "----------------------------------------------------------------------" << endl;
                curr = curr->next;
            }
        }
    }

    //linear seearch
    Report* searchOrderByName(string name) {
        Report* current = head;
        while (current != nullptr) {
            if (current->customer == name) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    bool removeOrderById(int id) {
        if (head == nullptr) return false;
        Report* current = head, * prev = nullptr;
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

    //linear seearch
    Report* searchReportById(string reportid) {
        Report* current = head;
        while (current != nullptr) {
            if (current->id == stoi(reportid)) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    //linear seearch
    Report* searchReportByCarId(string carid) {
        Report* current = head;
        while (current != nullptr) {
            if (current->carid == stoi(carid)) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    //selection sort
    void selectionSortByName() {
        Report* current = head;
        Report* minNode = NULL;
        Report* prev = NULL;

        while (current != NULL) {
            // Find the node with the minimum title
            minNode = current;
            for (Report* temp = current->next; temp != NULL; temp = temp->next) {
                if (temp->customer < minNode->customer) {
                    minNode = temp;
                }
            }

            // Swap the current node with the node with the minimum title
            if (current != minNode) {
                string tempTitle = current->customer;
                current->customer = minNode->customer;
                minNode->customer = tempTitle;
            }

            prev = current;
            current = current->next;
        }

        Report* curr = head;
        cout << "----------------------------------------------------------------------" << endl;
        cout << "			 Report		" << endl;
        cout << "----------------------------------------------------------------------" << endl;
        if (size == 0) {
            cout << "----------------------------------------------------------------------" << endl;
            cout << "			 No Report		" << endl;
            cout << "----------------------------------------------------------------------" << endl;
        }
        else {
            while (curr != NULL) {
                time_t t = curr->report_create_time; // convert to time_t   
                cout << "Customer Name: " << curr->customer << endl;
                cout << "----------------------------------" << endl;
                cout << "|| Id: " << curr->id << " || Customer Name: " << curr->customer << " || Created Time: " << asctime(localtime(&t)) << " || Car Id: " << curr->carid << " || Car Name: " << curr->title << " || Mileage: " << curr->mileage << " || Price: £" << curr->price << " || Registration Date: " << curr->registration_date << " || Fuel Type: " << curr->fuel_type << " || Transmission: " << curr->transmission << " || Engine Size: " << curr->engine_size << " || Doors: " << curr->doors << " || Colour: " << curr->colour << " || Body Type: " << curr->body_type << " || URL: " << curr->url << " || Sale Date: " << curr->sale_date << " ||" << endl;
                cout << "----------------------------------------------------------------------" << endl;
                curr = curr->next;
            }
        }
    }

    //selection sort
    void selectionSortByDateTime() {
        Report* current = head;
        Report* minNode = NULL;
        Report* prev = NULL;

        while (current != NULL) {
            // Find the node with the minimum price
            minNode = current;
            for (Report* temp = current->next; temp != NULL; temp = temp->next) {
                if (temp->report_create_time < minNode->report_create_time) {
                    minNode = temp;
                }
            }
            // Swap the current node with the node with the minimum price
            if (current != minNode) {
                double tempPrice = current->report_create_time;
                current->report_create_time = minNode->report_create_time;
                minNode->report_create_time = tempPrice;
            }

            prev = current;
            current = current->next;
        }

        Report* curr = head;
        cout << "----------------------------------------------------------------------" << endl;
        cout << "			 Report		" << endl;
        cout << "----------------------------------------------------------------------" << endl;
        if (size == 0) {
            cout << "----------------------------------------------------------------------" << endl;
            cout << "			 No Report		" << endl;
            cout << "----------------------------------------------------------------------" << endl;
        }
        else {

            while (curr != NULL) {
                time_t t = curr->report_create_time;  
                cout << "Created Time: " << asctime(localtime(&t)) << endl;
                cout << "----------------------------------" << endl;
                cout << "|| Id: " << curr->id << " || Customer Name: " << curr->customer << " || Created Time: " << asctime(localtime(&t)) << " || Car Id: " << curr->carid << " || Car Name: " << curr->title << " || Mileage: " << curr->mileage << " || Price: £" << curr->price << " || Registration Date: " << curr->registration_date << " || Fuel Type: " << curr->fuel_type << " || Transmission: " << curr->transmission << " || Engine Size: " << curr->engine_size << " || Doors: " << curr->doors << " || Colour: " << curr->colour << " || Body Type: " << curr->body_type << " || URL: " << curr->url << " || Sale Date: " << curr->sale_date << " ||" << endl;
                cout << "----------------------------------------------------------------------" << endl;
                curr = curr->next;
            }
        }
    }
};