//
// Created by Erik Sevre on 5/10/18.
//

#include <iostream>

#include "AudioUI.hpp"

AudioUI::AudioUI(QWidget *parent)
        : QWidget(parent),
          mainLayout(new QVBoxLayout(this)),
          deviceSettingsTopGrid(new WidgetPairGrid(this)),
          encodingModeBox(new QGroupBox(this))
{
    encodingGridLayout = new QGridLayout(encodingModeBox);

    setup_ui();
    populate_widgets();
    initial_setup();
    connect_components();
    this->setMinimumSize(225, 375);
}

void AudioUI::setup_ui()
{
    deviceSettingsTopGrid->addPair(deviceLabel, deviceComboBox);
    deviceSettingsTopGrid->addPair(codecLabel, codecComboBox);
    deviceSettingsTopGrid->addPair(containerLabel, containerComboBox);
    deviceSettingsTopGrid->addPair(sampleRateLabel, sampleRateComboBox);
    deviceSettingsTopGrid->addPair(channelsLabel, channelsComboBox);
    mainLayout->addWidget(deviceSettingsTopGrid);

    encodingGridLayout->addWidget(constantQualityButton, 0, 0, 1, 2);
    encodingGridLayout->addItem(sliderSpacer, 1, 0, 1, 1);
    encodingGridLayout->addWidget(qualitySlider, 1, 1, 1, 1);
    encodingGridLayout->addWidget(constantBitrateButton, 2, 0, 1, 2);
    encodingGridLayout->addWidget(bitrateComboBox, 3, 1, 1, 1);
    mainLayout->addWidget(encodingModeBox);

    controlButtonLayout->addWidget(outputButton);
    controlButtonLayout->addWidget(recordButton);
    controlButtonLayout->addWidget(pauseButton);
    mainLayout->addLayout(controlButtonLayout);

    levelsLayout->addWidget(levelLabel, 0, 0, 1, 1);
    levelsLayout->addWidget(audioLevel, 0, 1, 1, 2);
    mainLayout->addLayout(levelsLayout);

    mainLayout->addWidget(statusBar);
    mainLayout->addWidget(reloadDevicesButton);
}

void AudioUI::populate_widgets()
{

    deviceLabel->setText(QLabel::tr("Device:"));
    codecLabel->setText(QLabel::tr("Codec:"));
    containerLabel->setText(QLabel::tr("Container:"));
    sampleRateLabel->setText(QLabel::tr("Sample Rate:"));
    channelsLabel->setText(QLabel::tr("Channels:"));

    encodingModeBox->setTitle(QGroupBox::tr("Encoding Mode"));
    constantQualityButton->setText(QRadioButton::tr("Constant Quality:"));
    qualitySlider->setOrientation(Qt::Horizontal);
    constantBitrateButton->setText(QRadioButton::tr("Constant Bitrate"));
    bitrateComboBox->addItem(QComboBox::tr("Default"));

    outputButton->setText(QPushButton::tr("Output"));
    recordButton->setText(QPushButton::tr("Record"));
    pauseButton->setText(QPushButton::tr( "Pause "));

    levelLabel->setText(QLabel::tr("Level:"));

    reloadDevicesButton->setText(QPushButton::tr("Reload Devices"));

}

void AudioUI::initial_setup()
{
    selectConstantQuality();
    pauseButton->setEnabled(false);
    //this->resize(300, 500);
}

void AudioUI::connect_components() {
    //
    //  Radio select buttons
    //
    connect(constantQualityButton, SIGNAL(toggled(bool)), this, SLOT(constantQualityButtonToggled(bool)));
    connect(constantBitrateButton, SIGNAL(toggled(bool)), this, SLOT(constantBitrateButtonToggled(bool)));

    //
    // button selections
    //
    connect(recordButton, SIGNAL(clicked()), this, SLOT(recordButtonSelected()));
    connect(outputButton, SIGNAL(clicked()), this, SLOT(outputButtonSelected()));
    connect(pauseButton,  SIGNAL(clicked()), this, SLOT(pauseButtonSelected()));


}

void AudioUI::constantQualityButtonToggled(bool val) {
    if (val) {
        qualitySlider->setEnabled(true);
        constantBitrateButton->setChecked(false);
        bitrateComboBox->setEnabled(false);
    }
}

void AudioUI::constantBitrateButtonToggled(bool val) {
    if (val) {
        constantQualityButton->setChecked(false);
        qualitySlider->setEnabled(false);
        bitrateComboBox->setEnabled(true);
    }
}

void AudioUI::selectConstantQuality() {
    constantQualityButton->setChecked(true);
    qualitySlider->setEnabled(true);
    constantBitrateButton->setChecked(false);
    bitrateComboBox->setEnabled(false);
}

void AudioUI::selectConstantBitrate() {
    constantQualityButton->setChecked(false);
    qualitySlider->setEnabled(false);
    constantBitrateButton->setChecked(true);
    bitrateComboBox->setEnabled(true);

}

void AudioUI::updateButtons(bool output, bool record, bool pause) {
    outputButton->setEnabled(output);
    recordButton->setEnabled(record);
    pauseButton->setEnabled(pause);
}

void AudioUI::outputButtonSelected() {
    // open file selection button
}

void AudioUI::recordButtonSelected() {
    switch (status) {
        case Status::NONE:
            [[fallthrough]];
        case Status::STOPPED:
            // start recording
            // set buttons
            updateButtons(false, true, true);
            status = Status::RECORDING;
            break;
        case Status::PAUSED:
            [[fallthrough]];
        case Status::RECORDING:
            // stop recording
            updateButtons(true, true, false);
            status = Status::STOPPED;
            break;
    }
}

void AudioUI::pauseButtonSelected() {
    switch (status) {
        case Status::NONE:
            [[fallthrough]];
        case Status::STOPPED:
            break;
        case Status::PAUSED:
            // resume recording
            updateButtons(false, true, true);
            status = Status::RECORDING;
            break;
        case Status::RECORDING:
            // pause recording
            updateButtons(false, true, true);
            status = Status::PAUSED;
            break;
    }
}










