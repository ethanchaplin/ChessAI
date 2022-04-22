#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qgraphicsscene.h"

#include "qgraphicsview.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow: public QMainWindow {
    Q_OBJECT

    public:
        MainWindow(QWidget * parent = nullptr);
    ~MainWindow();
    void resizeEvent(QResizeEvent * event);
    void showEvent(QShowEvent * event);
    void updateUI(QGraphicsScene * scene);
    QGraphicsScene * getScene();
    void initUI();
    QString mainDir;
    private:
        Ui::MainWindow * ui;
    QGraphicsView * view;
    QGraphicsScene * scene;

};
#endif // MAINWINDOW_H
