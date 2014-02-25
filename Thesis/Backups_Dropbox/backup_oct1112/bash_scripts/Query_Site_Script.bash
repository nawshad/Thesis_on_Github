#!/bin/bash


#Delete all files other than partition_info.txt

rm -f ../Test_Data/A*
rm -f ../Test_Data/l*


local_pdcp_binary_path=../../local/bin/pdcp 
remote_pdcp_binary_path=/home/osborn/local/bin/pdcp
remote_host_names=osborn@nestor.westgrid.ca,jasper.westgrid.ca,bugaboo.westgrid.ca
local_file_path=../Test_Data/partition_info.txt
remote_file_path=/home/osborn/Thesis/Test_Data

#partition_info.txt file is sent each local sites.

$local_pdcp_binary_path -R ssh -e $remote_pdcp_binary_path -w $remote_host_names $local_file_path $remote_file_path

#Now it will wait for all local_enc_mbr to reach.

while [[ ! -s ../Test_Data/All_Enc_Coords.txt ]]; do
  if [ $(find ../Test_Data/local_enc* | wc -l) -eq 3 ]; then
    cat ../Test_Data/local_enc* > ../Test_Data/All_Enc_Coords.txt
  else
    sleep 1
  fi
done


#Calculate global_mbr and save it to global_enc_mbr.txt

../Global_MBR_Calc/Create_Global_MBR All_Enc_Coords.txt

#send global_enc_mbr.txt to remote sites

global_enc_file_path=../Test_Data/global_enc_mbr.txt

$local_pdcp_binary_path -R ssh -e $remote_pdcp_binary_path -w $remote_host_names $global_enc_file_path $remote_file_path

while [[ ! -s ../Test_Data/global_indices.txt ]]; do
  if [ $(find ../Test_Data/usi* | wc -l) -eq 3 ]; then
    join -j 1 ../Test_Data/usi* > ../Test_Data/global_indices.txt
  else
    sleep 1
  fi
done

global_indices_file_path=../Test_Data/global_indices.txt
$local_pdcp_binary_path -R ssh -e $remote_pdcp_binary_path -w $remote_host_names $global_indices_file_path $remote_file_path








