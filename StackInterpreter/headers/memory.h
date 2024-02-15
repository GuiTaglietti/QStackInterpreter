/**
 * @headerfile memory.h
 * @author Guilherme Martinelli Taglietti
*/
#ifndef MEMORY_H
#define MEMORY_H

#pragma once

#include "qcontainerfwd.h"
#include "QVector"

namespace stackinterpreter{

class Stack; // Forward declaration (Used in member functions)

typedef struct mem_slot{
    qsizetype  address;    /// --> Simulates the address of a Harvard architecture memory
    int        value;     ///  --> Value wich will be inserted on the memory at the specified address
    bool       occupied; ///   --> Flag to control if a slot is occuppied or not

    /// Constructors
    mem_slot() : occupied(false){} // All slots are not occuppied by default
    mem_slot(qsizetype _address, int _value, bool _occupied) : address(_address), value(_value), occupied(_occupied){}
} mem_slot;

class Memory{
public:
    Memory() : Memory(256){} // Default size = 256
    Memory(qsizetype _max_mem_size);
    Memory(const Memory &cpy);
    Memory& operator=(const Memory &rhs);

    bool push_in(const mem_slot &slot, stackinterpreter::Stack &stack) noexcept;
    bool pop_out(const mem_slot &slot, stackinterpreter::Stack &stack) noexcept;
    [[nodiscard]] bool resize_memory(qsizetype new_size) noexcept;
    /// @brief Return the max size that the current memory supports
    /// @return max_mem_size
    [[nodiscard]] qsizetype get_max_mem_size() const noexcept { return max_mem_size; } // Inline function
    /// @brief Return the max possible size that the memory can fit
    /// @return max_possible_mem_size
    [[nodiscard]] qsizetype get_max_possible_mem_size() const noexcept { return max_possible_mem_size; } // Inline function
    /// @brief Return a const reference to the memory log (Used to display de memory log in the UI)
    /// @return mem_log
    [[nodiscard]] const QVector<QString>& get_mem_log() const noexcept{ return mem_log; } // Inline function
    /// @brief Clear the memory operations log
    void clear_log() noexcept { mem_log.clear(); } // Inline function
    /// @brief Clear the memory vector
    void clear_memory() noexcept { mem.clear(); } // Inline function

protected:
    QVector<mem_slot> mem; /// QVector used to simulate the Harvard architecture memory
    QVector<QString> mem_log; /// QString vector used to store all the operations realized in the memory
    qsizetype max_mem_size; /// Max size that the current memory supports
    const qsizetype max_possible_mem_size = 10000; /// Max possible size that the memory can fit
    /// @brief Return if a memory slot is occupied or not
    /// @return occupied
    [[nodiscard]] bool is_occupied(int address) const noexcept { return mem[address].occupied; } // Inline function
};

} // namespace stackinterpreter

#endif // MEMORY_H
