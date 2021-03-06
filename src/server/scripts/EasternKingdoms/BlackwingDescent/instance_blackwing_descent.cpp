#include "ScriptPCH.h"
#include "blackwing_descent.h"

#define MAX_ENCOUNTER 6

class instance_blackwing_descent : public InstanceMapScript
{
    public:
        instance_blackwing_descent() : InstanceMapScript("instance_blackwing_descent", 669) { }

        InstanceScript* GetInstanceScript(InstanceMap* pMap) const
        {
           return new instance_blackwing_descent_InstanceMapScript(pMap);
        }

        struct instance_blackwing_descent_InstanceMapScript : public InstanceScript
        {
            instance_blackwing_descent_InstanceMapScript(Map* pMap) : InstanceScript(pMap) 
            {
                SetBossNumber(MAX_ENCOUNTER);
                omnotronHealth = 0;
                uiBileotron800Active = 0;
                uiMagmawGUID = 0;
                uiMagmawHeadGUID = 0;
                uiMaloriakGUID = 0;
                uiAberCount = 18;
                uiChimaeronGUID = 0;
                uiBileotron800GUID = 0;
                uiAtramedesGUID = 0;
                uiInnerChamberDoorGUID = 0;
                uiNefarianGUID = 0;
                uiOnyxiaGUID = 0;
                uiNefarianFloorGUID = 0;
				uiThrallGUID = 0;
                memset(&m_uiOmnotronGUID, 0, sizeof(m_uiOmnotronGUID));
				countATRAMEDESGUARDSDEAD = 0;
				uiSPIRITOFANGERFORGEGUID = 0;
				uiSPIRITOFTHAURISSANGUID = 0;
				uiSPIRITOFIRONSTARGUID = 0;
				uiSPIRITOFBURNINGEYEGUID = 0;
				uiSPIRITOFCOREHAMMERGUID = 0;
				uiSPIRITOFANVILRAGEGUID = 0;
				uiSPIRITOFMOLTENFISTGUID = 0;
				uiSPIRITOFSHADOWFORGEGUID = 0;
				uiEVENTFIRE = 0;
            }

            void OnPlayerEnter(Player* player)
            {
                if (!uiTeamInInstance)
                    uiTeamInInstance = player->GetTeam();
            }

            void OnCreatureCreate(Creature* creature)
            {
                if (!uiTeamInInstance)
                {
                    Map::PlayerList const &players = instance->GetPlayers();
                    if (!players.isEmpty())
                        if (Player* player = players.begin()->getSource())
                            uiTeamInInstance = player->GetTeam();
                }

                switch(creature->GetEntry())
                {
                case NPC_MAGMAW:
                    uiMagmawGUID = creature->GetGUID();
                    break;
                case NPC_MAGMAW_HEAD:
                    uiMagmawHeadGUID = creature->GetGUID();
                    break;
                case NPC_OMNOTRON:
                    uiOmnotronControllerGUID = creature->GetGUID();
                    break;                    
                case NPC_ARCANOTRON:
                    m_uiOmnotronGUID[0] = creature->GetGUID();
                    break;
                case NPC_ELECTRON:
                    m_uiOmnotronGUID[1] = creature->GetGUID();
                    break;
                case NPC_MAGMATRON:
                    m_uiOmnotronGUID[2] = creature->GetGUID();
                    break;
                case NPC_TOXITRON:
                    m_uiOmnotronGUID[3] = creature->GetGUID();
                    break;
                case NPC_MALORIAK:
                    uiMaloriakGUID = creature->GetGUID();
                    break;
                case NPC_CHIMAERON:
                    uiChimaeronGUID = creature->GetGUID();
                    break;
                case NPC_BILE_O_TRON_800:
                    uiBileotron800GUID = creature->GetGUID();
                    break;
                case NPC_ATRAMEDES:
                    uiAtramedesGUID = creature->GetGUID();
                    break;
					// Nefarian
				case NPC_NEFARIAN:
					uiNefarian = creature->GetGUID();
					break;
                case NPC_LORD_VICTOR_NEFARIAN:
                    uiNefarianGUID = creature->GetGUID();
                    break;
                case NPC_ONYXIA:
                    uiOnyxiaGUID = creature->GetGUID();
					break;
				case NPC_THRALL:
					uiThrallGUID = creature->GetGUID();
                    break;
				case NPC_SPIRIT_OF_ANGERFORGE:
					uiSPIRITOFANGERFORGEGUID = creature->GetGUID();
					break;
				case NPC_SPIRIT_OF_THAURISSAN:
					uiSPIRITOFTHAURISSANGUID = creature->GetGUID();
					break;
				case NPC_SPIRIT_OF_IRONSTAR:
					uiSPIRITOFIRONSTARGUID = creature->GetGUID();
					break;
				case NPC_SPIRIT_OF_BURNINGEYE:
					uiSPIRITOFBURNINGEYEGUID = creature->GetGUID();
					break;
				case NPC_SPIRIT_OF_COREHAMMER:
					uiSPIRITOFCOREHAMMERGUID = creature->GetGUID();
					break;
				case NPC_SPIRIT_OF_ANVILRAGE:
					uiSPIRITOFANVILRAGEGUID = creature->GetGUID();
					break;
				case NPC_SPIRIT_OF_MOLTENFIST:
					uiSPIRITOFMOLTENFISTGUID = creature->GetGUID();
					break;
				case NPC_SPIRIT_OF_SHADOWFORGE:
					uiSPIRITOFSHADOWFORGEGUID = creature->GetGUID();
					break;
				case NPC_EVENTFIRE:
					uiEVENTFIRE = creature->GetGUID();
                }				
            }

            void OnGameObjectCreate(GameObject *go)
            {
                switch (go->GetEntry())
                {
                case GO_INNER_CHAMBER_DOOR:
                    uiInnerChamberDoorGUID = go->GetGUID();
					HandleGameObject(uiInnerChamberDoorGUID, false, go);
					go->setActive(false);
					if (GetBossState(DATA_OMNOTRON) == DONE && GetBossState(DATA_MAGMAW) == DONE){
						go->setActive(true);
						HandleGameObject(uiInnerChamberDoorGUID, true, go);
					}
						
                    break;
				case GOB_ONYXIA_PLATFORM:
                    uiNefarianFloorGUID = go->GetGUID();
                    break;
                }
            }
            
            void OnGameObjectRemove(GameObject *go, bool)
            {
                switch (go->GetEntry())
                {
                case GO_INNER_CHAMBER_DOOR:
				case GOB_ONYXIA_PLATFORM:
                    break;
                default:
                    break;
                }
            }

            uint64 GetData64(uint32 type)
            {
                switch (type)
                {
					case DATA_MAGMAW:
						return uiMagmawGUID;
					case DATA_MAGMAW_HEAD:
						return uiMagmawHeadGUID;
					case DATA_OMNOTRON:
						return uiOmnotronControllerGUID;
					case DATA_ARCANOTRON:
						return m_uiOmnotronGUID[0];
					case DATA_ELECTRON:
						return m_uiOmnotronGUID[1];
					case DATA_MAGMATRON:
						return m_uiOmnotronGUID[2];
					case DATA_TOXITRON:
						return m_uiOmnotronGUID[3];
					case DATA_MALORIAK:
						return uiMaloriakGUID;
					case DATA_CHIMAERON:
						return uiChimaeronGUID;
					case DATA_BILE_O_TRON_800:
						return uiBileotron800GUID;
					case DATA_ATRAMEDES:
						return uiAtramedesGUID;
					case DATA_INNER_CHAMBER_DOOR:
						return uiInnerChamberDoorGUID;
					case DATA_NEFARIAN:
						return uiNefarian;
					case DATA_NEFARIAN_LORD:
						return uiNefarianGUID;
					case DATA_ONYXIA:
						return uiOnyxiaGUID;
					case DATA_NEFARIAN_FLOOR:
						return uiNefarianFloorGUID;
					case DATA_THRALL:
						return uiThrallGUID;
					case DATA_SPIRIT_OF_ANGERFORGE:
						return uiSPIRITOFANGERFORGEGUID;
					case DATA_SPIRIT_OF_THAURISSAN:
						return uiSPIRITOFTHAURISSANGUID;						
					case DATA_SPIRIT_OF_IRONSTAR:
						return uiSPIRITOFIRONSTARGUID;						
					case DATA_SPIRIT_OF_BURNINGEYE:
						return uiSPIRITOFBURNINGEYEGUID;						
					case DATA_SPIRIT_OF_COREHAMMER:
						return uiSPIRITOFCOREHAMMERGUID;						
					case DATA_SPIRIT_OF_ANVILRAGE:
						return uiSPIRITOFANVILRAGEGUID;						
					case DATA_SPIRIT_OF_MOLTENFIST:
						return uiSPIRITOFMOLTENFISTGUID;						
					case DATA_SPIRIT_OF_SHADOWFORGE:
						return uiSPIRITOFSHADOWFORGEGUID;						
					case DATA_EVENTFIRE:
						return uiEVENTFIRE;
                }
                return 0;
            }

            uint32 GetData(uint32 type)
            {
                switch (type)
                {
                case DATA_HEALTH_OMNOTRON_SHARED:
                    return omnotronHealth;
                    break;
                case DATA_MALORIAK_ABERRATIONS:
                    return uiAberCount;
                    break;
                case DATA_BILE_O_TRON_800:
                    return uiBileotron800Active;
                    break;
                }
                return 0;
            }

            bool SetBossState(uint32 type, EncounterState state)
            {
                if (!InstanceScript::SetBossState(type, state))
                    return false;
				if (state == DONE){
					switch (type)
					{
						case DATA_OMNOTRON:
							if (GetBossState(DATA_MAGMAW) == DONE){
								GameObject* go = instance->GetGameObject(uiInnerChamberDoorGUID);
								go->setActive(true);
								HandleGameObject(uiInnerChamberDoorGUID, true);
							}
								
							break;
						case DATA_MAGMAW:
							if (GetBossState(DATA_OMNOTRON) == DONE){
								GameObject* go = instance->GetGameObject(uiInnerChamberDoorGUID);
								go->setActive(true);
								HandleGameObject(uiInnerChamberDoorGUID, true);
							}
								
							break;
						case DATA_MALORIAK:
							break;
						case DATA_CHIMAERON:
							break;
						case DATA_ATRAMEDES:
							if (GameObject* onyxiaPlatform = instance->GetGameObject(uiNefarianFloorGUID))
								onyxiaPlatform->SetPhaseMask(PHASEMASK_NORMAL, true);
							break;
						case DATA_NEFARIAN:
							break;						
						default:
							break;
					}
				}
                
                return true;
            }

            void SetData(uint32 type, uint32 data)
            {
                switch (type)
                {
					case DATA_HEALTH_OMNOTRON_SHARED:
						omnotronHealth = data;
						break;
					case DATA_MALORIAK_ABERRATIONS:
						uiAberCount = data;
						break;
					case DATA_BILE_O_TRON_800:
						uiBileotron800Active = data;
						break;	
					case DATA_ATRAMEDES_READY:
						if (Creature* atramedes = instance->GetCreature(uiAtramedesGUID))
							atramedes->AI()->DoAction(6);
                }
            }

            bool CheckRequiredBosses(uint32 bossId, Player const* player = NULL) const
            {
                if (player && player->isGameMaster())
                    return true;
            
                switch (bossId)
                {
                case DATA_CHIMAERON:
                case DATA_MALORIAK:
                case DATA_ATRAMEDES:
                    if (GetBossState(DATA_MAGMAW) != DONE ||
                        GetBossState(DATA_OMNOTRON) != DONE)
                        return false;
                    break;
                case DATA_NEFARIAN:
                    if (GetBossState(DATA_MAGMAW) != DONE ||
                        GetBossState(DATA_OMNOTRON) != DONE ||
                        GetBossState(DATA_MALORIAK) != DONE ||
                        GetBossState(DATA_CHIMAERON) != DONE ||
                        GetBossState(DATA_ATRAMEDES) != DONE)
                        return false;
                default:   
                    break;
                }
                return true;
            }

            std::string GetSaveData()
            {
                OUT_SAVE_INST_DATA;

                std::string str_data;

                std::ostringstream saveStream;
                saveStream << "B D " << GetBossSaveData();

                str_data = saveStream.str();

                OUT_SAVE_INST_DATA_COMPLETE;
                return str_data;
            }

            void Load(const char* in)
            {
                if (!in)
                {
                    OUT_LOAD_INST_DATA_FAIL;
                    return;
                }

                OUT_LOAD_INST_DATA(in);

                char dataHead1, dataHead2;

                std::istringstream loadStream(in);
                loadStream >> dataHead1 >> dataHead2;

                if (dataHead1 == 'B' && dataHead2 == 'D')
                {
                    for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                    {
                        uint32 tmpState;
                        loadStream >> tmpState;
                        if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                            tmpState = NOT_STARTED;
                        SetBossState(i, EncounterState(tmpState));
                    }
                } 
                else OUT_LOAD_INST_DATA_FAIL;

                OUT_LOAD_INST_DATA_COMPLETE;
            }

            private:
                uint32 omnotronHealth;
                uint32 uiAberCount;
                uint32 uiBileotron800Active;
                uint64 uiMagmawGUID;
                uint64 uiMagmawHeadGUID;
                uint64 uiMaloriakGUID;
                uint64 m_uiOmnotronGUID[4];
                uint64 uiOmnotronControllerGUID;
                uint64 uiChimaeronGUID;
                uint64 uiBileotron800GUID;
                uint64 uiAtramedesGUID;
                uint64 uiInnerChamberDoorGUID;
                uint64 uiNefarianGUID;
                uint64 uiOnyxiaGUID;
                uint64 uiNefarianFloorGUID;
                uint32 uiTeamInInstance;
				uint32 uiNefarian;
				uint32 uiThrallGUID;
				uint32 uiSPIRITOFANGERFORGEGUID; 
				uint32 uiSPIRITOFTHAURISSANGUID;
				uint32 uiSPIRITOFIRONSTARGUID;
				uint32 uiSPIRITOFBURNINGEYEGUID;
				uint32 uiSPIRITOFCOREHAMMERGUID;
				uint32 uiSPIRITOFANVILRAGEGUID;
				uint32 uiSPIRITOFMOLTENFISTGUID;
				uint32 uiSPIRITOFSHADOWFORGEGUID;
				uint32 uiEVENTFIRE;
				uint8 countATRAMEDESGUARDSDEAD;
        };
};

void AddSC_instance_blackwing_descent()
{
    new instance_blackwing_descent();
}