#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "Local_MBR.h" 
#include "FileWriter.h"
#include "EncCoordsExtraction.h"

using namespace std;


vector <long double> encomp_mbr_calc(vector <long double> mydoubles)
{
		  
		  long double temp_doubles[]={};
		  int index=0;
		  int num_of_coords=mydoubles.size();
  		  
	      //cout<<"num_of_coords:"<<num_of_coords<<endl;
		  int coord_factor=num_of_coords/4;
		  vector<long double> temp_vector;
		  
		  
		  temp_vector.assign(temp_doubles,temp_doubles+coord_factor);
		  
    	  //cout<<"num of coords:"<<num_of_coords;
		  vector <long double> final_vector;
  		
		  for(int i=0;i<num_of_coords/coord_factor;i++)
		  {
		  		index=0;
		  		for(int j=i; j<num_of_coords; j=j+4)
			  	{
		  			
						temp_vector[index]=mydoubles[j];
						
						if(i==0 && index==coord_factor-1)
						{
							stable_sort (temp_vector.begin(),temp_vector.end());
							final_vector.push_back(temp_vector[0]);
						}
						else if(i==1 && index==coord_factor-1)
						{
							stable_sort (temp_vector.begin(),temp_vector.end());
							final_vector.push_back(temp_vector[coord_factor-1]);
							
						}
						else if(i==2 && index==coord_factor-1)
						{
							stable_sort (temp_vector.begin(),temp_vector.end());
							final_vector.push_back(temp_vector[0]);
							
						}
						else if(i==3 && index==coord_factor-1)
						{
							stable_sort (temp_vector.begin(),temp_vector.end());
							final_vector.push_back(temp_vector[coord_factor-1]);
							
						}
						index++;
		  		}
		  }
	 return final_vector;
}


int local_mbr_calc(std::string rtree_file)
{
	
	enc_coords_processing(rtree_file);
	std::string local_enc_coords="../Test_Data/enc_coords_"+rtree_file;
	//cout<<local_enc_coords<<endl;	
	vector<long double> file_inputs, local_mbr_vector;
	ifstream read_local_enc_coords(local_enc_coords.c_str());
	
	std::string read_local_coords;
	while(read_local_enc_coords >> read_local_coords)
	{
		file_inputs.push_back(::strtod(read_local_coords.c_str(),0));
	}
	/*for(int i=0; i<file_inputs.size();i++)
	{
		
		cout<<file_inputs[i]<<endl;
		
	}*/
	
	local_mbr_vector=encomp_mbr_calc(file_inputs);
	local_mbr_to_file(local_mbr_vector,rtree_file);
	
		
		
	return 0;	
}
