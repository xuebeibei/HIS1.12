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
        if(m_InpatientID.trimmed().isEmpty())
            m_InpatientID = temp->getInpatientID();

        return ReadChargeRecords(HospitalInPatient);
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
    if(temp->Save() && saveChargeRecords(HospitalInPatient))
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

QVector<HospitalChargeTable *>* HospitalChargeTable::selectFromDB(QDate startDate, QDate endDate, QString inpatientID)
{
    QVector<HospitalChargeTable*> *vec = new QVector<HospitalChargeTable*>;
    if(startDate > endDate)
        return NULL;

    QSqlTableModel *model = new QSqlTableModel;
    model->setTable(g_strAccount);
    QString strSql = "" , strTemp = "";

    QString strStartTime = startDate.toString("yyyy-MM-dd") + "T00:00:00";
    QString strEndTime = endDate.toString("yyyy-MM-dd") + "T23:59:59";

    strTemp = " Time between \'" + strStartTime + "\' and \'" + strEndTime + "\'";
    strSql += strTemp;

    if(!inpatientID.isEmpty())
    {
        strTemp = "and HospitalID = \'" + inpatientID + "\'";
        strSql += strTemp;
    }

    model->setFilter(strSql);
    model->select();

    for(int i = 0; i < model->rowCount();i++)
    {
        QSqlRecord record = model->record(i);
        HospitalChargeTable *temp = new HospitalChargeTable;
        temp->setID(record.value("ID").toString());
        temp->Read();
        vec->append(temp);
    }
    return vec;
}


