#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "customoptions.h"
#include "instruction_handler.h"
#include "stack.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init_selector() noexcept;

private slots:
    void on_instructions_select_currentIndexChanged(int index);
    void on_exec_button_clicked();
    void update_stack_progressbar();
    void on_cpp_export_button_clicked();
    void on_asm_export_button_clicked();
    void on_options_button_clicked();
    void on_clear_memory_log_button_clicked();
    void on_clear_instructions_log_button_clicked();
    void on_about_triggered();

private:
    Ui::MainWindow *ui;
    stackinterpreter::InstructionHandler instruction_handler;
    stackinterpreter::Stack stack;
    stackinterpreter::CustomOptions *options_dialog_box;
};
#endif // MAINWINDOW_H
