#ifndef HEADER_H
#define HEADER_H
#include <QVector>

struct Point3D {
    double x;
    double y;
    double z;
};
QVector<Point3D> calculate_cube_vertices(Point3D bottom_left_vertex, double side_length);

extern QVector<QVector<int>> cube_lines;

extern QVector<QVector<int>> cube_faces;

#endif // HEADER_H
