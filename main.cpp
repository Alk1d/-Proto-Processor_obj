#include <QCoreApplication>
#include <QDebug>
// #include <QTextStream>
// #include <QProcess>
// #include <QFile>
// #include <QVector>
#include "objreader.h"
#include "objwriter.h"

int main(int argc, char *argv[])
{
    QTextStream cin(stdin);
    int mode = 0;

    while( mode != 3)
    {
        qDebug() << "Generate OBJ [1]";
        qDebug() << "Read OBJ [2]";
        qDebug() << "Exit [3]";
        mode = cin.readLine().toInt();
        switch (mode)
        {
        case 1:
        {
            ObjWriter w("file.obj");
            w.setModelType("Cube");
            int writingMode = w.selectWritingMode();
            switch (writingMode) // select auto or manual writing or return
            {
            case 1: // auto generate
            {
                w.generateCubeModel();
                break;
            }
            case 2: // manual writing
            {
                w.AddVertex( 0.0, 0.0, 0.0 );
                w.AddVertex( 10.0, 0.0, 0.0 );
                w.AddVertex( 5.0, 10.0, 0.0 );
                w.AddLine( 1, 2 );
                w.AddFace( 1, 2, 3 );
                break;
            }
            case 3: // return
            {
                break;
            }
            default:
                qDebug() << "Invalid choice!";
            }
            break;
        }
        case 2:
        {
            qDebug() << "Enter .obj file path:";
            QString objfilepath = cin.readLine();

            ObjReader r;
            if (r.readFile(objfilepath) == true)
            {
                qDebug() << "Opened file:" << objfilepath;
                int pointsCount = r.getVertexCount();
                int framesCount = r.getFrameLinesCount();
                int facesCount = r.getFacesCount();

                qDebug() << "Vertices:" << pointsCount;
                for (int i = 0; i < pointsCount; ++i)
                {
                    Point3D point = r.getVertexPoint(i);
                    // Doing i+1 because counting starts from 0 in vector, but in .obj it starts with 1
                    qDebug() << "Vertex" << i+1 << ":" << point.x << point.y << point.z;
                }

                qDebug () << "\n3Frames:" << framesCount;
                for (int i = 0; i < framesCount; ++i)
                {
                    QVector<int> frame = r.getFrameLine(i);
                    QDebug dbg(QtDebugMsg);
                    dbg.nospace();
                    dbg << "Frame " << i+1 << ": ";
                    for (int j = 0; j < frame.size(); ++j)
                        dbg << frame[j] << " ";
                }

                qDebug () << "\nFaces:" << facesCount;
                for (int i = 0; i < facesCount; ++i)
                {
                    QVector<int> face = r.getFace(i);
                    QDebug dbg(QtDebugMsg);
                    dbg.nospace();
                    dbg << "Face " << i+1 << ": ";
                    for (int j = 0; j < face.size(); ++j)
                        dbg << face[j] << " ";
                }
            }
            break;
        }
        case 3:
            break;
        default:
            qDebug() << "Invalid choice!";
        }
    }
}


