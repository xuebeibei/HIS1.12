#include "clinicpaymentstatisticform.h"
#include "clinicinternalpayment.h"

ClinicPaymentStatisticForm::ClinicPaymentStatisticForm(SubForm *parent) :
    SubForm(parent)
{
    create();
    setMyLayout();
    init();
}

ClinicPaymentStatisticForm::~ClinicPaymentStatisticForm()
{
    delete m_startDateLabel;
    delete m_startDateEdit;
    delete m_endDateLabel;
    delete m_endDateEdit;

    delete m_conditionSortBtnGroup;
    delete m_conditionWhoBtnGroup;

    delete m_conditionSortGroup;
    delete m_clinicReceiptRadio;
    delete m_clinicSortRadio;

    delete m_conditionWhoGroup;
    delete m_departmentRadio;
    delete m_doctorRadio;
    delete m_makerRadio;

    delete m_resultView;
    delete m_resultModel;
}

void ClinicPaymentStatisticForm::newTableFile()
{
}

bool ClinicPaymentStatisticForm::saveTableFile()
{
    return true;
}

bool ClinicPaymentStatisticForm::deleteTableFile()
{
    return true;
}

void ClinicPaymentStatisticForm::exportTableFile()
{
}

bool ClinicPaymentStatisticForm::findTableFile()
{
    return true;
}

void ClinicPaymentStatisticForm::amendTableFile()
{
}

void ClinicPaymentStatisticForm::previewTableFile()
{
}

void ClinicPaymentStatisticForm::printTableFile()
{
}

void ClinicPaymentStatisticForm::create()
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


    m_conditionSortBtnGroup = new QButtonGroup(this);
    m_conditionWhoBtnGroup = new QButtonGroup(this);

    m_conditionSortGroup = new QGroupBox;
    m_clinicReceiptRadio = new QRadioButton("门诊收据");
    connect(m_clinicReceiptRadio, SIGNAL(clicked(bool)), this, SLOT(setConditionSort()));
    m_clinicSortRadio = new QRadioButton("门诊分类");
    connect(m_clinicSortRadio, SIGNAL(clicked(bool)), this, SLOT(setConditionSort()));
    m_conditionSortBtnGroup->addButton(m_clinicReceiptRadio, 0);
    m_conditionSortBtnGroup->addButton(m_clinicSortRadio, 1);

    m_conditionWhoGroup = new QGroupBox;
    m_departmentRadio = new QRadioButton("科室");
    connect(m_departmentRadio, SIGNAL(clicked(bool)), this, SLOT(setConditionWho()));
    m_doctorRadio = new QRadioButton("医生");
    connect(m_doctorRadio, SIGNAL(clicked(bool)), this, SLOT(setConditionWho()));
    m_makerRadio = new QRadioButton("制单人");
    connect(m_makerRadio, SIGNAL(clicked(bool)), this, SLOT(setConditionWho()));
    m_conditionWhoBtnGroup->addButton(m_departmentRadio, 0);
    m_conditionWhoBtnGroup->addButton(m_doctorRadio, 1);
    m_conditionWhoBtnGroup->addButton(m_makerRadio, 2);

    m_resultView = new QTableView;
    m_resultModel = new QStandardItemModel;
    m_resultView->setModel(m_resultModel);
    m_resultView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_resultView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_strConditionSort = "ChinicReceipt";
    m_strConditionWho = "Department";
}

void ClinicPaymentStatisticForm::setMyLayout()
{
    QHBoxLayout *mainLayout = new QHBoxLayout;
    QVBoxLayout *leftLayout = new QVBoxLayout;
    QVBoxLayout *rightLayout = new QVBoxLayout;
    QGridLayout *dateLayout = new QGridLayout;
    QVBoxLayout *conditionSortLayout = new QVBoxLayout;
    QVBoxLayout *conditionWhoLayout = new QVBoxLayout;

    dateLayout->addWidget(m_startDateLabel,0,0);
    dateLayout->addWidget(m_startDateEdit,0,1);
    dateLayout->addWidget(m_endDateLabel,1,0);
    dateLayout->addWidget(m_endDateEdit,1,1);

    conditionSortLayout->addWidget(m_clinicReceiptRadio);
    conditionSortLayout->addWidget(m_clinicSortRadio);
    m_conditionSortGroup->setLayout(conditionSortLayout);

    conditionWhoLayout->addWidget(m_departmentRadio);
    conditionWhoLayout->addWidget(m_doctorRadio);
    conditionWhoLayout->addWidget(m_makerRadio);
    m_conditionWhoGroup->setLayout(conditionWhoLayout);

    leftLayout->addLayout(dateLayout);
    leftLayout->addWidget(m_conditionSortGroup);
    leftLayout->addWidget(m_conditionWhoGroup);
    leftLayout->addStretch();

    rightLayout->addWidget(m_resultView);

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    mainLayout->setStretchFactor(rightLayout, 1);
    setLayout(mainLayout);
}

void ClinicPaymentStatisticForm::init()
{
    m_startDateEdit->setDate(QDate::currentDate());
    m_endDateEdit->setDate(QDate::currentDate());
    m_clinicReceiptRadio->setChecked(true);
    setConditionSort();
    m_departmentRadio->setChecked(true);
    setConditionWho();
}

void ClinicPaymentStatisticForm::initTable()
{
    m_resultModel->clear();
    QString str = "";
    if(m_strConditionSort == "ChinicReceipt")
        str = "门诊收据";
    if(m_strConditionSort == "ClinicSort")
        str = "门诊分类";
    m_resultModel->setHorizontalHeaderItem(0, new QStandardItem(str));
    for(int i = 0; i < m_vecWho.size();i++)
    {
        m_resultModel->setHorizontalHeaderItem(i+1, new QStandardItem(m_vecWho.at(i)));
    }
    int last = m_vecWho.size() == 0 ? 1: m_vecWho.size()+1;
    m_resultModel->setHorizontalHeaderItem(last, new QStandardItem("应收合计"));
    for(int i = 0;i < m_vecSort.size();i++)
    {
        m_resultModel->setItem(i, 0, new QStandardItem(m_vecSort.at(i)));
    }
}

void ClinicPaymentStatisticForm::updateTable()
{
    // 获取条件
    initTable();
    // 从数据库按条件查询
    selectFromDB(m_startDateEdit->date(),m_endDateEdit->date(),m_strConditionSort,m_strConditionWho);

    for(int i = 0;i<m_dueIncome.size();i++)
    {
        double all = 0.0;
        QVector<double> temp = m_dueIncome.at(i);
        for(int j = 0;j<temp.size();j++)
        {
            all += temp.at(j);
            m_resultModel->setItem(i, j+1, new QStandardItem(QString::number(temp.at(j))));
        }
        m_resultModel->setItem(i, temp.size()+1, new QStandardItem(QString::number(all)));
    }
}

void ClinicPaymentStatisticForm::setConditionSort()
{
    switch(m_conditionSortBtnGroup->checkedId())
    {
    case 0:
    {
        m_strConditionSort = "ChinicReceipt";
        break;
    }
    case 1:
    {
        m_strConditionSort = "ClinicSort";
        break;
    }
    }

    m_vecSort = ClinicInternalPayment::getDistinctFromDB(m_strConditionSort , g_strClinicChargeDetails);

    updateTable();
}

void ClinicPaymentStatisticForm::setConditionWho()
{
    switch(m_conditionWhoBtnGroup->checkedId())
    {
    case 0:
    {
        m_strConditionWho = "Department";
        break;
    }
    case 1:
    {
        m_strConditionWho = "Doctor";
        break;
    }
    case 2:
    {
        m_strConditionWho = "Maker";
        break;
    }
    }

    m_vecWho = ClinicInternalPayment::getDistinctFromDB(m_strConditionWho , g_strClinicCharge);

    updateTable();
}


void ClinicPaymentStatisticForm::selectFromDB(QDate startDate, QDate endDate, QString strConditionSort,QString strConditionWho)
{
    if(endDate < startDate)
        return;
    if(m_vecSort.size()<=0||m_vecWho.size()<=0)
        return;
    m_dueIncome.resize(0);
    if(myDB::connectDB())
    {
        QString startTime = startDate.toString("yyyy-MM-dd") + "T00:00:00";
        QString endTime = endDate.toString("yyyy-MM-dd") + "T23:59:59";
        QSqlQueryModel *sqlModel = new QSqlTableModel;
        for(int i = 0;i< m_vecSort.size();i++)
        {
            QString strSort = m_vecSort.at(i);
            m_resultModel->setItem(i, 0, new QStandardItem(strSort));
            QVector<double> temp;
            for(int j = 0;j< m_vecWho.size();j++)
            {

                QString strWho = m_vecWho.at(j);

                QString strSql = "select * from clinicchargedetails where "
                        + strConditionSort+ " = \'" + strSort + "\' and chargei"
                        "d in (select id from cliniccharge where time between \'"
                        + startTime+"\' and \'"+endTime+
                        "\' and " + strConditionWho +
                        " = \'" + strWho +"\')";
                sqlModel->setQuery(strSql);

                double all = 0;
                for(int n = 0;n<sqlModel->rowCount();n++)
                {
                    int nCount = sqlModel->record(n).value("ChargeItemCount").toInt();
                    double nPrice = sqlModel->record(n).value("ChargeItemPrice").toDouble();
                    all += nCount*nPrice;
                }
                temp.append(all);
            }
            m_dueIncome.append(temp);
        }
    }
}
