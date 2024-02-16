SELECT name FROM movies, stars, people WHERE movies.id = stars.movie_id AND people.id = stars.person_id AND movies.id IN
(SELECT movies.id FROM movies, stars, people WHERE movies.id = stars.movie_id AND people.id = stars.person_id AND people.name = "Kevin Bacon" and birth = 1958)
AND people.id NOT IN
(SELECT id FROM people WHERE name = "Kevin Bacon" and birth = 1958);