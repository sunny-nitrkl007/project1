module Widgets

  # All Plugin Widgets in Pathfinder system
  AllWidgets.update ({
    "DataLinkDataPlugin" =>
    {
      "interface" => "DataLinkDataPlugin",
      "displayName" => "DataLinkData Monitor",
      "category" => 1, # infrastructure
    },

    "PWMInputPlugin" =>
    {
      "interface" => "PWMInputPlugin",
      "displayName" => "PWMInput App",
      "category" => 1, # infrastructure
    },
    # Add new plugin definitions above this line
  })
end
