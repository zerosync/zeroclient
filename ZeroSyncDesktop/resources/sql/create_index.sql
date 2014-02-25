CREATE TABLE fileindex (
    state INTEGER NOT NULL,
    path TEXT NOT NULL,
    operation TEXT NOT NULL,
    timestamp INTEGER NOT NULL,
    size INTEGER NOT NULL,
    newpath TEXT,
    checksum TEXT NOT NULL,
    changed_self INTEGER NOT NULL,
    PRIMARY KEY (state, path, operation, timestamp, size, newpath, checksum)
);
