TARGET = tst_qtriangle3d
CONFIG += testcase
TEMPLATE=app
QT += testlib 3d

SOURCES += tst_qtriangle3d.cpp
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
CONFIG+=insignificant_test  # See QTBUG-27189
