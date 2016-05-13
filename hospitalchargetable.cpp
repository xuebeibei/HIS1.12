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
    return true;
}

bool HospitalChargeTable::Save()
{
    return true;
}

bool HospitalChargeTable::Delete()
{
    return true;
}
