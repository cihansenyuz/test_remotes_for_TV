#pragma once

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class IRSVTSettingsDialog;

}
QT_END_NAMESPACE

class IRSVTSettingsDialog : public QDialog
{
    Q_OBJECT

public:
    IRSVTSettingsDialog(QWidget *parent = nullptr);
    ~IRSVTSettingsDialog();

private slots:
    void onSaveButtonClicked();
    void onCancelButtonClicked();

private:
    Ui::IRSVTSettingsDialog *ui;
    
};