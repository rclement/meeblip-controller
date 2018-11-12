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

#include <controller/MidiController.h>

//==============================================================================

namespace mbctrl {
namespace controller {

//==============================================================================

static const std::map<common::ParameterId, int> sParameterCcMapper =
{
    { common::ParameterId::idEnvelopeAttack,    54 },
    { common::ParameterId::idEnvelopeDecay,     53 },
    { common::ParameterId::idFilterCutoff,      52 },
    { common::ParameterId::idPulseWidth,        51 },
    { common::ParameterId::idOscillatorDetune,  50 },
    { common::ParameterId::idLfoRate,           49 },
    { common::ParameterId::idLfoDepth,          48 },
    { common::ParameterId::idPortamento,        55 },
    { common::ParameterId::idVcfEnvelopeAmount, 56 },
    { common::ParameterId::idSustain,           64 },
    { common::ParameterId::idOscillatorBOctave, 65 },
    { common::ParameterId::idPWMSweep,          66 },
    { common::ParameterId::idLfoDestination,    67 },
    { common::ParameterId::idLfoRandom,         68 },
    { common::ParameterId::idLfoNoteRetrigger,  69 },
    { common::ParameterId::idOscillatorBWave,   70 },
};

//==============================================================================

static juce::MidiMessage createParameterControl (common::ParameterId paramId,
                                                 float value,
                                                 int channel)
{
    jassert (channel > 0);

    const auto param = common::sParameters.at (paramId);
    const auto ccType = sParameterCcMapper.at (paramId);
    const auto ccValue = (
        param.isBoolean
        ? static_cast<int> (value * 127)
        : static_cast<int> (value)
    );

    return juce::MidiMessage::controllerEvent (channel, ccType, ccValue);
}

//==============================================================================

MidiController::MidiController (grape::parameters::ParameterManager& parameters,
                                grape::settings::SettingManager& settingManager)
    : mMidiOutputDevices()
    , mMidiOutput (nullptr)
    , mMidiChannel (1)
    , mParameters (parameters)
    , mSettingManager (settingManager)
{
    for (const auto& p : sParameterCcMapper)
    {
        const auto paramId  = p.first;
        const auto param    = common::sParameters.at (paramId);

        mParametersValues[paramId] = param.defaultValue;
        mParameters.addParameterListener (param.id, this);
    }

    mSettingManager.addListener (this);

    updateMidiOutputDevices();
    updateSettingsValues();
    updateParametersValues();
}

MidiController::~MidiController()
{
    for (const auto& p : sParameterCcMapper)
    {
        const auto paramId = p.first;
        const auto param = common::sParameters.at (paramId);

        mParameters.removeParameterListener (param.id, this);
    }

    mSettingManager.removeListener (this);
}

//==============================================================================

juce::StringArray MidiController::getMidiOutputDevices() const
{
    return mMidiOutputDevices;
}

void MidiController::updateMidiOutputDevices()
{
    mMidiOutputDevices = juce::MidiOutput::getDevices();
}

bool MidiController::selectDefaultMidiOutputDevice()
{
    return selectMidiOutputDevice (juce::MidiOutput::getDefaultDeviceIndex());
}

bool MidiController::selectMidiOutputDevice (int index)
{
    const auto device = juce::MidiOutput::openDevice (index);
    if (device != nullptr)
    {
        const auto midiDeviceSetting = common::sSettings.at (common::SettingId::idMidiDevice);

        mMidiOutput.reset (device);
        mSettingManager.setSetting (
            midiDeviceSetting.id,
            juce::var (mMidiOutput->getName())
        );

        return true;
    }
    return false;
}

bool MidiController::selectMidiOutputDeviceByName (const juce::String& deviceName)
{
    updateMidiOutputDevices();
    for (int i = 0; i < mMidiOutputDevices.size(); ++i)
    {
        const auto d = mMidiOutputDevices[i];
        if (d == deviceName)
        {
            selectMidiOutputDevice (i);
            return true;
        }
    }
    return false;
}

juce::String MidiController::getSelectedMidiOutputDevice() const
{
    if (mMidiOutput == nullptr)
        return juce::String();

    return mMidiOutput->getName();
}

void MidiController::setMidiChannel (int channel)
{
    jassert (channel > 0 && channel <= 16);

    const auto midiChannelSetting = common::sSettings.at (common::SettingId::idMidiChannel);

    mMidiChannel = channel;
    mSettingManager.setSetting (midiChannelSetting.id, juce::var (mMidiChannel));
}

void MidiController::synchronize()
{
    for (const auto& p : sParameterCcMapper)
    {
        const auto paramId  = p.first;
        const auto param    = common::sParameters.at (paramId);
        const auto newValue = *mParameters.getRawParameterValue (param.id);

        mParametersValues[paramId] = newValue;
        sendParameterControl (paramId, newValue);
    }
}

//==============================================================================

void MidiController::sendParameterControl (common::ParameterId paramId, float newValue) const
{
    if (mMidiOutput == nullptr)
        return;

    const auto cc = createParameterControl (paramId, newValue, mMidiChannel);
    mMidiOutput->sendMessageNow (cc);

    DBG (
        juce::String ("Sending: cc (") + juce::String (cc.getControllerNumber()) + ")"
        + " value (" + juce::String (cc.getControllerValue()) + ")"
        + " channel (" + juce::String (cc.getChannel()) + ")"
    );
}

void MidiController::updateParametersValues()
{
    for (const auto& p : sParameterCcMapper)
    {
        const auto paramId = p.first;
        const auto param = common::sParameters.at (paramId);

        const auto currentValue = mParametersValues[paramId];
        const auto newValue = *mParameters.getRawParameterValue (param.id);

        if (newValue != currentValue)
        {
            mParametersValues[paramId] = newValue;
            sendParameterControl (paramId, newValue);
        }
    }
}

void MidiController::updateSettingsValues()
{
    {
        const auto midiDeviceSetting    = common::sSettings.at (common::SettingId::idMidiDevice);
        const auto midiDevice           = mSettingManager.getSetting (midiDeviceSetting.id);
        selectMidiOutputDeviceByName (midiDevice.toString());
    }

    {
        const auto midiChannelSetting   = common::sSettings.at (common::SettingId::idMidiChannel);
        const auto midiChannel          = mSettingManager.getSetting (midiChannelSetting.id);
        setMidiChannel (int (midiChannel));
    }
}

//==============================================================================

void MidiController::parameterChanged (const juce::String& paramId, float paramValue)
{
    updateParametersValues();
}

//==============================================================================

void MidiController::settingChanged (const juce::String& setting, const juce::var& value)
{
    updateSettingsValues();
}

//==============================================================================

} // namespace controller
} // namespace mbctrl
