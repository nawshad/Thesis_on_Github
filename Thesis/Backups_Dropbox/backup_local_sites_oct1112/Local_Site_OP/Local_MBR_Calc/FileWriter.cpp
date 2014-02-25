#include <fstream>
#include <iostream>
#include "FileWriter.h"
 
using namespace std;

int local_mbr_to_file(vector<long double> local_enc_mbr_vector, std::string local_file_name)
{
	
	std::string file_name="../Test_Data/local_enc_mbr_"+local_file_name;
	//cout<<file_name<<endl;
	ofstream write_local_enc_mbr(file_name.c_str());
	if(write_local_enc_mbr.is_open())
	{
		for(int i=0;i<local_enc_mbr_vector.size();i++)
		{
			write_local_enc_mbr<<local_enc_mbr_vector[i]<<endl;
		}
		write_local_enc_mbr.close();
	}
	else
	{
	 	cout<<"Cannot write the file";	
	}
	cout<<"File:"<<file_name<<" successfully written"<<endl;
	return 0;	
}