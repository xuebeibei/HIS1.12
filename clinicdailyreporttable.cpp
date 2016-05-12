#include "clinicdailyreporttable.h"

ClinicDailyReportTable::ClinicDailyReportTable()
{
    m_strId = g_strDailyReopotNumPR + getNewID();
    m_strPrefixion = g_strDailyReopotNumPR;
    m_dAllDueIncome = 0;
    m_dAllRealIncome = 0;
    m_dAllDebt = 0;
    m_date = QDate::currentDate();
    m_strMaker = "A";
    m_time = QDateTime::currentDateTime();
}

ClinicDailyReportTable::~ClinicDailyReportTable()
{
}

bool ClinicDailyReportTable::Read()
{
   return readDailyReport();
}

bool ClinicDailyReportTable::Save()
{
    return saveDailyReport();
}

bool ClinicDailyReportTable::Delete()
{
    return deleteDailyReport();
}

QDateTime ClinicDailyReportTable::getDateTime()
{
    return m_time;
}

QString ClinicDailyReportTable::getId() const
{
    return m_strId;
}

QString ClinicDailyReportTable::getPrefixion() const
{
    return m_strPrefixion;
}

double ClinicDailyReportTable::getAllDueIncome() const
{
    return m_dAllDueIncome;
}

double ClinicDailyReportTable::getAllRealIncome() const
{
    return m_dAllRealIncome;
}

double ClinicDailyReportTable::getAllDebt() const
{
    return m_dAllDebt;
}

QDate ClinicDailyReportTable::getdate() const
{
    return m_date;
}


void ClinicDailyReportTable::setId(QString strId)
{
    this->m_strId = strId;
}

void ClinicDailyReportTable::setPrefixion(QString strPrefixion)
{
    this->m_strPrefixion = strPrefixion;
}

void ClinicDailyReportTable::setAllDueIncome(double dAllDueIncome)
{
    this->m_dAllDueIncome = dAllDueIncome;
}

void ClinicDailyReportTable::setAllRealIncome(double dAllRealIncome)
{
    this->m_dAllRealIncome = dAllRealIncome;
}

void ClinicDailyReportTable::setAllDebt(double dAllDebt)
{
    this->m_dAllDebt = dAllDebt;
}

void ClinicDailyReportTable::setDate(QDate date)
{
    this->m_date = date;
}

QVector<ClinicDailyReportTable*> ClinicDailyReportTable::getRecord(QDate startDate, QDate endDate)
{
    QVector<ClinicDailyReportTable*> list;
    if(myDB::connectDB())
    {
        QSqlTableModel *model = new QSqlTableModel;
        model->setTable(g_strClinicDailyReport);
        QString strStartTime = startDate.toString("yyyy-MM-dd")/* + "T00:00:00"*/;
        QString strEndTime = endDate.toString("yyyy-MM-dd")/* + "T23:59:59"*/;
        model->setFilter("Date between \'" + strStartTime + "\' and \'" +strEndTime +"\'");
        model->select();

        for(int i = 0; i < model->rowCount(); i++)
        {
            ClinicDailyReportTable *table = new ClinicDailyReportTable;
            QSqlRecord record = model->record(i);
            table->setId(record.value("Id").toString());
            table->setDate(record.value("Date").toDate());
            table->setAllDueIncome(record.value("AllDueIncome").toDouble());
            table->setAllRealIncome(record.value("AllRealIncome").toDouble());
            list.append(table);
        }
    }
    return list;
}

bool ClinicDailyReportTable::readDailyReport()
{
    if(myDB::connectDB())
    {
        QSqlTableModel *model = new QSqlTableModel;
        model->setTable(g_strClinicDailyReport);
        model->setFilter("Id = \'" + m_strId + "\'");
        model->select();

        if(model->rowCount() == 1)
        {
            QSqlRecord record = model->record(0);
            m_strId = record.value("Id").toString();
            m_date = record.value("Date").toDate();
            m_dAllDueIncome = record.value("AllDueIncome").toDouble();
            m_dAllRealIncome = record.value("AllRealIncome").toDouble();
            m_dAllDebt = m_dAllDueIncome - m_dAllRealIncome;
            m_strMaker = record.value("Maker").toString();
            m_time = record.value("ReportTime").toDateTime();
            return true;
        }
        else
        {
            return false;
        }
    }
    else
        return false;
}

bool ClinicDailyReportTable::saveDailyReport()
{
    deleteDailyReport();
    if(myDB::connectDB())
    {
        QSqlTableModel *model = new QSqlTableModel;
        model->setTable(g_strClinicDailyReport);

        int row =0;
        model->insertRows(row,1);
        model->setData(model->index(row,0),m_strId);
        model->setData(model->index(row,1),m_date.toString("yyyy-MM-dd"));

        model->setData(model->index(row,2),m_time);
        model->setData(model->index(row,3),QString::number(m_dAllDueIncome));
        model->setData(model->index(row,4),QString::number(m_dAllRealIncome));
        model->setData(model->index(row,5),m_strMaker);
        model->submitAll();
        return true;
    }
    else
        return false;
}

bool ClinicDailyReportTable::deleteDailyReport()
{
    if(myDB::connectDB())
    {
        return deleteRows(g_strClinicDailyReport,"Id",m_strId);
    }
    else
        return false;
}

