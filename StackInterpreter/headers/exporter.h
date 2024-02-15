#ifndef EXPORTER_H
#define EXPORTER_H

#include <QString>

namespace stackinterpreter{

class Exporter{
public:
    explicit Exporter(){}
    explicit Exporter(const Exporter &cpy) = delete;
    Exporter& operator=(const Exporter &rhs) = delete;

    [[nodiscard]] virtual bool export_to_file(const QVector<QString> &instruction_log) const = 0;
};

} // namespace stackinterpreter

#endif // EXPORTER_H
