SELECT name1.title FROM
(SELECT movies.title, people.name FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE people.name = 'Bradley Cooper') AS name1
JOIN
(SELECT movies.title, people.name FROM movies
JOIN stars ON movies.id = stars.movie_id
JOIN people ON stars.person_id = people.id
WHERE people.name = 'Jennifer Lawrence') AS name2
ON name1.title = name2.title
;
