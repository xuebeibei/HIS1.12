#ifndef WINSTRING_H
#define WINSTRING_H
#include <QString>

const QString g_strNull = "";
const QString g_strIconPath = ":/icon/";
//---------------------------------------------------------------------------------------------------------------------------------------
// 医保类型
//---------------------------------------------------------------------------------------------------------------------------------------
enum MedicalInsuranceType
{
    selfPay = 0,   // 自费
    medicare = 1,  // 医保
    NCMS = 2       // 新农合
};

//---------------------------------------------------------------------------------------------------------------------------------------
// 性别
//---------------------------------------------------------------------------------------------------------------------------------------
enum Gender{
    man = 0,    // 男
    woman = 1   // 女
};

//---------------------------------------------------------------------------------------------------------------------------------------
// 门诊收据
//---------------------------------------------------------------------------------------------------------------------------------------
enum ClinicReceipt{
    drug = 0,
    other = 1
};

//---------------------------------------------------------------------------------------------------------------------------------------
// 护理级别
//---------------------------------------------------------------------------------------------------------------------------------------
enum NursingLevel{
    general = 0,
    first = 1,
    second = 2,
    third = 3
};

//---------------------------------------------------------------------------------------------------------------------------------------
// 账户操作
//---------------------------------------------------------------------------------------------------------------------------------------
enum AccountAction{
    payIn = 0,
    refund = 1,
    consume = 2
};

//---------------------------------------------------------------------------------------------------------------------------------------
// 付款方式
//---------------------------------------------------------------------------------------------------------------------------------------
enum PaymentMethod{
    cash = 0,
    slotCard = 1,
    bank = 2
};
//---------------------------------------------------------------------------------------------------------------------------------------
// 门诊收费记录
//---------------------------------------------------------------------------------------------------------------------------------------
enum ChargeItemIndex
{
    chargeItemNo = 0,    // 收费项编号
    chargeItemName = 1,  // 收费项名称
    chargeItemCount = 2, // 收费项数量
    chargeItemPrice = 3, // 收费项单价
    clinicReceipt = 4,   // 收费项所属门诊收据
    clinicSort = 5,      // 收费项所属门诊分类
    clinicChargeId = 6   // 收费项所属收费单单号
};

//---------------------------------------------------------------------------------------------------------------------------------------
// 数据库
//---------------------------------------------------------------------------------------------------------------------------------------
const QString g_strDBType = "QSQLITE";
// const QString g_strDBName = "./sqlite/test.db"; // 其他系统数据库路径
const QString g_strDBName = "./sqlite/test.db"; // windows相对路径
const QString g_strClinicCharge = "ClinicCharge";
const QString g_strClinicChargeDetails = "ClinicChargeDetails";
const QString g_strClinicDailyReport = "ClinicDailyReport";

const QString g_strHospitalRegistry = "HospitalRegistry";
const QString g_strInPatient = "Inpatient";
const QString g_strAccount = "Account";


//---------------------------------------------------------------------------------------------------------------------------------------
// 主窗体 - 工具栏
//---------------------------------------------------------------------------------------------------------------------------------------
const QString g_strNewAction = "新建";
const QString g_strSaveAction = "保存";
const QString g_strDeleteAction = "删除";
const QString g_strExportAction = "导出";
const QString g_strFindAction = "查找";
const QString g_strAmendAction = "修改";
const QString g_strComboAction = "套餐";
const QString g_strDeleteRowAction = "删除行";
const QString g_strAddRowAction = "添加行";
const QString g_strPreviewAction = "预览";
const QString g_strPrintAction = "打印";
const QString g_strFileToolBar = "文件";
const QString g_strEditToolBar = "编辑";
const QString g_strPrintToolBar = "打印";

//---------------------------------------------------------------------------------------------------------------------------------------
// 主窗体 - 菜单栏
//---------------------------------------------------------------------------------------------------------------------------------------
const QString g_strClinicMenu = "门诊";
const QString g_strhospitalMenu = "住院";
const QString g_strChargeAction = "收费";
const QString g_strDailyReportAction = "日结";
const QString g_strInternalPaymentAction = "内部缴款";

const QString g_strClinicChargeStatisticAction = "收费统计";
const QString g_strClinicReportStatisticAction = "日结统计";
const QString g_strClinicPaymentStatisticAction = "项目统计";

const QString g_strhospitalRegistryAction = "登记";
const QString g_strhospitalPayAction = "缴费";
const QString g_strhospitalDischargeAction = "出院";

const int g_nSubFormDefaultWidth = 850;
const int g_nSubFormDefaultHeight = 600;

const QString g_strPatientGroup = "患者信息";
const QString g_strNameLabel = "姓名：";
const QString g_strGenderLabel = "性别：";
const QString g_strMan = "男";
const QString g_strWoman = "女";
const QString g_strAgeLabel = "年龄：";
const QString g_strIdCardLabel = "身份证号：";
const QString g_strContactsLabel = "联系人：";
const QString g_strAddressLabel = "住址：";
const QString g_strTelLabel = "电话：";
const int g_nIdCardEditMinWidth = 135;

const QString g_strInsuranceGroup = "保险信息";
const QString g_strSocialSecurityNumLabel = "社保号码：";
const QString g_strMedicalInsuranceTypeLabel = "医保类型：";
const QString g_strNCMSNumLabel = "参合账号：";
const QString g_strSelfPay = "自费";
const QString g_strMedicare = "医保";
const QString g_strNCMS = "新农合";

const QString g_strDoctorGroup = "就诊信息";
const QString g_strDepartmentLabel = "就诊科室：";
const QString g_strDoctorLabel = "医生：";
const QString g_strBedNumLabel = "床位编号：";
const QString g_strNursingLevelLabel = "护理级别：";

const QString g_strHospitalisationNumLabel = "住院号：";
const QString g_strCaseNumLabel = "病历号：";
const QString g_strGuaranteeDepositLabel = "押金：";
const QString g_strDateLabel = "登记日期：";
const QString g_strMedicalResultLabel = "诊断结果：";


const QString g_strIncomeGroup = "收费信息";
const QString g_strDueIncomeLabel = "应收金额：";
const QString g_strRealIncomeLabel = "实收金额：";

const QString g_strClinicChargeNumGroup = "收费单信息";
const QString g_strClincChargeNumLabel = "收费单号：";

const QString g_strClinicChargeNumPR = "F";

const QString g_strChoiseButton = "选择";
const QString g_strCancelButton = "取消";



//---------------------------------------------------------------------------------------------------------------------------------------
// 门诊收费
//---------------------------------------------------------------------------------------------------------------------------------------
const QString g_strDailyReopotNumPR = "D";

const QString g_strStartDateLabel = "起始日期：";
const QString g_strEndDateLabel = "终止日期：";


#endif // WINSTRING_H
