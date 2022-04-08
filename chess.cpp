#include "chess.h"

#include "qgraphicsitem.h"

#include "qgraphicsview.h"

#include "ui_chess.h"


MainWindow::MainWindow(QWidget * parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui -> setupUi(this);
    scene = new QGraphicsScene();
    view = this -> findChild < QGraphicsView * > ("graphicsView");
}

MainWindow::~MainWindow() {
    delete ui;
}
void MainWindow::resizeEvent(QResizeEvent * event) {
    view -> fitInView(0, 0, 400, 400, Qt::KeepAspectRatio);

}

void MainWindow::showEvent(QShowEvent * event) {
    view -> fitInView(0, 0, 400, 400, Qt::KeepAspectRatio);
}

void MainWindow::updateUI(QGraphicsScene * scene) {
    this -> scene = scene;
    view -> setScene(this -> scene);

    view -> show();
}

void MainWindow::initUI() {

    QImage image("C:\\Users\\coold\\Documents\\ChessAI\\assets\board.png");
    image = image.scaled(400, 400);

    QGraphicsPixmapItem * item = new QGraphicsPixmapItem(QPixmap::fromImage(image));

    scene -> addItem(item);

    view -> setScene(scene);

    view -> show();

}
