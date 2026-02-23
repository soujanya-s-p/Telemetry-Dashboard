#include "dataparser.h"

QMap<QString, double> DataParser::parse(const QString &data)
{
    QMap<QString, double> map;

    QStringList pairs = data.split(",");

    for(const QString &pair : pairs)
    {
        QStringList kv = pair.split(":");
        if(kv.size() == 2)
        {
            map[kv[0]] = kv[1].toDouble();
        }
    }

    return map;
}
