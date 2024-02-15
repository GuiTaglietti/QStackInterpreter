#include "../headers/memory.h"
#include "../headers/stack.h"
#include <QMessageBox>

/**
 * @namespace stackinterpreter
 * @class Memory
 * @brief Constructor - Represents the memory module of the stack interpreter.
 * @param _max_mem_size - Maximum size of the memory.
 * @details Provides functionalities for managing memory slots.
*/
stackinterpreter::Memory::Memory(qsizetype _max_mem_size) : max_mem_size(_max_mem_size){
    mem.resize(max_mem_size);
    mem.assign(max_mem_size, stackinterpreter::mem_slot());
}

/**
 * @namespace stackinterpreter
 * @class Memory
 * @brief Copy constructor for the Memory class.
 * @param cpy - Memory object to be copied.
 * @details Initializes a new Memory object with the same properties as the provided object.
*/
stackinterpreter::Memory::Memory(const Memory &cpy) : mem(cpy.mem), max_mem_size(cpy.max_mem_size){
    mem.resize(max_mem_size);
    mem.assign(max_mem_size, stackinterpreter::mem_slot());
}

/**
 * @namespace stackinterpreter
 * @class Memory
 * @brief Assignment operator for the Memory class.
 * @param rhs - Memory object to be assigned.
 * @return Reference to the modified Memory object.
 * @details Assigns the properties of the provided Memory object to the current object.
*/
stackinterpreter::Memory& stackinterpreter::Memory::operator=(const Memory &rhs){
    if(this != &rhs){
        mem = rhs.mem;
        max_mem_size = rhs.max_mem_size;
    }
    return *this;
}

/**
 * @namespace stackinterpreter
 * @class Memory
 * @brief Pushes a value into the memory slot.
 * @param slot - Memory slot to insert the value.
 * @param stack - Stack object for error handling.
 * @return True if the operation is successful, false otherwise.
 * @details Inserts a value into the memory slot and handles errors using QMessageBox.
*/
bool stackinterpreter::Memory::push_in(const mem_slot &slot, stackinterpreter::Stack &stack) noexcept{
    if(slot.address == -1 || slot.address >= max_mem_size){
        QMessageBox::critical(nullptr, "Error!", "Error inserting the value in memory, check hexadecimal address!");
        return false;
    }
    int value = stack.DROP();
    mem[slot.address] = stackinterpreter::mem_slot(slot.address, value, true);
    return true;
}

/**
 * @namespace stackinterpreter
 * @class Memory
 * @brief Pops a value out of the memory slot.
 * @param slot - Memory slot to remove the value from.
 * @param stack - Stack object for error handling.
 * @return True if the operation is successful, false otherwise.
 * @details Removes a value from the memory slot and handles errors using QMessageBox.
*/
bool stackinterpreter::Memory::pop_out(const mem_slot &slot, stackinterpreter::Stack &stack) noexcept{
    if(slot.address == -1 || slot.address >= max_mem_size){
        QMessageBox::critical(nullptr, "Error!", "Error removing the value in memory, check hexadecimal address!");
        return false;
    }
    else if(!is_occupied(slot.address)){
        QMessageBox::critical(nullptr, "Error!", "Error removing empty memory slot!");
        return false;
    }
    int value = slot.value;
    mem[slot.address] = stackinterpreter::mem_slot();
    stack.PUSHI(value);
    return true;
}

/**
 * @namespace stackinterpreter
 * @class Memory
 * @brief Resizes the memory.
 * @param new_size - New size for the memory.
 * @return True if the operation is successful, false otherwise.
 * @details Resizes the memory to the specified size, if it's valid.
*/
bool stackinterpreter::Memory::resize_memory(qsizetype new_size) noexcept{
    if(new_size < max_mem_size && new_size < mem.size())
        return false;
    max_mem_size = new_size;
    return true;
}
