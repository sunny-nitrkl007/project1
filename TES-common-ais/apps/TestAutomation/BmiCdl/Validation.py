#!/usr/bin/python
# -*- coding: cp1252 -*-
from Config import*
import xlwt
import xlrd
import sys
import json
from pprint import pprint
import xlsxwriter
import io
import datetime
import csv, os
from glob import glob
from xlsxwriter.workbook import Workbook
from xlwt import Workbook
from xlrd import open_workbook
import openpyxl

PID_DSI_flag =0
PID_DSI_flag_Neglect =0
GPS_DSI_flag =0
GPS_DSI_flag_Neglect =0
TimeZone_DSI_flag =0
TimeZone_DSI_flag_Neglect =0
ProductID_DSI_flag =0
ProductID_DSI_flag_Neglect =0
JSON_FAIL = [] # This List contains the JSON files that didnt simulate data properly

######################################################
## Converts all the output CSV files to excel files
######################################################
for csvfile in glob(Output_File_path+'*.csv'):
    name = os.path.basename(csvfile).split('.')[0]
    workbooknew = xlsxwriter.Workbook(Output_File_path+'excel/' + str(name) + '.xlsx', {'strings_to_numbers': True,'constant_memory': True})
    worksheetnew = workbooknew.add_worksheet()
    with open(csvfile, 'r') as f:
        r = csv.reader(f)
        for row_index, row in enumerate(r):
            for col_index, data in enumerate(row):
                worksheetnew.write(row_index, col_index, data)
    workbooknew.close()

print("-------------------------------------------")
print(" .CSV to .XLSX Conversion Successful")
print("-------------------------------------------")

pidlist = []
PIDtype =[]
typelist = []
ddlist = []
mddlist =[]
rlist = []
testdata =[]
Input = xlrd.open_workbook(Input_excel_file)
sheet = Input.sheet_by_index(0)

######################################################
## Stores the list PIDs from input
## excel file in the list - 'pidlist'
######################################################

for colidx in range(sheet.ncols):
     if sheet.cell_value(0, colidx) == "PID":
          for row in range(1, sheet.nrows):
                pidlist.append(sheet.cell_value(row, colidx))
print ('PIDList', pidlist)

######################################################
## Stores the PID type (Int/Character) from input
## excel file in the list - 'typelist'
######################################################

for row in range(1, sheet.nrows):
                typelist.append(sheet.cell_value(row,2))
print ('Type list', typelist)

######################################################
## Stores the Default data from input excel file
## in the list - 'rlist'
######################################################

for colidx in range(sheet.ncols):
     if sheet.cell_value(0, colidx) == "Resolution":
          for row in range(1, sheet.nrows):
                rlist.append(sheet.cell_value(row, colidx))
print ('Resolution List', rlist)

######################################################
## Stores the Default data from input excel file
## in the list - 'ddlist'
######################################################

for colidx in range(sheet.ncols):
     if sheet.cell_value(0, colidx) == "Default Data":
          for row in range(1, sheet.nrows):
               ddlist.append(sheet.cell_value(row, colidx))
print ('Default Data List',ddlist)

######################################################
## Stores the Default data multiplied with their
## respective resoltion in the list - 'mddlist'
######################################################

for pid in range(len(pidlist)):
     if typelist[pid] != '':
          mddlist.append(ddlist[pid]*rlist[pid]) 
     else:
          mddlist.append(ddlist[pid])
print 'Default Data List with resolution'+str(mddlist)

######################################################
## Creates Dictionary to store all PID input entries
######################################################
paramDict = {}
for i in range(len(pidlist)):
    paramDict["pidtv_"+str(i)] = []
print('paramDict',paramDict)

######################################################
## Stores all the input values into the Dictionary
##  - 'paramDICT'
######################################################

for colidx in range(sheet.ncols):
     if sheet.cell_value(0, colidx) == "PID":
          for pid in range(len(pidlist)):
               for rowidx in range(sheet.nrows):
                    if pidlist[pid] == sheet.cell_value(rowidx,colidx):
                         if typelist[pid] != '':
                              paramDict["pidtv_"+str(pid)].append([sheet.cell_value(rowidx, i)*rlist[pid] for i in range(5,(5+Test_input_count))])
                         else:
                              paramDict["pidtv_"+str(pid)].append([sheet.cell_value(rowidx, i) for i in range(5,(5+Test_input_count))])


print 'PARAMDICT'+str(paramDict)
print("-------------------------------------------")
print(" Get the input details")
print("-------------------------------------------")

######################################################
## Validation for all the output excel files
######################################################
workbook = xlsxwriter.Workbook(Report_path)
dir = Output_File_path+'excel'
print (len(os.listdir(dir)))
print (os.listdir(dir))
for n in range(len(os.listdir(dir))):
     prototype =[]
     gottype =[]

     ##################################################
     ## Parse into the Test JSON file and store
     ## the protocol type in the list - 'prototype'
     ##################################################
     a = open(Json_File_path+'BmiCdl_Test_'+str(n)+'.json',"r").readlines()
     for num, line in enumerate(a,1):
        if 'parm_request_type' in line:
            gottype.append(line.strip().split(':')[1])     

     for i in range(len(gottype)):
         if gottype[i]== ' 0,':
             prototype.append('SPB')
         elif gottype[i]== ' 1,':
             prototype.append('PGB')
         elif gottype[i]==' 2,':
             prototype.append('ADT')
         elif gottype[i]== ' 3,':
             prototype.append('read poll')
         else: 
             prototype.append('invalid value')

     print('Protocol type'+str(n),prototype)

     print("-------------------------------------------")
     print(" Read from json protocol type")
     print("-------------------------------------------")

     paramData = {}
     paramInputData = {}
     fails=[]
     values =[]
     change =[]
     blanks =[]
     startDT =[]
     endDT =[]
     endDT1 =[]
     dsi =[]
     dsi1 =[]
     compare =[]
     variable =[]
     variable1 =[]
     variable2 =[]
     variable3 =[]
     PIDLIST=[]
     pid_index = 0

     protocol1= xlrd.open_workbook(Output_File_path+'excel/' + str(n)+ '_AutomationOutput.xlsx')
     sheet1 = protocol1.sheet_by_index(0)
     for pid in range(len(pidlist)):
          paramData["PIDvalues_"+str(pid)] = []
          paramInputData["pidtv_"+str(pid)] = []
          for colidx in range(sheet1.ncols):
               if pidlist[pid] == sheet1.cell_value(0,colidx):
                    tvs = paramDict["pidtv_"+str(pid)][0]
                    print ('TEST DATA OF THE PID '+str(pidlist[pid]),tvs)
                    if typelist[pid] != '':
                         count = 0
                         for rowidx in range(sheet1.nrows):
                              if rowidx == 0:
                                   if sheet1.cell_value(rowidx,colidx) == pidlist[pid]:
                                    print ('PID TO VERIFY '+str(pidlist[pid]))
                                    PIDLIST.append(sheet1.cell_value(rowidx,colidx))
                                    for colidx1 in range(sheet.ncols):
                                           if sheet.cell_value(0, colidx1) == "PID":
                                               for rowidx1 in range(sheet.nrows):
                                                   if sheet1.cell_value(rowidx,colidx) == sheet.cell_value(rowidx1,colidx1):
                                                       paramInputData["pidtv_"+str(pid_index)].append([(int(round(sheet.cell_value(rowidx1, i)*rlist[pid]))) for i in range(5,(5+Test_input_count))])
                      
                              else:     
                                   for i in range(len(tvs)):
                                       if sheet1.cell_value(rowidx,colidx) == tvs[i]:
                                           PID_DSI_flag = 1
                                           values.append(colidx)
                                           paramData["PIDvalues_"+str(pid_index)].append(sheet1.cell_value(rowidx,colidx))
                                           startDT.append(sheet1.cell_value(rowidx,0))
                                       else:
                                           NOTHING =0
                                           
                                   paramData["PIDvalues_"+str(pid_index)] = list(dict.fromkeys(paramData["PIDvalues_"+str(pid_index)]))
                                                                                     
                                   if sheet1.cell_value(rowidx,colidx) == 'ff10' or sheet1.cell_value(rowidx,colidx) == 'ff13' or sheet1.cell_value(rowidx,colidx) == 'ff11':
                                        if PID_DSI_flag == 1:
                                             count= count+1
                                   elif sheet1.cell_value(rowidx,colidx) == mddlist[pid]:
                                        change.append(colidx)
                                   
                                   elif sheet1.cell_value(rowidx,colidx) == '':
                                        blanks.append(colidx)
                      
                         pid_index = pid_index+1
                         PID_DSI_flag = 0
                         dsi.append(count)
                         
                    else:
                         Variable_count = 0
                         for rowidx in range(sheet1.nrows):
                              if sheet1.cell_value(0,colidx) == 'fa27':
                                   if sheet1.cell_value(rowidx,colidx) == pidlist[pid]:
                                         print ('PID TO VERIFY '+str(pidlist[pid]))
                                         PIDLIST.append(sheet1.cell_value(rowidx,colidx))
                                         for colidx1 in range(sheet.ncols):
                                           if sheet.cell_value(0, colidx1) == "PID":
                                               for rowidx1 in range(sheet.nrows):
                                                   if sheet1.cell_value(rowidx,colidx) == sheet.cell_value(rowidx1,colidx1):
                                                       paramInputData["pidtv_"+str(pid_index)].append([sheet.cell_value(rowidx1, i) for i in range(5,(5+Test_input_count))])

                                   elif sheet1.cell_value(rowidx,colidx) == ':;<=ABCDEFGHIJK[\]^':
                                       change.append(colidx)
                                       TimeZone_DSI_flag = 1
                                   elif sheet1.cell_value(rowidx,colidx) == 'ff10' or sheet1.cell_value(rowidx,colidx) == 'ff13' or sheet1.cell_value(rowidx,colidx) == 'ff11':
                                       if TimeZone_DSI_flag == 1:
                                             Variable_count= Variable_count+1
                                   elif sheet1.cell_value(rowidx,colidx) == '':
                                       blanks.append(colidx)
                                   elif sheet1.cell_value(rowidx,colidx) != '':
                                       Variable = []
                                       for conv in str(sheet1.cell_value(rowidx,colidx)):
                                             a = ord(str(conv))
                                             a = hex(a).split('x')[-1]
                                             Variable.append(a)
                                             b = ' '.join(Variable)                                             
                                       variable1.append(b)
                                       TimeZoneList = []
                                       for data in variable1:
                                            TimeZoneList.append(data.upper())
                                       TimeZoneList = list(dict.fromkeys(TimeZoneList))
                                       paramData["PIDvalues_"+str(pid_index)] = list(TimeZoneList)
##                                       print ('TimeZoneList',TimeZoneList)

                              elif sheet1.cell_value(0,colidx) == 'f84d':
                                   if sheet1.cell_value(rowidx,colidx) == pidlist[pid]:
                                         print ('PID TO VERIFY '+str(pidlist[pid]))
                                         PIDLIST.append(sheet1.cell_value(rowidx,colidx))
                                         for colidx1 in range(sheet.ncols):
                                           if sheet.cell_value(0, colidx1) == "PID":
                                               for rowidx1 in range(sheet.nrows):
                                                   if sheet1.cell_value(rowidx,colidx) == sheet.cell_value(rowidx1,colidx1):
                                                       paramInputData["pidtv_"+str(pid_index)].append([sheet.cell_value(rowidx1, i) for i in range(5,(5+Test_input_count))])

                                   elif sheet1.cell_value(rowidx,colidx) == '!"#$%&(()01abc':
                                       change.append(colidx)
                                       GPS_DSI_flag = 1
                                   elif sheet1.cell_value(rowidx,colidx) == 'ff10' or sheet1.cell_value(rowidx,colidx) == 'ff13' or sheet1.cell_value(rowidx,colidx) == 'ff11':
                                       if GPS_DSI_flag == 1:
                                             Variable_count= Variable_count+1
                                   elif sheet1.cell_value(rowidx,colidx) == '':
                                       blanks.append(colidx)   
                                   elif sheet1.cell_value(rowidx,colidx) != '':
                                       Variable = []
                                       for conv in str(sheet1.cell_value(rowidx,colidx)):
                                             a = ord(str(conv))
                                             a = hex(a).split('x')[-1]
                                             Variable.append(a)
                                             b = ' '.join(Variable)                                             
                                       variable2.append(b)
                                       GPSList = []
                                       for data in variable2:
                                            GPSList.append(data.upper())
                                       GPSList = list(dict.fromkeys(GPSList))
                                       paramData["PIDvalues_"+str(pid_index)] = list(GPSList)
##                                       print ('GPSList',GPSList)

                              elif sheet1.cell_value(0,colidx) == 'f82d':
                                   if sheet1.cell_value(rowidx,colidx) == pidlist[pid]:
                                         print ('PID TO VERIFY '+str(pidlist[pid]))
                                         PIDLIST.append(sheet1.cell_value(rowidx,colidx))
                                         for colidx1 in range(sheet.ncols):
                                           if sheet.cell_value(0, colidx1) == "PID":
                                               for rowidx1 in range(sheet.nrows):
                                                   if sheet1.cell_value(rowidx,colidx) == sheet.cell_value(rowidx1,colidx1):
                                                       paramInputData["pidtv_"+str(pid_index)].append([sheet.cell_value(rowidx1, i) for i in range(5,(5+Test_input_count))])

                                   elif sheet1.cell_value(rowidx,colidx) == ':;<=ABCDEFGHIJK[\]^':
                                       change.append(colidx)
                                       ProductID_DSI_flag = 1                               
                                   elif sheet1.cell_value(rowidx,colidx) == 'ff10' or sheet1.cell_value(rowidx,colidx) == 'ff13' or sheet1.cell_value(rowidx,colidx) == 'ff11':
                                       if ProductID_DSI_flag == 1:
                                             Variable_count= Variable_count+1
                                   elif sheet1.cell_value(rowidx,colidx) == '':
                                       blanks.append(colidx)
                                   elif sheet1.cell_value(rowidx,colidx) != '':
                                       Variable = []
                                       for conv in str(sheet1.cell_value(rowidx,colidx)):
                                             a = ord(str(conv))
                                             a = hex(a).split('x')[-1]
                                             Variable.append(a)
                                             b = ' '.join(Variable)                                             
                                       variable3.append(b)
                                       ProductIDList = []
                                       for data in variable3:
                                            ProductIDList.append(data.upper())
                                       ProductIDList = list(dict.fromkeys(ProductIDList))
                                       paramData["PIDvalues_"+str(pid_index)] = list(ProductIDList)
##                                       print ('ProductIDList',ProductIDList)
                         pid_index = pid_index+1
                         GPS_DSI_flag = 0
                         TimeZone_DSI_flag = 0
                         ProductID_DSI_flag = 0
                         dsi.append(Variable_count)
     print '----------------------------------'
     print 'OUTPUT DATA OF ALL PIDS'
     print '----------------------------------'
     print ('PARAMETER Data',paramData)

     print '----------------------------------'
     print 'Input DATA OF ALL PIDS'
     print '----------------------------------'          
     print ('INPUT PARAMETER Data',paramInputData) 

     ##############################################
     ## Parse into the output excel file
     ## through each pid to find the number of
     ## DSI occurences & stores in the list -'DSI'
     ##############################################
     
     for pid in range(len(pidlist)):
          for colidx in range(sheet1.ncols):
               if pidlist[pid] == sheet1.cell_value(0,colidx):
                    tvs = paramDict["pidtv_"+str(pid)][0]
                    if typelist[pid] != '':
                         count = 0
                         for rowidx in range((sheet1.nrows-1),-1,-1):
                             if sheet1.cell_value(rowidx,colidx) == 'ff10' or sheet1.cell_value(rowidx,colidx) == 'ff13' or sheet1.cell_value(rowidx,colidx) == 'ff11':
                                 if PID_DSI_flag_Neglect == 0:
                                             count= count+1
                             elif sheet1.cell_value(rowidx,colidx) == mddlist[pid]:
                                 PID_DSI_flag_Neglect = 1
                             
                         PID_DSI_flag_Neglect = 0
                         dsi1.append(count)
                    else:
                        Variable_count = 0
                        for rowidx in range((sheet1.nrows-1),-1,-1):
                              if sheet1.cell_value(0,colidx) == 'fa27':
                                  if sheet1.cell_value(rowidx,colidx) == 'ff10' or sheet1.cell_value(rowidx,colidx) == 'ff13' or sheet1.cell_value(rowidx,colidx) == 'ff11':
                                      if TimeZone_DSI_flag_Neglect == 0:
                                          Variable_count = Variable_count+1
                                  elif sheet1.cell_value(rowidx,colidx) == ':;<=ABCDEFGHIJK[\]^':
                                      TimeZone_DSI_flag_Neglect = 1
                              if sheet1.cell_value(0,colidx) == 'f84d':
                                  if sheet1.cell_value(rowidx,colidx) == 'ff10' or sheet1.cell_value(rowidx,colidx) == 'ff13' or sheet1.cell_value(rowidx,colidx) == 'ff11':
                                      if GPS_DSI_flag_Neglect == 0:
                                          Variable_count = Variable_count+1
                                  elif sheet1.cell_value(rowidx,colidx) == '!"#$%&(()01abc':
                                      GPS_DSI_flag_Neglect = 1                                      
                              if sheet1.cell_value(0,colidx) == 'f82d':
                                  if sheet1.cell_value(rowidx,colidx) == 'ff10' or sheet1.cell_value(rowidx,colidx) == 'ff13' or sheet1.cell_value(rowidx,colidx) == 'ff11':
                                      if ProductID_DSI_flag_Neglect == 0:
                                          Variable_count = Variable_count+1
                                  elif sheet1.cell_value(rowidx,colidx) == ':;<=ABCDEFGHIJK[\]^':
                                      ProductID_DSI_flag_Neglect = 1
                        TimeZone_DSI_flag_Neglect=0
                        GPS_DSI_flag_Neglect=0
                        ProductID_DSI_flag_Neglect=0
                        dsi1.append(Variable_count)
     print '----------------------------------'
     print ('DSI_STATUS_1',dsi1)
     print '----------------------------------'                   
     for i in range(len(dsi) - len(dsi1)):
          dsi1.append(0)
     
     DSI = []
     for num in range(len(dsi1)):
         a = dsi[num] - dsi1[num]
         DSI.append(a)
     for i in range(len(DSI)):
          if DSI[i] >0:
               fails.append(i+1)
     for i in range(len(DSI)):
         if DSI[i] <0:
             DSI[i] = 0
     print '----------------------------------'
     print ('DSI_STATUS',DSI)
     print '----------------------------------'

     ############################################
     ## Stores the fail cases in the List-'fails'
     ############################################
     for pid in range(len(prototype)):
          if Test_input_count == len(paramData["PIDvalues_"+str(pid)]):
              tvs = paramInputData["pidtv_"+str(pid)][0]                            
              for i in range(len(paramData["PIDvalues_"+str(pid)])):
                                if paramData["PIDvalues_"+str(pid)][i] in tvs:
                                    Nothing = 0
                                else:
                                    fails.append(pid+1)    
          else:
              fails.append(pid+1)   
     ###########################################
     ## Stores the Start Time of testing for a
     ## particular JSON file
     ###########################################
     for rowcheck in range(sheet1.nrows):
       abd=(sheet1.cell_value(rowcheck,0))
     endDT = abd

     ###########################################
     ## Stores the END time of testing for a
     ## particular JSON file
     ###########################################
     for rowcheck in range((sheet1.nrows-1),-1,-1):
       if rowcheck == 1 :
           abd=(sheet1.cell_value(rowcheck,0))
     startDT = abd
     
     failcol =[]
     for x in fails:
          if x not in failcol:
               failcol.append(x)

         
     print("-------------------------------------------")
     print(" Validate the output")
     print("-------------------------------------------")

     
    
     m = (len(pidlist)+2)*n
     date_format = workbook.add_format({'num_format': 'hh:mm:ss'})
     if n==0:
          worksheet = workbook.add_worksheet('index')
          worksheet.write(0, 0, 'Automated test report for TES Common App')
          worksheet.write(1, 0, 'Tested by')
          worksheet.write(1, 1, Tested_by)
          worksheet.write(2, 0,'Tested on')
          currentDT = datetime.datetime.now()
          worksheet.write(2, 1, currentDT,date_format)
          worksheet.write(3, 0,'Test feature')
          worksheet.write(3, 1,'BMI CDL')
          worksheet.write(4, 0,'Total no of test cases')
          worksheet.write(5, 0,'No of pass cases')
          worksheet.write(6, 0, 'No of failure cases')
          worksheet.write(7, 0, 'TES common release tag')
          worksheet.write(7, 1, Release_tag)
          worksheet = workbook.add_worksheet('REPORT')
     worksheet.write(0, 0, 'CDL PID')
     worksheet.write(m+1, 0, 'TEST '+str(n))
     worksheet.write(0, 2, 'protocol used')
     for i in range(len(prototype)):
      worksheet.write(m+i+2, 2, prototype[i])
     
     worksheet.write(0, 3, 'Number of input values verified')
     for i in range(len(prototype)):
          a = len(paramData["PIDvalues_"+str(i)])
          worksheet.write(m+i+2, 3, a)
          if a<Test_input_count:
              print 'FAILS'
              JSON_FAIL.append(n)
     
     worksheet.write(0, 4, 'Timestamp begin')
     for i in range(len(prototype)):
      worksheet.write(m+i+2, 4, startDT,date_format)
     worksheet.write(0, 5, 'Timestamp end')
     for i in range(len(prototype)):
      worksheet.write(m+i+2,5, endDT,date_format)
     worksheet.write(0, 6, 'Total DSI values received')
     for i in range(len(prototype)):
      worksheet.write(m+i+2,6, DSI[i])

     worksheet.write(0, 8, 'Data Tested')
     for i in range(len(prototype)):
         TESTED_DATA=[]
         TESTED_DATA = paramData["PIDvalues_"+str(i)]
         for j in range(len(TESTED_DATA)):
             worksheet.write(m+i+2,8+j, TESTED_DATA[j])

     worksheet.write(0, 1, 'Result')
     for row in range( len(prototype)):
                   worksheet.write(m+row+2,0, PIDLIST[row])

     for row in range( len(prototype)):
                   worksheet.write(m+row+2,1, 'PASS')
                   
     for row in failcol:
                   worksheet.write(m+row+1, 1, 'FAIL')

     print pidlist
     print prototype
workbook.close()

Report = xlrd.open_workbook(Report_path)
Report_sheet = Report.sheet_by_index(1)
Test_case_count = 0
Pass_Test_case_count = 0
Fail_Test_case_count = 0
for colidx in range(Report_sheet.ncols):
     if Report_sheet.cell_value(0, colidx) == "Result":
          for row in range(1, Report_sheet.nrows):
              if Report_sheet.cell_value(row, colidx)=="PASS" or Report_sheet.cell_value(row, colidx)=="FAIL":
                  Test_case_count = Test_case_count+1
              if Report_sheet.cell_value(row, colidx)=="PASS":
                  Pass_Test_case_count = Pass_Test_case_count+1
              if Report_sheet.cell_value(row, colidx)=="FAIL":
                  Fail_Test_case_count = Fail_Test_case_count+1
                  


xfile = openpyxl.load_workbook(Report_path)

sheet = xfile.get_sheet_by_name('index')
sheet['B5'] = Test_case_count
sheet['B6'] = Pass_Test_case_count
sheet['B7'] = Fail_Test_case_count
xfile.save(Report_path)

print("-------------------------------------------")
print(" Report is generated.")
print("-------------------------------------------")



JSON_Simulation_FAIL = [] 

''' Removing the duplicate values from List - JSON_FAIL
    and populating the values in List - JSON_Simlation_FAIL'''
for x in JSON_FAIL:
    if x not in JSON_Simulation_FAIL:
        JSON_Simulation_FAIL.append(x)

print ('JSON_Simulation_FAIL',JSON_Simulation_FAIL)











