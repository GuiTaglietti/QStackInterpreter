#include "../headers/customoptions.h"
#include "qlabel.h"
#include "qpushbutton.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

/**
 * @namespace stackinterpreter
 * @class CustomOptions
 * @extends QDialog
 * @brief A dialog for custom size control options
 * @param parent - Parent widget
 */
stackinterpreter::CustomOptions::CustomOptions(QWidget *parent) : QDialog(parent){
    QVBoxLayout *main = new QVBoxLayout(this);
    setMinimumWidth(600);
    setMaximumWidth(600);
    setWindowTitle("Size control options");

    label1 = new QLabel("Stack size:", this);
    label2 = new QLabel("Memory size:", this);
    input1 = new QLineEdit(this);
    input2 = new QLineEdit(this);

    input1->setPlaceholderText("Min: Number of actual elements in the stack - Max: 10000");
    input2->setPlaceholderText("Min: 256 - Max: 10000");

    QHBoxLayout *input1_layout = new QHBoxLayout;
    input1_layout->addWidget(label1);
    input1_layout->addWidget(input1);

    QHBoxLayout *input2_layout = new QHBoxLayout;
    input2_layout->addWidget(label2);
    input2_layout->addWidget(input2);

    ok_button = new QPushButton("OK", this);
    cancel_button = new QPushButton("Discard", this);

    QHBoxLayout *button_layout = new QHBoxLayout;
    button_layout->addWidget(ok_button);
    button_layout->addWidget(cancel_button);

    main->addLayout(input1_layout);
    main->addLayout(input2_layout);
    main->addLayout(button_layout);

    connect(ok_button, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel_button, SIGNAL(clicked()), this, SLOT(reject()));
}

/**
 * @constructor
 * @brief Copy constructor for CustomOptions
 * @param cpy - Another instance of CustomOptions to be copied
 */
stackinterpreter::CustomOptions::CustomOptions(const CustomOptions &cpy) : QDialog(nullptr){
    input1 = new QLineEdit(cpy.get_stack_size_input(), this);
    input2 = new QLineEdit(cpy.get_memory_size_input(), this);
    label1 = new QLabel("Stack size:", this);
    label2 = new QLabel("Memory size:", this);
    ok_button = new QPushButton("OK", this);
    cancel_button = new QPushButton("Discard", this);
}

/**
 * @destructor
 * @brief Destructor for CustomOptions, frees allocated resources
 */
stackinterpreter::CustomOptions::~CustomOptions(){
    delete input1;
    delete input2;
    delete ok_button;
    delete cancel_button;
    delete label1;
    delete label2;
}

/**
 * @function operator=
 * @brief Assignment operator for CustomOptions
 * @param rhs - Another instance of CustomOptions to be assigned
 * @return A reference to the modified instance
 */
stackinterpreter::CustomOptions& stackinterpreter::CustomOptions::operator=(const CustomOptions &rhs){
    if(this != &rhs){
        delete input1;
        delete input2;
        delete ok_button;
        delete cancel_button;
        delete label1;
        delete label2;
        input1 = new QLineEdit(rhs.get_stack_size_input(), this);
        input2 = new QLineEdit(rhs.get_memory_size_input(), this);
        label1 = new QLabel("Stack size:", this);
        label2 = new QLabel("Memory size:", this);
        ok_button = new QPushButton("OK", this);
        cancel_button = new QPushButton("Discard", this);
    }
    return *this;
}
