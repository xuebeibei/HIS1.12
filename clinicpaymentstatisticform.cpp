#include "clinicpaymentstatisticform.h"
#include "internalpayment.h"

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

    delete m_clinicReceiptRadio;
    delete m_clinicSortRadio;

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

    m_clinicReceiptRadio = new QRadioButton("门诊收据");
    connect(m_clinicReceiptRadio, SIGNAL(clicked(bool)), this, SLOT(setConditionSort()));
    m_clinicSortRadio = new QRadioButton("门诊分类");
    connect(m_clinicSortRadio, SIGNAL(clicked(bool)), this, SLOT(setConditionSort()));
    m_conditionSortBtnGroup->addButton(m_clinicReceiptRadio, 0);
    m_conditionSortBtnGroup->addButton(m_clinicSortRadio, 1);

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

    m_strConditionSort = "ClinicReceipt";
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

    QGroupBox *conditionSortGroup = new QGroupBox;
    conditionSortLayout->addWidget(m_clinicReceiptRadio);
    conditionSortLayout->addWidget(m_clinicSortRadio);
    conditionSortGroup->setLayout(conditionSortLayout);

    QGroupBox *m_conditionWhoGroup = new QGroupBox;
    conditionWhoLayout->addWidget(m_departmentRadio);
    conditionWhoLayout->addWidget(m_doctorRadio);
    conditionWhoLayout->addWidget(m_makerRadio);
    m_conditionWhoGroup->setLayout(conditionWhoLayout);

    leftLayout->addLayout(dateLayout);
    leftLayout->addWidget(conditionSortGroup);
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
    if(m_strConditionSort == "ClinicReceipt")
        str = "门诊收据";
    if(m_strConditionSort == "ClinicSort")
        str = "门诊分类";
    m_resultModel->setHorizontalHeaderItem(0, new QStandardItem(str));
}

void ClinicPaymentStatisticForm::updateTable()
{
    QVector<QVector<QString> > *dueIncome = new QVector<QVector<QString> >;
    // 获取条件
    initTable();
    // 从数据库按条件查询
    dueIncome = InternalPayment::selectFromDB(
                m_startDateEdit->date(),
                m_endDateEdit->date(),
                m_strConditionSort,
                g_strChargeDetails,
                m_strConditionWho,
                g_strClinicCharge);


    if(dueIncome == NULL)
        return;
    for(int i = 0;i<dueIncome->size();i++)
    {
        double all = 0.0;
        QVector<QString> temp = dueIncome->at(i);
        for(int j = 0;j<temp.size();j++)
        {
            if(i == 0)
            {
                m_resultModel->setHorizontalHeaderItem(j+1, new QStandardItem(temp.at(j)));
            }
            else if( i > 0)
            {
                m_resultModel->setItem(i-1, j, new QStandardItem(temp.at(j)));
                if(j!=0)
                     all += temp.at(j).toDouble();
            }

        }
        if(i == 0)
        {
            m_resultModel->setHorizontalHeaderItem(temp.size()+1, new QStandardItem("合计"));
        }
        else if(i > 0)
        {
            m_resultModel->setItem(i-1, temp.size(), new QStandardItem(QString::number(all)));
        }

    }
}

void ClinicPaymentStatisticForm::setConditionSort()
{
    switch(m_conditionSortBtnGroup->checkedId())
    {
    case 0:
    {
        m_strConditionSort = "ClinicReceipt";
        break;
    }
    case 1:
    {
        m_strConditionSort = "ClinicSort";
        break;
    }
    }

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

    updateTable();
}
