#ifndef EDGE_H
#define EDGE_H

#include <QList>
#include <QPoint>
#include <QDebug>

#include <complex>
#include <vector>

class Edge
{
    friend class EdgeFT;

private:

    int m_closureValueCount;
    std::vector<std::complex<double> > m_values;

public:

    Edge();

    void print() const;

    void addValue(std::complex<double> value);

    const std::vector<std::complex<double> >& constValues() const { return m_values; }

    static void getEdgePoints(const QPoint &p1, const QPoint &p2, QList<QPoint> &points);

private:

    void deleteClosureValues();
    void close();

};

#endif // EDGE_H
