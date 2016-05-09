#include "finddailyreportdialog.h"
#include "clinicdailyreporttable.h"

FindDailyReportDialog::FindDailyReportDialog(QWidget *parent) :
    QDialog(parent)
{
    create();
    setMyLayout();
    init();
}

FindDailyReportDialog::~FindDailyReportDialog()
{
    delete m_dateEdit;
    delete m_findButton;
    delete m_resultsView;
    delete m_resultsModel;
    delete m_choiseButton;
    delete m_cancelButton;
}

QString FindDailyReportDialog::getID()
{
    return m_strId;
}

void FindDailyReportDialog::create()
{
    m_dateEdit = new QDateEdit;
    m_dateEdit->setCalendarPopup(true);
    m_findButton = new QToolButton;
    m_findButton->setIcon(QIcon(g_strIconPath + "find.png"));
    connect(m_findButton, SIGNAL(clicked()), this, SLOT(find()));

    m_resultsView = new QTableView;
    m_resultsModel = new QStandardItemModel;
    m_resultsView->setModel(m_resultsModel);
    connect(m_resultsView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(choise()));

    m_choiseButton = new QPushButton(g_strChoiseButton);
    connect(m_choiseButton, SIGNAL(clicked()), this, SLOT(choise()));

    m_cancelButton = new QPushButton(g_strCancelButton);
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

void FindDailyReportDialog::setMyLayout()
{
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(m_dateEdit);
    topLayout->addStretch();
    topLayout->addWidget(m_findButton);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addStretch();
    bottomLayout->addWidget(m_choiseButton);
    bottomLayout->addWidget(m_cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(m_resultsView);
    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);
}

void FindDailyReportDialog::init()
{
    m_dateEdit->setDate(QDate::currentDate());
    m_resultsView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_resultsView->setSelectionBehavior(QAbstractItemView::SelectRows);
    initTable();
}

void FindDailyReportDialog::initTable()
{
    m_resultsModel->clear();
    m_resultsModel->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("日结单号")));
    m_resultsModel->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("应收合计")));
    m_resultsModel->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("实收合计")));
    m_resultsModel->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("制单时间")));
    m_resultsModel->setItem(0, 3, NULL);
}

void FindDailyReportDialog::choise()
{
    QModelIndex index = m_resultsView->currentIndex();
    if(index.isValid())
    {
        QStandardItem *item = m_resultsModel->item(index.row(),0);
        m_strId = item->text();
        close();
    }
}

void FindDailyReportDialog::find()
{
    initTable();

    QVector<ClinicDailyReportTable*> record = ClinicDailyReportTable::getRecord(m_dateEdit->date(),m_dateEdit->date());

    for(int i = 0; i < record.size();i++)
    {
        ClinicDailyReportTable *table = record.at(i);
        m_resultsModel->setItem(i,0,new QStandardItem(table->getId()));
        m_resultsModel->setItem(i,1,new QStandardItem(QString::number(table->getAllDueIncome())));
        m_resultsModel->setItem(i,2,new QStandardItem(QString::number(table->getAllRealIncome())));
    }
    m_resultsView->setModel(m_resultsModel);
}
