SELECT title FROM movies
JOIN stars s ON movies.id = s.movie_id
JOIN people p ON s.person_id = p.id
JOIN ratings r ON r.movie_id = s.movie_id
WHERE p.name = 'Chadwick Boseman' ORDER BY rating DESC LIMIT 5;