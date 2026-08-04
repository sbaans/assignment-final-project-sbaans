#!/bin/sh

if test -z "$DBUS_SESSION_BUS_ADDRESS" ; then
     echo "Starting dbus" 
     export $(dbus-launch)
fi
