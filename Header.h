#ifndef HEADER_H
#define HEADER_H
#include <QVector>

struct Point3D {
    double x;
    double y;
    double z;
};
QVector<Point3D> calculate_cube_vertices(Point3D bottom_left_vertex, double side_length)
{
    QVector<Point3D> vertices;
    // Offsets for each vertex relative to the bottom-left vertex
    QVector<Point3D> offsets = {
        {0, 0, 0},
        {side_length, 0, 0},
        {side_length, side_length, 0},
        {0, side_length, 0},
        {0, 0, side_length},
        {side_length, 0, side_length},
        {side_length, side_length, side_length},
        {0, side_length, side_length}
    };

    // Add the offsets to the bottom-left vertex coordinates
    for (const auto& offset : offsets) {
        Point3D vertex = {
            bottom_left_vertex.x + offset.x,
            bottom_left_vertex.y + offset.y,
            bottom_left_vertex.z + offset.z
        };
        vertices.push_back(vertex);
    }

    return vertices;
}
QVector<QVector<int>> cube_lines =
    {
        {1, 2},
        {5, 6},
        {2, 6},
        {1, 5},
        {2, 3},
        {3, 7},
        {7, 6},
        {3, 4},
        {4, 1},
        {4, 8},
        {7, 8},
        {5, 8}
};

QVector<QVector<int>> cube_faces =
    {
        {1, 2, 5},
        {2, 5, 6},
        {2, 3, 6},
        {3, 7, 6},
        {3, 4, 7},
        {4, 7, 8},
        {4, 1, 5},
        {4, 5, 8},
        {8, 5, 6},
        {8, 6, 7},
        {1, 2, 3},
        {1, 3, 4}
};
#endif // HEADER_H
