#include "clinicchargetable.h"

ClinicChargeTable::ClinicChargeTable()
{
    m_strID = getNewClinicChargeID();
    m_dRealIncome = 0.0;
    m_strMaker = g_strMaker;
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

bool ClinicChargeTable::Read()
{
    QSqlTableModel *model = new QSqlTableModel;
    model->setTable(g_strClinicCharge);
    model->setFilter(g_strID + " = \'" + m_strID + "\'");
    model->select();
    for(int i = 0; i< model->rowCount();i++)
    {
        QSqlRecord record = model->record(i);
        m_strID = record.value(g_strID).toString();
        m_patient.setName(record.value(g_strName).toString());
        m_patient.setGender((Gender)record.value(g_strGender).toInt());
        m_patient.setAge(record.value(g_strAge).toInt());
        m_patient.setIDCard(record.value(g_strIdCardNum).toString());
        m_patient.setSocialSecurityNum(record.value(g_strSocialSecurityNum).toString());
        m_patient.setMedicalInsuranceType((MedicalInsuranceType)record.value(g_strMedicalInsuranceType).toInt());
        m_patient.setDepartment(record.value(g_strDepartment).toString());
        m_patient.setDoctor(record.value(g_strDoctor).toString());
        m_time = record.value(g_strTime).toDateTime();
        m_dDueIncome = record.value(g_strDueIncome).toDouble();
        m_dRealIncome = record.value(g_strRealIncome).toDouble();
        m_strMaker = record.value(g_strMaker).toString();
    }

    return ReadChargeRecords();
}

bool ClinicChargeTable::Save()
{
    deleteRows(g_strClinicCharge,g_strID,m_strID);

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

    return saveChargeRecords();
}

bool ClinicChargeTable::Delete()
{
    if(deleteRows(g_strClinicCharge,g_strID,m_strID))
        return deleteChargeRecords();
    else
        return false;
}

QVector<ClinicChargeTable *> ClinicChargeTable::selectClinicChargesFromDb(QDate date , QDateTime ReportTime)
{
    QVector<ClinicChargeTable *> vecClinicCharges;
    QSqlTableModel *model = new QSqlTableModel;
    model->setTable(g_strClinicCharge);

    QString strStartTime = date.toString(g_strYMD) + g_strDayStartTime;
    QString strEndTime;
    if(ReportTime .date() > date)
    {
        strEndTime = date.toString(g_strYMD) + g_strDayEndTime;
    }
    else if(ReportTime .date() == date)
    {
        strEndTime = date.toString(g_strYMD) + ReportTime .time().toString("Thh:mm:ss");
    }

    model->setFilter(g_strTime +" between \'" + strStartTime + "\' and \'" +strEndTime +"\'");
    model->select();

    for(int i = 0; i < model->rowCount(); i++)
    {
        QSqlRecord record = model->record(i);
        QString strChargeId = record.value(g_strID).toString();
        ClinicChargeTable *charge = new ClinicChargeTable;
        charge->setID(strChargeId);
        charge->Read();
        vecClinicCharges.append(charge);
    }
    return vecClinicCharges;
}
