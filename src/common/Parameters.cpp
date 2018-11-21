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

#include <common/Parameters.h>
#include <grape/helpers/Helpers.h>

//==============================================================================

namespace mbctrl {
namespace common {

//==============================================================================

static const int sNumSwitches = 2;
const std::array<juce::String, sNumSwitches> sSwitchLabels =
{{
    "Off",
    "On",
}};

static const int sNumLfoDestinations = 2;
const std::array<juce::String, sNumLfoDestinations> sLfoDestinationLabels =
{{
    "Osc",
    "Filter",
}};

static const int sNumOscillatorBWaves = 2;
const std::array<juce::String, sNumOscillatorBWaves> sOscillatorBWaveLabels =
{{
    "Pulse",
    "Sawtooth",
}};

//==============================================================================

const std::map<ParameterId, grape::parameters::Parameter> sParameters =
{
    {
        ParameterId::idEnvelopeAttack,
        {
            "envelope-attack",
            "Envelope Attack",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            0.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    {
        ParameterId::idEnvelopeDecay,
        {
            "envelope-decay",
            "Envelope Decay",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            64.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    {
        ParameterId::idFilterCutoff,
        {
            "filter-cutoff",
            "Filter Cutoff",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            64.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    {
        ParameterId::idPulseWidth,
        {
            "pulse-width",
            "Pulse Width",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            64.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    {
        ParameterId::idOscillatorDetune,
        {
            "oscillator-detune",
            "Oscillator Detune",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            64.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    {
        ParameterId::idLfoRate,
        {
            "lfo-rate",
            "LFO Rate",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            64.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    {
        ParameterId::idLfoDepth,
        {
            "lfo-depth",
            "LFO Depth",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            0.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    {
        ParameterId::idPortamento,
        {
            "portamento",
            "Portamento",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            0.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    {
        ParameterId::idVcfEnvelopeAmount,
        {
            "vcf-envelope-amount",
            "VCF Envelope Amount",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            64.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    {
        ParameterId::idSustain,
        {
            "sustain",
            "Sustain",
            "",
            juce::NormalisableRange<float> (0.0f, sNumSwitches - 1.0f, 1.0f),
            0.0f,
            grape::helpers::choiceIndexToLabel<sNumSwitches, sSwitchLabels>,
            grape::helpers::choiceLabelToIndex<sNumSwitches, sSwitchLabels>,
            false,
            true,
            true,
            true,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    {
        ParameterId::idOscillatorBOctave,
        {
            "oscillator-b-octave",
            "Oscillator B Octave",
            "",
            juce::NormalisableRange<float> (0.0f, sNumSwitches - 1.0f, 1.0f),
            0.0f,
            grape::helpers::choiceIndexToLabel<sNumSwitches, sSwitchLabels>,
            grape::helpers::choiceLabelToIndex<sNumSwitches, sSwitchLabels>,
            false,
            true,
            true,
            true,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    {
        ParameterId::idPWMSweep,
        {
            "pwm-sweep",
            "PWM Sweep",
            "",
            juce::NormalisableRange<float> (0.0f, sNumSwitches - 1.0f, 1.0f),
            0.0f,
            grape::helpers::choiceIndexToLabel<sNumSwitches, sSwitchLabels>,
            grape::helpers::choiceLabelToIndex<sNumSwitches, sSwitchLabels>,
            false,
            true,
            true,
            true,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    {
        ParameterId::idLfoDestination,
        {
            "lfo-destination",
            "LFO Destination",
            "",
            juce::NormalisableRange<float> (0.0f, sNumLfoDestinations - 1.0f, 1.0f),
            1.0f,
            grape::helpers::choiceIndexToLabel<sNumLfoDestinations, sLfoDestinationLabels>,
            grape::helpers::choiceLabelToIndex<sNumLfoDestinations, sLfoDestinationLabels>,
            false,
            true,
            true,
            true,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    {
        ParameterId::idLfoRandom,
        {
            "lfo-random",
            "LFO Random",
            "",
            juce::NormalisableRange<float> (0.0f, sNumSwitches - 1.0f, 1.0f),
            0.0f,
            grape::helpers::choiceIndexToLabel<sNumSwitches, sSwitchLabels>,
            grape::helpers::choiceLabelToIndex<sNumSwitches, sSwitchLabels>,
            false,
            true,
            true,
            true,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    {
        ParameterId::idLfoNoteRetrigger,
        {
            "lfo-note-retrigger",
            "LFO Note Retrigger",
            "",
            juce::NormalisableRange<float> (0.0f, sNumSwitches - 1.0f, 1.0f),
            0.0f,
            grape::helpers::choiceIndexToLabel<sNumSwitches, sSwitchLabels>,
            grape::helpers::choiceLabelToIndex<sNumSwitches, sSwitchLabels>,
            false,
            true,
            true,
            true,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    {
        ParameterId::idOscillatorBWave,
        {
            "oscillator-b-wave",
            "Oscillator B Wave",
            "",
            juce::NormalisableRange<float> (0.0f, sNumOscillatorBWaves - 1.0f, 1.0f),
            0.0f,
            grape::helpers::choiceIndexToLabel<sNumOscillatorBWaves, sOscillatorBWaveLabels>,
            grape::helpers::choiceLabelToIndex<sNumOscillatorBWaves, sOscillatorBWaveLabels>,
            false,
            true,
            true,
            true,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
};

const std::vector<grape::parameters::Parameter> sOrderedParameters =
{{
    sParameters.at (ParameterId::idEnvelopeAttack),
    sParameters.at (ParameterId::idEnvelopeDecay),
    sParameters.at (ParameterId::idFilterCutoff),
    sParameters.at (ParameterId::idPulseWidth),
    sParameters.at (ParameterId::idOscillatorDetune),
    sParameters.at (ParameterId::idLfoRate),
    sParameters.at (ParameterId::idLfoDepth),
    sParameters.at (ParameterId::idPortamento),
    sParameters.at (ParameterId::idVcfEnvelopeAmount),
    sParameters.at (ParameterId::idSustain),
    sParameters.at (ParameterId::idOscillatorBOctave),
    sParameters.at (ParameterId::idPWMSweep),
    sParameters.at (ParameterId::idLfoDestination),
    sParameters.at (ParameterId::idLfoRandom),
    sParameters.at (ParameterId::idLfoNoteRetrigger),
    sParameters.at (ParameterId::idOscillatorBWave),
}};

//==============================================================================

} // namespace common
} // namespace mbctrl
