#include <fstream>
#include <iostream>
#include "FileWriter.h"
 
 using namespace std;

int bool_array_to_file(vector <bool> bloombits, std::string file_name)
{
	std::string bloom_filter_file_name="../Test_Data/Bloom_Filter_Site_A_"+file_name;
	ofstream write_bloom_filter(bloom_filter_file_name.c_str());
	if(write_bloom_filter.is_open())
	{
		for(int i=0;i<bloombits.size();i++)
		{
			write_bloom_filter<<bloombits[i]<<endl;
		}
		write_bloom_filter.close();
	}
	else
	{
	 	cout<<"Cannot write the file";	
	}
	return 0;
}

int bool_ins_vector_to_file(vector <bool> bloombits)
{
	std::string ins_bloom_filter_file_name="../Test_Data/Intersected_Bloom_Filter.txt";
	ofstream write_ins_bloom_filter(ins_bloom_filter_file_name.c_str());
	if(write_ins_bloom_filter.is_open())
	{
		for(int i=0;i<bloombits.size();i++)
		{
			write_ins_bloom_filter<<bloombits[i]<<endl;
		}
		write_ins_bloom_filter.close();
	}
	else
	{
	 	cout<<"Cannot write the file";	
	}
	return 0;
}

int string_array_to_file(vector <string> rect_ids_and_indices, std::string file_name)
{
    std::string rectids_and_indices_file_name="../Test_Data/RectIds_and_Indices_Site_"+file_name;
	ofstream write_rectids_and_indices(rectids_and_indices_file_name.c_str());
	if(write_rectids_and_indices.is_open())
	{
		for(int i=0;i<rect_ids_and_indices.size();i++)
		{
			write_rectids_and_indices<<rect_ids_and_indices[i];
		}
		write_rectids_and_indices.close();
	}
	else
	{
	 	cout<<"Cannot write the file";	
	}
	return 0;
}

int bloom_filter_info(int *info, std::string file_name)
{
	
	std::string info_file_name="../Test_Data/BloomFilterInfo_Site_A_"+file_name;
	ofstream write_fileinfo(info_file_name.c_str());
	if(write_fileinfo.is_open())
	{
		for(int i=0;i<3;i++)
		{
			write_fileinfo<<info[i]<<endl;
		}
		write_fileinfo.close();
	}
	else
	{
	 	cout<<"Cannot write the file";	
	}
	return 0;	
}

int enc_mbr_to_file(vector<long double> enc_mbr_vector, std::string local_file_name)
{
	
	std::string enc_file_name="../Test_Data/enc_mbr_"+local_file_name;
	ofstream write_enc_mbr(enc_file_name.c_str());
	if(write_enc_mbr.is_open())
	{
		for(int i=0;i<enc_mbr_vector.size();i++)
		{
			write_enc_mbr<<enc_mbr_vector[i]<<endl;
		}
		write_enc_mbr.close();
	}
	else
	{
	 	cout<<"Cannot write the file";	
	}
	return 0;	
}

int global_mbr_to_file(vector<long double> local_enc_mbr_vector)
{
	
	std::string global_file_name="../Test_Data/global_enc_mbr.txt";
	ofstream write_global_enc_mbr(global_file_name.c_str());
	if(write_global_enc_mbr.is_open())
	{
		for(int i=0;i<local_enc_mbr_vector.size();i++)
		{
			write_global_enc_mbr<<local_enc_mbr_vector[i]<<endl;
		}
		write_global_enc_mbr.close();
	}
	else
	{
	 	cout<<"Cannot write the file";	
	}
	return 0;	
}
