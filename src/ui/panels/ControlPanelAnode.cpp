/*
    Meeblip Controller - MIDI controller for the Meeblip Anode synthesizer
    Copyright (c) 2018 Romain Clement

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

//==============================================================================

#include <ui/panels/ControlPanelAnode.h>
#include <common/Parameters.h>

//==============================================================================

namespace mbctrl {
namespace ui {

//==============================================================================

ControlPanelAnode::ControlPanelAnode (grape::parameters::ParameterManager& parameterManager,
                                      controller::MidiController& midiController)
    : mMidiController (midiController)
    , mEnvelopeAttack (parameterManager, common::ParameterId::idEnvelopeAttack, "ATTACK")
    , mEnvelopeDecay (parameterManager, common::ParameterId::idEnvelopeDecay, "DECAY")
    , mEnvelopeSustain (parameterManager, common::ParameterId::idSustain, "SUSTAIN")
    , mFilterCutoff (parameterManager, common::ParameterId::idFilterCutoff, "CUTOFF")
    , mOscillatorPulseWidth (parameterManager, common::ParameterId::idPulseWidth, "WIDTH")
    , mOscillatorDetune (parameterManager, common::ParameterId::idOscillatorDetune, "DETUNE")
    , mOscillatorBOctave (parameterManager, common::ParameterId::idOscillatorBOctave, "OCTAVE")
    , mPwmSweep (parameterManager, common::ParameterId::idPWMSweep, "SWEEP")
    , mLfoRate (parameterManager, common::ParameterId::idLfoRate, "RATE")
    , mLfoDepth (parameterManager, common::ParameterId::idLfoDepth, "DEPTH")
    , mLfoDestination (parameterManager, common::ParameterId::idLfoDestination, "LFO DEST")
    , mPortamento (parameterManager, common::ParameterId::idPortamento, "GLIDE")
    , mVcfEnvelopeAmount (parameterManager, common::ParameterId::idVcfEnvelopeAmount, "VCF ENV")
    , mLfoRandom (parameterManager, common::ParameterId::idLfoRandom, "LFO RAND")
    , mLfoNoteRetrigger (parameterManager, common::ParameterId::idLfoNoteRetrigger, "LFO RETRIG")
    , mOscillatorBWave (parameterManager, common::ParameterId::idOscillatorBWave, "OSC B")
{
    addAndMakeVisible (mMeeblipLogo);
    addAndMakeVisible (mAnodeLogo);

    mSync.setButtonText ("Synchronize");
    mSync.onClick = [this] { mMidiController.synchronize(); };
    addAndMakeVisible (mSync);

    mEnvelopeGroup.setText ("ENVELOPE");
    mEnvelopeGroup.setTextLabelPosition (juce::Justification::centred);
    addAndMakeVisible (mEnvelopeGroup);

    addAndMakeVisible (mEnvelopeAttack);
    addAndMakeVisible (mEnvelopeDecay);
    addAndMakeVisible (mEnvelopeSustain);

    mFilterGroup.setText ("FILTER");
    mFilterGroup.setTextLabelPosition (juce::Justification::centred);
    addAndMakeVisible (mFilterGroup);

    addAndMakeVisible (mFilterCutoff);

    mOscillatorsGroup.setText ("OSCILLATORS");
    mOscillatorsGroup.setTextLabelPosition (juce::Justification::centred);
    addAndMakeVisible (mOscillatorsGroup);

    addAndMakeVisible (mOscillatorPulseWidth);
    addAndMakeVisible (mOscillatorDetune);
    addAndMakeVisible (mOscillatorBOctave);
    addAndMakeVisible (mPwmSweep);

    mLfoGroup.setText ("LFO");
    mLfoGroup.setTextLabelPosition (juce::Justification::centred);
    addAndMakeVisible (mLfoGroup);

    addAndMakeVisible (mLfoRate);
    addAndMakeVisible (mLfoDepth);
    addAndMakeVisible (mLfoDestination);

    mMidiOnlyGroup.setText ("MIDI ONLY");
    mMidiOnlyGroup.setTextLabelPosition (juce::Justification::centred);
    addAndMakeVisible (mMidiOnlyGroup);

    addAndMakeVisible (mPortamento);
    addAndMakeVisible (mVcfEnvelopeAmount);
    addAndMakeVisible (mLfoRandom);
    addAndMakeVisible (mLfoNoteRetrigger);
    addAndMakeVisible (mOscillatorBWave);
}

ControlPanelAnode::~ControlPanelAnode()
{

}

//==============================================================================

void ControlPanelAnode::resized()
{
    static const auto sHorizontalMargin = 20;
    static const auto sVerticalMargin   = 20;
    static const auto sKnobWidth        = 70;
    static const auto sKnobHeight       = 80;
    static const auto sToggleWidth      = 70;
    static const auto sToggleHeight     = 80;
    static const auto sListWidth        = 70;
    static const auto sListHeight       = 80;
    static const auto sMeeblipWidth     = 100;
    static const auto sMeeblipHeight    = 25;
    static const auto sAnodeWidth       = 56;
    static const auto sAnodeHeight      = 25;
    static const auto sSyncWidth        = 100;
    static const auto sSyncHeight       = 20;

    const auto bounds       = getLocalBounds();
    const auto usableWidth  = bounds.getWidth() - sHorizontalMargin * 3;
    const auto leftWidth    = 3 * usableWidth / 5;
    const auto rightWidth   = usableWidth - leftWidth;

    {
        int meeblipLogoPngSize = 0;
        const auto meeblipLogoPng = AssetsData::getNamedResource (
            "meebliplogowhite_png",
            meeblipLogoPngSize
        );

        auto meeblipLogoImage = juce::ImageCache::getFromMemory (
            meeblipLogoPng,
            meeblipLogoPngSize
        );

        mMeeblipLogo.setImage (
            meeblipLogoImage.rescaled (sMeeblipWidth * 2, sMeeblipHeight * 2)
        );
    }

    mMeeblipLogo.setBounds (
        (sHorizontalMargin + (leftWidth / 2)) - sMeeblipWidth,
        sVerticalMargin,
        sMeeblipWidth,
        sMeeblipHeight
    );

    mMeeblipLogo.setBoundingBox (mMeeblipLogo.getBounds().toFloat());

    {
        int anodeLogoPngSize = 0;
        const auto anodeLogoPng = AssetsData::getNamedResource (
            "anodelogowhite_png",
            anodeLogoPngSize
        );

        auto anodeLogoImage = juce::ImageCache::getFromMemory (
            anodeLogoPng,
            anodeLogoPngSize
        );

        mAnodeLogo.setImage (
            anodeLogoImage.rescaled (sAnodeWidth * 2, sAnodeHeight * 2)
        );
    }

    mAnodeLogo.setBounds (
        mMeeblipLogo.getRight(),
        mMeeblipLogo.getY(),
        sAnodeWidth,
        sAnodeHeight
    );

    mAnodeLogo.setBoundingBox (mAnodeLogo.getBounds().toFloat());

    mSync.setBounds (
        (sHorizontalMargin * 2 + leftWidth + (rightWidth / 2)) - (sSyncWidth / 2),
        sVerticalMargin,
        sSyncWidth,
        sSyncHeight
    );

    mEnvelopeGroup.setBounds (
        sHorizontalMargin,
        mMeeblipLogo.getBottom() + sVerticalMargin,
        leftWidth,
        sKnobHeight + sVerticalMargin
    );

    mEnvelopeAttack.setBounds (
        mEnvelopeGroup.getX(),
        mEnvelopeGroup.getY() + sVerticalMargin,
        sKnobWidth,
        sKnobHeight
    );

    mEnvelopeDecay.setBounds (
        mEnvelopeGroup.getBounds().getCentreX() - (sKnobWidth / 2),
        mEnvelopeAttack.getY(),
        sKnobWidth,
        sKnobHeight
    );

    mEnvelopeSustain.setBounds (
        mEnvelopeGroup.getRight() - sToggleWidth,
        mEnvelopeDecay.getY(),
        sToggleWidth,
        sToggleHeight
    );

    mFilterGroup.setBounds (
        mEnvelopeGroup.getRight() + sHorizontalMargin,
        mEnvelopeGroup.getY(),
        rightWidth,
        mEnvelopeGroup.getHeight()
    );

    mFilterCutoff.setBounds (
        mFilterGroup.getBounds().getCentreX() - (sKnobWidth / 2),
        mFilterGroup.getY() + sVerticalMargin,
        sKnobWidth,
        sKnobHeight
    );

    mOscillatorsGroup.setBounds (
        mEnvelopeGroup.getX(),
        mEnvelopeGroup.getBottom() + sVerticalMargin,
        mEnvelopeGroup.getWidth(),
        sKnobHeight + sToggleHeight + sVerticalMargin
    );

    mOscillatorPulseWidth.setBounds (
        mOscillatorsGroup.getX(),
        mOscillatorsGroup.getY() + sVerticalMargin,
        sKnobWidth,
        sKnobHeight
    );

    mOscillatorDetune.setBounds (
        mOscillatorsGroup.getBounds().getCentreX() - (sKnobWidth / 2),
        mOscillatorPulseWidth.getY(),
        sKnobWidth,
        sKnobHeight
    );

    mOscillatorBOctave.setBounds (
        mOscillatorsGroup.getRight() - sToggleWidth,
        mOscillatorDetune.getY(),
        sToggleWidth,
        sToggleHeight
    );

    mPwmSweep.setBounds (
        mOscillatorDetune.getX(),
        mOscillatorDetune.getBottom(),
        sToggleWidth,
        sToggleHeight
    );

    mLfoGroup.setBounds (
        mFilterGroup.getX(),
        mFilterGroup.getBottom() + sVerticalMargin,
        mFilterGroup.getWidth(),
        mFilterGroup.getHeight()
    );

    mLfoRate.setBounds (
        mLfoGroup.getX(),
        mLfoGroup.getY() + sVerticalMargin,
        sKnobWidth,
        sKnobHeight
    );

    mLfoDepth.setBounds (
        mLfoGroup.getRight() - sKnobWidth,
        mLfoRate.getY(),
        sKnobWidth,
        sKnobHeight
    );

    mLfoDestination.setBounds (
        mLfoGroup.getBounds().getCentreX() - (sToggleWidth / 2),
        mLfoRate.getBottom(),
        sToggleWidth,
        sToggleHeight
    );

    mMidiOnlyGroup.setBounds (
        mOscillatorsGroup.getX(),
        mOscillatorsGroup.getBottom() + sVerticalMargin,
        mLfoGroup.getRight() - mOscillatorsGroup.getX(),
        mEnvelopeGroup.getHeight()
    );

    mPortamento.setBounds (
        mMidiOnlyGroup.getX(),
        mMidiOnlyGroup.getY() + sVerticalMargin,
        sKnobWidth,
        sKnobHeight
    );

    mLfoRandom.setBounds (
        mMidiOnlyGroup.getBounds().getCentreX() - (sToggleWidth / 2),
        mPortamento.getY(),
        sToggleWidth,
        sToggleHeight
    );

    mOscillatorBWave.setBounds (
        mMidiOnlyGroup.getRight() - sListWidth,
        mPortamento.getY(),
        sListWidth,
        sListHeight
    );

    mVcfEnvelopeAmount.setBounds (
        mPortamento.getRight() + (mLfoRandom.getX() - mPortamento.getRight()) / 2 - (sKnobWidth / 2),
        mPortamento.getY(),
        sKnobWidth,
        sKnobHeight
    );

    mLfoNoteRetrigger.setBounds (
        mLfoRandom.getRight() + (mOscillatorBWave.getX() - mLfoRandom.getRight()) / 2 - (sToggleWidth / 2),
        mPortamento.getY(),
        sToggleWidth,
        sToggleHeight
    );
}

void ControlPanelAnode::paint (juce::Graphics&)
{

}

//==============================================================================

} // namespace ui
} // namespace mbctrl

