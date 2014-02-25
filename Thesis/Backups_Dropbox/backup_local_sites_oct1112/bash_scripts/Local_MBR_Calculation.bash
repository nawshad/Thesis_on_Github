#!/bin/bash


#This script will wait for the partition_info.txt file to arrive from query_site: orcinus.westgrid.ca.Upon the arrival it understands that the process has started
#and then it calculates the local MBR and send the local_enc_mbr_<file_name> to the query site.

#files other than rtree_lb_* are delete
rm -f ../Test_Data/e*
rm -f ../Test_Data/g*
rm -f ../Test_Data/l*
rm -f ../Test_Data/p*
rm -f ../Test_Data/R*
rm -f ../Test_Data/u*
rm -f ../Test_Data/s*
rm -f ../Test_Data/f*

#wait for the partition_info.txt to arrive.

while true
do

	if [ -f ../Test_Data/partition_info.txt ]
	then 
		echo found!
		break
	else
		sleep 0.001
		#echo not found!
	fi
	
done

../Local_Site_OP/Local_MBR_Calc/Create_Local_MBR $1

local_enc_mbr_file_path=../Test_Data/local_enc_mbr_$1
remote_address=osborn@orcinus.westgrid.ca:/home/osborn/Thesis/Test_Data

scp $local_enc_mbr_file_path $remote_address
echo file successfully sent to  $remote_address



#wait for global_enc_mbr.txt file to arrive


while true
do
	if [ -f ../Test_Data/global_enc_mbr.txt ]
	then
		break
	else
		sleep 0.001
	fi
done

echo Global_enc_mbr.txt arrived!



#upon arrival of global_enc_mbr.txt, it runs the PartitionBasedSpJoin

../Local_Site_OP/Partition_Based_SP_Join/local_pb_sp_join $1

#The above program outputs the RectIds_and_Indices_Site_$1


cut -d ' ' -f1 ../Test_Data/RectIds_and_Indices_Site_$1 | sort -u > ../Test_Data/usi_$1
scp ../Test_Data/usi_$1 osborn@orcinus.westgrid.ca:/home/osborn/Thesis/Test_Data

#wait for global_indices.txt file to arrive

while true
do
	if [ -f ../Test_Data/global_indices.txt ]
	then
		break
	else
		sleep 0.001
	fi
done

echo global_indices arrived!

#Now find out the final rect_ids

sort ../Test_Data/RectIds_and_Indices_Site_$1 > ../Test_Data/Sorted_RectIds_and_Indices_Site_$1

join -j 1 ../Test_Data/Sorted_RectIds_and_Indices_Site_$1 ../Test_Data/global_indices.txt | awk '{ print $2 }' | uniq > ../Test_Data/final_rectids_$1

echo File Written Successfully!



 




