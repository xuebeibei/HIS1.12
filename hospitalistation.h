#ifndef HOSPITALISTATION_H
#define HOSPITALISTATION_H

#include <QWidget>
#include "stdafx.h"
#include "hospitalisationregistry.h"
#include "hospitalisationaccountform.h"
#include "hospitalisationchargeform.h"
#include "leavehospitalform.h"
#include "allinpatientsform.h"
#include "inpatient.h"
#include "subform.h"

class Hospitalistation : public SubForm
{
    Q_OBJECT
public:
    explicit Hospitalistation(SubForm *parent = 0);
    ~Hospitalistation();

    void newTableFile();
    bool saveTableFile();
    bool deleteTableFile();
    void exportTableFile();
    bool findTableFile();
    void amendTableFile();
    void previewTableFile();
    void printTableFile();

protected:
    void create();
    void setMyLayout();
    void init();
    
protected:

    AllInpatientsForm *m_allInpaitent;
    HospitalisationRegistry *m_registry;
    HospitalisationAccountForm *m_account;
    HospitalisationChargeForm *m_charge;
    LeaveHospitalForm *m_leave;

    //Inpatient *m_patient;
};

#endif // HOSPITALISTATION_H
