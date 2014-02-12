CREATE TABLE files (
    path TEXT NOT NULL,
    timestamp INTEGER NOT NULL,
    checksum TEXT NOT NULL,
    size INTEGER NOT NULL,
    newpath TEXT,
    changed INTEGER NOT NULL,
    updated INTEGER NOT NULL,
    renamed INTEGER NOT NULL,
    deleted INTEGER NOT NULL,
    PRIMARY KEY (path)
);
