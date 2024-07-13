#include "ObjReader.h"
#include "Header.h"

#include <QFile>
#include <QTextStream>

ObjReader::ObjReader()
{
}

bool ObjReader::ReadFile( const QString& filepath )
{
  QTextStream cout( stdout );
  QFile file( filepath );

  if ( !file.open( QIODevice::ReadOnly ) )
  {
    cout << "Error: Could not open file:" << filepath << Qt::endl;
    return false;
  }

  QTextStream in( &file );

  while ( !in.atEnd() )
  {
    m_line = in.readLine();
    QStringList parts = m_line.split( " " );

    if ( parts.first() == "v" )
    {
      Point3D vertex;
      vertex.x = parts[1].toDouble();
      vertex.y = parts[2].toDouble();
      vertex.z = parts[3].toDouble();
      m_vertices.push_back( vertex );
    }
    else if ( parts.first() == "l" )
    {
      QList<int> frameLineList;
      frameLineList << parts[1].toInt();
      frameLineList << parts[2].toInt();
      m_frameLines.push_back( frameLineList );
    }
    else if ( parts.first() == "f" )
    {
      QList<int> faceTriangleList;
      faceTriangleList << parts[1].toInt();
      faceTriangleList << parts[2].toInt();
      faceTriangleList << parts[3].toInt();
      m_faces.push_back( faceTriangleList );
    }
  }

  m_objFile = in.readAll();
  file.close();
  return true;
}
int ObjReader::GetVertexCount()
{
  return m_vertices.size();
}

Point3D ObjReader::GetVertexPoint( int point )
{
  return m_vertices.value( point );
}

int ObjReader::GetFrameLinesCount()
{
  return m_frameLines.size();
}

QVector<int> ObjReader::GetFrameLine( int line )
{
  return m_frameLines.value( line );
}

int ObjReader::GetFacesCount()
{
  return m_faces.size();
}

QVector<int> ObjReader::GetFace( int face )
{
  return m_faces.value( face );
}
