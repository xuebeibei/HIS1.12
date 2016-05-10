#-------------------------------------------------
#
# Project created by QtCreator 2016-04-12T10:30:17
#
#-------------------------------------------------

QT       += core gui
QT += sql
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HIS
TEMPLATE = app


SOURCES += main.cpp\
        hismainwindow.cpp \
    subform.cpp \
    histable.cpp \
    persion.cpp \
    patient.cpp \
    clinicchargetable.cpp \
    clinicchargeitem.cpp \
    findclincchargedlg.cpp \
    clinicchargeform.cpp \
    clinicdailyreportform.cpp \
    clinicdailyreporttable.cpp \
    clinicinternalpaymentform.cpp \
    clinicinternalpayment.cpp \
    clinicchargestatisticform.cpp \
    clinicreportstatisticform.cpp \
    clinicpaymentstatisticform.cpp \
    finddailyreportdialog.cpp \
    hospitalisationregistry.cpp \
    inpatient.cpp \
    account.cpp \
    contacts.cpp \
    finddlg.cpp \
    findregistrydlg.cpp

HEADERS  += hismainwindow.h \
    stdafx.h \
    subform.h \
    winSet.h \
    histable.h \
    persion.h \
    patient.h \
    clinicchargetable.h \
    connectDB.h \
    clinicchargeitem.h \
    findclincchargedlg.h \
    clinicchargeform.h \
    clinicdailyreportform.h \
    clinicdailyreporttable.h \
    clinicinternalpaymentform.h \
    clinicinternalpayment.h \
    clinicchargestatisticform.h \
    clinicreportstatisticform.h \
    clinicpaymentstatisticform.h \
    finddailyreportdialog.h \
    hospitalisationregistry.h \
    inpatient.h \
    account.h \
    contacts.h \
    finddlg.h \
    findregistrydlg.h

FORMS    +=

OTHER_FILES +=

RESOURCES +=
