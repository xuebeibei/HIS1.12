#include "clinicchargetable.h"

ClinicChargeTable::ClinicChargeTable()
{
    m_strID = getNewClinicChargeID();
    m_dRealIncome = 0.0;
    m_strMaker = "maker";
}

QString ClinicChargeTable::getNewClinicChargeID()
{
    return g_strClinicChargeNumPR + getNewID();
}

double ClinicChargeTable::getRealImcome() const
{
    return m_dRealIncome;
}

Patient ClinicChargeTable::getPatient() const
{
    return m_patient;
}

void ClinicChargeTable::setRealIncome(double d_RealIncome)
{
    this->m_dRealIncome = d_RealIncome;
}

void ClinicChargeTable::setPatient(Patient patient)
{
    this->m_patient = patient;
}

bool ClinicChargeTable::readChargeTable()
{

    QSqlTableModel *model = new QSqlTableModel;
    model->setTable(g_strClinicCharge);
    model->setFilter("ID = \'" + m_strID + "\'");
    model->select();
    for(int i = 0; i< model->rowCount();i++)
    {
        QSqlRecord record = model->record(i);
        m_strID = record.value("id").toString();
        m_patient.setName(record.value("name").toString());
        m_patient.setGender((Gender)record.value("Gender").toInt());
        m_patient.setAge(record.value("Age").toInt());
        m_patient.setIDCard(record.value("IdCardNum").toString());
        m_patient.setSocialSecurityNum(record.value("SocialSecurityNum").toString());
        m_patient.setMedicalInsuranceType((MedicalInsuranceType)record.value("MedicalInsuranceType").toInt());
        m_patient.setDepartment(record.value("Department").toString());
        m_patient.setDoctor(record.value("Doctor").toString());
        m_time = record.value("Time").toDateTime();
        m_dDueIncome = record.value("DueIncome").toDouble();
        m_dRealIncome = record.value("RealIncome").toDouble();
        m_strMaker = record.value("Maker").toString();
    }

    return true;

}

bool ClinicChargeTable::saveChargeTable()
{

    deleteRows(g_strClinicCharge,"ID",m_strID);

    QSqlTableModel *model = new QSqlTableModel;
    model->setTable(g_strClinicCharge);

    int row =0;
    model->insertRows(row,1);
    model->setData(model->index(row,0),m_strID);
    model->setData(model->index(row,1),m_patient.getName());
    model->setData(model->index(row,2),m_patient.getGender());
    model->setData(model->index(row,3),m_patient.getAge());
    model->setData(model->index(row,4),m_patient.getIDCard());
    model->setData(model->index(row,5),m_patient.getSocialSecurityNum());
    model->setData(model->index(row,6),m_patient.getMedicalInsuranceType());
    model->setData(model->index(row,7),m_patient.getDepartment());
    model->setData(model->index(row,8),m_patient.getDoctor());
    model->setData(model->index(row,9),m_dDueIncome);
    model->setData(model->index(row,10),m_dRealIncome);
    model->setData(model->index(row,11),m_time);
    model->setData(model->index(row,12),m_strMaker);
    model->submitAll();
    return true;
}

bool ClinicChargeTable::Read()
{
    if(readChargeTable())
    {
        return ReadChargeRecords();
    }
    else
        return false;
}

bool ClinicChargeTable::Save()
{
    if(saveChargeTable())
    {
        return saveChargeRecords();
    }
    else
        return false;
}

bool ClinicChargeTable::Delete()
{
    if(deleteChargeTable())
        return deleteChargeRecords();
    else
        return false;
}

QVector<ClinicChargeTable *> ClinicChargeTable::selectClinicChargesFromDb(QDate date , QDateTime ReportTime)
{
    QVector<ClinicChargeTable *> vecClinicCharges;
    QSqlTableModel *model = new QSqlTableModel;
    model->setTable(g_strClinicCharge);
    QString strStartTime = date.toString("yyyy-MM-dd") + "T00:00:00";
    QString strEndTime;
    if(ReportTime .date() > date)
    {
        strEndTime = date.toString("yyyy-MM-dd") + "T23:59:59";
    }
    else if(ReportTime .date() == date)
    {
        strEndTime = date.toString("yyyy-MM-dd") + ReportTime .time().toString("Thh:mm:ss");
    }

    model->setFilter("Time between \'" + strStartTime + "\' and \'" +strEndTime +"\'");
    model->select();

    for(int i = 0; i < model->rowCount(); i++)
    {
        QSqlRecord record = model->record(i);
        QString strChargeId = record.value("ID").toString();
        ClinicChargeTable *charge = new ClinicChargeTable;
        charge->setID(strChargeId);
        charge->Read();
        vecClinicCharges.append(charge);
    }
    return vecClinicCharges;
}

bool ClinicChargeTable::deleteChargeTable()
{

    return deleteRows(g_strClinicCharge,"ID",m_strID);

}

bool ClinicChargeTable::deleteChargeRecords()
{

    return deleteRows(g_strClinicChargeDetails,"ChargeId",m_strID);
}

