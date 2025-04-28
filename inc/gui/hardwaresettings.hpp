#pragma once

#include <QDialog>
#include "../../res/ui/ui_hardwaresettings.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class HardwareSettings;

}
QT_END_NAMESPACE

class HardwareSettings : public QDialog
{
    Q_OBJECT

public:
    HardwareSettings(QWidget *parent = nullptr);
    ~HardwareSettings();

private slots:
    void onSaveButtonClicked();
    void onCancelButtonClicked();

private:
    Ui::HardwareSettings *ui;
    
};