QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/asmexporter.cpp \
    src/cppexporter.cpp \
    src/customoptions.cpp \
    src/instruction_handler.cpp \
    src/mainwindow.cpp \
    src/memory.cpp \
    src/stack.cpp \
    main.cpp

HEADERS += \
    headers/asmexporter.h \
    headers/cppexporter.h \
    headers/customoptions.h \
    headers/exporter.h \
    headers/instruction_handler.h \
    headers/instructions.h \
    headers/mainwindow.h \
    headers/memory.h \
    headers/stack.h

FORMS += \
    GUI/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
