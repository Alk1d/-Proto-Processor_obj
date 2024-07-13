#pragma once

#include <QString>

struct Point3D;

class ObjWriter
{
public:
  ObjWriter( const QString& filename );
  void SetModelName();

  void AddVertex( double x, double y, double z );
  void AddLine( int vertex1, int vertex2 );
  void AddFace( int vertex1, int vertex2, int vertex3 );

private:

  int m_writingMode;
  QString m_model;
  QString m_fileExtension;
};
