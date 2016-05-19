#include "internalpaymentform.h"

InternalPaymentForm::InternalPaymentForm(SubForm *parent) :
    SubForm(parent)
{
    create();
    init();
}

InternalPaymentForm::~InternalPaymentForm()
{
    delete m_startDateLabel;
    delete m_endDateLabel;

    delete m_startDateEdit;
    delete m_endDateEdit;

    delete m_allDueIncomeLabel;
    delete m_allDueIncomeEdit;

    delete m_resultView;
    delete m_resultModel;

}

void InternalPaymentForm::newTableFile()
{
}

bool InternalPaymentForm::saveTableFile()
{
    return false;
}

bool InternalPaymentForm::deleteTableFile()
{
    return false;
}

void InternalPaymentForm::exportTableFile()
{
    return;
}

bool InternalPaymentForm::findTableFile()
{
    return false;
}

void InternalPaymentForm::amendTableFile()
{
    return;
}

void InternalPaymentForm::previewTableFile()
{
    return;
}

void InternalPaymentForm::printTableFile()
{
    return;
}

void InternalPaymentForm::create()
{
    m_startDateLabel = new QLabel(g_strStartDateLabel);
    m_startDateEdit = new QDateEdit;
    m_startDateEdit->setCalendarPopup(true);
    m_startDateEdit->setMaximumDateTime(QDateTime::currentDateTime());

    m_endDateLabel = new QLabel(g_strEndDateLabel);
    m_endDateEdit = new QDateEdit;
    m_endDateEdit->setCalendarPopup(true);
    m_endDateEdit->setMaximumDateTime(QDateTime::currentDateTime());

    m_allDueIncomeLabel = new QLabel("应收合计：");
    m_allDueIncomeEdit = new QLineEdit;
    m_allDueIncomeEdit->setReadOnly(true);

    m_resultView = new QTableView;
    m_resultModel = new QStandardItemModel;
    m_resultView->setModel(m_resultModel);
    m_resultView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void InternalPaymentForm::init()
{
    m_startDateEdit->setDate(QDate::currentDate());
    m_endDateEdit->setDate(QDate::currentDate());
}

void InternalPaymentForm::initTable(QStringList strList)
{
    m_resultModel->clear();
    for(int i = 0; i < strList.size(); i++)
    {
        m_resultModel->setHorizontalHeaderItem(i,new QStandardItem(strList.at(i)));
    }
}

void InternalPaymentForm::setMyLayout()
{
}

void InternalPaymentForm::updateIncome()
{
    double dAllDueIncome = 0.0;
    for(int i = 0; i < m_resultModel->rowCount();i++)
    {
        QStandardItem *dueIncomeItem = m_resultModel->item(i,1);
        double dDueIncome  = (dueIncomeItem == NULL) ? 0 : dueIncomeItem->text().toDouble();
        dAllDueIncome += dDueIncome;
    }
    m_allDueIncomeEdit->setText(QString::number(dAllDueIncome));
}
