//
// Created by Erik Sevre on 5/14/18.
//

#ifndef AUDIOPROJECT_AUDIORECORDER_HPP
#define AUDIOPROJECT_AUDIORECORDER_HPP

#include <QtWidgets>

#include "AudioUI.hpp"

class AudioRecorder : public QWidget {
Q_OBJECT
public:
    AudioRecorder(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    AudioUI *ui;

};


#endif //AUDIOPROJECT_AUDIORECORDER_HPP