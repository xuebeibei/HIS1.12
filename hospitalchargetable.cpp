#include "hospitalchargetable.h"

HospitalChargeTable::HospitalChargeTable()
{
    m_strID = getNewHospitalChargeID();
    m_InpatientID = g_strNull;
    m_strMaker = "maker";
}

QString HospitalChargeTable::getNewHospitalChargeID()
{
    return g_strHospitalChargeNumPR + getNewID();
}

bool HospitalChargeTable::Read()
{
    Account *temp = new Account(m_InpatientID);
    temp->setID(m_strID);

    if(temp->Read())
    {
        m_dDueIncome = temp->getActionMoney();
        m_time = temp->getDateTime();

        return ReadChargeRecords();
    }
    else
        return false;
}

bool HospitalChargeTable::Save()
{
    Account *temp = new Account(m_InpatientID);
    temp->setID(m_strID);
    temp->Read();
    temp->setAction(consume);
    temp->setActionMoney(m_dDueIncome);
    temp->Refund();
    if(temp->Save() && saveChargeRecords())
        return true;
    else
        return false;
}

bool HospitalChargeTable::Delete()
{
    Account *temp = new Account(m_InpatientID);
    temp->setID(m_strID);
    if(temp->Delete() && deleteChargeRecords())
        return true;
    else
        return false;
}

void HospitalChargeTable::setInpatientID(QString strInpatientID)
{
    m_InpatientID = strInpatientID;
}

QString HospitalChargeTable::getInpatientID() const
{
    return m_InpatientID;
}
