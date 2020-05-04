/*******************************************************************************
 *
 *  VTMine Framework.
 *  (c) xidv.ru 2014–2020.
 *
 *  This source is for internal use only — Restricted Distribution.
 *  All rights reserved.
 *
 ******************************************************************************/


#include <QErrorMessage>

#include "date_picker.h"
#include "ui_date_picker.h"


namespace vtmine {

DatePicker::DatePicker(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DatePicker)
{
    ui->setupUi(this);

    _days = new bool[7];
    for (int i = 0; i < 7; ++i)
    {
        if (i < 5)
            _days[i] = true;
        else
            _days[i] = false;
    }

    QDate today = QDate::currentDate();
    ui->startDatePicker->setDate(today);
    ui->endDatePicker->setDate(today);

    _datesConfirmed = false;
}

DatePicker::~DatePicker()
{
    delete _days;
    delete ui;
}

void DatePicker::on_okBtn_clicked()
{
    if (_startDate > _endDate)
    {
        QErrorMessage* msg = new QErrorMessage();
        msg->setAttribute(Qt::WA_DeleteOnClose);
        msg->showMessage("End date should be equal or "
                         "later than the start date!");
        return;
    }

    QList<QCheckBox*> boxes = ui->groupBox->findChildren<QCheckBox*>();
    for (int i = 0; i < boxes.size(); ++i)
    {
        if (boxes[i]->isChecked())
            _days[i] = true;
        else
            _days[i] = false;
    }

    _datesConfirmed = true;
    close();
}

void DatePicker::on_startDatePicker_userDateChanged(const QDate& date)
{
    _startDate = date;
}

void DatePicker::on_endDatePicker_userDateChanged(const QDate& date)
{
    _endDate = date;
}

} // namespace vtmine



