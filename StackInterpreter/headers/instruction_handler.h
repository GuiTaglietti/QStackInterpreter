/**
 * @headerfile instruction_handler.h
 * @author Guilherme Martinelli Taglietti
*/
#ifndef INSTRUCTION_HANDLER_H
#define INSTRUCTION_HANDLER_H

#include <QString>
#include "instructions.h" // Enum
#include "qtextedit.h"
#include "stack.h"

namespace stackinterpreter{

typedef struct instruction_tuple{
    stackinterpreter::Instructions instruction; // Enum type
    int                            value;       // Can be null in case where the instruction is not PUSHI, PUSH or POP
    QString                        description; // Description to add do instruction log

    /// Constructors
    instruction_tuple(){}
    instruction_tuple(stackinterpreter::Instructions _instruction, int _value): instruction(_instruction), value(_value){}
    instruction_tuple(stackinterpreter::Instructions _instruction, int _value, const QString &_description): instruction(_instruction), value(_value), description(_description){}
} instruction_tuple;

class InstructionHandler{
public:
    explicit InstructionHandler(){}
    virtual ~InstructionHandler(){}

    /// Deleting copy constructor && assignment operator
    InstructionHandler(const InstructionHandler &cpy) = delete;
    InstructionHandler& operator=(const InstructionHandler &rhs) = delete;

    void execute(QWidget* parent, stackinterpreter::Stack &stack, int enumtype, int value, InstructionHandler &handler, const QString &description = "null") noexcept; /// T instead of int value soon
    [[nodiscard]] stackinterpreter::instruction_tuple handle_instruction(int enumtype, const QString &val = "null") noexcept;
                  /*       ALIAS TYPE RETURN       */
    [[nodiscard]] QVector<QString>& get_log() noexcept { return log; } /// Inline function
    void clear_log() noexcept { log.clear(); } /// Inline function
    [[nodiscard]] int hex_to_int(const QString &hex) const noexcept;
    [[nodiscard]] bool is_valid_number(const QString &numstr) const noexcept;

    friend QTextEdit& operator<<(QTextEdit &textEdit, InstructionHandler &handler);

private:
    QVector<QString> log;
};

} // namespsace stackinterpreter

#endif // INSTRUCTION_HANDLER_H
