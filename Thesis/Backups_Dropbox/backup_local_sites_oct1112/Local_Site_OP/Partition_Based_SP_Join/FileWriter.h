#ifndef INCLUDE_FILEWRITERCLASS_CPP_H
#define INCLUDE_FILEWRITERCLASS_CPP_H
#include <vector>
#include <string>
using namespace std;

int bool_array_to_file(vector <bool>, std::string);
int string_array_to_file(vector <string>, std::string);
int bloom_filter_info(int *, std::string);
int enc_mbr_to_file(vector<long double>, std::string);
int bool_ins_vector_to_file(vector <bool>);
int global_mbr_to_file(vector <long double>);

#endif
