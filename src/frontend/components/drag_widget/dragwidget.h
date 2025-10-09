#include <QFrame>
#include <QWidget>
#include <qpoint.h>
#include <qtmetamacros.h>
#include <vector>

#include "../../components/programming_blocks/blockitem.h"

using namespace std;

class DragWidget : public QFrame
{
	Q_OBJECT
public:
    explicit DragWidget(QWidget *parent = nullptr);
    static QString puzzleMimeType() { return QStringLiteral("image/x-puzzle-piece"); }

private:
	QPoint m_pressPos;
	vector<BlockItem*> blocks;
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};

