/*
SQL RoG WoW				  
Desarrollado por:
Fecha: 23/9/2019
### Scripts Privados / Derechos Reservados RoG WoW ########
### Datos SQL ###########################################*/
SET @CREATURE  	:= 'Guard Captain Oakenshield';
SET @ENTRY 		:= '57198';
/*SET @MAP   		:= 530;       *//*(Outland)*/
/*SET @ZONE  		:= 6455;      *//*(Sunstrider Isle)*/
/*SET @AREA  		:= 3431;      *//*(Sunstrider Isle)*/
/*#######################################################*/


/* Step 1.1 Table  `creature_template` */
DELETE FROM `creature_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `difficulty_entry_4`, `difficulty_entry_5`, `difficulty_entry_6`, `difficulty_entry_7`, `difficulty_entry_8`, `difficulty_entry_9`, `difficulty_entry_10`, `difficulty_entry_11`, `difficulty_entry_12`, `difficulty_entry_13`, `difficulty_entry_14`, `difficulty_entry_15`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `npcflag2`, `speed_walk`, `speed_run`, `speed_swim`, `speed_fly`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES 
(@ENTRY, '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '41217', '0', '0', '0', @CREATURE, '', '', '0', '87', '87', '4', '0', '35', '35', '2', '0', '1', '1.14286', '0', '1.14286', '1', '0', '7326', '9786', '0', '29946', '1', '2000', '2000', '2', '32768', '2048', '0', '0', '0', '0', '0', '0', '0', '0', '0', '7', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '3', '1', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '57198', '0', '0', '', '16048');

/* Step 1.2 Table `creature_equip_template */
DELETE FROM `creature_equip_template` WHERE `entry`= 57198;
INSERT INTO `creature_equip_template` (`entry`, `itemEntry1`, `itemEntry2`, `itemEntry3`) VALUES 
('57198', '77370', '1985', '0'); /* [ItemEntry1(77370): THIS ITEM IS JUST VISUAL, DONT HAVE TEMPLATE] [ItemEntry2(1985): Monster - Shield, Large Wooden] */

/* Step 1.3 Table  creature_template_addon */
DELETE FROM creature_template_addon WHERE  `entry` = @ENTRY;
INSERT INTO `creature_template_addon` (`entry`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES 
(@ENTRY, '0', '0', '0', '1', '0', ''); 


/* Step 2.7 Table  `creature_model_info */
DELETE m1 FROM creature_template AS ct JOIN creature_model_info AS m1 ON ct.modelid1 = m1.modelid OR ct.modelid2 = m1.modelid OR ct.modelid3 = m1.modelid OR ct.modelid4 = m1.modelid WHERE entry = @ENTRY;
INSERT INTO `creature_model_info` (`modelid`,`bounding_radius`,`combat_reach`,`gender`,`modelid_other_gender`) VALUES 
('41217', '0.381944', '1.65', '0', '0'); 


/* Step 1.6 Table  `creature_text */
DELETE FROM  `creature_text` WHERE `entry`= @ENTRY;
/* Step 1.6 Table  `smart_scripts` */
DELETE FROM smart_scripts WHERE `entryorguid` = 57198 AND `source_type`= 0;
/* Step 1.7 Table  `creature */
DELETE FROM creature WHERE  `id` = @ENTRY;
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`, `currentwaypoint`,`curhealth`, `curmana`, `MovementType`, `npcflag`, `npcflag2`, `unit_flags`,`unit_flags2`,`dynamicflags`,`isActive`,`protec_anti_doublet`) VALUES 
(NULL, @ENTRY, '870', '5805', '5968', '1', '1', '0', '0', '-366.797', '1987.32', '126.045', '1.25945', '300', '0', '0', '1', '0', '0', '2', '0', '32768', '0', '0', '0', '0'), 
(NULL, @ENTRY, '870', '5805', '5969', '1', '65535', '0', '57198', '-204.776', '2201.1', '116.792', '3.94755', '300', '0', '0', '214985', '9310', '0', '0', '0', '0', '0', '0', '0', '0'); 

/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-366.797' AND `position_y` REGEXP '1987.32' AND `position_z` REGEXP '126.045' AND `phaseMask` = '1' AND `map` = '870');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-366.797' AND `position_y` REGEXP '1987.32' AND `position_z` REGEXP '126.045' AND `phaseMask` = '1' AND `map` = '870');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-204.776' AND `position_y` REGEXP '2201.1' AND `position_z` REGEXP '116.792' AND `phaseMask` = '65535' AND `map` = '870');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-204.776' AND `position_y` REGEXP '2201.1' AND `position_z` REGEXP '116.792' AND `phaseMask` = '65535' AND `map` = '870');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;


/*## Step 2: Creature Loots ##########################################*/

/* Step 2.2 Table  `creature_loot_currency */
DELETE FROM creature_loot_currency WHERE  `creature_id` = @ENTRY;
/* Step 2.1 Table  `creature_onkill_reputation */
DELETE FROM creature_onkill_reputation WHERE `creature_id` = @ENTRY;
/* Step 2.3 Table  `pickpocketing_loot_template */
DELETE FROM pickpocketing_loot_template WHERE `entry` = @ENTRY;
/* Step 2.4 Table  `skinning_loot_template */
DELETE FROM skinning_loot_template WHERE  `entry` = @ENTRY;
/*Creature Loot Template Items Data: Id - Quality - SellPrice - ItemLevel - RequiredLevel - Name */
/*
/*Pickpocketing Loot Template Items Data: Id - Quality - SellPrice - ItemLevel - RequiredLevel - Name */
/*
*/
/*Skinning Loot Template Items Data: Id - Quality - SellPrice - ItemLevel - RequiredLevel - Name */
/*
*/


/*## Step 3: Creature Extras ##########################################*/

/* Step 3.3 Table  `creature_summon_groups` */
DELETE FROM  `creature_summon_groups` WHERE `summonerId` = @ENTRY AND `summonerType` = 0;
/*## Step 4: Creature Gossip Menu Options #############################*/

/* Step 2.7 Table  `gossip_menu */
DELETE FROM gossip_menu WHERE  `entry` = 0;
/*## Step 5: Creature NPC Trainer / Vendor ############################*/

/* Step 2.0 Table  `npc_trainer */
DELETE FROM npc_trainer WHERE `entry` = @ENTRY;
/* Step 1.9 Table  `npc_vendor */
DELETE FROM npc_vendor WHERE  `entry` = @ENTRY;
/*## Step 6: Creature NPC Conditions ##################################*/

/* Step 6.9 Table `conditions` */
/*DELETE FROM  `conditions` WHERE `SourceTypeOrReferenceId` AND `SourceGroup`;
*/

/*## Step 7: Creature NPC Needs to Work ###############################*/

/* Step 2.2 Table  `creature_questrelation */
DELETE FROM  `creature_questrelation` WHERE `id`= @ENTRY;
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES 
('57198', '30625'),  /* Quest(30625): Students No More ,QuestMinLevel: 86 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('57198', '30626');  /* Quest(30626): Retreat! ,QuestMinLevel: 86 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 


/* Step 2.2 Table  `creature_involvedrelation */
DELETE FROM  `creature_involvedrelation` WHERE `id`= @ENTRY;
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES 
('57198', '30622'),  /* Quest(30622): The Swarm Begins ,QuestMinLevel: 86 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('57198', '30625');  /* Quest(30625): Students No More ,QuestMinLevel: 86 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 


/* Step 1.8 Table  `waypoints */
DELETE FROM waypoints WHERE  `entry` = @ENTRY;
/* Step 2.5 Table  `npc_spellclick_spells */
DELETE FROM npc_spellclick_spells WHERE  `npc_entry` = @ENTRY;
/* Step 2.6 Table  `pet_levelstats */
DELETE FROM pet_levelstats WHERE  `creature_entry` = @ENTRY;

