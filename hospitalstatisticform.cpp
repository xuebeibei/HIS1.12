#include "hospitalstatisticform.h"

HospitalStatisticForm::HospitalStatisticForm(SubForm *parent) :
    SubForm(parent)
{
    create();
    setMyLayout();
    init();
}

HospitalStatisticForm::~HospitalStatisticForm()
{
    delete m_conditionGroup;
    delete m_inHospitalStatistic;
    delete m_payInStatistic;
    delete m_chargeStatistic;
    delete m_dailyReportStatistic;
    delete m_balanceStatistic;
    delete m_paymentStatistic;

    delete m_startDateLabel;
    delete m_endDateLabel;
    delete m_inpatientIDLabel;
    delete m_nameLabel;
    delete m_genderLabel;
    delete m_inpatientStatusLabel;
    delete m_statisticMethodLabel;

    delete m_startDateEdit;
    delete m_endDateEdit;
    delete m_inpatientIDEdit;
    delete m_nameEdit;
    delete m_genderCombo;
    delete m_inpatientStatusCombo;
    delete m_statisticMethodCombo;
    delete m_conditionSortGroup;
    delete m_conditionWhoGroup;
    delete m_ReceiptRadio;
    delete m_SortRadio;
    delete m_departmentRadio;
    delete m_doctorRadio;
    delete m_makerRadio;

    delete m_view;
    delete m_model;

    delete m_findInpatientBtn;
    delete m_selectBtn;
}

void HospitalStatisticForm::newTableFile()
{

}

bool HospitalStatisticForm::saveTableFile()
{
    return true;
}

bool HospitalStatisticForm::deleteTableFile()
{
    return true;
}

void HospitalStatisticForm::exportTableFile()
{
}

bool HospitalStatisticForm::findTableFile()
{
    return true;
}

void HospitalStatisticForm::amendTableFile()
{
}

void HospitalStatisticForm::previewTableFile()
{
}

void HospitalStatisticForm::printTableFile()
{
}


void HospitalStatisticForm::setCondition()
{
    m_eType = (HospitalStatisticType)m_conditionGroup->checkedId();
    showResults();
}

void HospitalStatisticForm::findInpatient()
{
    FindRegistryDlg *dailog = new FindRegistryDlg;
    dailog->exec();
    QString strID = dailog->getID();

    if(!strID.isEmpty())
    {
        Inpatient *temp = new Inpatient;
        temp->setID(strID);
        temp->Read();
        m_nameEdit->setText(temp->getName());
        m_inpatientIDEdit->setText(temp->getID());
        m_genderCombo->setCurrentIndex(temp->getGender());
    }
}

void HospitalStatisticForm::showResults()
{
    setAllDefaultEnable();
    switch (m_eType)
    {
    case inHospitalStatistic:
    {
        onInHospitalStatistic();
        break;
    }
    case payInStatistic:
    {
        onPayInStatistic();
        break;
    }
    case chargeStatistic:
    {
        onChargeStatistic();

        break;
    }
    case dailyReportStatistic:
    {
        onDailyReportStatistic();
        break;
    }
    case balanceStatistic:
    {
        onBalanceStatistic();
        break;
    }
    case paymentStatistic:
    {
        onPaymentStatistic();
        break;
    }
    default:
        break;
    }
}

void HospitalStatisticForm::setAllDefaultEnable()
{
    m_startDateLabel->setEnabled(true);
    m_startDateEdit->setEnabled(true);
    m_endDateLabel->setEnabled(true);
    m_endDateEdit->setEnabled(true);
    m_inpatientIDLabel->setEnabled(true);
    m_inpatientIDEdit->setEnabled(true);
    m_findInpatientBtn->setEnabled(true);
    m_nameLabel->setEnabled(true);
    m_nameEdit->setEnabled(true);
    m_genderLabel->setEnabled(true);
    m_genderCombo->setEnabled(true);
    m_inpatientStatusLabel->setEnabled(true);
    m_inpatientStatusCombo->setEnabled(true);
    m_statisticMethodLabel->setEnabled(true);
    m_statisticMethodCombo->setEnabled(true);

    m_ReceiptRadio->setEnabled(true);
    m_SortRadio->setEnabled(true);

    m_departmentRadio->setEnabled(true);
    m_doctorRadio->setEnabled(true);
    m_makerRadio->setEnabled(true);
}

void HospitalStatisticForm::onInHospitalStatistic()
{
    m_startDateLabel->setEnabled(false);
    m_endDateLabel->setEnabled(false);
    m_startDateEdit->setEnabled(false);
    m_endDateEdit->setEnabled(false);

    m_statisticMethodLabel->setEnabled(false);
    m_statisticMethodCombo->setEnabled(false);

    m_ReceiptRadio->setEnabled(false);
    m_SortRadio->setEnabled(false);

    m_departmentRadio->setEnabled(false);
    m_doctorRadio->setEnabled(false);
    m_makerRadio->setEnabled(false);

    initInHospitalStatisticTable();
    selectHospitalStatisticFromDB();
}

void HospitalStatisticForm::onPayInStatistic()
{
    m_startDateLabel->setEnabled(false);
    m_endDateLabel->setEnabled(false);
    m_startDateEdit->setEnabled(false);
    m_endDateEdit->setEnabled(false);

    m_statisticMethodLabel->setEnabled(false);
    m_statisticMethodCombo->setEnabled(false);

    m_ReceiptRadio->setEnabled(false);
    m_SortRadio->setEnabled(false);

    m_departmentRadio->setEnabled(false);
    m_doctorRadio->setEnabled(false);
    m_makerRadio->setEnabled(false);

    initPayInStatistisTable();
    selectPayInStatistisFromDB();
}

void HospitalStatisticForm::onChargeStatistic()
{
    m_ReceiptRadio->setEnabled(false);
    m_SortRadio->setEnabled(false);

    m_departmentRadio->setEnabled(false);
    m_doctorRadio->setEnabled(false);
    m_makerRadio->setEnabled(false);

    initChargeStatisticTable();
    selectChargeStatisticFromDB();
}

void HospitalStatisticForm::onDailyReportStatistic()
{
    m_inpatientIDLabel->setEnabled(false);
    m_inpatientIDEdit->setEnabled(false);
    m_findInpatientBtn->setEnabled(false);
    m_nameLabel->setEnabled(false);
    m_nameEdit->setEnabled(false);
    m_genderLabel->setEnabled(false);
    m_genderCombo->setEnabled(false);
    m_inpatientStatusLabel->setEnabled(false);
    m_inpatientStatusCombo->setEnabled(false);

    m_statisticMethodLabel->setEnabled(false);
    m_statisticMethodCombo->setEnabled(false);
    m_ReceiptRadio->setEnabled(false);
    m_SortRadio->setEnabled(false);

    m_departmentRadio->setEnabled(false);
    m_doctorRadio->setEnabled(false);
    m_makerRadio->setEnabled(false);

    initDailyReportStatisticTable();
}

void HospitalStatisticForm::onBalanceStatistic()
{
    m_inpatientStatusLabel->setEnabled(false);
    m_inpatientStatusCombo->setEnabled(false);
    m_statisticMethodLabel->setEnabled(false);
    m_statisticMethodCombo->setEnabled(false);
    m_ReceiptRadio->setEnabled(false);
    m_SortRadio->setEnabled(false);

    m_departmentRadio->setEnabled(false);
    m_doctorRadio->setEnabled(false);
    m_makerRadio->setEnabled(false);

    initBalanceStatisticTable();
}

void HospitalStatisticForm::onPaymentStatistic()
{
    m_inpatientIDLabel->setEnabled(false);
    m_inpatientIDEdit->setEnabled(false);
    m_findInpatientBtn->setEnabled(false);
    m_nameLabel->setEnabled(false);
    m_nameEdit->setEnabled(false);
    m_genderLabel->setEnabled(false);
    m_genderCombo->setEnabled(false);
    m_inpatientStatusLabel->setEnabled(false);
    m_inpatientStatusCombo->setEnabled(false);

    initPaymentStatistic();
}

void HospitalStatisticForm::initTable(QStringList strList)
{
    m_model->clear();
    for(int i = 0; i < strList.size(); i++)
    {
         m_model->setHorizontalHeaderItem(i,new QStandardItem(strList.at(i)));
    }
    if(strList.size() > 0)
        m_model->setItem(0, strList.size()-1, NULL);
}

void HospitalStatisticForm::initInHospitalStatisticTable()
{
    QStringList strList;
    strList.append("住院号");
    strList.append("姓名");
    strList.append("性别");
    strList.append("年龄");
    strList.append("科室");
    strList.append("医生");
    strList.append("护理级别");
    strList.append("床位");
    strList.append("诊断结果");
    strList.append("入院日期");
    strList.append("身份证号");
    strList.append("医保类型");
    strList.append("社保账号");
    strList.append("联系人");
    strList.append("电话");
    strList.append("地址");

    initTable(strList);
}

void HospitalStatisticForm::initPayInStatistisTable()
{
    QStringList strList;
    strList.append("缴款单号");
    strList.append("缴款时间");
    strList.append("住院号");
    strList.append("姓名");
    strList.append("金额");
    initTable(strList);
}

void HospitalStatisticForm::initChargeStatisticTable()
{
    QStringList strList;
    strList.append("收费单号");
    strList.append("收费时间");
    strList.append("住院号");
    strList.append("姓名");
    strList.append("收费项名称");
    strList.append("数量");
    strList.append("单价");
    strList.append("住院收据");
    initTable(strList);
}

void HospitalStatisticForm::initDailyReportStatisticTable()
{
    QStringList strList;
    strList.append("日结单号");
    strList.append("日结时间");
    strList.append("应收金额");
    strList.append("制单人");
    initTable(strList);
}

void HospitalStatisticForm::initBalanceStatisticTable()
{
    QStringList strList;
    strList.append("住院号");
    strList.append("姓名");
    strList.append("缴款合计");
    strList.append("消费合计");
    strList.append("余额");
    initTable(strList);
}

void HospitalStatisticForm::initPaymentStatistic()
{
    QStringList strList;
    strList.append("");
    strList.append("合计");
    initTable(strList);
}

void HospitalStatisticForm::updateInHospitalStatisticTable(QVector<Inpatient*> *vec)
{
    initInHospitalStatisticTable();

    for(int i = 0; i < vec->size(); i++)
    {
        m_model->setItem(i,0,new QStandardItem(vec->at(i)->getID()));
        m_model->setItem(i,1,new QStandardItem(vec->at(i)->getName()));
        m_model->setItem(i,2,new QStandardItem(QString::number(vec->at(i)->getGender())));
        m_model->setItem(i,3,new QStandardItem(QString::number(vec->at(i)->getAge())));
        m_model->setItem(i,4,new QStandardItem(vec->at(i)->getDepartment()));
        m_model->setItem(i,5,new QStandardItem(vec->at(i)->getDoctor()));
        m_model->setItem(i,6,new QStandardItem(QString::number(vec->at(i)->getNursingLevel())));
        m_model->setItem(i,7,new QStandardItem(QString::number(vec->at(i)->getBedNum())));
        m_model->setItem(i,8,new QStandardItem(vec->at(i)->getIDCard()));
        m_model->setItem(i,9,new QStandardItem(vec->at(i)->getContacts().getName()));
        m_model->setItem(i,10,new QStandardItem(vec->at(i)->getContacts().getTel()));
        m_model->setItem(i,11,new QStandardItem(vec->at(i)->getContacts().getAddress()));
    }
}

void HospitalStatisticForm::updatePayInStatistisTable(QVector<Account*> *vec)
{
    initPayInStatistisTable();

    int index = 0;
    for(int i = 0; i < vec->size(); i++)
    {
        QString strID = vec->at(i)->getID();
        if(QString::compare(strID.left(g_strHospitalChargeNumPR.length()),g_strHospitalChargeNumPR) == 0)
            continue;
        m_model->setItem(index,0,new QStandardItem(vec->at(i)->getID()));
        m_model->setItem(index,1,new QStandardItem(vec->at(i)->getDateTime().toString("yyyy-MM-dd hh:mm:ss")));
        m_model->setItem(index,2,new QStandardItem(vec->at(i)->getInpatientID()));
        m_model->setItem(index,3,new QStandardItem(Inpatient::getNameByID(vec->at(i)->getInpatientID())));
        m_model->setItem(index,4,new QStandardItem(QString::number(vec->at(i)->getBalance())));
        index++;
    }
}

void HospitalStatisticForm::updateChargeStatisticTable(QVector<HospitalChargeTable *> *vec)
{
    initChargeStatisticTable();

    int index = 0;
    for(int i = 0; i < vec->size();i++)
    {
        QString strID = vec->at(i)->getID();
        if(!QString::compare(strID.left(g_strHospitalChargeNumPR.length()),g_strHospitalChargeNumPR) == 0)
        {
            continue;
        }
        for(int j = 0; j < vec->at(i)->getChargeItems().size(); j++)
        {
            m_model->setItem(index,0,new QStandardItem(strID));
            m_model->setItem(index,1,new QStandardItem(vec->at(i)->getTime().toString("yyyy-MM-dd hh:mm:ss")));
            m_model->setItem(index,2, new QStandardItem(vec->at(i)->getInpatientID()));
            m_model->setItem(index,3, new QStandardItem(Inpatient::getNameByID(vec->at(i)->getInpatientID())));

            m_model->setItem(index,4,new QStandardItem(vec->at(i)->getChargeItems().at(j)->getChargeItemName()));
            m_model->setItem(index,5,new QStandardItem(QString::number(vec->at(i)->getChargeItems().at(j)->getChargeItemCount())));
            m_model->setItem(index,6,new QStandardItem(QString::number(vec->at(i)->getChargeItems().at(j)->getChargeItemPrice())));
            m_model->setItem(index,7,new QStandardItem(vec->at(i)->getChargeItems().at(j)->getReceipt()));

            index++;
        }
    }
}

void HospitalStatisticForm::updateDailyReportStatisticTable()
{
}

void HospitalStatisticForm::updateBalanceStatisticTable()
{
}

void HospitalStatisticForm::updatePaymentStatistic()
{
}

void HospitalStatisticForm::selectHospitalStatisticFromDB()
{
    QVector<Inpatient *> vec =  Inpatient::selectFromDB(
                m_inpatientIDEdit->text(),
                m_nameEdit->text(),
                (Gender)m_genderCombo->currentIndex());
    updateInHospitalStatisticTable(&vec);
}

void HospitalStatisticForm::selectPayInStatistisFromDB()
{
    QVector<Account*> vec;
    vec = Account::getRecords(m_inpatientIDEdit->text());
    updatePayInStatistisTable(&vec);
}

void HospitalStatisticForm::selectChargeStatisticFromDB()
{
    QVector<HospitalChargeTable *> *vec = new QVector<HospitalChargeTable *>;
    vec = HospitalChargeTable::selectFromDB(m_startDateEdit->date(), m_endDateEdit->date(), m_inpatientIDEdit->text());
    if(vec == NULL)
        return;
    updateChargeStatisticTable(vec);
}

void HospitalStatisticForm::create()
{
    createStatisticType();
    createConditions();
    createTable();
}

void HospitalStatisticForm::setMyLayout()
{
    QGroupBox *leftTopGroup = new QGroupBox;
    QGridLayout *leftTopLayout = new QGridLayout;
    leftTopLayout->addWidget(m_inHospitalStatistic,0,0);
    leftTopLayout->addWidget(m_payInStatistic,0,1);
    leftTopLayout->addWidget(m_chargeStatistic,1,0);
    leftTopLayout->addWidget(m_dailyReportStatistic,1,1);
    leftTopLayout->addWidget(m_balanceStatistic,2,0);
    leftTopLayout->addWidget(m_paymentStatistic,2,1);
    leftTopGroup->setLayout(leftTopLayout);

    QGridLayout *leftBottomLayout = new QGridLayout;
    leftBottomLayout->addWidget(m_startDateLabel,0,0);
    leftBottomLayout->addWidget(m_startDateEdit,0,1,1,2);
    leftBottomLayout->addWidget(m_endDateLabel,1,0);
    leftBottomLayout->addWidget(m_endDateEdit,1,1,1,2);
    leftBottomLayout->addWidget(m_inpatientIDLabel,2,0);
    leftBottomLayout->addWidget(m_inpatientIDEdit,2,1);
    leftBottomLayout->addWidget(m_findInpatientBtn,2,2);
    leftBottomLayout->addWidget(m_nameLabel,3,0);
    leftBottomLayout->addWidget(m_nameEdit,3,1,1,2);
    leftBottomLayout->addWidget(m_genderLabel,4,0);
    leftBottomLayout->addWidget(m_genderCombo,4,1,1,2);
    leftBottomLayout->addWidget(m_inpatientStatusLabel,5,0);
    leftBottomLayout->addWidget(m_inpatientStatusCombo,5,1,1,2);
    leftBottomLayout->addWidget(m_statisticMethodLabel,6,0);
    leftBottomLayout->addWidget(m_statisticMethodCombo,6,1,1,2);

    QGroupBox *conditionSortGroup = new QGroupBox;
    QVBoxLayout *conditionSortLayout = new QVBoxLayout;
    conditionSortLayout->addWidget(m_ReceiptRadio);
    conditionSortLayout->addWidget(m_SortRadio);
    conditionSortGroup->setLayout(conditionSortLayout);

    QGroupBox *conditionWhoGroup = new QGroupBox;
    QVBoxLayout *conditionWhoLayout = new QVBoxLayout;
    conditionWhoLayout->addWidget(m_departmentRadio);
    conditionWhoLayout->addWidget(m_doctorRadio);
    conditionWhoLayout->addWidget(m_makerRadio);
    conditionWhoGroup->setLayout(conditionWhoLayout);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(leftTopGroup);
    leftLayout->addLayout(leftBottomLayout);
    leftLayout->addWidget(conditionSortGroup);
    leftLayout->addWidget(conditionWhoGroup);
    leftLayout->addWidget(m_selectBtn);
    leftLayout->addStretch();

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(m_view);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    mainLayout->setStretchFactor(rightLayout, 1);

    setLayout(mainLayout);
}

void HospitalStatisticForm::init()
{
    m_inHospitalStatistic->setChecked(true);
    m_eType = inHospitalStatistic;
    onInHospitalStatistic();
    m_startDateEdit->setDate(QDate::currentDate());
    m_endDateEdit->setDate(QDate::currentDate());
    m_genderCombo->setCurrentIndex(allGender);
}

void HospitalStatisticForm::createStatisticType()
{
    m_conditionGroup = new QButtonGroup;

    m_inHospitalStatistic = new QRadioButton;
    m_payInStatistic = new QRadioButton;
    m_chargeStatistic = new QRadioButton;
    m_dailyReportStatistic = new QRadioButton;
    m_balanceStatistic = new QRadioButton;
    m_paymentStatistic = new QRadioButton;

    m_inHospitalStatistic->setText(g_strInHospitalStatistic);
    m_payInStatistic->setText(g_strPayInStatistic);
    m_chargeStatistic->setText(g_strChargeStatistic);
    m_dailyReportStatistic->setText(g_strDailyReportStatistic);
    m_balanceStatistic->setText(g_strBalanceStatistic);
    m_paymentStatistic->setText(g_strPaymentStatistic);

    connect(m_inHospitalStatistic, SIGNAL(clicked(bool)), this, SLOT(setCondition()));
    connect(m_payInStatistic, SIGNAL(clicked(bool)), this, SLOT(setCondition()));
    connect(m_chargeStatistic, SIGNAL(clicked(bool)), this, SLOT(setCondition()));
    connect(m_dailyReportStatistic, SIGNAL(clicked(bool)), this, SLOT(setCondition()));
    connect(m_balanceStatistic, SIGNAL(clicked(bool)), this, SLOT(setCondition()));
    connect(m_paymentStatistic, SIGNAL(clicked(bool)), this, SLOT(setCondition()));

    m_conditionGroup->addButton(m_inHospitalStatistic, inHospitalStatistic);
    m_conditionGroup->addButton(m_payInStatistic, payInStatistic);
    m_conditionGroup->addButton(m_chargeStatistic, chargeStatistic);
    m_conditionGroup->addButton(m_dailyReportStatistic, dailyReportStatistic);
    m_conditionGroup->addButton(m_balanceStatistic, balanceStatistic);
    m_conditionGroup->addButton(m_paymentStatistic, paymentStatistic);
}

void HospitalStatisticForm::createConditions()
{
    m_startDateLabel = new QLabel(g_strStartDateLabel);
    m_endDateLabel = new QLabel(g_strEndDateLabel);
    m_inpatientIDLabel = new QLabel("住院号：");
    m_nameLabel = new QLabel("姓名：");
    m_genderLabel = new QLabel("性别：");
    m_inpatientStatusLabel = new QLabel("住院状态：");
    m_statisticMethodLabel = new QLabel("统计方式：");

    m_startDateEdit = new QDateEdit;
    m_startDateEdit->setCalendarPopup(true);
    m_startDateEdit->setMaximumDate(QDate::currentDate());

    m_endDateEdit = new QDateEdit;
    m_endDateEdit->setCalendarPopup(true);
    m_endDateEdit->setMaximumDate(QDate::currentDate());

    m_inpatientIDEdit = new QLineEdit;
    m_nameEdit = new QLineEdit;

    m_genderCombo = new QComboBox;
    m_genderCombo->addItem(g_strMan);
    m_genderCombo->addItem(g_strWoman);
    m_genderCombo->addItem(g_strAllGender);

    m_inpatientStatusCombo = new QComboBox;
    m_inpatientStatusCombo->addItem("住院中");
    m_inpatientStatusCombo->addItem("已出院");
    m_inpatientStatusCombo->addItem("全部");

    m_statisticMethodCombo = new QComboBox;
    m_statisticMethodCombo->addItem("详细清单");
    m_statisticMethodCombo->addItem("费用汇总");

    m_conditionSortGroup = new QButtonGroup;
    m_conditionWhoGroup = new QButtonGroup;

    m_ReceiptRadio = new QRadioButton("住院收据");
    m_SortRadio = new QRadioButton("住院分类");

    m_departmentRadio = new QRadioButton("科室");
    m_doctorRadio = new QRadioButton("医生");
    m_makerRadio = new QRadioButton("制单人");

    m_findInpatientBtn = new QToolButton;
    m_findInpatientBtn->setIcon(QIcon(g_strIconPath + "find.png"));
    connect(m_findInpatientBtn, SIGNAL(clicked(bool)), this, SLOT(findInpatient()));

    m_selectBtn = new QPushButton("统计查询");
    m_selectBtn->setStyleSheet("QPushButton { color: blue }");
    connect(m_selectBtn, SIGNAL(clicked()), this, SLOT(showResults()));
}

void HospitalStatisticForm::createTable()
{
    m_view = new QTableView;
    m_model = new QStandardItemModel;
    m_view->setModel(m_model);
}
