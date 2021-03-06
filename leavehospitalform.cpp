#include "leavehospitalform.h"

LeaveHospitalForm::LeaveHospitalForm(QWidget *parent) :
    QWidget(parent)
{
    create();
    setMyLayout();
    init();
    setMinimumWidth(180);
}

LeaveHospitalForm::~LeaveHospitalForm()
{
}

void LeaveHospitalForm::updatePayIn(double dPayIn, double dConsume)
{
     double dBalance = 0.0;

     dBalance = dPayIn - dConsume;
     m_allPayInEdit->setText(QString::number(dPayIn));
     m_allChargeEdit->setText(QString::number(dConsume));
     m_allBalanceEdit->setText(QString::number(dBalance));
     if(dBalance > 0)
     {
         m_payInArrearsButton->setText("退款");
         m_payInArrearsButton->setEnabled(true);
     }
     else if(dBalance < 0)
     {
         m_payInArrearsButton->setText("补款");
         m_payInArrearsButton->setEnabled(true);
     }
     else if(dBalance == 0)
         m_payInArrearsButton->setEnabled(false);
}

void LeaveHospitalForm::create()
{
    m_allPayInLabel = new QLabel("总缴费：");
    m_allPayInEdit = new QLineEdit;
    m_allPayInEdit->setStyleSheet(g_strLineEditNoBorder);
    m_allPayInEdit->setReadOnly(true);
    m_allChargeLabel = new QLabel("总消费：");
    m_allChargeEdit = new QLineEdit;
    m_allChargeEdit->setStyleSheet(g_strLineEditNoBorder);
    m_allChargeEdit->setReadOnly(true);
    m_allBalanceLabel = new QLabel("总余额：");
    m_allBalanceEdit = new QLineEdit;
    m_allBalanceEdit->setStyleSheet(g_strLineEditNoBorder);
    m_allBalanceEdit->setReadOnly(true);

    m_payInArrearsButton = new QPushButton("补款");

    m_proposerLabel = new QLabel("申请人：");
    m_proposerEdit = new QLineEdit;
    m_printButton = new QPushButton("打印结算单");
    m_leaveButton = new QPushButton("出院");
}

void LeaveHospitalForm::setMyLayout()
{
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(m_allPayInLabel,0,0);
    layout->addWidget(m_allPayInEdit,0,1);

    layout->addWidget(m_allChargeLabel,1,0);
    layout->addWidget(m_allChargeEdit,1,1);

    layout->addWidget(m_allBalanceLabel,2,0);
    layout->addWidget(m_allBalanceEdit,2,1);

    layout->addWidget(m_payInArrearsButton,3,0,1,2);

    layout->addWidget(m_proposerLabel,4,0);
    layout->addWidget(m_proposerEdit,4,1);
    layout->addWidget(m_printButton,5,0,1,2);
    layout->addWidget(m_leaveButton,6,0,1,2);

    QGroupBox *allGroup = new QGroupBox;
    allGroup->setTitle("出院");
    QVBoxLayout *allLayout = new QVBoxLayout;
    allLayout->addLayout(layout);
    allGroup->setLayout(allLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(allGroup);
    setLayout(mainLayout);
}

void LeaveHospitalForm::init()
{
    m_allPayInEdit->setText(QString::number(0));
    m_allChargeEdit->setText(QString::number(0));
    m_allBalanceEdit->setText(QString::number(0));
}
