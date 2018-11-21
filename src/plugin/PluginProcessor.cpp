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

#include <plugin/PluginProcessor.h>
#include <plugin/PluginEditor.h>
#include <common/Parameters.h>
#include <common/Settings.h>

//==============================================================================

namespace mbctrl {
namespace plugin {

//==============================================================================

PluginProcessor::PluginProcessor()
    : juce::AudioProcessor (
          juce::AudioProcessor::BusesProperties()
              .withInput ("Input", juce::AudioChannelSet::stereo(), true)
              .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
      )
    , mUndoManager()
    , mParameterManager (*this, &mUndoManager, common::sOrderedParameters)
    , mPresetManager (mParameterManager)
    , mSettingManager (common::sOrderedSettings, &mUndoManager)
    , mMidiController (mParameterManager,
                       mSettingManager,
                       wrapperType == WrapperType::wrapperType_Standalone)
{

}

PluginProcessor::~PluginProcessor()
{

}

//==============================================================================

const juce::String PluginProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PluginProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PluginProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PluginProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PluginProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PluginProcessor::getNumPrograms()
{
    const auto factoryPresets = mPresetManager.getFactoryPresets();
    const int numPrograms = factoryPresets.size();
    return numPrograms > 0 ? numPrograms : 1;
}

int PluginProcessor::getCurrentProgram()
{
    const auto factoryPresets = mPresetManager.getFactoryPresets();
    const auto currentPreset = mPresetManager.getCurrentPreset();
    return juce::jmax (0, factoryPresets.indexOf (currentPreset));
}

void PluginProcessor::setCurrentProgram (int index)
{
    const auto factoryPresets = mPresetManager.getFactoryPresets();
    const auto preset = factoryPresets[index];
    mPresetManager.loadPreset (preset);
}

const juce::String PluginProcessor::getProgramName (int index)
{
    const auto factoryPresets = mPresetManager.getFactoryPresets();
    const auto preset = factoryPresets[index];
    return preset.getName();
}

void PluginProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================

void PluginProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{

}

void PluginProcessor::releaseResources()
{

}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PluginProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void PluginProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                    juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;

    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    {
        const auto useMidiExternalSetting   = common::sSettings.at (common::SettingId::idUseExternalMidi);
        const auto useMidiExternal          = bool (mSettingManager.getSetting (useMidiExternalSetting.id));

        if (!useMidiExternal)
        {
            const auto midiEvents = mMidiController.extractMidiBuffer();
            auto midiIterator = juce::MidiBuffer::Iterator (midiEvents);

            juce::MidiMessage midiMessage;
            int midiSampleNumber;
            while (midiIterator.getNextEvent (midiMessage, midiSampleNumber))
            {
                midiMessages.addEvent (midiMessage, midiSampleNumber);
            }
        }
    }
}

//==============================================================================

bool PluginProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* PluginProcessor::createEditor()
{
    return new PluginEditor (*this);
}

//==============================================================================

void PluginProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    int xmlIndex = 0;
    std::unique_ptr<juce::XmlElement> xmlState (new juce::XmlElement ("state"));
    xmlState->insertChildElement (mParameterManager.toXml(), xmlIndex++);
    xmlState->insertChildElement (mPresetManager.toXml(), xmlIndex++);
    xmlState->insertChildElement (mSettingManager.toXml(), xmlIndex++);
    copyXmlToBinary (*xmlState, destData);
}

void PluginProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    int xmlIndex = 0;
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    if (xmlState.get() != nullptr && xmlState->hasTagName ("state"))
    {
        const auto xmlParameters = xmlState->getChildElement (xmlIndex++);
        if (xmlParameters != nullptr)
        {
            mParameterManager.fromXml (*xmlParameters);
        }

        const auto xmlCurrentPreset = xmlState->getChildElement (xmlIndex++);
        if (xmlCurrentPreset != nullptr)
        {
            mPresetManager.fromXml (*xmlCurrentPreset);
        }

        const auto xmlSettings = xmlState->getChildElement (xmlIndex++);
        if (xmlSettings != nullptr)
        {
            mSettingManager.fromXml (*xmlSettings);
        }
    }
}

//==============================================================================

} // namespace plugin
} // namespace mbctrl

//==============================================================================

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new mbctrl::plugin::PluginProcessor();
}


