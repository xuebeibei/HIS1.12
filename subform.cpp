#include "subform.h"
#include "stdafx.h"

SubForm::SubForm(QWidget *parent) :
    QWidget(parent)
{
    createToolButtons();
}

SubForm::~SubForm()
{
}


void SubForm::createToolButtons()
{
    m_newButton = new QToolButton;
    m_newButton->setIcon(QIcon(g_strIconPath + "new.png"));
    m_newButton->setToolTip("new");
    connect(m_newButton, SIGNAL(clicked()), this, SLOT(newTableFile()));

    m_saveButton = new QToolButton;
    m_saveButton->setIcon(QIcon(g_strIconPath + "save.png"));
    m_saveButton->setToolTip("save");
    connect(m_saveButton, SIGNAL(clicked()), this, SLOT(saveTableFile()));

    m_deleteButton = new QToolButton;
    m_deleteButton->setIcon(QIcon(g_strIconPath + "delete.png"));
    m_deleteButton->setToolTip("delete");
    connect(m_deleteButton, SIGNAL(clicked()), this, SLOT(deleteTableFile()));

    m_amendButton = new QToolButton;
    m_amendButton->setIcon(QIcon(g_strIconPath + "amend.png"));
    m_amendButton->setToolTip("amend");
    connect(m_amendButton, SIGNAL(clicked()), this, SLOT(amendTableFile()));

    m_findButton = new QToolButton;
    m_findButton->setIcon(QIcon(g_strIconPath + "find.png"));
    m_findButton->setToolTip("find");
    connect(m_findButton, SIGNAL(clicked()), this, SLOT(findTableFile()));
}

