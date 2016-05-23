#ifndef HOSPITALSTATISTICFORM_H
#define HOSPITALSTATISTICFORM_H

#include <QWidget>
#include "subform.h"
#include "findregistrydlg.h"
#include "inpatient.h"
#include "hospitalchargetable.h"

const QString g_strInHospitalStatistic = QObject::tr("住院统计");
const QString g_strPayInStatistic = QObject::tr("缴/退费统计");
const QString g_strChargeStatistic = QObject::tr("收费统计");
const QString g_strDailyReportStatistic = QObject::tr("日结统计");
const QString g_strBalanceStatistic = QObject::tr("余额统计");
const QString g_strPaymentStatistic = QObject::tr("项目统计");

enum HospitalStatisticType
{
    inHospitalStatistic = 0,
    payInStatistic = 1,
    chargeStatistic = 2,
    dailyReportStatistic = 3,
    balanceStatistic = 4,
    paymentStatistic = 5
};


class HospitalStatisticForm : public SubForm
{
    Q_OBJECT
    
public:
    explicit HospitalStatisticForm(SubForm *parent = 0);
    ~HospitalStatisticForm();
    void newTableFile();
    bool saveTableFile();
    bool deleteTableFile();
    void exportTableFile();
    bool findTableFile();
    void amendTableFile();
    void previewTableFile();
    void printTableFile();

protected:

    void create();
    void setMyLayout();
    void init();
    void createStatisticType();
    void createConditions();
    void createTable();

    void setAllDefaultEnable();

    void onInHospitalStatistic();
    void onPayInStatistic();
    void onChargeStatistic();
    void onDailyReportStatistic();
    void onBalanceStatistic();
    void onPaymentStatistic();
    void initTable(QStringList strList);

    void initInHospitalStatisticTable();
    void initPayInStatistisTable();
    void initChargeStatisticTable();
    void initDailyReportStatisticTable();
    void initBalanceStatisticTable();
    void initPaymentStatistic();

    void updateInHospitalStatisticTable(QVector<Inpatient*> *vec);
    void updatePayInStatistisTable(QVector<Account*> *vec);
    void updateChargeStatisticTable(QVector<HospitalChargeTable *> *vec);
    void updateDailyReportStatisticTable();
    void updateBalanceStatisticTable();
    void updatePaymentStatistic();

    void selectHospitalStatisticFromDB();
    void selectPayInStatistisFromDB();
    void selectChargeStatisticFromDB();
protected slots:
    void setCondition();
    void findInpatient();
    void showResults();

protected:

    // 界面
    QButtonGroup *m_conditionGroup;         // 统计查询种类
    QRadioButton *m_inHospitalStatistic;    // 住院查询
    QRadioButton *m_payInStatistic;         // 缴费/退费查询
    QRadioButton *m_chargeStatistic;        // 收费查询
    QRadioButton *m_dailyReportStatistic;   // 日结查询
    QRadioButton *m_balanceStatistic;       // 余额查询
    QRadioButton *m_paymentStatistic;       // 项目查询


    QLabel *m_startDateLabel;               // 起始日期
    QLabel *m_endDateLabel;                 // 结束日期
    QLabel *m_inpatientIDLabel;             // 住院号
    QLabel *m_nameLabel;                    // 姓名
    QLabel *m_genderLabel;                  // 性别
    QLabel *m_inpatientStatusLabel;         // 住院状态
    QLabel *m_statisticMethodLabel;         // 统计方式

    QDateEdit *m_startDateEdit;             // 起始日期
    QDateEdit *m_endDateEdit;               // 结束日期

    QLineEdit *m_inpatientIDEdit;           // 住院号
    QLineEdit *m_nameEdit;                  // 姓名
    QComboBox *m_genderCombo;               // 性别
    QComboBox *m_inpatientStatusCombo;      // 住院状态
    QComboBox *m_statisticMethodCombo;      // 统计方式

    QButtonGroup *m_conditionSortGroup;     // 项目查询筛选条件1
    QButtonGroup *m_conditionWhoGroup;      // 项目查询筛选条件2

    QRadioButton *m_ReceiptRadio;           // 住院收据
    QRadioButton *m_SortRadio;              // 住院分类

    QRadioButton *m_departmentRadio;        // 科室
    QRadioButton *m_doctorRadio;            // 医生
    QRadioButton *m_makerRadio;             // 制单人

    QTableView *m_view;                     // 查询结果
    QStandardItemModel *m_model;            // 查询结果

    QToolButton *m_findInpatientBtn;        // 查找住院号
    QPushButton *m_selectBtn;               // 查找统计结果

    // 数据
    HospitalStatisticType m_eType;          // 统计查询种类
};

#endif // HOSPITALSTATISTICFORM_H
