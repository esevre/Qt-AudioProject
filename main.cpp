#include <iostream>

#include <QtWidgets/QApplication>

#include "AudioTools/AudioRecorder.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    AudioRecorder recorder;

    recorder.show();


    return QApplication::exec();
}