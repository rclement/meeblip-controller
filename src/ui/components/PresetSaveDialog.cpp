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

#include <ui/components/PresetSaveDialog.h>

//==============================================================================

namespace mbctrl {
namespace ui {

//==============================================================================

PresetSaveDialog::PresetSaveDialog (grape::presets::PresetManager& presetManager)
    : mPresetManager (presetManager)
{
    const auto userPresets      = mPresetManager.getUserPresets();
    const auto currentPreset    = presetManager.getCurrentPreset();

    mPresetNameLabel.setText ("Name", juce::NotificationType::dontSendNotification);
    addAndMakeVisible (mPresetNameLabel);

    {
        juce::StringArray presetNames;
        for (const auto& p : userPresets)
        {
            presetNames.addIfNotAlreadyThere (p.getName());
        }
        mPresetNameSelector.addItemList (presetNames, 1);
    }
    mPresetNameSelector.onChange = [this] {
        mSaveButton.setEnabled (mPresetNameSelector.getText() != juce::String());
    };
    mPresetNameSelector.setEditableText (true);
    mPresetNameSelector.setText (currentPreset.getName());
    addAndMakeVisible (mPresetNameSelector);

    mPresetBankLabel.setText ("Bank", juce::NotificationType::dontSendNotification);
    addAndMakeVisible (mPresetBankLabel);

    {
        juce::StringArray presetBanks;
        for (const auto& p : userPresets)
        {
            presetBanks.addIfNotAlreadyThere (p.getBank());
        }
        mPresetBankSelector.addItemList (presetBanks, 1);
    }
    mPresetBankSelector.setEditableText (true);
    mPresetBankSelector.setText (currentPreset.getBank());
    addAndMakeVisible (mPresetBankSelector);

    mPresetAuthorLabel.setText ("Author", juce::NotificationType::dontSendNotification);
    addAndMakeVisible (mPresetAuthorLabel);

    mPresetAuthorText.setMultiLine (false);
    mPresetAuthorText.setText (currentPreset.getAuthor());
    addAndMakeVisible (mPresetAuthorText);

    mPresetCommentsLabel.setText ("Comments", juce::NotificationType::dontSendNotification);
    addAndMakeVisible (mPresetCommentsLabel);

    mPresetCommentsText.setMultiLine (true);
    mPresetCommentsText.setReturnKeyStartsNewLine (true);
    mPresetCommentsText.setText (currentPreset.getComments());
    addAndMakeVisible (mPresetCommentsText);

    mCancelButton.setEnabled (true);
    mCancelButton.onClick = [this] { closeParentModal(); };
    mCancelButton.setButtonText ("Cancel");
    addAndMakeVisible (mCancelButton);

    mSaveButton.setEnabled (false);
    mSaveButton.onClick = [this] { savePreset(); };
    mSaveButton.setButtonText ("Save");
    addAndMakeVisible (mSaveButton);
}

PresetSaveDialog::~PresetSaveDialog()
{

}

//==============================================================================

void PresetSaveDialog::resized()
{
    static const auto sHeight           = 20;
    static const auto sHorizontalMargin = 10;
    static const auto sVerticalMargin   = 10;

    const auto bounds = getLocalBounds();

    const auto usableWidth  = (bounds.getWidth() - sHorizontalMargin * 3);
    const auto labelWidth   = usableWidth / 3;
    const auto editorWidth  = usableWidth - labelWidth;

    mPresetNameLabel.setBounds (
        sHorizontalMargin,
        sVerticalMargin,
        labelWidth,
        sHeight
    );

    mPresetNameSelector.setBounds (
        mPresetNameLabel.getRight() + sHorizontalMargin,
        mPresetNameLabel.getY(),
        editorWidth,
        sHeight
    );

    mPresetBankLabel.setBounds (
        mPresetNameLabel.getX(),
        mPresetNameLabel.getBottom() + sVerticalMargin,
        labelWidth,
        sHeight
    );

    mPresetBankSelector.setBounds (
        mPresetBankLabel.getRight() + sHorizontalMargin,
        mPresetBankLabel.getY(),
        editorWidth,
        sHeight
    );

    mPresetAuthorLabel.setBounds (
        mPresetBankLabel.getX(),
        mPresetBankLabel.getBottom() + sVerticalMargin,
        labelWidth,
        sHeight
    );

    mPresetAuthorText.setBounds (
        mPresetAuthorLabel.getRight() + sHorizontalMargin,
        mPresetAuthorLabel.getY(),
        editorWidth,
        sHeight
    );

    mPresetCommentsLabel.setBounds (
        mPresetAuthorLabel.getX(),
        mPresetAuthorLabel.getBottom() + sVerticalMargin,
        labelWidth,
        sHeight
    );

    mPresetCommentsText.setBounds (
        mPresetCommentsLabel.getRight() + sHorizontalMargin,
        mPresetCommentsLabel.getY(),
        editorWidth,
        60
    );

    mCancelButton.setBounds (
        mPresetCommentsLabel.getX(),
        mPresetCommentsText.getBottom() + sVerticalMargin,
        usableWidth / 2,
        sHeight
    );

    mSaveButton.setBounds (
        mPresetCommentsText.getRight() - (usableWidth / 2),
        mPresetCommentsText.getBottom() + sVerticalMargin,
        usableWidth / 2,
        sHeight
    );
}

void PresetSaveDialog::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

//==============================================================================

void PresetSaveDialog::closeParentModal()
{
    if (juce::DialogWindow* dw = findParentComponentOfClass<juce::DialogWindow>())
    {
        dw->exitModalState (0);
    }
}

void PresetSaveDialog::savePreset()
{
    const auto userPresets  	= mPresetManager.getUserPresets();
    const auto presetName   	= mPresetNameSelector.getText();
    const auto presetBank       = mPresetBankSelector.getText();
    const auto presetAuthor     = mPresetAuthorText.getText();
    const auto presetComments   = mPresetCommentsText.getText();

    bool overwrite = false;
    for (auto& p : userPresets)
    {
        if (p.getName() == presetName && p.getBank() == presetBank)
        {
            overwrite = true;
            break;
        }
    }

    if (overwrite)
    {
        const bool confirm = juce::AlertWindow::showOkCancelBox (
            juce::AlertWindow::AlertIconType::QuestionIcon,
            "Overwrite Preset",
            presetName + " already exists, saving the preset will replace it. Overwrite?"
        );

        if (!confirm)
            return;
    }

    const bool saved = mPresetManager.saveCurrentPreset (
        presetName,
        presetBank,
        presetAuthor,
        presetComments
    );

    if (saved)
    {
        closeParentModal();
    }
}

//==============================================================================

} // namespace ui
} // namespace mbctrl
