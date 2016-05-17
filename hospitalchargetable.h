#ifndef HOSPITALCHARGETABLE_H
#define HOSPITALCHARGETABLE_H
#include "stdafx.h"
#include "chargetable.h"
#include "histable.h"
#include "account.h"

class HospitalChargeTable : public ChargeTable, public HISTable
{
public:
    HospitalChargeTable();

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：getNewHospitalChargeID
    // 作用：根据年月日时分秒毫秒计算一个新的收费单单号
    // 参数：无
    // 返回值：
    // QString - 收费单编号
    // 备注：无
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    QString getNewHospitalChargeID();

    bool Read();
    bool Save();
    bool Delete();
    void setInpatientID(QString strInpatientID);
    QString getInpatientID() const;

protected:
    QString m_InpatientID;                    // 患者住院号
};

#endif // HOSPITALCHARGETABLE_H
