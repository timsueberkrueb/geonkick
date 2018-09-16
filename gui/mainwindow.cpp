/**
 * File name: mainwindow.cpp
 * Project: GeonKick (A kick synthesizer)
 *
 * Copyright (C) 2017 Iurie Nistor (http://geontime.com)
 *
 * This file is part of GeonKick.
 *
 * GeonKick is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "mainwindow.h"
#include "gkick_envelope_widget.h"
#include "oscillator_group_box.h"
#include "general_group_box.h"
#include "control_area.h"
#include "geonkick_theme.h"
#include "top_bar.h"
#include "fader.h"

#include <QCloseEvent>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>

#define GEONKICK_MAINWINDOW_WIDTH  940
#define GEONKICK_MAINWINDOW_HEIGHT 765

MainWindow::MainWindow(GeonkickWidget *parent) :
        GeonkickWidget(parent),
        gkickApi(std::make_shared<GKickApi>())
{
        QPalette pal;
        pal.setColor(QPalette::Background, QColor(68, 68, 70));
        setAutoFillBackground(true);
        setPalette(pal);
        setFixedSize(GEONKICK_MAINWINDOW_WIDTH, GEONKICK_MAINWINDOW_HEIGHT);
        setWindowFlags(Qt::FramelessWindowHint | Qt::WindowCloseButtonHint);
}

MainWindow::~MainWindow()
{
}

bool MainWindow::init(void)
{
        if (gkickApi->init()) {
	  //return false;
        }

        setTheme(new GeonkickTheme("Geontime"));

        gkickApi->setMaxLength(300);
        gkickApi->setKickLength(300);
        gkickApi->setAmplitude(0);
        gkickApi->setKickFilterFrequency(0);
        oscillators = gkickApi.get()->getOscillators();
	oscillators[GKickOscillator::OSC_1].get()->setOscFunction(GKickOscillator::OSC_FUNC_SINE);
	oscillators[GKickOscillator::OSC_2].get()->setOscFunction(GKickOscillator::OSC_FUNC_SINE);
	oscillators[GKickOscillator::OSC_NOISE].get()->setOscFunction(GKickOscillator::OSC_FUNC_NOISE);
	oscillators[GKickOscillator::OSC_1].get()->setOscAmplitudeValue(0.8);
	oscillators[GKickOscillator::OSC_1].get()->setOscFrequencyValue(1000);
	oscillators[GKickOscillator::OSC_1].get()->setFilterType(GKickOscillator::FILTER_LP);
	oscillators[GKickOscillator::OSC_1].get()->setFilterFrequency(20000);
	oscillators[GKickOscillator::OSC_2].get()->setOscAmplitudeValue(0.8);
	oscillators[GKickOscillator::OSC_2].get()->setOscFrequencyValue(1000);
	oscillators[GKickOscillator::OSC_2].get()->setFilterType(GKickOscillator::FILTER_LP);
	oscillators[GKickOscillator::OSC_2].get()->setFilterFrequency(20000);
	oscillators[GKickOscillator::OSC_NOISE].get()->setOscAmplitudeValue(0.8);
	oscillators[GKickOscillator::OSC_NOISE].get()->setFilterType(GKickOscillator::FILTER_LP);
	oscillators[GKickOscillator::OSC_NOISE].get()->setFilterFrequency(20000);

	QVBoxLayout *mainLayout = new QVBoxLayout(this);
        mainLayout->setContentsMargins(0, 0, 0, 10);
        mainLayout->setSpacing(5);
        setLayout(mainLayout);

        mainLayout->addWidget(new TopBar(this));

        // Create envelope widget.
        auto hBoxLayout = new QHBoxLayout;
        hBoxLayout->setSpacing(0);
        hBoxLayout->setContentsMargins(0, 0, 0, 0);
        auto envelopeWidget = new GKickEnvelopeWidget(this, gkickApi, oscillators);
        envelopeWidget->setFixedSize(850, 340);
        hBoxLayout->addWidget(envelopeWidget);
        auto faderWidget = new Fader(this);
        faderWidget->setFixedSize(65, 330);
        hBoxLayout->addWidget(faderWidget, 0, Qt::AlignTop);
        hBoxLayout->addSpacing(5);
        mainLayout->addLayout(hBoxLayout);

        // Create control area.
        ControlArea *controlAreaWidget = new ControlArea(this, gkickApi, oscillators);
        mainLayout->addWidget(controlAreaWidget);

        return true;
}
