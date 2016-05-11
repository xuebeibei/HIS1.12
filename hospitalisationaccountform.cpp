#include "hospitalisationaccountform.h"

HospitalisationAccountForm::HospitalisationAccountForm(SubForm *parent) :
    SubForm(parent)
{
    create();
    setMyLayout();
}

HospitalisationAccountForm::~HospitalisationAccountForm()
{

}

void HospitalisationAccountForm::newTableFile()
{
}

bool HospitalisationAccountForm::saveTableFile()
{
    return true;
}

bool HospitalisationAccountForm::deleteTableFile()
{
    return true;
}

void HospitalisationAccountForm::exportTableFile()
{
}

bool HospitalisationAccountForm::findTableFile()
{
    return true;
}

void HospitalisationAccountForm::amendTableFile()
{
}

void HospitalisationAccountForm::previewTableFile()
{
}

void HospitalisationAccountForm::printTableFile()
{
}

void HospitalisationAccountForm::create()
{
    m_numberLabel = new QLabel("缴费单号：");
    m_numberEdit = new QLineEdit;
    m_numberEdit->setStyleSheet(g_strLineEditNoBorder);
    m_beforeBalanceLabel = new QLabel("缴费前余额：");
    m_beforeBalanceEdit = new QLineEdit;
    m_beforeBalanceEdit->setStyleSheet(g_strLineEditNoBorder);
    m_paymentMethodLabel = new QLabel("缴费方式：");
    m_paymentMethodCombo = new QComboBox;
    m_paymentLabel = new QLabel("缴费金额：");
    m_paymentEdit = new QLineEdit;
    m_afterBalanceLabel = new QLabel("缴费后余额：");
    m_afterBalanceEdit = new QLineEdit;
    m_afterBalanceEdit->setStyleSheet(g_strLineEditNoBorder);
    m_dontKnowLabel = new QLabel("票号：");
    m_dontKnowEdit = new QLineEdit;

    m_resultsView = new QTableView;
    m_resultsModel = new QStandardItemModel;
    m_resultsView->setModel(m_resultsModel);
}

void HospitalisationAccountForm::setMyLayout()
{
    QGroupBox *leftGroup = new QGroupBox;
    QGridLayout *leftLayout = new QGridLayout;
    leftLayout->addWidget(m_numberLabel,0,0);
    leftLayout->addWidget(m_numberEdit,0,1);
    leftLayout->addWidget(m_beforeBalanceLabel,1,0);
    leftLayout->addWidget(m_beforeBalanceEdit,1,1);
    leftLayout->addWidget(m_paymentMethodLabel,2,0);
    leftLayout->addWidget(m_paymentMethodCombo,2,1);
    leftLayout->addWidget(m_paymentLabel,3,0);
    leftLayout->addWidget(m_paymentEdit,3,1);
    leftLayout->addWidget(m_afterBalanceLabel,4,0);
    leftLayout->addWidget(m_afterBalanceEdit,4,1);
    leftLayout->addWidget(m_dontKnowLabel,5,0);
    leftLayout->addWidget(m_dontKnowEdit,5,1);
    leftGroup->setLayout(leftLayout);


    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(m_resultsView);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(leftGroup);
    bottomLayout->addLayout(rightLayout);
    bottomLayout->setStretchFactor(rightLayout,1);


    QGroupBox *allGroup = new QGroupBox;
    allGroup->setTitle("缴费");
    QVBoxLayout *allLayout = new QVBoxLayout;
    allLayout->addLayout(m_topLayout);
    allLayout->addLayout(bottomLayout);
    allGroup->setLayout(allLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(allGroup);
    setLayout(mainLayout);
}

void HospitalisationAccountForm::init()
{
}
