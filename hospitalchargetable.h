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

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：selectFromDB
    // 作用：从数据库中查找一段时间内，某个人或者所有人的住院收费单
    // 参数：
    // startDate - 起始查找日期
    // endDate - 结束查找日期
    // inpatientID - 一个人的住院号，如果为空则查询所有人的收费单
    // 返回值：
    // QVector<HospitalChargeTable*>* - 收费单数组
    // 备注：无
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    static QVector<HospitalChargeTable*>* selectFromDB(QDate startDate, QDate endDate, QString inpatientID);

protected:
    QString m_InpatientID;                    // 患者住院号
};

#endif // HOSPITALCHARGETABLE_H
