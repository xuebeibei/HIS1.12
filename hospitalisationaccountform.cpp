#include "hospitalisationaccountform.h"

HospitalisationAccountForm::HospitalisationAccountForm(SubForm *parent) :
    SubForm(parent)
{
    create();
    setMyLayout();
    init();
    setMaximumHeight(240);
    setMinimumWidth(700);
}

HospitalisationAccountForm::~HospitalisationAccountForm()
{

}

void HospitalisationAccountForm::updateInpatientID(QString strInpatientID)
{
    m_strInpatientID = strInpatientID;
    newTableFile();
}

void HospitalisationAccountForm::updateAccountDate()
{
    showRecords();
}

double HospitalisationAccountForm::getAllPayIn()
{
    return m_allPayIn;
}

double HospitalisationAccountForm::getAllConsume()
{
    return m_allConsume;
}

void HospitalisationAccountForm::newTableFile()
{
    init();
    m_account = new Account(m_strInpatientID);
    Read();
    showRecords();
}

bool HospitalisationAccountForm::saveTableFile()
{
    m_account->setAction(payIn);
    double dMoney = m_paymentEdit->text().toDouble();
    if(dMoney <= 0)
        return false;
    m_account->Read();
    m_account->setActionMoney(dMoney);
    m_account->setPaymentMethod((PaymentMethod)m_paymentMethodCombo->currentIndex());
    m_account->PayIn();
    if(m_account->Save())
    {
        newTableFile();
        return true;
    }
    else
        return false;
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

void HospitalisationAccountForm::updateAfterBalance()
{
    double dBeforeBalance = m_beforeBalanceEdit->text().toDouble();
    double dPayIn = m_paymentEdit->text().toDouble();
    double dAfterBalance = dBeforeBalance + dPayIn;
    m_afterBalanceEdit->setText(QString::number(dAfterBalance));
}

void HospitalisationAccountForm::create()
{
    m_numberLabel = new QLabel("缴费单号：");
    m_numberEdit = new QLineEdit;
    m_numberEdit->setStyleSheet(g_strLineEditNoBorder);
    m_numberEdit->setReadOnly(true);

    m_beforeBalanceLabel = new QLabel("缴费前余额：");
    m_beforeBalanceEdit = new QLineEdit;
    m_beforeBalanceEdit->setStyleSheet(g_strLineEditNoBorder);
    m_beforeBalanceEdit->setReadOnly(true);

    m_paymentMethodLabel = new QLabel("缴费方式：");
    m_paymentMethodCombo = new QComboBox;
    m_paymentMethodCombo->addItem("现金");
    m_paymentMethodCombo->addItem("刷卡");
    m_paymentMethodCombo->addItem("银行");

    m_paymentLabel = new QLabel("缴费金额：");
    m_paymentEdit = new QLineEdit;
    connect(m_paymentEdit, SIGNAL(textChanged(QString)), this, SLOT(updateAfterBalance()));

    m_afterBalanceLabel = new QLabel("缴费后余额：");
    m_afterBalanceEdit = new QLineEdit;
    m_afterBalanceEdit->setStyleSheet(g_strLineEditNoBorder);
    m_afterBalanceEdit->setReadOnly(true);

    m_dontKnowLabel = new QLabel("票号：");
    m_dontKnowEdit = new QLineEdit;

    m_saveButton = new QPushButton("缴费");
    connect(m_saveButton, SIGNAL(clicked()), this, SLOT(saveTableFile()));
    m_cancelButton = new QPushButton("取消");
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(newTableFile()));

    m_resultsView = new QTableView;
    m_resultsModel = new QStandardItemModel;
    m_resultsView->setModel(m_resultsModel);
    m_resultsView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_resultsView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void HospitalisationAccountForm::setMyLayout()
{
    QGroupBox *leftGroup = new QGroupBox;
    leftGroup->setTitle("缴费");
    QGridLayout *leftTopLayout = new QGridLayout;
    leftTopLayout->addWidget(m_numberLabel,0,0);
    leftTopLayout->addWidget(m_numberEdit,0,1);
    leftTopLayout->addWidget(m_beforeBalanceLabel,1,0);
    leftTopLayout->addWidget(m_beforeBalanceEdit,1,1);
    leftTopLayout->addWidget(m_paymentMethodLabel,2,0);
    leftTopLayout->addWidget(m_paymentMethodCombo,2,1);
    leftTopLayout->addWidget(m_paymentLabel,3,0);
    leftTopLayout->addWidget(m_paymentEdit,3,1);
    leftTopLayout->addWidget(m_afterBalanceLabel,4,0);
    leftTopLayout->addWidget(m_afterBalanceEdit,4,1);
    leftTopLayout->addWidget(m_saveButton,5,0,1,2);
    leftTopLayout->addWidget(m_cancelButton,6,0,1,2);
    leftGroup->setLayout(leftTopLayout);

    QGroupBox *rightGroup = new QGroupBox;
    rightGroup->setTitle("账户记录");
    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(m_resultsView);
    rightGroup->setLayout(rightLayout);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(leftGroup);
    mainLayout->addWidget(rightGroup);
    mainLayout->setStretchFactor(rightGroup,1);
    setLayout(mainLayout);
}

void HospitalisationAccountForm::init()
{
    m_paymentMethodCombo->setCurrentIndex(0);
    m_numberEdit->setText(g_strNull);
    m_beforeBalanceEdit->setText(g_strNull);
    m_paymentEdit->setText(g_strNull);
    m_afterBalanceEdit->setText(g_strNull);
    initTableView();
}

void HospitalisationAccountForm::Read()
{
    if(m_account->Read())
    {
        m_paymentMethodCombo->setCurrentIndex(m_account->getPaymentMethod());
    }
    m_numberEdit->setText(m_account->getID());
    m_beforeBalanceEdit->setText(QString::number(m_account->getBalance()));
}

void HospitalisationAccountForm::initTableView()
{
    QStringList strList;
    strList.append("单号");
    strList.append("日期");
    strList.append("余额");
    strList.append("类型");
    strList.append("金额");
    strList.append("付款方式");

    m_resultsModel->clear();
    for(int i = 0; i < strList.size(); i++)
    {
        m_resultsModel->setHorizontalHeaderItem(i,new QStandardItem(strList.at(i)));
    }
    if(strList.size() > 0)
        m_resultsModel->setItem(0, strList.size()-1, NULL);
}

void HospitalisationAccountForm::showRecords()
{
    initTableView();

    QVector<Account *> vec = Account::getRecords(m_strInpatientID);
    for(int i = 0; i < vec.size(); i++)
    {
        QString strID = vec.at(i)->getID();
        m_resultsModel->setItem(i,0,new QStandardItem(strID));
        m_resultsModel->setItem(i,1,new QStandardItem(vec.at(i)->getDateTime().toString("yyyy-MM-dd hh:mm:ss")));
        m_resultsModel->setItem(i,2,new QStandardItem(QString::number(vec.at(i)->getBalance())));
        m_resultsModel->setItem(i,3,new QStandardItem(vec.at(i)->actionToString()));
        m_resultsModel->setItem(i,4,new QStandardItem(QString::number(vec.at(i)->getActionMoney())));
        m_resultsModel->setItem(i,5,new QStandardItem(vec.at(i)->paymentMethodToString()));
    }

    double dAllPayIn = 0;
    double dallConsume = 0;
    for(int i = 0; i < vec.size(); i++)
    {
        AccountAction eTemp = vec.at(i)->getAction();
        if(eTemp == payIn)
        {
            dAllPayIn += vec.at(i)->getActionMoney();
        }
        else if(eTemp == consume)
        {
            dallConsume += vec.at(i)->getActionMoney();
        }
    }
    setAllPayIn(dAllPayIn, dallConsume);
}

void HospitalisationAccountForm::setAllPayIn(double pay, double consume)
{
    if(pay != m_allPayIn || consume != m_allConsume)
    {
        m_allPayIn = pay;
        m_allConsume = consume;
        m_beforeBalanceEdit->setText(QString::number(m_allPayIn - m_allConsume));
        emit changePayIn(m_allPayIn, m_allConsume);
    }
}
