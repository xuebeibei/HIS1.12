#include "inpatient.h"

Inpatient::Inpatient(QString strID)
{
    m_strID = strID;
    m_strCaseID = m_strID;
    m_nBedNum = 0;
    m_eNursingLevel = general;
    m_strMedicalResult = g_strNull;
    m_account = new Account(strID);
}

QString Inpatient::getID() const
{
    return m_strID;
}

QString Inpatient::getCaseID() const
{
    return m_strCaseID;
}

int Inpatient::getBedNum() const
{
    return m_nBedNum;
}

NursingLevel Inpatient::getNursingLevel() const
{
    return m_eNursingLevel;
}

QString Inpatient::getMedicalResult() const
{
    return m_strMedicalResult;
}

Account* Inpatient::getAccount() const
{
    return m_account;
}

Contacts Inpatient::getContacts() const
{
    return m_contacts;
}

void Inpatient::setID(QString strID)
{
    m_strID = strID;
}

void Inpatient::setCaseID(QString strCaseID)
{
    m_strCaseID = strCaseID;
}

void Inpatient::setBedNum(int nBedNum)
{
    m_nBedNum = nBedNum;
}

void Inpatient::setNursingLevel(NursingLevel eNursingLevel)
{
    m_eNursingLevel = eNursingLevel;
}

void Inpatient::setMedicalResult(QString strMedicalResult)
{
    m_strMedicalResult = strMedicalResult;
}

void Inpatient::setAccount(Account *account)
{
    m_account = account;
}

void Inpatient::setContacts(Contacts contacts)
{
    m_contacts = contacts;
}

bool Inpatient::Read()
{
    QSqlTableModel *sqlModel = new QSqlTableModel;
    sqlModel->setTable(g_strInPatient);
    sqlModel->setFilter("ID = \'" + m_strID + "\'");
    sqlModel->select();

    if(sqlModel->rowCount() == 1)
    {
        QSqlRecord record = sqlModel->record(0);
        m_strName = record.value("Name").toString();
        m_eGender = (Gender)record.value("Gender").toInt();
        m_nAge = record.value("Age").toInt();
        m_strIDCard = record.value("IDCard").toString();
        m_strCaseID = record.value("CaseID").toString();
        m_strDepartment = record.value("Department").toString();
        m_strDoctor = record.value("Doctor").toString();
        m_eMedicalInsuranceType = (MedicalInsuranceType)record.value("MedicalInsuranceType").toInt();
        m_strSocialSecurityNum = record.value("SocialSecurityNum").toString();

        m_nBedNum = record.value("BedNum").toInt();
        m_eNursingLevel = (NursingLevel)record.value("NursingLevel").toInt();
        m_account->Read();

        m_strMedicalResult = record.value("MedicalResult").toString();

        return true;
    }
    else
        return false;
}

bool Inpatient::Save()
{
    QSqlTableModel *sqlModel = new QSqlTableModel;
    sqlModel->setTable(g_strInPatient);

    int row = 0;
    sqlModel->insertRow(row);
    sqlModel->setData(sqlModel->index(row,0), m_strID);
    sqlModel->setData(sqlModel->index(row,1), m_strName);
    sqlModel->setData(sqlModel->index(row,2), m_eGender);
    sqlModel->setData(sqlModel->index(row,3), m_nAge);
    sqlModel->setData(sqlModel->index(row,4), m_strIDCard);
    sqlModel->setData(sqlModel->index(row,5), m_strCaseID);
    sqlModel->setData(sqlModel->index(row,6), m_strDepartment);
    sqlModel->setData(sqlModel->index(row,7), m_strDoctor);
    sqlModel->setData(sqlModel->index(row,8), m_eMedicalInsuranceType);
    sqlModel->setData(sqlModel->index(row,9), m_strSocialSecurityNum);
    sqlModel->setData(sqlModel->index(row,10), m_nBedNum);
    sqlModel->setData(sqlModel->index(row,11), m_eNursingLevel);
    sqlModel->setData(sqlModel->index(row,12), m_strMedicalResult);
    sqlModel->setData(sqlModel->index(row,13), m_contacts.getName());
    sqlModel->setData(sqlModel->index(row,14), m_contacts.getTel());
    sqlModel->setData(sqlModel->index(row,15), m_contacts.getAddress());
    sqlModel->submitAll();

    return m_account->Save();
}
