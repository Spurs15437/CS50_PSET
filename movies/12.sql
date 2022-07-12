SELECT title FROM movies,stars,people
WHERE stars.movie_id = movies.id
AND stars.person_id = people.id
AND (name LIKE 'Johnny Depp' or name LIKE 'Helena Bonham Carter')
GROUP BY title
having count(title) = 2;