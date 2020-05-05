/*******************************************************************************
 *
 *  VTMine Framework.
 *  (c) xidv.ru 2014–2020.
 *
 *  This source is for internal use only — Restricted Distribution.
 *  All rights reserved.
 *
 ******************************************************************************/


#include <QFile>
#include <QTextStream>

#include "helpwindow.h"
#include "ui_helpwindow.h"


namespace vtmine {

HelpWindow::HelpWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpWindow)
{
    ui->setupUi(this);
}

HelpWindow::~HelpWindow()
{
    delete ui;
}

void HelpWindow::openFile(QString& path)
{
    QFile file(path);
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream stream(&file);
    ui->textEdit->setText(stream.readAll());
}

} // namespace vtmine
