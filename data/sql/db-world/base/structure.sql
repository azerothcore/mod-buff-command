-- STRUCTURE
DROP TABLE IF EXISTS `player_buff`;
CREATE TABLE `player_buff`  (
  `spellid` int(10) NOT NULL COMMENT 'Spell ID',
  `comment` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL,
  PRIMARY KEY (`spellid`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- DATA
INSERT INTO `player_buff` VALUES (25898, NULL);
INSERT INTO `player_buff` VALUES (48074, NULL);
INSERT INTO `player_buff` VALUES (48162, NULL);
INSERT INTO `player_buff` VALUES (48470, NULL);
INSERT INTO `player_buff` VALUES (57623, NULL);
INSERT INTO `player_buff` VALUES (61316, NULL);

-- COMMAND
INSERT INTO `command`(`name`, `security`, `help`) VALUES ('buff', 0, 'Syntax: .buff. Buff player.\r\n.buff reload - reload player_buff table.');
