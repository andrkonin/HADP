#ifndef PMD_H
#define PMD_H

#include <QtOpenGL>
#include <TOF_Sensor.h>
#include <GL/glu.h>

#define SOURCE_PLUGIN "C:/Users/kentand1/Desktop/Hyperion/simpleopengl/simpleopengl/camboardnano"
#define SOURCE_PARAM ""
#define PROC_PLUGIN "C:/Users/kentand1/Desktop/Hyperion/simpleopengl/simpleopengl/camboardnanoproc"
#define PROC_PARAM ""

#define MAX_VALUE 1.0

class PMD : public QGLWidget
 {
     Q_OBJECT

 public:

    bool layer;
    char qpmode;
    bool stop;
    char mode;
    float minI;
    float maxI;
    float minD;
    float maxD;
    float lminI;
    float lmaxI;
    float lminD;
    float lmaxD;
    bool grid;
    float D_M;

bool invalid;

    struct stSensorConfig
    {
        unsigned short usSensorID;                      /**< ID of connected sensor */
        char scSensorIP[MAX_APP_CHAR];			/**< IP address of sensor */
        char scSensorSerial[MAX_APP_CHAR];		/**< MAC of sensor */
        PMDHandle HndSensor;				/**< sensor handle */
        unsigned short usResX;				/**< resolution x */
        unsigned short usResY;				/**< resolution y */
        unsigned short usApertureH;			/**< aperture size horizontal */
        unsigned short usApertureV;                     /**< aperture size vertical */
        unsigned short usSensorOnline;			/**< number of frames to capture */
    };
    struct stSensorConfig stCurrentSensor;

    PMD(QWidget *parent=0)
    {
//Red
         PCol[0][0]=255;
         PCol[0][1]=0;
         PCol[0][2]=0;
         PDis[0]=0.0;
//Yellow
         PCol[1][0]=255;
         PCol[1][1]=255;
         PCol[1][2]=0;
         PDis[1]=0.2;
//Green
         PCol[2][0]=0;
         PCol[2][1]=255;
         PCol[2][2]=0;
         PDis[2]=0.4;
//Cyan
         PCol[3][0]=0;
         PCol[3][1]=255;
         PCol[3][2]=255;
         PDis[3]=0.6;
//Blue
         PCol[4][0]=0;
         PCol[4][1]=0;
         PCol[4][2]=255;
         PDis[4]=0.8;
//DarkBlue
         PCol[5][0]=0;
         PCol[5][1]=0;
         PCol[5][2]=127;
         PDis[5]=1.0;

         colcount=6;
         PDisStep=0.2;
         PColStep=5;

         PColOrder[0][0]=1;
         PColOrder[0][1]=1;
         PColOrder[1][0]=0;
         PColOrder[1][1]=-1;
         PColOrder[2][0]=2;
         PColOrder[2][1]=1;
         PColOrder[3][0]=1;
         PColOrder[3][1]=-1;
         PColOrder[4][0]=2;
         PColOrder[4][1]=-1;

         minD=10000.0;
         minI=5000.0;
         maxD=0.0;
         maxI=0.0;

        setFormat(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer));
        rotationX=0.0;
        rotationY=0.0;
        rotationZ=0.0;
        faceColors[0]=Qt::red;
        faceColors[1]=Qt::green;
        faceColors[2]=Qt::blue;
        faceColors[3]=Qt::yellow;
        D_M=3.0;
        stop=false;

        scale=30;
        farValue=-10.0;
        middle=farValue;
        volume=1.0;

        layer=false;
        begin=0.0;
        end=0.0;
        time=50;
        qpmode='p';
        mode='d';
        minD=0.0;
        maxD=0.0;
        minI=0.0;
        maxI=0.0;

        stCurrentSensor.usSensorID = 0;
        strcpy(stCurrentSensor.scSensorIP, "192.168.0.69");
        stCurrentSensor.usResX = 165;
        stCurrentSensor.usResY = 120;
        stCurrentSensor.usApertureH = 30;
        stCurrentSensor.usApertureV = 40;
        stCurrentSensor.usSensorOnline	= 0;

invalid = true;
grid = true;

        // Open the sensor with the specified plugins and parameters
        connected=false;
        PMD::PMDConnect();

    }

    QWidget *createWidget(QWidget *parent)
    {
        return new PMD(parent);
    }

public slots:

    void changeValue(int value)
    {
        D_M=(float)value;
        printf("%f\n",D_M);
    }

    void changeView()
    {
        if (mode=='i')
            mode='d';
        else
            mode='i';
    }

    void showinvalid()
    {
        if (invalid)
            invalid=false;
        else
            invalid=true;
    }

    void showgrid()
    {
        if (grid)
            grid=false;
        else
            grid=true;
    }

    void backDefault()
    {
        scale=30;
        farValue=-10.0;
        volume=1.0;

        rotationX=0.0;
        rotationY=0.0;
        rotationZ=0.0;
        qpmode='p';
        mode='d';
        //if (stop)
        //{
        //   stop=false;
        //}
    }

    void PMDConnect()
    {
        if (!connected)
        {
            invalid = true;
            grid = true;
          int res;
          char err[128];
          maxAmp = 3000.0/2.0;
          m_xyz = 0;
          m_size = 0;
          res = pmdOpen (&m_handle, SOURCE_PLUGIN, SOURCE_PARAM, PROC_PLUGIN, PROC_PARAM);
          pmdSetIntegrationTime(m_handle,0,1000);
          //pmdGetFlags(m_handle, &flags, sizeof(flags));
          //pmdSetModulationFrequency(m_handle,0,10);
          // Check if the sensor was opened
          if (res != PMD_OK)
          {
             // Sensor wasn't opened correctly, output error message and exit
            pmdGetLastError (0, err, 128);
            QMessageBox::critical (this, "SimpleOpenGL", QString::fromAscii (err));
            exit (1);
          }
        connected=true;
        mode='d';
        qpmode='p';

            if (stop)
            {
                stop=false;
            }
            connected=true;

            int slResult;               /* keeps return values */
            char scLogTxt[64];		/* array for log */
            char scSerial[64];
            /* connect to sensor */
            /* open connection */
            printf ("--> Connecting SENSOR %s", stCurrentSensor.scSensorIP);
            slResult = pmdOpen (&stCurrentSensor.HndSensor, "./settings/o3.L32.pcp",
                     stCurrentSensor.scSensorIP , "./settings/o3.L32.pcp", "");
            if (slResult != PMD_OK)
            {
                sprintf (scLogTxt, "--> Could not connect to sensor Error: %i\n", slResult);
                //printf(scLogTxt);
                stCurrentSensor.usSensorOnline = 0;
            }
            else
            {
                slResult = pmdUpdate(stCurrentSensor.HndSensor);
                if (slResult != PMD_OK)
                {
                    sprintf (scLogTxt, "--> Could not update to sensor Error: %i\n", slResult);
                    //printf(scLogTxt);
                }

                /* GetSerialNumber */
                slResult = pmdSourceCommand (stCurrentSensor.HndSensor,
                                             scSerial, sizeof(scSerial),
                                             "GetSerialNumber");
                if (slResult != PMD_OK)
                {
                    sprintf (scLogTxt, "--> Could not send pmdSourceCommand GetSerialNumber ERROR:%i\n", slResult);
                   // printf(scLogTxt);
                }
                else
                {
                    strcpy(stCurrentSensor.scSensorSerial, scSerial);
                    sprintf (scLogTxt, "--> Sensor MAC: %s\n",
                                 stCurrentSensor.scSensorSerial);
                    //printf(scLogTxt);
                }

                stCurrentSensor.usSensorOnline = 1;
                sprintf (scLogTxt, "--> Connected to sensor %s\n",
                         stCurrentSensor.scSensorIP);
                //printf(scLogTxt);
            }
        }
    }

    void PMDDisconnect()
    {
        if (connected)
        {
            pmdClose (m_handle);
            connected=false;
            scale=30;
            farValue=-10.0;
            volume=1.0;
            rotationX=0.0;
            rotationY=0.0;
            rotationZ=0.0;
        }
    }

    void showLayer(QString sbegin,QString send)
    {
        int b,e;
        bool ok;
        if (!sbegin.isEmpty()&&!send.isEmpty())
        {
            b=sbegin.toInt(&ok,10);
            e=send.toInt(&ok,10);
            if (b>e)
            {
                int c=b;
                b=e;
                e=c;
            }
            layer=true;
            begin=(float)b/1000.0;
            end=(float)e/1000.0;
        }
        else
        {
            //printf("\Incorrect input range\n");
        }
    }

    void pmdauto()
    {
        if (layer) layer=false;
    }

    void pmdtopview()
    {
        rotationX=-90;
        rotationY=180;
        farValue=-12;
    }
    void pmdquadspoints()
    {
        if (qpmode=='q') qpmode='p';
        else qpmode='q';
    }

protected:
    void InitializeGL()
    {
        qglClearColor(Qt::black);
        glShadeModel(GL_FLAT);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glDepthMask(GL_TRUE);
       //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    }

    void resizeGL(int width,int height)
    {
        glViewport(0,0,width,height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        GLfloat x=GLfloat(width)/height;
        glFrustum(-x,x,-1.0,1.0,4.0,15.0);
        glMatrixMode(GL_MODELVIEW);

    }

    void paintGL()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        draw();
    }

    void mousePressEvent(QMouseEvent *event)
    {
        if (connected)
        {
            lastPos=event->pos();
        }
    }

    void mouseMoveEvent(QMouseEvent *event)
    {
        if (connected)
        {
            float rx;
            float ry;
            GLfloat dx=GLfloat(event->x() - lastPos.x())/width();
            GLfloat dy=GLfloat(event->y() - lastPos.y())/height();
            if (event->buttons()&Qt::RightButton)
            {
                rx=rotationX-180*dy;
                ry=rotationY-180*dx;
                if (rx>-90&&rx<90)
                    rotationX=rx;
                if (ry>90&&ry<270)
                    rotationY=ry;

                updateGL();
            }
            else if (event->buttons()&Qt::LeftButton)
            {
                rotationX-=180*dy;
                rotationZ+=180*dx;
                updateGL();
            }
            lastPos=event->pos();
        }
    }

    void mouseDoubleClickEvent(QMouseEvent *event)
    {
        if (connected) stop=!stop;
    }

    void wheelEvent(QWheelEvent *event)
    {

        if (connected)
        {
            if (event->delta()>0)
            {
                if (farValue<-4.0)
                farValue++;
            }
            else
                if (farValue>-20.0) farValue--;
            updateGL();
        }
    }

private:
    void draw()
    {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.0,0.0,farValue);
        glRotatef(rotationX,1.0,0.0,0.0);
        glRotatef(rotationY,0.0,1.0,0.0);
        glRotatef(rotationZ,0.0,0.0,1.0);
        // Tell the sensor to retrieve the next frame


        pmdUpdate (m_handle);

        // Retrieve the data description
        PMDDataDescription dd;
        pmdGetSourceDataDescription (m_handle, &dd);

        // Remember the number of pixels
        m_size = dd.std.numColumns * dd.std.numRows;

        // Retrieve the source data
        char* sourceData = new char[dd.size];
        pmdGetSourceData (m_handle, sourceData, dd.size);

        // Calculate the amplitudes from the source data
      //  float* tmpXYZ = new float [dd.std.numColumns * dd.std.numRows * 3];
      //  pmdCalc3DCoordinates (m_handle, tmpXYZ, dd.std.numColumns * dd.std.numRows * 3 * sizeof (float), dd, sourceData);
        //float* tmpXYZ = new float [dd.std.numColumns * dd.std.numRows * 3];
       // pmdCalc3DCoordinates (m_handle, tmpXYZ, dd.std.numColumns * dd.std.numRows * 3 * sizeof (float), dd, sourceData);

        if (!stop)
        {
            intense = new float [dd.img.numRows * dd.img.numColumns];
            pmdGetAmplitudes (m_handle, intense, dd.img.numColumns * dd.img.numRows * sizeof (float));

            dist = new float [dd.img.numRows * dd.img.numColumns];
            pmdGetDistances (m_handle, dist, dd.img.numColumns * dd.img.numRows * sizeof (float));

            pmdGetFlags(m_handle, flags, sizeof(flags));
        }
/*
        if (!m_xyz)
          {
            // If our XYZ is not created yet, create it
            m_xyz = new float [dd.std.numColumns * dd.std.numRows * 3];

          }
        if (!m_intense)
          {
            // If our XYZ is not created yet, create it
            m_intense = new float [dd.std.numColumns * dd.std.numRows * 3];

          }
*/
        // Copy the 3D data, so that we can use it in the paintGL method
        //memcpy (m_xyz, tmpXYZ, dd.std.numColumns * dd.std.numRows * 3 * sizeof (float));
        //memcpy (m_intense, intense, dd.std.numColumns * dd.std.numRows * sizeof (float));

        //delete [] tmpXYZ;
        //delete [] sourceData;


        float midX=(float)stCurrentSensor.usResX/(scale*2);
        float midY=(float)stCurrentSensor.usResY/(scale*2);

        if (!m_size)
          {
            // If we have no data yet then return silently
            return;
          }

       // float* currentPixel = &tmpXYZ[0];
        float* currentColor = &intense[0];
        float* currentDist = &dist[0];


        // We want to draw points


        if (connected)
        {

                //printf("OK\n");
                lminD=10000.0;
                lminI=5000.0;
                lmaxD=0.0;
                lmaxI=0.0;

                int i,j;                        /* counter values */
                int slResult,slFResult;		/* keeps return values */
                int slFrameSize;		/* size of a frame */
                int slFrameNumbers;		/* number of frames */
                int slCamCount = 0;		/* counter for sensors */

                //float *flMeanDistance;          /* pointer to array with single frame */

                char scLogTxt[64];		/* array for log */

                /* get amount of frames to capture and their size */
                slFrameNumbers = 1;
                slFrameSize = stCurrentSensor.usResX*stCurrentSensor.usResY;
               // printf("--> Framesize %i X %i\n", slFrameSize, slFrameNumbers);

                /* allocate memory for every frame colum */
                if (!stop)
                {
                    flDistances = (float *)malloc(slFrameSize * sizeof(float));
                    flIntensities = (float *)malloc(slFrameSize *sizeof(float));

                    if(flDistances == NULL||flIntensities == NULL)
                    {
                        sprintf(scLogTxt, "--> No memory for row  %d\n", slCamCount);
                        //printf(scLogTxt);
                    }

                    /* start capturing amount of frames 'slFrameNumbers' */
                    //slCamCount = 0;
                    slResult = pmdUpdate(stCurrentSensor.HndSensor);
                    slResult = pmdGetDistances(stCurrentSensor.HndSensor, flDistances,
                               (slFrameSize *sizeof(float)));
                    slFResult = pmdGetIntensities(stCurrentSensor.HndSensor, flIntensities,
                               (slFrameSize *sizeof(float)));
                }
                slCamCount = 0;



                int x=stCurrentSensor.usResX;
                int y=stCurrentSensor.usResY;
                int c=0;

                QColor color;
                glPushMatrix();

                //Drawing axes

                if (grid)
                {

                glColor3d(255,255,255);
                float xstep=(float)x/10.0;
                float ystep=(float)y/10.0;
                float zstep=maxD*D_M/10.0;
                glBegin(GL_LINES);

                for (i=0;i<=10;i++)
                {
                    //Back horizontal
                    glVertex3f((float)(i*xstep)/scale-midX,
                               midY,-MAX_VALUE*D_M+middle*D_M);
                    glVertex3f((float)(i*xstep)/scale-midX,
                               0.0-midY,-MAX_VALUE*D_M+middle*D_M);
                    //Back vertical
                    glVertex3f(midX,(i*ystep)/scale-midY,
                              -MAX_VALUE*D_M+middle*D_M);
                    glVertex3f(0.0-midX,(i*ystep)/scale-midY,
                              -MAX_VALUE*D_M+middle*D_M);
                    //Left horizontal

                    glVertex3f((float)(i*xstep)/scale-midX, -midY,
                               -MAX_VALUE*D_M+middle*D_M);
                    glVertex3f((float)(i*xstep)/scale-midX, -midY,
                               (float)10*zstep-middle*D_M);
                    //Left vertical

                    glVertex3f(midX,-midY,
                               (float)i*zstep-middle*D_M);
                    glVertex3f(0.0-midX,-midY,
                               (float)i*zstep-middle*D_M);

                    //Bottom horizontal
                    glVertex3f(0.0-midX,midY,
                               (float)(i*zstep)-middle*D_M);
                    glVertex3f(0.0-midX,0.0-midY,
                               (float)(i*zstep)-middle*D_M);
                    //Botton vertical
                    glVertex3f(0.0-midX,(i*ystep)/scale-midY ,
                               (float)10*zstep-middle*D_M);
                    glVertex3f(0.0-midX,(i*ystep)/scale-midY ,
                               0.0-middle*D_M);

                }
                glEnd();
                }


                //Drawing distance data

               /* QFont serifFont("Times", 8, QFont::Normal);
                color.setRgb(255,255,255);
                qglColor(color);
                int k=10;
                for (i=0;i<=10;i++,k--)
                {
                    renderText(-midX,-midY+0.3,
                      (float)i*zstep/1.5-middle*D_M,QString::number(maxD*100*k,'f',0),serifFont);
                }*/

                //Main color variables

                float mn,mc;
                int nn;

                //Drawing camera image

                for (i=0;i<stCurrentSensor.usResY;i++)
                {
                    for (j=0;j<stCurrentSensor.usResX;j++)
                    {
                        c=i*stCurrentSensor.usResX+j;

                        if (qpmode=='q')
                        {
                            if (mode=='i')
                            {

                                if (layer)
                                {
                                    if ((currentColor[i*x+j]>=begin&&currentColor[i*x+j]<=end)&&
                                        (currentColor[i*x+j+1]>=begin&&currentColor[i*x+j+1]<=end)&&
                                        (currentColor[(i+1)*x+j+1]>=begin&&currentColor[(i+1)*x+j+1]<=end)&&
                                        (currentColor[(i+1)*x+j]>=begin&&currentColor[(i+1)*x+j]<=end))
                                    {
                                        glBegin(GL_QUADS);
                                        glColor3f(currentColor[c]/maxAmp,currentColor[c]/maxAmp,currentColor[c]/maxAmp);
                                        glVertex3f((float)j/scale-(float)midX,(float)(y-i)/scale-(float)midY,
                                                   currentDist[i*x+j]-middle);
                                        glColor3f(currentColor[c+1]/maxAmp,currentColor[c+1]/maxAmp,currentColor[c+1]/maxAmp);
                                        glVertex3f((float)(j+1)/scale-(float)midX,(float)(y-i)/scale-(float)midY,
                                                   currentDist[i*x+j+1]-middle);
                                        glColor3f(currentColor[c+x+1]/maxAmp,currentColor[c+x+1]/maxAmp,currentColor[c+x+1]/maxAmp);
                                        glVertex3f((float)(j+1)/scale-(float)midX,(float)(y-i-1)/scale-(float)midY,
                                                   currentDist[(i+1)*x+j+1]-middle);
                                        glColor3f(currentColor[c+x]/maxAmp,currentColor[c+x]/8.0,currentColor[c+x]/maxAmp);
                                        glVertex3f((float)j/scale-(float)midX,(float)(y-i-1)/scale-(float)midY,
                                                   currentDist[(i+1)*x+j]-middle);
                                        glEnd();
                                    }
                                }
                                else if (!layer)
                                {
                                    glBegin(GL_QUADS);
                                    glColor3f(currentColor[c]/maxAmp,currentColor[c]/8.0,currentColor[c]/maxAmp);
                                    glVertex3f((float)j/scale-(float)midX,(float)(y-i)/scale-(float)midY,
                                               currentDist[i*x+j]-middle);
                                    glColor3f(currentColor[c+1]/maxAmp,currentColor[c+1]/8.0,currentColor[c+1]/maxAmp);
                                    glVertex3f((float)(j+1)/scale-(float)midX,(float)(y-i)/scale-(float)midY,
                                               currentDist[i*x+j+1]-middle);
                                    glColor3f(currentColor[c+x+1]/maxAmp,currentColor[c+x+1]/8.0,currentColor[c+x+1]/maxAmp);
                                    glVertex3f((float)(j+1)/scale-(float)midX,(float)(y-i-1)/scale-(float)midY,
                                               currentDist[(i+1)*x+j+1]-middle);
                                    glColor3f(currentColor[c+x]/maxAmp,currentColor[c+x]/8.0,currentColor[c+x]/maxAmp);
                                    glVertex3f((float)j/scale-(float)midX,(float)(y-i-1)/scale-(float)midY,
                                               currentDist[(i+1)*x+j]-middle);
                                    glEnd();
                                }
                            }
                            else if (mode=='d')
                            {
                                if (layer)
                                {
                                    if ((currentColor[i*x+j]>=begin&&currentColor[i*x+j]<=end)&&
                                        (currentColor[i*x+j+1]>=begin&&currentColor[i*x+j+1]<=end)&&
                                        (currentColor[(i+1)*x+j+1]>=begin&&currentColor[(i+1)*x+j+1]<=end)&&
                                        (currentColor[(i+1)*x+j]>=begin&&currentColor[(i+1)*x+j]<=end))
                                    {
                                        glBegin(GL_QUADS);
                                        nn=(int)(currentColor[c]/PDisStep);
                                        mn=currentDist[c]-PDis[nn];
                                        mc=255.0*(mn/(PDis[nn+1]-PDis[nn]))*(float)PColOrder[nn][1];
                                        if (PColOrder[nn][0]==0)
                                            color.setRgb(PCol[nn][0]+(int)mc,PCol[nn][1],PCol[nn][2]);
                                        else if (PColOrder[nn][0]==1)
                                            color.setRgb(PCol[nn][0],PCol[nn][1]+(int)mc,PCol[nn][2]);
                                        else
                                            color.setRgb(PCol[nn][0],PCol[nn][1],PCol[nn][2]+(int)mc);
                                        qglColor(color);
                                        glVertex3f((float)j/scale-(float)midX,(float)(y-i)/scale-(float)midY,
                                                   currentDist[i*x+j]-middle);

                                        nn=(int)(currentDist[i*x+j+1]/PDisStep);
                                        mn=currentDist[i*x+j+1]-PDis[nn];
                                        mc=255.0*(mn/(PDis[nn+1]-PDis[nn]))*(float)PColOrder[nn][1];
                                        if (PColOrder[nn][0]==0)
                                            color.setRgb(PCol[nn][0]+(int)mc,PCol[nn][1],PCol[nn][2]);
                                        else if (PColOrder[nn][0]==1)
                                            color.setRgb(PCol[nn][0],PCol[nn][1]+(int)mc,PCol[nn][2]);
                                        else
                                            color.setRgb(PCol[nn][0],PCol[nn][1],PCol[nn][2]+(int)mc);
                                        qglColor(color);
                                        glVertex3f((float)(j+1)/scale-(float)midX,(float)(y-i)/scale-(float)midY,
                                                   currentDist[i*x+j+1]-middle);

                                        nn=(int)(currentDist[(i+1)*x+j+1]/PDisStep);
                                        mn=currentDist[(i+1)*x+j+1]-PDis[nn];
                                        mc=255.0*(mn/(PDis[nn+1]-PDis[nn]))*(float)PColOrder[nn][1];
                                        if (PColOrder[nn][0]==0)
                                            color.setRgb(PCol[nn][0]+(int)mc,PCol[nn][1],PCol[nn][2]);
                                        else if (PColOrder[nn][0]==1)
                                            color.setRgb(PCol[nn][0],PCol[nn][1]+(int)mc,PCol[nn][2]);
                                        else
                                            color.setRgb(PCol[nn][0],PCol[nn][1],PCol[nn][2]+(int)mc);
                                        qglColor(color);
                                        glVertex3f((float)(j+1)/scale-(float)midX,(float)(y-i-1)/scale-(float)midY,
                                                   currentDist[(i+1)*x+j+1]-middle);

                                        nn=(int)(currentDist[(i+1)*x+j]/PDisStep);
                                        mn=currentDist[(i+1)*x+j]-PDis[nn];
                                        mc=255.0*(mn/(PDis[nn+1]-PDis[nn]))*(float)PColOrder[nn][1];
                                        if (PColOrder[nn][0]==0)
                                            color.setRgb(PCol[nn][0]+(int)mc,PCol[nn][1],PCol[nn][2]);
                                        else if (PColOrder[nn][0]==1)
                                            color.setRgb(PCol[nn][0],PCol[nn][1]+(int)mc,PCol[nn][2]);
                                        else
                                            color.setRgb(PCol[nn][0],PCol[nn][1],PCol[nn][2]+(int)mc);
                                        qglColor(color);
                                        glVertex3f((float)j/scale-(float)midX,(float)(y-i-1)/scale-(float)midY,
                                                   currentDist[(i+1)*x+j]-middle);
                                        glEnd();
                                    }
                                }
                                else if (!layer)
                                {
                                    glBegin(GL_QUADS);
                                    nn=(int)(currentDist[c]/PDisStep);
                                    mn=currentDist[c]-PDis[nn];
                                    mc=255.0*(mn/(PDis[nn+1]-PDis[nn]))*(float)PColOrder[nn][1];
                                    if (PColOrder[nn][0]==0)
                                        color.setRgb(PCol[nn][0]+(int)mc,PCol[nn][1],PCol[nn][2]);
                                    else if (PColOrder[nn][0]==1)
                                        color.setRgb(PCol[nn][0],PCol[nn][1]+(int)mc,PCol[nn][2]);
                                    else
                                        color.setRgb(PCol[nn][0],PCol[nn][1],PCol[nn][2]+(int)mc);
                                    qglColor(color);
                                    glVertex3f((float)j/scale-(float)midX,(float)(y-i)/scale-(float)midY,
                                               currentDist[i*x+j]-middle);

                                    nn=(int)(currentDist[i*x+j+1]/PDisStep);
                                    mn=currentDist[i*x+j+1]-PDis[nn];
                                    mc=255.0*(mn/(PDis[nn+1]-PDis[nn]))*(float)PColOrder[nn][1];
                                    if (PColOrder[nn][0]==0)
                                        color.setRgb(PCol[nn][0]+(int)mc,PCol[nn][1],PCol[nn][2]);
                                    else if (PColOrder[nn][0]==1)
                                        color.setRgb(PCol[nn][0],PCol[nn][1]+(int)mc,PCol[nn][2]);
                                    else
                                        color.setRgb(PCol[nn][0],PCol[nn][1],PCol[nn][2]+(int)mc);
                                    qglColor(color);
                                    glVertex3f((float)(j+1)/scale-(float)midX,(float)(y-i)/scale-(float)midY,
                                               currentDist[i*x+j+1]-middle);

                                    nn=(int)(currentDist[(i+1)*x+j+1]/PDisStep);
                                    mn=currentDist[(i+1)*x+j+1]-PDis[nn];
                                    mc=255.0*(mn/(PDis[nn+1]-PDis[nn]))*(float)PColOrder[nn][1];
                                    if (PColOrder[nn][0]==0)
                                        color.setRgb(PCol[nn][0]+(int)mc,PCol[nn][1],PCol[nn][2]);
                                    else if (PColOrder[nn][0]==1)
                                        color.setRgb(PCol[nn][0],PCol[nn][1]+(int)mc,PCol[nn][2]);
                                    else
                                        color.setRgb(PCol[nn][0],PCol[nn][1],PCol[nn][2]+(int)mc);
                                    qglColor(color);
                                    glVertex3f((float)(j+1)/scale-(float)midX,(float)(y-i-1)/scale-(float)midY,
                                               currentDist[(i+1)*x+j+1]-middle);

                                    nn=(int)(currentDist[(i+1)*x+j]/PDisStep);
                                    mn=currentDist[(i+1)*x+j]-PDis[nn];
                                    mc=255.0*(mn/(PDis[nn+1]-PDis[nn]))*(float)PColOrder[nn][1];
                                    if (PColOrder[nn][0]==0)
                                        color.setRgb(PCol[nn][0]+(int)mc,PCol[nn][1],PCol[nn][2]);
                                    else if (PColOrder[nn][0]==1)
                                        color.setRgb(PCol[nn][0],PCol[nn][1]+(int)mc,PCol[nn][2]);
                                    else
                                        color.setRgb(PCol[nn][0],PCol[nn][1],PCol[nn][2]+(int)mc);
                                    qglColor(color);
                                    glVertex3f((float)j/scale-(float)midX,(float)(y-i-1)/scale-(float)midY,
                                               currentDist[(i+1)*x+j]-middle);
                                    glEnd();

                                    nn=(int)(currentDist[c]/PDisStep);
                                    mn=currentDist[c]-PDis[nn];
                                    mc=255.0*(mn/(PDis[nn+1]-PDis[nn]))*(float)PColOrder[nn][1];
                                }
                            }
                        }
                        else
                        if (qpmode=='p')

                        {
                            glPointSize(4);
                            if (mode=='i')
                            {
                                if (layer)
                                {
                                    if (currentDist[c]>=begin&&currentDist[c]<=end)
                                    {
                                        glBegin(GL_POINTS);
                                        glColor3d(currentColor[c]/maxAmp,currentColor[c]/maxAmp,currentColor[c]/maxAmp);
                                        if ((invalid && !(flags[c] & PMD_FLAG_INVALID)) || !invalid)
                                           glVertex3f((float)j/scale-(float)midX,
                                                   (float)i/scale-(float)midY,
                                                           -currentDist[c]*D_M+middle*D_M);
                                        glEnd();
                                    }
                                }
                                else if (currentDist[c]<=MAX_VALUE&&currentDist[c]>0.0)
                                {

                                    glBegin(GL_POINTS);
                                    glColor3d(currentColor[c]/maxAmp,currentColor[c]/maxAmp,currentColor[c]/maxAmp);
                                    if ((invalid && !(flags[c] & PMD_FLAG_INVALID)) || !invalid)
                                        glVertex3f((float)j/scale-(float)midX,
                                               (float)i/scale-(float)midY,
                                                       -currentDist[c]*D_M+middle*D_M);
                                    glEnd();
                                }
                            }
                            else if (mode=='d')
                            {
                                if (layer)
                                {
                                    if (currentDist[c]>=begin&&currentDist[c]<=end)
                                    {
                                        nn=(int)(currentDist[c]/PDisStep);
                                        mn=currentDist[c]-PDis[nn];
                                        mc=255.0*(mn/(PDis[nn+1]-PDis[nn]))*(float)PColOrder[nn][1];
                                        if (PColOrder[nn][0]==0)
                                            color.setRgb(PCol[nn][0]+(int)mc,PCol[nn][1],PCol[nn][2]);
                                        else if (PColOrder[nn][0]==1)
                                            color.setRgb(PCol[nn][0],PCol[nn][1]+(int)mc,PCol[nn][2]);
                                        else
                                        color.setRgb(PCol[nn][0],PCol[nn][1],PCol[nn][2]+(int)mc);
                                        qglColor(color);
                                        glBegin(GL_POINTS);
                                        if ((invalid && !(flags[c] & PMD_FLAG_INVALID)) || !invalid)
                                            glVertex3f((float)j/scale-(float)midX,
                                                   (float)i/scale-(float)midY,
                                                           -currentDist[c]*D_M+middle*D_M);
                                        glEnd();
                                    }
                                }
                                else if (currentDist[c]<=MAX_VALUE&&currentDist[c]>0.0)
                                {

                                    nn=(int)(currentDist[c]/PDisStep);
                                    mn=currentDist[c]-PDis[nn];
                                    mc=255.0*(mn/(PDis[nn+1]-PDis[nn]))*(float)PColOrder[nn][1];

                                    if (PColOrder[nn][0]==0)
                                        color.setRgb(PCol[nn][0]+(int)mc,PCol[nn][1],PCol[nn][2]);
                                    else if (PColOrder[nn][0]==1)
                                        color.setRgb(PCol[nn][0],PCol[nn][1]+(int)mc,PCol[nn][2]);
                                    else
                                        color.setRgb(PCol[nn][0],PCol[nn][1],PCol[nn][2]+(int)mc);

                                    //color.setRgb(255,255,255);
                                    qglColor(color);
                                    glBegin(GL_POINTS);
                                    if ((invalid && !(flags[c] & PMD_FLAG_INVALID)) || !invalid)
                                        glVertex3f((float)j/scale-(float)midX,
                                               (float)i/scale-(float)midY,
                                                       -currentDist[c]*D_M+middle*D_M);
                                    glEnd();

                                }
                            }
                        }
                        if (currentColor[c]>lmaxI) lmaxI=currentColor[c];
                        if (currentColor[c]<lminI) lminI=currentColor[c];
                        if (currentDist[c]<=MAX_VALUE)
                        {
                            if (currentDist[c]>lmaxD) lmaxD=currentDist[c];
                            if (currentDist[c]<lminD) lminD=currentDist[c];
                        }
                    }
                }
                maxD=lmaxD;
                minD=lminD;
                maxI=lmaxI;
                minI=lminI;
                middle=(maxD-minD)/2.0;
                glPopMatrix();
           /*}
            else
            {
                glPushMatrix();
                qglColor(Qt::white);
                QString s="No signal";
                QFont serifFont("Times", 10, QFont::Bold);
                float midX=(float)stCurrentSensor.usResX/60;
                renderText(0.0,midX/4,0.0,s,serifFont);
                glPopMatrix();
            }*/
        }
        else
        {
            glPushMatrix();
            qglColor(Qt::white);
            QString s="Please, press \"Connect\"";
            QFont serifFont("Times", 10, QFont::Bold);
            float midX=(float)stCurrentSensor.usResX/30;
            renderText(0.0,0.0,0.0,s,serifFont);
            glPopMatrix();
        }
    }
    int faceAtPosition(const QPoint &pos)
    {
        const int MaxSize=512;
        GLuint buffer[MaxSize];
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT,viewport);
        glSelectBuffer(MaxSize,buffer);
        glRenderMode(GL_SELECT);
        glInitNames();
        glPushName(0);
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluPickMatrix(GLdouble(pos.x()),
                       GLdouble(viewport[3]-pos.y()),
                       5.0,5.0,viewport);
        GLfloat x=GLfloat(width())/height();
        glFrustum(-x,x,-1.0,1.0,4.0,15.0);
        draw();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        if (!glRenderMode(GL_RENDER))
             return -1;
        return buffer[3];
    }
    GLfloat rotationX;
    GLfloat rotationY;
    GLfloat rotationZ;
    int scale;
    float farValue;
    float volume;
    bool connected;
    float begin;
    float end;
    float middle;
    float *flDistances;
    float *flIntensities;
    QColor faceColors[4];
    QPoint lastPos;
    int time;
    int colcount;
    int PCol[26][3];
    float PDis[26];
    float PDisStep;
    int PColStep;
    int PColOrder[5][2];
    /** Sensor handle */
    PMDHandle m_handle;
    /** Timer to trigger the frame recording */
    QTimer m_timer;
    /** XYZ Buffer */
    float* m_xyz;
    float* m_intense;
    /** Number of pixels */
    unsigned m_size;
    float maxAmp;
    float* intense;
    float *dist;
    unsigned flags[19800];


};
#endif // PMD_H
