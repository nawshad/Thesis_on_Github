#include <iostream>
#include <string>

#include "EncCoordsExtraction.h"
#include "Local_MBR.h"



int main(int argc, char** argv)
{
	
	//std::string file_name="rtree_lb_2000.txt";
	local_mbr_calc(argv[1]);
	return 0;	 
}
