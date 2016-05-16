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

bool ChargeTable::ReadChargeRecords()
{
    QSqlTableModel *model = new QSqlTableModel;
    model->setTable(g_strClinicChargeDetails);
    model->setFilter("ChargeId = \'" + m_strID +"\'");
    model->select();

    m_chargeItems.clear();
    for(int i =0; i < model->rowCount();i++)
    {
        QSqlRecord record = model->record(i);

        ChargeItem *item = new ChargeItem;
        item->setChargeItemNo(record.value("ChargeItemNo").toString());
        item->setChargeItemName(record.value("ChargeItemName").toString());
        item->setChargeItemCount(record.value("ChargeItemCount").toInt());
        item->setChargeItemPrice(record.value("ChargeItemPrice").toDouble());
        item->setReceipt(record.value("ChinicReceipt").toString());
        item->setSort(record.value("ClinicSort").toString());
        item->setChargeId(record.value("ClinicChargeId").toString());

        m_chargeItems.append(item);
    }

    return true;

}

bool ChargeTable::saveChargeRecords()
{

    HISTable::deleteRows(g_strClinicChargeDetails,"ChargeId",m_strID);

    QSqlTableModel *model = new QSqlTableModel;
    model->setTable(g_strClinicChargeDetails);

    for(int i = 0; i < m_chargeItems.size(); i++)
    {
        int row = i;
        model->insertRows(row,1);
        model->setData(model->index(row,chargeItemNo),m_chargeItems.at(row)->getChargeItemNo());
        model->setData(model->index(row,chargeItemName),m_chargeItems.at(row)->getChargeItemName());
        model->setData(model->index(row,chargeItemCount),m_chargeItems.at(row)->getChargeItemCount());
        model->setData(model->index(row,chargeItemPrice),m_chargeItems.at(row)->getChargeItemPrice());
        model->setData(model->index(row,clinicReceipt),m_chargeItems.at(row)->getReceipt());
        model->setData(model->index(row,clinicSort),m_chargeItems.at(row)->getSort());
        model->setData(model->index(row,clinicChargeId),m_chargeItems.at(row)->getChargeId());
        model->submitAll();
    }

    return true;
}
