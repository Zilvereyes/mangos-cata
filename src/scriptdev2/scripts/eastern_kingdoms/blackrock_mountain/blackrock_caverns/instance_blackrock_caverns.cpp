/* This file is part of the ScriptDev2 Project. See AUTHORS file for Copyright information
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: instance_blackrock_caverns
SD%Complete: 10
SDComment: Placeholder
SDCategory: Blackrock Caverns
EndScriptData */

#include "precompiled.h"
#include "blackrock_caverns.h"

instance_blackrock_caverns::instance_blackrock_caverns(Map* pMap) : ScriptedInstance(pMap)
{
    Initialize();
};

void instance_blackrock_caverns::Initialize()
{
    memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
}

void instance_blackrock_caverns::OnCreatureCreate(Creature* pCreature)
{
    // ToDo: add Creature references here
}

void instance_blackrock_caverns::OnObjectCreate(GameObject* pGo)
{
    // ToDo: add Gameobject references here
}

void instance_blackrock_caverns::SetData(uint32 uiType, uint32 uiData)
{
    switch (uiType)
    {
        case TYPE_ROMOGG:
        case TYPE_CORLA:
        case TYPE_KARSH:
        case TYPE_BEAUTY:
        case TYPE_OBSIDIUS:
            m_auiEncounter[uiType] = uiData;
            break;
    }

    if (uiData == DONE)
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;
        saveStream << m_auiEncounter[0] << " " << m_auiEncounter[1] << " " << m_auiEncounter[2] << " "
                   << m_auiEncounter[3] << " " << m_auiEncounter[4];

        m_strInstData = saveStream.str();

        SaveToDB();
        OUT_SAVE_INST_DATA_COMPLETE;
    }
}

uint32 instance_blackrock_caverns::GetData(uint32 uiType) const
{
    if (uiType < MAX_ENCOUNTER)
        return m_auiEncounter[uiType];

    return 0;
}

void instance_blackrock_caverns::Load(const char* chrIn)
{
    if (!chrIn)
    {
        OUT_LOAD_INST_DATA_FAIL;
        return;
    }

    OUT_LOAD_INST_DATA(chrIn);

    std::istringstream loadStream(chrIn);
    loadStream >> m_auiEncounter[0] >> m_auiEncounter[1] >> m_auiEncounter[2] >> m_auiEncounter[3]
               >> m_auiEncounter[4];

    for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
    {
        if (m_auiEncounter[i] == IN_PROGRESS)
            m_auiEncounter[i] = NOT_STARTED;
    }

    OUT_LOAD_INST_DATA_COMPLETE;
}

InstanceData* GetInstanceData_instance_blackrock_caverns(Map* pMap)
{
    return new instance_blackrock_caverns(pMap);
}

void AddSC_instance_blackrock_caverns()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "instance_blackrock_caverns";
    pNewScript->GetInstanceData = &GetInstanceData_instance_blackrock_caverns;
    pNewScript->RegisterSelf();
}
