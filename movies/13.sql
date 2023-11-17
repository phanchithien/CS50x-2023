SELECT people.name FROM stars
JOIN
(SELECT stars.movie_id FROM people
JOIN stars ON people.id = stars.person_id
WHERE people.name = 'Kevin Bacon' and people.birth = 1958)
AS kevin_movie
ON stars.movie_id = kevin_movie.movie_id
JOIN people ON stars.person_id = people.id
WHERE people.name != 'Kevin Bacon'
;
