-- Keep a log of any SQL queries you execute as you solve the mystery.

Who the thief is,
What city the thief escaped to, and
Who the thief’s accomplice is who helped them escape

All you know is that the theft took place on July 28, 2021 and that it took place on Humphrey Street.

SELECT description FROM crime_scene_reports WHERE street = "Humphrey Street" AND month = 7 AND day = 28 LIMIT 1;

SELECT transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28;

5773159633


-- thief

SELECT * FROM people
    WHERE phone_number IN
        (SELECT caller FROM phone_calls
            WHERE caller IN
                (SELECT phone_number FROM people
                        WHERE license_plate IN
                            (SELECT license_plate FROM bakery_security_logs
                                WHERE year = 2021
                                    AND month = 7
                                    AND day = 28
                                    AND hour = 10
                                    AND minute <= 25
                                    AND minute >= 15
                                    AND activity = 'exit')
                INTERSECT
                SELECT phone_number FROM people WHERE id IN
                    (SELECT person_id FROM bank_accounts
                        WHERE account_number IN
                            (SELECT account_number FROM atm_transactions
                                WHERE atm_location = 'Leggett Street' AND year = 2021
                                    AND month = 7 AND day = 28 AND transaction_type = 'withdraw')))
                AND day = 28
                AND duration < 60)
INTERSECT
SELECT * FROM people
    WHERE passport_number IN
        (SELECT passport_number FROM passengers
            WHERE flight_id =
                (SELECT id FROM flights
                    WHERE year = 2021
                        AND month = 7
                        AND day = 29
                        AND origin_airport_id
                            IN (SELECT id FROM airports WHERE city = 'Fiftyville')
                        ORDER BY hour ASC, hour LIMIT 1))
        ORDER BY passport_number;


-- accomplice

SELECT * FROM people
    WHERE phone_number IN
        (SELECT receiver FROM phone_calls
            WHERE caller IN
                (SELECT phone_number FROM people
                    WHERE phone_number IN
                        (SELECT caller FROM phone_calls
                            WHERE caller IN
                                (SELECT phone_number FROM people
                                        WHERE license_plate IN
                                            (SELECT license_plate FROM bakery_security_logs
                                                WHERE year = 2021
                                                    AND month = 7
                                                    AND day = 28
                                                    AND hour = 10
                                                    AND minute <= 25
                                                    AND minute >= 15
                                                    AND activity = 'exit')
                                INTERSECT
                                SELECT phone_number FROM people WHERE id IN
                                    (SELECT person_id FROM bank_accounts
                                        WHERE account_number IN
                                            (SELECT account_number FROM atm_transactions
                                                WHERE atm_location = 'Leggett Street' AND year = 2021
                                                    AND month = 7 AND day = 28 AND transaction_type = 'withdraw')))
                                AND day = 28
                                AND duration < 60)
                INTERSECT
                SELECT phone_number FROM people
                    WHERE passport_number IN
                        (SELECT passport_number FROM passengers
                            WHERE flight_id =
                                (SELECT id FROM flights
                                    WHERE year = 2021
                                        AND month = 7
                                        AND day = 29
                                        AND origin_airport_id
                                            IN (SELECT id FROM airports WHERE city = 'Fiftyville')
                                        ORDER BY hour ASC, hour LIMIT 1)))
                AND day = 28
                AND duration < 60);


-- city

SELECT city FROM airports WHERE id =
    (SELECT destination_airport_id FROM flights
        WHERE year = 2021
            AND month = 7
            AND day = 29
            AND origin_airport_id
                IN (SELECT id FROM airports WHERE city = 'Fiftyville')
        ORDER BY hour ASC, hour LIMIT 1);
