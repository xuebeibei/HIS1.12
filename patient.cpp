#include "patient.h"

Patient::Patient()
{
    m_strSocialSecurityNum = g_strNull;
    m_eMedicalInsuranceType = selfPay;
    m_strDepartment = g_strNull;
    m_strDoctor = g_strNull;
}

QString Patient::getSocialSecurityNum() const
{
    return m_strSocialSecurityNum;
}

MedicalInsuranceType Patient::getMedicalInsuranceType() const
{
    return m_eMedicalInsuranceType;
}

QString Patient::getDepartment() const
{
    return m_strDepartment;
}

QString Patient::getDoctor() const
{
    return m_strDoctor;
}

void Patient::setSocialSecurityNum(QString str_SocialSecurityNum)
{
    this->m_strSocialSecurityNum = str_SocialSecurityNum;
}

void Patient::setMedicalInsuranceType(MedicalInsuranceType edicalInsuranceType)
{
    this->m_eMedicalInsuranceType = edicalInsuranceType;
}

void Patient::setDepartment(QString str_Department)
{
    this->m_strDepartment = str_Department;
}

void Patient::setDoctor(QString str_Doctor)
{
    this->m_strDoctor = str_Doctor;
}
