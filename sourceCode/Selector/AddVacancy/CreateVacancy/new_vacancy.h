#ifndef NEW_VAC_H
#define NEW_VAC_H

#include <QInputDialog>
#include <QMessageBox>
#include <vector>
#include <algorithm>
#include "../../Vacancy.hpp"

namespace Ui {
class new_vac;
}

class new_vac : public QWidget
{
    Q_OBJECT

public:
    explicit new_vac(QWidget *parent = nullptr);
    ~new_vac();


signals:
    void firstWindow();

private slots:
    // Слот-обработчик нажатия кнопки

    void on_ChooseSkill_clicked();

    void on_CreateNewVacancy_clicked();

    void on_RemoveSkill_clicked();

    void on_CreateNewSkill_clicked();

private:
    Ui::new_vac *ui;
    std::vector<QString> skills;
    std::vector<Vacancy> vacancy;
    std::vector<QString> all_skills;
};

#endif // NEW_VAC_H
