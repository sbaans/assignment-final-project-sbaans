# See https://git.yoctoproject.org/poky/tree/meta/files/common-licenses
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

FILESEXTRAPATHS:prepend := "${THISDIR}/../../audio_app:"
SRC_URI = "file://startdbus.sh file://Makefile file://audio_app.c"

PV = "1.0+git${SRCPV}"

SRCREV = "2901cd5b2e36b77ad34afbbc863cf8a73b2f6ee4"

S = "${WORKDIR}"

inherit update-rc.d

do_compile () {
	oe_runmake clean
	oe_runmake CFLAGS="${CFLAGS} -Wall -Werror" LDFLAGS="${LDFLAGS} -pthread"
}

INITSCRIPT_NAME = "startdbus"
INITSCRIPT_PARAMS = "defaults"
INITSCRIPT_PACKAGES = "${PN}"

do_install () {
	install -d ${D}${sysconfdir}/init.d
	install -m 0755 ${WORKDIR}/startdbus.sh ${D}${sysconfdir}/init.d/startdbus
	install -d ${D}${bindir}
	install -m 0755 ${WORKDIR}/audio_app ${D}${bindir}/audio_app
}


FILES:${PN} += "${sysconfdir}/init.d/startdbus ${bindir}/audio_app"
