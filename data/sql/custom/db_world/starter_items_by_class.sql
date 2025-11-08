-- Таблица для хранения стартовых предметов по классам
DROP TABLE IF EXISTS `player_starter_items`;
CREATE TABLE `player_starter_items` (
    `class` TINYINT(3) UNSIGNED NOT NULL COMMENT 'ID класса персонажа',
    `itemId` MEDIUMINT(8) UNSIGNED NOT NULL COMMENT 'ID предмета',
    `count` TINYINT(3) UNSIGNED NOT NULL DEFAULT 1 COMMENT 'Количество предметов',
    `comment` VARCHAR(255) DEFAULT NULL COMMENT 'Комментарий',
    PRIMARY KEY (`class`, `itemId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COMMENT='Стартовые предметы для персонажей при первом входе';

-- Очистка таблицы
TRUNCATE TABLE `player_starter_items`;

-- Warrior (CLASS_WARRIOR = 1)
INSERT INTO `player_starter_items` (`class`, `itemId`, `count`, `comment`) VALUES
(1, 42949, 1, 'Наплечники'),
(1, 48685, 1, 'Нагрудник'),
(1, 42991, 2, 'Аксессуар'),
(1, 42945, 1, 'Оружие'),
(1, 50255, 1, 'Кольцо'),
(1, 41600, 4, 'Сумка');

-- Paladin (CLASS_PALADIN = 2)
INSERT INTO `player_starter_items` (`class`, `itemId`, `count`, `comment`) VALUES
(2, 42949, 1, 'Наплечники'),
(2, 48685, 1, 'Нагрудник'),
(2, 42991, 2, 'Аксессуар'),
(2, 42945, 1, 'Оружие'),
(2, 50255, 1, 'Кольцо'),
(2, 41600, 4, 'Сумка');

-- Hunter (CLASS_HUNTER = 3)
INSERT INTO `player_starter_items` (`class`, `itemId`, `count`, `comment`) VALUES
(3, 42950, 1, 'Наплечники'),
(3, 48677, 1, 'Нагрудник'),
(3, 42991, 2, 'Аксессуар'),
(3, 42943, 1, 'Оружие - Лук'),
(3, 42946, 1, 'Оружие - Посох'),
(3, 50255, 1, 'Кольцо'),
(3, 41600, 4, 'Сумка');

-- Rogue (CLASS_ROGUE = 4)
INSERT INTO `player_starter_items` (`class`, `itemId`, `count`, `comment`) VALUES
(4, 42952, 1, 'Наплечники'),
(4, 48689, 1, 'Нагрудник'),
(4, 42991, 2, 'Аксессуар'),
(4, 42944, 2, 'Оружие - Два кинжала'),
(4, 50255, 1, 'Кольцо'),
(4, 41600, 4, 'Сумка');

-- Priest (CLASS_PRIEST = 5)
INSERT INTO `player_starter_items` (`class`, `itemId`, `count`, `comment`) VALUES
(5, 42985, 1, 'Наплечники'),
(5, 48691, 1, 'Нагрудник'),
(5, 42992, 2, 'Аксессуар'),
(5, 42947, 1, 'Оружие - Посох'),
(5, 50255, 1, 'Кольцо'),
(5, 41600, 4, 'Сумка');

-- Death Knight (CLASS_DEATH_KNIGHT = 6)
INSERT INTO `player_starter_items` (`class`, `itemId`, `count`, `comment`) VALUES
(6, 42949, 1, 'Наплечники'),
(6, 48685, 1, 'Нагрудник'),
(6, 42991, 2, 'Аксессуар'),
(6, 42945, 1, 'Оружие'),
(6, 50255, 1, 'Кольцо'),
(6, 41600, 4, 'Сумка');

-- Shaman (CLASS_SHAMAN = 7)
INSERT INTO `player_starter_items` (`class`, `itemId`, `count`, `comment`) VALUES
(7, 42951, 1, 'Наплечники'),
(7, 48683, 1, 'Нагрудник'),
(7, 42992, 2, 'Аксессуар'),
(7, 42948, 1, 'Оружие - Булава'),
(7, 42947, 1, 'Оружие - Посох'),
(7, 50255, 1, 'Кольцо'),
(7, 41600, 4, 'Сумка');

-- Mage (CLASS_MAGE = 8)
INSERT INTO `player_starter_items` (`class`, `itemId`, `count`, `comment`) VALUES
(8, 42985, 1, 'Наплечники'),
(8, 48691, 1, 'Нагрудник'),
(8, 42992, 2, 'Аксессуар'),
(8, 42947, 1, 'Оружие - Посох'),
(8, 50255, 1, 'Кольцо'),
(8, 41600, 4, 'Сумка');

-- Warlock (CLASS_WARLOCK = 9)
INSERT INTO `player_starter_items` (`class`, `itemId`, `count`, `comment`) VALUES
(9, 42985, 1, 'Наплечники'),
(9, 48691, 1, 'Нагрудник'),
(9, 42992, 2, 'Аксессуар'),
(9, 42947, 1, 'Оружие - Посох'),
(9, 50255, 1, 'Кольцо'),
(9, 41600, 4, 'Сумка');

-- Druid (CLASS_DRUID = 11)
INSERT INTO `player_starter_items` (`class`, `itemId`, `count`, `comment`) VALUES
(11, 42984, 1, 'Наплечники (кожа)'),
(11, 48687, 1, 'Нагрудник (кожа)'),
(11, 42992, 2, 'Аксессуар (заклинатель)'),
(11, 42948, 1, 'Оружие - Булава'),
(11, 42952, 1, 'Наплечники (кожа, ловкость)'),
(11, 48689, 1, 'Нагрудник (кожа, ловкость)'),
(11, 42991, 2, 'Аксессуар (физ. урон)'),
(11, 48718, 1, 'Оружие - Древковое'),
(11, 50255, 1, 'Кольцо'),
(11, 41600, 4, 'Сумка');
