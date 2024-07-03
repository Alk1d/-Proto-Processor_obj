#ifndef OBJREADER_H
#define OBJREADER_H
#include <QString>
#include <QFile>
#include "Header.h"

class ObjReader
{
public:
    ObjReader();
    bool readFile(QString filepath);

    int getVertexCount();
    Point3D getVertexPoint(int point);

    int getFrameLinesCount();
    QVector<int> getFrameLine(int line);

    int getFacesCount();
    QVector<int> getFace(int face);

private:
    QString objfile;
    QString line;
    QVector<Point3D> vertices;
    QVector<QVector<int>> frameLines;
    QVector<QVector<int>> faces;
};


#endif // OBJREADER_H
