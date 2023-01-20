#include "../include/manage_vehicle.h"

namespace UVIS
{
    using namespace Interface;
    using namespace Csv;
    using namespace std;
    void same();
    void decision(int N, severaldatatype* operations, void (*functions[])(), severaldatatype title);

    void ViewVehicleSortByName() {
        Interface::select_menu sort_name;
        sort_name.set_title("View Vehicle Sort By Name");



        table course_semester_table = carlist.get_table();
        //cout<<course_semester_table.get_keys().size();
        Interface::print_table(course_semester_table, severaldatatype("Cart list"));



        Interface::pause();
        
        same();
    }

    void ViewVehicleSortByMilleage() {
        same();
    }

    void ViewVehicleSortByPrice() {
        same();
    }

    void BookVehicle() {



    }

    void same() {
        severaldatatype book_vehicle__main[] = { "Book Vehicle" };
        void (*__bookvehicle[])() = { BookVehicle };
        decision(1, book_vehicle__main, __bookvehicle, "Book Vehicle");
    }

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

};