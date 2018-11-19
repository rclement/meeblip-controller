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

#include <ui/CustomLookAndFeel.h>

//==============================================================================

namespace mbctrl {
namespace ui {

//==============================================================================

static const juce::LookAndFeel_V4::ColourScheme sAnodeColourScheme =
{
    0xff222222, 0xff333333, 0xff333333,
    0xffffffff, 0xffffffff, 0x00000000,
    0xffffffff, 0xffe85727, 0xffffffff
};

const std::map<CustomLookAndFeel::TypefaceId, CustomLookAndFeel::TypefaceData> CustomLookAndFeel::sTypefaces =
{
    {
        TypefaceId::typefaceMontserratExtraLight,
        {
            "montserrat-extra-light",
            juce::Typeface::createSystemTypefaceFor (
                AssetsData::MontserratExtraLight_ttf,
                AssetsData::MontserratExtraLight_ttfSize
            )
        }
    },
    {
        TypefaceId::typefaceMontserratRegular,
        {
            "montserrat-regular",
            juce::Typeface::createSystemTypefaceFor (
                AssetsData::MontserratRegular_ttf,
                AssetsData::MontserratRegular_ttfSize
            )
        }
    }
};

//==============================================================================

CustomLookAndFeel::CustomLookAndFeel()
{
    setColourScheme (sAnodeColourScheme);

    {
        const auto& tf = sTypefaces.at (TypefaceId::typefaceMontserratRegular);
        setDefaultSansSerifTypefaceName (tf.mName);
        setDefaultSansSerifTypeface (tf.mPtr);
    }

    setColour (
        juce::GroupComponent::ColourIds::textColourId,
        getCurrentColourScheme()
            .getUIColour (juce::LookAndFeel_V4::ColourScheme::UIColour::outline)
            .contrasting()
    );
}

CustomLookAndFeel::~CustomLookAndFeel()
{

}

//==============================================================================

juce::Typeface::Ptr CustomLookAndFeel::getTypefaceForFont (const juce::Font& f)
{
    const juce::String& typefaceName = f.getTypefaceName();
    for (auto t : sTypefaces)
    {
        auto data = t.second;
        if (data.mName == typefaceName)
        {
            return data.mPtr;
        }
    }

    return juce::LookAndFeel_V4::getTypefaceForFont (f);
}

void CustomLookAndFeel::drawGroupComponentOutline (juce::Graphics& g,
                                                   int width,
                                                   int height,
                                                   const juce::String& text,
                                                   const juce::Justification& position,
                                                   juce::GroupComponent& group)
{
    const float textH = 15.0f;
    const float indent = 3.0f;
    const float textEdgeGap = 4.0f;
    auto cs = 5.0f;

    juce::Font f (textH);

    auto x = indent;
    auto y = f.getAscent() - 3.0f;
    auto w = juce::jmax (0.0f, width - x * 2.0f);
    auto h = juce::jmax (0.0f, height - y  - indent);
    cs = juce::jmin (cs, w * 0.5f, h * 0.5f);
    auto cs2 = 2.0f * cs;

    auto textW = text.isEmpty() ? 0 : juce::jlimit (0.0f, juce::jmax (0.0f, w - cs2 - textEdgeGap * 2), f.getStringWidth (text) + textEdgeGap * 2.0f);
    auto textX = cs + textEdgeGap;

    if (position.testFlags (juce::Justification::horizontallyCentred))
        textX = cs + (w - cs2 - textW) * 0.5f;
    else if (position.testFlags (juce::Justification::right))
        textX = w - cs - textW - textEdgeGap;

    auto alpha = group.isEnabled() ? 1.0f : 0.5f;

    g.setColour (
        group.findColour (juce::GroupComponent::outlineColourId)
            .withMultipliedAlpha (alpha)
    );
    g.fillRoundedRectangle (x, 0, w, f.getHeight(), 3);

    g.setColour (
        group.findColour (juce::GroupComponent::textColourId)
            .withMultipliedAlpha (alpha)
    );
    g.setFont (f);
    g.drawText (
        text,
        juce::roundToInt (x + textX),
        0,
        juce::roundToInt (textW),
        juce::roundToInt (textH),
        juce::Justification::centred,
        true
    );
}

void CustomLookAndFeel::drawToggleButton (juce::Graphics& g,
                                          juce::ToggleButton& button,
                                          bool isMouseOverButton,
                                          bool isButtonDown)
{
    const auto ticked       = button.getToggleState();
    const auto buttonBounds = button.getBounds();
    const auto buttonSize   = juce::jmin (button.getWidth(), button.getHeight());

    const auto rectMargin   = 8;
    const auto rectWidth    = buttonSize - 2 * rectMargin;
    const auto rectHeight   = (buttonSize - 3 * rectMargin) / 2;
    const auto rectX        = buttonBounds.getCentreX() - (rectWidth / 2);
    const auto rectY        = button.getBottom() - rectHeight - rectMargin;

    const auto tickMargin   = 4;
    const auto tickRadius   = rectHeight - 2 * tickMargin;
    const auto tickX        = ticked ? rectX + rectWidth - tickRadius - tickMargin : rectX + tickMargin;
    const auto tickY        = rectY + tickMargin;

    const auto cubeMargin   = tickMargin;
    const auto cubeSize     = tickRadius;

    g.setColour (
        getCurrentColourScheme()
            .getUIColour (juce::LookAndFeel_V4::ColourScheme::UIColour::outline)
    );
    g.drawRoundedRectangle (rectX + cubeMargin, rectMargin + cubeMargin, cubeSize, cubeSize, 3, 2);
    g.fillRoundedRectangle (rectX + rectWidth - cubeMargin - cubeSize, rectMargin + cubeMargin, cubeSize, cubeSize, 3);
    g.drawRoundedRectangle (rectX, rectY, rectWidth, rectHeight, 5, 2);

    g.setColour (button.findColour (juce::ToggleButton::tickColourId));
    g.fillEllipse (tickX, tickY, tickRadius, tickRadius);
}

void CustomLookAndFeel::drawRotarySlider (juce::Graphics& g,
                                          int x, int y,
                                          int width, int height,
                                          float sliderPos,
                                          const float rotaryStartAngle,
                                          const float rotaryEndAngle,
                                          juce::Slider& slider)
{
    auto outline = slider.findColour (juce::Slider::rotarySliderOutlineColourId);
    auto fill    = slider.findColour (juce::Slider::rotarySliderFillColourId);

    auto bounds = juce::Rectangle<int> (x, y, width, height).toFloat().reduced (10);

    auto radius = juce::jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
    auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    auto lineW = juce::jmin (4.0f, radius * 0.5f);
    auto arcRadius = radius - lineW * 0.5f;

    juce::Path backgroundArc;
    backgroundArc.addCentredArc (bounds.getCentreX(),
                                 bounds.getCentreY(),
                                 arcRadius,
                                 arcRadius,
                                 0.0f,
                                 rotaryStartAngle,
                                 rotaryEndAngle,
                                 true);

    g.setColour (outline);
    g.strokePath (
        backgroundArc,
        juce::PathStrokeType (
            lineW,
            juce::PathStrokeType::curved,
            juce::PathStrokeType::rounded
        )
    );

    if (slider.isEnabled())
    {
        juce::Path valueArc;
        valueArc.addCentredArc (bounds.getCentreX(),
                                bounds.getCentreY(),
                                arcRadius,
                                arcRadius,
                                0.0f,
                                rotaryStartAngle,
                                toAngle,
                                true);

        g.setColour (fill);
        g.strokePath (
            valueArc,
            juce::PathStrokeType (
                lineW,
                juce::PathStrokeType::curved,
                juce::PathStrokeType::rounded
            )
        );
    }

    auto thumbWidth = lineW * 2.0f;
    juce::Point<float> thumbPoint (
        bounds.getCentreX() + arcRadius * std::cos (toAngle - juce::MathConstants<float>::halfPi),
        bounds.getCentreY() + arcRadius * std::sin (toAngle - juce::MathConstants<float>::halfPi)
    );

    g.setColour (slider.findColour (juce::Slider::thumbColourId));
    g.fillEllipse (
        juce::Rectangle<float> (thumbWidth, thumbWidth).withCentre (thumbPoint)
    );

    g.setColour (slider.findColour (juce::Slider::textBoxTextColourId));
    g.drawText (
        juce::String (slider.getValue()),
        x, y, width, height,
        juce::Justification::centred
    );
}

//==============================================================================

} // namespace ui
} // namespace mbctrl
