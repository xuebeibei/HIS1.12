#include "contacts.h"

Contacts::Contacts()
{
    m_strTel = g_strNull;
    m_strAddress = g_strNull;
}

QString Contacts::getTel() const
{
    return m_strTel;
}

QString Contacts::getAddress() const
{
    return m_strAddress;
}


void Contacts::setTel(QString strTel)
{
    m_strTel = strTel;
}

void Contacts::setAddress(QString strAddress)
{
    m_strAddress = strAddress;
}
