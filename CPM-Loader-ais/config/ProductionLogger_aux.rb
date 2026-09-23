# Override the defaults provided by eta-ais
Parameters.update( {
  # The rate that we flush data to disk. This is a different thread, and doesn't
  # need to be particularly fast, to allow data to build up in the cache. Make
  # this higher if your cache size is small.
  "flushRate_hz" => 0.0083,

  # The size of the memory cache. Roughly, this will correspond to how much data
  # you can keep in memory when the disk dies. If this is 100MB, and you log at
  # 10MB/second, then you can keep 10 seconds worth of data in memory.
  "cacheSize_mb" => 32,

  # The maximum amount of disk space the logger will attempt to use. If set at
  # zero, this will attempt to use every bit of free space it can find. If this
  # is set at less than zero, it will use all of the space up to the drive
  # maximum, reserving the space given (ie, setting to -20 will reserve 20gb
  # on the drive for "other" things)
  "maximumUsableDiskSpace_gb" => -4.0, # floating point value is supported

  # Determines the use of fsync() when writing logs out. Using fsync() may make
  # the log writing more deterministic and less data loss in a catastrophic failure,
  # but can also negatively impact the system as a whole.
  "useFsync" => false,
} )

