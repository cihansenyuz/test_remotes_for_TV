#include "../../inc/gui/IRSVTsettingsdialog.hpp"
#include "../../res/ui/ui_IRSVTsettingsdialog.h"
#include "../../inc/testconfig.hpp"

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
    TestSettings::getInstance().IR.dataSize = ui->dataSizeSpinBox->value();
    TestSettings::getInstance().IR.minHeaderDuration = ui->minHeaderDurationSpinBox->value();
    TestSettings::getInstance().IR.maxHeaderDuration = ui->maxHeaderDurationSpinBox->value();

    TestSettings::getInstance().IRSVT.totalTestCount = ui->totalTestCountSpinBox->value();
    TestSettings::getInstance().IRSVT.testQuantityToMeasure = ui->testQuantityToMeasureSpinBox->value();
    TestSettings::getInstance().IRSVT.measurementQuantityToSave = ui->measurementQuantityToSaveSpinBox->value();
    TestSettings::getInstance().IRSVT.totalErrorToFailTest = ui->totalErrorToFailTestSpinBox->value();

    accept();
}

void IRSVTSettingsDialog::onCancelButtonClicked(){
    reject();
}