#!/bin/bash
# Script to build image for qemu.
# Author: Siddhant Jajoo.

git submodule init
git submodule sync
git submodule update

# local.conf won't exist until this step on first execution
source poky/oe-init-build-env

LOCAL_CONF_FILE=conf/test_local.conf

CONFLINE="MACHINE = \"raspberrypi4-64\""

CONF_MACHINE="MACHINE = \"raspberrypi4-64\""
CONF_UART="ENABLE_UART = \"1\""
CONF_LIC="LICENSE_FLAGS_ACCEPTED += \"synaptics-killswitch\""
CONF_DLDIR="DL_DIR=\"${TOPDIR}/../../downloads\""
CONF_SSTATE="SSTATE_DIR=\"${TOPDIR}/../../sstate-cache\""
CONF_URI="CONNECTIVITY_CHECK_URIS = \"\""
CONF_EXTRA="EXTRA_IMAGE_FEATURES = \"ssh-server-dropbear allow-empty-password empty-root-password allow-root-login\""
CONF_INSTALL="IMAGE_INSTALL += \" net-tools\""
CONF_THREADS="BB_NUMBER_THREADS = \"\${@oe.utils.cpu_count()-1}\""
CONF_PARALLEL="PARALLEL_MAKE = \"-j ${BB_NUMBER_THREADS}\""

cat ${LOCAL_CONF_FILE} | grep "${CONFLINE}" > /dev/null
local_conf_info=$?

if [ $local_conf_info -ne 0 ];then
	echo "Append ${CONFLINE} in the local.conf file"
	echo ${CONF_MACHINE} >> ${LOCAL_CONF_FILE}
	echo ${CONF_UART} >> ${LOCAL_CONF_FILE}
	echo ${CONF_LIC} >> ${LOCAL_CONF_FILE}
	echo ${CONF_DLDIR} >> ${LOCAL_CONF_FILE}
	echo ${CONF_SSTATE} >> ${LOCAL_CONF_FILE}
	echo ${CONF_URI} >> ${LOCAL_CONF_FILE}
	echo ${CONF_EXTRA} >> ${LOCAL_CONF_FILE}
	echo ${CONF_INSTALL} >> ${LOCAL_CONF_FILE}
	echo ${CONF_THREADS} >> ${LOCAL_CONF_FILE}
	echo ${CONF_PARALLEL} >> ${LOCAL_CONF_FILE}
	
else
	echo "${CONFLINE} already exists in the local.conf file"
fi


bitbake-layers show-layers | grep "meta-raspberrypi" > /dev/null
layer_info=$?

if [ $layer_info -ne 0 ];then
	echo "Adding meta-raspberrypi layer"
	bitbake-layers add-layer ../meta-raspberrypi
else
	echo "meta-raspberrypi layer already exists"
fi

set -e
bitbake core-image-minimal
