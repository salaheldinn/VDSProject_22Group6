#include "Manager.h"
#include <vector>
#include <unordered_map>

using namespace ClassProject;

Manager::Manager(){
    //Initialize False and True in the unique table
    unique_table_entry temp_entry = {.id=0, .high=0, .low=0, .topvar=0, .label="False"};
    unique_table.push_back(temp_entry);
    temp_entry = {.id=1, .high=1, .low=1, .topvar=1, .label="True"};
    unique_table.push_back(temp_entry);
}