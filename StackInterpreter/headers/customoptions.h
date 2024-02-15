#ifndef CUSTOMOPTIONS_H
#define CUSTOMOPTIONS_H

#include "qdialog.h"
#include "qlabel.h"
#include "qlineedit.h"

namespace stackinterpreter{

class CustomOptions : public QDialog{
    Q_OBJECT

public:
    CustomOptions() : CustomOptions(nullptr){}
    CustomOptions(QWidget *parent);
    CustomOptions(const CustomOptions &cpy);
    virtual ~CustomOptions();
    CustomOptions& operator=(const CustomOptions &rhs);

    [[nodiscard]] QString get_stack_size_input() const { return input1->text(); } /// Inline function
    [[nodiscard]] QString get_memory_size_input() const { return input2->text(); } /// Inline function

    void init() { this->exec(); }; /// Inline function

private:
    QLineEdit *input1;
    QLineEdit *input2;
    QPushButton *ok_button;
    QPushButton *cancel_button;
    QLabel *label1;
    QLabel *label2;

};

}

#endif // CUSTOMOPTIONS_H
