SELECT S1.title FROM
(SELECT title, movies.id FROM movies, stars, people WHERE name = "Helena Bonham Carter" AND people.id = stars.person_id AND stars.movie_id = movies.id) S1,
(SELECT title, movies.id FROM movies, stars, people WHERE name = "Johnny Depp" AND people.id = stars.person_id AND stars.movie_id = movies.id) S2
WHERE S1.id = S2.id;