#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QListView>
#include <QListWidget>
#include "QMessageBox"

#include "../../Vacancy.hpp"
#include <new_vacancy.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_OpenCreateVacancy_clicked();
    void on_GetVacancies_clicked();

private:
    Ui::MainWindow *ui;
    new_vac * new_vacancy;
};

#endif // MAINWINDOW_H
