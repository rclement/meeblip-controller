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

#include <ui/panels/PresetPanel.h>
#include <ui/components/AboutDialog.h>
#include <ui/CustomLookAndFeel.h>
#include <map>

//==============================================================================

namespace mbctrl {
namespace ui {

//==============================================================================

PresetPanel::PresetPanel (grape::presets::PresetManager& presetManager,
                          juce::UndoManager& undoManager)
    : mUndoManager (undoManager)
    , mLogo ("logo", juce::DrawableButton::ButtonStyle::ImageStretched)
    , mPresetBar (presetManager)
{
    {
        int mbctrlLogoPngSize = 0;
        const auto mbctrlLogoPng = AssetsData::getNamedResource (
            "mbctrllogowhite_png",
            mbctrlLogoPngSize
        );

        std::unique_ptr<juce::Drawable> mbctrlLogoImage (
            juce::Drawable::createFromImageData (
                mbctrlLogoPng,
                mbctrlLogoPngSize
            )
        );

        mLogo.setImages (mbctrlLogoImage.get());
    }
    mLogo.onClick = [this]
    {
        juce::DialogWindow::LaunchOptions options;
        options.dialogTitle = "About";
        options.escapeKeyTriggersCloseButton = true;
        options.resizable = false;
        options.useBottomRightCornerResizer = false;
        options.componentToCentreAround = getTopLevelComponent();
        options.content.set (new AboutDialog (), true);
        options.content->setSize(400, 200);
        options.launchAsync();
    };
    addAndMakeVisible (mLogo);

    addAndMakeVisible (mPresetBar);

    mUndo.onClick = [this] { mUndoManager.undo(); };
    mUndo.setButtonText ("Undo");
    mUndo.setConnectedEdges (juce::Button::ConnectedEdgeFlags::ConnectedOnRight);
    addAndMakeVisible (mUndo);

    mRedo.onClick = [this] { mUndoManager.redo(); };
    mRedo.setButtonText ("Redo");
    mRedo.setConnectedEdges (juce::Button::ConnectedEdgeFlags::ConnectedOnLeft);
    addAndMakeVisible (mRedo);

    mUndoManager.addChangeListener (this);
    updateUndoRedoState();
}

PresetPanel::~PresetPanel()
{
    mUndoManager.removeChangeListener (this);
}

//==============================================================================

void PresetPanel::resized()
{
    static const auto sVerticalMargin   = 10;
    static const auto sHorizontalMargin = 20;
    static const auto sButtonWidth      = 40;
    static const auto sButtonHeight     = 20;

    const auto bounds           = getLocalBounds();
    const auto logoSize         = juce::Rectangle<int> (bounds.getHeight(), bounds.getHeight());
    const auto presetBarSize    = juce::Rectangle<int> (
        bounds.getWidth() - logoSize.getWidth() - sButtonWidth * 2 - sHorizontalMargin * 4,
        sButtonHeight
    );

    mLogo.setBounds (
        sHorizontalMargin,
        0,
        logoSize.getWidth(),
        logoSize.getHeight()
    );

    mPresetBar.setBounds (
        mLogo.getRight() + sHorizontalMargin,
        sVerticalMargin + 5,
        presetBarSize.getWidth(),
        presetBarSize.getHeight()
    );

    mUndo.setBounds (
        mPresetBar.getRight() + sHorizontalMargin,
        mPresetBar.getY(),
        sButtonWidth,
        sButtonHeight
    );

    mRedo.setBounds (
        mUndo.getRight() - 1,
        mUndo.getY(),
        sButtonWidth,
        sButtonHeight
    );
}

void PresetPanel::paint (juce::Graphics& g)
{
    const auto bounds = getLocalBounds();

    g.setColour (juce::Colours::white);
    g.drawLine (
        bounds.getX(),
        bounds.getBottom(),
        bounds.getRight(),
        bounds.getBottom(),
        2
    );
}

//==============================================================================

void PresetPanel::updateUndoRedoState()
{
    mUndo.setEnabled (mUndoManager.canUndo());
    mRedo.setEnabled (mUndoManager.canRedo());
}

//==============================================================================

void PresetPanel::changeListenerCallback (juce::ChangeBroadcaster* source)
{
    if (source != nullptr && source == &mUndoManager)
    {
        updateUndoRedoState();
    }
}

//==============================================================================

} // namespace ui
} // namespace mbctrl

