#ifndef CHARGEITEM_H
#define CHARGEITEM_H
#include "stdafx.h"

//-----------------------------------------------------------------------------------------------------------------------------------
// 收费记录类
//-----------------------------------------------------------------------------------------------------------------------------------
class ChargeItem
{
public:
    ChargeItem();

    ChargeItem(QString strChargeItemNo,
                     QString strChargeItemName,
                     int nChargeItemCount,
                     double dChargeItemPrice,
                     QString strReceipt,
                     QString strSort,
                     QString strChargeId);

    ChargeItem(ChargeItem* chargeItem);

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：getChargeItemNo
    // 作用：得到收费项编号
    // 参数：无
    // 返回值：
    // QString - 收费项编号
    // 备注：无
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    QString getChargeItemNo() const;

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：getChargeItemName
    // 作用：得到收费项名称
    // 参数：无
    // 返回值：
    // QString - 收费项名称
    // 备注：无
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    QString getChargeItemName() const;

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：getChargeItemCount
    // 作用：得到收费项数量
    // 参数：无
    // 返回值：
    // int - 收费项数量
    // 备注：无
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    int getChargeItemCount() const;

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：getChargeItemPrice
    // 作用：得到收费项单价
    // 参数：无
    // 返回值：
    // double - 收费项单价
    // 备注：无
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    double getChargeItemPrice() const;

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：getReceipt
    // 作用：得到收费项所属收据
    // 参数：无
    // 返回值：
    // QString -收费项所属收据
    // 备注：意义有待商讨
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    QString getReceipt() const;

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：getSort
    // 作用：得到收费项所属分类
    // 参数：无
    // 返回值：
    // QString - 收费项所属分类
    // 备注：意义有待商讨
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    QString getSort() const;

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：getChargeId
    // 作用：得到收费项纪录所在收费单单号
    // 参数：无
    // 返回值：
    // QString - 收费项所在收费单单号
    // 备注：无
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    QString getChargeId() const;

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：setChargeItemNo
    // 作用：设置收费项编号
    // 参数：
    // strChargeItemNo - 收费项编号
    // 返回值：无
    // 备注：无
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    void setChargeItemNo(QString strChargeItemNo);

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：setChargeItemName
    // 作用：设置收费项名称
    // 参数：
    // strChargeItemName - 收费项名称
    // 返回值：无
    // 备注：无
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    void setChargeItemName(QString strChargeItemName);

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：setChargeItemCount
    // 作用：设置收费项数量
    // 参数：
    // nChargeItemCount - 收费项数量
    // 返回值：无
    // 备注：无
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    void setChargeItemCount(int nChargeItemCount);

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：setChargeItemPrice
    // 作用：设置收费项单价
    // 参数：
    // dChargeItemPrice - 收费项单价
    // 返回值：无
    // 备注：无
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    void setChargeItemPrice(double dChargeItemPrice);

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：setReceipt
    // 作用：设置收费项所属收据
    // 参数：
    // strReceipt - 收据
    // 返回值：无
    // 备注：意义有待商讨
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    void setReceipt(QString strReceipt);

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：setSort
    // 作用：设置收费项所属分类
    // 参数：
    // strSort - 分类
    // 返回值：无
    // 备注：无
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    void setSort(QString strSort);

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：setChargeId
    // 作用：设置收费项所在收费单的单号
    // 参数：
    // strChargeId - 收费单单号
    // 返回值：无
    // 备注：无
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    void setChargeId(QString strChargeId);

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：isEmptyItem
    // 作用：判断收费记录是否为空
    // 参数：无
    // 返回值：
    // true  - 该收费记录为空
    // false - 该收费记录不为空
    // 备注：无
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    bool isEmptyItem();
protected:
    QString m_strChargeItemNo;     // 收费项编号
    QString m_strChargeItemName;   // 收费项名称
    int m_nChargeItemCount;        // 数量
    double m_dChargeItemPrice;     // 单价
    QString m_strReceipt;          // 收据（有待商讨）
    QString m_strSort;             // 分类（有待商讨）
    QString m_strChargeId;         // 收费项所在收费单单号
};

#endif // CHARGEITEM_H