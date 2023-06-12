#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QPainter>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void rect_intersection(QRect rect1,QRect rect2);
    void circ_intersection(QRect rect1,QPointF circlecentre,int radius);
private slots:
    virtual void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);

    void on_Square_toggled(bool checked);

    void on_Circle_toggled(bool checked);

    void on_Line_toggled(bool checked);

    void onChildItemSelected();

    void displayTree();

    void resetApplication();

    void on_Reset_clicked();



private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
