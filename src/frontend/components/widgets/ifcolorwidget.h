#include <qitemselectionmodel.h>
#include <components/programming_blocks/ifcolorblock.h>
#include <qtmetamacros.h>
#include <QWidget>
#include <QComboBox>

class IfColorWidget : public QWidget{
	Q_OBJECT
public:
	explicit IfColorWidget(QWidget* parent = nullptr);
private:
	IfColorBlock* ifBlock;
	QComboBox* colorList;

};
