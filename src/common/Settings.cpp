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

#include <common/Settings.h>
#include <grape/helpers/Helpers.h>

//==============================================================================

namespace mbctrl {
namespace common {

//==============================================================================

const std::map<SettingId, grape::settings::Setting> sSettings =
{
    {
        SettingId::idUseExternalMidi,
        {
            "user-external-midi",
            "Use External MIDI",
            false,
            grape::helpers::varValueToText,
            grape::helpers::varTextToValue
        }
    },
    {
        SettingId::idMidiDevice,
        {
            "midi-device",
            "MIDI Device",
            "",
            grape::helpers::varValueToText,
            grape::helpers::varTextToValue
        }
    },
    {
        SettingId::idMidiChannel,
        {
            "midi-channel",
            "MIDI Channel",
            1,
            grape::helpers::varValueToText,
            grape::helpers::varTextToValue
        }
    }
};

const std::vector<grape::settings::Setting> sOrderedSettings =
{{
    sSettings.at (SettingId::idMidiDevice),
    sSettings.at (SettingId::idMidiChannel),
}};

//==============================================================================

} // namespace common
} // namespace mbctrl
