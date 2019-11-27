QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        auth/authorize.cpp \
        common.cpp \
        core/luna_core.cpp \
        core/service/alive_nodes_service.cpp \
        core/service/boardcast_service.cpp \
        core/service/file_control_service.cpp \
        core/service/file_transfer_service.cpp \
    extra/message_manager.cpp \
    extra/user_unit_for_view.cpp \
        io/database_handler.cpp \
        io/iocenter.cpp \
        main.cpp \
        network/tcp/tcp_client_handler.cpp \
        network/tcp/tcp_server.cpp \
        network/tcp/tcp_server_handler.cpp \
        network/tcp/tcp_server_private.cpp \
        network/udp/udp_client_handler.cpp \
        network/udp/udp_server_handler.cpp \
        utils/util.cpp \
    mainwindow.cpp

HEADERS += \
    extra/message_manager.h \
    extra/user_unit_for_view.h \
    mainwindow.h \
    auth/authorize.h \
    common.h \
    core/luna_core.h \
    core/service/alive_nodes_service.h \
    core/service/boardcast_service.h \
    core/service/file_control_service.h \
    core/service/file_transfer_service.h \
    io/database_handler.h \
    io/iocenter.h \
    network/tcp/tcp_client_handler.h \
    network/tcp/tcp_server.h \
    network/tcp/tcp_server_handler.h \
    network/tcp/tcp_server_private.h \
    network/udp/udp_client_handler.h \
    network/udp/udp_server_handler.h \
    utils/util.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
