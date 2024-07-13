#include <QTextStream>

#include "ObjReader.h"
#include "ObjWriter.h"
#include "Header.h"

int main( int argc, char* argv[] )
{
  QTextStream cin( stdin );
  QTextStream cout( stdout );
  int mode = 0;

  while ( mode != 3 )
  {
    cout << "Generate OBJ [1]" << Qt::endl;
    cout << "Read OBJ [2]" << Qt::endl;
    cout << "Exit [3]" << Qt::endl;
    mode = cin.readLine().toInt();

    switch ( mode )
    {
      case 1:
      {
        ObjWriter w( "file.obj" );
        w.SetModelName(); // user-input of the file and model name
        w.AddVertex( 0.0, 0.0, 0.0 );
        w.AddVertex( 10.0, 0.0, 0.0 );
        w.AddVertex( 5.0, 10.0, 0.0 );
        w.AddLine( 1, 2 );
        w.AddFace( 1, 2, 3 );
        break;
      }

      case 2:
      {
        cout << "Enter .obj file path:" << Qt::endl;
        QString objfilepath = cin.readLine();

        ObjReader r;

        if ( r.ReadFile( objfilepath ) == true )
        {
          cout << "Opened file:" << objfilepath << Qt::endl;
          int pointsCount = r.GetVertexCount();
          int framesCount = r.GetFrameLinesCount();
          int facesCount = r.GetFacesCount();

          cout << "Vertices: " << pointsCount << Qt::endl;

          for ( int i = 0; i < pointsCount; ++i )
          {
            Point3D point = r.GetVertexPoint( i );
            // Doing i+1 because counting starts from 0 in vector, but in .obj it starts with 1
            cout << "Vertex " << i + 1 << ": " << point.x << " " << point.y << " " << point.z << Qt::endl;
          }

          cout << "\nFrames: " << framesCount << Qt::endl;

          for ( int i = 0; i < framesCount; ++i )
          {
            QVector<int> frame = r.GetFrameLine( i );
            cout << "Frame " << i + 1 << ": ";

            for ( int j = 0; j < frame.size(); ++j )
              cout << frame[j] << " ";
          }

          cout << "\nFaces: " << facesCount << Qt::endl;

          for ( int i = 0; i < facesCount; ++i )
          {
            QVector<int> face = r.GetFace( i );
            cout << "Face " << i + 1 << ": ";

            for ( int j = 0; j < face.size(); ++j )
              cout << face[j] << " ";
          }
        }

        cout << Qt::endl;
        break;
      }

      case 3:
        break;

      default:
        cout << "Invalid choice!" << Qt::endl;
    } // switch
  } // while

  return 0;
}
