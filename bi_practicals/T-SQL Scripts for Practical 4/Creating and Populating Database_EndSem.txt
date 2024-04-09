USE [StudentsDB]

-- Create table
CREATE TABLE EndSem (
    id INT PRIMARY KEY,
    RollNo INT,
    PhoneNumber BIGINT,
    BIMarks INT,
    NLPMarks INT,
    DLMarks INT,
    HPCMarks INT,
    SoftComputingMarks INT,
    DataScienceMarks INT,
    DAAMarks INT,
    TotalMarks INT,
    Grade CHAR(1),
    Percentage DECIMAL(5, 2)
);

-- Insert dummy values
DECLARE @counter INT = 1;
WHILE @counter <= 10000
BEGIN
    INSERT INTO EndSem (id, RollNo, PhoneNumber, BIMarks, NLPMarks, DLMarks, HPCMarks, SoftComputingMarks, DataScienceMarks, DAAMarks)
    VALUES (
        @counter,
        @counter,
        CAST(RAND() * 10000000000 AS BIGINT), -- Random phone number
        CAST(RAND() * 100 AS INT),
        CAST(RAND() * 100 AS INT),
        CAST(RAND() * 100 AS INT),
        CAST(RAND() * 100 AS INT),
        CAST(RAND() * 100 AS INT),
        CAST(RAND() * 100 AS INT),
        CAST(RAND() * 100 AS INT)
    );

    SET @counter = @counter + 1;
END;

-- Calculate TotalMarks, Grade, and Percentage
UPDATE EndSem
SET TotalMarks = BIMarks + NLPMarks + DLMarks + HPCMarks + SoftComputingMarks + DataScienceMarks + DAAMarks,
    Grade = CASE
                WHEN (BIMarks + NLPMarks + DLMarks + HPCMarks + SoftComputingMarks + DataScienceMarks + DAAMarks) >= 700 THEN 'A'
                WHEN (BIMarks + NLPMarks + DLMarks + HPCMarks + SoftComputingMarks + DataScienceMarks + DAAMarks) >= 600 THEN 'B'
                WHEN (BIMarks + NLPMarks + DLMarks + HPCMarks + SoftComputingMarks + DataScienceMarks + DAAMarks) >= 500 THEN 'C'
                WHEN (BIMarks + NLPMarks + DLMarks + HPCMarks + SoftComputingMarks + DataScienceMarks + DAAMarks) >= 400 THEN 'D'
                ELSE 'F'
            END,
    Percentage = ((BIMarks + NLPMarks + DLMarks + HPCMarks + SoftComputingMarks + DataScienceMarks + DAAMarks) / 700.0) * 100;

-- Display the table
SELECT * FROM EndSem;
