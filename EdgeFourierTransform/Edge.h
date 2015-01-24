#ifndef EDGE_H
#define EDGE_H

#include "Fourier.h"

#include <QColor>
#include <QObject>

class Edge : public QObject
{
    Q_OBJECT

private:

    QColor m_color;
    ComplexVector m_points;

public:

    Edge(const QColor& color = Qt::black);
    Edge(const Edge& e);
    ~Edge();

    QColor color() const { return m_color; }

    const ComplexVector& points() const { return m_points; }
    void setPoints(const ComplexVector& points);

    void clear();

    void print() const;

    Edge& operator=(const Edge& e);

signals:

    void pointsChanged(Edge* e);
};

#endif // EDGE_H
