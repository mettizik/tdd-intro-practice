TEMPLATE = subdirs

SUBDIRS += \
    workshops \
    homework \
    3rd_party

homework.depends = 3rd_party
workshops.depends = 3rd_party
