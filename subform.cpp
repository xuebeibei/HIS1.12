#include "subform.h"
#include "stdafx.h"

SubForm::SubForm(QWidget *parent) :
    QWidget(parent)
{
    setMinimumWidth(g_nSubFormDefaultWidth);
    setMinimumHeight(g_nSubFormDefaultHeight);
}

SubForm::~SubForm()
{
}
