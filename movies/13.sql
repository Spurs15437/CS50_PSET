SELECT name FROM people, stars, movies
WHERE stars.movie_id = movies.id
AND stars.person_id = people.id
AND title IN (SELECT title FROM people , stars, movies
WHERE stars.movie_id = movies.id
AND stars.person_id = people.id
AND name = 'Kevin Bacon'
AND birth = 1958)
AND name != 'Kevin Bacon';