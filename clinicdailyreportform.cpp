#include "clinicdailyreportform.h"
#include "clinicchargetable.h"
#include "finddailyreportdialog.h"

ClinicDailyReportFrom::ClinicDailyReportFrom(SubForm *parent) :
    SubForm(parent)
{
    create();
    setMyLayout();
    setAllDefaultEnable();
    init();
    newTableFile();
}

ClinicDailyReportFrom::~ClinicDailyReportFrom()
{
    delete m_dailyReportNumLabel;
    delete m_dateLabel;
    delete m_allDueIncomeLabel;
    delete m_allRealIncomeLabel;
    delete m_allDebtLabel;

    delete m_dailyReportNumEdit;
    delete m_allDueIncomeEdit;
    delete m_allRealIncomeEdit;
    delete m_allDebtEdit;

    delete m_dateEdit;
    delete m_dailyChargesView;

    delete m_dailyChargesModel;

    //delete m_dailyReportTable;
}

void ClinicDailyReportFrom::newTableFile()
{
    setAllDefaultEnable();
    m_dailyReportTable = new ClinicDailyReportTable;
    Read();
}

bool ClinicDailyReportFrom::saveTableFile()
{
    if(Save())
    {
        QMessageBox::information(this,"提示","保存成功！");
        setAllUnEnable();
        return true;
    }
    else
    {
        QMessageBox::information(this,"提示","保存失败！");
        return false;
    }
}

bool ClinicDailyReportFrom::deleteTableFile()
{
    QMessageBox *box = new QMessageBox;
    box->setWindowTitle(tr("警告"));
    box->setIcon(QMessageBox::Warning);
    box->setText(tr("确认删除当前日结单？"));
    box->setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    box->setButtonText(QMessageBox::Yes,"是");
    box->setButtonText(QMessageBox::No,"否");
    if(box->exec()==QMessageBox::Yes)
    {
        return Delete();
    }
    else
    {
        return false;
    }
}

void ClinicDailyReportFrom::exportTableFile()
{
    QMessageBox::information(this,"提示","导出 - 门诊日结");
}

bool ClinicDailyReportFrom::findTableFile()
{
    FindDailyReportDialog *dailog = new FindDailyReportDialog;
    dailog->exec();
    QString strID = dailog->getID();

    if(!strID.isEmpty())
    {
        m_dailyReportTable->setId(strID);
        Read();
        setAllUnEnable();
        return true;
    }
    return false;
}

void ClinicDailyReportFrom::amendTableFile()
{
    QMessageBox::information(this,"提示","修改 - 门诊日结 - 不可用");
}

void ClinicDailyReportFrom::previewTableFile()
{
    QMessageBox::information(this,"提示","预览 - 门诊日结");
}

void ClinicDailyReportFrom::printTableFile()
{
    QMessageBox::information(this,"提示","打印 - 门诊日结");
}

void ClinicDailyReportFrom::updateCharges(QDateTime ReportTime)
{
    initTable();
    QVector<ClinicChargeTable*> vecClinicCharges;
    vecClinicCharges = ClinicChargeTable::selectClinicChargesFromDb(m_dateEdit->date() , ReportTime);

    for(int index = 0; index < vecClinicCharges.size(); index++)
    {
        ClinicChargeTable *charge = vecClinicCharges.at(index);

        m_dailyChargesModel->setItem(index, 0, new QStandardItem(charge->getID()));
        m_dailyChargesModel->setItem(index, 1, new QStandardItem(charge->getTime().toString("yyyy-MM-dd hh:mm:ss")));
        m_dailyChargesModel->setItem(index, 2, new QStandardItem(QString::number(charge->getDueIncome())));
        m_dailyChargesModel->setItem(index, 3, new QStandardItem(QString::number(charge->getRealImcome())));
        m_dailyChargesModel->setItem(index, 4, new QStandardItem(QString::number(charge->getDueIncome() - charge->getRealImcome())));
    }
    updateIncome();
}

void ClinicDailyReportFrom::updateIncome()
{
    double dAllDueIncome = 0.0;
    double dAllRealIncome = 0.0;

    for(int i = 0; i < m_dailyChargesModel->rowCount();i++)
    {
        QStandardItem *dueIncomeItem = m_dailyChargesModel->item(i,2);
        QStandardItem *realIncomeItem = m_dailyChargesModel->item(i,3);
        double dDueIncome  = (dueIncomeItem == NULL) ? 0 : dueIncomeItem->text().toDouble();
        double dRealIncome = (realIncomeItem == NULL) ? 0 : realIncomeItem->text().toDouble();
        dAllDueIncome += dDueIncome;
        dAllRealIncome += dRealIncome;
    }

    m_allDueIncomeEdit->setText(QString::number(dAllDueIncome));
    m_allRealIncomeEdit->setText(QString::number(dAllRealIncome));
    m_allDebtEdit->setText(QString::number(dAllDueIncome - dAllRealIncome));
}

void ClinicDailyReportFrom::create()
{
    m_dailyReportNumLabel = new QLabel("日结单号：");
    m_dailyReportNumEdit = new QLineEdit;

    m_dateLabel = new QLabel("日结日期：");
    m_dateEdit = new QDateEdit;
    m_dateEdit->setCalendarPopup(true);
    m_dateEdit->setMaximumDate(QDate::currentDate());
    connect(m_dateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(updateCharges()));

    m_allDueIncomeLabel = new QLabel("应收合计：");
    m_allRealIncomeLabel = new QLabel("实收合计：");
    m_allDebtLabel = new QLabel("欠款合计：");

    m_allDueIncomeEdit = new QLineEdit;
    m_allRealIncomeEdit = new QLineEdit;
    m_allDebtEdit = new QLineEdit;

    m_dailyChargesView = new QTableView;
    m_dailyChargesModel = new QStandardItemModel;
    m_dailyChargesView->setModel(m_dailyChargesModel);
    connect(m_dailyChargesModel,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this, SLOT(updateIncome()));
}

void ClinicDailyReportFrom::init()
{
    m_dailyReportNumEdit->setText(g_strNull);
    initTable();
}

void ClinicDailyReportFrom::initTable()
{
    m_dailyChargesModel->clear();
    m_dailyChargesModel->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("收费单号")));
    m_dailyChargesModel->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("收费时间")));
    m_dailyChargesModel->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("应收金额")));
    m_dailyChargesModel->setHorizontalHeaderItem(3, new QStandardItem(QObject::tr("实收金额")));
    m_dailyChargesModel->setHorizontalHeaderItem(4, new QStandardItem(QObject::tr("欠款金额")));
    m_dailyChargesModel->setItem(0, 4, NULL);
    updateIncome();
}

void ClinicDailyReportFrom::setMyLayout()
{
    QGroupBox *topGroup = new QGroupBox("日结单信息");
    QGridLayout *topLeftLayout = new QGridLayout;
    topLeftLayout->addWidget(m_dailyReportNumLabel,0,0);
    topLeftLayout->addWidget(m_dailyReportNumEdit,0,1);
    topLeftLayout->addWidget(m_dateLabel,1,0);
    topLeftLayout->addWidget(m_dateEdit,1,1);
    topGroup->setLayout(topLeftLayout);

    QGroupBox *IncomeGroup = new QGroupBox("合计信息");
    QGridLayout *IncomeLayout = new QGridLayout;
    IncomeLayout->addWidget(m_allDueIncomeLabel,0,0);
    IncomeLayout->addWidget(m_allDueIncomeEdit,0,1);
    IncomeLayout->addWidget(m_allRealIncomeLabel,1,0);
    IncomeLayout->addWidget(m_allRealIncomeEdit,1,1);
    IncomeLayout->addWidget(m_allDebtLabel,2,0);
    IncomeLayout->addWidget(m_allDebtEdit,2,1);
    IncomeGroup->setLayout(IncomeLayout);


    QVBoxLayout *LeftLayout = new QVBoxLayout;
    LeftLayout->addWidget(topGroup);
    LeftLayout->addWidget(IncomeGroup);
    LeftLayout->addStretch();

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(m_dailyChargesView);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(LeftLayout);
    mainLayout->addLayout(rightLayout);
    mainLayout->setStretchFactor(rightLayout,1);
    setLayout(mainLayout);
}

void ClinicDailyReportFrom::setAllDefaultEnable()
{
    m_dailyReportNumEdit->setReadOnly(true);
    m_allDueIncomeEdit->setReadOnly(true);
    m_allRealIncomeEdit->setReadOnly(true);
    m_allDebtEdit->setReadOnly(true);
    m_dateEdit->setReadOnly(false);



    m_dailyChargesView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_dailyChargesView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void ClinicDailyReportFrom::setAllUnEnable()
{
    m_dailyReportNumEdit->setReadOnly(true);
    m_allDueIncomeEdit->setReadOnly(true);
    m_allRealIncomeEdit->setReadOnly(true);
    m_allDebtEdit->setReadOnly(true);
    m_dateEdit->setReadOnly(true);

    m_dailyChargesView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_dailyChargesView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

bool ClinicDailyReportFrom::Read()
{
    if(m_dailyReportTable->Read())
    {
        QString strId = m_dailyReportTable->getId();
        m_dailyReportNumEdit->setText(strId);
        m_dateEdit->setDate(m_dailyReportTable->getdate());
        updateCharges(m_dailyReportTable->getDateTime());
        m_allDueIncomeEdit->setText(QString::number(m_dailyReportTable->getAllDueIncome()));
        m_allRealIncomeEdit->setText(QString::number(m_dailyReportTable->getAllRealIncome()));
        m_allDebtEdit->setText(QString::number(m_dailyReportTable->getAllDebt()));
        return true;
    }
    else
    {
        QString strId = m_dailyReportTable->getId();
        m_dailyReportNumEdit->setText(strId);
        m_dateEdit->setDate(m_dailyReportTable->getdate());
        updateCharges();
        return false;
    }
}

bool ClinicDailyReportFrom::Save()
{
    m_dailyReportTable->setDate(m_dateEdit->date());
    m_dailyReportTable->setAllDueIncome(m_allDueIncomeEdit->text().toDouble());
    m_dailyReportTable->setAllRealIncome(m_allRealIncomeEdit->text().toDouble());
    m_dailyReportTable->setAllDebt(m_allDebtEdit->text().toDouble());
    return m_dailyReportTable->Save();
}

bool ClinicDailyReportFrom::Delete()
{

    if(m_dailyReportTable->Delete())
    {
        newTableFile();
        QMessageBox::information(this,"提示","删除成功！");
        return true;
    }
    else
    {
        QMessageBox::information(this,"提示","删除失败！");
        return false;
    }
}
