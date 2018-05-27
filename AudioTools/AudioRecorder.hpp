//
// Created by Erik Sevre on 5/14/18.
//

#ifndef AUDIOPROJECT_AUDIORECORDER_HPP
#define AUDIOPROJECT_AUDIORECORDER_HPP

#include <QtWidgets>
#include <QAudioProbe>
#include <QAudioRecorder>

#include <QMainWindow>
#include <QMediaRecorder>
#include <QUrl>


#include <vector>

#include "AudioUI.hpp"
#include "AudioLevel.hpp"

class AudioRecorder : public QMainWindow {
    Q_OBJECT
public:
    explicit AudioRecorder(QWidget *parent = nullptr);

public slots:
    void querySystemComponents();

protected:
    void resizeEvent(QResizeEvent *event) override;

public slots:
    void processBuffer(const QAudioBuffer &);

private slots:
    void setOutputLocation();
    void togglePause();
    void toggleRecord();

    void updateStatus(QMediaRecorder::Status);
    void onStateChanged(QMediaRecorder::State);
    void updateProgress(qint64 pos);
    void displayErrorMessage();


private:
    void clearAudioLevels();
    void setupRecordingConnections();

private:
    AudioUI *ui;
    QAudioRecorder *recorder;
    QAudioProbe *probe;
    std::vector<AudioLevel> audioLevels;
    bool output_location_set;

};


#endif //AUDIOPROJECT_AUDIORECORDER_HPP