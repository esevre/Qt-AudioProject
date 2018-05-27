//
// Created by Erik Sevre on 5/14/18.
//

#include "AudioRecorder.hpp"
#include "AudioBufferHelper.hpp"

#include <iostream>

#include <QAudioProbe>
#include <QAudioRecorder>
#include <QDir>
#include <QFileDialog>
#include <QMediaRecorder>
#include <QStandardPaths>


AudioRecorder::AudioRecorder(QWidget *parent)
        : QMainWindow(parent)
{
    // Setup UI
    ui = new AudioUI(this);
    this->setMinimumSize(ui->size());
    this->resize(300, 500);


    querySystemComponents();

    setupRecordingConnections();

    connect(recorder, &QAudioRecorder::durationChanged,
            this, &AudioRecorder::updateProgress);
    connect(recorder, &QAudioRecorder::statusChanged,
            this, &AudioRecorder::updateStatus);
    connect(recorder, &QAudioRecorder::stateChanged,
            this, &AudioRecorder::onStateChanged);

//    connect(recorder, SIGNAL(QAudioRecorder::error()),
//            this, SLOT(displayErrorMessage()));

    connect(ui->reloadDevicesButton, SIGNAL(clicked()),
            this, SLOT(querySystemComponents()));

}


void AudioRecorder::updateProgress(qint64 duration) {
    if (recorder->error() != QMediaRecorder::NoError || duration < 2000) {
        return;
    }

    ui->statusBar->showMessage(tr("Recorded %1 sec").arg(duration/1000));
}

void AudioRecorder::querySystemComponents() {
    // Setup recorder and probe
    recorder = new QAudioRecorder(this);

    probe = new QAudioProbe(this);
    connect(probe, &QAudioProbe::audioBufferProbed,
            this, &AudioRecorder::processBuffer);
    probe->setSource(recorder);


    // clear out the combo boxes
    ui->deviceComboBox->clear();
    ui->codecComboBox->clear();
    ui->containerComboBox->clear();
    ui->sampleRateComboBox->clear();
    ui->channelsComboBox->clear();
    ui->bitrateComboBox->clear();

    // audio devices
    ui->deviceComboBox->addItem(tr("Default"), QVariant(QString()));
    for (auto &device : recorder->audioInputs()) {
        ui->deviceComboBox->addItem(device, QVariant(device));
    }

    // audio codecs
    ui->codecComboBox->addItem(tr("Default"), QVariant(QString()));
    for (auto &codecName : recorder->supportedAudioCodecs()) {
        ui->codecComboBox->addItem(codecName, QVariant(codecName));
    }

    // containers
    ui->containerComboBox->addItem(tr("Default"), QVariant(QString()));
    for (auto &containerName : recorder->supportedContainers()) {
        ui->containerComboBox->addItem(containerName, QVariant(containerName));
    }

    // sample rate
    ui->sampleRateComboBox->addItem(tr("Default"), QVariant(QString()));
    for (auto sampleRate : recorder->supportedAudioSampleRates()){
        ui->sampleRateComboBox->addItem(QString::number(sampleRate), QVariant(sampleRate));
    }

    // channels
    ui->channelsComboBox->addItem(tr("Default"), QVariant(-1));
    ui->channelsComboBox->addItem(tr("1"), QVariant(1));
    ui->channelsComboBox->addItem(tr("2"), QVariant(2));
    ui->channelsComboBox->addItem(tr("3"), QVariant(4));

    // quality
    ui->qualitySlider->setRange(0, int(QMultimedia::VeryHighQuality));
    ui->qualitySlider->setValue(int(QMultimedia::NormalQuality));

    // bitrates
    ui->bitrateComboBox->addItem(tr("Default"), QVariant(0));
    ui->bitrateComboBox->addItem(tr("32000"), QVariant(32000));
    ui->bitrateComboBox->addItem(tr("64000"), QVariant(64000));
    ui->bitrateComboBox->addItem(tr("96000"), QVariant(96000));
    ui->bitrateComboBox->addItem(tr("128000"), QVariant(128000));

}

void AudioRecorder::updateStatus(QMediaRecorder::Status status) {
    QString statusMessage;

    switch (status) {
        case QMediaRecorder::RecordingStatus:
            statusMessage = tr("Recording to %1").arg(recorder->actualLocation().toString());
            break;
        case QMediaRecorder::PausedStatus:
            clearAudioLevels();
            statusMessage = tr("Paused");
            break;
        case QMediaRecorder::UnloadedStatus:
        case QMediaRecorder::LoadedStatus:
            clearAudioLevels();
            statusMessage = tr("Stopped");
        default:
            break;
    }

    if (recorder->error() == QMediaRecorder::NoError) {
        ui->statusBar->showMessage(statusMessage);
    }

}

void AudioRecorder::onStateChanged(QMediaRecorder::State state) {
    switch (state) {
        case QMediaRecorder::RecordingState:
            ui->recordButton->setText(tr("Stop"));
            ui->pauseButton->setText(tr("Pause"));
            break;
        case QMediaRecorder::PausedState:
            ui->recordButton->setText(tr("Stop"));
            ui->pauseButton->setText(tr("Resume"));
            break;
        case QMediaRecorder::StoppedState:
            ui->recordButton->setText(tr("Record"));
            ui->pauseButton->setText(tr("Pause"));
            break;
    }

    ui->pauseButton->setEnabled(recorder->state() != QMediaRecorder::StoppedState);
}

static QVariant boxValue(const QComboBox *box) {
    int idx = box->currentIndex();
    if (idx == -1){
        return QVariant();
    }
    return box->itemData(idx);
}

void AudioRecorder::toggleRecord() {
    if (recorder->state() == QMediaRecorder::StoppedState) {
        recorder->setAudioInput(boxValue(ui->deviceComboBox).toString());

        QAudioEncoderSettings settings;

        settings.setCodec(boxValue(ui->codecComboBox).toString());
        settings.setSampleRate(boxValue(ui->sampleRateComboBox).toInt());
        settings.setBitRate(boxValue(ui->bitrateComboBox).toInt());
        settings.setChannelCount(boxValue(ui->channelsComboBox).toInt());
        settings.setQuality(QMultimedia::EncodingQuality(ui->qualitySlider->value()));
        settings.setEncodingMode(ui->constantQualityButton->isChecked() ?
                                 QMultimedia::ConstantQualityEncoding :
                                 QMultimedia::ConstantBitRateEncoding);

        QString container = boxValue(ui->containerComboBox).toString();

        recorder->setEncodingSettings(settings, QVideoEncoderSettings(), container);
        std::cout << "starting recording:\n";
        recorder->record();

    }
    else {
        recorder->stop();
    }
}

void AudioRecorder::togglePause() {

}

void AudioRecorder::setOutputLocation() {
#ifdef Q_OS_WINRT
    // UWP does not allow to store outside the sandbox
    const QString cacheDir = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);
    if (!QDir().mkpath(cacheDir)) {
        qWarning() << "Failed to create cache directory";
        return;
    }
    QString fileName = cacheDir + QLatin1String("/output.wav");
#else
    QString fileName = QFileDialog::getSaveFileName();
#endif

    recorder->setOutputLocation(QUrl::fromLocalFile(fileName));
    output_location_set = true;

}

void AudioRecorder::displayErrorMessage() {
    ui->statusBar->showMessage(recorder->errorString());
}

void AudioRecorder::clearAudioLevels() {
    for (int i = 0; i < audioLevels.size(); ++i) {
        audioLevels.at(i).setLevel(0);
    }
}


void AudioRecorder::resizeEvent(QResizeEvent *event) {
    ui->resize(event->size());
}

void AudioRecorder::processBuffer(const QAudioBuffer &buffer) {
    if (audioLevels.size() != buffer.format().channelCount()) {

    }

    auto levels = getBufferLevels(buffer);
    for (int i = 0; i < levels.size(); ++i) {
        //audioLevels.at(i)->setLevel(levels.at(i));
        audioLevels[i].setLevel((levels[i]));
    }
}


void AudioRecorder::setupRecordingConnections() {
    // Record button clicked
    connect(ui->recordButton, SIGNAL(clicked()),
            this, SLOT(toggleRecord()));
    // Pause button clicked
    connect(ui->pauseButton, SIGNAL(clicked()),
            this, SLOT(togglePause()));
    // Output Button clicked
    connect(ui->outputButton, SIGNAL(clicked()),
            this, SLOT(setOutputLocation()));
    // Quality Radio Button


}







