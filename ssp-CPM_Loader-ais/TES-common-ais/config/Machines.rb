require "socket"


module Machines

  # Get the Spoofed name if set
  thisHostname = CommonTaskParams::Parameters["spoofDnsName"];

  realHostname = getHostname()

  print "Host name is:", thisHostname,"\n"

  # if not spoofed, grab the real hostname
  if thisHostname == nil
    thisHostname = realHostname
  end

  print "Host name is:", thisHostname,"\n"

  onBoardA6N1Ecms      = ["A6N1"] # list of A6N1 ECMs
  onBoardA6N2Ecms      = ["A6N2", "CPM"] # list of A6N2 ECMs

  # Modify Machine Mapping based on hostname
  case thisHostname

  when *onBoardA6N2Ecms then
    puts "---------Using Machine configuration for A6N2 ECMs!"
    MachineMap = {
      "ecm"   => thisHostname,
      "ocs"    => "ocs",
    }
    MachineMap.default = thisHostname;

  when *onBoardA6N1Ecms then
    puts "---------Using Machine configuration for A6N1 ECMs!"
    MachineMap = {
      "ecm"   => "A6N1",
      "ocs"    => "ocs",
    }
    MachineMap.default = thisHostname;

  when "ocs"
    puts "---------Using OCS Machine configuration!"
    MachineMap = {
      "ecm"    => "A6N2",
      "ocs"    => realHostname,
    }
    MachineMap.default = realHostname;

  else
    puts "---------Using Default Machine configuration!"

    MachineMap = {
      "ecm"    => thisHostname,
      "ocs"    => thisHostname,
    }
    MachineMap.default = thisHostname;
  end
end
