#-------------------------------------------------
#
# Project created by QtCreator 2016-04-12T10:30:17
#
#-------------------------------------------------

QT       += core gui
QT += sql
QT += xml
PRECOMPILED_HEADER = stdafx.h

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
    findclincchargedlg.cpp \
    clinicdailyreportform.cpp \
    clinicdailyreporttable.cpp \
    clinicinternalpaymentform.cpp \
    clinicchargestatisticform.cpp \
    clinicreportstatisticform.cpp \
    clinicpaymentstatisticform.cpp \
    finddailyreportdialog.cpp \
    hospitalisationregistry.cpp \
    inpatient.cpp \
    account.cpp \
    contacts.cpp \
    finddlg.cpp \
    findregistrydlg.cpp \
    hospitalistation.cpp \
    hospitalisationaccountform.cpp \
    hospitalisationchargeform.cpp \
    leavehospitalform.cpp \
    allinpatientsform.cpp \
    clinicchargeform.cpp \
    chargeitem.cpp \
    hospitalchargetable.cpp \
    chargetable.cpp \
    chargeform.cpp \
    findhospitalchargedlg.cpp \
    internalpaymentform.cpp \
    hospitalinternalpaymentform.cpp \
    internalpayment.cpp

HEADERS  += hismainwindow.h \
    stdafx.h \
    subform.h \
    winSet.h \
    histable.h \
    persion.h \
    patient.h \
    clinicchargetable.h \
    connectDB.h \
    findclincchargedlg.h \
    clinicchargeform.h \
    clinicdailyreportform.h \
    clinicdailyreporttable.h \
    clinicinternalpaymentform.h \
    clinicchargestatisticform.h \
    clinicreportstatisticform.h \
    clinicpaymentstatisticform.h \
    finddailyreportdialog.h \
    hospitalisationregistry.h \
    inpatient.h \
    account.h \
    contacts.h \
    finddlg.h \
    findregistrydlg.h \
    hospitalistation.h \
    hospitalisationaccountform.h \
    hospitalisationchargeform.h \
    leavehospitalform.h \
    allinpatientsform.h \
    chargeitem.h \
    hospitalchargetable.h \
    chargetable.h \
    chargeform.h \
    findhospitalchargedlg.h \
    internalpaymentform.h \
    hospitalinternalpaymentform.h \
    internalpayment.h

FORMS    +=

OTHER_FILES +=

RESOURCES += \
    pic.qrc
