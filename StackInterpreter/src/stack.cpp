/**
 * @file stack.cpp
 * @author Guilherme Martinelli Taglietti
*/
#include "../headers/stack.h"
#include "qtextedit.h"
#include <QMessageBox>
#include <QInputDialog>

/**
 * @namespace stackinterpreter
 * @class Stack
 * @brief Represents the stack module of the stack interpreter.
 * @param _max_size - Maximum size of the stack.
 * @details Provides functionalities for managing the stack.
*/
stackinterpreter::Stack::Stack(qsizetype _max_size){ max_size =_max_size > max_possible_size ? max_possible_size : _max_size; }

/**
 * @namespace stackinterpreter
 * @class Stack
 * @brief Assignment operator for the Stack class.
 * @param rhs - Stack object to be assigned.
 * @return Reference to the modified Stack object.
 * @details Assigns the properties of the provided Stack object to the current object.
*/
stackinterpreter::Stack& stackinterpreter::Stack::operator=(const Stack &rhs){
    if(this != &rhs){
        max_size = rhs.max_size;
        stack = rhs.stack;
    }
    return *this;
}

/**
 * @namespace stackinterpreter
 * @class Stack
 * @brief Pushes an integer value onto the stack.
 * @param value - Integer value to be pushed onto the stack.
 * @details Checks for stack overflow and handles errors using QMessageBox.
*/
void stackinterpreter::Stack::PUSHI(int value) noexcept{
    if(stack.size() == max_size){
        QMessageBox::critical(nullptr, "Error!", "Stack overflow! Please clear or resize the stack to continue...");
        return;
    }
    stack.push(value);
}

/**
 * @namespace stackinterpreter
 * @class Stack
 * @brief Pushes an integer value onto the stack with additional logging functionality.
 * @param value - Integer value to be pushed onto the stack.
 * @param description - Description of the instruction.
 * @param log - Vector to store the instruction log.
 * @details Checks for stack overflow and handles errors using QMessageBox.
*/
void stackinterpreter::Stack::PUSHI(int value, const QString &description, QVector<QString> &log) noexcept{
    if(stack.size() == max_size){
        QMessageBox::critical(nullptr, "Error!", "Stack overflow! Please clear or resize the stack to continue...");
        return;
    }
    else if(value == -1)
        return;
    stackutil::log_write(description, log, QString::number(value));
    stack.push(value);
}

/**
 * @namespace stackinterpreter
 * @class Stack
 * @brief Pushes an integer value onto the stack.
 * @param value - Integer value to be pushed onto the stack.
 * @param description - Description of the instruction.
 * @param log - Vector to store the instruction log.
 * @details Checks for stack underflow, pushes the value onto the stack, and logs the action.
*/
void stackinterpreter::Stack::PUSH(int value, const QString &description, QVector<QString> &log) noexcept{
    if(stack.empty()){
        QMessageBox::critical(nullptr, "Error!", "Stack underflow! Not enough values to execute the instruction...");
        return;
    }
    else if(value == -1)
        return;
    int value1 = stack.top();
    bool ok = push_in(stackinterpreter::mem_slot(value, value1, true), *this);
    if(ok){
        mem_log.append("Address " + QString::number(value) + " pushed in memory the value: " + QString::number(value1) + "\n");
        stackutil::log_write(description, log, QString::number(value1));
    }
}

/**
 * @namespace stackinterpreter
 * @class Stack
 * @brief Pops a value from memory and pushes it onto the stack.
 * @param value - Address of the memory slot.
 * @param description - Description of the instruction.
 * @param log - Vector to store the instruction log.
 * @details Checks for stack overflow, pops a value from memory, pushes it onto the stack, and logs the action.
*/
void stackinterpreter::Stack::POP(int value, const QString &description, QVector<QString> &log) noexcept{
    if(stack.size() == max_size){
        QMessageBox::critical(nullptr, "Error!", "Stack overflow! Please clear or resize the stack to continue...");
        return;
    }
    else if(value == -1)
        return;
    stackinterpreter::mem_slot slot_buffer = stackinterpreter::mem_slot(value, mem[value].value, false);
    bool ok = pop_out(slot_buffer, *this);
    if(ok){
        mem_log.append("Address " + QString::number(value) + " removed the value " + QString::number(slot_buffer.value) + " from the memory and pushed it to the stack\n" );
        stackutil::log_write(description, log, QString::number(value));
    }
}


/**
 * @namespace stackinterpreter
 * @class Stack
 * @brief Reads input from the user and pushes it onto the stack.
 * @param parent - Parent widget for input dialog.
 * @param description - Description of the instruction.
 * @param log - Vector to store the instruction log.
 * @details Checks for stack overflow, reads input from the user, pushes it onto the stack, and logs the action.
*/
void stackinterpreter::Stack::INPUT(QWidget *parent, const QString &description, QVector<QString> &log) noexcept{
    if(stack.size() == max_size){
        QMessageBox::critical(nullptr, "Error!", "Stack overflow! Please clear or resize the stack to continue...");
        return;
    }
    bool ok;
    int value = QInputDialog::getInt(parent, "Type a number", "Number:", 0, -2147483647, 2147483647, 1, &ok);
    if(ok){
        stack.push(value);
        stackutil::log_write(description, log, QString::number(value));
    }
    else
        QMessageBox::information(parent, "Warning", "Instruction canceled!");
}

/**
 * @namespace stackinterpreter
 * @class Stack
 * @brief Prints the top value of the stack and discards it.
 * @param parent - Parent widget for message box.
 * @param description - Description of the instruction.
 * @param log - Vector to store the instruction log.
 * @details Checks for stack underflow, prints the top value of the stack, discards it, and logs the action.
*/
void stackinterpreter::Stack::PRINT(QWidget *parent, const QString &description, QVector<QString> &log) noexcept{
    if(stack.empty()){
        QMessageBox::critical(nullptr, "Error!", "Stack underflow! Not enough values to execute the instruction...");
        return;
    }
    int value = stack.top();
    stack.pop();
    stackutil::log_write(description, log, QString::number(value));
    QMessageBox::information(parent, "PRINT Instruction", "Value discarded and printed: " + QString::fromStdString(std::to_string(value)));
}

/**
 * @namespace stackinterpreter
 * @class Stack
 * @brief Adds the top two values of the stack.
 * @param description - Description of the instruction.
 * @param log - Vector to store the instruction log.
 * @details Checks for stack underflow, pops the top two values from the stack, adds them, pushes the result onto the stack, and logs the action.
*/
void stackinterpreter::Stack::ADD(const QString &description, QVector<QString> &log) noexcept{
    if(stack.empty() || stack.size() == 1){
        QMessageBox::critical(nullptr, "Error!", "Stack underflow! Not enough values to execute the instruction...");
        return;
    }
    int value1, value2;
    value1 = stack.top(); stack.pop();
    value2 = stack.top(); stack.pop();
    stack.push(value2 + value1);
    stackutil::log_write(description, log, QString::number(value1), QString::number(value2));
}

/**
 * @namespace stackinterpreter
 * @class Stack
 * @brief Subtracts the top value from the second top value of the stack.
 * @param description - Description of the instruction.
 * @param log - Vector to store the instruction log.
 * @details Checks for stack underflow, pops the top two values from the stack, subtracts them, pushes the result onto the stack, and logs the action.
*/
void stackinterpreter::Stack::SUB(const QString &description, QVector<QString> &log) noexcept{
    if(stack.empty() || stack.size() == 1){
        QMessageBox::critical(nullptr, "Error!", "Stack underflow! Not enough values to execute the instruction...");
        return;
    }
    int value1, value2;
    value1 = stack.top(); stack.pop();
    value2 = stack.top(); stack.pop();
    stack.push(value2 - value1);
    stackutil::log_write(description, log, QString::number(value1), QString::number(value2));
}

/**
 * @namespace stackinterpreter
 * @class Stack
 * @brief Multiplies the top two values of the stack.
 * @param description - Description of the instruction.
 * @param log - Vector to store the instruction log.
 * @details Checks for stack underflow, pops the top two values from the stack, multiplies them, pushes the result onto the stack, and logs the action.
*/
void stackinterpreter::Stack::MUL(const QString &description, QVector<QString> &log) noexcept{
    if(stack.empty() || stack.size() == 1){
        QMessageBox::critical(nullptr, "Error!", "Stack underflow! Not enough values to execute the instruction...");
        return;
    }
    int value1, value2;
    value1 = stack.top(); stack.pop();
    value2 = stack.top(); stack.pop();
    stack.push(value2 * value1);
    stackutil::log_write(description, log, QString::number(value1), QString::number(value2));
}


/**
 * @namespace stackinterpreter
 * @class Stack
 * @brief Divides the second top value by the top value of the stack.
 * @param description - Description of the instruction.
 * @param log - Vector to store the instruction log.
 * @details Checks for stack underflow, pops the top two values from the stack, divides them, pushes the result onto the stack, and logs the action.
*/
void stackinterpreter::Stack::DIV(const QString &description, QVector<QString> &log) noexcept{
    if(stack.empty() || stack.size() == 1){
        QMessageBox::critical(nullptr, "Error!", "Stack underflow! Not enough values to execute the instruction...");
        return;
    }
    else if(stack.top() == 0){
        QMessageBox::critical(nullptr, "Error!", "Division by zero is impossible!");
        return;
    }
    int value1, value2;
    value1 = stack.top(); stack.pop();
    value2 = stack.top(); stack.pop();
    stack.push(value2 / value1);
    stackutil::log_write(description, log, QString::number(value1), QString::number(value2));
}

/**
 * @namespace stackinterpreter
 * @class Stack
 * @brief Swaps the top two values of the stack.
 * @param description - Description of the instruction.
 * @param log - Vector to store the instruction log.
 * @details Checks for stack underflow, pops the top two values from the stack, swaps them, and pushes them back onto the stack, then logs the action.
*/
void stackinterpreter::Stack::SWAP(const QString &description, QVector<QString> &log) noexcept{
    if(stack.empty() || stack.size() == 1){
        QMessageBox::critical(nullptr, "Error!", "Stack underflow! Not enough values to execute the instruction...");
        return;
    }
    int value1, value2;
    value1 = stack.top(); stack.pop();
    value2 = stack.top(); stack.pop();
    stack.push(value1);
    stack.push(value2);
    stackutil::log_write(description, log, QString::number(value1), QString::number(value2));
}

/**
 * @namespace stackinterpreter
 * @class Stack
 * @brief Removes and returns the top value of the stack.
 * @return The top value of the stack.
 * @details Checks for stack underflow, removes and returns the top value of the stack.
*/
int stackinterpreter::Stack::DROP() noexcept{
    if(stack.empty()){
        QMessageBox::critical(nullptr, "Error!", "Stack underflow! Not enough values to execute the instruction...");
        return -1;
    }
    int value = stack.top();
    stack.pop();
    return value;
}

/**
 * @namespace stackinterpreter
 * @class Stack
 * @brief Removes and returns the top value of the stack, and logs the action.
 * @param description - Description of the instruction.
 * @param log - Vector to store the instruction log.
 * @return The top value of the stack.
 * @details Checks for stack underflow, removes and returns the top value of the stack, and logs the action.
*/
int stackinterpreter::Stack::DROP(const QString &description, QVector<QString> &log) noexcept{
    if(stack.empty()){
        QMessageBox::critical(nullptr, "Error!", "Stack underflow! Not enough values to execute the instruction...");
        return -1;
    }
    int value = stack.top();
    stack.pop();
    stackutil::log_write(description, log, QString::number(value));
    return value;
}

/**
 * @namespace stackinterpreter
 * @class Stack
 * @brief Duplicates the top value of the stack and pushes it onto the stack.
 * @param description - Description of the instruction.
 * @param log - Vector to store the instruction log.
 * @details Checks for stack overflow, duplicates the top value of the stack, pushes it onto the stack, and logs the action.
*/
void stackinterpreter::Stack::DUP(const QString &description, QVector<QString> &log) noexcept{
    if(stack.size() == max_size){
        QMessageBox::critical(nullptr, "Error!", "Stack overflow! Please clear or resize the stack to continue...");
        return;
    }
    int value = stack.top();
    stack.push(value);
    stackutil::log_write(description, log, QString::number(value));
}

/**
 * @namespace stackinterpreter
 * @class Stack
 * @brief Halts the program by clearing the stack and logging the action.
 * @param description - Description of the instruction.
 * @param log - Vector to store the instruction log.
 * @details Clears the stack and logs the action
*/
void stackinterpreter::Stack::HLT(const QString &description, QVector<QString> &log) noexcept{
    while(!stack.empty())
        stack.pop();
    stackutil::log_write(description, log);
    clear_log();
}

/**
 * @namespace stackinterpreter
 * @class Stack
 * @brief Resizes the stack to a new size if possible.
 * @param new_size - The new size for the stack.
 * @return True if the resizing was successful, false otherwise.
 * @details Checks if the new size is smaller than the current maximum size and smaller than the current stack size. If so, updates the maximum size and returns true, indicating success. Otherwise, returns false.
*/
bool stackinterpreter::Stack::resize_stack(qsizetype new_size) noexcept{
    if(new_size < max_size && new_size < stack.size())
        return false;
    max_size = new_size;
    return true;
}

/**
 * @namespace stackinterpreter
 * @class Stack
 * @brief Displays the memory log in a QTextEdit widget.
 * @param os - The QTextEdit widget to display the memory log.
 * @details Concatenates all memory log strings and sets the text of the QTextEdit widget to the resulting string.
*/
void stackinterpreter::Stack::display_memory_log(QTextEdit &os) const noexcept{
    QString text;
    for(const QString &mem_log_str : mem_log)
        text.append(mem_log_str);
    os.setText(text);
}

/**
 * @namespace stackinterpreter
 * @brief Overloaded operator to display the stack in a QLineEdit widget.
 * @param os - The QLineEdit widget to display the stack.
 * @param stack - The Stack object to display.
 * @details Prepares a copy of the stack, formats it as a string, and sets the text of the QLineEdit widget to the formatted string.
*/
void stackinterpreter::operator<<(QLineEdit &os, const stackinterpreter::Stack &stack){
    QStack<int> stack_buffer = stack.get_stack();
    stack_buffer = stackinterpreter::stackutil::prepare(stack_buffer);
    QString text;
    while(!stack_buffer.empty()){
        text += QString::number(stack_buffer.top());
        stack_buffer.pop();
        if(!stack_buffer.empty())
            text += " - ";
    }
    os.setText(text);
}

/// STACKUTIL NAMESPACE IMPLEMENTATIONS BELOW

/**
 * @namespace stackinterpreter
 * @namespace stackutil
 * @brief Prepares a copy of a stack for display.
 * @param orig - The original stack.
 * @return A copy of the original stack.
 * @details If the original stack is empty or has only one element, returns the original stack. Otherwise, creates a copy of the original stack by popping all elements and pushing them onto a new stack, then returns the copy.
*/
QStack<int> stackinterpreter::stackutil::prepare(QStack<int> &orig) noexcept{
    if(orig.empty() || orig.size() == 1)
        return orig;
    QStack<int> cpy;
    while(!orig.empty()){
        cpy.push(orig.top());
        orig.pop();
    }
    return cpy;
}

/**
 * @namespace stackinterpreter
 * @namespace stackutil
 * @brief Writes an instruction to the log with optional values.
 * @param instruction - The instruction to write to the log.
 * @param log - The vector to store the instruction log.
 * @param value1 - Optional value 1 to include in the log.
 * @param value2 - Optional value 2 to include in the log.
 * @details If both value1 and value2 are "null", appends only the instruction to the log. If value2 is "null", appends the instruction followed by value1. Otherwise, appends the instruction followed by value1 and value2, separated by a space.
*/
void stackinterpreter::stackutil::log_write(const QString &instruction, QVector<QString> &log, const QString &value1, const QString &value2) noexcept{
    if(value1 == "null" && value2 == "null"){
        log.append(instruction);
        return;
    }
    else if(value2 == "null"){
        log.append(instruction + "    " + value1);
        return;
    }
    log.append(instruction + "    " + value1 + " " + value2);
}

