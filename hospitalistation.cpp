#include "hospitalistation.h"

Hospitalistation::Hospitalistation(QWidget *parent) :
    QWidget(parent)
{
    create();
    setMyLayout();
}

void Hospitalistation::create()
{
    m_allInpaitent = new AllInpatientsForm;
    m_registry = new HospitalisationRegistry;
    m_account = new HospitalisationAccountForm;
    m_charge = new HospitalisationChargeForm;
    m_leave = new LeaveHospitalForm;
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
