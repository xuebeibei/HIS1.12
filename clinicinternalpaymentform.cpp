#include "clinicinternalpaymentform.h"
#include "connectDB.h"

ClinicInternalPaymentForm::ClinicInternalPaymentForm(SubForm *parent) :
    SubForm(parent)
{
    create();
    setMyLayout();
    init();
}

ClinicInternalPaymentForm::~ClinicInternalPaymentForm()
{

}

void ClinicInternalPaymentForm::newTableFile()
{
    updateTable();
}

bool ClinicInternalPaymentForm::saveTableFile()
{
    return false;
}

bool ClinicInternalPaymentForm::deleteTableFile()
{
    return false;
}

void ClinicInternalPaymentForm::exportTableFile()
{
    return;
}

bool ClinicInternalPaymentForm::findTableFile()
{
    return false;
}

void ClinicInternalPaymentForm::amendTableFile()
{
    return;
}

void ClinicInternalPaymentForm::previewTableFile()
{
    return;
}

void ClinicInternalPaymentForm::printTableFile()
{
    return;
}

void ClinicInternalPaymentForm::create()
{
    m_startDateLabel = new QLabel(g_strStartDateLabel);
    m_startDateEdit = new QDateEdit;
    m_startDateEdit->setCalendarPopup(true);
    m_startDateEdit->setMaximumDateTime(QDateTime::currentDateTime());
    connect(m_startDateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(updateTable()));

    m_endDateLabel = new QLabel(g_strEndDateLabel);
    m_endDateEdit = new QDateEdit;
    m_endDateEdit->setCalendarPopup(true);
    m_endDateEdit->setMaximumDateTime(QDateTime::currentDateTime());
    connect(m_endDateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(updateTable()));

    m_allDueIncomeLabel = new QLabel("应收合计：");
    m_allDueIncomeEdit = new QLineEdit;
    m_allDueIncomeEdit->setReadOnly(true);

    m_resultView = new QTableView;
    m_resultModel = new QStandardItemModel;
    m_resultView->setModel(m_resultModel);
    m_resultView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void ClinicInternalPaymentForm::init()
{
    initTable();
    m_startDateEdit->setDate(QDate::currentDate());
    m_endDateEdit->setDate(QDate::currentDate());
}

void ClinicInternalPaymentForm::initTable()
{
    m_resultModel->clear();
    m_resultModel->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("门诊收据")));
    m_resultModel->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("应收金额")));
    m_resultModel->setItem(0, 1, NULL);
}

void ClinicInternalPaymentForm::setMyLayout()
{
    QGridLayout *leftTopLayout = new QGridLayout;
    leftTopLayout->addWidget(m_startDateLabel,0,0);
    leftTopLayout->addWidget(m_startDateEdit,0,1);
    leftTopLayout->addWidget(m_endDateLabel,1,0);
    leftTopLayout->addWidget(m_endDateEdit,1,1);
    leftTopLayout->addWidget(m_allDueIncomeLabel,2,0);
    leftTopLayout->addWidget(m_allDueIncomeEdit,2,1);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(leftTopLayout);

    leftLayout->addStretch();

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(m_resultView);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    mainLayout->setStretchFactor(rightLayout,1);

    setLayout(mainLayout);
}

void ClinicInternalPaymentForm::updateTable()
{
    QVector<InternalPaymentItem*> payments = ClinicInternalPayment::selectFromDB(m_startDateEdit->date(), m_endDateEdit->date());

    initTable();
    for(int i = 0; i < payments.size() ; i++)
    {
        m_resultModel->setItem(i, 0, new QStandardItem(payments.at(i)->m_strName));
        m_resultModel->setItem(i, 1, new QStandardItem(QString::number(payments.at(i)->m_dDueIncome)));
    }
    updateIncome();
}

void ClinicInternalPaymentForm::updateIncome()
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
