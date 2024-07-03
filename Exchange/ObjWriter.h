#pragma once

#include <QString>

struct Point3D;

class ObjWriter
{
public:
  ObjWriter( const QString& filename );
  int SelectWritingMode();

  void SetModelType( const QString& name );
  void GenerateCubeModel();

  void AddVertex( double x, double y, double z );
  void AddLine( int vertex1, int vertex2 );
  void AddFace( int vertex1, int vertex2, int vertex3 );

private:
  QVector<Point3D> CalculateCubeVertices( const Point3D& bottomLeftVertex, double sideLength );

  int m_writingMode;
  QString m_model;
  QString m_fileExtension;
};
