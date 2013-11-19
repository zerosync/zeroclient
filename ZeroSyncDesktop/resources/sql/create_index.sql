CREATE TABLE fileindex (
    path TEXT NOT NULL,
    operation TEXT NOT NULL,
    timestamp INTEGER NOT NULL,
    size INTEGER NOT NULL,
    newpath TEXT,
    checksum TEXT NOT NULL,
    PRIMARY KEY (path)
);
