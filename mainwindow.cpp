#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mainwindow.h"
#include<QDebug>
#include <QtCore/qmath.h>

const int array_size=50;
int vertexX[array_size];
int vertexY[array_size];
int index=0;
int CvertexX[array_size];
int CvertexY[array_size];
int Cindex=0;
int LvertexX[array_size];
int LvertexY[array_size];
int Lindex=0;
bool upd=false;
bool rect_select=false;
bool cir_select=false;
bool lin_select=false;

bool rect_intersec=false;

int value=0;
int value_s=0;
int value_c=0;
int value_l=0;

int value_arr[2];
int value_arr_s[2];
int value_arr_c[2];
int value_arr_l[2];


int r_inter_point_x[array_size];
int r_inter_point_y[array_size];

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     displayTree();

    ui->Square->setText("Rectangle");
    ui->Square->setCheckable(true);

    ui->Circle->setText("Circle");
    ui->Circle->setCheckable(true);

    ui->Line->setText("Line");
    ui->Line->setCheckable(true);


    connect(ui->treeWidget, &QTreeWidget::itemSelectionChanged, this, &MainWindow::onChildItemSelected);
    ui->treeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayTree()
{
    ui->treeWidget->setColumnCount(4);
    QStringList lables;
    lables<<"Shapes"<<"lable"<<"Start"<<"End";
    ui->treeWidget->setHeaderLabels(lables);

    QTreeWidgetItem *root = new QTreeWidgetItem(ui->treeWidget);
    root->setText(0,"Rectangle");
    ui->treeWidget->addTopLevelItem(root);

//    QTreeWidgetItem *child = new QTreeWidgetItem;
//    child->setText(0,"1");
//    root->addChild(child);

    QTreeWidgetItem *root2 = new QTreeWidgetItem(ui->treeWidget);
    root2->setText(0,"Circle");
    ui->treeWidget->addTopLevelItem(root2);

    QTreeWidgetItem *root3 = new QTreeWidgetItem(ui->treeWidget);
    root3->setText(0,"Line");
    ui->treeWidget->addTopLevelItem(root3);
}


void MainWindow::on_Square_toggled(bool checked)
{
    if(checked)
    {
        qDebug()<<"Square ON";
         ui->Square->setStyleSheet("background-color: yellow;");

    }
    else
    {
    qDebug()<<"Square OFF";
    ui->Square->setStyleSheet("");
    }
}

void MainWindow::on_Circle_toggled(bool checked)
{
    if(checked)
    {
        qDebug()<<"Circle ON";
        ui->Circle->setStyleSheet("background-color: yellow;");
    }
    else
    {
    qDebug()<<"Circle OFF";
    ui->Circle->setStyleSheet("");
    }
}


void MainWindow::on_Line_toggled(bool checked)
{
    if(checked)
    {
        qDebug()<<"Line ON";
         ui->Line->setStyleSheet("background-color: yellow;");
    }
    else
    {
    qDebug()<<"Line OFF";
    ui->Line->setStyleSheet("");
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);


    if(rect_intersec)
    {
        QPainter painter(this);
        for(int i=0;i<=3;i++)
        {
             painter.setPen(QPen(Qt::yellow, 2));
             painter.setBrush(Qt::yellow);
           painter.drawEllipse(r_inter_point_x[i]-5, r_inter_point_y[i]-5 , 10, 10);
        }
    }


    if(rect_select)
    {

         QPainter painter(this);
         for(int i=0;i<=value_s;i++)
         {
        int width =vertexX[value_arr_s[i]+1]-vertexX[value_arr_s[i]];
        int height =vertexY[value_arr_s[i]+1]-vertexY[value_arr_s[i]];
       // painter.setBrush(Qt::yellow);
        painter.setPen(QPen(Qt::red, 2));
        painter.drawRect(QRect(vertexX[value_arr_s[i]],vertexY[value_arr_s[i]], width, height));
         }
    }

    if(cir_select)
    {
         QPainter painter(this);
         for(int i=0;i<=value_c;i++)
         {
        int width =CvertexX[value_arr_c[i]+1]-CvertexX[value_arr_c[i]];
        int height =CvertexY[value_arr_c[i]+1]-CvertexY[value_arr_c[i]];
       // painter.setBrush(Qt::yellow);
        painter.setPen(QPen(Qt::red, 2));
        int radius = qSqrt(width * width + height * height);
         painter.drawEllipse(QPointF(CvertexX[value_arr_c[i]],CvertexY[value_arr_c[i]]), radius, radius);
         }
    }

    if(lin_select)
    {
        for(int i=0;i<=value_l;i++)
        {
         QPainter painter(this);
       // painter.setBrush(Qt::yellow);
        painter.setPen(QPen(Qt::red, 2));
        painter.drawLine(LvertexX[value_arr_l[i]],LvertexY[value_arr_l[i]],LvertexX[value_arr_l[i]+1],LvertexY[value_arr_l[i]+1]);
        }
    }


    if(index>=1)
    {
        QPainter painter(this);
        for (int i = 0; i < index; i += 2)
            {
                int x = vertexX[i];
                int y = vertexY[i];
                int width = vertexX[i + 1] - x;
                int height = vertexY[i + 1] - y;
                qDebug() <<i;
                painter.drawRect(QRect(x, y, width, height));


            }

    }
    if(Cindex>=1)
    {
        QPainter painter(this);
        for (int i = 0; i < Cindex; i += 2)
            {
                int x = CvertexX[i];
                int y = CvertexY[i];
                int width = CvertexX[i + 1] - x;
                int height = CvertexY[i + 1] - y;
                qDebug() <<i;
                int radius = qSqrt(width * width + height * height);
                        int centerX = x ;
                        int centerY = y ;
                        painter.drawEllipse(QPointF(centerX, centerY), radius, radius);

            }
    }
    if(Lindex>=1)
    {
        QPainter painter(this);
        for (int i = 0; i < Lindex; i += 2)
            {
                int x1 = LvertexX[i];
                int y1 = LvertexY[i];
                int x2 = LvertexX[i + 1];
                int y2 = LvertexY[i + 1];
                qDebug() <<i;
                painter.drawLine(x1,y1,x2,y2);
            }
    }

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint mousePos = event->pos();
        QRect treeWidgetRect = ui->treeWidget->geometry();
        if (!treeWidgetRect.contains(mousePos))
        {
            // Deselect the selected items in the QTreeWidget
            ui->treeWidget->clearSelection();
            rect_select=false;
            cir_select=false;
            lin_select=false;
            rect_intersec=false;

        }


    if(ui->Square->isChecked())
    {
    int x = event->pos().x();
    int y = event->pos().y();
    vertexX[index]=x;
    vertexY[index]=y;
    index++;
     qDebug() << "Square is checked"<<x<<" "<<y<<" "<<index ;
     if (index >= 2 && index%2==0)
     {
         upd=true;
         QTreeWidgetItem *root = ui->treeWidget->topLevelItem(0); // Get the root item
                 QTreeWidgetItem *child = new QTreeWidgetItem;
                 QString text = QString("(%1, %2)").arg(vertexX[index-2]).arg(vertexY[index-2]);
                 QString text2 = QString("(%1, %2)").arg(vertexX[index-1]).arg(vertexY[index-1]);
                 QString text3 = QString("%1").arg(index-2);
                 child->setText(0, "Rectangle");
                 child->setText(1, text3);
                 child->setText(2, text);
                 child->setText(3, text2);
                 root->addChild(child);
     }
     else
     {
     upd=false;
     }
    }
    if(ui->Circle->isChecked())
    {
        int x = event->pos().x();
        int y = event->pos().y();
        CvertexX[Cindex]=x;
        CvertexY[Cindex]=y;
        Cindex++;
         qDebug() << "Circle is checked"<<x<<" "<<y<<" "<<Cindex ;
         if (Cindex >= 2 && Cindex%2==0)
         {
             upd=true;
             QTreeWidgetItem *root2 = ui->treeWidget->topLevelItem(1); // Get the root item
                     QTreeWidgetItem *child = new QTreeWidgetItem;
                     QString text = QString("(%1, %2)").arg(CvertexX[Cindex-2]).arg(CvertexY[Cindex-2]);
                     QString text2 = QString("(%1, %2)").arg(CvertexX[Cindex-1]).arg(CvertexY[Cindex-1]);
                     QString text3 = QString("%1").arg(Cindex-2);
                     child->setText(0, "Circle");
                     child->setText(1, text3);
                     child->setText(2, text);
                     child->setText(3, text2);
                     root2->addChild(child);
         }
         else
         {
         upd=false;
         }

    }
    if(ui->Line->isChecked())
    {
        int x = event->pos().x();
        int y = event->pos().y();
        LvertexX[Lindex]=x;
        LvertexY[Lindex]=y;
        Lindex++;
         qDebug() << "Circle is checked"<<x<<" "<<y<<" "<<Lindex ;
         if (Lindex >= 2 && Lindex%2==0)
         {
             upd=true;
             QTreeWidgetItem *root3 = ui->treeWidget->topLevelItem(2); // Get the root item
                     QTreeWidgetItem *child = new QTreeWidgetItem;
                     QString text = QString("(%1, %2)").arg(LvertexX[Lindex-2]).arg(LvertexY[Lindex-2]);
                     QString text2 = QString("(%1, %2)").arg(LvertexX[Lindex-1]).arg(LvertexY[Lindex-1]);
                     QString text3 = QString("%1").arg(Lindex-2);
                     child->setText(0, "Line");
                     child->setText(1, text3);
                     child->setText(2, text);
                     child->setText(3, text2);
                     root3->addChild(child);
         }
         else
         {
         upd=false;
         }

    }

    if (upd)
            {
                update(); // Trigger a repaint to draw the rectangle
            }

 QMainWindow::mousePressEvent(event);
}

void MainWindow::onChildItemSelected()
{
    int i=0;
    int r_i=0;
    int c_i=0;
    int l_i=0;

    QList<QTreeWidgetItem*> selectedItems = ui->treeWidget->selectedItems();
        foreach (QTreeWidgetItem* selectedItem, selectedItems)
        {

            QString text = selectedItem->text(1);
            QString text2 = selectedItem->text(0);
           // value = i;
           // value_arr[i]=text.toInt();

           // qDebug() << "Selected child item: " << value;
           // qDebug() << "Selected child item: " << value_arr[i]<<sizeof (value_arr);


            if (text2 == "Rectangle")
            {
                rect_select = true;
                value_s=r_i;
                value_arr_s[r_i]=text.toInt();
                r_i++;
            }
            if (text2 == "Circle")
            {
                cir_select = true;
                value_c=c_i;
                value_arr_c[c_i]=text.toInt();
                c_i++;
            }
            if (text2 == "Line")
            {
                lin_select = true;
                value_l=l_i;
                value_arr_l[l_i]=text.toInt();
                l_i++;
            }

            if(i>0)
            {

                if(rect_select==true&&cir_select==false&&lin_select==false)
            {

               int width1 =vertexX[value_arr_s[0]+1]-vertexX[value_arr_s[0]];
               int height1 =vertexY[value_arr_s[0]+1]-vertexY[value_arr_s[0]];
               QRect rect1(vertexX[value_arr_s[0]],vertexY[value_arr_s[0]], width1, height1);

               int width2 =vertexX[value_arr_s[1]+1]-vertexX[value_arr_s[1]];
               int height2 =vertexY[value_arr_s[1]+1]-vertexY[value_arr_s[1]];
               QRect rect2(vertexX[value_arr_s[1]],vertexY[value_arr_s[1]], width2, height2);
                rect_intersection(rect1,rect2);
               // Check if the rectangles intersect

            }

                if(rect_select==true&&cir_select==true&&lin_select==false)
                {
                    int width1 =vertexX[value_arr_s[0]+1]-vertexX[value_arr_s[0]];
                    int height1 =vertexY[value_arr_s[0]+1]-vertexY[value_arr_s[0]];
                    QRect rect1(vertexX[value_arr_s[0]],vertexY[value_arr_s[0]], width1, height1);


                    QPointF circlecentre (CvertexX[value_arr_s[0]], CvertexY[value_arr_s[0]]);
                    int width =CvertexX[value_arr_c[i]+1]-CvertexX[value_arr_c[i]];
                    int height =CvertexY[value_arr_c[i]+1]-CvertexY[value_arr_c[i]];
                    int radius = qSqrt(width * width + height * height);

                    circ_intersection( rect1,circlecentre,radius);

                }



            }


            if(i>=2)
            {
                ui->treeWidget->clearSelection();
                rect_select=false;
                cir_select=false;
                lin_select=false;
                rect_intersec=false;
                update();
                break;
            }
             i++;
             update();
        }



}

void MainWindow::resetApplication()
{
    // Reset all variables and data structures to their initial state

    index=0;
    Cindex=0;
    Lindex=0;
    upd=false;
    rect_select=false;
    cir_select=false;
    lin_select=false;
    rect_intersec=false;

    value=0;
    for (int i = 0; i < array_size; ++i) {
        vertexX[i] = 0;
        vertexY[i] = 0;
        CvertexX[i] = 0;
        CvertexY[i] = 0;
        LvertexX[i] = 0;
        LvertexY[i] = 0;
        r_inter_point_x[i]=0;
        r_inter_point_y[i]=0;
    }


    QTreeWidgetItem *root = ui->treeWidget->topLevelItem(0);
    QList<QTreeWidgetItem*> childItems = root->takeChildren();
    foreach (QTreeWidgetItem* child, childItems)
    {
        delete child;
    }

    QTreeWidgetItem *root1 = ui->treeWidget->topLevelItem(1);
    QList<QTreeWidgetItem*> childItems1 = root1->takeChildren();
    foreach (QTreeWidgetItem* child, childItems1)
    {
        delete child;
    }

    QTreeWidgetItem *root2 = ui->treeWidget->topLevelItem(2);
    QList<QTreeWidgetItem*> childItems2 = root2->takeChildren();
    foreach (QTreeWidgetItem* child, childItems2)
    {
        delete child;
    }


    ui->Square->setChecked(false);
    ui->Square->setStyleSheet("");
    ui->Circle->setChecked(false);
    ui->Circle->setStyleSheet("");
    ui->Line->setChecked(false);
    ui->Line->setStyleSheet("");

    update();

}


void MainWindow::on_Reset_clicked()
{
    resetApplication();
}


void MainWindow::rect_intersection(QRect rect1,QRect rect2)
{
    if (rect1.intersects(rect2))
    {

        QRect intersectionRect = rect1.intersected(rect2);



        int intersectionX = intersectionRect.x();
        int intersectionY = intersectionRect.y();
        int intersectionWidth = intersectionRect.width();
        int intersectionHeight = intersectionRect.height();


         QVector<QPoint> intersectingPoints;



        if (rect2.contains(rect1))
        {
            qDebug() <<"Does not intersect";
        }

        else if (rect1.contains(rect2))
        {
           qDebug() <<"Does not intersect";
        }

        else
        {
                    intersectingPoints.append(QPoint(intersectionX, intersectionY));

                    // Top-right corner of intersection rectangle
                    intersectingPoints.append(QPoint(intersectionX + intersectionWidth, intersectionY));

                    // Bottom-right corner of intersection rectangle
                    intersectingPoints.append(QPoint(intersectionX + intersectionWidth, intersectionY + intersectionHeight));

                    // Bottom-left corner of intersection rectangle
                    intersectingPoints.append(QPoint(intersectionX, intersectionY + intersectionHeight));




        }

        int j=0;
        for (const QPoint& point : intersectingPoints)
        {
            int x = point.x();
            int y = point.y();
            r_inter_point_x[j]=x;
            r_inter_point_y[j]=y;
            qDebug()<<"Ïntersecting Points are :"<<x<<" "<<y;
            j++;
            rect_intersec=true;
        }
        j=0;
        update();
    }
    else
    {
        qDebug() <<"Does not intersect";
    }
}

void MainWindow::circ_intersection(QRect rectangle, QPointF circleCenter, int circleRadius)
{
    QVector<QPoint> intersectionPoints;

    QLineF rectEdges[] = {
        QLineF(rectangle.topLeft(), rectangle.topRight()),      // Top edge
        QLineF(rectangle.topRight(), rectangle.bottomRight()),  // Right edge
        QLineF(rectangle.bottomRight(), rectangle.bottomLeft()),// Bottom edge
        QLineF(rectangle.bottomLeft(), rectangle.topLeft())     // Left edge
    };

    for (const QLineF& edge : rectEdges) {
        QLineF::IntersectType intersectType;
        QPointF intersectionPoint;

        // Check for intersection between the edge and the circle
        intersectType = edge.intersect(QLineF(circleCenter, edge.p1()), &intersectionPoint);

        if (intersectType == QLineF::BoundedIntersection) {
            intersectionPoints.append(intersectionPoint.toPoint());
        }

        intersectType = edge.intersect(QLineF(circleCenter, edge.p2()), &intersectionPoint);

        if (intersectType == QLineF::BoundedIntersection) {
            intersectionPoints.append(intersectionPoint.toPoint());
        }
    }


    // Print the intersection points
    for (const QPoint& point : intersectionPoints) {
        qDebug() << "Intersection Point: (" << point.x() << ", " << point.y() << ")";
    }
}

