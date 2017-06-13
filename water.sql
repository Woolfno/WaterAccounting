PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- Таблица: account
DROP TABLE IF EXISTS account;

CREATE TABLE account (
    id          INTEGER PRIMARY KEY AUTOINCREMENT,
    first_name  TEXT,
    second_name TEXT,
    last_name   TEXT
);

-- Таблица: accruals
DROP TABLE IF EXISTS accruals;

CREATE TABLE accruals (
    id       INTEGER     PRIMARY KEY AUTOINCREMENT,
    date     TEXT,
    building TEXT,
    rate     INTEGER,
    ammount  INTEGER,
    month    INTEGER (2) NOT NULL,
    FOREIGN KEY (
        rate
    )
    REFERENCES rate (id) 
);

-- Таблица: building
DROP TABLE IF EXISTS building;

CREATE TABLE building (
    id          TEXT    NOT NULL
                        PRIMARY KEY,
    street      INTEGER,
    number      INTEGER,
    number_flat INTEGER,
    category    TEXT,
    FOREIGN KEY (
        street
    )
    REFERENCES street (id),
    FOREIGN KEY (
        category
    )
    REFERENCES category (id) 
);

-- Таблица: category
DROP TABLE IF EXISTS category;

CREATE TABLE category (
    id    TEXT NOT NULL
               PRIMARY KEY,
    value TEXT
);

-- Таблица: number_of_people
DROP TABLE IF EXISTS number_of_people;

CREATE TABLE number_of_people (
    id          INTEGER PRIMARY KEY AUTOINCREMENT,
    building    TEXT    REFERENCES building (id),
    value       INTEGER,
    active_from TEXT,
    active_to   TEXT,
    FOREIGN KEY (
        building
    )
    REFERENCES building (id) 
);

-- Таблица: owner
DROP TABLE IF EXISTS owner;

CREATE TABLE owner (
    id          INTEGER PRIMARY KEY AUTOINCREMENT,
    building    INTEGER,
    account     INTEGER,
    active_from TEXT,
    active_to   TEXT,
    FOREIGN KEY (
        building
    )
    REFERENCES building (id),
    FOREIGN KEY (
        account
    )
    REFERENCES account (id) 
);

-- Таблица: payment
DROP TABLE IF EXISTS payment;

CREATE TABLE payment (
    id       INTEGER PRIMARY KEY AUTOINCREMENT,
    date     TEXT,
    building INTEGER,
    ammount  REAL,
    month    INTEGER NOT NULL,
    FOREIGN KEY (
        building
    )
    REFERENCES building (id) 
);

-- Таблица: rate
DROP TABLE IF EXISTS rate;

CREATE TABLE rate (
    id              INTEGER PRIMARY KEY AUTOINCREMENT,
    per_cube        REAL,
    cube_per_person REAL,
    created         TEXT
);

-- Таблица: rate_building
DROP TABLE IF EXISTS rate_building;

CREATE TABLE rate_building (
    id          INTEGER      NOT NULL
                             PRIMARY KEY AUTOINCREMENT,
    building    VARCHAR (10) NOT NULL,
    rate        INTEGER (10) NOT NULL,
    active_from DATE         NOT NULL,
    active_to   DATE,
    FOREIGN KEY (
        rate
    )
    REFERENCES rate (id),
    FOREIGN KEY (
        building
    )
    REFERENCES building (id) 
);

-- Таблица: street
DROP TABLE IF EXISTS street;

CREATE TABLE street (
    id   INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT
);

COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
