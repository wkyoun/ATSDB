/*
 * This file is part of ATSDB.
 *
 * ATSDB is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ATSDB is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with ATSDB.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ALLBUFFERCSVEXPORTJOB_H
#define ALLBUFFERCSVEXPORTJOB_H

#include "boost/date_time/posix_time/posix_time.hpp"
#include <memory>

#include "job.h"
#include "buffer.h"

class DBOVariableOrderedSet;

class AllBufferCSVExportJob : public Job
{
public:
    AllBufferCSVExportJob(std::map<std::string, std::shared_ptr <Buffer>> buffers, DBOVariableOrderedSet* read_set,
                          std::map <unsigned int, std::string> number_to_dbo,
                          const std::vector <std::pair<unsigned int, unsigned int>>& row_indexes,
                          const std::string& file_name, bool overwrite, bool only_selected, bool use_presentation,
                          bool show_associations);
    virtual ~AllBufferCSVExportJob();

    virtual void run ();

protected:
    std::map<std::string, std::shared_ptr <Buffer>> buffers_;
    DBOVariableOrderedSet* read_set_;
    std::map <unsigned int, std::string> number_to_dbo_;
    const std::vector <std::pair<unsigned int, unsigned int>>& row_indexes_;

    std::string file_name_;
    bool overwrite_;
    bool only_selected_;
    bool use_presentation_;
    bool show_associations_;

    boost::posix_time::ptime start_time_;
    boost::posix_time::ptime stop_time_;
};

#endif // AllBufferCSVExportJob_H
