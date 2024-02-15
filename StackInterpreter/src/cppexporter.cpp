#include "../headers/cppexporter.h"
#include <fstream>
#include <QVector>
#include <QStringList>
#include <QDir>

/**
 * @namespace stackinterpreter
 * @class ASMExporter @extends Exporter
 * @name export_to_file
 * @brief Create a .cpp (C++ file) based on the current stack and operations log
 * @param instruction_log
 * @return true if successfully exported, else false
 */
bool stackinterpreter::CPPExporter::export_to_file(const QVector<QString> &instruction_log) const{
    if(!instruction_log.size())
        return false;
    try{
        std::ofstream cppfile(filename.toStdString().c_str());
        cppfile << "#include <iostream>\n#include <stack>\n\nint main(){\n    std::stack<int> stack;\n";
        bool is_declared = false;
        for(const QString &instruction : instruction_log){
            QStringList parsed = instruction.split("    ");
            if(parsed[0] == "PUSHI")
                cppfile << "    stack.push(" << parsed[1].toInt() << ");\n";
            else if(parsed[0] == "PUSH")
                cppfile << "    stack.pop(); /* PUSHED A VALUE FROM THE STACK TO MEMORY IN THE ADDRESS: " << parsed[1].toInt() << " */\n";
            else if(parsed[0] == "POP")
                cppfile << "    stack.push(" << parsed[1].toInt() << "); /* PUSHED A VALUE THAT WAS ON MEMORY TO THE STACK: " << parsed[1].toInt() << " */\n";
            else if(parsed[0] == "INPUT")
                cppfile << "    stack.push(" << parsed[1].toInt() << ");\n";
            else if(parsed[0] == "ADD"){
                if(!is_declared){
                    cppfile << "    int v1 = stack.top(); stack.pop();\n    int v2 = stack.top(); stack.pop();\n";
                    cppfile << "    stack.push(v1 + v2);\n";
                    is_declared = true;
                }
                else{
                    cppfile << "    v1 = stack.top(); stack.pop();\n    v2 = stack.top(); stack.pop();\n";
                    cppfile << "    stack.push(v1 + v2);\n";
                }
            }
            else if(parsed[0] == "SUB"){
                if(!is_declared){
                    cppfile << "    int v1 = stack.top(); stack.pop();\n    int v2 = stack.top(); stack.pop();\n";
                    cppfile << "    stack.push(v1 - v2);\n";
                    is_declared = true;
                }
                else{
                    cppfile << "    v1 = stack.top(); stack.pop();\n    v2 = stack.top(); stack.pop();\n";
                    cppfile << "    stack.push(v1 - v2);\n";
                }
            }
            else if(parsed[0] == "MUL"){
                if(!is_declared){
                    cppfile << "    int v1 = stack.top(); stack.pop();\n    int v2 = stack.top(); stack.pop();\n";
                    cppfile << "    stack.push(v1 * v2);\n";
                    is_declared = true;
                }
                else{
                    cppfile << "    v1 = stack.top(); stack.pop();\n    v2 = stack.top(); stack.pop();\n";
                    cppfile << "    stack.push(v1 * v2);\n";
                }
            }
            else if(parsed[0] == "DIV"){
                if(!is_declared){
                    cppfile << "    int v1 = stack.top(); stack.pop();\n    int v2 = stack.top(); stack.pop();\n";
                    cppfile << "    stack.push(v1 / v2);\n";
                    is_declared = true;
                }
                else{
                    cppfile << "    v1 = stack.top(); stack.pop();\n    v2 = stack.top(); stack.pop();\n";
                    cppfile << "    stack.push(v1 / v2);\n";
                }
            }
            else if(parsed[0] == "SWAP"){
                if(!is_declared){
                    cppfile << "    int v1 = stack.top(); stack.pop();\n    int v2 = stack.top(); stack.pop();\n";
                    cppfile << "    stack.push(v1);\n";
                    cppfile << "    stack.push(v2);\n";
                }
                else{
                    cppfile << "    v1 = stack.top(); stack.pop();\n    v2 = stack.top(); stack.pop();\n";
                    cppfile << "    stack.push(v1);\n";
                    cppfile << "    stack.push(v2);\n";
                }
            }
            else if(parsed[0] == "DUP")
                cppfile << "    stack.push(stack.top());\n";
            else if(parsed[0] == "DROP")
                cppfile << "    stack.pop();\n";
            else if(parsed[0] == "PRINT")
                cppfile << "    stack.pop();\n";
        }
        cppfile << "    return 0;\n}";
        return true;
    } catch(const std::exception &exception){
        QFile::remove(filename);
        return false;
    }
}
