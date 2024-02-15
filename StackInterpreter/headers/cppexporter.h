#ifndef CPPEXPORTER_H
#define CPPEXPORTER_H

#include "exporter.h"

namespace stackinterpreter{

class CPPExporter : public Exporter{
public:
    explicit CPPExporter() : CPPExporter("export.cpp"){}
    explicit CPPExporter(const char* _filename) : filename(_filename){}
    CPPExporter(const CPPExporter &cpy) = delete;
    CPPExporter& operator=(const CPPExporter &rhs) = delete;

    [[nodiscard]] bool export_to_file(const QVector<QString> &instruction_log) const override;

private:
    QString filename;
};

} // namespace stackinterpreter

#endif // CPPEXPORTER_H
