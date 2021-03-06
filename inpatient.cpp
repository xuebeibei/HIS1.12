#include "inpatient.h"

Inpatient::Inpatient()
{
    m_strID = getNewID();
    m_strCaseID = m_strID;
    m_nBedNum = 0;
    m_eNursingLevel = general;
    m_strMedicalResult = g_strNull;
    m_registryDate = QDate::currentDate();
}

Inpatient::~Inpatient()
{
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

Contacts Inpatient::getContacts() const
{
    return m_contacts;
}

QDate Inpatient::getRegistryDate() const
{
    return m_registryDate;
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

void Inpatient::setContacts(Contacts contacts)
{
    m_contacts = contacts;
}

void Inpatient::setRegistryDate(QDate registryDate)
{
    m_registryDate = registryDate;
}

bool Inpatient::Read()
{
    QSqlTableModel *sqlModel = new QSqlTableModel;
    sqlModel->setTable(g_strInPatient);
    sqlModel->setFilter("HospitalID = \'" + m_strID + "\'");
    sqlModel->select();

    if(sqlModel->rowCount() == 1)
    {
        QSqlRecord record = sqlModel->record(0);
        m_strName = record.value("Name").toString();
        m_eGender = (Gender)record.value("Gender").toInt();
        m_nAge = record.value("Age").toInt();
        m_strIDCard = record.value("IdCardNum").toString();
        m_strCaseID = record.value("CaseID").toString();
        m_strDepartment = record.value("Department").toString();
        m_strDoctor = record.value("Doctor").toString();
        m_eMedicalInsuranceType = (MedicalInsuranceType)record.value("MedicalInsuranceType").toInt();
        m_strSocialSecurityNum = record.value("SocialSecurityNum").toString();

        m_nBedNum = record.value("BedNum").toInt();
        m_eNursingLevel = (NursingLevel)record.value("NursingLevel").toInt();

        m_strMedicalResult = record.value("MedicalResult").toString();
        m_contacts.setName(record.value("Contacts").toString());
        m_contacts.setTel(record.value("Tel").toString());
        m_contacts.setAddress(record.value("Address").toString());
        m_registryDate = record.value("Date").toDate();

        return true;
    }
    else
        return false;
}

bool Inpatient::Save()
{

    deleteRows(g_strInPatient,"HospitalID",m_strID);

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
    sqlModel->setData(sqlModel->index(row,16), m_registryDate.toString("yyyy-MM-dd"));
    sqlModel->submitAll();

    return true;
}

bool Inpatient::Delete()
{
    bool deleteInpatient = deleteRows(g_strInPatient,"HospitalID",m_strID);
    bool deleteAccounts =  deleteRows(g_strAccount,"HospitalID",m_strID);
    return deleteInpatient&&deleteAccounts;
}

QStringList Inpatient::getIDsFromDB(QString strID, QString strName, Gender eGender)
{
    QSqlTableModel *sqlModel = new QSqlTableModel;
    sqlModel->setTable(g_strInPatient);

    QString strSql = "",strTemp;
    QStringList sqlList;
    if(eGender != allGender)
    {
        strTemp = "Gender = \'" + QString::number((int)eGender) +"\' ";
        sqlList.append(strTemp);
    }

    if(!strID.trimmed().isEmpty())
    {
        strTemp = " HospitalID = \'" + strID +"\' ";
        sqlList.append(strTemp);
    }
    if(!strName.trimmed().isEmpty())
    {
        strTemp = " Name = \'" + strName +"\' ";
        sqlList.append(strTemp);
    }

    for(int i = 0; i < sqlList.size(); i++)
    {
        if(i != 0)
            strSql += " and ";
        strSql += sqlList.at(i);
    }

    sqlModel->setFilter(strSql);
    sqlModel->select();
    QStringList strList;
    for(int i = 0;i < sqlModel->rowCount(); i++)
    {
        QSqlRecord record = sqlModel->record(i);
        QString strID = record.value("HospitalID").toString();
        strList.append(strID);
    }

    return strList;
}

QVector<Inpatient *> Inpatient::selectFromDB(QString strID, QString strName, Gender eGender)
{
    QVector<Inpatient *> vec;

    QStringList strIDsList = getIDsFromDB(strID, strName, eGender);
    for(int i = 0;i < strIDsList.size(); i++)
    {
        Inpatient *temp = new Inpatient;
        temp->setID(strIDsList.at(i));
        temp->Read();
        vec.append(temp);
    }

    return vec;
}

QString Inpatient::getNameByID(QString strID)
{
    Inpatient *tempInpatient = new Inpatient;
    tempInpatient->setID(strID);
    tempInpatient->Read();
    return tempInpatient->getName();
}

bool Inpatient::isLeaveHospital(QString strID)
{
    QSqlTableModel *sqlModel = new QSqlTableModel;
    sqlModel->setTable(g_strLeaveHospital);
    sqlModel->setFilter("HospitalID = \'" + strID +"\'" );
    sqlModel->select();

    if(sqlModel->rowCount() > 0)
    {
        return true;
    }
    else
        return false;

}
