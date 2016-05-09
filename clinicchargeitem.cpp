#include "clinicchargeitem.h"

ClinicChargeItem::ClinicChargeItem()
{
    this->m_strChargeItemNo = g_strNull;
    this->m_strChargeItemName = g_strNull;
    this->m_nChargeItemCount = 0;
    this->m_dChargeItemPrice = 0;
    this->m_strClinicReceipt = g_strNull;
    this->m_strClinicSort = g_strNull;
    this->m_strClinicChargeId = g_strNull;
}

ClinicChargeItem::ClinicChargeItem(QString strChargeItemNo,
                                   QString strChargeItemName,
                                   int nChargeItemCount,
                                   double dChargeItemPrice,
                                   QString strClinicReceipt,
                                   QString strClinicSort,
                                   QString strClinicChargeId)
{
    this->m_strChargeItemNo = strChargeItemNo;
    this->m_strChargeItemName = strChargeItemName;
    this->m_nChargeItemCount = nChargeItemCount;
    this->m_dChargeItemPrice = dChargeItemPrice;
    this->m_strClinicReceipt = strClinicReceipt;
    this->m_strClinicSort = strClinicSort;
    this->m_strClinicChargeId = strClinicChargeId;
}

ClinicChargeItem::ClinicChargeItem(ClinicChargeItem* chargeItem)
{
    this->m_strChargeItemNo = chargeItem->m_strChargeItemNo;
    this->m_strChargeItemName = chargeItem->m_strChargeItemName;
    this->m_nChargeItemCount = chargeItem->m_nChargeItemCount;
    this->m_dChargeItemPrice = chargeItem->m_dChargeItemPrice;
    this->m_strClinicReceipt = chargeItem->m_strClinicReceipt;
    this->m_strClinicSort = chargeItem->m_strClinicSort;
    this->m_strClinicChargeId = chargeItem->m_strClinicChargeId;
}

QString ClinicChargeItem::getChargeItemNo() const
{
    return m_strChargeItemNo;
}

QString ClinicChargeItem::getChargeItemName() const
{
    return m_strChargeItemName;
}

int ClinicChargeItem::getChargeItemCount() const
{
    return m_nChargeItemCount;
}

double ClinicChargeItem::getChargeItemPrice() const
{
    return m_dChargeItemPrice;
}

QString ClinicChargeItem::getClinicReceipt() const
{
    return m_strClinicReceipt;
}

QString ClinicChargeItem::getClinicSort() const
{
    return m_strClinicSort;
}

QString ClinicChargeItem::getClinicChargeId() const
{
    return m_strClinicChargeId;
}

void ClinicChargeItem::setChargeItemNo(QString strChargeItemNo)
{
    this->m_strChargeItemNo = strChargeItemNo;
}

void ClinicChargeItem::setChargeItemName(QString strChargeItemName)
{
    this->m_strChargeItemName = strChargeItemName;
}

void ClinicChargeItem::setChargeItemCount(int nChargeItemCount)
{
    this->m_nChargeItemCount = nChargeItemCount;
}

void ClinicChargeItem::setChargeItemPrice(double dChargeItemPrice)
{
    this->m_dChargeItemPrice = dChargeItemPrice;
}

void ClinicChargeItem::setClinicReceipt(QString strClinicReceipt)
{
    this->m_strClinicReceipt = strClinicReceipt;
}

void ClinicChargeItem::setClinicSort(QString strClinicSort)
{
    this->m_strClinicSort = strClinicSort;
}

void ClinicChargeItem::setClinicChargeId(QString strClinicChargeId)
{
    this->m_strClinicChargeId = strClinicChargeId;
}

bool ClinicChargeItem::isEmptyItem()
{
    if(this->m_strChargeItemNo.isEmpty()
            &&this->m_strChargeItemName.isEmpty()
            &&(this->m_nChargeItemCount == 0)
            &&(this->m_dChargeItemPrice == 0)
            &&this->m_strClinicReceipt.isEmpty()
            &&this->m_strClinicSort.isEmpty())
        return true;
    else
        return false;
}
