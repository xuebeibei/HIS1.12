#ifndef CLINICCHARGETABLE_H
#define CLINICCHARGETABLE_H
#include "histable.h"
#include "patient.h"
#include "chargeitem.h"
#include "chargetable.h"


const QString g_strName = QObject::tr("Name");
const QString g_strGender = QObject::tr("Gender");
const QString g_strAge = QObject::tr("Age");
const QString g_strIdCardNum = QObject::tr("IdCardNum");
const QString g_strSocialSecurityNum = QObject::tr("SocialSecurityNum");
const QString g_strMedicalInsuranceType = QObject::tr("MedicalInsuranceType");
const QString g_strDepartment = QObject::tr("Department");
const QString g_strDoctor = QObject::tr("Doctor");

const QString g_strDueIncome= QObject::tr("DueIncome");
const QString g_strRealIncome = QObject::tr("RealIncome");
const QString g_strMaker = QObject::tr("Maker"); // temp

const QString g_strYMD = QObject::tr("yyyy-MM-dd");
const QString g_strDayStartTime = QObject::tr("T00:00:00");
const QString g_strDayEndTime = QObject::tr("T23:59:59");


//-----------------------------------------------------------------------------------------------------------------------------------
// 门诊收费单数据类
//-----------------------------------------------------------------------------------------------------------------------------------
class ClinicChargeTable : public ChargeTable,public HISTable
{
public:
    ClinicChargeTable();

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：getNewClinicChargeID
    // 作用：根据年月日时分秒毫秒计算一个新的收费单单号
    // 参数：无
    // 返回值：
    // QString - 收费单编号
    // 备注：无
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    QString getNewClinicChargeID();

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：getRealImcome
    // 作用：得到实收金额
    // 参数：无
    // 返回值：
    // double - 实收金额
    // 备注：无
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    double getRealImcome() const;

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：getPatient
    // 作用：得到收费单所属患者的信息
    // 参数：无
    // 返回值：
    // Patient - 收费单所属患者的信息
    // 备注：无
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    Patient getPatient() const;

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：setRealIncome
    // 作用：设置实收金额
    // 参数：
    // d_RealIncome - 实收金额
    // 返回值：无
    // 备注：无
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    void setRealIncome(double d_RealIncome);

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：setPatient
    // 作用：设置收费单所属患者
    // 参数：
    // patient - 患者
    // 返回值：无
    // 备注：无
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    void setPatient(Patient patient);

    bool Read();
    bool Save();
    bool Delete();

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：selectClinicChargesFromDb
    // 作用：对某天的收费单做日结处理
    // 参数：
    // date - 日结需要的日期
    // ReportTime - 日结操作发生的时间
    // 返回值：
    // QVector<ClinicChargeTable*> - 收费单数组
    // 备注：无
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    static QVector<ClinicChargeTable*> selectClinicChargesFromDb(QDate date , QDateTime ReportTime);

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：selectFromDB
    // 作用：从数据库中查找一段时间内，某个人或者所有人的门诊收费单
    // 参数：
    // startDate - 起始查找日期
    // endDate - 结束查找日期
    // strName - 姓名
    // eGender - 性别
    // 返回值：
    // QVector<ClinicChargeTable*>* - 收费单数组
    // 备注：无
    // 时间：2016-04-20
    //-----------------------------------------------------------------------------------------------------------------------------------
    static QVector<ClinicChargeTable*> * selectFromDB(QDate startDate, QDate endDate, QString strName, Gender eGender);
protected:
    double m_dRealIncome;                     // 实收金额
    Patient m_patient;                        // 患者
};

#endif // CLINICCHARGETABLE_H
