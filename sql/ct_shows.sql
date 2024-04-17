CREATE TABLE shows (
	id INTEGER PRIMARY KEY,
	name VARCHAR NOT NULL,
	season TINYINT,
	episode TINYINT,
	status CHAR[2],
	boo BOOLEAN,
	blurb VARCHAR,
	category VARCHAR,
);
