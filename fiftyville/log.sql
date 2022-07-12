-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Step1, Query the crime_scene_reports TABLE to get the ID and details
-- command:
SELECT id, description FROM crime_scene_reports
WHERE year = 2021 AND month = 7 AND day = 28 AND street LIKE 'Humphrey%';
-- answer: FROM the following two results, the id:295 was choose
    -- | 295 | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
    -- Interviews were conducted today with three witnesses
    -- who were present at the time – each of their interview transcripts mentions the bakery. |
    -- | 297 | Littering took place at 16:36. No known witnesses. |
-- infer:
    -- time : 10:15am
    -- the key place : bakery
    -- the number of witness : 3

-- What did the interviewer say?
-- Unable to find a connection
-- Query bakery logs to find bakery bread crumbs

-- Step2, Take your cues from interviews
-- command:
SELECT * FROM interviews
WHERE year = 2021
AND month = 7
AND day = 28
AND transcript LIKE '%thief%';
-- answer:
--| 161 | Ruth    | 2021 | 7     | 28  |
--Sometime within ten minutes of the theft,
--I saw the thief get into a car in the bakery parking lot and drive away.
--If you have security footage from the bakery parking lot,
--you might want to look for cars that left the parking lot in that time frame.|
--| 162 | Eugene  | 2021 | 7     | 28  |
--I don't know the thief's name, but it was someone I recognized.
--Earlier this morning, before I arrived at Emma's bakery,
--I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money. |
--| 163 | Raymond | 2021 | 7     | 28  |
--As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
--In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
--The thief then asked the person on the other end of the phone to purchase the flight ticket. |

-- Step3, Query the license_plate from bakery_security_logs
-- command:
SELECT * FROM bakery_security_logs
WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute < 35 AND activity LIKE 'exit';
-- answer: Look for people who don't follow normal procedures
-- +-----+------+-------+-----+------+--------+----------+---------------+
-- | id  | year | month | day | hour | minute | activity | license_plate |
-- +-----+------+-------+-----+------+--------+----------+---------------+
-- | 260 | 2021 | 7     | 28  | 10   | 16     | exit     | 5P2BI95       |
-- | 261 | 2021 | 7     | 28  | 10   | 18     | exit     | 94KL13X       |
-- | 262 | 2021 | 7     | 28  | 10   | 18     | exit     | 6P58WS2       |
-- | 263 | 2021 | 7     | 28  | 10   | 19     | exit     | 4328GD8       |
-- | 264 | 2021 | 7     | 28  | 10   | 20     | exit     | G412CB7       |
-- | 265 | 2021 | 7     | 28  | 10   | 21     | exit     | L93JTIZ       |
-- | 266 | 2021 | 7     | 28  | 10   | 23     | exit     | 322W7JE       |
-- | 267 | 2021 | 7     | 28  | 10   | 23     | exit     | 0NTHK55       |
-- +-----+------+-------+-----+------+--------+----------+---------------+

-- Step4, Query the people from people TABLE
-- command:
SELECT * FROM people
WHERE license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7
AND day = 28 AND hour = 10 AND minute < 35 AND activity LIKE 'exit');
-- answer:
-- +--------+---------+----------------+-----------------+---------------+
-- |   id   |  name   |  phone_number  | passport_number | license_plate |
-- +--------+---------+----------------+-----------------+---------------+
-- | 221103 | Vanessa | (725) 555-4692 | 2963008352      | 5P2BI95       |
-- | 243696 | Barry   | (301) 555-4174 | 7526138472      | 6P58WS2       |
-- | 396669 | Iman    | (829) 555-5269 | 7049073643      | L93JTIZ       |
-- | 398010 | Sofia   | (130) 555-0289 | 1695452385      | G412CB7       |
-- | 467400 | Luca    | (389) 555-5198 | 8496433585      | 4328GD8       |
-- | 514354 | Diana   | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 560886 | Kelsey  | (499) 555-9472 | 8294398571      | 0NTHK55       |
-- | 686048 | Bruce   | (367) 555-5533 | 5773159633      | 94KL13X       |
-- +--------+---------+----------------+-----------------+---------------+
--
--
-- Step5, Query someone whose bank_account havs some change -- on Leggett Street -- withdrawing
-- command:
SELECT account_number FROM atm_transactions
WHERE year = 2021 AND month = 7 AND day = 28 AND transaction_type LIKE 'withdraw%'
AND atm_location LIKE 'Leggett Street';
-- answer:
-- +-----+----------------+------+-------+-----+----------------+------------------+--------+
-- | id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
-- +-----+----------------+------+-------+-----+----------------+------------------+--------+
-- | 246 | 28500762       | 2021 | 7     | 28  | Leggett Street | withdraw         | 48     |
-- | 264 | 28296815       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
-- | 266 | 76054385       | 2021 | 7     | 28  | Leggett Street | withdraw         | 60     |
-- | 267 | 49610011       | 2021 | 7     | 28  | Leggett Street | withdraw         | 50     |
-- | 269 | 16153065       | 2021 | 7     | 28  | Leggett Street | withdraw         | 80     |
-- | 288 | 25506511       | 2021 | 7     | 28  | Leggett Street | withdraw         | 20     |
-- | 313 | 81061156       | 2021 | 7     | 28  | Leggett Street | withdraw         | 30     |
-- | 336 | 26013199       | 2021 | 7     | 28  | Leggett Street | withdraw         | 35     |
-- +-----+----------------+------+-------+-----+----------------+------------------+--------+
--
-- command:
SELECT * FROM bank_accounts,people WHERE bank_accounts.person_id = people.id AND account_number IN
(SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND transaction_type
LIKE 'withdraw%' AND atm_location LIKE 'Leggett Street') AND license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28
AND hour = 10 AND minute < 35 AND activity LIKE 'exit');
-- answer:
-- +----------------+-----------+---------------+--------+-------+----------------+-----------------+---------------+
-- | account_number | person_id | creation_year |   id   | name  |  phone_number  | passport_number | license_plate |
-- +----------------+-----------+---------------+--------+-------+----------------+-----------------+---------------+
-- | 49610011       | 686048    | 2010          | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
-- | 26013199       | 514354    | 2012          | 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
-- | 25506511       | 396669    | 2014          | 396669 | Iman  | (829) 555-5269 | 7049073643      | L93JTIZ       |
-- | 28500762       | 467400    | 2014          | 467400 | Luca  | (389) 555-5198 | 8496433585      | 4328GD8       |
-- +----------------+-----------+---------------+--------+-------+----------------+-----------------+---------------+


-- Step6, find the call
-- command:
SELECT * FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND caller IN
(SELECT phone_number FROM bank_accounts,people WHERE bank_accounts.person_id = people.id AND account_number IN
(SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28
AND transaction_type LIKE 'withdraw%' AND atm_location LIKE 'Leggett Street') AND license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10
AND minute < 35 AND activity LIKE 'exit'));
-- answer:
-- +-----+----------------+----------------+------+-------+-----+----------+
-- | id  |     caller     |    receiver    | year | month | day | duration |
-- +-----+----------------+----------------+------+-------+-----+----------+
-- | 233 | (367) 555-5533 | (375) 555-8161 | 2021 | 7     | 28  | 45       |
-- | 255 | (770) 555-1861 | (725) 555-3243 | 2021 | 7     | 28  | 49       |
-- +-----+----------------+----------------+------+-------+-----+----------+

-- command:
SELECT * FROM people WHERE phone_number IN
(SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND caller IN
(SELECT phone_number FROM bank_accounts,people WHERE bank_accounts.person_id = people.id AND account_number IN
(SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28
AND transaction_type LIKE 'withdraw%' AND atm_location LIKE 'Leggett Street') AND license_plate IN
(SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10
AND minute < 35 AND activity LIKE 'exit')));
-- answer
-- +--------+--------+----------------+-----------------+---------------+
-- |   id   |  name  |  phone_number  | passport_number | license_plate |
-- +--------+--------+----------------+-----------------+---------------+
-- | 847116 | Philip | (725) 555-3243 | 3391710505      | GW362R6       |
-- | 864400 | Robin  | (375) 555-8161 |                 | 4V16VO0       |
-- +--------+--------+----------------+-----------------+---------------+

-- Step7, find the flight
-- command:
SELECT * FROM flights,passengers
WHERE flights.id = passengers.flight_id
AND flight_id IN (SELECT flight_id FROM passengers WHERE passport_number IN
(SELECT passport_number FROM bank_accounts,people WHERE bank_accounts.person_id = people.id
AND account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021
AND month = 7 AND day = 28 AND transaction_type LIKE 'withdraw%' AND atm_location LIKE 'Leggett Street')
AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021
AND month = 7 AND day = 28 AND hour = 10 AND minute < 35 AND activity LIKE 'exit')))
AND year = 2021 AND month = 7 AND day = 29;
-- answer:
-- +----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+
-- | id | origin_airport_id | destination_airport_id | year | month | day | hour | minute | flight_id | passport_number | seat |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+
-- | 18 | 8                 | 6                      | 2021 | 7     | 29  | 16   | 0      | 18        | 2835165196      | 9C   |
-- | 18 | 8                 | 6                      | 2021 | 7     | 29  | 16   | 0      | 18        | 6131360461      | 2C   |
-- | 18 | 8                 | 6                      | 2021 | 7     | 29  | 16   | 0      | 18        | 3231999695      | 3C   |
-- | 18 | 8                 | 6                      | 2021 | 7     | 29  | 16   | 0      | 18        | 3592750733      | 4C   |
-- | 18 | 8                 | 6                      | 2021 | 7     | 29  | 16   | 0      | 18        | 2626335085      | 5D   |
-- | 18 | 8                 | 6                      | 2021 | 7     | 29  | 16   | 0      | 18        | 6117294637      | 6B   |
-- | 18 | 8                 | 6                      | 2021 | 7     | 29  | 16   | 0      | 18        | 2996517496      | 7A   |
-- | 18 | 8                 | 6                      | 2021 | 7     | 29  | 16   | 0      | 18        | 3915621712      | 8D   |
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 7214083635      | 2A   |
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 1695452385      | 3B   |
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 5773159633      | 4A   |
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 1540955065      | 5C   |
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 8294398571      | 6C   |
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 1988161715      | 6D   |
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 9878712108      | 7A   |
-- | 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     | 36        | 8496433585      | 7B   |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+-----------+-----------------+------+
--
-- command:
SELECT abbreviation, full_name, city FROM airports WHERE id = 4;
-- answer:
-- +---------------+
-- |     city      |
-- +---------------+
-- | New York City |
-- +---------------+

-- Finally.
-- Thief is Bruce;
-- To New York City;
-- Accomplice is Robin.