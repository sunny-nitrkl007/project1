from Validation import*
Json_fail = []
for i in range(len(JSON_Simulation_FAIL)):
    Json_fail.append(JSON_Simulation_FAIL[i])
print ('Json_fail',Json_fail)

if not Json_fail:
    print "-----------------------------"
    print "TESTING COMPLETE"
    print "-----------------------------"
else:
    print "TESTING FAILED JSON FILE"
    
    from Config import*

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

  
    ''' Json_files has the list of .json files present in the Json file path given '''
    Json_files = glob.glob(Json_File_path+"*.json")
    ## Total number of Json Files
    Json_files_count = len(Json_files)

    def Change_json_file(Request_file):
        ''' Change_json_file uploads the Test json file from local path to all the json
            files in the server path'''
        for filename in sftp.listdir('/opt/CPM/config'):
            if fnmatch.fnmatch(filename, "*.json"):
                Json_Filename = '/opt/CPM/config/' + filename
                Test_Filename = Json_File_path+Request_file
                sftp.put(Test_Filename,Json_Filename)

    global stop_thread
    global GPS_Data,ProductID_Data,Time_zone

    ##############################################
    ### Threads that run continously with a
    ### particular time period
    ##############################################
    def GPS_Data_simulation():
        ''' This thread send the data for GPS location for every one sec.
             The execution time of the thread is configurable  '''
        global GPS_Data,ProductID_Data,Time_zone
        threading.Timer(0.2, GPS_Data_simulation).start()
        if stop_thread == 'false':        
            telematics.Simulation.SendrawCDL(GPS_Data)

    def ProductID_Data_simulation():
        ''' This thread send the data for Product ID for every one sec.
             The execution time of the thread is configurable  '''
        global GPS_Data,ProductID_Data,Time_zone
        threading.Timer(0.2, ProductID_Data_simulation).start()
        if stop_thread == 'false':
            telematics.Simulation.SendrawCDL(ProductID_Data)

    def Time_zone_simulation():
        ''' This thread send the data for Time Zone for every one sec.
             The execution time of the thread is configurable  '''
        global GPS_Data,ProductID_Data,Time_zone
        threading.Timer(0.2, Time_zone_simulation).start()
        if stop_thread == 'false':
            telematics.Simulation.SendrawCDL(Time_zone)
        
    ##############################################
    ### Simulates the test input Data
    ##############################################
    def Input_simulator(Test_case,Input_filename):
        global GPS_Data,ProductID_Data,Time_zone
        global i
        i = Test_case + 4
        workbook = xlrd.open_workbook(Input_filename)
        sheet = workbook.sheet_by_index(0)
        for row in range(1,sheet.nrows):
            if sheet.cell_value(row,2) == 'I':
                param_name = sheet.cell_value(row,0)
                param_name = (param_name.encode('ascii', 'ignore'))
                pid_data = sheet.cell_value(row,i)
                telematics.Simulation.set_parameter(param_name,pid_data)
            if sheet.cell_value(row,2) == '':
                pid = sheet.cell_value(row,1)
                pid_data = sheet.cell_value(row,i)
                pid_data = (pid_data.encode('ascii', 'ignore'))
                if sheet.cell_value(row,1)=='f84d':
                    GPS_Data = 'A1 37 '+'F84D'+' '+'0E '+pid_data
                if sheet.cell_value(row,1)=='fa27':
                    Time_zone = 'A1 37 '+'FA27'+' '+'13 '+pid_data
                if sheet.cell_value(row,1)=='f82d':
                    ProductID_Data = 'A1 37 '+'F82D'+' '+'08 '+pid_data
                

    
    print ('JSON_FILE - FAIL LIST',Json_fail)

    ECM_key = paramiko.RSAKey.from_private_key_file(A6N2_key_File_path,A6N2_Key_password)
    ECM_connect = paramiko.SSHClient()
    ECM_connect.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    ECM_connect.connect(hostname=Host_IP,port=22,username="root",pkey=ECM_key)
    sftp = ECM_connect.open_sftp()

    for i in range(len(Json_fail)):
        print str(Json_fail[i])+'_AutomationOutput.csv'
        Test = Json_fail[i]
        ''' stop_thread given false to start the Simulation for variable length PID '''
        stop_thread = 'false'


        ''' This is the default data being sent for the PIDS - GPS_Data(F84D),
            Product_ID(F82D) & Time_zone(FA27) until there is some data being sent '''

        GPS_Data = 'A1 37 F84D 0E 21 22 23 24 25 26 28 28 29 30 31 61 62 63'
        ProductID_Data = 'A1 37 F82D 08 54 34 50 31 32 33 34 35'
        Time_zone = 'A1 37 FA27 13 3A 3B 3C 3D 41 42 43 44 45 46 47 48 49 4A 4B 5B 5C 5D 5E'

        #############################################
        ## Copy the Test Json File into ECM
        #############################################
        Change_json_file('BmiCdl_Test_'+str(Test)+'.json')

        print '------------------------------'
        print 'BmiCdl_Test_'+str(Test)+'.json'
        print '------------------------------'
        print 'STEP 6 : Copying Test JSON File'
    
        #############################################
        ## Enable ECM Simulation
        #############################################
        ''' The XML file containing the PIDs to be simulated is configured with Vbench
            simulator'''
        telematics.Simulation.configure(XML_File_path+'CDL_Test_XML_'+str(Test)+'.xml')
        mydoc = minidom.parse(XML_File_path+'CDL_Test_XML_'+str(Test)+'.xml')
        items = mydoc.getElementsByTagName('module')
        for elem in items:
            ECM_name = (elem.attributes['name'].value)
            telematics.Simulation.add_ecm_to_network(ECM_name)
            time.sleep(2)
        
        print 'STEP 7 : XML File Configure'
    
        #############################################
        ## CDL simulation for variable length data
        #############################################
        GPS_Data_simulation()
##      ProductID_Data_simulation()
        Time_zone_simulation()
        print 'STEP 8 : Start Variable length PID Simulation'
    
        ###########################################
        ## Running BMI & SCS
        ###########################################
        ''' Changing the mode in the CPM/bin/ path in the ECM and running the
             application BmiCdl and scs in release mode'''  
        mount = 'mount -o remount,exec /opt/'
        stdin, stdout, stderr = ECM_connect.exec_command(mount)
        stdin, stdout, stderr = ECM_connect.exec_command('chmod -R 777 /opt/CPM/bin/')
        stdin, stdout, stderr = ECM_connect.exec_command('cd /opt/CPM/;. changeCatEnvToHere.sh;export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/CPM/usr/lib;/opt/CPM/bin/scs')
        stdin, stdout, stderr = ECM_connect.exec_command('cd /opt/CPM/;. changeCatEnvToHere.sh;export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/opt/CPM/usr/lib;/opt/CPM/bin/bmiCdl >/opt/cdl.txt')
        time.sleep(5)
        print 'STEP 9 : Running BMI_CDL & SCS Application'
        time.sleep(5)
    
        #############################################
        ### Test Data Simulation
        #############################################
        print 'STEP 10 : Simulation START with the Input Test data'
        for Data in range(Test_input_count):
            Input_simulator(0,InputCSV_File_path)
            time.sleep(2)
            Input_simulator(Data+1,InputCSV_File_path)
            time.sleep(2)
        Input_simulator(0,InputCSV_File_path)
        time.sleep(2)
        print 'STEP 10 : Simulation DONE with the Input Test data'

        #############################################
        ## Disable ECM Simulation
        #############################################    
        mydoc1 = minidom.parse(XML_File_path+'CDL_Test_XML_'+str(Test)+'.xml')
        items1 = mydoc1.getElementsByTagName('module')
        for elem in items1:
            ECM_name1 = (elem.attributes['name'].value)
            ECM_name1 = (ECM_name1.encode('ascii', 'ignore'))
            telematics.Simulation.remove_ecm_from_network(ECM_name1)
            time.sleep(2)
        stop_thread = 'true'
        print 'STEP 11 : Stop Simulation from all the ECM'
        time.sleep(5)
    
        #############################################
        ### FILE CREATION
        #############################################
        OutputFileName = str(Test)+'_AutomationOutput.csv'
        OutputFilePath = Output_File_path+OutputFileName
        f_obj = open(OutputFilePath,"w")
        time.sleep(5)
        sftp.get('/opt/tmp/outputFiles/AutomationData.csv',OutputFilePath)
        f_obj.close()
        print 'STEP 12 : OUTPUT File creation'

        #############################################
        ## Kill BMI-CDL & SCS application
        ############################################# 
        stdin, stdout, stderr = ECM_connect.exec_command('cd /opt/;killall -9 scs')
        time.sleep(2)
        stdin, stdout, stderr = ECM_connect.exec_command('cd /opt/;killall -9 bmiCdl')
        time.sleep(2)
        print 'STEP 13 : BMI_CDL & SCS Application Killed'

        sftp.remove('/opt/tmp/outputFiles/AutomationData.csv')
        print 'STEP 14 : CSV File created in ECM removed'
        time.sleep(10)

    execfile('Validation.py')
