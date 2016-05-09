#include "clinicreportstatisticform.h"
#include "clinicdailyreporttable.h"
#include "connectDB.h"

ClinicReportStatisticForm::ClinicReportStatisticForm(SubForm *parent) :
    SubForm(parent)
{
    create();
    setMyLayout();
    init();
}

ClinicReportStatisticForm::~ClinicReportStatisticForm()
{

}

void ClinicReportStatisticForm::newTableFile()
{
}

bool ClinicReportStatisticForm::saveTableFile()
{
    return true;
}

bool ClinicReportStatisticForm::deleteTableFile()
{
    return true;
}

void ClinicReportStatisticForm::exportTableFile()
{
}

bool ClinicReportStatisticForm::findTableFile()
{
    return true;
}

void ClinicReportStatisticForm::amendTableFile()
{
}

void ClinicReportStatisticForm::previewTableFile()
{
}

void ClinicReportStatisticForm::printTableFile()
{
}

void ClinicReportStatisticForm::create()
{
    m_startDateLabel = new QLabel(g_strStartDateLabel);
    m_startDateEdit = new QDateEdit;
    m_startDateEdit->setCalendarPopup(true);
    m_startDateEdit->setMaximumDate(QDate::currentDate());
    connect(m_startDateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(updateTable()));
    m_endDateLabel = new QLabel(g_strEndDateLabel);
    m_endDateEdit = new QDateEdit;
    m_endDateEdit->setCalendarPopup(true);
    m_endDateEdit->setMaximumDate(QDate::currentDate());
    connect(m_endDateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(updateTable()));

    m_resultsView = new QTableView;
    m_resultsModel = new QStandardItemModel;
    m_resultsView->setModel(m_resultsModel);
    m_resultsView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_resultsView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void ClinicReportStatisticForm::setMyLayout()
{
    QHBoxLayout *mainLayout = new QHBoxLayout;
    QVBoxLayout *leftLayout = new QVBoxLayout;
    QVBoxLayout *rightLayout = new QVBoxLayout;
    QGridLayout *leftTopLayout = new QGridLayout;

    leftTopLayout->addWidget(m_startDateLabel,0,0);
    leftTopLayout->addWidget(m_startDateEdit,0,1);
    leftTopLayout->addWidget(m_endDateLabel,1,0);
    leftTopLayout->addWidget(m_endDateEdit,1,1);

    leftLayout->addLayout(leftTopLayout);
    leftLayout->addStretch();

    rightLayout->addWidget(m_resultsView);

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    mainLayout->setStretchFactor(rightLayout, 1);

    setLayout(mainLayout);
}

void ClinicReportStatisticForm::init()
{
    initTable();
    m_startDateEdit->setDate(QDate::currentDate());
    m_endDateEdit->setDate(QDate::currentDate());
}

void ClinicReportStatisticForm::initTable()
{
    m_resultsModel->clear();
    m_resultsModel->setHorizontalHeaderItem(0, new QStandardItem("日结单号"));
    m_resultsModel->setHorizontalHeaderItem(1, new QStandardItem("应收合计"));
    m_resultsModel->setHorizontalHeaderItem(2, new QStandardItem("实收合计"));
    m_resultsModel->setItem(0, 2, NULL);
}

void ClinicReportStatisticForm::updateTable()
{
    initTable();

    QDate startDate = m_startDateEdit->date();
    QDate endDate = m_endDateEdit->date();
    if(endDate < startDate)
        return;
    QVector<ClinicDailyReportTable*> record = ClinicDailyReportTable::getRecord(startDate,endDate);

    for(int i = 0; i < record.size();i++)
    {
        ClinicDailyReportTable *table = record.at(i);
        m_resultsModel->setItem(i,0,new QStandardItem(table->getId()));
        m_resultsModel->setItem(i,1,new QStandardItem(QString::number(table->getAllDueIncome())));
        m_resultsModel->setItem(i,2,new QStandardItem(QString::number(table->getAllRealIncome())));
    }
    m_resultsView->setModel(m_resultsModel);


}
