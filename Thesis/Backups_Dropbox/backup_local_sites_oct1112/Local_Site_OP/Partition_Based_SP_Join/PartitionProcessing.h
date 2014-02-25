#ifndef INCLUDE_PARTITIONPROCESSING_CPP_H
#define INCLUDE_PARTITIONPROCESSING_CPP_H
#include <vector>
#include <string>

using namespace std;


int level1_coords_processing(std::string);
int leaves_coords_processing(std::string);
int enc_coords_processing(std::string);
int create_coords_encmp_array(const char*, const char*, std::string);
int	get_partition_indices(vector <long double>, vector <long double>,int,std::string);
int partition_function_input(vector <long double>,long double*,int, vector<string>&);


#endif
