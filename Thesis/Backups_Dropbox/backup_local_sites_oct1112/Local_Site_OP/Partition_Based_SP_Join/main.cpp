#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

#include "PartitionProcessing.h"
#include "Global_MBR.h"

/*int partition_based_sp_join()
{
    cout<<"Now Please specify the file:"<<endl;
	cout<<"File Name?:";
	std::string file_name;
	cin>>file_name;
	
	std::string file_name_str;
	file_name_str="../Test_Data/"+file_name;
	
	std::string level;
	//std::transform(level.begin(),level.end(), level.begin(), ::toupper);	
	leaves_coords_processing(file_name);		
	return 0;
	
}*/

int main(int argc, char** argv)
{

	
	leaves_coords_processing(argv[1]);

	return 0;	 
}
