#include <fstream>
#include <iostream>
#include "FileWriter.h"
 
 using namespace std;



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
