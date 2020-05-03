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

    /// "Open file" action handler.
    void on_action_Open_triggered();

    /// "Save file" action handler.
    void on_action_Save_triggered();

    /// "Select dates" action handler.
    void on_action_Select_triggered();

    /// "Add dates" action handler.
    void on_action_Add_triggered();

    /// "Clear dates" action handler.
    void on_action_Clear_triggered();

    /// "Check selected row" action handler.
    void on_action_Check_selected_row_triggered();

    /// "Uncheck selected row" action handler.
    void on_action_Uncheck_selected_row_triggered();

    /// "Check selected column" action handler.
    void on_action_Check_selected_column_triggered();

    /// "Uncheck selected column" action handler.
    void on_action_Uncheck_selected_column_triggered();

    /// "Check all" action handler.
    void on_action_Check_all_triggered();

    /// "Uncheck all" action handler.
    void on_action_Uncheck_all_triggered();

protected:

    /// Opens file with students' list or attendance table.
    void openFile();

    /// Opens file with students' list (*.csv or *.txt).
    QList<Person*> openStudentsList(QString fileName);

    /// Opens file with attendance table (*.atnd).
    QList<Person*> openTable(QString fileName);

    /// Parses dates from CSV file header.
    void getDatesFromCsv(QString line);

    /// Saves file with attendance table.
    void saveFile();

    /** \brief Assembles a string of CSV headers.
     *  \return String with CSV headers.
     */
    QString getCsvHeaders();

    /// Opens dates selector.
    void selectDatesToAdd();

    /// Clears dates in table.
    void clearDates();

    /** \brief Sets all values in selected row to one value.
     *  \param checked -- Value to be set.
     */
    void setRowMarks(bool checked);

    /** \brief Sets all values in selected column to one value.
     *  \param checked -- Value to be set.
     */
    void setColumnMarks(bool checked);

    /** \brief Sets all values in table to one value.
     *  \param checked -- Value to be set.
     */
    void setAllTable(bool checked);

    /// Determines dates from dialog result.
    void getDates(QDate start, QDate end, bool* daysOfWeek);

    /** \brief Displays a message box.
     *  \param text -- Message text.
     */
    void showMessage(const char* text);

    /// Enables menu actions for date editing.
    void enableDateEdit();

    /** \brief Enables or disables menu actions for table editing.
     *  \param flag -- Enable/disable.
     */
    void setTableEditEnabled(bool flag);

protected:
    /// Model for displaying attendance table.
    AttendanceModel* _attendanceModel = nullptr;

    /// Dialog for date picking.
    DatePicker* _datePicker;

    /// Dates to mark.
    QList<QDate*> _dates;

    bool _modelHasDates = false;

protected:
    /// Main window UI.
    Ui::MainWindow* ui;
};

} // namespace vtmine

#endif // VTMINE_FRAMEWORK_PLUGINS_MAINWINDOW_H_
