#include <QStyledItemDelegate>
#include <QPainter>
#include <QApplication>
#include <QSize>

class ColorDelegate : public QStyledItemDelegate {
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    QSize sizeHint(const QStyleOptionViewItem& opt, const QModelIndex&) const override {
        return { qMax(48, opt.rect.width()), 22 };
    }

    void paint(QPainter* p, const QStyleOptionViewItem& option, const QModelIndex& index) const override {
        QStyleOptionViewItem opt = option;
        initStyleOption(&opt, index);

        QStyle* style = opt.widget ? opt.widget->style() : QApplication::style();
        style->drawPrimitive(QStyle::PE_PanelItemViewItem, &opt, p, opt.widget);

        const QVariant v = index.data(Qt::UserRole);
        const QColor color = v.canConvert<QColor>() ? v.value<QColor>() : QColor(Qt::transparent);

        QRect r = opt.rect.adjusted(6, 3, -6, -3);

        p->save();
        p->setRenderHint(QPainter::Antialiasing, true);

        p->setPen(Qt::NoPen);
        p->setBrush(color.isValid() ? color : opt.palette.window());
        p->drawRoundedRect(r, 4, 4);

        QPen pen(QColor(0,0,0,60));
        pen.setWidth(1);
        p->setPen(pen);
        p->setBrush(Qt::NoBrush);
        p->drawRoundedRect(r, 4, 4);

        p->restore();
    }
};
