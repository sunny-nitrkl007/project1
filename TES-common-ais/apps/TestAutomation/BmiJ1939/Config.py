import paramiko
import os
import stat
import threading
import glob
import xlrd
import fnmatch
import time
import csv
import openpyxl
import datetime
from xml.dom import minidom
import telematics
from telematics import*
from vlib import Simulations

telematics.a5mx_interface.initialization()

''' THE BELOW ARE CONFIGURABLE PARAMETERS '''
###################################################
## Path for all the Input files
###################################################
XML_File_path = "C:/Tools/BMI_J1939/Input_Files/XML-File/"

Json_File_path = "C:/Tools/BMI_J1939/Input_Files/JSON-File/"

Robot_file_path = "C:/Tools/BMI_J1939/Input_Files/Robo-File/Test_Robot.rb"

A6N2_key_File_path = "C:/Tools/BMI_J1939/Input_Files/A6N2-Key/a6n2-id_rsa"
A6N2_Key_password = "p30r1a"

Input_File_path = "C:/Tools/BMI_J1939/Input_Files/Input_data.xlsx"

Output_File_path = "C:/Tools/BMI_J1939/Output_Files/"

Host_IP = "165.26.79.19"

###################################################
## Total number of Test Data in the InputData File
###################################################
Test_input_count = 3
        
###################################################
## Path of CPM folder
###################################################    
target_path_get = "C:/Tools/BMI_J1939/CPM/"

source_path_put = "C:/Tools/BMI_J1939/CPM/"

###################################################
## Verity Name 
###################################################
Verity_name = 'CPM_5471997_14_00'
Autostart_name = 'zzAutostart_5471997_14_00'

###################################################
## Validation 
###################################################
Input_excel_file = "C:/Tools/BMI_J1939/Input_Files/Input_data.xlsx"
Report_path = "C:/Tools/BMI_J1939/Report.xlsx"
input_file_path = "C:/Tools/BMI_J1939/Input_Files/"
Tested_by = "Anuhya"
Release_tag = "0.9.0"

###################################################
## Interchange of Rows in input excel
###################################################
TEST_DATA = 'C:/Tools/BMI_J1939/Input_Files/TEST_INPUT.xlsx'
Input_file = 'C:/Tools/BMI_J1939/Input_Files/Input_data.xlsx'

