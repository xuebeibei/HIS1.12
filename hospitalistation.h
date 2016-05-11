#ifndef HOSPITALISTATION_H
#define HOSPITALISTATION_H

#include <QWidget>
#include "stdafx.h"
#include "hospitalisationregistry.h"
#include "hospitalisationaccountform.h"
#include "hospitalisationchargeform.h"
#include "leavehospitalform.h"
#include "allinpatientsform.h"

class Hospitalistation : public QWidget
{
    Q_OBJECT
public:
    explicit Hospitalistation(QWidget *parent = 0);
    
protected:
    void create();
    void setMyLayout();

signals:
    
public slots:

protected:

    AllInpatientsForm *m_allInpaitent;
    HospitalisationRegistry *m_registry;
    HospitalisationAccountForm *m_account;
    HospitalisationChargeForm *m_charge;
    LeaveHospitalForm *m_leave;
};

#endif // HOSPITALISTATION_H
