//
// Created by Erik Sevre on 5/14/18.
//

#include "AudioRecorder.hpp"

#include <iostream>

AudioRecorder::AudioRecorder(QWidget *parent) : QWidget(parent)
{
    ui = new AudioUI(this);
    this->setMinimumSize(ui->size());
}

void AudioRecorder::resizeEvent(QResizeEvent *event) {
    ui->resize(event->size());
}


