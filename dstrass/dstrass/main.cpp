#include <iostream>
#include <string>
#include "carlist.h"
#include "reportlist.h"
#include "billlist.h"
using namespace std;

string authorized_userid, authorized_role;
CarList carlist;
ReportList reportlist;
BillingtList billingtlist;

void readcsv();
void book_vehicle();
void manage_vehicle();
void manage_client();
void manage_report();
bool checkLogin(string username,string password);
void login();
void home();
void logout();

void readcsv() {
	ifstream file("db/carlist.csv");
	string line;
	getline(file, line);
	while (std::getline(file, line)) {
		string data;
		string title;
		string registration_date;
		string price;
		string mileage;
		string fuel_type;
		string transmission;
		string engine_size;
		string doors;
		string colour;
		string body_type;
		string url;
		string sale_date;
		bool in_quote = false;
		int column = 0;
		for (char c : line) {
			if (c == '"') {
				in_quote = !in_quote;
			}
			else if (c == ',' && !in_quote) {
				if (column == 0) {
					title = data;
				}
				else if (column == 1) {
					price = data;
					int pos = price.find("Â£");
					if (pos != string::npos) {
						price.erase(pos, 2);
					}
					int pos2 = price.find(",");
					if (pos2 != string::npos) {
						price.erase(pos2, 1);
					}
				}
				else if (column == 2) {
					registration_date = data;
				}
				else if (column == 3) {
					mileage = data;
				}
				else if (column == 4) {
					fuel_type = data;
				}
				else if (column == 5) {
					transmission = data;
				}
				else if (column == 6) {
					engine_size = data;
				}
				else if (column == 7) {
					if (data == "") {
						doors = "-";
					}else{
						doors = data;
					}
				}
				else if (column == 8) {
					colour = data;
				}
				else if (column == 9) {
					body_type = data;
				}
				else if (column == 10) {
					url = data;
				}
				else if (column == 11) {
					sale_date = data;
				}
				data.clear();
				column++;
			}
			else {
				data += c;
			}
		}

		sale_date = data;
		carlist.insertAtLast(title, stod(price), stoi(registration_date), stoi(mileage), fuel_type, transmission, engine_size, doors, colour, body_type, url, sale_date);
	}
}

bool checkLogin(string username, string password) {

	if (username=="Manager" && password=="Manager" || username=="Salesperson" && password=="Salesperson")
	{
		if (username=="Manager") {
			authorized_userid = "Manager";
			authorized_role = "Manager";
		}
		else{
			authorized_userid = "Salesperson";
			authorized_role = "Salesperson";
		}

		return true;
	}
	return false;
}


void manage_client(){
	cout << "1. Search Client By Name" << endl;
	cout << "2. View All Client Order" << endl;
	cout << "3. Cancel Client Order" << endl;
	cout << "4. Back" << endl << endl;
	string option;
	cout << "Your Option: ";
	cin >> option;
	while (option != "1" && option != "2" && option != "3" && option != "4")
	{
		cout << "Your Option: " << endl;
		cin >> option;
	}
	if (option == "1") {
		if (reportlist.size == 0) {
			cout << "----------------------------------------------------------------------" << endl;
			cout << "			 No Order		" << endl;
			cout << "----------------------------------------------------------------------" << endl;
			home();
		}
		else {
			string customer;
			cout << "Give the customer name: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, customer);
			Report* foundOrder = reportlist.searchOrderByName(customer);
			time_t t = foundOrder->report_create_time;
			if (foundOrder == nullptr) {
				cout << "Order not found." << std::endl;
				home();
			}
			else {
				cout << "----------------------------------------------------------------------" << endl;
				cout << "			 Order Found		" << endl;
				cout << "----------------------------------------------------------------------" << endl;
				cout << "Order Id: " << foundOrder->id << endl;
				cout << "Customer Name: " << foundOrder->customer << endl;
				cout << "Created Time: " << asctime(localtime(&t)) << endl;
				cout << "Selected Car Id: " << foundOrder->carid << endl;
				cout << "Selected Car Name: " << foundOrder->title << endl;
				cout << "Price: Â£" << foundOrder->price << endl;
				cout << "Mileage: " << foundOrder->mileage << endl;
				cout << "Registration Date: " << foundOrder->registration_date << endl;
				cout << "Fuel Type: " << foundOrder->fuel_type << endl;
				cout << "Transmission: " << foundOrder->transmission << endl;
				cout << "Engine Size: " << foundOrder->engine_size << endl;
				cout << "Doors: " << foundOrder->doors << endl;
				cout << "Colour: " << foundOrder->colour << endl;
				cout << "Body Type: " << foundOrder->body_type << endl;
				cout << "URL: " << foundOrder->url << endl;
				cout << "Sale Date: " << foundOrder->sale_date << endl;
				cout << "----------------------------------------------------------------------" << endl << endl << endl;
				cout << "----------------------------------------------------------------------" << endl << endl;
				home();
			}
		}
	}
	else if (option == "2") {
		reportlist.viewAllOrder();
		home();
	}
	else if (option == "3") {
		reportlist.viewAllOrder();
		if (reportlist.size == 0) {
			cout << "			 No Order can Cancel"<<endl;
			cout << "----------------------------------------------------------------------" << endl << endl << endl;
			home();
		}
		else {
			int id;
			cout << "Give the order id you want to cancel: ";
			cin >> id;
			Report* foundOrder = reportlist.searchReportById(id);
			carlist.reinsertAtLast(foundOrder->carid, foundOrder->title, foundOrder->price, foundOrder->registration_date, foundOrder->mileage, foundOrder->fuel_type, foundOrder->transmission, foundOrder->engine_size, foundOrder->doors, foundOrder->colour, foundOrder->body_type, foundOrder->url, foundOrder->sale_date);
			if (reportlist.removeOrderById(id)) {
				billingtlist.removeBillById(id);
				cout << "----------------------------------------------------------------------" << endl;
				cout << "			 Cancel Successful		" << endl;
				cout << "----------------------------------------------------------------------" << endl << endl << endl;
				home();
			}
			else {
				cout << "----------------------------------------------------------------------" << endl;
				cout << "			 Something Wrong, Cancel Fail		" << endl;
				cout << "----------------------------------------------------------------------" << endl << endl << endl;
				home();
			}

		}
	}
	else {
		system("cls");
		home();
	}
};

void manage_report(){
	cout << "1. View All Sale Report By Name" << endl;
	cout << "2. View All Sale Report By DateTime" << endl;
	cout << "3. View All Billing Report By Price" << endl;
	cout << "4. Search Sale Report By Id" << endl ;
	cout << "5. Search Billing Report By Id" << endl;
	cout << "6. Search Sale Report By Car Id" << endl;
	cout << "7. Back" << endl << endl;
	string option;
	cout << "Your Option: ";
	cin >> option;
	while (option != "1" && option != "2" && option != "3" && option != "4" && option != "5" && option != "6" && option != "7")
	{
		cout << "Your Option: " << endl;
		cin >> option;
	}
	if (option == "1") {
		reportlist.selectionSortByName();
		home();
	}
	else if (option == "2") {
		reportlist.selectionSortByDateTime();
		home();
	}
	else if (option == "3") {
		billingtlist.selectionSortByPrice();
		home();
	}
	else if (option == "4") {
		if (reportlist.size == 0) {
			cout << "----------------------------------------------------------------------" << endl;
			cout << "			 No Report		" << endl;
			cout << "----------------------------------------------------------------------" << endl;
			home();
		}
		else {
			string reportid;
			cout << "Give the report id: ";
			cin >> reportid;
			Report* foundReport = reportlist.searchReportById(reportid);
			if (foundReport == nullptr) {
				cout << "----------------------------------------------------------------------" << endl;
				cout << "			 Report Not Found		" << endl;
				cout << "----------------------------------------------------------------------" << endl;
				home();
			}
			else {
				cout << "----------------------------------------------------------------------" << endl;
				cout << "			 Report Found		" << endl;
				cout << "----------------------------------------------------------------------" << endl;
				cout << "Report Id: " << foundReport->id << endl;
				cout << "Customer Name: " << foundReport->customer << endl;
				cout << "Selected Car Id: " << foundReport->carid << endl;
				cout << "Selected Car Name: " << foundReport->title << endl;
				cout << "Price: Â£" << foundReport->price << endl;
				cout << "Mileage: " << foundReport->mileage << endl;
				cout << "Registration Date: " << foundReport->registration_date << endl;
				cout << "Fuel Type: " << foundReport->fuel_type << endl;
				cout << "Transmission: " << foundReport->transmission << endl;
				cout << "Engine Size: " << foundReport->engine_size << endl;
				cout << "Doors: " << foundReport->doors << endl;
				cout << "Colour: " << foundReport->colour << endl;
				cout << "Body Type: " << foundReport->body_type << endl;
				cout << "URL: " << foundReport->url << endl;
				cout << "Sale Date: " << foundReport->sale_date << endl;
				cout << "----------------------------------------------------------------------" << endl << endl << endl;
				cout << "----------------------------------------------------------------------" << endl << endl;
				home();
			}
		}
	}
	else if (option == "5") {
		if (billingtlist.size == 0) {
			cout << "----------------------------------------------------------------------" << endl;
			cout << "			 No Report		" << endl;
			cout << "----------------------------------------------------------------------" << endl;
			home();
		}
		else {
			string billingid;
			cout << "Give the billing report id: ";
			cin >> billingid;
			Billing* foundBilling = billingtlist.searchReportByCarId(billingid);
			if (foundBilling == nullptr) {
				cout << "----------------------------------------------------------------------" << endl;
				cout << "			 Billing Report Not Found		" << endl;
				cout << "----------------------------------------------------------------------" << endl;
				home();
			}
			else {
				cout << "----------------------------------------------------------------------" << endl;
				cout << "			 Billing Report Found		" << endl;
				cout << "----------------------------------------------------------------------" << endl;
				cout << "Selected Billing Id: " << foundBilling->id << endl;
				cout << "Customer Name: " << foundBilling->customer << endl;
				cout << "Price Amount: Â£" << foundBilling->price << endl;
				cout << "----------------------------------------------------------------------" << endl << endl << endl;
				cout << "----------------------------------------------------------------------" << endl << endl;
				home();
			}
		}
	}
	else if (option == "6") {
		if (reportlist.size == 0) {
			cout << "----------------------------------------------------------------------" << endl;
			cout << "			 No Report		" << endl;
			cout << "----------------------------------------------------------------------" << endl;
			home();
		}
		else {
			string carid;
			cout << "Give the car id: ";
			cin >> carid;
			Report* foundReport = reportlist.searchReportByCarId(carid);
			if (foundReport == nullptr) {
				cout << "----------------------------------------------------------------------" << endl;
				cout << "			 Report Not Found		" << endl;
				cout << "----------------------------------------------------------------------" << endl;
				home();
			}
			else {
				cout << "----------------------------------------------------------------------" << endl;
				cout << "			 Report Found		" << endl;
				cout << "----------------------------------------------------------------------" << endl;
				cout << "Report Id: " << foundReport->id << endl;
				cout << "Customer Name: " << foundReport->customer << endl;
				cout << "Selected Car Id: " << foundReport->carid << endl;
				cout << "Selected Car Name: " << foundReport->title << endl;
				cout << "Price: Â£" << foundReport->price << endl;
				cout << "Mileage: " << foundReport->mileage << endl;
				cout << "Registration Date: " << foundReport->registration_date << endl;
				cout << "Fuel Type: " << foundReport->fuel_type << endl;
				cout << "Transmission: " << foundReport->transmission << endl;
				cout << "Engine Size: " << foundReport->engine_size << endl;
				cout << "Doors: " << foundReport->doors << endl;
				cout << "Colour: " << foundReport->colour << endl;
				cout << "Body Type: " << foundReport->body_type << endl;
				cout << "URL: " << foundReport->url << endl;
				cout << "Sale Date: " << foundReport->sale_date << endl;
				cout << "----------------------------------------------------------------------" << endl << endl << endl;
				cout << "----------------------------------------------------------------------" << endl << endl;
				home();
			}
		}
	}
	else {
		system("cls");
		home();
	}
};

void book_vehicle() {
	cout << "1. Book Vehicle" << endl;
	cout << "2. Back" << endl << endl;
	string option;
	cout << "Your Option: ";
	cin >> option;

	while (option != "1" && option != "2")
	{
		cout << "Your Option: " << endl << endl;
		cin >> option;
	}
	if (option == "1") {
		string car;
		cout << "Selected car: ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, car);

		Car* foundCar = carlist.binarysearchcardetail(stoi(car));
		if (foundCar != nullptr) {
			cout << "Car title: " << foundCar->title << endl;
			cout << "Price: Â£" << foundCar->price << endl;
			cout <<  "Mileage: " << foundCar->mileage << endl;
			cout << "Registration Date: " << foundCar->registration_date << endl;
			cout << "Fuel Type: " << foundCar->fuel_type << endl; 
			cout << "Transmission: " << foundCar->transmission << endl; 
			cout << "Engine Size: " << foundCar->engine_size << endl;
			cout << "Doors: " << foundCar->doors << endl;
			cout << "Colour: " << foundCar->colour << endl;
			cout << "Body Type: " << foundCar->body_type << endl;
			cout << "URL: " << foundCar->url << endl;
			cout << "Sale Date: " << foundCar->sale_date << endl;
			cout << "----------------------------------------------------------------------" << endl << endl;
			string customername;
			string remarkid = to_string(reportlist.id) + "-" + to_string(billingtlist.id);
			int report_value, bill_value;
			report_value = reportlist.id;
			bill_value = billingtlist.id;
			cout << "Please Give Customer Name: ";
			cin >> customername;
			reportlist.insertAtLast(customername, remarkid, foundCar->id, foundCar->title, foundCar->price, foundCar->registration_date, foundCar->mileage,foundCar->fuel_type, foundCar->transmission, foundCar->engine_size, foundCar->doors, foundCar->colour, foundCar->body_type, foundCar->url, foundCar->sale_date);
			billingtlist.insertAtLast(foundCar->price, remarkid,customername);
			carlist.removeCarById(foundCar->id);
			cout << "----------------------------------------------------------------------"  << endl;
			cout <<	"			 Book Succesful !" << endl;
			cout << "----------------------------------------------------------------------" << endl << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "			 Receipt		" << endl;
			cout << "----------------------------------------------------------------------" << endl;
			Report* foundReport = reportlist.searchReportById(report_value);
			if (foundReport != nullptr) {
				cout << "Customer Name: " << foundReport->customer << endl;
				cout << "Selected Car Id: " << foundReport->carid << endl;
				cout << "Selected Car Name: " << foundReport->title << endl;
				cout << "Price: Â£" << foundReport->price << endl;
				cout << "Mileage: " << foundReport->mileage << endl;
				cout << "Registration Date: " << foundReport->registration_date << endl;
				cout << "Fuel Type: " << foundReport->fuel_type << endl;
				cout << "Transmission: " << foundReport->transmission << endl;
				cout << "Engine Size: " << foundReport->engine_size << endl;
				cout << "Doors: " << foundReport->doors << endl;
				cout << "Colour: " << foundReport->colour << endl;
				cout << "Body Type: " << foundReport->body_type << endl;
				cout << "URL: " << foundReport->url << endl;
				cout << "Sale Date: " << foundReport->sale_date << endl;
				cout << "----------------------------------------------------------------------" << endl << endl << endl;
				cout << "----------------------------------------------------------------------" << endl << endl;
				home();
			}
			else {
				cout << "Receipt not found" << endl << endl;
				home();
			}
		}
		else {
			cout << car << " not found in the list." << endl << endl;
			home();
		}
	}
	else {
		home();
	}
};

void manage_vehicle() {
	cout << "1. View Vehicle Sort By Name" << endl;
	cout << "2. View Vehicle Sort By Milleage" << endl;
	cout << "3. View Vehicle Sort By Price" << endl;
	cout << "4. Back" << endl << endl;
	cout << "Your Option: ";
	string option;
	cin >> option;
	while (option != "1" && option != "2" && option != "3" && option != "4")
	{
		cout << "Your Option: " << endl;
		cin >> option;
	}
	if (option == "1") {
		carlist.displaysortbyName();
		book_vehicle();
	}
	else if (option == "2") {
		carlist.displaysortbyMileage();
		book_vehicle();
	}
	else if (option == "3") {
		carlist.displaysortbyPrice();
		book_vehicle();
	}
	else {
		system("cls");
		home();
	}
};

void home() {
	if (authorized_role=="Manager") {
		string option;
		cout << "1. Manage Vehicle" << endl;
		cout << "2. Manage Client" << endl;
		cout << "3. Logout" << endl << endl;
		cout << "Your Option: ";
		cin >> option;
		while (option != "1" && option != "2" && option != "3")
		{
			cout << "Your Option: " << endl;
			cin >> option;
		}
		if (option == "1") {
			manage_vehicle();
		}
		else if (option == "2") {
			manage_client();
		}else{
			cout << "You have successfully logged out @" << authorized_userid << endl << endl;
			login();
		}

	}
	else {
		string option;
		cout << "1. Manage Vehicle" << endl;
		cout << "2. Manage Client" << endl;
		cout << "3. Manage Report" << endl;
		cout << "4. Logout" << endl << endl;
		cout << "Your Option: ";
		cin >> option;
		while (option != "1" && option != "2" && option != "3" && option != "4")
		{
			cout << "Your Option: " << endl;
			cin >> option;
		}
		if (option == "1") {
			manage_vehicle();
		}
		else if (option == "2") {
			manage_client();
		}
		else if(option=="3"){
			manage_report();
		}
		else {
			cout << "You have successfully logged out @" << authorized_userid << endl << endl;
			login();
		}
	}
}

void login() {
	cout << "What do you want?" << endl;
	cout << "1. Login" << endl;
	cout << "2. Exit" << endl << endl;
	string option;
	cout << "Your Option: ";
	cin >> option;

	while (option != "1" && option != "2")
    {
		cout << "Your Option: " << endl;
		cin >> option;
    }
	if (option == "1")
	{
		system("cls");
		string username, password;
		cout << "Username: ";
		cin >> username;
		cout << endl;
		cout << "Password: ";
		cin >> password;
		cout << endl;

		if (checkLogin(username, password))
		{
			cout<<"You have successfully logged in @" <<authorized_userid <<endl << endl;
			home();
		}
		else
		{
			cout <<"Username or password is incorrect. Please try again." << endl << endl;
			login();
		}
	}
	else{
		system("cls");
		return;
	}

	
}

int main()
{
	cout << "WELCOME TO  USED VEHICLE INVOCING SYSTEM"<<endl << endl;
	system("pause");
	system("cls");
	readcsv();
	login();

	cout << "BYE SEE YOU NEXT TIME !"<<endl<< endl << "EXITING UVIS..." << endl << endl;
	return 0;
}

