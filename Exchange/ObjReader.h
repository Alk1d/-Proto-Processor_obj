#pragma once

#include <QVector>

struct Point3D;

class ObjReader
{
public:
  ObjReader();
  bool ReadFile( const QString& filepath );

  int GetVertexCount();
  Point3D GetVertexPoint( int point );

  int GetFrameLinesCount();
  QVector<int> GetFrameLine( int line );

  int GetFacesCount();
  QVector<int> GetFace( int face );

private:
  QString m_objFile;
  QString m_line;
  QVector<Point3D> m_vertices;
  QVector<QVector<int>> m_frameLines;
  QVector<QVector<int>> m_faces;
};
