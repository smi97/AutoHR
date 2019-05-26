#include "new_vacancy.h"
#include "ui_new_vac.h"


new_vac::new_vac(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::new_vac)
{
    ui->setupUi(this);
    //all_skills = GetAllSkills();

    all_skills.push_back("C++");
    all_skills.push_back("Java");
    all_skills.push_back("Python");
    all_skills.push_back("Boost");

    for (auto &itr : all_skills){
        ui->listWidget->addItem(itr);
    }
}

new_vac::~new_vac()
{
    delete ui;
}

void new_vac::on_ChooseSkill_clicked()
{
    if(ui->listWidget->isItemSelected(ui->listWidget->currentItem())){
        QString skill = ui->listWidget->currentItem()->text();
        if (std::find(skills.begin(),skills.end(),skill) == skills.end()){
            skills.push_back(skill);
            ui->listWidget_2->addItem(skill);
        }
    }
}

void new_vac::on_CreateNewVacancy_clicked()
{
    QString job = ui->lineEdit->text();
    if (job.length() == 0){
        QMessageBox::warning(this,"Внимание","Введите название работы");
        return;
    }
    if (skills.empty()){
        QMessageBox::warning(this,"Внимание","Не выбрали навыки");
        return;
    }
    std::vector<QString> new_skills;
    std::vector<int> requirements;
    for (auto &itr: skills){
        vector<QString>::iterator it = std::find(all_skills.begin(), all_skills.end(),itr);
        if (it != skills.end()){
            requirements.push_back(it - all_skills.begin());
        }
        else{
            new_skills.push_back(itr);
            all_skills.push_back(itr);
            requirements.push_back(it - all_skills.begin());
        }
    }
    Vacancy new_vacancy(4,job.toStdString(),requirements);

    // Отправляем вакансию в базу данных
    //Add_To_BD(new_vacancy);
    // Отправляем новые скилы
    // Add_to_BD(new_skills)

    skills.clear();
    ui->listWidget_2->clear();
    ui->lineEdit->clear();
    QMessageBox::information(this,"Информация","Вакансия создана");
}

void new_vac::on_RemoveSkill_clicked()
{
    if(ui->listWidget_2->isItemSelected(ui->listWidget_2->currentItem())){
        QString skill = ui->listWidget_2->currentItem()->text();
        skills.erase(std::remove(skills.begin(),skills.end(),skill),skills.end());

        ui->listWidget_2->clear();
        for (auto &itr: skills)
            ui->listWidget_2->addItem(itr);
    }
}

void new_vac::on_CreateNewSkill_clicked()
{
    QString skill = QInputDialog::getText(this,"input","Skill:",QLineEdit::Normal);
    if(skill.length() == 0)
        return;
    if (std::find(skills.begin(),skills.end(),skill) == skills.end()){
        all_skills.push_back(skill);
        ui->listWidget->addItem(skill);
    }
}
