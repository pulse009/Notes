DO $$ 
BEGIN
    IF NOT EXISTS (SELECT 1 FROM pg_database WHERE datname = 'notes') THEN
        CREATE DATABASE notes;
    END IF;
END $$;

-- DB connection
\c notes;

CREATE TABLE IF NOT EXISTS notes (
    id SERIAL PRIMARY KEY,
    note TEXT
);
