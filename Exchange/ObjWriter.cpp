#include "ObjWriter.h"
#include "Header.h"

#include <QTextStream>
#include <QFile>

ObjWriter::ObjWriter( const QString& filename )
  : m_fileExtension( ".obj" )
{
}

void ObjWriter::SetModelType( const QString& name )
{
  m_model = name;
}

int ObjWriter::SelectWritingMode()
{
  QTextStream cin( stdin );
  QTextStream cout( stdout );
  cout << "Select writing mode:" << Qt::endl;
  cout << "Generate vertices, frames and polygons [1]" << Qt::endl;
  cout << "Manual writing [2]" << Qt::endl;
  cout << "Return [3]" << Qt::endl;
  m_writingMode = cin.readLine().toInt();
  return m_writingMode;
}

void ObjWriter::GenerateCubeModel()
{
  QTextStream cin( stdin );
  QTextStream cout( stdout );

  cout << "Write a length of a cube edge:" << Qt::endl;
  double cubeLength = 0;
  cubeLength = cin.readLine().toDouble();
  cout << "Write a coordinates for bottom-left point:" << Qt::endl;

  cout << "x:" << Qt::endl;
  double cubeBtmleftPointX = 0;
  cubeBtmleftPointX = cin.readLine().toDouble();
  cout << "y:" << Qt::endl;
  double cubeBtmleftPointY = 0;
  cubeBtmleftPointY = cin.readLine().toDouble();
  cout << "z:" << Qt::endl;
  double cubeBtmleftPointZ = 0;
  cubeBtmleftPointZ = cin.readLine().toDouble();

  Point3D btmleftPoint = {cubeBtmleftPointX, cubeBtmleftPointY, cubeBtmleftPointZ};
  QVector<Point3D> cubeVertices = CalculateCubeVertices( btmleftPoint, cubeLength );

  QFile objFile( m_model + m_fileExtension );

  if ( objFile.open( QIODevice::WriteOnly ) )
  {
    QTextStream out( &objFile );
    out << "o " << m_model << "\n";

    // writing vertices, lines and polygons
    for ( int i = 0; i < cubeVertices.size(); ++i )
    {
      QString verticeX = QString::number( cubeVertices[i].x );
      QString verticeY = QString::number( cubeVertices[i].y );
      QString verticeZ = QString::number( cubeVertices[i].z );
      out << "v " + verticeX + " " + verticeY + " " + verticeZ + "\n";
    }

    for ( int i = 0; i < cube_lines.size(); ++i )
    {
      out << "l ";

      for ( int j = 0; j < cube_lines[i].size(); ++j )
        out << cube_lines[i][j] << " ";

      out << "\n";
    }

    for ( int i = 0; i < cube_faces.size(); ++i )
    {
      out << "f ";

      for ( int j = 0; j < cube_faces[i].size(); ++j )
        out << cube_faces[i][j] << " ";

      out << "\n";
    }

    objFile.close();
    cout << "OBJ file created" << Qt::endl;
  }
  else
    cout << "Error creating OBJ file!" << Qt::endl;
}

//repeated code!
void ObjWriter::AddVertex( double x, double y, double z )
{
  QTextStream cout( stdout );
  QFile objFile( m_model + m_fileExtension );

  if ( objFile.open( QIODevice::WriteOnly | QIODevice::Append ) )
  {
    QTextStream out( &objFile );
    QString verticeX = QString::number( x );
    QString verticeY = QString::number( y );
    QString verticeZ = QString::number( z );
    out << "v " + verticeX + " " + verticeY + " " + verticeZ + "\n";
    objFile.close();
    cout << "Vertex appended" << Qt::endl;
  }
  else
    cout << "Error creating or appending OBJ file!" << Qt::endl;
}

void ObjWriter::AddLine( int vertex1, int vertex2 )
{
  QTextStream cout( stdout );
  QFile objFile( m_model + m_fileExtension );

  if ( objFile.open( QIODevice::WriteOnly | QIODevice::Append ) )
  {
    QTextStream out( &objFile );
    QString vertexOneStr = QString::number( vertex1 );
    QString vertexTwoStr = QString::number( vertex2 );
    out << "l " + vertexOneStr + " " + vertexTwoStr + "\n";
    objFile.close();
    cout << "FrameLine appended" << Qt::endl;
  }
  else
    cout << "Error creating or appending OBJ file!" << Qt::endl;
}

void ObjWriter::AddFace( int vertex1, int vertex2, int vertex3 )
{
  QTextStream cout( stdout );
  QFile objFile( m_model + m_fileExtension );

  if ( objFile.open( QIODevice::WriteOnly | QIODevice::Append ) )
  {
    QTextStream out( &objFile );
    QString vertexOneStr = QString::number( vertex1 );
    QString vertexTwoStr = QString::number( vertex2 );
    QString vertexThreeStr = QString::number( vertex3 );
    out << "f " + vertexOneStr + " " + vertexTwoStr + " " + vertexThreeStr + "\n";
    objFile.close();
    cout << "Face appended" << Qt::endl;
  }
  else
    cout << "Error creating or appending OBJ file!" << Qt::endl;
}

QVector<Point3D> ObjWriter::CalculateCubeVertices( const Point3D& bottomLeftVertex, double sideLength )
{
  QVector<Point3D> vertices;
  // Offsets for each vertex relative to the bottom-left vertex
  QVector<Point3D> offsets =
  {
    {0, 0, 0},
    {sideLength, 0, 0},
    {sideLength, sideLength, 0},
    {0, sideLength, 0},
    {0, 0, sideLength},
    {sideLength, 0, sideLength},
    {sideLength, sideLength, sideLength},
    {0, sideLength, sideLength}
  };

  // Add the offsets to the bottom-left vertex coordinates
  for ( const auto& offset : offsets )
  {
    Point3D vertex =
    {
      bottomLeftVertex.x + offset.x,
      bottomLeftVertex.y + offset.y,
      bottomLeftVertex.z + offset.z
    };
    vertices.push_back( vertex );
  }

  return vertices;
}
