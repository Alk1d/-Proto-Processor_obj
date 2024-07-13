#include "ObjWriter.h"

#include <QTextStream>
#include <QFile>

ObjWriter::ObjWriter( const QString& filename )
  : m_fileExtension( ".obj" )
{
}

void ObjWriter::SetModelName()
{
  QTextStream cin( stdin );
  QTextStream cout( stdout );
  cout << "Enter object name:" << Qt::endl;
  m_model = cin.readLine();
}

//repeated code!
void ObjWriter::AddVertex( double x, double y, double z )
{
  QTextStream cout( stdout );
  QFile objFile( m_model + m_fileExtension );

  if ( objFile.open( QIODevice::WriteOnly | QIODevice::Append ) )
  {
    QTextStream out( & objFile );
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
    QTextStream out( & objFile );
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
    QTextStream out( & objFile );
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
