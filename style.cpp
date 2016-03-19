#include <QDebug>
#include <QPainter>
#include <QStyleOption>
#include "style.h"

Style::Style()
    : QProxyStyle()
{
}

Style::~Style()
{
}

void Style::drawPrimitive(PrimitiveElement pe, const QStyleOption *opt, QPainter *p,
                          const QWidget *w) const
{
    qDebug() << pe;

    switch (pe) {
    case PE_FrameFocusRect:
        p->setPen(Qt::blue);
        p->drawRect(opt->rect);
        break;
    default:
        QProxyStyle::drawPrimitive(pe, opt, p, w);
    }
}

void Style::drawControl(ControlElement element, const QStyleOption *opt,
                        QPainter *p, const QWidget *widget) const
{
    qDebug() << element;

    switch (element) {
    /*
    case CE_FocusFrame:
        p->fillRect(opt->rect, opt->palette.foreground());
        break;
    case CE_MenuItem:
        if (const QStyleOptionMenuItem *item = qstyleoption_cast<const QStyleOptionMenuItem *>(opt)) {
            p->drawText(item->rect, item->text);
        }
        break;
        */
    default:
        QProxyStyle::drawControl(element, opt, p, widget);
    }
}

QRect Style::subElementRect(SubElement sr, const QStyleOption *opt,
                            const QWidget *widget) const
{
    qDebug() << "subElementRect : " << sr;
    qDebug() << "-----------------------------------------------";

    QRect r;
    switch (sr) {
    case SE_PushButtonFocusRect:
        if (const QStyleOptionButton *btn = qstyleoption_cast<const QStyleOptionButton *>(opt)) {
            r.setRect(btn->rect.x(), btn->rect.y(), btn->rect.width() - 1, btn->rect.height() - 1);
            r = visualRect(opt->direction, opt->rect, r);
        }
        break;
    default:
        r = QProxyStyle::subElementRect(sr, opt, widget);
    }

    qDebug() << "r = " << r;
    qDebug() << "===============================================";

    return r;
}

void Style::drawComplexControl(ComplexControl cc, const QStyleOptionComplex *opt, QPainter *p,
                               const QWidget *w) const
{
    qDebug() << "drawComplexControl : " << cc;
    qDebug() << "===============================================";

    switch (cc) {
    default:
        QProxyStyle::drawComplexControl(cc, opt, p, w);
    }
}

QRect Style::subControlRect(ComplexControl cc, const QStyleOptionComplex *opt, SubControl sc,
                            const QWidget *w) const
{
    qDebug() << "subControlRect : " << cc;
    qDebug() << "------------------------------------------------";

    QRect r;
    switch (cc) {
    default:
        r = QProxyStyle::subControlRect(cc, opt, sc, w);
    }

    qDebug() << "r = " << r;
    qDebug() << "===============================================";

    return r;
}

int Style::pixelMetric(PixelMetric m, const QStyleOption *opt, const QWidget *widget) const
{
    qDebug() << "pixelMetric : " << m;
    qDebug() << "-----------------------------------------------";

    int ret;

    switch (m) {
    case PM_FocusFrameVMargin:
    case PM_FocusFrameHMargin:
    case PM_DefaultFrameWidth:
        ret = 0;
        break;
    default:
        ret = QProxyStyle::pixelMetric(m, opt, widget);
    }

    qDebug() << "ret = " << ret;
    qDebug() << "===============================================";

    return ret;
}
