#ifndef HOSPITALSATIONREGISTRYTABLE_H
#define HOSPITALSATIONREGISTRYTABLE_H
#include "stdafx.h"
#include "histable.h"
#include "inpatient.h"
#include "connectDB.h"

class HospitalsationRegistryTable : public HISTable
{
public:
    HospitalsationRegistryTable();
    bool Read();
    bool Save();
    bool Delete();
    Inpatient* getInpatient() const;
    QDate getRegistryDate() const;

    void setInpatient(Inpatient* inpatient);
    void setRegistryDate(QDate registryDate);
protected:
    Inpatient *m_inpatient;  // 住院患者
    QDate m_registryDate;   // 登记日期
};

#endif // HOSPITALSATIONREGISTRYTABLE_H
