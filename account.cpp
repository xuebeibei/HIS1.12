#include "account.h"

Account::Account(QString strID)
{
    m_strID = strID;
    m_dBalance = 0.0;
    m_eAction = payIn;
    m_dActionMoney = 0.0;
    m_dateTime = QDateTime::currentDateTime();
    m_ePaymentMethod = cash;
    m_strRemarks = g_strNull;
}

Account* Account::operator = (Account oneAccount)
{
    this->m_strID = oneAccount.m_strID;
    this->m_dBalance = oneAccount.m_dBalance;
    this->m_eAction = oneAccount.m_eAction;
    this->m_dActionMoney = oneAccount.m_dActionMoney;
    this->m_dateTime = oneAccount.m_dateTime;
    this->m_ePaymentMethod = oneAccount.m_ePaymentMethod;
    this->m_strRemarks = oneAccount.m_strRemarks;

    return this;
}

double Account::getBalance()
{
    return m_dBalance;
}

double Account::getActionMoney()
{
    return m_dActionMoney;
}

AccountAction Account::getAction()
{
    return m_eAction;
}

PaymentMethod Account::getPaymentMethod()
{
    return m_ePaymentMethod;
}

QString Account::getRemarks()
{
    return m_strRemarks;
}

void Account::setActionMoney(double dMoney)
{
    m_dActionMoney = dMoney;
}

void Account::setAction(AccountAction eAction)
{
    m_eAction = eAction;
}

void Account::setPaymentMethod(PaymentMethod ePaymentMethod)
{
    m_ePaymentMethod = ePaymentMethod;
}

void Account::setRemarks(QString strRemarks)
{
    m_strRemarks = strRemarks;
}

void Account::PayIn()
{
    m_dBalance += m_dActionMoney;
}

void Account::Refund()
{
    m_dBalance -= m_dActionMoney;
}

bool Account::Read()
{
    QSqlTableModel *sqlModel = new QSqlTableModel;
    sqlModel->setTable(g_strAccount);
    sqlModel->setFilter("ID = \'" + m_strID + "\' Order By Time desc");
    sqlModel->select();

    if(sqlModel->rowCount() > 0)
    {
        QSqlRecord record = sqlModel->record(0);
        m_eAction = (AccountAction)record.value("Action").toInt();
        m_dActionMoney = record.value("ActionMoney").toDouble();
        m_dBalance = record.value("Balance").toDouble();
        m_dateTime = record.value("Time").toDateTime();

        m_ePaymentMethod = (PaymentMethod)record.value("Method").toInt();
        m_strRemarks = record.value("Remarks").toString();
        return true;
    }
    else
        return false;
}

bool Account::Save()
{
    QSqlTableModel *sqlModel = new QSqlTableModel;
    sqlModel->setTable(g_strAccount);

    int row = 0;
    sqlModel->insertRow(row);
    sqlModel->setData(sqlModel->index(row,0), m_strID);
    sqlModel->setData(sqlModel->index(row,1), m_eAction);
    sqlModel->setData(sqlModel->index(row,2), m_dActionMoney);
    sqlModel->setData(sqlModel->index(row,3), m_dBalance);
    sqlModel->setData(sqlModel->index(row,4), m_dateTime);
    sqlModel->setData(sqlModel->index(row,5), m_ePaymentMethod);
    sqlModel->setData(sqlModel->index(row,6), m_strRemarks);
    sqlModel->submitAll();

    return true;
}
