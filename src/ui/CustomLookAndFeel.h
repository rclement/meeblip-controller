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

#pragma once

#include <JuceHeader.h>
#include <map>

//==============================================================================

namespace mbctrl {
namespace ui {

//==============================================================================

class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
    CustomLookAndFeel();
    ~CustomLookAndFeel();

public:
    enum class TypefaceId
    {
        typefaceMontserratExtraLight,
        typefaceMontserratRegular,
        numTypefaceIds,
    };

    struct TypefaceData
    {
        juce::String        mName;
        juce::Typeface::Ptr mPtr;
    };

public:
    static const std::map<TypefaceId, TypefaceData> sTypefaces;

public: // LookAndFeel_V4
    juce::Typeface::Ptr getTypefaceForFont (const juce::Font& f) override;
    void drawGroupComponentOutline (juce::Graphics&, int, int,
                                    const juce::String& text,
                                    const juce::Justification&,
                                    juce::GroupComponent&) override;
    void drawToggleButton (juce::Graphics& g,
                           juce::ToggleButton& button,
                           bool isMouseOverButton,
                           bool isButtonDown) override;
    void drawRotarySlider (juce::Graphics& g,
                           int x, int y, int width, int height,
                           float sliderPos,
                           const float rotaryStartAngle,
                           const float rotaryEndAngle,
                           juce::Slider& slider) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomLookAndFeel)
};

//==============================================================================

} // namespace ui
} // namespace mbctrl
