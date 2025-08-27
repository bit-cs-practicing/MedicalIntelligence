#ifndef DAILYPATIENTLIMIT_H
#define DAILYPATIENTLIMIT_H

class DailyPatientLimit {
public:
    explicit DailyPatientLimit(int limit);

    int getValue() const;

private:
    int limit;
};

#endif // DAILYPATIENTLIMIT_H
