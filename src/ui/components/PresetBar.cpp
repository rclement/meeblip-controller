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

#include <ui/components/PresetBar.h>
#include <ui/components/PresetSaveDialog.h>
#include <map>

//==============================================================================

namespace mbctrl {
namespace ui {

//==============================================================================

PresetBar::PresetBar (grape::presets::PresetManager& presetManager)
    : mPresetManager (presetManager)
    , mPresetPrevious ("preset-previous", juce::DrawableButton::ButtonStyle::ImageStretched)
    , mPresetNext ("preset-next", juce::DrawableButton::ButtonStyle::ImageStretched)
{
    {
        int leftArrowSvgSize = 0;
        const auto leftArrowSvg = AssetsData::getNamedResource (
            "leftarrow_svg",
            leftArrowSvgSize
        );

        std::unique_ptr<juce::Drawable> leftArrowImage (
            juce::Drawable::createFromImageData (
                leftArrowSvg,
                leftArrowSvgSize
            )
        );

        mPresetPrevious.setImages (leftArrowImage.get());
        mPresetPrevious.setButtonStyle (juce::DrawableButton::ButtonStyle::ImageOnButtonBackground);
        mPresetPrevious.setConnectedEdges (juce::Button::ConnectedEdgeFlags::ConnectedOnRight);
    }
    mPresetPrevious.onClick = [this] { mPresetManager.loadPreviousPreset(); };
    addAndMakeVisible (mPresetPrevious);

    {
        int rightArrowSvgSize = 0;
        const auto rightArrowSvg = AssetsData::getNamedResource (
            "rightarrow_svg",
            rightArrowSvgSize
        );

        std::unique_ptr<juce::Drawable> rightArrowImage (
            juce::Drawable::createFromImageData (
                rightArrowSvg,
                rightArrowSvgSize
            )
        );

        mPresetNext.setImages (rightArrowImage.get());
        mPresetNext.setButtonStyle (juce::DrawableButton::ButtonStyle::ImageOnButtonBackground);
        mPresetNext.setConnectedEdges (
            juce::Button::ConnectedEdgeFlags::ConnectedOnLeft
            | juce::Button::ConnectedEdgeFlags::ConnectedOnRight
        );
    }
    mPresetNext.onClick = [this] { mPresetManager.loadNextPreset(); };
    addAndMakeVisible (mPresetNext);

    mPresetLoader.setConnectedEdges (
        juce::Button::ConnectedEdgeFlags::ConnectedOnLeft
        | juce::Button::ConnectedEdgeFlags::ConnectedOnRight
    );
    mPresetLoader.onClick = [this] { openPresetLoader(); };
    addAndMakeVisible (mPresetLoader);

    mPresetSave.setButtonText ("Save");
    mPresetSave.setConnectedEdges (juce::Button::ConnectedEdgeFlags::ConnectedOnLeft);
    mPresetSave.onClick = [this] { openPresetSaveDialog(); };
    addAndMakeVisible (mPresetSave);

    mPresetManager.addListener (this);
    updateCurrentPreset (mPresetManager.getCurrentPreset());
}

PresetBar::~PresetBar()
{
    mPresetManager.removeListener (this);
}

//==============================================================================

void PresetBar::resized()
{
    static const auto sPresetPrevNextSize   = juce::Rectangle<int> (20, 20);
    static const auto sPresetSaveSize       = juce::Rectangle<int> (50, 20);

    const auto bounds = getLocalBounds();

    const auto presetLoaderSize = juce::Rectangle<int> (
        bounds.getWidth() - sPresetPrevNextSize.getWidth() * 2 - sPresetSaveSize.getWidth(),
        20
    );

    mPresetPrevious.setBounds (
        0,
        0,
        sPresetPrevNextSize.getWidth(),
        sPresetPrevNextSize.getHeight()
    );

    mPresetNext.setBounds (
        mPresetPrevious.getBounds().getRight() - 1,
        0,
        sPresetPrevNextSize.getWidth(),
        sPresetPrevNextSize.getHeight()
    );

    mPresetLoader.setBounds (
        mPresetNext.getBounds().getRight() - 1,
        0,
        presetLoaderSize.getWidth(),
        presetLoaderSize.getHeight()
    );

    mPresetSave.setBounds (
        mPresetLoader.getBounds().getRight() - 1,
        0,
        sPresetSaveSize.getWidth(),
        sPresetSaveSize.getHeight()
    );
}

void PresetBar::paint (juce::Graphics& g)
{

}

//==============================================================================

void PresetBar::updateCurrentPreset (const grape::presets::Preset& preset)
{
    mCurrentPreset = preset;

    const auto currentPresetName = (
        mCurrentPreset.getName()
        + (mCurrentPreset.isModified() ? " *" : "")
    );

    mPresetLoader.setButtonText (currentPresetName);
    mPresetPrevious.setEnabled (mPresetManager.canLoadPreviousPreset());
    mPresetNext.setEnabled (mPresetManager.canLoadNextPreset());
}

void PresetBar::openPresetLoader()
{
    const auto factoryPresets   = mPresetManager.getFactoryPresets();
    const auto userPresets      = mPresetManager.getUserPresets();

    const auto numFactoryPresets    = factoryPresets.size();
    const auto numUserPresets       = userPresets.size();

    const auto factoryPresetsOffsetIdStart  = 1;
    const auto factoryPresetsOffsetIdEnd    = numFactoryPresets;
    const auto userPresetsOffsetIdStart     = factoryPresetsOffsetIdEnd + 1;
    const auto userPresetsOffsetIdEnd       = userPresetsOffsetIdStart + numUserPresets - 1;
    const auto defaultPresetsOffsetId       = userPresetsOffsetIdEnd + 1;
    const auto openUserPresetsOffsetId      = defaultPresetsOffsetId + 1;

    juce::PopupMenu menuFactory = createPresetsMenu (factoryPresets, factoryPresetsOffsetIdStart);
    juce::PopupMenu menuUser = createPresetsMenu (userPresets, userPresetsOffsetIdStart);

    juce::PopupMenu menu;
    menu.addSubMenu ("Factory presets", menuFactory);
    menu.addSubMenu ("User presets", menuUser);
    menu.addSeparator();
    menu.addItem (defaultPresetsOffsetId, "Default preset");
    menu.addSeparator();
    menu.addItem (openUserPresetsOffsetId, "Open user presets folder");

    grape::presets::Preset preset;

    const int selected = menu.showMenu (
        juce::PopupMenu::Options()
            .withTargetComponent (&mPresetLoader)
            .withMaximumNumColumns (1)
    );

    if (selected >= factoryPresetsOffsetIdStart && selected <= factoryPresetsOffsetIdEnd)
    {
        const int presetIndex = selected - 1;
        preset = factoryPresets[presetIndex];
    }
    else if (selected >= userPresetsOffsetIdStart && selected <= userPresetsOffsetIdEnd)
    {
        const int presetIndex = selected - numFactoryPresets - 1;
        preset = userPresets[presetIndex];
    }
    else if (selected == defaultPresetsOffsetId)
    {
        mPresetManager.loadDefaultPreset();
    }
    else if (selected == openUserPresetsOffsetId)
    {
        const auto userPresetsFolder = mPresetManager.getUserPresetsLocation();
        userPresetsFolder.revealToUser();
    }

    if (preset.getName() != juce::String())
    {
        mPresetManager.loadPreset (preset);
    }
}

juce::PopupMenu PresetBar::createPresetsMenu (const juce::Array<grape::presets::Preset>& presetsList,
                                              int idOffset)
{
    juce::PopupMenu menu;

    if (presetsList.size() > 0)
    {
        std::vector<juce::PopupMenu::Item> noBankItems;
        std::map<juce::String, juce::PopupMenu> bankMenus;

        for (auto& p : presetsList)
        {
            const bool selected = (p == mCurrentPreset);
            const auto bank = p.getBank();

            juce::String name (p.getName());
            if (selected && mCurrentPreset.isModified())
                name += " *";

            juce::PopupMenu::Item item;
            item.text = name;
            item.itemID = idOffset++;
            item.isEnabled = true;
            item.isTicked = selected;

            if (bank == juce::String())
            {
                noBankItems.push_back (item);
            }
            else
            {
                bankMenus[bank].addItem (item);
            }
        }

        for (auto& m : bankMenus)
        {
            if (m.second.getNumItems() == 0)
                continue;

            menu.addSubMenu (m.first, m.second);
        }

        for (auto& item : noBankItems)
        {
            menu.addItem (item);
        }
    }
    else
    {
        menu.addItem (idOffset++, "No presets", false);
    }

    return menu;
}

void PresetBar::openPresetSaveDialog()
{
    juce::DialogWindow::LaunchOptions options;
    options.dialogTitle = "Save Preset";
    options.escapeKeyTriggersCloseButton = true;
    options.resizable = false;
    options.useBottomRightCornerResizer = false;
    options.componentToCentreAround = getTopLevelComponent();
    options.content.set (new PresetSaveDialog (mPresetManager), true);
    options.content->setSize(300, 200);
    options.launchAsync();
}

//==============================================================================

void PresetBar::presetChanged (const grape::presets::Preset& preset)
{
    updateCurrentPreset (preset);
}

//==============================================================================

} // namespace ui
} // namespace mbctrl


