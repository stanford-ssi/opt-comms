TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    opcommmessage.cpp \
    opcommmessagesend.cpp \
    opcommmessagereceive.cpp \
    opcommencryptionmethods.cpp \
    opcommchecksummethods.cpp

HEADERS += \
    opcommmessage.h \
    opcommmessagesend.h \
    opcommmessagereceive.h \
    opcommencryptionmethods.h \
    opcommchecksummethods.h

-std=gnu++11
