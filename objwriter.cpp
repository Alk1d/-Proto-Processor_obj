#include "objwriter.h"
#include <QDebug>
#include <QFile>

ObjWriter::ObjWriter(QString filename) {file_extension = ".obj";}

void ObjWriter::setModelType(QString name)
{
    model = name;
}


int ObjWriter::selectWritingMode()
{
    QTextStream cin(stdin);
    qDebug() << "Select writing mode:";
    qDebug() << "Generate vertices, frames and polygons [1]";
    qDebug() << "Manual writing [2]";
    qDebug() << "Return [3]";
    writingMode = cin.readLine().toInt();
    return writingMode;
}

void ObjWriter::generateCubeModel()
{
    QTextStream cin(stdin);
    qDebug() << "Write a length of a cube edge:";
    double cube_length = 0;
    cube_length = cin.readLine().toDouble();
    qDebug() << "Write a coordinates for bottom-left point:";

    qDebug() << "x:";
    double cube_btmleft_point_x = 0;
    cube_btmleft_point_x = cin.readLine().toDouble();
    qDebug() << "y:";
    double cube_btmleft_point_y = 0;
    cube_btmleft_point_y = cin.readLine().toDouble();
    qDebug() << "z:";
    double cube_btmleft_point_z = 0;
    cube_btmleft_point_z = cin.readLine().toDouble();

    Point3D btmleft_point = {cube_btmleft_point_x, cube_btmleft_point_y, cube_btmleft_point_z};
    QVector<Point3D> cube_vertices = calculate_cube_vertices(btmleft_point, cube_length);

    QFile objFile(model + file_extension);
    if (objFile.open(QIODevice::WriteOnly))
    {
        QTextStream out(&objFile);
        out << "o " << model << "\n";
        // writing vertices, lines and polygons
        for (int i = 0; i < cube_vertices.size(); ++i)
        {
            QString vertice_x_string = QString::number(cube_vertices[i].x);
            QString vertice_y_string = QString::number(cube_vertices[i].y);
            QString vertice_z_string = QString::number(cube_vertices[i].z);
            out << "v " + vertice_x_string + " " + vertice_y_string + " " + vertice_z_string + "\n";
        }
        for (int i = 0; i < cube_lines.size(); ++i)
        {
            out << "l ";
            for (int j = 0; j < cube_lines[i].size(); ++j)
                out << cube_lines[i][j] << " ";
            out << "\n";
        }
        for (int i = 0; i < cube_faces.size(); ++i)
        {
            out << "f ";
            for (int j = 0; j < cube_faces[i].size(); ++j)
                out << cube_faces[i][j] << " ";
            out << "\n";
        }
        objFile.close();
        qDebug() << "OBJ file created";
    }
    else qDebug() << "Error creating OBJ file!";
}

//repeated code!
void ObjWriter::AddVertex(double x, double y, double z)
{
    QFile objFile(model + file_extension);
    if (objFile.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream out(&objFile);
        QString x_string = QString::number(x);
        QString y_string = QString::number(y);
        QString z_string = QString::number(z);
        out << "v " + x_string + " " + y_string + " " + z_string + "\n";
        objFile.close();
        qDebug() << "Vertex appended";
    }
    else qDebug() << "Error creating or appending OBJ file!";
}

void ObjWriter::AddLine(int vertex1, int vertex2)
{
    QFile objFile(model + file_extension);
    if (objFile.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream out(&objFile);
        QString vertex1_string = QString::number(vertex1);
        QString vertex2_string = QString::number(vertex2);
        out << "l " + vertex1_string + " " + vertex2_string + "\n";
        objFile.close();
        qDebug() << "FrameLine appended";
    }
    else qDebug() << "Error creating or appending OBJ file!";
}

void ObjWriter::AddFace(int vertex1, int vertex2, int vertex3)
{
    QFile objFile(model + file_extension);
    if (objFile.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream out(&objFile);
        QString vertex1_string = QString::number(vertex1);
        QString vertex2_string = QString::number(vertex2);
        QString vertex3_string = QString::number(vertex3);
        out << "f " + vertex1_string + " " + vertex2_string + " " + vertex3_string + "\n";
        objFile.close();
        qDebug() << "Face appended";
    }
    else qDebug() << "Error creating or appending OBJ file!";
}
