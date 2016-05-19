#include "hospitalinternalpaymentform.h"

HospitalInternalPaymentForm::HospitalInternalPaymentForm(InternalPaymentForm *parent) :
    InternalPaymentForm(parent)
{
    create();
    setMyLayout();
    init();
}

HospitalInternalPaymentForm::~HospitalInternalPaymentForm()
{

}

void HospitalInternalPaymentForm::updateTable()
{
    QVector<InternalPaymentItem*> payments = ClinicInternalPayment::selectFromDB(m_startDateEdit->date(), m_endDateEdit->date());

    //initResults();
    for(int i = 0; i < payments.size() ; i++)
    {
        m_resultModel->setItem(i, 0, new QStandardItem(payments.at(i)->m_strName));
        m_resultModel->setItem(i, 1, new QStandardItem(QString::number(payments.at(i)->m_dDueIncome)));
    }
    updateIncome();
}

void HospitalInternalPaymentForm::onSummarizing()
{
    QStringList strList;
    strList.append("住院收据");
    strList.append("应收金额");
    initTable(strList);
    updateTable();
}

void HospitalInternalPaymentForm::onParticulars()
{
    QStringList strList;
    strList.append("住院收据");
    strList.append("患者1");
    strList.append("患者2");
    strList.append("……");
    strList.append("患者n");
    strList.append("应收金额");
    initTable(strList);
    updateTable();
}

void HospitalInternalPaymentForm::create()
{
    m_conditionSortGroup = new QGroupBox;
    m_summarizing = new QRadioButton;
    m_summarizing->setText(QObject::tr("汇总"));
    connect(m_summarizing, SIGNAL(clicked(bool)), this, SLOT(onSummarizing()));
    m_particulars = new QRadioButton;
    m_particulars->setText(QObject::tr("明细"));
    connect(m_particulars, SIGNAL(clicked(bool)), this, SLOT(onParticulars()));

    connect(m_startDateEdit, SIGNAL(dateChanged(QDate)),this, SLOT(updateTable()));
    connect(m_endDateEdit, SIGNAL(dateChanged(QDate)),this, SLOT(updateTable()));
}

void HospitalInternalPaymentForm::setMyLayout()
{
    QGridLayout *leftTopLayout = new QGridLayout;
    leftTopLayout->addWidget(m_particulars,0,0);
    leftTopLayout->addWidget(m_summarizing,0,1);
    leftTopLayout->addWidget(m_startDateLabel,1,0);
    leftTopLayout->addWidget(m_startDateEdit,1,1);
    leftTopLayout->addWidget(m_endDateLabel,2,0);
    leftTopLayout->addWidget(m_endDateEdit,2,1);
    leftTopLayout->addWidget(m_allDueIncomeLabel,3,0);
    leftTopLayout->addWidget(m_allDueIncomeEdit,3,1);

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

void HospitalInternalPaymentForm::init()
{
    m_particulars->setChecked(true);
    onParticulars();
}
