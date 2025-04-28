#include "../../inc/gui/IRSVTsettingsdialog.hpp"
#include "../../res/ui/ui_IRSVTsettingsdialog.h"

IRSVTSettingsDialog::IRSVTSettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::IRSVTSettingsDialog)
{
    ui->setupUi(this);

    QObject::connect(ui->save_button, &QPushButton::clicked,
                    this, &IRSVTSettingsDialog::onSaveButtonClicked);
    QObject::connect(ui->cancel_button, &QPushButton::clicked,
                    this, &IRSVTSettingsDialog::onCancelButtonClicked);
}

IRSVTSettingsDialog::~IRSVTSettingsDialog()
{
    delete ui;
}

void IRSVTSettingsDialog::onSaveButtonClicked(){
    // save test settings
    accept();
}

void IRSVTSettingsDialog::onCancelButtonClicked(){
    reject();
}