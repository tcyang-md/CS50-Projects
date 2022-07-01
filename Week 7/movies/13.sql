SELECT DISTINCT name FROM people
JOIN stars ON stars.person_id = people.id
JOIN movies ON movies.id = stars.movie_id
WHERE movies.id in
(SELECT movies.id FROM movies
join people on stars.person_id=people.id
join stars on stars.movie_id=movies.id
WHERE people.name = 'Kevin Bacon' AND people.birth = 1958)
AND people.name != "Kevin Bacon";