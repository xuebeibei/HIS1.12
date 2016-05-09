#ifndef INPATIENT_H
#define INPATIENT_H
#include "patient.h"
#include "stdafx.h"
#include "winSet.h"
#include "account.h"
#include "contacts.h"

class Inpatient : public Patient
{
public:
    Inpatient(QString strID);
    QString getID() const;
    QString getCaseID() const;
    int     getBedNum() const;
    NursingLevel getNursingLevel() const;
    QString getMedicalResult() const;
    Account* getAccount() const;
    Contacts getContacts() const;

    void setID(QString strID);
    void setCaseID(QString strCaseID);
    void setBedNum(int nBedNum);
    void setNursingLevel(NursingLevel eNursingLevel);
    void setMedicalResult(QString strmedicalResult);
    void setAccount(Account *account);
    void setContacts(Contacts contacts);

    bool Read();
    bool Save();
protected:
    QString m_strID;              // 住院号
    QString m_strCaseID;          // 病例号*
    unsigned int m_nBedNum;       // 床位
    NursingLevel m_eNursingLevel; // 护理级别
    QString m_strMedicalResult;   // 诊断结果
    Account *m_account;           // 缴款账号
    Contacts m_contacts;          // 联系人
};

#endif // INPATIENT_H
