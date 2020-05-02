/*******************************************************************************
 *
 *  VTMine Framework.
 *  (c) xidv.ru 2014–2020.
 *
 *  This source is for internal use only — Restricted Distribution.
 *  All rights reserved.
 *
 ******************************************************************************/


#include <QFileDialog>
#include <QErrorMessage>
#include <QTextStream>
#include <QHeaderView>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "person.h"
#include "date_picker.h"


namespace vtmine {

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->attendanceTable->horizontalHeader()->setStretchLastSection(true);
}

MainWindow::~MainWindow()
{ 
    for (QDate* date: _dates)
        delete date;
    delete _attendanceModel;
    delete ui;
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(0, "Open file", "",
                                                    "*.csv *.txt");
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QErrorMessage* msg = new QErrorMessage();
        msg->setAttribute(Qt::WA_DeleteOnClose);
        msg->showMessage("Can't open file!");
        return;
    }

    QTextStream fin(&file);
    int counter = 1;
    QList<Person*> personList;
    while (!fin.atEnd())
    {
        QString line = fin.readLine();     
        for (QString next: line.split(";"))
        {
            personList.append(new Person(next, counter++));
        }
    }
    file.close();

    _attendanceModel = new AttendanceModel(personList);
    ui->attendanceTable->setModel(_attendanceModel);
}

void MainWindow::on_selectDatesButton_clicked()
{
    _datePicker = new DatePicker(this);
    _datePicker->exec();
    QDate startDate = _datePicker->getStartDate();
    QDate endDate = _datePicker->getEndDate();
    bool* days = _datePicker->getDays();

    delete _datePicker;

    getDates(startDate, endDate, days);
    _attendanceModel->addDates(_dates);
}

void MainWindow::on_openFileButton_clicked()
{
    openFile();
}

void MainWindow::getDates(QDate start, QDate end, bool* daysOfWeek)
{
    QDate tmp = start;
    do {
        if (daysOfWeek[tmp.dayOfWeek() - 1])
            _dates.append(new QDate(tmp));
        tmp = tmp.addDays(1);
    } while (tmp <= end);
}

} // namespace vtmine





