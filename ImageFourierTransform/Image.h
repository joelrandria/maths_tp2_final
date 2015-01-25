#ifndef IMAGE_H
#define IMAGE_H

#include <QPixmap>
#include <QObject>

class Image : public QObject
{
    Q_OBJECT

private:

    QPixmap m_pixmap;
    QPixmap m_pow2SizedPixmap;

public:

    Image();
    Image(const Image& image);
    ~Image();

    const QPixmap& pixmap() const { return m_pixmap; }
    void setPixmap(const QString& filename);

    const QPixmap& pow2SizedPixmap() const { return m_pow2SizedPixmap; }

    Image& operator=(const Image& image);

signals:

    void changed(Image*);
};

#endif // IMAGE_H
