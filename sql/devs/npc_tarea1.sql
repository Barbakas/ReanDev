SET @Entry :=50001;
SET @ModelID :=27436;
SET @Name :='Izan Tremblay';
SET @Subname :='';
SET @NPCFLAG :=1; -- 1 is gossip - http://collab.kpsn.org/display/tc/creature_template#creature_template-npcflag
SET @ScriptName :='npc_tarea1';
DELETE FROM `creature_template` WHERE `entry`=@Entry;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES
(@Entry, 0, 0, 0, 0, 0, @ModelID, 0, 0, 0, @Name, @Subname, '', 0, 80, 80, 2, 35, 35, @NPCFLAG, 1, 1.14286, 1, 3, 10, 10, 0, 0, 1, 1000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 10000, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, @ScriptName, 1);

-- type texts: Say(12) Yell(14) Emote(16) Whisper(15) Boss Emote(41) Boss Whisper(42)
DELETE FROM `creature_text` WHERE `entry`=@Entry;
INSERT INTO `creature_text`(`entry`,`groupid`,`id`,`text`,`type`,`comment`)
VALUES (@Entry,0,0,'You\'re like an angel',15,CONCAT(@Name,' - SAY_ANGEL_TRANSFORM'));

INSERT INTO `creature_text`(`entry`,`groupid`,`id`,`text`,`type`,`comment`)
VALUES (@Entry,1,0,'Nobody spits in my face!',14,CONCAT(@Name,' - SAY_SPIT'));


INSERT INTO `creature_text`(`entry`,`groupid`,`id`,`text`,`type`,`comment`)
VALUES (@Entry,2,0,'You will be reduced to ashes',14,CONCAT(@Name,' - SAY_YELL_1'));

INSERT INTO `creature_text`(`entry`,`groupid`,`id`,`text`,`type`,`comment`)
VALUES (@Entry,3,0,'I will tear your face off',14,CONCAT(@Name,' - SAY_YELL_2'));


INSERT INTO `creature_text`(`entry`,`groupid`,`id`,`text`,`type`,`comment`)
VALUES (@Entry,4,0,'That\'s all you can do?',14,CONCAT(@Name,' - SAY_YELL_3'));

INSERT INTO `creature_text`(`entry`,`groupid`,`id`,`text`,`type`,`comment`)
VALUES (@Entry,5,0,'I will rip off you apart',14,CONCAT(@Name,' - SAY_YELL_4'));

INSERT INTO `creature_text`(`entry`,`groupid`,`id`,`text`,`type`,`comment`)
VALUES (@Entry,6,0,'As you wish',12,CONCAT(@Name,' - SAY_AGGRO'));

INSERT INTO `creature_text`(`entry`,`groupid`,`id`,`text`,`type`,`comment`)
VALUES (@Entry,7,0,'This ends now!',14,CONCAT(@Name,' - SAY_BERSERK'));

