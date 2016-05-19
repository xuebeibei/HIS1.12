#include "hospitalinterpaymentform.h"

HospitalInterPaymentForm::HospitalInterPaymentForm()
{
    create();
    setMyLayout();
    init();
}

void HospitalInterPaymentForm::onSummarizing()
{
    QStringList strList;
    strList.append("门诊收据");
    strList.append("应收金额");
    initTable(strList);
}

void HospitalInterPaymentForm::onParticulars()
{
    QStringList strList;
    strList.append("门诊收据");
    strList.append("患者1");
    strList.append("患者2");
    strList.append("……");
    strList.append("患者n");
    strList.append("应收金额");
    initTable(strList);
}

void HospitalInterPaymentForm::create()
{
    m_conditionSortGroup = new QGroupBox;
    m_summarizing = new QRadioButton;
    m_summarizing->setText(QObject::tr("汇总"));
    connect(m_summarizing, SIGNAL(clicked(bool)), m_resultView, SLOT(onSummarizing()));
    m_particulars = new QRadioButton;
    m_particulars->setText(QObject::tr("明细"));
    connect(m_particulars, SIGNAL(clicked(bool)), m_resultView, SLOT(onParticulars()));
}

void HospitalInterPaymentForm::setMyLayout()
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

void HospitalInterPaymentForm::init()
{
    m_particulars->setChecked(true);
}

