require "CoachingTask_Base.rb"

# Add application specific interfaces
Interfaces.update( {
} )

Parameters.update( {
  # Add application specific parameters

  # Override default parameters
} )

# Load scenario specific Interfaces and Parameters
loadInstanceAuxFile(__FILE__)
