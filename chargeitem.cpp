#include "chargeitem.h"

ChargeItem::ChargeItem()
{
    this->m_strChargeItemNo = g_strNull;
    this->m_strChargeItemName = g_strNull;
    this->m_nChargeItemCount = 0;
    this->m_dChargeItemPrice = 0;
    this->m_strReceipt = g_strNull;
    this->m_strSort = g_strNull;
    this->m_strChargeId = g_strNull;
}

ChargeItem::ChargeItem(QString strChargeItemNo,
                                   QString strChargeItemName,
                                   int nChargeItemCount,
                                   double dChargeItemPrice,
                                   QString strReceipt,
                                   QString strSort,
                                   QString strChargeId)
{
    this->m_strChargeItemNo = strChargeItemNo;
    this->m_strChargeItemName = strChargeItemName;
    this->m_nChargeItemCount = nChargeItemCount;
    this->m_dChargeItemPrice = dChargeItemPrice;
    this->m_strReceipt = strReceipt;
    this->m_strSort = strSort;
    this->m_strChargeId = strChargeId;
}

ChargeItem::ChargeItem(ChargeItem* chargeItem)
{
    this->m_strChargeItemNo = chargeItem->m_strChargeItemNo;
    this->m_strChargeItemName = chargeItem->m_strChargeItemName;
    this->m_nChargeItemCount = chargeItem->m_nChargeItemCount;
    this->m_dChargeItemPrice = chargeItem->m_dChargeItemPrice;
    this->m_strReceipt = chargeItem->m_strReceipt;
    this->m_strSort = chargeItem->m_strSort;
    this->m_strChargeId = chargeItem->m_strChargeId;
}

QString ChargeItem::getChargeItemNo() const
{
    return m_strChargeItemNo;
}

QString ChargeItem::getChargeItemName() const
{
    return m_strChargeItemName;
}

int ChargeItem::getChargeItemCount() const
{
    return m_nChargeItemCount;
}

double ChargeItem::getChargeItemPrice() const
{
    return m_dChargeItemPrice;
}

QString ChargeItem::getReceipt() const
{
    return m_strReceipt;
}

QString ChargeItem::getSort() const
{
    return m_strSort;
}

QString ChargeItem::getChargeId() const
{
    return m_strChargeId;
}

void ChargeItem::setChargeItemNo(QString strChargeItemNo)
{
    this->m_strChargeItemNo = strChargeItemNo;
}

void ChargeItem::setChargeItemName(QString strChargeItemName)
{
    this->m_strChargeItemName = strChargeItemName;
}

void ChargeItem::setChargeItemCount(int nChargeItemCount)
{
    this->m_nChargeItemCount = nChargeItemCount;
}

void ChargeItem::setChargeItemPrice(double dChargeItemPrice)
{
    this->m_dChargeItemPrice = dChargeItemPrice;
}

void ChargeItem::setReceipt(QString strReceipt)
{
    this->m_strReceipt = strReceipt;
}

void ChargeItem::setSort(QString strSort)
{
    this->m_strSort = strSort;
}

void ChargeItem::setChargeId(QString strChargeId)
{
    this->m_strChargeId = strChargeId;
}

bool ChargeItem::isEmptyItem()
{
    if(this->m_strChargeItemNo.isEmpty()
            &&this->m_strChargeItemName.isEmpty()
            &&(this->m_nChargeItemCount == 0)
            &&(this->m_dChargeItemPrice == 0)
            &&this->m_strReceipt.isEmpty()
            &&this->m_strSort.isEmpty())
        return true;
    else
        return false;
}
