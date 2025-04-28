#include "../../inc/gui/hardwaresettings.hpp"

HardwareSettings::HardwareSettings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::HardwareSettings)
{
    ui->setupUi(this);
}

HardwareSettings::~HardwareSettings()
{
    delete ui;
}