/**
 * @headerfile instructions.h
 * @author Guilherme Martinelli Taglietti
*/
#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

namespace stackinterpreter{

/**
 * @namespace stackinterpreter
 * @enum
 * @brief Enum class used to hold the possible set of instructions that te interpreter can use.
*/
enum Instructions{
    PUSHI,
    PUSH,
    POP,
    INPUT,
    PRINT,
    ADD,
    SUB,
    MUL,
    DIV,
    SWAP,
    DROP,
    DUP,
    HLT,
    ERROR
};

} // namespace stackinterpreter

#endif // INSTRUCTIONS_H
