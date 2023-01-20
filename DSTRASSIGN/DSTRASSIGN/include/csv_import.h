#ifndef CSV_IMPORT_H
#define CSV_IMPORT_H

#include "csv.h"

namespace UVIS
{
    using namespace Csv;

    extern csv_handler carlist;


    void csv_read_util(csv_handler& csv, const severaldatatype& filename, const list<severaldatatype>& keys);

    // import all csv files.
    void init_all_csvs();
}

#endif // CSV_IMPORT_H
