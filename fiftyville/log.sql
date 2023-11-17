-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Step 1 : identify reports crime
SELECT description FROM crime_scene_reports AS rp
WHERE rp.day = 28
AND rp.month = 7
AND rp.year = 2021
AND rp.street = 'Humphrey Street'
AND rp.description LIKE '%Duck%'
;
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

-- Step 2: Get information from interviewer
SELECT * FROM interviews
WHERE year = 2021
AND month = 7
AND day = 28
AND transcript LIKE '%bakery%';

-- Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
-- I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- Step 3: Get license_plate
SELECT license_plate FROM bakery_security_logs
WHERE year = 2021
AND month = 7
AND day = 28
AND hour = 10
AND minute >= 15
AND minute <= 25;

-- Step 4: Get account number from atm_transactions, then get list of person_id
SELECT account_number FROM atm_transactions
WHERE atm_location = 'Leggett Street'
AND transaction_type = 'withdraw'
AND year = 2021
AND month = 7
AND day = 28;

SELECT person_id FROM bank_accounts JOIN
(SELECT account_number FROM atm_transactions
WHERE atm_location = 'Leggett Street'
AND transaction_type = 'withdraw'
AND year = 2021
AND month = 7
AND day = 28) as ac
ON bank_accounts.account_number = ac.account_number;


-- Step 5: Get caller and receiver phone number
SELECT caller, receiver FROM phone_calls
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60;

-- Step 6: Get airport id
SELECT id FROM airports
WHERE city = 'Fiftyville'
;

-- Step 7: Get info of earliest flight on 29 July 2021 from airport id
SELECT id FROM flights
WHERE origin_airport_id = (SELECT id FROM airports
WHERE city = 'Fiftyville')
AND year = 2021
AND month = 7
AND day = 29
ORDER BY hour, minute
LIMIT 1;

-- Get the city thief escaped to => New York City
SELECT airports.city FROM flights
JOIN airports ON airports.id = flights.destination_airport_id
WHERE origin_airport_id = (SELECT id FROM airports
WHERE city = 'Fiftyville')
AND year = 2021
AND month = 7
AND day = 29
ORDER BY hour, minute
LIMIT 1;


-- Step 8: Get passport_number
SELECT passport_number FROM passengers
WHERE flight_id = (SELECT id FROM flights
WHERE origin_airport_id = (SELECT id FROM airports
WHERE city = 'Fiftyville')
AND year = 2021
AND month = 7
AND day = 29
ORDER BY hour, minute
LIMIT 1);

-- Step 9: Get name of thief => Bruce, accomplice => Robin
SELECT people.name AS thief, accomplice.name AS accomplice FROM people
JOIN
(SELECT person_id FROM bank_accounts JOIN
(SELECT account_number FROM atm_transactions
WHERE atm_location = 'Leggett Street'
AND transaction_type = 'withdraw'
AND year = 2021
AND month = 7
AND day = 28) as ac
ON bank_accounts.account_number = ac.account_number
) as person
ON person.person_id = people.id
JOIN (SELECT passport_number FROM passengers
WHERE flight_id = (SELECT id FROM flights
WHERE origin_airport_id = (SELECT id FROM airports
WHERE city = 'Fiftyville')
AND year = 2021
AND month = 7
AND day = 29
ORDER BY hour, minute
LIMIT 1)) passport
ON people.passport_number = passport.passport_number
JOIN (SELECT caller, receiver FROM phone_calls
WHERE year = 2021
AND month = 7
AND day = 28
AND duration < 60) AS phone_call
ON people.phone_number = phone_call.caller
JOIN (SELECT license_plate FROM bakery_security_logs
WHERE year = 2021
AND month = 7
AND day = 28
AND hour = 10
AND minute >= 15
AND minute <= 25) AS lp
ON people.license_plate = lp.license_plate
JOIN people AS accomplice
ON phone_call.receiver = accomplice.phone_number










