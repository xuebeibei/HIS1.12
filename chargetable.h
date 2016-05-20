#ifndef CHARGETABLE_H
#define CHARGETABLE_H
#include "stdafx.h"
#include "chargeitem.h"
#include "histable.h"

const QString strCharge = QObject::tr("Charge");
const QString strId = strCharge + QObject::tr("Id");
const QString strItemNo = strCharge +  QObject::tr("ItemNo");
const QString strItemName = strCharge +  QObject::tr("ItemName");
const QString strItemCount = strCharge + QObject::tr("ItemCount");
const QString strItemPrice = strCharge + QObject::tr("ItemPrice");
const QString strClinicReceipt = QObject::tr("ClinicReceipt");
const QString strClinicSort = QObject::tr("ClinicSort");
const QString strHospitalReceipt = QObject::tr("HospitalReceipt");
const QString strHospitalSort = QObject::tr("HospitalSort");

class ChargeTable
{
public:
    ChargeTable();

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：getID
    // 作用：得到收费单单号
    // 参数：无
    // 返回值：
    // QString - 收费单单号
    // 备注：无
    // 时间：2016-05-13
    //-----------------------------------------------------------------------------------------------------------------------------------
    QString getID() const;

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：getMaker
    // 作用：得到制单人
    // 参数：无
    // 返回值：
    // QString - 收费制单人
    // 备注：无
    // 时间：2016-05-13
    //-----------------------------------------------------------------------------------------------------------------------------------
    QString getMaker() const;

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：getDueIncome
    // 作用：得到应收金额
    // 参数：无
    // 返回值：
    // double - 应收金额
    // 备注：无
    // 时间：2016-05-13
    //-----------------------------------------------------------------------------------------------------------------------------------
    double getDueIncome() const;

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：getChargeItems
    // 作用：得到收费项列表
    // 参数：无
    // 返回值：
    // QVector<ClinicChargeItem*> - 收费项详细列表
    // 备注：无
    // 时间：2016-05-13
    //-----------------------------------------------------------------------------------------------------------------------------------
    QVector<ChargeItem*> getChargeItems() const;

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：getTime
    // 作用：得到收费单的保存时间
    // 参数：无
    // 返回值：
    // QDateTime - 门诊收费单在保存进数据库的时候会获得当前时间，在门诊日结的时候需要显示这个时间
    // 备注：无
    // 时间：2016-05-13
    //-----------------------------------------------------------------------------------------------------------------------------------
    QDateTime getTime() const;

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：setID
    // 作用：设置收费单号
    // 参数：
    // strID - 收费单号
    // 返回值：无
    // 备注：无
    // 时间：2016-05-13
    //-----------------------------------------------------------------------------------------------------------------------------------
    void setID(QString strID);

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：setMaker
    // 作用：设置制单人
    // 参数：
    // strMaker - 收费制单人
    // 返回值：无
    // 备注：无
    // 时间：2016-05-13
    //-----------------------------------------------------------------------------------------------------------------------------------
    void setMaker(QString strMaker);

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：setDueIncome
    // 作用：设置应收金额
    // 参数：
    // d_DueIncome - 应收金额
    // 返回值：无
    // 备注：无
    // 时间：2016-05-13
    //-----------------------------------------------------------------------------------------------------------------------------------
    void setDueIncome(double dDueIncome);

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：setChargeItems
    // 作用：设置收费详细列表
    // 参数：
    // chargeItems - 收费项详细列表
    // 返回值：无
    // 备注：无
    // 时间：2016-05-13
    //-----------------------------------------------------------------------------------------------------------------------------------
    void setChargeItems(QVector<ChargeItem*> chargeItems);

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：ReadChargeRecords
    // 作用：根据收费单号从数据库中读取该收费单号对应的所有收费记录
    // 参数：无
    // 返回值：
    // true  - 读取成功
    // false - 读取失败
    // 备注：无
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    bool ReadChargeRecords(PatientType eType);

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：saveChargeRecords
    // 作用：将该收费单的所有收费记录保存到数据库
    // 参数：无
    // 返回值：
    // true  - 保存成功
    // false - 保存失败
    // 备注：无
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    bool saveChargeRecords(PatientType eType);

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：deleteChargeRecords
    // 作用：根据自身单号从数据库中删除收费单对应的所有收费记录
    // 参数：无
    // 返回值：
    // true  - 删除成功
    // false - 删除失败
    // 备注：无
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    bool deleteChargeRecords();

protected:
    QString m_strID;                          // 收费单单号
    QString m_strMaker;                       // 制单员
    double  m_dDueIncome;                     // 应收金额
    QDateTime m_time;                         // 保存进数据库的时间
    QVector<ChargeItem*> m_chargeItems;       // 收费明细列表
};

#endif // CHARGETABLE_H
