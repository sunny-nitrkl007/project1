from Config import*

''' Configures the private key in the path given'''
ECM_key = paramiko.RSAKey.from_private_key_file(A6N2_key_File_path,A6N2_Key_password)
''' TO establish a connection with the ECM by SSH into ECM'''
ECM_connect = paramiko.SSHClient()
ECM_connect.set_missing_host_key_policy(paramiko.AutoAddPolicy())
print "ECM connecting"
ECM_connect.connect(hostname=Host_IP,port=22,username="root",pkey=ECM_key)
print "ECM connected"
sftp = ECM_connect.open_sftp()

print 'STEP 1 : Extracting CPM folder from ECM'
execfile('GET.py')

############################################
##To remove Verity from the ECM
############################################
    
sftp.remove('/opt/'+Verity_name+'.verity')
sftp.remove('/opt/'+Verity_name+'.verity_verify')
sftp.remove('/opt/'+Autostart_name+'.verity')
sftp.remove('/opt/'+Autostart_name+'.verity_verify')
print 'STEP 2 : Removed Verity from ECM'

##############################################
### Reboot ECM
##############################################
print 'STEP 3 : ECM Rebooting'
stdin, stdout, stderr = ECM_connect.exec_command('/sbin/reboot')
time.sleep(80)
ECM_connect.close()
print 'STEP 3 : ECM Reboot Done'

print 'STEP 4 : Uploading CPM folder to ECM'
execfile('PUT.py')
############################################
### Change Default robot File & JSON file
############################################
ECM_key = paramiko.RSAKey.from_private_key_file(A6N2_key_File_path,A6N2_Key_password)
ECM_connect = paramiko.SSHClient()
ECM_connect.set_missing_host_key_policy(paramiko.AutoAddPolicy())
print "ECM connecting"
ECM_connect.connect(hostname=Host_IP,port=22,username="root",pkey=ECM_key)
print "ECM connected"

sftp = ECM_connect.open_sftp()
mount = 'mount -o remount,exec /opt/'
stdin, stdout, stderr = ECM_connect.exec_command(mount)
stdin, stdout, stderr = ECM_connect.exec_command('chmod -R 777 /opt/CPM/')

for filename in sftp.listdir('/opt/CPM/config'):
    if fnmatch.fnmatch(filename, "Robot_Default.rb"):
        Robot_Filename = '/opt/CPM/config/' + filename
        Test_Filename = Robot_file_path
        sftp.put(Test_Filename,Robot_Filename)
print 'STEP 5 : Robot file changed'
time.sleep(5)
execfile('Protocol_Test.py')
