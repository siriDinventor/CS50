SELECT  AVG(energy)
FROM songs
JOIN artists a ON artist_id = a.id
WHERE a.name = 'Drake';