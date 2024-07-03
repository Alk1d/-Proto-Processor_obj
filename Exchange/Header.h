#pragma once

#include <QVector>

struct Point3D
{
  double x;
  double y;
  double z;
};

extern QVector<QVector<int>> cube_lines;

extern QVector<QVector<int>> cube_faces;
