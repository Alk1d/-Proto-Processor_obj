#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include <QProcess>
#include <QFile>
#include <QVector>
#include <Header.h>

int main(int argc, char *argv[])
{
    QTextStream cin(stdin);
    // program main menu, change into a function later
    int mode = 0;

    while( mode != 3)
    {
        qDebug() << "Generate OBJ [1]";
        qDebug() << "Read OBJ [2]";
        qDebug() << "Exit [3]";
        mode = cin.readLine().toInt();
        switch (mode)
        {
        case 1:
        {
            qDebug() << "Select model:";
            qDebug() << "Cube [1]";
            QString model_type = "0";
            model_type = cin.readLine();

            qDebug() << "Write an object name:";
            QString model_name = "0";
            model_name = cin.readLine();
            if (model_type == "1")
            {
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

                QString file_extension = ".obj";
                QFile objFile(model_name + file_extension);
                if (objFile.open(QIODevice::WriteOnly))
                {
                    QTextStream out(&objFile);
                    out << "o " << model_name << "\n";
                    // writing loop in a file, need to add "f" (polygons) writing and "l" (lines)
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
            break;
        }
        case 2:
        {
            // using path to open file, #include QFileDialog gives file is not found
            qDebug() << "Enter .obj file path:";
            QString objfilepath = cin.readLine();

            QFile objfile(objfilepath);
            if (!objfile.open(QIODevice::ReadOnly)) {
                qDebug() << "Error: Could not open file: " << objfilepath.toStdString();
                break;
            }

            QTextStream in(&objfile);
            QString line = "0";
            QVector<Point3D> vertices;
            QVector<QVector<int>> faces;
            int vertex_counter = 0;
            int faces_counter = 0;
            while (!in.atEnd())
            {
                line = in.readLine();
                QStringList parts = line.split(" ");
                // add parts.first() == "f" later
                if (parts.first() == "v")
                {
                    vertex_counter++;
                    Point3D vertex;
                    vertex.x = parts[1].toDouble();
                    vertex.y = parts[2].toDouble();
                    vertex.z = parts[3].toDouble();
                    vertices.push_back(vertex);
                }
                else if (parts.first() == "f")
                {
                    faces_counter++;
                    QList<int> face_triangleList;
                    face_triangleList << parts[1].toInt();
                    face_triangleList << parts[2].toInt();
                    face_triangleList << parts[3].toInt();
                    faces.push_back(face_triangleList);
                    // use faces vector of vectors and populate it

                }
            }
            objfile.close();
            qDebug() << vertex_counter << "vertices";
            qDebug() << faces_counter << "polygons";
            qDebug() << "Vertices:";
            for (int i = 0; i < vertices.size(); ++i)
            {
                qDebug().nospace() << "("
                         << vertices[i].x << ", "
                         << vertices[i].y << ", "
                         << vertices[i].z << ")\n";
            }
            qDebug() << "Polygons:";
            for (int i = 0; i < faces.size(); ++i)
            {
                QDebug dbg(QtDebugMsg);
                dbg.nospace();
                dbg << "(";
                for (int j = 0; j < faces[i].size(); ++j)
                {
                    dbg << faces[i][j];
                    if (j < faces[i].size() - 1)
                        dbg << ", ";
                }
                dbg << ")\n";
            }
            break;
        }
        case 3:
            break;
        default:
            qDebug() << "Invalid choice";
        }
    }
}
