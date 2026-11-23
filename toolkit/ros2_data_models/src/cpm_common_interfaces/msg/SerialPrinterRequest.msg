################################################################################
# SerialPrinterRequestInterfaceCommand
################################################################################

uint8 PRINT=0
uint8 TEST=1

################################################################################
# SerialPrinterRequestInterfaceStorage
################################################################################

uint8 command
string file_path
# Preserve the legacy accessor semantics in consumers: min(value, 3); zero prints nothing.
uint8 number_of_copies
