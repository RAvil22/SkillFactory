QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chat.cpp \
    contactwidget.cpp \
    main.cpp \
    autorization.cpp \
    messenger.cpp \
    newpassword.cpp \
    privatechat.cpp \
    publicchat.cpp \
    qmessagewidget.cpp \
    registration.cpp \
    singledialog.cpp \
    user.cpp \
    user_chats_create-remove.cpp \
    user_chats_display.cpp \
    user_chats_search.cpp \
    user_messages.cpp

HEADERS += \
    autorization.h \
    chat.h \
    chatExcept.h \
    contactwidget.h \
    message.h \
    messenger.h \
    newpassword.h \
    qmessagewidget.h \
    registration.h \
    singledialog.h \
    user.h

FORMS += \
    Registration.ui \
    autorization.ui \
    messenger.ui \
    newpassword.ui \
    singledialog.ui

TRANSLATIONS += \
    project_1_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
