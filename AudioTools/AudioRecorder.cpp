//
// Created by Erik Sevre on 5/14/18.
//

#include "AudioRecorder.hpp"

#include <iostream>

AudioRecorder::AudioRecorder(QWidget *parent)
        : QMainWindow(parent)
{
    // Setup UI
    ui = new AudioUI(this);
    this->setMinimumSize(ui->size());
    this->resize(300, 500);

    querySystemComponents();

    connect(recorder, &QAudioRecorder::statusChanged,  // SIGNAL
            this, &AudioRecorder::updateStatus);       // SLOTS

    connect(ui->reloadDevicesButton, SIGNAL(clicked()),  // SIGNAL
            this, SLOT(querySystemComponents()));        // SLOTS

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

void AudioRecorder::resizeEvent(QResizeEvent *event) {
    ui->resize(event->size());
}

void AudioRecorder::processBuffer(const QAudioBuffer &buffer) {

}

void AudioRecorder::clearAudioLevels() {
    for (int i = 0; i < audioLevels.size(); ++i) {
        audioLevels.at(i).setLevel(0);
    }
}


void AudioRecorder::setOutputLocation() {
    QString fileName = QFileDialog::getSaveFileName();
    recorder->setOutputLocation(QUrl::fromLocalFile(fileName));
    output_location_set = true;
}

void AudioRecorder::togglePause() {

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

static QVariant boxValue(const QComboBox *box)
{
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
        recorder->record();
    }
    else {
        recorder->stop();
    }
}
