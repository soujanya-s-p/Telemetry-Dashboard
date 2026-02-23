#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <QString>
#include <QMap>

class DataParser
{
public:
    static QMap<QString, double> parse(const QString &data);
};

#endif
