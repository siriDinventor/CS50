-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT year, month, day, description, street FROM crime_scene_reports WHERE description LIKE '%duck%';
SELECT name, transcript
FROM interviews
WHERE year = '2021' AND month = '7' AND day = '28';


SELECT name FROM people p
JOIN bank_accounts b ON p.id = b.person_id
JOIN atm_transactions a ON b.account_number = a.account_number
WHERE atm_location = 'Leggett Street' AND year = '2021' AND month = '7' AND day = '28' AND transaction_type LIKE 'withdraw%';


SELECT license_plate FROM bakery_security_logs WHERE year ='2021' AND month = '7' AND day = '28';

SELECT DISTINCT people.name
FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE phone_calls.year = '2021' AND phone_calls.month = '7' AND phone_calls.day = '28' AND phone_calls.duration < 60;

SELECT DISTINCT people.name
FROM people
JOIN phone_calls ON people.phone_number = phone_calls.reciever
WHERE phone_calls.year = '2021' AND phone_calls.month = '7' AND phone_calls.day = '28' AND phone_calls.duration < 60;

SELECT name
FROM people p
JOIN bakery_security_logs b ON p.license_plate =  b.license_plate  WHERE year = '2021' AND month = '7' AND day = '28'  AND hour < '11';


SELECT DISTINCT p.name
FROM people p
JOIN phone_calls pc ON p.phone_number = pc.caller
JOIN bakery_security_logs bsl ON p.license_plate = bsl.license_plate
JOIN bank_accounts ba ON p.id = ba.person_id
JOIN atm_transactions atm ON ba.account_number = atm.account_number
WHERE
    pc.year = '2021' AND pc.month = '7' AND pc.day = '28' AND pc.duration < 60
    AND bsl.year = '2021' AND bsl.month = '7' AND bsl.day = '28'
    AND atm.atm_location = 'Leggett Street' AND atm.year = '2021' AND atm.month = '7' AND atm.day = '28' AND atm.transaction_type LIKE 'withdraw%'
    AND bsl.hour < 11;




SELECT DISTINCT p.name, bsl.activity, pc.receiver
FROM people p
JOIN phone_calls pc ON p.phone_number = pc.caller
JOIN bakery_security_logs bsl ON p.license_plate = bsl.license_plate
JOIN bank_accounts ba ON p.id = ba.person_id
JOIN atm_transactions atm ON ba.account_number = atm.account_number
JOIN passengers ON p.passport_number = passengers.passport_number
WHERE
    pc.year = '2021' AND pc.month = '7' AND pc.day = '28' AND pc.duration < 60
    AND bsl.year = '2021' AND bsl.month = '7' AND bsl.day = '28' AND bsl.minute < 25
    AND atm.atm_location = 'Leggett Street' AND atm.year = '2021' AND atm.month = '7' AND atm.day = '28' AND atm.transaction_type LIKE 'withdraw%'
    AND passengers.flight_id = 36;



+--------+
|  name  |
+--------+
| Taylor |
| Bruce  |
| Diana  |
+--------+




SELECT * FROM flights
WHERE flight
ORDER BY hour LIMIT 5;
 id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     |



SELECT DISTINCT name
FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE phone_calls.year = '2021' AND phone_calls.month = '7' AND phone_calls.day = '28';



SELECT DISTINCT name
FROM people
WHERE phone_number = '(375) 555-8161';



SELECT city
FROM airports WHERE id = '4';