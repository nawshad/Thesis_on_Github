#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <cmath>


#include "EncCoordsExtraction.h"
#include "FileWriter.h"

using namespace std;


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
