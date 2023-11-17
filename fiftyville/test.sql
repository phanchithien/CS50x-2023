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
