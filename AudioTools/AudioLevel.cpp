//
// Created by Erik Sevre on 5/9/18.
//

#include <QtGui/QPainter>

#include "AudioLevel.hpp"

AudioLevel::AudioLevel(QWidget *parent)
        : QWidget(parent)
{
    setMinimumHeight(15);
    setMaximumHeight(50);
}

void AudioLevel::setLevel(qreal level) {
    if (m_level != level) {
        m_level = level;
        update();
    }
}

/// Draw a fill bar to represent audio level visually on screen
/// \param event
void AudioLevel::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    // draw level
    qreal widthLevel = m_level * width();
    painter.fillRect(0, 0, (int) widthLevel, height(), Qt::red);
    // clear the rest of the control
    painter.fillRect((int) widthLevel, 0, width(), height(), Qt::black);

}
