#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include "Global_MBR.h" 
#include "FileWriter.h"
#include "PartitionProcessing.h"

using namespace std;


vector <long double> encomp_mbr_calc(vector <long double> mydoubles, int flag=0)
{
		  
		  long double temp_doubles[]={};
		  int index=0;
		  int num_of_coords;
		 
		  if(flag==0)
  		  {
  			num_of_coords=mydoubles.size()-1;	
  		  }
  		  else
          {
  	     	num_of_coords=mydoubles.size();
  		  }
	      cout<<"num_of_coords:"<<num_of_coords<<endl;
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

int read_files(std::string file_name, vector<long double> &container)
{
	
/*Getting enc_coords and save it to an enc_coords_vector, pass it to get_enc_coords()::EncompassingMBR*/	
	enc_coords_processing(file_name);
	std::string enc_coords_file_name="../Test_Data/enc_coords_"+file_name;
	
	ifstream read_enc_coords_file(enc_coords_file_name.c_str());
	std::string enc_coords_line;
	
	vector<long double> enc_coords_vector;
	if(read_enc_coords_file.is_open())
	{
		while(read_enc_coords_file.good())
		{	
			getline(read_enc_coords_file,enc_coords_line);
			long double temp = ::strtod(enc_coords_line.c_str(),0);
			//cout<<temp<<endl;
  			enc_coords_vector.push_back(temp);
				
		}
	read_enc_coords_file.close();	
	}
	vector<long double> encmp_mbr_vector = encomp_mbr_calc(enc_coords_vector); 
	//cout<<"Size:"<<encmp_mbr_vector.size();
	//cout<<file_name;
	enc_mbr_to_file(encmp_mbr_vector,file_name);
/*------------------------End Process------------------------------------------*/	
	
	std::string full_name= "../Test_Data/enc_mbr_"+file_name;
	std::string read_enc_mbr;
	ifstream read_enc_mbr_file(full_name.c_str());
	if(read_enc_mbr_file.is_open())
	{		
		while(read_enc_mbr_file.good())
		{
		    
		 		getline(read_enc_mbr_file,read_enc_mbr);
			 	long double temp=::strtod(read_enc_mbr.c_str(),0);
	         	container.push_back(temp);	
		 	
		 }
	read_enc_coords_file.close();	 
	}
	else
	{
		cout<<"Unable to open:"<<file_name<<"at:"<<"Global_MBR_Calc::read_file()"<<endl;
	}
		
	return 0;
}
int global_mbr_calc()
{
	cout<<"Please Specify the files,for Global MBR Calculation"<<endl;
	std::string files[10], file_name;
	char ch;
	vector <long double> container;
	
	int index=0;
	while(1)
	{
		cout<<"Encompassing MBR File Name?:";
		cin>>file_name;
		files[index]=file_name;
		read_files(files[index],container);
		index++;			
		cout<<"Continue?(y/n):";
		cin>>ch;
		if(ch=='n')break;
	}
	
	vector<long double> mbr_vector;
	cout<<"Container Data:"<<endl;
	for(int i=0; i<container.size();i+=5)
	{
	
		for(int j=i;j<i+4;j++)
		{
			mbr_vector.push_back(container[j]);
			cout<<container[j]<<endl;	
		}		
	}
	
	//cout<<"MBR Vector Size:"<<mbr_vector.size();
	/*for(int i=0;i<mbr_vector.size();i++)
	{		
		cout<<mbr_vector[i]<<endl;		
	}*/	
    vector<long double> global_mbr_vector;
	if(index>1)
	{
		global_mbr_vector=encomp_mbr_calc(mbr_vector,1);
		global_mbr_to_file(global_mbr_vector);
	}
	else
	{
		global_mbr_to_file(mbr_vector);
	}
		
	return 0;	
}
