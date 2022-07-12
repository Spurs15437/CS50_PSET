SELECT DISTINCT(name) FROM people, ratings, movies, directors
WHERE movies.id = ratings.movie_id
AND movies.id = directors.movie_id
AND people.id = directors.person_id
AND rating >= 9.0;