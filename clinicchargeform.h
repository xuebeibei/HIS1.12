#ifndef CLINICCHARGE_H
#define CLINICCHARGE_H

#include <QWidget>
#include "stdafx.h"
#include "subform.h"
#include "clinicchargetable.h"

//-----------------------------------------------------------------------------------------------------------------------------------
// 门诊收费界面类
//-----------------------------------------------------------------------------------------------------------------------------------
class ClinicChargeForm : public SubForm
{
    Q_OBJECT
    
public:
    explicit ClinicChargeForm(SubForm *parent = 0);
    ~ClinicChargeForm();

public slots:

    void newTableFile();
    bool saveTableFile();
    bool deleteTableFile();
    void exportTableFile();
    bool findTableFile();
    void amendTableFile();
    void previewTableFile();
    void printTableFile();
private slots:

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：addRow
    // 作用：在收费明细表中在最底端添加一行
    // 参数：无
    // 返回值：无
    // 备注：无
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    void addRow();

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：deleteRow
    // 作用：在收费明细中删除选中的行
    // 参数：无
    // 返回值：无
    // 备注：无
    // 时间：2016-05-03
    //-----------------------------------------------------------------------------------------------------------------------------------
    void deleteRow();

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：combo
    // 作用：在收费明细表中添加套餐数据
    // 参数：无
    // 返回值：无
    // 备注：还未实现
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    void combo();

    void updateIncome();

protected:

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：init
    // 作用：初始化门诊收费所有界面控件的值
    // 参数：无
    // 返回值：无
    // 备注：无
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    void init();

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：initTableModel
    // 作用：初始化门诊收费界面table的值
    // 参数：无
    // 返回值：无
    // 备注：无
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    void initTableModel();

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：setAllDefaultEnable
    // 作用：将门诊收费界面的所有控件的可用属性设置为默认属性
    // 参数：无
    // 返回值：无
    // 备注：tableModel的可用性更改还没有写
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    void setAllDefaultEnable();

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：setAllUnEnable
    // 作用：将门诊收费界面的所有控件的可用属性设置为不可用
    // 参数：无
    // 返回值：无
    // 备注：tableModel的可用性更改还没有写
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    void setAllUnEnable();

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：create
    // 作用：创建门诊收费窗体中所有控件
    // 参数：无
    // 返回值：无
    // 备注：无
    // 时间：2016-04-15
    //-----------------------------------------------------------------------------------------------------------------------------------
    void create();

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：CreatePatientPart
    // 作用：创建患者信息部分控件并编组
    // 参数：无
    // 返回值：无
    // 备注：无
    // 时间：2016-04-15
    //-----------------------------------------------------------------------------------------------------------------------------------
    void CreatePatientPart();

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：CreateSocialSecurityPart
    // 作用：创建社保信息部分控件并编组
    // 参数：无
    // 返回值：无
    // 备注：无
    // 时间：2016-04-15
    //-----------------------------------------------------------------------------------------------------------------------------------
    void CreateSocialSecurityPart();

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：CreateDoctorPart
    // 作用：创建医生信息部分控件并编组
    // 参数：无
    // 返回值：无
    // 备注：无
    // 时间：2016-04-15
    //-----------------------------------------------------------------------------------------------------------------------------------
    void CreateDoctorPart();

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：CreateIncomePart
    // 作用：创建收入信息部分控件并编组
    // 参数：无
    // 返回值：无
    // 备注：无
    // 时间：2016-04-15
    //-----------------------------------------------------------------------------------------------------------------------------------
    void CreateIncomePart();

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：CreateChargeTablePart
    // 作用：创建收费表格信息部分控件
    // 参数：无
    // 返回值：无
    // 备注：无
    // 时间：2016-04-15
    //-----------------------------------------------------------------------------------------------------------------------------------
    void CreateChargeTablePart();

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：SetMyLayout
    // 作用：将门诊收费界面所有控件进行布局
    // 参数：无
    // 返回值：无
    // 备注：无
    // 时间：2016-04-15
    //-----------------------------------------------------------------------------------------------------------------------------------
    void setMyLayout();

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：Read
    // 作用：从数据类中读取收费单，并更新至界面
    // 参数：无
    // 返回值：
    // true  - 读取成功
    // false - 读取失败
    // 备注：无
    // 时间：2016-04-15
    //-----------------------------------------------------------------------------------------------------------------------------------
    bool Read();

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：Save
    // 作用：将界面上的数据保存到数据库中
    // 参数：无
    // 返回值：
    // true  - 保存成功
    // false - 保存失败
    // 备注：无
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    bool Save();

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：Delete
    // 作用：从数据库中删除当前收费单
    // 参数：无
    // 返回值：
    // true  - 删除成功
    // false - 删除失败
    // 备注：无
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    bool Delete();

private:
    //-----------------------------------------------------------------------------------------------------------------------------------
    // - 界面
    //-----------------------------------------------------------------------------------------------------------------------------------
    QLabel *m_chargeNumLabel;                 // 收费单号
    QLabel *m_nameLabel;                      // 姓名
    QLabel *m_genderLabel;                    // 性别
    QLabel *m_ageLabel;                       // 年龄
    QLabel *m_idCardNumLabel;                 // 身份证号码
    QLabel *m_socialSecurityNumLabel;         // 社保号码
    QLabel *m_medicalInsuranceTypeLabel;      // 医保类型
    QLabel *m_departmentLabel;                // 科室
    QLabel *m_doctorLabel;                    // 医生
    QLabel *m_dueIncomeLabel;                 // 应收金额
    QLabel *m_realIncomeLabel;                // 实收金额

    QLineEdit *m_chargeNumEdit;               // 收费单号
    QLineEdit *m_nameEdit;                    // 姓名
    QLineEdit *m_ageEdit;                     // 年龄
    QLineEdit *m_idCardNumEdit;               // 身份证号码
    QLineEdit *m_socialSecurityNumEdit;       // 社保号码
    QLineEdit *m_departmentEdit;              // 科室
    QLineEdit *m_doctorEdit;                  // 医生
    QLineEdit *m_dueIncomeEdit;               // 应收金额
    QLineEdit *m_realIncomeEdit;              // 实收金额

    QComboBox *m_genderCombo;                 // 性别
    QComboBox *m_medicalInsuranceTypeCombo;   // 医保类型


    QTableView *m_chargeTableView;            // 收费明细表
    QStandardItemModel *m_chargeRecordsmodel;

    QGroupBox *m_patientGroup;                // 患者信息组
    QGroupBox *m_insuranceGroup;              // 医保信息组
    QGroupBox *m_doctorGroup;                 // 医生信息组
    QGroupBox *m_incomeGroup;                 // 应收信息组
    QGroupBox *m_chargeNumGroup;              // 实收信息组

    QToolButton *addRowButton;
    QToolButton *deleteRowButton;
    QToolButton *comboButton;

    //-----------------------------------------------------------------------------------------------------------------------------------
    // - 数据
    //-----------------------------------------------------------------------------------------------------------------------------------
    ClinicChargeTable *m_chargeTable;

};

#endif // CLINICCHARGE_H
