#include <iostream>
#include "include/csv_import.h"
#include "include/interface.h"
#include "include/manage_client.h"
#include "include/manage_report.h"
#include "include/manage_vehicle.h"
using namespace std;
using namespace Csv;
using namespace Interface;
using namespace UVIS;

severaldatatype authorized_userid, authorized_role;

void decision(int N, severaldatatype* operations, void (*functions[])(), severaldatatype title);

void manage_vehicle();
void manage_client();
void manage_report();


bool checkLogin(const severaldatatype& username, const severaldatatype& password);
void login();
void home();
void logout();

void decision(int N, severaldatatype* operations, void (*functions[])(), severaldatatype title)
{
    select_menu select;
    select.set_title(title);
    for (int i = 0; i < N; ++i)
        select.add_item(i + 1, operations[i]);
    select.add_item(N + 1, "Back");

    int chosen;
    do
    {
        chosen = select.print_menu_and_wait().to_int();
        if (chosen >= 1 && chosen <= N)
            functions[chosen - 1]();
    } while (chosen != N + 1);
}

void logout()
{
    authorized_userid.init();
    authorized_role.init();
    login();
}


void manage_vehicle() {
    severaldatatype manage_vehicle__main[] = { "View Vehicle Sort By Name", "View Vehicle Sort By Milleage", "View Vehicle Sort By Price"};
    void (*__manage_vehicle[])() = { ViewVehicleSortByName,ViewVehicleSortByMilleage,ViewVehicleSortByPrice };
    decision(3, manage_vehicle__main, __manage_vehicle, "Manage Vehicle");
}

void manage_client() {
    severaldatatype manage_client__main[] = { "Search Client By Name", "View All Client Order", "Cancel Client Order"};
    void (*__manageclient[])() = { SearchClientName,ViewAllOrder,CanceelOrder };
    decision(3, manage_client__main, __manageclient, "Manage Client");
}

void manage_report() {
    severaldatatype manage_report__main[] = { "View Sale Report By Name", "View All Sale Report By DateTime", "View All Billing Report By Price" , "Search Sale Report By Id" , "Search Billing Report By Id" };
    void (*__managereport[])() = { ViewSRptByName,ViewSRptByDateTime,ViewBRptByDatePrice,SearchSRptById,SearchBRptById };
    decision(5, manage_report__main, __managereport, "Manage Report");
}

void home()
{
    select_menu user;
    user.set_title(severaldatatype("Welcome ").append(authorized_role).append(" @").append(authorized_userid));
    if (authorized_role.equal("Manager")) {
        user.add_item(1, "Manage Vehicle");
        user.add_item(2, "Manage Client");
        user.add_item(3, "Logout");
    }
    else {
        user.add_item(1, "Manage Vehicle");
        user.add_item(2, "Manage Client");
        user.add_item(3, "Manage Report");
        user.add_item(4, "Logout");
    }
    while (true)
    {
        int chosen = user.print_menu_and_wait().to_int();
        if (authorized_role.equal("Manager")) {
            if (chosen == 1)
            {
                manage_vehicle();
            }
            else if (chosen == 2) {
                manage_client();
            }
            else {
                break;
            }
        }
        else {
            if (chosen == 1)
            {
                manage_vehicle();
            }
            else if (chosen == 2) {
                manage_client();
            }
            else if (chosen == 3) {
                manage_report();
            }
            else {
                break;
            }
        }                
    }
    logout();
}



bool checkLogin(const severaldatatype& username, const severaldatatype& password) {
        
    if ((username.equal("Manager") && password.equal("Manager"))||(username.equal("Salesperson") && password.equal("Salesperson")))
    {
        if (username.equal("Manager")) {
            authorized_userid = "Manager";
            authorized_role = "Manager";
        }
        else if (username.equal("Salesperson")) {
            authorized_userid = "Salesperson";
            authorized_role = "Salesperson";
        }

        return true;
    }
    return false;
}

void login() {
    input_menu login_menu;
    login_menu.set_title("Login");
    login_menu.add_item("Username");
    login_menu.add_item("Password");
    select_menu select;
    select.set_title("What do you want?");
    select.add_item(1, "Login");
    select.add_item(2, "Exit");
    while (true)
    {
        int chosen = select.print_menu_and_wait().to_int();
        if (chosen == 1)
        {
            list<severaldatatype> res = login_menu.print_menu_and_wait();
            if (checkLogin(res.at(0), res.at(1)))
            {
                print_note("You have successfully logged in.", "Success");
                pause();
                break;
            }
            else
            {
                print_note("Username or password is incorrect. Please try again.", "Failed");
                pause();
            }
        }
        else
            return;
    }
    home();
}



int main()
{
	cout << "Importing data... ";
    init_all_csvs();
    cout << "Done!" << endl
        << endl;
    system("pause");

    login();
    print_note("Bye See You Next Time !", "Exiting UVIS...");
    pause();
    return 0;
}

