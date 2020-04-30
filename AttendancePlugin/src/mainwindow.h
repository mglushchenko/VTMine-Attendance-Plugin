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
 *  Plugin main window.
 *
 ******************************************************************************/

#ifndef VTMINE_FRAMEWORK_PLUGINS_MAINWINDOW_H_
#define VTMINE_FRAMEWORK_PLUGINS_MAINWINDOW_H_


#include <QMainWindow>


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

private:
    /// Main window UI.
    Ui::MainWindow* ui;
};

} // namespace vtmine

#endif // VTMINE_FRAMEWORK_PLUGINS_MAINWINDOW_H_
