#include "persion.h"

Persion::Persion()
{
    m_strName = g_strNull;
    m_nAge = 0;
    m_eGender = man;
    m_strIDCard = g_strNull;
}

QString Persion::getName() const
{
    return m_strName;
}

int Persion::getAge() const
{
    return m_nAge;
}

Gender Persion::getGender() const
{
    return m_eGender;
}

QString Persion::getIDCard() const
{
    return m_strIDCard;
}

void Persion::setName(QString str_Name)
{
    this->m_strName = str_Name;
}

void Persion::setAge(int n_Age)
{
    this->m_nAge = n_Age;
}

void Persion::setGender(Gender e_Gender)
{
    this->m_eGender = e_Gender;
}

void Persion::setIDCard(QString str_IDCard)
{
    this->m_strIDCard = str_IDCard;
}
