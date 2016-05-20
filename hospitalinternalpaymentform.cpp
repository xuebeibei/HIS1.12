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


void HospitalInternalPaymentForm::onSummarizing()
{
    initResults();

    QVector<InternalPaymentItem*> payments = InternalPayment::selectFromDB(HospitalInPatient,m_startDateEdit->date(), m_endDateEdit->date());
    for(int i = 0; i < payments.size() ; i++)
    {
        m_resultModel->setItem(i, 0, new QStandardItem(payments.at(i)->m_strName));
        m_resultModel->setItem(i, 1, new QStandardItem(QString::number(payments.at(i)->m_dDueIncome)));
    }
    updateIncome();
}

void HospitalInternalPaymentForm::onParticulars()
{
    initResults();

    QVector<QVector<QString> > *dueIncome = new QVector<QVector<QString> >;

    dueIncome = InternalPayment::selectFromDB(
                m_startDateEdit->date(),
                m_endDateEdit->date(),
                "HospitalReceipt",
                g_strChargeDetails,
                "HospitalID",
                g_strAccount);

    if(dueIncome == NULL)
        return;

    for(int nIndexReceipt = 0;nIndexReceipt<dueIncome->size();nIndexReceipt++)
    {
        double all = 0.0;
        QVector<QString> temp = dueIncome->at(nIndexReceipt);
        for(int nIndexPatient = 0;nIndexPatient<temp.size();nIndexPatient++)
        {
            if(nIndexReceipt == 0)
            {
                m_resultModel->setHorizontalHeaderItem(nIndexPatient+1, new QStandardItem(Inpatient::getNameByID(temp.at(nIndexPatient))));

            }
            else if( nIndexReceipt > 0)
            {
                m_resultModel->setItem(nIndexReceipt-1, nIndexPatient, new QStandardItem(temp.at(nIndexPatient)));
                if(nIndexPatient!=0)
                     all += temp.at(nIndexPatient).toDouble();
            }

        }
        if(nIndexReceipt == 0)
        {
            m_resultModel->setHorizontalHeaderItem(temp.size()+1, new QStandardItem("合计"));
        }
        else if(nIndexReceipt > 0)
        {
            m_resultModel->setItem(nIndexReceipt-1, temp.size(), new QStandardItem(QString::number(all)));
        }

    }

    updateIncome();
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

    m_allDueIncomeEdit->setReadOnly(true);
    m_allDueIncomeEdit->setStyleSheet(g_strLineEditNoBorder);
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

void HospitalInternalPaymentForm::initResults()
{
    QStringList strList;
    strList.append("住院收据");
    strList.append("应收金额");
    initTable(strList);
    m_allDueIncomeEdit->setText(g_strNull);
}
