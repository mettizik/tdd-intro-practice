TEMPLATE = subdirs

SUBDIRS += \
    workshops \
    homework \
    3rd_party \
    cleanroom

homework.depends = 3rd_party
workshops.depends = 3rd_party
cleanroom.depends = 3rd_party
