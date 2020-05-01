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
 *  Date picker dialog.
 *
 ******************************************************************************/


#ifndef VTMINE_FRAMEWORK_PLUGINS_DATEPICKER_H_
#define VTMINE_FRAMEWORK_PLUGINS_DATEPICKER_H_


#include <QWidget>
#include <QDate>


namespace Ui {
class DatePicker;
}

namespace vtmine {

class DatePicker : public QWidget
{
    Q_OBJECT

public:
    /// Class constructor.
    explicit DatePicker(QWidget *parent = nullptr);

    /// Class destructor.
    ~DatePicker();

    /// Start date getter.
    QDate getStartDate() const { return _startDate; }

    /// End date getter.
    QDate getEndDate() const { return _endDate; }

    /// Getter for selected days.
    bool* getDays() const { return _days; }

protected:
    /// Selected start date.
    QDate _startDate;

    /// Selected end date.
    QDate _endDate;

    /// Selected days of week.
    bool* _days;

protected:
    /// Widget UI.
    Ui::DatePicker *ui;
private slots:
    void on_okBtn_clicked();
    void on_startDatePicker_userDateChanged(const QDate &date);
    void on_endDatePicker_userDateChanged(const QDate &date);
};

} // namespace vtmine

#endif // VTMINE_FRAMEWORK_PLUGINS_DATEPICKER_H_
