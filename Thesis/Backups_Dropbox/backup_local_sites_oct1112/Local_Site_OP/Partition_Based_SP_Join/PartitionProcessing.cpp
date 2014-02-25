#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <cmath>

#include "PartitionProcessing.h"
#include "FileWriter.h"

using namespace std;

int level1_coords_processing(std::string file_name)
{
	
	std::string pattern1="'/Non-Leaf Node:  level=1/,/Leaf Node:  level=0/p'";
	std::string pattern2="RS='branch' 'NR > 1 { print $7, $8, $9, $10, $5 }'";

	std::string sed_cmd1 = "sed -n " + pattern1 +" ../Test_Data/"+file_name;
	std::string sed_cmd2="awk -v "+ pattern2 + ">" +" ../Test_Data/l1_awk_coords_"+file_name; 
	std::string final_command=sed_cmd1+" | "+sed_cmd2;
	
	//cout<<final_command<<endl;
	system(final_command.c_str());
	
	//enc_coords_processing(file_name);
	
	std::string level_1_coords_file="../Test_Data/l1_awk_coords_"+file_name; 
	std::string encmp_coords_file= "../Test_Data/global_enc_mbr.txt";
	
	create_coords_encmp_array(level_1_coords_file.c_str(),encmp_coords_file.c_str(),file_name);
	
	return 0;
}

int leaves_coords_processing(std::string file_name)
{
	
	std::string pattern1="'/Leaf Node:  level=0/,/Non-Leaf Node:  level=1/p'";
	std::string pattern2="RS='branch' 'NR > 1 { print $7, $8, $9, $10, $5 }'";

	std::string sed_cmd1 = "sed -n " + pattern1 +" ../Test_Data/"+file_name;
	std::string sed_cmd2= "awk -v "+ pattern2 +">"+" ../Test_Data/leaves_awk_coords_"+file_name;  
	std::string final_command=sed_cmd1+" | "+sed_cmd2;
	
	//cout<<final_command<<endl;
	system(final_command.c_str());
	
	//enc_coords_processing(file_name);
	
	std::string leaves_coords_file="../Test_Data/leaves_awk_coords_"+file_name; 
	std::string encmp_coords_file= "../Test_Data/global_enc_mbr.txt";
	
	create_coords_encmp_array(leaves_coords_file.c_str(),encmp_coords_file.c_str(),file_name);
	
	return 0;

}
int enc_coords_processing(std::string file_name)
{
	
	std::string pattern1= "'2,/Leaf Node:  level=0/p'";
	std::string pattern2= "\'/^rect:[\\t]*/{s///; N ; s/\\n[ ]*/ / ;s/[\\t]\\+/\\n/g ; p}'";

	std::string sed_cmd1 = "sed -n " + pattern1+ " ../Test_Data/"+file_name;
	std::string sed_cmd2= "sed -ne "+ pattern2 +">"+" ../Test_Data/enc_coords_"+file_name;  	

	std::string final_command=sed_cmd1+" | "+sed_cmd2;
	//cout<<final_command<<endl;
	system(final_command.c_str());
	return 0;
			
}
int create_coords_encmp_array(const char* coords, const char* encmp, std::string file_name)
{
		long int coords_length=0,encmp_coords_length=0;
		
/*----------------Coords Array Initialization Starts--------------------------------*/
		
		ifstream read_coords_file_count(coords);
		std::string coords_ids_line,coords_substr;
		if(read_coords_file_count.is_open())
		{
			while(read_coords_file_count.good())
			{
				getline(read_coords_file_count,coords_ids_line);
				istringstream iss(coords_ids_line,istringstream::in);
				while(iss>>coords_substr)
				{
				   coords_length++;
				}					
			}
		read_coords_file_count.close();
		}
		else
		{
			cout<<"Unable to open:"<<coords<<"at"<<"create_coords_encmp_array() inside BloomFilterProcessing.cpp";	
		}
		cout<<"coords_length:"<<coords_length<<endl;
		//long double *coords_ids_array= new long double[coords_length];
		vector <long double> coords_ids_vector;
		coords_ids_vector.reserve(coords_length);
		
/*-----------------Coords Array Initialization Ends------------------------------------------*/
/*-----------------Encmp Array Initialization Starts-----------------------------------------*/
		
		ifstream read_encmp_file_count(encmp);
		std::string encmp_line;
		
		if(read_encmp_file_count.is_open())
		{
			while(read_encmp_file_count.good())
			{
				getline(read_encmp_file_count,encmp_line);
				encmp_coords_length++;
						
			}
		read_encmp_file_count.close();	
		}
		else
		{
			cout<<"Unable to open:"<<encmp<<"at"<<"BloomFilterProcessing.cpp::create_coords_encmp_array()";	
		}
		//cout<<"encmp_coords_length:"<<encmp_coords_length<<endl;
		long double encmp_array[encmp_coords_length];
					
/*-----------------------------Encmp Array Initialization Ends---------------------------------------*/	

/*-----------------------------Coords Array Insertion Starts-----------------------------------------*/
		
		ifstream read_coords_file(coords);
		std::string coords_file_line,substr;
		
		if(read_coords_file.is_open())
		{
			//int i=0;
			while(read_coords_file.good())
			{
				getline(read_coords_file,coords_file_line);
				istringstream iss(coords_file_line,istringstream::in);
				while(iss>>substr)
				{
				   long double temp=::strtod(substr.c_str(),0);
				   coords_ids_vector.push_back(temp);
				}
			}
		}
		else
		{
			cout<<"Unable to open:"<<coords<<"at"<<"BloomFilterProcessing.cpp::create_coords_encmp_array()";	
		}
		
/*-----------------------------Coords Array Insertion Ends---------------------------------------*/	

/*------------------------------Encmp Array Insertion Starts---------------------------------*/
		
		ifstream read_encmp_file(encmp);
		std::string encmp_file_line;
		
		if(read_encmp_file.is_open())
		{
			int i=0;
			while(read_encmp_file.good())
			{
				getline(read_encmp_file,encmp_file_line);
				long double temp=::strtod(encmp_file_line.c_str(),0);
	   			encmp_array[i++]=temp;
			}
		read_encmp_file.close();	
		}
		else
		{
			cout<<"Unable to open:"<<encmp<<"at"<<"BloomFilterProcessing.cpp::create_coords_encmp_array()";	
		}
		
					
/*-----------------------------Encmp Array Insertion Ends---------------------------------------*/	
	
	
	//cout<<"Encmp Coords Length:"<<endl;
	//cout<<encmp_coords_length;
	
	vector <long double> enc_mbr_vector;
	for(int i=0; i<encmp_coords_length-1; i++)
	{
		enc_mbr_vector.push_back(encmp_array[i]);
	}
	//EncompassingMBR encompMBR;
	//encompMBR.encomp_mbr_calc(enc_coords_vector);
	
	//vector <long double> enc_mbr_vector = encompMBR.get_enc_coord_vector();
	//enc_mbr_to_file(enc_mbr_vector,file_name);
	
	get_partition_indices(enc_mbr_vector,coords_ids_vector,coords_length,file_name);
	return 0;	
}


int get_partition_indices(vector <long double> enc_mbr_vector, vector <long double> coords_ids_vector,int coords_length, std::string file_name)
{
  
  int no_of_partitions;
  //cout<<"How many partitions?:"<<endl;
  //cin>>no_of_partitions;

  ifstream read_partition_info("../Test_Data/partition_info.txt");
  std::string read_line;

 while(read_partition_info >> read_line )
 {
	
	no_of_partitions= atoi(read_line.c_str());

 }	

/*--------------------Partitions  Starts--------------------------------------------------------------------------*/	
    long double c_mbr[5],candidate_mbr[5]={0};
    vector<string> final_indices;
    int cmbr_index=0;
	for(int i=0;i<coords_ids_vector.size();i+=5)
 	{
 	    cmbr_index=0;
	    for(int j=i;j<i+5;j++)
	 	{
 			c_mbr[cmbr_index++]=coords_ids_vector[j];	
 		}
 		candidate_mbr[0]=c_mbr[0];
 		candidate_mbr[1]=c_mbr[2];
 		candidate_mbr[2]=c_mbr[1];
 		candidate_mbr[3]=c_mbr[3];
 		candidate_mbr[4]=c_mbr[4];
 		
		 partition_function_input(enc_mbr_vector,candidate_mbr,no_of_partitions,final_indices);
 		
 				
 	}
 	string_array_to_file(final_indices,file_name);
	return 0;	
}


int partition_function_input(vector <long double> encompassing_mbr_coord,long double *candidate_mbr,int no_of_partitions, vector<string> &final_indices)
{
	
	long double lowest_x,lowest_y,highest_x,highest_y;
	
	lowest_x=encompassing_mbr_coord[0];
	highest_x=encompassing_mbr_coord[1];
	lowest_y=encompassing_mbr_coord[2];
	highest_y=encompassing_mbr_coord[3];

	int row_dim=no_of_partitions*no_of_partitions;
	long double coords[row_dim][4];
	

	//cout<<"Encmp MBRs: "<<"lx:"<<encompassing_mbr_coord[0]<<" ly:"<<encompassing_mbr_coord[1]<<" hx:"<<encompassing_mbr_coord[2]<<" hy:"<<encompassing_mbr_coord[3]<<endl;
	//cout<<"Candidate MBRs: "<<"lx:"<<candidate_mbr[0]<<" ly:"<<candidate_mbr[1]<<" hx:"<<candidate_mbr[2]<<" hy:"<<candidate_mbr[3]<<endl;

	//int mbr_index_holder[2];
	
	long double partition_along_x_axis=abs(highest_x-lowest_x)/no_of_partitions;
	long double partition_along_y_axis=abs(highest_y-lowest_y)/no_of_partitions;
	
	//cout<<"partition_along_x_axis:"<<partition_along_x_axis<<endl;
	//cout<<"partition_along_y_axis:"<<partition_along_y_axis<<endl;
	
        int count=0;
        for(long double st_y=lowest_y;st_y<highest_y;st_y+=partition_along_y_axis)
		{
			double loop_hy=st_y+partition_along_y_axis;
			for(long double st_x=lowest_x;st_x<highest_x;st_x+=partition_along_x_axis)
			{
					coords[count][0]=st_x;
					coords[count][1]=st_y;
					coords[count][2]=st_x+partition_along_x_axis;
					coords[count][3]=st_y+partition_along_y_axis;
					count++;
					
					double loop_hx=st_x+partition_along_x_axis;
					if(loop_hx>=highest_x)
					{
						break;	
					}
			}
			if(loop_hy>=highest_y)
			{
				break;	
			}
	}
	//int index=0;
	
	vector<int> mbr_index_holder;
	mbr_index_holder.reserve(2);
	
	for(int i=0;i<row_dim;i++)
	{
	
            if(candidate_mbr[0]>=coords[i][0]
		   	&& candidate_mbr[0]<=coords[i][2]
 			&& candidate_mbr[1]>=coords[i][1]
 			&& candidate_mbr[1]<=coords[i][3])
            {
				mbr_index_holder.push_back(i);
	        }
		   	else if(candidate_mbr[2]>=coords[i][0]
			   && candidate_mbr[2]<=coords[i][2]
 			   && candidate_mbr[3]>=coords[i][1]
 			   && candidate_mbr[3]<=coords[i][3])
			   {
				mbr_index_holder.push_back(i);
			   }
	}
	
	//vector<string> final_indices;
	//index_vector.reserve(row_dim);
	
	if(mbr_index_holder.size()>0)
	{
			long double temp_lx,temp_ly,temp_hx,temp_hy;
			int temp_index_1,temp_index_2;
			
			temp_index_1=mbr_index_holder[0];
			temp_index_2=mbr_index_holder[mbr_index_holder.size()-1];
		
			
			temp_lx=coords[temp_index_1][0];
			temp_ly=coords[temp_index_1][1];
			
			temp_hx=coords[temp_index_2][2];
			temp_hy=coords[temp_index_2][3];	
				
			//cout<<"temp_lx:"<<temp_lx<<endl<<"temp_ly:"<<temp_ly<<endl<<"temp_hx:"<<temp_hx<<endl<<"temp_hy:"<<temp_hy;
				
			int index_array_count=0;
			char buff[10];
			for(int i=0;i<row_dim;i++)
			{
			
						if(coords[i][0]>=temp_lx 
						&& coords[i][0]<=temp_hx 
						&& coords[i][1]>=temp_ly 
						&& coords[i][1]<=temp_hy
						&& coords[i][2]>=temp_lx 
						&& coords[i][2]<=temp_hx 
						&& coords[i][3]>=temp_ly 
						&& coords[i][3]<=temp_hy)
				        {
							
							sprintf(buff,"%d",i);
							std::string temp;
							temp=buff;
							final_indices.push_back(temp);
							
							std::stringstream ss;
						    ss<< candidate_mbr[4];
							std::string rectids_indices;
							rectids_indices=" "+ss.str();
							final_indices.push_back(rectids_indices);
							final_indices.push_back("\n");
							
						}
					
			}
	}
    /*std::stringstream ss;
    ss<< candidate_mbr[4];
	std::string rectids_indices;
	rectids_indices=" "+ss.str();
	final_indices.push_back(rectids_indices);*/
	//final_indices.push_back("\n");
	
	return 0;
}

