SELECT DISTINCT(name)
FROM people JOIN directors d ON d.person_id = people.id
JOIN ratings r ON d.movie_id = r.movie_id
WHERE rating >= '9.0' LIMIT 10;