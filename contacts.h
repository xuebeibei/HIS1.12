#ifndef CONTACTS_H
#define CONTACTS_H
#include "persion.h"

class Contacts : public Persion
{
public:
    Contacts();
    QString getTel() const;
    QString getAddress() const;

    void setTel(QString strTel);
    void setAddress(QString strAddress);

protected:
    QString m_strTel;      // 电话
    QString m_strAddress;  // 住址
};

#endif // CONTACTS_H
