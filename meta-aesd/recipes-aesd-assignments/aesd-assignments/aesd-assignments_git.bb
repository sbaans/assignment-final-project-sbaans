# See https://git.yoctoproject.org/poky/tree/meta/files/common-licenses
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"


SRC_URI = "file://startdbus.sh"

PV = "1.0+git${SRCPV}"

SRCREV = "2901cd5b2e36b77ad34afbbc863cf8a73b2f6ee4"

S = "${WORKDIR}"

inherit update-rc.d


do_install () {
	install -m 0755 ${WORKDIR}/startdbus.sh ${D}/etc/init.d/startdbus.sh
}

INITSCRIPT_NAME = "startdbus"

FILES:${PN} = "/etc/init.d/startdbus.sh"