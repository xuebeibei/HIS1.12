#include "clinicinternalpaymentform.h"

ClinicInternalPaymentForm::ClinicInternalPaymentForm(InternalPaymentForm *parent) :
    InternalPaymentForm(parent)
{
    create();
    setMyLayout();
    init();
    updateTable();
}

ClinicInternalPaymentForm::~ClinicInternalPaymentForm()
{
}

void ClinicInternalPaymentForm::create()
{
    connect(m_startDateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(updateTable()));
    connect(m_endDateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(updateTable()));
}

void ClinicInternalPaymentForm::init()
{
    initResults();
    m_startDateEdit->setDate(QDate::currentDate());
    m_endDateEdit->setDate(QDate::currentDate());
}

void ClinicInternalPaymentForm::setMyLayout()
{
    QGridLayout *leftTopLayout = new QGridLayout;
    leftTopLayout->addWidget(m_startDateLabel,0,0);
    leftTopLayout->addWidget(m_startDateEdit,0,1);
    leftTopLayout->addWidget(m_endDateLabel,1,0);
    leftTopLayout->addWidget(m_endDateEdit,1,1);
    leftTopLayout->addWidget(m_allDueIncomeLabel,2,0);
    leftTopLayout->addWidget(m_allDueIncomeEdit,2,1);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(leftTopLayout);

    leftLayout->addStretch();

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(m_resultView);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    mainLayout->setStretchFactor(rightLayout,1);

    setLayout(mainLayout);
}

void ClinicInternalPaymentForm::initResults()
{
    QStringList strList;
    strList.append(QObject::tr("门诊收据"));
    strList.append(QObject::tr("应收金额"));
    initTable(strList);
}

void ClinicInternalPaymentForm::updateTable()
{
    QVector<InternalPaymentItem*> payments = ClinicInternalPayment::selectFromDB(m_startDateEdit->date(), m_endDateEdit->date());

    initResults();
    for(int i = 0; i < payments.size() ; i++)
    {
        m_resultModel->setItem(i, 0, new QStandardItem(payments.at(i)->m_strName));
        m_resultModel->setItem(i, 1, new QStandardItem(QString::number(payments.at(i)->m_dDueIncome)));
    }
    updateIncome();
}

