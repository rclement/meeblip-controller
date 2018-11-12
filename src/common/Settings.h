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
#include <grape/settings/Setting.h>
#include <vector>
#include <map>

//==============================================================================

namespace mbctrl {
namespace common {

//==============================================================================

enum class SettingId
{
    idMidiDevice,
    idMidiChannel,
    numSettingIds,
};

//==============================================================================

extern const std::map<SettingId, grape::settings::Setting> 	sSettings;
extern const std::vector<grape::settings::Setting>          sOrderedSettings;

//==============================================================================

typedef std::map<SettingId, float> SettingMapper;

//==============================================================================

} // namespace common
} // namespace mbctrl
