/*******************************************************************************
 *
 *  VTMine Framework.
 *  (c) xidv.ru 2014–2020.
 *
 *  This source is for internal use only — Restricted Distribution.
 *  All rights reserved.
 *
 ******************************************************************************/


#include <QGridLayout>
#include <QFileDialog>
#include <QErrorMessage>
#include <QMessageBox>
#include <QTextStream>
#include <QHeaderView>

#include <fstream>

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
    QGridLayout* layout = new QGridLayout();
    layout->addWidget(ui->attendanceTable);

    _central = new QWidget();
    _central->setLayout(layout);
    setCentralWidget(_central);
    ui->attendanceTable->resizeColumnsToContents();
    ui->attendanceTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{ 
    for (QDate* date: _dates)
        delete date;
    delete _attendanceModel;
    delete _central;
    delete ui;
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(0, "Open file", "",
                                                    "*.atnd *.csv *.txt");

    QList<Person*> personList;
    if (fileName.contains(".txt") || fileName.contains(".csv"))
        personList = openStudentsList(fileName);
    else {
        personList = openTable(fileName);
        setTableEditEnabled(true);
    }

    enableDateEdit();

    if (_attendanceModel)
        delete _attendanceModel;

    _attendanceModel = new AttendanceModel(personList);
    ui->attendanceTable->setModel(_attendanceModel);
}

QList<Person*> MainWindow::openStudentsList(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        showMessage("Can't open file!");
        return QList<Person*>();
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

    return personList;
}

QList<Person*> MainWindow::openTable(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        showMessage("Can't open file!");
        return QList<Person*>();
    }

    QTextStream fin(&file);

    QString line = fin.readLine();
    getDatesFromCsv(line);

    QList<Person*> personList;
    while (!fin.atEnd())
    {
        line = fin.readLine();
        Person* p = new Person(line, _dates);
        personList.append(p);
    }
    file.close();
    return personList;
}

void MainWindow::getDatesFromCsv(QString line)
{
    if (!_dates.empty())
        _dates.clear();

    char delim = ';';
    QStringList headerList = line.split(delim);
    for (int i = 2; i < headerList.size(); ++i)
    {
        QDate date = QDate::fromString(headerList[i], "yyyy-dd-MM");
        _dates.append(new QDate(date));
    }
}

void MainWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(0, "Save file",
                                                    "", "*.atnd");
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        showMessage("Can't save file!");
        return;
    }
    QTextStream out(&file);

    out << getCsvHeaders();
    for (Person* p: _attendanceModel->getPersonList())
        out << p->toCsv();

    file.close();

    showMessage("File saved successfully!");
}

QString MainWindow::getCsvHeaders()
{
    char delim = ';';
    QString headers[2] = {"ID", "Name"};
    QString res = headers[0] + delim;
    res += headers[1] + delim;
    for (QDate* date: _dates)
    {
        res += date->toString("yyyy-dd-MM") + delim;
    }
    res.remove(res.size() - 1, 1);
    res += "\n";
    return res;
}

void MainWindow::selectDatesToAdd()
{
    _datePicker = new DatePicker(this);
    _datePicker->exec();

    if (_datePicker->getDatesConfirmed())
    {
        QDate startDate = _datePicker->getStartDate();
        QDate endDate = _datePicker->getEndDate();
        bool* days = _datePicker->getDays();
        getDates(startDate, endDate, days);
        _attendanceModel->addDates(_dates);
        setTableEditEnabled(true);
    }

    delete _datePicker;

}

void MainWindow::clearDates()
{
    _attendanceModel->clearDates();
    setTableEditEnabled(false);
}

void MainWindow::setRowMarks(bool checked)
{
    int row = ui->attendanceTable->selectionModel()->currentIndex().row();
    _attendanceModel->setMarksForPerson(row, checked);
}

void MainWindow::setColumnMarks(bool checked)
{
    int column = ui->attendanceTable->selectionModel()->currentIndex().column();
    _attendanceModel->setMarksForDate(column, checked);
}

void MainWindow::setAllTable(bool checked)
{
    for (int i = 0; i < _attendanceModel->rowCount(); ++i)
        _attendanceModel->setMarksForPerson(i, checked);
}


void MainWindow::getDates(QDate start, QDate end, bool* daysOfWeek)
{
    if (!_dates.empty())
        _dates.clear();
    QDate tmp = start;
    do {
        if (daysOfWeek[tmp.dayOfWeek() - 1])
            _dates.append(new QDate(tmp));
        tmp = tmp.addDays(1);
    } while (tmp <= end);
}

void MainWindow::showMessage(const char* text)
{
    QMessageBox* msg = new QMessageBox();
    msg->setText(text);
    msg->setAttribute(Qt::WA_DeleteOnClose);
    msg->exec();
}

void MainWindow::enableDateEdit()
{
    ui->action_Add->setEnabled(true);
    ui->action_Select->setEnabled(true);
    ui->action_Clear->setEnabled(true);
}

void MainWindow::setTableEditEnabled(bool flag)
{
    ui->action_Save->setEnabled(true);
    ui->action_Check_all->setEnabled(true);
    ui->action_Uncheck_all->setEnabled(true);
    ui->action_Check_selected_row->setEnabled(true);
    ui->action_Uncheck_selected_row->setEnabled(true);
    ui->action_Check_selected_column->setEnabled(true);
    ui->action_Uncheck_selected_column->setEnabled(true);
}

void MainWindow::on_action_Open_triggered()
{
    openFile();
}

void MainWindow::on_action_Save_triggered()
{
    saveFile();
}

void MainWindow::on_action_Select_triggered()
{
    if (_modelHasDates)
        clearDates();
    selectDatesToAdd();
    _modelHasDates = true;
}

void MainWindow::on_action_Add_triggered()
{
    selectDatesToAdd();
    _modelHasDates = true;
}

void MainWindow::on_action_Clear_triggered()
{
    clearDates();
    _modelHasDates = false;
}

void MainWindow::on_action_Check_selected_row_triggered()
{
    setRowMarks(true);
}

void MainWindow::on_action_Uncheck_selected_row_triggered()
{
    setRowMarks(false);
}

void MainWindow::on_action_Check_selected_column_triggered()
{
    setColumnMarks(true);
}

void MainWindow::on_action_Uncheck_selected_column_triggered()
{
    setColumnMarks(false);
}

void MainWindow::on_action_Check_all_triggered()
{
    setAllTable(true);
}

void MainWindow::on_action_Uncheck_all_triggered()
{
    setAllTable(false);
}

} // namespace vtmine



