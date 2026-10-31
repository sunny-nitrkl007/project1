from Config import*

source_path = "/opt/CPM/"

ECM_key = paramiko.RSAKey.from_private_key_file(A6N2_key_File_path,A6N2_Key_password)

transport = paramiko.Transport((Host_IP, 22))
transport.connect(username = "root", password = A6N2_Key_password, pkey=ECM_key)
sftp = paramiko.SFTPClient.from_transport(transport)

def downLoadFile(remotePath, localPath):
    for fileattr in sftp.listdir_attr(remotePath):
        if stat.S_ISDIR(fileattr.st_mode):
            source_path = remotePath+fileattr.filename+'/'
            target_path_get = localPath+fileattr.filename+'/'
            os.mkdir(target_path_get)
            downLoadFile(source_path,target_path_get)
        else:
            sftp.get(remotePath+fileattr.filename, localPath+fileattr.filename)

            
        
downLoadFile(source_path,target_path_get)  
