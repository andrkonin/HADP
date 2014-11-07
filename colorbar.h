#ifndef COLORBAR_H
#define COLORBAR_H

#include <QWidget>
#include <QPainter>
//#include "colors.h"

class COLORBAR: public QWidget
 {
     Q_OBJECT        // must include this if you use Qt signals/slots

 public:

     char mode;
     float minI;
     float maxI;
     float minD;
     float maxD;
     int fontheight;
     COLORBAR(QWidget *parent=0)
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

         fontheight=8;
         minD=0.0;
         maxD=0.0;
     }
     void draw(QPainter *painter)
     {
         int i;
         QFont font("Franklin Gothic Book", fontheight, QFont::Normal);
         painter->setFont(font);
         painter->setBrush(palette().foreground());

         if (minI<0.0) minI=0.0;
         if (maxI<0.0) maxI=0.0;
         int step=(height()-40)/16;
         int p;
         float pstep=(maxD-minD)/16.0;
         float t;
         float istep=(maxI-minI)/16.0;
         //printf("%f %f\n",minI,maxI);
         float i_;
         if (mode=='i')
         {
             painter->drawText(30,19,"Intensity:");
         }
         else if (mode=='d')
         {
             painter->drawText(30,19,"Distance:");
         }
         for (i=0;i<17;i++)
         {
             p=30+i*step+fontheight/2;
             painter->drawLine(35,p,37,p);
             t=(minD+(float)i*pstep)*1000.0;
             i_=(maxI-(float)i*istep);
             if (i%4==0)
             {
                 if (mode=='d')
                 painter->drawText(41,p+fontheight/2,
                          QString::number(t,'f',0)+" mm");
                 else if (mode=='i')
                 painter->drawText(41,p+fontheight/2,
                          QString::number(i_,'f',2));
             }
         }
         QLinearGradient linearGrad(QPointF(20, height()-30),
                      QPointF(10, 30));
         QColor color;
         if (mode=='i')
         {
             float c;
             float MI=8.0;
             if (minI/MI>1.0) c=1.0;
             else c=minI/MI;
             color.setRgbF(c,c,c);
             linearGrad.setColorAt(0, color);
             //c=(int)maxI;
             printf("maxI=%f\n",maxI);
             if (maxI/MI>1.0) c=1.0;
             else c=maxI/MI;
             color.setRgbF(c,c,c);
             linearGrad.setColorAt(1, color);
         }
         else if (mode=='d')
         {
            int d_min=7;
            int d_max=0;
            bool p_min=false;
            bool p_max=false;
            for (i=0;i<colcount-1;i++)
            {
                if (!p_min&&minD>=PDis[i]&&minD<=PDis[i+1])
                {
                    d_min=i;
                    p_min=true;
                }
                if (!p_max&&maxD>=PDis[i]&&maxD<=PDis[i+1])
                {
                    d_max=i;
                    p_max=true;
                }
            }
            if (!p_max) d_max=colcount-1;
            if (!p_min) d_min=colcount-1;

            //printf("minD=%f d_min=%d maxD=%f d_max=%d\n",minD,d_min,maxD,d_max);
            float d_step=1.0/((float)(d_max-d_min));

            color.setRgb(PCol[d_min][0],PCol[d_min][1],PCol[d_min][2],255);
            linearGrad.setColorAt(1.0,color);
            int n=1;
            for (int k_i=d_min+1;k_i<d_max;k_i++)
            {
                color.setRgb(PCol[k_i][0],PCol[k_i][1],PCol[k_i][2],255);
                linearGrad.setColorAt(1.0-d_step*n,color);
                n++;
            }
            color.setRgb(PCol[d_max][0],PCol[d_max][1],PCol[d_max][2],255);
            linearGrad.setColorAt(0.0,color);

/*      This section represent static colorbar

            float k;
            int m=0;
            float colorstep=1.0/(float)(colcount-1);
            for (k=0.0;k<=1.0;k+=colorstep)
            {

                color.setRgb(PCol[m][0],PCol[m][1],PCol[m][2],255);
                linearGrad.setColorAt(1.0-k,color);
                m++;
            }
   */
         }

         painter->setBrush(QBrush(linearGrad));
         painter->drawRect(10,30,20,height()-40);

         painter->drawLine(0,0,0,height());
         painter->drawLine(0,0,width(),0);
         painter->drawLine(width(),0,width(),height());
         painter->drawLine(0,height(),width(),height());
     }
 protected:
     void paintEvent(QPaintEvent *event)
     {
         QPainter painter(this);
         painter.setRenderHint(QPainter::Antialiasing,true);
         painter.setViewport(0,0,width(),height());
         painter.setWindow(0,0,width(),height());
         draw(&painter);
     }
 private:
     char colormode;
     int PCol[26][3];
     float PDis[26];
     int colcount;
 };
#endif // PAINT_H
