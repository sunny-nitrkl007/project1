# Override eta-ais parameters if desired
Parameters.update( {
  # "loggerThreshold" => "warn",

  # We need to wait for time to come in before we start logging, otherwise,
  # some of our filenames will be off. This is really only important for the
  # case of returning proper error codes to the end user when a time is way
  # out of range.
  # "requireGPSTimeSynchronizationOnStart" => true,
  
  # The rate that we service data coming in over SCS. Should be high. This keeps
  # data from sitting (or dropping) off SCS queues.
  # "cycleRate_hz" => 50,   
  
  # The rate that we flush data to disk. This is a different thread, and doesn't
  # need to be particularly fast, to allow data to build up in the cache. Make
  # this higher if your cache size is small.
  "flushRate_hz" => 40,

  # The rate that we rescan the dataset (and snapshots) from disk. Scanning the
  # dataset can be CPU intensive, so raise this limit at your own risk.
  # "rescanRate_hz" => 1,
  
  # The size of the memory cache. Roughly, this will correspond to how much data
  # you can keep in memory when the disk dies. If this is 100MB, and you log at
  # 10MB/second, then you can keep 10 seconds worth of data in memory.
  "cacheSize_mb" => 64,
  
  # The size of individual blocks. You should not need to change this. Smaller
  # blocks cause more overhead and fragmentation, but are (perhaps) more efficient
  # to be written out.
  # "blockSize_kb" => 256,
  
  # The size of split files for tables. Preference. This limit is hard-obeyed.
  # "tableSplitFileSize_mb" => 256,
  
  # The maximum amount of disk space the logger will attempt to use. If set at
  # zero, this will attempt to use every bit of free space it can find. If this
  # is set at less than zero, it will use all of the space up to the drive
  # maximum, reserving the space given (ie, setting to -20 will reserve 20gb
  # on the drive for "other" things)
  # "maximumUsableDiskSpace_gb" => -2.0, # floating point value is supported

  # The maximum amount of disk space the logger can use for snapshots. If the
  # amount of data snapshotted exceeds this value, then attempts to create new
  # snapshots will fail.
  "maximumSnapshotDiskSpace_percent" => 40.0,

  # This is the threshold that we will throw up a warning autonomy condition at.
  "warningSnapshotDiskSpace_percent" => 35.0,

  # This is the threshold that we will throw up a warning autonomy condition at,
  # if the cache has reached some critical level (ie, a disk is not present).
  # "warningCacheSpace_percent" => 75.0,
  
  # Determines the use of fsync() when writing logs out. Using fsync() may make
  # the log writing more deterministic and less data loss in a catastrophic failure,
  # but can also negatively impact the system as a whole.
  # "useFsync" => true,

  # When fsync() is enabled, this determines the maximum number of bytes that can
  # be written out with write() before fsync() is called. This can level out some
  # write performance cases, at the expense of slightly higher disk latency. Set
  # to zero to disable.
  # "bytesWrittenPerFsync_kb" => 4096,
  
  # The path to write logs out to.
  # "logOutputPath" => ENV[ 'HOME' ] + "/log/productionLogs",
  
  # Path to the write suppression file. If this is set, and this file exists, all
  # disk writes are disabled. This prevents us from writing to the flash card when
  # the logging drive is unmounted.
  # "writeSuppressionPath" => ENV[ 'HOME' ] + "/log/UNMOUNTED",

  # Defines the maximum time delta, in seconds, that a datum can have to our
  # local clock. If it is outside of this range, the data will not be logged.
  # Set to zero to disable the filter and log all datums.
  "maximumDatumTimeDelta_seconds" => 0,

  # Temporary variable, to help me with debugging.
  # "indexGenerationEnabled" => false,

  # Temporary configuration variable -- Enable/disable ProductionLogger's logging of the config.tar.gz file with the log set. 
  # This shouldn't be needed now that we are logging directly in datum format.
  # "logConfigTarball" => false,

  # When set to anything except passthrough the given compressor will be used to
  # compress any datum not already compressed and not on the do not compress
  # list.  Recommended values => passthrough, lz4, snappy (see hub compression
  # for the full list).
  # "defaultDatumCompression" => InterfaceDefs::DefaultCompression,

  # Channel on this list will not be compressed, no matter what the value of
  # dafaultDatumCompression is.
  # "doNotCompressChannels" => [
  #                             "CameraImage.Channel",
  #                             "OCSCameraImage.Channel",
  #                            ]
} )
