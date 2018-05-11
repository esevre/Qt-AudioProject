//
// Created by Erik Sevre on 5/9/18.
//

#ifndef AUDIOPROJECT_AUDIOLEVEL_HPP
#define AUDIOPROJECT_AUDIOLEVEL_HPP


#include <QWidget>

// An audio level is the
class AudioLevel : public QWidget {
Q_OBJECT
public:
    explicit AudioLevel(QWidget *parent = nullptr);
    // using [0; 1.0] range
    void setLevel(qreal level);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    qreal m_level = 0.0;
};


#endif //AUDIOPROJECT_AUDIOLEVEL_HPP