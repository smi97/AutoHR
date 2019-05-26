#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    new_vacancy = new new_vac();
    connect(new_vacancy, &new_vac::firstWindow, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_OpenCreateVacancy_clicked()
{
    new_vacancy->show();
}

void MainWindow::on_GetVacancies_clicked()
{
    std::vector<Vacancy> vacancies;
    // Получаем вакансии из БД
    //vacancies = GetAllVacacies();

    vacancies.push_back({1,"Builder",{1,2,3}});
    vacancies.push_back({2,"Developer",{1,2,3}});
    vacancies.push_back({3,"Driver",{1,2,3}});
    vacancies.push_back({4,"Teacher",{1,2,3}});

    ui->listWidget->clear();
    for (auto & itr: vacancies){
        ui->listWidget->addItem(QString::fromStdString(itr.getJob()));
    }
}
