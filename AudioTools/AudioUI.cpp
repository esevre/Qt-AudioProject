//
// Created by Erik Sevre on 5/10/18.
//

#include <iostream>

#include "AudioUI.hpp"

AudioUI::AudioUI(QWidget *parent)
        : QWidget(parent),
          main_layout(new QVBoxLayout(this)),
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
    deviceSettingsTopGrid->addPair(device_label, device_combo_box);
    deviceSettingsTopGrid->addPair(codec_label, codec_combo_box);
    deviceSettingsTopGrid->addPair(container_label, container_combo_box);
    deviceSettingsTopGrid->addPair(sample_rate_label, sample_rate_combo_box);
    deviceSettingsTopGrid->addPair(channels_label, channels_combo_box);
    main_layout->addWidget(deviceSettingsTopGrid);

    encodingGridLayout->addWidget(constantQualityButton, 0, 0, 1, 2);
    encodingGridLayout->addItem(sliderSpacer, 1, 0, 1, 1);
    encodingGridLayout->addWidget(qualitySlider, 1, 1, 1, 1);
    encodingGridLayout->addWidget(constantBitrateButton, 2, 0, 1, 2);
    encodingGridLayout->addWidget(bitrateComboBox, 3, 1, 1, 1);
    main_layout->addWidget(encodingModeBox);

    controlButtonLayout->addWidget(outputButton);
    controlButtonLayout->addWidget(recordButton);
    controlButtonLayout->addWidget(pauseButton);
    main_layout->addLayout(controlButtonLayout);

    levelsLayout->addWidget(levelLabel, 0, 0, 1, 1);
    levelsLayout->addWidget(audioLevel, 0, 1, 1, 2);
    main_layout->addLayout(levelsLayout);
}

void AudioUI::populate_widgets()
{

    device_label->setText(QLabel::tr("Device:"));
    device_combo_box->addItem(QComboBox::tr("Default"));
    codec_label->setText(QLabel::tr("Codec:"));
    codec_combo_box->addItem(QComboBox::tr("Default"));
    container_label->setText(QLabel::tr("Container:"));
    container_combo_box->addItem(QComboBox::tr("Default"));
    sample_rate_label->setText(QLabel::tr("Sample Rate:"));
    sample_rate_combo_box->addItem(QComboBox::tr("Default"));
    channels_label->setText(QLabel::tr("Channels:"));
    channels_combo_box->addItem(QComboBox::tr("Default"));

    encodingModeBox->setTitle(QGroupBox::tr("Encoding Mode"));
    constantQualityButton->setText(QRadioButton::tr("Constant Quality:"));
    qualitySlider->setOrientation(Qt::Horizontal);
    constantBitrateButton->setText(QRadioButton::tr("Constant Bitrate"));
    bitrateComboBox->addItem(QComboBox::tr("Default"));

    outputButton->setText(QPushButton::tr("Output"));
    recordButton->setText(QPushButton::tr("Record"));
    pauseButton->setText(QPushButton::tr( "Pause "));

    levelLabel->setText(QLabel::tr("Level:"));
    audioLevel->setLevel(0.0);
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










