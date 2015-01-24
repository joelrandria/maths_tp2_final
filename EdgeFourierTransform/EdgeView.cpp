#include "EdgeView.h"

#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <QString>
#include <QElapsedTimer>
#include <QDebug>

#include <complex>

EdgeView::EdgeView(QWidget *parent) :
    QGraphicsView(parent)
{
}
EdgeView::~EdgeView()
{
}

void EdgeView::paintEvent(QPaintEvent* event)
{
    uint i;

    QGraphicsView::paintEvent(event);

    QPainter painter(viewport());

    for (i = 0; i < m_edges.size(); ++i)
        drawEdge(painter, m_edges[i], 2);
}
void EdgeView::drawEdge(QPainter& painter, const Edge* edge, qreal width)
{
    int pointCount;
    ComplexVector points;

    points = edge->points();
    pointCount = points.size();

    QPen pen(edge->color(), width);

    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing);

    for (int i = 0; i < pointCount; ++i)
            painter.drawPoint(points[i].real(), points[i].imag());
}

void EdgeView::mouseReleaseEvent(QMouseEvent *event)
{
    emit mouseClicked(event->pos());
}

void EdgeView::addEdge(Edge* edge)
{
    m_edges.push_back(edge);

    connect(edge, SIGNAL(pointsChanged(Edge*)), this, SLOT(onEdgePointsChanged(Edge*)));
}

void EdgeView::onEdgePointsChanged(Edge*)
{
    viewport()->update();
}
