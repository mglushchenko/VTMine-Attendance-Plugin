/***************************************************************************//**
 *  \file
 *  \brief     VTMine Framework plugin interface.
 *  \author    Sergey Shershakov, Maria Gluschenko
 *  \version   0.1.0
 *  \date      09.04.2020
 *  \copyright (c) xidv.ru 2014–2020.
 *             This source is for internal use only — Restricted Distribution.
 *             All rights reserved.
 *
 *  Attendance plugin main window.
 *
 ******************************************************************************/

#ifndef VTMINE_FRAMEWORK_PLUGINS_MAINWINDOW_H_
#define VTMINE_FRAMEWORK_PLUGINS_MAINWINDOW_H_


#include <QMainWindow>
#include <QPushButton>
#include <QStandardItemModel>

#include "attendance_model.h"
#include "date_picker.h"


namespace Ui {
class MainWindow;
}

namespace vtmine {

/***************************************************************************//**
 *  Plugin main window class.
 ******************************************************************************/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /// Class constructor.
    explicit MainWindow(QWidget* parent = nullptr);

    /// Class destructor.
    ~MainWindow();

private slots:
    void openFile();

    void on_pushButton_clicked();

    void on_selectDatesButton_clicked();

    void on_openFileButton_clicked();

protected:
    void getDates(QDate start, QDate end, bool* daysOfWeek);

protected:
    QPushButton* _openFileButton;
    AttendanceModel* _attendanceModel;

    DatePicker* _datePicker;

    QList<QDate> _dates;

protected:
    /// Main window UI.
    Ui::MainWindow* ui;
};

} // namespace vtmine

#endif // VTMINE_FRAMEWORK_PLUGINS_MAINWINDOW_H_
