#include "mainwindow.h"
#include "components/drag_widget/dragwidget.h"
#include "programcanvas.h"
#include <components/widgets/runprogramwidget.h>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPainter>
#include <QPixmap>
#include <QStackedLayout>
#include <QVBoxLayout>
#include <qboxlayout.h>
#include <qgridlayout.h>
#include <qnamespace.h>
#include <qpushbutton.h>
#include <qsize.h>
#include <qsizepolicy.h>
#include <qstackedlayout.h>
#include <qwidget.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
      scene(new QGraphicsScene(this)) {
  ui->setupUi(this);
  ProgramCanvas *view = new ProgramCanvas(100, 100);

  if (!centralWidget())
    setCentralWidget(new QWidget(this));
  QWidget *mainWidget = centralWidget();

  auto *lyt = qobject_cast<QGridLayout *>(centralWidget()->layout());
  if (!lyt) {
    lyt = new QGridLayout(centralWidget());
    centralWidget()->setLayout(lyt);
  }
  lyt->setContentsMargins(0, 0, 0, 0);
  lyt->setSpacing(0);

  QWidget *progUIWidget = new QWidget(centralWidget());
  QVBoxLayout *progUILyt = new QVBoxLayout(progUIWidget);

  progUILyt->addWidget(view);

  auto *drag = new DragWidget(this);
  drag->setAcceptDrops(false);
  progUILyt->addWidget(drag);

  view->setRenderHint(QPainter::Antialiasing, true);
  view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
  view->setScene(scene);
  lyt->addWidget(progUIWidget, 0, 0);

  RunProgramWidget *runButton = new RunProgramWidget(centralWidget());
  QHBoxLayout *overlayLayout = new QHBoxLayout(runButton);
  runButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
  connect(runButton, &QPushButton::clicked, runButton,
          &RunProgramWidget::runProgram);
  connect(runButton, &RunProgramWidget::execute, view,
          &ProgramCanvas::runProgram);
  overlayLayout->setContentsMargins(0, 0, 10, 10);
  runButton->setMinimumSize(QSize(10, 10));
  overlayLayout->setAlignment(Qt::AlignTop | Qt::AlignRight);
  lyt->addWidget(runButton, 0, 0, 1, 1, Qt::AlignTop | Qt::AlignRight);
}

MainWindow::~MainWindow() { delete ui; }
