#include "hospitalistation.h"

Hospitalistation::Hospitalistation(SubForm *parent) :
    SubForm(parent)
{
    create();
    setMyLayout();
    newTableFile();
}

Hospitalistation::~Hospitalistation()
{
}

void Hospitalistation::newTableFile()
{
    m_registry->newTableFile();
    m_account->setEnabled(false);
    m_account->init();
    m_charge->setEnabled(false);
    m_charge->init();
    m_leave->setEnabled(false);
    m_leave->init();
}

bool Hospitalistation::saveTableFile()
{
    if(m_registry->saveTableFile())
    {
        m_account->setEnabled(true);
        m_charge->setEnabled(true);
        m_leave->setEnabled(true);
        return true;
    }
    else
        return false;
}

bool Hospitalistation::deleteTableFile()
{
    return m_registry->deleteTableFile();
}

void Hospitalistation::exportTableFile()
{
    m_registry->exportTableFile();
}

bool Hospitalistation::findTableFile()
{
    if(m_registry->findTableFile())
    {
        m_account->setEnabled(true);
        m_charge->setEnabled(true);
        m_leave->setEnabled(true);
        return true;
    }
    else
        return false;
}

void Hospitalistation::amendTableFile()
{
    m_account->setEnabled(false);
    m_charge->setEnabled(false);
    m_leave->setEnabled(false);
    m_registry->amendTableFile(); 
}

void Hospitalistation::previewTableFile()
{
    m_registry->previewTableFile();
}

void Hospitalistation::printTableFile()
{
    m_registry->printTableFile();
}

void Hospitalistation::create()
{
    m_allInpaitent = new AllInpatientsForm;
    m_registry = new HospitalisationRegistry;
    m_account = new HospitalisationAccountForm;

    m_charge = new HospitalisationChargeForm;
    m_leave = new LeaveHospitalForm;

    connect(m_allInpaitent,SIGNAL(UpdateInpatientID(QString)),m_registry, SLOT(showInpatient(QString)));
    connect(m_registry, SIGNAL(inpatientIDChanged(QString)), m_account, SLOT(updateInpatientID(QString)));
    connect(m_registry, SIGNAL(inpatientIDChanged(QString)), m_charge, SLOT(updateInpatientID(QString)));
    connect(m_charge, SIGNAL(ChargeChanged()),m_account,SLOT(showRecords()));
    connect(m_account, SIGNAL(changePayIn(double,double)),m_leave,SLOT(updatePayIn(double,double)));
}

void Hospitalistation::setMyLayout()
{
    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(m_allInpaitent);

    QVBoxLayout *templeftLayout = new QVBoxLayout;
    templeftLayout->addWidget(m_account);
    QHBoxLayout *tempLayout = new QHBoxLayout;
    tempLayout->addLayout(templeftLayout);
    tempLayout->addWidget(m_leave);
    tempLayout->setStretchFactor(templeftLayout,1);


    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(m_registry);
    rightLayout->addWidget(m_charge);
    rightLayout->addLayout(tempLayout);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    mainLayout->setStretchFactor(rightLayout,1);

    setLayout(mainLayout);
}

void Hospitalistation::init()
{
}
