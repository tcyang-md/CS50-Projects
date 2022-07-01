-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Get descriptions containing the keyword duck
SELECT year, month, day, description FROM crime_scene_reports WHERE description LIKE '%duck%';
-- 7/28/2021, 10:15 am at Humphrey Street bakery, 3 witnesses, all mentioned bakery

-- get all interview transcripts on 7/28/2021
SELECT name, transcript FROM interviews WHERE year = 2021 and month = 7 and day = 28 and transcript LIKE '%bakery%';
-- look at cars that left the parking lot around 10:15 am in security footage, within 10 minutes of theft
-- theif withdrew money before 10:15 am at ATM on Leggett Street
-- call around 10:15 am, less than minute long, earliest flight out of Fiftyville on 7/29/2021, purchased flight ticket

-- check bakery_security_logs for exits around 10:15 am to get license plate and get their names matched
SELECT DISTINCT name, bakery_security_logs.hour, bakery_security_logs.minute, people.license_plate FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE people.license_plate in
(SELECT license_plate FROM bakery_security_logs WHERE year = 2021 and month = 7 and day = 28 and activity = 'exit' and hour <= 11 and hour >=10
) and bakery_security_logs.hour = 10 ORDER BY name;
-- +---------+------+--------+---------------+
-- |  name   | hour | minute | license_plate |
-- +---------+------+--------+---------------+
-- | Barry   | 10   | 18     | 6P58WS2       |
-- | Bruce   | 10   | 18     | 94KL13X       |
-- | Diana   | 10   | 23     | 322W7JE       |
-- | Iman    | 10   | 21     | L93JTIZ       |
-- | Kelsey  | 10   | 23     | 0NTHK55       |
-- | Luca    | 10   | 19     | 4328GD8       |
-- | Sofia   | 10   | 20     | G412CB7       |
-- | Taylor  | 10   | 35     | 1106N58       |
-- | Vanessa | 10   | 16     | 5P2BI95       |
-- +---------+------+--------+---------------+

-- check ATM withdrawal on Leggett Street before 10:15 am
SELECT bank_accounts.person_id, bank_accounts.account_number FROM atm_transactions
JOIN bank_accounts ON bank_accounts.account_number = atm_transactions.account_number
WHERE year = 2021 and month = 7 and day = 28 and atm_location = 'Leggett Street' and transaction_type = 'withdraw';
-- +-----------+----------------+
-- | person_id | account_number |
-- +-----------+----------------+
-- | 467400    | 28500762       |
-- | 395717    | 28296815       |
-- | 449774    | 76054385       |
-- | 686048    | 49610011       |
-- | 458378    | 16153065       |
-- | 396669    | 25506511       |
-- | 438727    | 81061156       |
-- | 514354    | 26013199       |
-- +-----------+----------------+

-- check phone calls made on 7/28/2021 made by the people from our list that lasted less than a minute
SELECT DISTINCT caller FROM phone_calls WHERE year = 2021 and month = 7 and day = 28 and duration <= 60 ORDER BY caller;
-- +----------------+
-- |     caller     |
-- +----------------+
-- | (031) 555-6622 |
-- | (130) 555-0289 |
-- | (286) 555-6063 |
-- | (338) 555-6650 |
-- | (367) 555-5533 |
-- | (499) 555-9472 |
-- | (609) 555-5876 |
-- | (770) 555-1861 |
-- | (826) 555-1652 |
-- +----------------+

-- caller ID of the phone numbers that went out on 7/28/2021 that lasted less than a minute
SELECT DISTINCT people.name, people.phone_number FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE phone_number in (SELECT DISTINCT caller FROM phone_calls WHERE year = 2021 and month = 7 and day = 28 and duration <= 60 ORDER BY caller) ORDER BY name;
-- +---------+----------------+
-- |  name   |  phone_number  |
-- +---------+----------------+
-- | Benista | (338) 555-6650 |
-- | Bruce   | (367) 555-5533 |
-- | Carina  | (031) 555-6622 |
-- | Diana   | (770) 555-1861 |
-- | Kathryn | (609) 555-5876 |
-- | Kelsey  | (499) 555-9472 |
-- | Kenny   | (826) 555-1652 |
-- | Sofia   | (130) 555-0289 |
-- | Taylor  | (286) 555-6063 |
-- +---------+----------------+

-- based on the data from the parking lot and the phone call data, we can say that these are the leftover suspects
SELECT name, phone_number, license_plate, passport_number FROM people WHERE
name = 'Bruce' or
name = 'Diana' or
name = 'Kelsey' or
name = 'Sofia' or
name = 'Taylor'
ORDER BY name;
-- +--------+----------------+---------------+-----------------+
-- |  name  |  phone_number  | license_plate | passport_number |
-- +--------+----------------+---------------+-----------------+
-- | Bruce  | (367) 555-5533 | 94KL13X       | 5773159633      |
-- | Diana  | (770) 555-1861 | 322W7JE       | 3592750733      |
-- | Kelsey | (499) 555-9472 | 0NTHK55       | 8294398571      |
-- | Sofia  | (130) 555-0289 | G412CB7       | 1695452385      |
-- | Taylor | (286) 555-6063 | 1106N58       | 1988161715      |
-- +--------+----------------+---------------+-----------------+

-- fiftyville id is 8
SELECT id FROM airports WHERE city = 'Fiftyville';
-- check flights out of fiftyville on 7/29/2021 first in the morning
SELECT id, hour, minute, origin_airport_id, destination_airport_id FROM flights WHERE year = 2021 and month = 7 and day = 29 and origin_airport_id = 8 ORDER BY hour, minute;
-- earliest flight is 8:20 in the morning id of 4

-- check passengers on flight 4 that have matching passport number
SELECT passport_number FROM passengers WHERE flight_id = 4;
-- check passengers on flight 4 that have matching passport numbers to list of suspects that we already have
SELECT people.name FROM people
JOIN passengers ON passengers.passport_number = people.passport_number
WHERE passengers.passport_number = (
SELECT passport_number FROM people WHERE
name = 'Bruce' or
name = 'Diana' or
name = 'Kelsey' or
name = 'Sofia' or
name = 'Taylor'
ORDER BY name
);
-- Bruce is our man

-- destination of our flight is airport 4
SELECT city FROM airports WHERE id = 4;
-- Bruce was trying to go to Chicago

-- Who was bruce trying to contact?
SELECT DISTINCT caller, receiver FROM phone_calls WHERE year = 2021 and month = 7 and day = 28 and duration <= 60 ORDER BY caller;
-- +----------------+----------------+
-- |     caller     |    receiver    |
-- +----------------+----------------+
-- | (031) 555-6622 | (910) 555-3251 |
-- | (130) 555-0289 | (996) 555-8899 |
-- | (286) 555-6063 | (676) 555-6554 |
-- | (338) 555-6650 | (704) 555-2131 |

-- this is bruce's number
-- | (367) 555-5533 | (375) 555-8161 |

-- | (499) 555-9472 | (892) 555-8872 |
-- | (499) 555-9472 | (717) 555-1342 |
-- | (609) 555-5876 | (389) 555-5198 |
-- | (770) 555-1861 | (725) 555-3243 |
-- | (826) 555-1652 | (066) 555-9701 |
-- +----------------+----------------+

SELECT name FROM people WHERE phone_number = '(375) 555-8161';
-- Robin was the accomplice