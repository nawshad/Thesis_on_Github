#include <iostream>
#include <string>

#include "EncCoordsExtraction.h"
#include "Global_MBR.h"

int main(int argc, char** argv)
{
	
	//std::string file_name="../Test_Data/All_Local_Enc_Coords.txt";
	global_mbr_calc(argv[1]);
	return 0;	 
}
