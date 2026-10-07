#!/bin/sh
### BEGIN INIT INFO
# Provides:             startdbus
# Required-Start:
# Required-Stop:
# Default-Start:        S
# Default-Stop:
### END INIT INFO

if test -z "$DBUS_SESSION_BUS_ADDRESS" ; then
     echo "Starting dbus" 
     export $(dbus-launch)
fi
