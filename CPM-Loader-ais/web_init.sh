# Make sure the app is present

if [ ! -f $1 ]
then
   exit 1
fi
   
# Register menu entries with the Web Manager.  The first argument to this script
# ($1) is the path to the menu register application.  The two sets of arguments 
# to the menu register application are as follows:

# $1 APP_NAME LINK_MENU_NAME LINK_MENU_PATH
# $1 APP_NAME DROPDOWN_MENU_NAME DROPDOWN_SUBMENU_NAME DROPDOWN_SUBMENU_PATH

# APP_NAME:
#    Name of application.  This should be the same as the verity image's mounted
#    directory name (e.g. OurApp_02013052301.verity would have an application
#    name of OurApp)
# LINK_MENU_NAME:
#    Menu name for a single link (non-dropdown) menu entry
# LINK_MENU_PATH
#    Path to link target relative to application web root (www folder)
# DROPDOWN_MENU_NAME:
#    Toplevel menu name for a Dropdown menu entry
# DROPDOWN_SUBMENU_NAME
#    Submenu name for a Dropdown menu entry
# DROPDOWN_SUBMENU_PATH
#    Path to dropdown menu link target relative to application web root (www folder)

/bin/echo "Registering Service Dashboard with $1"
$1 CPM "Payload" ServiceDashboard/index.html
