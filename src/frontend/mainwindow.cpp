#include "mainwindow.h"
#include "components/drag_widget/dragwidget.h"
#include "programcanvas.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QPixmap>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      scene(new QGraphicsScene(this)) {
  ui->setupUi(this);
  ProgramCanvas *view = new ProgramCanvas(100, 100);

  if (!centralWidget())
    setCentralWidget(new QWidget(this));

  auto *lyt = qobject_cast<QVBoxLayout *>(centralWidget()->layout());
  if (!lyt) {
    lyt = new QVBoxLayout;
    centralWidget()->setLayout(lyt);
  }

  // 2) Crear/agregar el QGraphicsView si no existe
  // if (!view) {
  //   view = new QGraphicsView(this);
  //   view->setObjectName("programCanvas");
  // }
  lyt->addWidget(view);

  // 1) Agregar primero el DragWidget
  auto *drag = new DragWidget(this);
  drag->setAcceptDrops(false);
  lyt->addWidget(drag);

  view->setRenderHint(QPainter::Antialiasing, true);
  view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
  // view->setDragMode(QGraphicsView::RubberBandDrag);
  view->setScene(scene);

  // QPixmap skin(":/blocks/start_program.png"); // tu PNG (transparente);
  // QPixmap scaledSkin = skin.scaledToHeight(80, Qt::SmoothTransformation);
  //
  // QPixmap moveForwardSkin(":/blocks/move_forward.png"); // tu PNG
  // (transparente); QPixmap scaledMoveForwardSkin =
  // moveForwardSkin.scaledToHeight(80, Qt::SmoothTransformation);
  //
  // QPixmap moveBackwardSkin(":/blocks/move_backward.png"); // tu PNG
  // (transparente); QPixmap scaledMoveBackwardSkin =
  // moveBackwardSkin.scaledToHeight(80, Qt::SmoothTransformation);

  // Bloques de ejemplo (puedes mezclar skins y colores)
  // auto* b1 = new BlockItem(scaledSkin, false, true); scene->addItem(b1);
  // b1->setPos(0, 0); auto* b2 = new BlockItem(scaledMoveForwardSkin, true,
  // true); scene->addItem(b2); b2->setPos(220, 0); auto* b3 = new
  // BlockItem(scaledMoveBackwardSkin, true, true); scene->addItem(b3);
  // b3->setPos(220, 140);

  // Si quieres dejar dos ya conectados al iniciar:
  // b1->attachBelow(b2);
}

MainWindow::~MainWindow() { delete ui; }
