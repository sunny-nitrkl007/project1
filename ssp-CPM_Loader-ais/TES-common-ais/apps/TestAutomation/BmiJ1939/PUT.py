from Config import*

target_path = "/opt/CPM/"

ECM_key = paramiko.RSAKey.from_private_key_file(A6N2_key_File_path,A6N2_Key_password)

class MySFTPClient(paramiko.SFTPClient):
    def put_dir(self, source, target):
        ''' Uploads the contents of the source directory to the target path. The
            target directory needs to exists. All subdirectories in source are 
            created under target.
        '''
        for item in os.listdir(source):
            if os.path.isfile(os.path.join(source, item)):
                self.put(os.path.join(source, item), '%s/%s' % (target, item))
            else:
                self.mkdir('%s/%s' % (target, item), ignore_existing=True)
                self.put_dir(os.path.join(source, item), '%s/%s' % (target, item))

    def mkdir(self, path, mode=511, ignore_existing=False):
        ''' Augments mkdir by adding an option to not fail if the folder exists  '''
        try:
            super(MySFTPClient, self).mkdir(path, mode)
        except IOError:
            if ignore_existing:
                pass
            else:
                raise

transport = paramiko.Transport((Host_IP, 22))
transport.connect(username = "root", password = A6N2_Key_password, pkey=ECM_key)
sftp = MySFTPClient.from_transport(transport)
sftp.mkdir(target_path, ignore_existing=True)
sftp.put_dir(source_path_put, target_path)
sftp.close()
