#ifndef ASMEXPORTER_H
#define ASMEXPORTER_H

#include "exporter.h"

namespace stackinterpreter{

class ASMExporter : public Exporter{
public:
    explicit ASMExporter() : ASMExporter("export.asm"){}
    explicit ASMExporter(const char* _filename) : filename(_filename){}
    ASMExporter(const ASMExporter &cpy) = delete;
    ASMExporter& operator=(const ASMExporter &rhs) = delete;

    [[nodiscard]] bool export_to_file(const QVector<QString> &instruction_log) const override;

private:
    QString filename;
};

}

#endif // ASMEXPORTER_H
