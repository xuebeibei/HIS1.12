#ifndef CLINICCHARGESTATISTICFORM_H
#define CLINICCHARGESTATISTICFORM_H

#include <QWidget>
#include "stdafx.h"
#include "subform.h"
#include "connectDB.h"

class ClinicChargeStatisticForm : public SubForm
{
    Q_OBJECT
    
public:
    explicit ClinicChargeStatisticForm(SubForm *parent = 0);
    ~ClinicChargeStatisticForm();

    void newTableFile();
    bool saveTableFile();
    bool deleteTableFile();
    void exportTableFile();
    bool findTableFile();
    void amendTableFile();
    void previewTableFile();
    void printTableFile();

    void create();
    void setMyLayout();
    void init();
    void initTable();

protected slots:
    void updateTable();

protected:
    QLabel *m_nameLabel;
    QLineEdit *m_nameEdit;
    QLabel *m_genderLabel;
    QComboBox *m_genderComboBox;
    QLabel *m_startDateLabel;
    QDateEdit *m_startDateEdit;
    QLabel *m_endDateLabel;
    QDateEdit *m_endDateEdit;

    QTableView *m_resultsView;
    QStandardItemModel *m_resultsModel;
};

#endif // CLINICCHARGESTATISTICFORM_H
