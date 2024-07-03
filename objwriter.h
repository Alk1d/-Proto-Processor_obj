#ifndef OBJWRITER_H
#define OBJWRITER_H
#include "Header.h"
#include <QString>

class ObjWriter
{
public:
    ObjWriter(QString filename);
    int selectWritingMode();

    void setModelType(QString name);
    void generateCubeModel();

    void AddVertex(double x, double y, double z);
    void AddLine(int vertex1, int vertex2);
    void AddFace(int vertex1, int vertex2, int vertex3);

private:
    QString model;
    int writingMode;
    QString file_extension;
};

#endif // OBJWRITER_H
