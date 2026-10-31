from Config import*

''' Json_files has the list of .json files present in the Json file path given '''
Json_files = glob.glob(Json_File_path+"*.json")
## Total number of Json Files
Json_files_count = len(Json_files)
print ('Json_files_count',Json_files_count)

def Change_json_file(Request_file):   
    ''' Change_json_file uploads the Test json file from local path to all the json
        files in the server path'''
    for filename in sftp.listdir('/opt/CPM/config'):
        if fnmatch.fnmatch(filename, "BmiJ1939Cfg_Default.json"):
            Json_Filename = '/opt/CPM/config/' + filename
            Test_Filename = Json_File_path+Request_file
            sftp.put(Test_Filename,Json_Filename)


def Input_simulator(Test_case,Input_filename):
    global i
    i = Test_case + 5
    workbook = xlrd.open_workbook(Input_filename)
    sheet = workbook.sheet_by_index(0)
    for row in range(1,sheet.nrows):
        if sheet.cell_value(row,3) == 'I':
            param_name = sheet.cell_value(row,0)
            param_name = (param_name.encode('ascii', 'ignore'))
            pid_data = sheet.cell_value(row,i)
            telematics.Simulation.set_parameter(param_name,pid_data)
            time.sleep(1)
        elif sheet.cell_value(row,3) == '':
            param_name = sheet.cell_value(row,0)
            param_name = (param_name.encode('ascii', 'ignore'))
            pid_data = sheet.cell_value(row,i)
            pid_data = (pid_data.encode('ascii', 'ignore'))
            telematics.Simulation.set_parameter(param_name,pid_data)
            time.sleep(2)
        elif sheet.cell_value(row,3) == 'PGN':
            paramater = sheet.cell_value(row,0)
            paramater = (paramater.encode('ascii', 'ignore'))
            ECM_Name = sheet.cell_value(row,2)
            ECM_Name = (ECM_Name.encode('ascii', 'ignore'))
            PiD_data = sheet.cell_value(row,i)
            PiD_data = (PiD_data.encode('ascii', 'ignore'))
            telematics.Simulation.j1939_broadcast_prop_change(ECM_Name, paramater,"value", PiD_data)


ECM_key = paramiko.RSAKey.from_private_key_file(A6N2_key_File_path,A6N2_Key_password)
ECM_connect = paramiko.SSHClient()
ECM_connect.set_missing_host_key_policy(paramiko.AutoAddPolicy())
ECM_connect.connect(hostname=Host_IP,port=22,username="root",pkey=ECM_key)
sftp = ECM_connect.open_sftp()

for Test in range(Json_files_count):
    
    #############################################
    ## Copy the Test Json File into ECM
    #############################################    
    Change_json_file('BmiJ1939_Test_'+str(Test)+'.json')
    print Test
    print '------------------------------'
    print 'BmiJ1939_Test_'+str(Test)+'.json'
    print '------------------------------'
    print 'STEP 6 : Copying Test JSON File'
    time.sleep(5)
    
    ###########################################
    ## Running BMI-J1939 & SCS
    ###########################################
    ECM_connect.invoke_shell()
    mount = 'mount -o remount,exec /opt/'
    stdin, stdout, stderr = ECM_connect.exec_command(mount)
    stdin, stdout, stderr = ECM_connect.exec_command('chmod -R 777 /opt/CPM/bin/')
    ECM_connect.invoke_shell()
    stdin, stdout, stderr = ECM_connect.exec_command('cd /opt/CPM/;. changeCatEnvToHere.sh;export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/CPM/usr/lib;cd /opt/CPM/bin/;./scs')
    time.sleep(5)
    ECM_connect.invoke_shell()
    stdin, stdout, stderr = ECM_connect.exec_command('cd /opt/CPM/;. changeCatEnvToHere.sh;export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/CPM/usr/lib;cd /opt/CPM/bin/;./bmiJ1939 >/opt/j1939.txt')
    time.sleep(5)
    print 'STEP 7 : Running BMI-J1939 and SCS'
    time.sleep(5)

    
    #############################################
    ## Enable ECM-PID Simulation
    #############################################    
    telematics.Simulation.configure(XML_File_path+'J1939_Test_XML_'+str(Test)+'.xml')
    mydoc = minidom.parse(XML_File_path+'J1939_Test_XML_'+str(Test)+'.xml')
    items = mydoc.getElementsByTagName('module')
    for elem in items:
        ECM_name = (elem.attributes['name'].value)
        telematics.Simulation.add_ecm_to_network(ECM_name)
        time.sleep(2)

    #############################################
    ## Enable ECM-PGN Simulation
    #############################################
   
    print 'STEP 8 : Configured the SImulation XML file'
    
    #############################################
    ### Test Data Simulation
    #############################################
    print 'STEP 9 : Simulation START with the Input Test data'
    Input_simulator(0,Input_File_path)
    for Data in range(Test_input_count):
##        Input_simulator(0,Input_File_path)
##        time.sleep(2)
        Input_simulator(Data+1,Input_File_path)
        time.sleep(2)
    Input_simulator(0,Input_File_path)
    time.sleep(2)
    print 'STEP 10 : Simulation DONE with the Input Test data'

    #############################################
    ## Disable ECM Simulation
    #############################################
    mydoc1 = minidom.parse(XML_File_path+'J1939_Test_XML_'+str(Test)+'.xml')
    items1 = mydoc1.getElementsByTagName('module')
    for elem in items1:
        ECM_name1 = (elem.attributes['name'].value)
        ECM_name1 = (ECM_name1.encode('ascii', 'ignore'))
        telematics.Simulation.remove_ecm_from_network(ECM_name1)
        time.sleep(2)
        
    print 'STEP 11 : Stop Simulation from all the ECM'
    time.sleep(5)

    #############################################
    ### FILE CREATION
    #############################################
    OutputFileName = str(Test)+'_AutomationOutput.csv'
    OutputFilePath = Output_File_path+OutputFileName
    f_obj = open(OutputFilePath,"w")
    time.sleep(5)
    sftp.get('/opt/tmp/outputFiles/AutomationData_J1939.csv',OutputFilePath)
    f_obj.close()
    print 'STEP 12 : OUTPUT File creation'

    #############################################
    ## Kill BMI-CDL & SCS application
    ############################################# 
    stdin, stdout, stderr = ECM_connect.exec_command('cd /opt/;killall -9 scs')
    time.sleep(2)
    stdin, stdout, stderr = ECM_connect.exec_command('cd /opt/;killall -9 bmiJ1939')
    time.sleep(2)
    print 'STEP 13 : BMI_J1939 & SCS Application Killed'

    sftp.remove('/opt/tmp/outputFiles/AutomationData_J1939.csv')
    print 'STEP 14 : CSV File created in ECM removed'
    time.sleep(5)
    

######################################################
## Creates a folder 'Excel' in the output files path
######################################################
if os.path.exists(Output_File_path+'excel') == False:
    os.mkdir(Output_File_path+'excel')
else :
    print 'Output Excel folder already exists'
    files = glob.glob(Output_File_path+'excel/*')
    for f in files:
        os.remove(f)    
    print 'Removed already existing files in Output Excel folder'

execfile('Validation.py')

