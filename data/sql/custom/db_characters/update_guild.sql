-- fdd
-- ALTER TABLE IF NOT EXISTS guild ADD defaultName VARCHAR(24) NOT NULL DEFAULT '';
-- UPDATE guild SET defaultName = name;

CREATE TABLE IF NOT EXISTS guild_level_exp (
level int unsigned NOT NULL COMMENT 'Guild level',
exp int unsigned NOT NULL COMMENT 'Guild exp for level',
PRIMARY KEY (level)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;

INSERT INTO guild_level_exp (level, exp) VALUES
(1, 0),
(2, 2000),
(3, 4000),
(4, 6000),
(5, 8000),
(6, 10000),
(7, 12000),
(8, 14000),
(9, 16000),
(10, 18000),
(11, 20000),
(12, 22000),
(13, 24000),
(14, 26000),
(15, 28000),
(16, 30000),
(17, 32000),
(18, 34000),
(19, 36000),
(20, 38000),
(21, 40000),
(22, 42000),
(23, 44000),
(24, 46000),
(25, 48000)
ON DUPLICATE KEY UPDATE exp = VALUES(exp);

CREATE TABLE IF NOT EXISTS guild_level_invest_log (
guildId int unsigned NOT NULL,
playerGuid int unsigned NOT NULL,
playerName varchar(12) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
exp int unsigned NOT NULL,
datetime datetime DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;

CREATE TABLE IF NOT EXISTS guild_level_spell (
level int unsigned NOT NULL,
spellId int unsigned NOT NULL,
title varchar(70) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
PRIMARY KEY (level,spellId)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;