#ifndef INPATIENT_H
#define INPATIENT_H
#include "patient.h"
#include "stdafx.h"
#include "winSet.h"
#include "account.h"
#include "contacts.h"
#include "histable.h"

class Inpatient : public Patient, public HISTable
{
public:
    Inpatient();
    ~Inpatient();
    QString getID() const;
    QString getCaseID() const;
    int     getBedNum() const;
    NursingLevel getNursingLevel() const;
    QString getMedicalResult() const;
    Contacts getContacts() const;
    QDate getRegistryDate() const;

    void setID(QString strID);
    void setCaseID(QString strCaseID);
    void setBedNum(int nBedNum);
    void setNursingLevel(NursingLevel eNursingLevel);
    void setMedicalResult(QString strmedicalResult);
    void setContacts(Contacts contacts);
    void setRegistryDate(QDate registryDate);

    bool Read();
    bool Save();
    bool Delete();

    static QStringList getIDsFromDB(QString strID, QString strName, Gender eGender);
    static QVector<Inpatient* > selectFromDB(QString strID, QString strName, Gender eGender);
    static QString getNameByID(QString strID);

    static bool isLeaveHospital(QString strID);
protected:
    QString m_strID;              // 住院号
    QString m_strCaseID;          // 病例号*
    unsigned int m_nBedNum;       // 床位
    NursingLevel m_eNursingLevel; // 护理级别
    QString m_strMedicalResult;   // 诊断结果
    Contacts m_contacts;          // 联系人
    QDate m_registryDate;         // 登记日期
};

#endif // INPATIENT_H
