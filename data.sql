PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

INSERT INTO accruals (
                         id,
                         date,
                         building,
                         rate,
                         ammount,
                         month
                     )
                     VALUES (
                         1,
                         '06.06.2017',
                         '10-n',
                         1,
                         2900,
                         6
                     );

INSERT INTO accruals (
                         id,
                         date,
                         building,
                         rate,
                         ammount,
                         month
                     )
                     VALUES (
                         2,
                         '06.06.2017',
                         '10-n',
                         1,
                         2900,
                         6
                     );

INSERT INTO accruals (
                         id,
                         date,
                         building,
                         rate,
                         ammount,
                         month
                     )
                     VALUES (
                         3,
                         '08.06.2017',
                         '10-n',
                         1,
                         580,
                         6
                     );

INSERT INTO accruals (
                         id,
                         date,
                         building,
                         rate,
                         ammount,
                         month
                     )
                     VALUES (
                         4,
                         '08.06.2017',
                         '6-n',
                         1,
                         1160,
                         6
                     );

INSERT INTO accruals (
                         id,
                         date,
                         building,
                         rate,
                         ammount,
                         month
                     )
                     VALUES (
                         5,
                         '08.06.2017',
                         '6-n',
                         1,
                         1160,
                         6
                     );

INSERT INTO accruals (
                         id,
                         date,
                         building,
                         rate,
                         ammount,
                         month
                     )
                     VALUES (
                         6,
                         '09.06.2017',
                         '5-n',
                         1,
                         1160,
                         6
                     );

INSERT INTO accruals (
                         id,
                         date,
                         building,
                         rate,
                         ammount,
                         month
                     )
                     VALUES (
                         7,
                         '10.06.2017',
                         '1-м',
                         1,
                         1160,
                         6
                     );

INSERT INTO accruals (
                         id,
                         date,
                         building,
                         rate,
                         ammount,
                         month
                     )
                     VALUES (
                         8,
                         '10.06.2017',
                         '10-n',
                         1,
                         580,
                         6
                     );

INSERT INTO accruals (
                         id,
                         date,
                         building,
                         rate,
                         ammount,
                         month
                     )
                     VALUES (
                         9,
                         '10.06.2017',
                         '5-n',
                         1,
                         0,
                         6
                     );

INSERT INTO accruals (
                         id,
                         date,
                         building,
                         rate,
                         ammount,
                         month
                     )
                     VALUES (
                         10,
                         '10.06.2017',
                         '6-n',
                         1,
                         1160,
                         6
                     );

INSERT INTO accruals (
                         id,
                         date,
                         building,
                         rate,
                         ammount,
                         month
                     )
                     VALUES (
                         11,
                         '10.06.2017',
                         '6-n',
                         1,
                         1160,
                         6
                     );

INSERT INTO accruals (
                         id,
                         date,
                         building,
                         rate,
                         ammount,
                         month
                     )
                     VALUES (
                         12,
                         '11.06.2017',
                         '2-m',
                         4,
                         12150,
                         6
                     );

					 INSERT INTO account (
                        id,
                        first_name,
                        second_name,
                        last_name
                    )
                    VALUES (
                        1,
                        'Петрова',
                        'Раиса',
                        'Генадевна'
                    );

INSERT INTO account (
                        id,
                        first_name,
                        second_name,
                        last_name
                    )
                    VALUES (
                        2,
                        'Полякова',
                        'Таисья',
                        'Леонидовна'
                    );

INSERT INTO account (
                        id,
                        first_name,
                        second_name,
                        last_name
                    )
                    VALUES (
                        3,
                        'Хохрякова',
                        'Раиса',
                        'Генадьевна'
                    );

INSERT INTO account (
                        id,
                        first_name,
                        second_name,
                        last_name
                    )
                    VALUES (
                        4,
                        'Васиильева',
                        'Нина',
                        'Александровна'
                    );

INSERT INTO account (
                        id,
                        first_name,
                        second_name,
                        last_name
                    )
                    VALUES (
                        5,
                        'Федоров',
                        'Максим',
                        'Сергеевич'
                    );

					INSERT INTO building (
                         id,
                         street,
                         number,
                         number_flat,
                         category
                     )
                     VALUES (
                         '10-n',
                         1,
                         12,
                         1,
                         'POPUL'
                     );

INSERT INTO building (
                         id,
                         street,
                         number,
                         number_flat,
                         category
                     )
                     VALUES (
                         '1-м',
                         4,
                         1,
                         1,
                         'POPUL'
                     );

INSERT INTO building (
                         id,
                         street,
                         number,
                         number_flat,
                         category
                     )
                     VALUES (
                         '5-n',
                         1,
                         5,
                         1,
                         'POPUL'
                     );

INSERT INTO building (
                         id,
                         street,
                         number,
                         number_flat,
                         category
                     )
                     VALUES (
                         '6-n',
                         1,
                         5,
                         1,
                         'POPUL'
                     );

INSERT INTO building (
                         id,
                         street,
                         number,
                         number_flat,
                         category
                     )
                     VALUES (
                         '2-m',
                         4,
                         2,
                         1,
                         'POPUL'
                     );

					 INSERT INTO category (
                         id,
                         value
                     )
                     VALUES (
                         'POPUL',
                         'Население'
                     );

INSERT INTO category (
                         id,
                         value
                     )
                     VALUES (
                         'ORG',
                         'Организация'
                     );

					 INSERT INTO number_of_people (
                                 id,
                                 building,
                                 value,
                                 active_from,
                                 active_to
                             )
                             VALUES (
                                 1,
                                 '10-n',
                                 1,
                                 '1.06.2017',
                                 NULL
                             );

INSERT INTO number_of_people (
                                 id,
                                 building,
                                 value,
                                 active_from,
                                 active_to
                             )
                             VALUES (
                                 2,
                                 '1-м',
                                 2,
                                 '31.05.2017',
                                 NULL
                             );

INSERT INTO number_of_people (
                                 id,
                                 building,
                                 value,
                                 active_from,
                                 active_to
                             )
                             VALUES (
                                 3,
                                 '6-n',
                                 2,
                                 '08.06.2017',
                                 NULL
                             );

INSERT INTO number_of_people (
                                 id,
                                 building,
                                 value,
                                 active_from,
                                 active_to
                             )
                             VALUES (
                                 4,
                                 '2-m',
                                 3,
                                 '11.06.2017',
                                 NULL
                             );
INSERT INTO owner (
                      id,
                      building,
                      account,
                      active_from,
                      active_to
                  )
                  VALUES (
                      1,
                      '10-n',
                      1,
                      NULL,
                      NULL
                  );

INSERT INTO owner (
                      id,
                      building,
                      account,
                      active_from,
                      active_to
                  )
                  VALUES (
                      2,
                      '1-м',
                      1,
                      '31.05.2017',
                      NULL
                  );

INSERT INTO owner (
                      id,
                      building,
                      account,
                      active_from,
                      active_to
                  )
                  VALUES (
                      3,
                      '6-n',
                      3,
                      '08.06.2017',
                      NULL
                  );

INSERT INTO owner (
                      id,
                      building,
                      account,
                      active_from,
                      active_to
                  )
                  VALUES (
                      4,
                      '2-m',
                      5,
                      '11.06.2017',
                      NULL
                  );
INSERT INTO payment (
                        id,
                        date,
                        building,
                        ammount,
                        month
                    )
                    VALUES (
                        1,
                        '06.06.2017',
                        '10-n',
                        2895,
                        6
                    );

INSERT INTO payment (
                        id,
                        date,
                        building,
                        ammount,
                        month
                    )
                    VALUES (
                        2,
                        '06.06.2017',
                        '10-n',
                        2895,
                        6
                    );

INSERT INTO payment (
                        id,
                        date,
                        building,
                        ammount,
                        month
                    )
                    VALUES (
                        3,
                        '08.06.2017',
                        '10-n',
                        575,
                        6
                    );

INSERT INTO payment (
                        id,
                        date,
                        building,
                        ammount,
                        month
                    )
                    VALUES (
                        4,
                        '08.06.2017',
                        '6-n',
                        1155,
                        6
                    );

INSERT INTO payment (
                        id,
                        date,
                        building,
                        ammount,
                        month
                    )
                    VALUES (
                        5,
                        '08.06.2017',
                        '6-n',
                        1155,
                        6
                    );

INSERT INTO payment (
                        id,
                        date,
                        building,
                        ammount,
                        month
                    )
                    VALUES (
                        6,
                        '08.07.2017',
                        '10-n',
                        1234,
                        7
                    );

INSERT INTO payment (
                        id,
                        date,
                        building,
                        ammount,
                        month
                    )
                    VALUES (
                        7,
                        '09.07.2017',
                        '10-n',
                        25,
                        7
                    );
INSERT INTO rate (
                     id,
                     per_cube,
                     cube_per_person,
                     created
                 )
                 VALUES (
                     1,
                     5.8,
                     3,
                     '30.05.2017'
                 );

INSERT INTO rate (
                     id,
                     per_cube,
                     cube_per_person,
                     created
                 )
                 VALUES (
                     2,
                     6,
                     3,
                     '01.06.2017'
                 );

INSERT INTO rate (
                     id,
                     per_cube,
                     cube_per_person,
                     created
                 )
                 VALUES (
                     3,
                     8.9,
                     3,
                     '02.06.2017'
                 );

INSERT INTO rate (
                     id,
                     per_cube,
                     cube_per_person,
                     created
                 )
                 VALUES (
                     4,
                     40.5,
                     3,
                     '08.06.2017'
                 );

INSERT INTO rate_building (
                              id,
                              building,
                              rate,
                              active_from,
                              active_to
                          )
                          VALUES (
                              1,
                              '10-n',
                              1,
                              '30.05.2017',
                              '11.06.2017'
                          );

INSERT INTO rate_building (
                              id,
                              building,
                              rate,
                              active_from,
                              active_to
                          )
                          VALUES (
                              2,
                              '6-n',
                              1,
                              '3.06.2017',
                              NULL
                          );

INSERT INTO rate_building (
                              id,
                              building,
                              rate,
                              active_from,
                              active_to
                          )
                          VALUES (
                              3,
                              '5-n',
                              1,
                              '2.06.2017',
                              NULL
                          );

INSERT INTO rate_building (
                              id,
                              building,
                              rate,
                              active_from,
                              active_to
                          )
                          VALUES (
                              4,
                              '1-м',
                              1,
                              '1.06.2017',
                              NULL
                          );

INSERT INTO rate_building (
                              id,
                              building,
                              rate,
                              active_from,
                              active_to
                          )
                          VALUES (
                              5,
                              '10-n',
                              2,
                              '11.06.2017',
                              NULL
                          );

INSERT INTO rate_building (
                              id,
                              building,
                              rate,
                              active_from,
                              active_to
                          )
                          VALUES (
                              6,
                              '2-m',
                              4,
                              '11.06.2017',
                              NULL
                          );
INSERT INTO street (
                       id,
                       name
                   )
                   VALUES (
                       1,
                       'Новая'
                   );

INSERT INTO street (
                       id,
                       name
                   )
                   VALUES (
                       2,
                       'Центральная'
                   );

INSERT INTO street (
                       id,
                       name
                   )
                   VALUES (
                       4,
                       'Молодежная'
                   );

COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
