#pragma once

#include <QMainWindow>
#include <memory>
#include "gui/hardwaresettings.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;

}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onRunTestButtonClicked();

private:
    Ui::MainWindow *ui;
    std::unique_ptr<HardwareSettings> hardware_settings;
    
};