#include "objreader.h"
#include <QFile>
#include <QDebug>
ObjReader::ObjReader() {}

bool ObjReader::readFile(QString filepath)
{
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error: Could not open file:" << filepath.toStdString();
        return false;
    }
    QTextStream in(&file);

    while (!in.atEnd())
    {
        line = in.readLine();
        QStringList parts = line.split(" ");
        if (parts.first() == "v")
        {
            Point3D vertex;
            vertex.x = parts[1].toDouble();
            vertex.y = parts[2].toDouble();
            vertex.z = parts[3].toDouble();
            vertices.push_back(vertex);
        }
        else if (parts.first() == "l")
        {
            QList<int> frameLineList;
            frameLineList << parts[1].toInt();
            frameLineList << parts[2].toInt();
            frameLines.push_back(frameLineList);
        }
        else if (parts.first() == "f")
        {
            QList<int> faceTriangleList;
            faceTriangleList << parts[1].toInt();
            faceTriangleList << parts[2].toInt();
            faceTriangleList << parts[3].toInt();
            faces.push_back(faceTriangleList);
        }
    }
    objfile = in.readAll();
    file.close();
    return true;
}
int ObjReader::getVertexCount()
{
    return vertices.size();
}

Point3D ObjReader::getVertexPoint(int point)
{
    return  vertices[point];
}

int ObjReader::getFrameLinesCount()
{
    return frameLines.size();
}

QVector<int> ObjReader::getFrameLine(int line)
{
    return frameLines[line];
}

int ObjReader::getFacesCount()
{
    return faces.size();
}

QVector<int> ObjReader::getFace(int face)
{
    return faces[face];
}
