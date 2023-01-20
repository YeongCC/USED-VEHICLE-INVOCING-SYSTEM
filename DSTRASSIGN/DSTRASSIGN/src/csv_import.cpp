#include "../include/csv_import.h"
#include "../include/interface.h"
#include <exception>

namespace UVIS
{
    csv_handler carlist("db/carlist.csv");


    void csv_read_util(csv_handler& csv, const severaldatatype& filename, const list<severaldatatype>& keys)
    {
        if (!csv.init_read())
        {
            Interface::print_note("Importing error!", Csv::severaldatatype("Database file ").append(filename).append(".csv\" is missing."));
            throw std::runtime_error("Data is corrupted.");
            return;
        }
        csv.read_and_terminate();
        csv.get_table().fix_keys(keys);
    }

    void init_all_csvs()
    {
        csv_read_util(carlist, "carlist",
            {  "Price" });
    }
}
