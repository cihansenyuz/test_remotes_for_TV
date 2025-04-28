#include "../../inc/gui/hardwaresettings.hpp"
#include "../../inc/ina238config.hpp"

HardwareSettings::HardwareSettings(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::HardwareSettings)
{
    ui->setupUi(this);

    QObject::connect(ui->save_button, &QPushButton::clicked,
                    this, &HardwareSettings::onSaveButtonClicked);
    QObject::connect(ui->cancel_button, &QPushButton::clicked,
                    this, &HardwareSettings::onCancelButtonClicked);
}

HardwareSettings::~HardwareSettings()
{
    delete ui;
}

void HardwareSettings::onSaveButtonClicked(){
    INA238Config::getInstance().setDeviceAddress(ui->device_address_spinbox->value());
    INA238Config::getInstance().setBusNumber(ui->bus_number_spinbox->value());
    INA238Config::getInstance().setShuntResistance(ui->shunt_resistance_spinbox->value());
    INA238Config::getInstance().setMaxCurrent(ui->max_current_spinbox->value());

    INA238Config::getInstance().setIRPin(ui->ir_pin_spinbox->value());
    INA238Config::getInstance().setServoPin(ui->servo_pin_spinbox->value());
    INA238Config::getInstance().setRelayPin(ui->relay_pin_spinbox->value());
    accept();
}

void HardwareSettings::onCancelButtonClicked(){
    reject();
}