FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

PV = "1.9.11+git"
SRCREV = "ba8887e5f1e922f866681ec7dec1a00b602a9328"
SRC_URI:remove = "file://0001-configure-Prune-PIE-flags.patch"
SRC_URI:remove:class-native = "file://older-glibc-symbols.patch"
SRC_URI:append:class-native = " file://older-glibc-symbols-pseudo-1.9.11.patch"
SRC_URI:remove:class-nativesdk = "file://older-glibc-symbols.patch"
SRC_URI:append:class-nativesdk = " file://older-glibc-symbols-pseudo-1.9.11.patch"