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
    TestSettings::getInstance().IR.dataSize = ui->dataSizeSpinBox->getValue();
    TestSettings::getInstance().IR.minHeaderDuration = ui->minHeaderDurationSpinBox->getValue();
    TestSettings::getInstance().IR.maxHeaderDuration = ui->maxHeaderDurationSpinBox->getValue();

    TestSettings::getInstance().IRSVT.totalTestCount = ui->totalTestCountSpinBox->getValue();
    TestSettings::getInstance().IRSVT.testQuantityToMeasure = ui->testQuantityToMeasureSpinBox->getValue();
    TestSettings::getInstance().IRSVT.measurementQuantityToSave = ui->measurementQuantityToSaveSpinBox->getValue();
    TestSettings::getInstance().IRSVT.totalErrorToFailTest = ui->totalErrorToFailTestSpinBox->getValue();

    accept();
}

void IRSVTSettingsDialog::onCancelButtonClicked(){
    reject();
}