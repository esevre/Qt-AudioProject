//
// Created by Erik Sevre on 5/10/18.
//
//
//  todo: add slots and signals for event handling in the UI
//

#ifndef AUDIOPROJECT_AUDIOUI_HPP
#define AUDIOPROJECT_AUDIOUI_HPP

#include <QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>

#include "AudioLevel.hpp"
#include "WidgetPairGrid.hpp"


class AudioUI : public QWidget {
Q_OBJECT

public:
    explicit AudioUI(QWidget *parent=nullptr);
    enum class Status {NONE, RECORDING, PAUSED, STOPPED};

protected:
    QVBoxLayout *mainLayout;
    WidgetPairGrid *deviceSettingsTopGrid;
    QGridLayout *encodingGridLayout;
    QGroupBox *encodingModeBox;

    QHBoxLayout *controlButtonLayout = new QHBoxLayout;
    QGridLayout *levelsLayout = new QGridLayout;

    void setup_ui();
    void initial_setup();
    void populate_widgets();
    void connect_components();
private:
    void selectConstantQuality();
    void selectConstantBitrate();
    void updateButtons(bool output, bool record, bool pause);

private slots:
    void constantQualityButtonToggled(bool val);
    void constantBitrateButtonToggled(bool val);

    void outputButtonSelected();
    void recordButtonSelected();
    void pauseButtonSelected();

public:
    QLabel *deviceLabel = new QLabel;
    QComboBox *deviceComboBox = new QComboBox;
    QLabel *codecLabel = new QLabel;
    QComboBox *codecComboBox = new QComboBox;
    QLabel *containerLabel = new QLabel;
    QComboBox *containerComboBox = new QComboBox;
    QLabel *sampleRateLabel = new QLabel;
    QComboBox *sampleRateComboBox = new QComboBox;
    QLabel *channelsLabel = new QLabel;
    QComboBox *channelsComboBox = new QComboBox;

    QRadioButton *constantQualityButton = new QRadioButton;
    QSlider *qualitySlider = new QSlider;
    QRadioButton *constantBitrateButton = new QRadioButton;
    QComboBox *bitrateComboBox = new QComboBox;

    QPushButton *outputButton = new QPushButton;
    QPushButton *recordButton = new QPushButton;
    QPushButton *pauseButton = new QPushButton;

    QLabel *levelLabel = new QLabel;
    AudioLevel *audioLevel = new AudioLevel;

    QSpacerItem *sliderSpacer = new QSpacerItem(40, 30, QSizePolicy::Fixed, QSizePolicy::Minimum);

    Status status = Status::NONE;

    QStatusBar *statusBar = new QStatusBar;

    QPushButton *reloadDevicesButton = new QPushButton;

};


#endif //AUDIOPROJECT_AUDIOUI_HPP