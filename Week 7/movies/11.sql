SELECT title FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people on stars.person_id = people.id
JOIN ratings on movies.id = ratings.movie_id
WHERE people.name = 'Chadwick Boseman'
ORDER BY ratings.rating DESC
LIMIT 5;