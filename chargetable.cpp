#include "chargetable.h"

ChargeTable::ChargeTable()
{
    m_strID = g_strNull;
    m_strMaker = g_strNull;
    m_dDueIncome = 0.0;
    m_time = QDateTime::currentDateTime();
    m_chargeItems.resize(0);
}

QString ChargeTable::getID() const
{
    return m_strID;
}

QString ChargeTable::getMaker() const
{
    return m_strMaker;
}

double ChargeTable::getDueIncome() const
{
    return m_dDueIncome;
}

QVector<ChargeItem *> ChargeTable::getChargeItems() const
{
    return m_chargeItems;
}

QDateTime ChargeTable::getTime() const
{
    return m_time;
}

void ChargeTable::setID(QString strID)
{
    m_strID = strID;
}

void ChargeTable::setMaker(QString strMaker)
{
    m_strMaker = strMaker;
}

void ChargeTable::setDueIncome(double dDueIncome)
{
    m_dDueIncome = dDueIncome;
}

void ChargeTable::setChargeItems(QVector<ChargeItem *> chargeItems)
{
    m_chargeItems.clear();
    for(int i = 0; i< chargeItems.size(); i++)
    {
        ChargeItem* item = new ChargeItem(chargeItems.at(i));
        m_chargeItems.append(item);
    }
}
