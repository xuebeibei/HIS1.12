#include "account.h"

Account::Account(QString strInpatientID)
{
    m_strID = getNewID();
    m_InpatientID = strInpatientID;
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
    this->m_InpatientID = oneAccount.m_InpatientID;
    this->m_dBalance = oneAccount.m_dBalance;
    this->m_eAction = oneAccount.m_eAction;
    this->m_dActionMoney = oneAccount.m_dActionMoney;
    this->m_dateTime = oneAccount.m_dateTime;
    this->m_ePaymentMethod = oneAccount.m_ePaymentMethod;
    this->m_strRemarks = oneAccount.m_strRemarks;

    return this;
}

QString Account::getID()
{
    return m_strID;
}

QString Account::getInpatientID()
{
    return m_InpatientID;
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

QDateTime Account::getDateTime()
{
    return m_dateTime;
}

void Account::setID(QString strID)
{
    m_strID = strID;
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
    sqlModel->setFilter(g_strID + " = \'" + m_strID + "\'");
    sqlModel->select();

    if(sqlModel->rowCount() > 0)
    {
        QSqlRecord record = sqlModel->record(0);
        m_InpatientID = record.value(g_strHospitalID).toString();
        m_eAction = (AccountAction)record.value(g_strAccountAction).toInt();
        m_dActionMoney = record.value(g_strMoney).toDouble();
        m_dBalance = record.value(g_strBalance).toDouble();
        m_dateTime = record.value(g_strTime).toDateTime();

        m_ePaymentMethod = (PaymentMethod)record.value(g_strMethod).toInt();
        m_strRemarks = record.value(g_strRemarks).toString();
        return true;
    }
    else
    {
        sqlModel->setFilter(g_strHospitalID + " = \'" + m_InpatientID + "\' Order By DateTime desc");
        sqlModel->select();

        if(sqlModel->rowCount() > 0)
        {
            QSqlRecord record = sqlModel->record(0);
            m_dBalance = record.value(g_strBalance).toDouble();
        }
        else
        {
            return false;
        }
    }

    return false;
}

bool Account::Save()
{
    deleteRows(g_strAccount,g_strID,m_strID);

    QSqlTableModel *sqlModel = new QSqlTableModel;
    sqlModel->setTable(g_strAccount);

    int row = 0;
    sqlModel->insertRow(row);
    sqlModel->setData(sqlModel->index(row,0), m_strID);
    sqlModel->setData(sqlModel->index(row,1), m_InpatientID);
    sqlModel->setData(sqlModel->index(row,2), m_eAction);
    sqlModel->setData(sqlModel->index(row,3), m_dActionMoney);
    sqlModel->setData(sqlModel->index(row,4), m_dBalance);
    m_dateTime = QDateTime::currentDateTime();
    sqlModel->setData(sqlModel->index(row,5), m_dateTime);
    sqlModel->setData(sqlModel->index(row,6), m_ePaymentMethod);
    sqlModel->setData(sqlModel->index(row,7), m_strRemarks);
    sqlModel->submitAll();

    return true;
}

bool Account::Delete()
{
    return deleteRows(g_strAccount,g_strHospitalID,m_strID);
}

QVector<Account *> Account::getRecords(QString strInpatientID)
{
    QVector<Account *> vec;
    QSqlTableModel *sqlModel = new QSqlTableModel;
    sqlModel->setTable(g_strAccount);
    sqlModel->setFilter(g_strHospitalID + " = \'" + strInpatientID + "\' Order By " + g_strTime + " desc");
    sqlModel->select();

    for(int i = 0; i < sqlModel->rowCount(); i++)
    {
        Account *temp = new Account(strInpatientID);
        QSqlRecord record = sqlModel->record(i);
        temp->m_strID = record.value(g_strID).toString();
        temp->m_InpatientID = record.value(g_strHospitalID).toString();
        temp->m_eAction = (AccountAction)record.value(g_strAccountAction).toInt();
        temp->m_dActionMoney = record.value(g_strMoney).toDouble();
        temp->m_dBalance = record.value(g_strBalance).toDouble();
        temp->m_dateTime = record.value(g_strTime).toDateTime();

        temp->m_ePaymentMethod = (PaymentMethod)record.value(g_strMethod).toInt();
        temp->m_strRemarks = record.value(g_strRemarks).toString();
        vec.append(temp);
    }

    return vec;
}

QString Account::actionToString()
{
    QString strTemp = g_strNull;
    switch(m_eAction)
    {
    case payIn:
    {
        strTemp = g_strAdd;
        break;
    }
    case refund:
    {
        strTemp = g_strSubtract;
        break;
    }
    case consume:
    {
        strTemp = g_strSubtract;
        break;
    }
    default:
        break;
    }

    return strTemp;
}

QString Account::paymentMethodToString()
{
    QString strTemp = g_strNull;
    switch(m_ePaymentMethod)
    {
    case cash:
    {
        strTemp = g_strCash;
        break;
    }
    case slotCard:
    {
        strTemp = g_strSlotCard;
        break;
    }
    case bank:
    {
        strTemp = g_strBank;
        break;
    }
    default:
        break;
    }

    return strTemp;
}
