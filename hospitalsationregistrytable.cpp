#include "hospitalsationregistrytable.h"

HospitalsationRegistryTable::HospitalsationRegistryTable()
{
    m_inpatient = new Inpatient(getNewID());
    m_registryDate = QDate::currentDate();
}

bool HospitalsationRegistryTable::Read()
{
    if(myDB::connectDB())
    {
        QSqlTableModel *sqlModel = new QSqlTableModel;
        sqlModel->setTable(g_strHospitalRegistry);
        sqlModel->setFilter("ID = \'" + m_inpatient->getID() + "\'");
        sqlModel->select();

        if(sqlModel->rowCount() == 1)
        {
            QSqlRecord record = sqlModel->record(0);
            m_registryDate = record.value("Date").toDate();

            return m_inpatient->Read();
        }
        else
        {
            return false;
        }
    }
    return false;
}

bool HospitalsationRegistryTable::Save()
{
    if(myDB::connectDB())
    {
        QSqlTableModel *sqlModel = new QSqlTableModel;
        sqlModel->setTable(g_strHospitalRegistry);

        int row = 0;
        sqlModel->insertRow(row);
        sqlModel->setData(sqlModel->index(row,0), m_inpatient->getID());
        sqlModel->setData(sqlModel->index(row,1), m_registryDate.toString("yyyy-MM-dd"));
        sqlModel->submitAll();

        return m_inpatient->Save();
    }
    else
        return false;
}

bool HospitalsationRegistryTable::Delete()
{
    return true;
}


Inpatient* HospitalsationRegistryTable::getInpatient() const
{
    return m_inpatient;
}

QDate HospitalsationRegistryTable::getRegistryDate() const
{
    return m_registryDate;
}

void HospitalsationRegistryTable::setInpatient(Inpatient* inpatient)
{
    m_inpatient = inpatient;
}

void HospitalsationRegistryTable::setRegistryDate(QDate registryDate)
{
    m_registryDate = registryDate;
}
