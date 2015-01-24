#include "Edge.h"

#include <QDebug>

Edge::Edge(const QColor& color)
    : QObject(),
      m_color(color)
{
}
Edge::Edge(const Edge& e)
    :QObject()
{
    *this = e;
}
Edge::~Edge()
{
}

Edge &Edge::operator=(const Edge &e)
{
    m_color = e.m_color;
    m_points = e.m_points;

    emit pointsChanged(this);

    return *this;
}

void Edge::setPoints(const ComplexVector &points)
{
    m_points = points;

    emit pointsChanged(this);
}

void Edge::clear()
{
    m_points.clear();

    emit pointsChanged(this);
}

void Edge::print() const
{
    for (int i = 0; i < (int)m_points.size(); ++i)
        qDebug() << QString("<%1,%2>").arg(m_points[i].real()).arg(m_points[i].imag());
}
