SELECT people.name FROM movies, people, stars WHERE title = "Toy Story" AND people.id == stars.person_id AND stars.movie_id = movies.id;