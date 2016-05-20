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

bool ChargeTable::ReadChargeRecords(PatientType eType)
{
    QSqlTableModel *model = new QSqlTableModel;
    model->setTable(g_strChargeDetails);
    model->setFilter(strId + " = \'" + m_strID +"\'");
    model->select();

    m_chargeItems.clear();
    for(int i =0; i < model->rowCount();i++)
    {
        QSqlRecord record = model->record(i);

        ChargeItem *item = new ChargeItem;
        item->setChargeId(record.value(strId).toString());
        item->setChargeItemNo(record.value(strItemNo).toString());
        item->setChargeItemName(record.value(strItemName).toString());
        item->setChargeItemCount(record.value(strItemCount).toInt());
        item->setChargeItemPrice(record.value(strItemPrice).toDouble());

        if(eType == ClinicPatient)
        {
            item->setReceipt(record.value(strClinicReceipt).toString());
            item->setSort(record.value(strClinicSort).toString());
        }
        else if(eType == HospitalInPatient)
        {
            item->setReceipt(record.value(strHospitalReceipt).toString());
            item->setSort(record.value(strHospitalSort).toString());
        }


        m_chargeItems.append(item);
    }

    return true;
}

bool ChargeTable::saveChargeRecords(PatientType eType)
{

    HISTable::deleteRows(g_strChargeDetails,strId,m_strID);

    QSqlTableModel *model = new QSqlTableModel;
    model->setTable(g_strChargeDetails);

    for(int i = 0; i < m_chargeItems.size(); i++)
    {
        int row = i;
        model->insertRows(row,1);
        model->setData(model->index(row,chargeItemNo),m_chargeItems.at(row)->getChargeItemNo());
        model->setData(model->index(row,chargeItemName),m_chargeItems.at(row)->getChargeItemName());
        model->setData(model->index(row,chargeItemCount),m_chargeItems.at(row)->getChargeItemCount());
        model->setData(model->index(row,chargeItemPrice),m_chargeItems.at(row)->getChargeItemPrice());
        if(eType == ClinicPatient)
        {
            model->setData(model->index(row,clinicReceipt),m_chargeItems.at(row)->getReceipt());
            model->setData(model->index(row,clinicSort),m_chargeItems.at(row)->getSort());
        }
        else if(eType == HospitalInPatient)
        {
            model->setData(model->index(row,hospitalReceipt),m_chargeItems.at(row)->getReceipt());
            model->setData(model->index(row,hospitalSort),m_chargeItems.at(row)->getSort());
        }

        model->setData(model->index(row,ChargeId),m_chargeItems.at(row)->getChargeId());
        model->submitAll();
    }
    return true;
}

bool ChargeTable::deleteChargeRecords()
{
     return HISTable::deleteRows(g_strChargeDetails,strId,m_strID);
}
