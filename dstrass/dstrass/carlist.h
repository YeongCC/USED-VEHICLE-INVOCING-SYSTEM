#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


struct Car {
    int id;
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
    Car* next;
};


struct CarList {
    Car* head;
    int size;
    CarList() {
        this->size = 0;
        this->head = nullptr;
    }

    void insertAtLast(string title, double price, int registration_date, int mileage, string fuel_type, string transmission, string engine_size, string doors, string colour, string body_type, string url, string sale_date)
    {
        Car* newCar = new Car;
        newCar->id = size;
        newCar->title = title;
        newCar->price = price;
        newCar->registration_date = registration_date;
        newCar->mileage = mileage;
        newCar->fuel_type = fuel_type;
        newCar->transmission = transmission;
        newCar->engine_size = engine_size;
        newCar->doors = doors;
        newCar->colour = colour;
        newCar->body_type = body_type;
        newCar->url = url;
        newCar->sale_date = sale_date;
        newCar->next = head;
        newCar->next = nullptr;

        if (head == nullptr) {
            head = newCar;
        }
        else {
            Car* last = head;
            while (last->next != nullptr) {
                last = last->next;
            }
            last->next = newCar;
        }
        size++;
    }

    void reinsertAtLast(int id,string title, double price, int registration_date, int mileage, string fuel_type, string transmission, string engine_size, string doors, string colour, string body_type, string url, string sale_date)
    {
        Car* newCar = new Car;
        newCar->id = id;
        newCar->title = title;
        newCar->price = price;
        newCar->registration_date = registration_date;
        newCar->mileage = mileage;
        newCar->fuel_type = fuel_type;
        newCar->transmission = transmission;
        newCar->engine_size = engine_size;
        newCar->doors = doors;
        newCar->colour = colour;
        newCar->body_type = body_type;
        newCar->url = url;
        newCar->sale_date = sale_date;
        newCar->next = head;
        newCar->next = nullptr;

        if (head == nullptr) {
            head = newCar;
        }
        else {
            Car* last = head;
            while (last->next != nullptr) {
                last = last->next;
            }
            last->next = newCar;
        }
        size++;
    }


    void displaysortbyName() {
        int n = size; // number of elements in linked list
        Car* arr = new Car[n];
        Car* temp = head;

        for (int i = 0; i < n; i++) {
            arr[i] = *temp;
            temp = temp->next;
        }

        heapSortName(arr, n);

        cout << "----------------------------------------------------------------------" << endl;
        cout << "			 Car List Sort By Name		" << endl;
        cout << "----------------------------------------------------------------------" << endl;
        if (size == 0) {
            cout << "----------------------------------------------------------------------" << endl;
            cout << "			 No Car		" << endl;
            cout << "----------------------------------------------------------------------" << endl;
        }
        else {
            for (int i = 0; i < n; i++) {
                cout << "Car Name: " << arr[i].title << endl;
                cout << "----------------------------------" << endl;
                cout << "|| Car Id: " << arr[i].id << " || Car Name: " << arr[i].title << " || Price: £" << arr[i].price << " || Registration Date: " << arr[i].registration_date << " || Mileage: " << arr[i].mileage << " || Fuel Type: " << arr[i].fuel_type << " || Transmission: " << arr[i].transmission << " || Engine Size: " << arr[i].engine_size << " || Doors: " << arr[i].doors << " || Colour: " << arr[i].colour << " || Body Type: " << arr[i].body_type << " || URL: " << arr[i].url << " || Sale Date: " << arr[i].sale_date << " ||" << endl;
                cout << "----------------------------------------------------------------------" << endl << endl;
            }
        }
    }

    void displaysortbyMileage() {
        int n = size; 
        Car* arr = new Car[n];
        Car* temp = head;
        for (int i = 0; i < n; i++) {
            arr[i] = *temp;
            temp = temp->next;
        }

        heapSortMileage(arr, n);
        cout << "----------------------------------------------------------------------" << endl;
        cout << "			 Car List Sort By Mileage		" << endl;
        cout << "----------------------------------------------------------------------" << endl;
        if (size == 0) {
            cout << "----------------------------------------------------------------------" << endl;
            cout << "			 No Car		" << endl;
            cout << "----------------------------------------------------------------------" << endl;
        }
        else {
            for (int i = 0; i < n; i++) {
                cout << "Mileage: " << arr[i].mileage << endl;
                cout << "----------------------------------" << endl;
                cout << "|| Car Id: " << arr[i].id << " || Car Name: " << arr[i].title << " || Price: £" << arr[i].price << " || Registration Date: " << arr[i].registration_date << " || Mileage: " << arr[i].mileage << " || Fuel Type: " << arr[i].fuel_type << " || Transmission: " << arr[i].transmission << " || Engine Size: " << arr[i].engine_size << " || Doors: " << arr[i].doors << " || Colour: " << arr[i].colour << " || Body Type: " << arr[i].body_type << " || URL: " << arr[i].url << " || Sale Date: " << arr[i].sale_date << " ||"  << endl;
                cout << "----------------------------------------------------------------------" << endl << endl;
            }
        }
    }

    void displaysortbyPrice() {
        int n = size; 
        Car* arr = new Car[n];
        Car* temp = head;
  
        for (int i = 0; i < n; i++) {
            arr[i] = *temp;
            temp = temp->next;
        }

        heapSortPrice(arr, n);
        cout << "----------------------------------------------------------------------" << endl;
        cout << "			 Car List Sort By Price		" << endl;
        cout << "----------------------------------------------------------------------" << endl;
        if (size == 0) {
            cout << "----------------------------------------------------------------------" << endl;
            cout << "			 No Car		" << endl;
            cout << "----------------------------------------------------------------------" << endl;
        }
        else {
            for (int i = 0; i < n; i++) {
                cout << "Price: £" << arr[i].price << endl;
                cout << "----------------------------------" << endl;
                cout << "|| Car Id: " << arr[i].id << " || Car Name: " << arr[i].title << " || Mileage: " << arr[i].mileage << " || Price: £" << arr[i].price << " || Registration Date: " << arr[i].registration_date << " || Fuel Type: " << arr[i].fuel_type << " || Transmission: " << arr[i].transmission << " || Engine Size: " << arr[i].engine_size << " || Doors: " << arr[i].doors << " || Colour: " << arr[i].colour << " || Body Type: " << arr[i].body_type << " || URL: " << arr[i].url << " || Sale Date: " << arr[i].sale_date << " ||"  << endl;
                cout << "----------------------------------------------------------------------" << endl << endl;
            }
        }
    }

    template <typename T>
    void swap(T& a, T& b) {
        T temp = a;
        a = b;
        b = temp;
    }

    //heap sort
    void heapifyName(Car* arr, int n, int i) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < n && arr[l].title > arr[largest].title)
            largest = l;
        if (r < n && arr[r].title > arr[largest].title)
            largest = r;
        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapifyName(arr, n, largest);
        }
    }

    void heapSortName(Car* arr, int n) {
        for (int i = n / 2 - 1; i >= 0; i--)
            heapifyName(arr, n, i);
        for (int i = n - 1; i >= 0; i--) {
            swap(arr[0], arr[i]);
            heapifyName(arr, i, 0);
        }
    }

    //heap sort
    void heapifyPrice(Car* arr, int n, int i) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < n && arr[l].price > arr[largest].price)
            largest = l;
        if (r < n && arr[r].price > arr[largest].price)
            largest = r;
        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapifyPrice(arr, n, largest);
        }
    }

    void heapSortPrice(Car* arr, int n) {
        for (int i = n / 2 - 1; i >= 0; i--)
            heapifyPrice(arr, n, i);
        for (int i = n - 1; i >= 0; i--) {
            swap(arr[0], arr[i]);
            heapifyPrice(arr, i, 0);
        }
    }

    //heap sort
    void heapifyMileage(Car* arr, int n, int i) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < n && arr[l].mileage > arr[largest].mileage)
            largest = l;
        if (r < n && arr[r].mileage > arr[largest].mileage)
            largest = r;
        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapifyMileage(arr, n, largest);
        }
    }

    void heapSortMileage(Car* arr, int n) {
        for (int i = n / 2 - 1; i >= 0; i--)
            heapifyMileage(arr, n, i);
        for (int i = n - 1; i >= 0; i--) {
            swap(arr[0], arr[i]);
            heapifyMileage(arr, i, 0);
        }
    }

    bool removeCarById(int id) {
        if (head == nullptr) return false;
       Car* current = head, * prev = nullptr;
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

    //merge sort
    Car* merge_sort(Car* head) {
        if (head == NULL || head->next == NULL) {
            return head;
        }
        Car* mid = mid_point(head);
        Car* a = head;
        Car* b = mid->next;
        mid->next = NULL;
        a = merge_sort(a);
        b = merge_sort(b);
        Car* c = merge(a, b);
        return c;
    }

    Car* merge(Car* a, Car* b)
    {
        if (a == NULL) {
            return b;
        }
        if (b == NULL) {
            return a;
        }
        
        Car* c;
        if (a->id < b->id)
        {
            c = a;
            c->next = merge(a->next, b);
        }
        else
        {
            c = b;
            c->next = merge(a, b->next);
        }
        return c;
    }

    Car* mid_point(Car* head)
    {
        if (head == NULL || head->next == NULL) {
            return head;
        }
        Car* fast = head;
        Car* slow = head;
        while (fast != NULL && fast->next != NULL)
        {
            fast = fast->next;
            if (fast->next == NULL)
                break;
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }

    void sort() {
        head = merge_sort(head);
        merge_sort(head);
    }

    //binary search
    Car* binarysearchcardetail(int target)
    {
        sort();
        int n = size;
        int left = 0, right = n - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            Car* midNode = head;
            for (int i = 0; i < mid; i++)
                midNode = midNode->next;

            if (midNode->id == target)
                return midNode;

            if (midNode->id < target)
                left = mid + 1;

            else
                right = mid - 1;
        }

        // Target not found
        return NULL;
    }

};


