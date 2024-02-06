#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define MONTH_MULTIPLIER 690
#define YEAR_MULTIPLIER 2280

typedef struct {
    int year, month, day;
    int value;
    char comment[4096];
} Reply;

typedef struct {
    int start;
    int end;
    double median;
    double mean;
    double maxDifference;
    int size;
    int *dates;
} Interval;

int isYearLeap (int year) {
    if (year % 4 == 0 && (year % 100 != 0 || (year % 400 == 0 && year % 4000 != 0))) {
        return 1;
    }
    return 0;
}

int isValidDate(int year, int month, int day) {
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1800 || year > 3000) return 0;
    if (day > 30 && (month == 4 || month == 6 || month == 9 || month == 11)) return 0;
    if (month == 2) {
        if (day > 29) return 0;
        if (day == 29 && !isYearLeap(year)) return 0;
    }
    return 1;
}

int isDateLater(int year, int month, int day, int lYear, int lMonth, int lDay){
    int firstDate = day + month*MONTH_MULTIPLIER + year*YEAR_MULTIPLIER;
    int laterDate = lDay + lMonth*MONTH_MULTIPLIER + lYear*YEAR_MULTIPLIER;
    if(laterDate >= firstDate){
        return 1;
    }
    return 0;
}

int compareIntervals(const void *a, const void *b) {
    double diff = ((Interval *)b)->maxDifference - ((Interval *)a)->maxDifference;
    if (fabs(diff) < DBL_EPSILON) {     // because C isn't as developed as java, we use limiter between 0 and EPSILON
        return 0;
    } else if (diff > 0) {
        return 1;
    } else {
        return -1;
    }
}

int compareMedian(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}
 
double calculateMedian(int *arr, int n) {
    qsort(arr, n, sizeof(int), compareMedian);
    if (n % 2 != 0) {
        return arr[n / 2];
    } else {
        return arr[(n - 1) / 2] < arr[n / 2] ? arr[(n - 1) / 2] : arr[n / 2];
    }
}

int countTotalDates(Reply replies[], int n, int y, int m, int d) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (replies[i].year == y &&
            replies[i].month == m &&
            replies[i].day == d) {
            count++;
        }
    }
    return count;
}

int countIntervalDates(int *dates, int n, int date) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (dates[i] == date){
            count++;
        }
    }
    return count;
}

int containsAllDates(Reply *replies, int replyCount, int start, int end, int *dates, int size) {
    int startDate = replies[start].day + replies[start].month * MONTH_MULTIPLIER + replies[start].year * YEAR_MULTIPLIER;
    int endDate = replies[end].day + replies[end].month * MONTH_MULTIPLIER + replies[end].year * YEAR_MULTIPLIER;
    int numberOfStartDates = countTotalDates(replies, replyCount, replies[start].year, replies[start].month, replies[start].day);
    int numberOfEndDates = countTotalDates(replies, replyCount, replies[end].year, replies[end].month, replies[end].day);
    if(numberOfStartDates == countIntervalDates(dates, size, startDate) && numberOfEndDates == countIntervalDates(dates,size,endDate)){
        return 1;
    }
    return 0;
}

int moreValues(Interval *intervals, int count){
    double biggestValue = intervals[0].maxDifference;
    int interval = 1;
    if(count == 1){
        return interval;
    }
    for(int i = 1; i < count; i++){
        if(intervals[i].maxDifference == biggestValue){
            interval++;
        }
    }
    return interval;
}

void freeInterval(Interval *intervals, int count){
    for(int i = 0; i < count; i++){
        free(intervals[i].dates);
    }
    free(intervals);
}

int intervalWithMoreDates(Interval *intervals, int count){
    size_t biggestSize = sizeof(intervals[0].dates);
    int index = 0;
    for(int i = 1; i < count; i++){
        size_t currentSize = sizeof(intervals[i].dates);
        if(currentSize > biggestSize){
            biggestSize = currentSize;
            index = i;
        }
    }
    return index;
}

int intervalWithLatestDate(Reply *replies, Interval *intervals, int count){
    int index = 0;
    int latestDate = replies[intervals[0].end].day + replies[intervals[0].end].month * MONTH_MULTIPLIER + replies[intervals[0].end].year*YEAR_MULTIPLIER;
    for(int i = 1; i < count; i++){
        int date = replies[intervals[i].end].day + replies[intervals[i].end].month * MONTH_MULTIPLIER + replies[intervals[i].end].year*YEAR_MULTIPLIER;
        if(date > latestDate){
            latestDate = date;
            index = i;
        }
    }
    return index;
}

int sameIntervalWithLatestDates(Reply *replies, Interval *intervals, int count){
    int num = 1;
    int latestDate = replies[intervals[0].end].day + replies[intervals[0].end].month * MONTH_MULTIPLIER + replies[intervals[0].end].year*YEAR_MULTIPLIER;
    for(int i = 1; i < count; i++){
        int date = replies[intervals[i].end].day + replies[intervals[i].end].month * MONTH_MULTIPLIER + replies[intervals[i].end].year*YEAR_MULTIPLIER;
        if(date == latestDate){
            num++;
        }
    }
    return num;
}

int main() {
    int y=-1;
    int m = 0;
    int d = 0;                  //very first date
    int minRequest;           // or request for ? / #
    Reply *replies = NULL;      //replies should be stored as global variable as permanent, # and ? results will be temporary
    int replyCount = 0;
    int chr;
    printf("Recenze:\n");
    while ((chr = fgetc(stdin)) != EOF) {
        if (chr == '+') {                   //here we adding values
            replies = (Reply*) realloc(replies,(replyCount+1)*sizeof(Reply));
            int year, month, day, baseValue;
            if(scanf(" %4d - %02d - %02d %i ", &year, &month, &day, &baseValue) != 4 || baseValue < 1){
                printf("Nespravny vstup.\n");
                free(replies);
                return 1;
            }
            if(!isValidDate(year, month, day)){
                printf("Nespravny vstup.\n");
                free(replies);
                return 1;
            }
            if (y == -1 || isDateLater(y, m, d, year, month, day)) {
                y = year;
                m = month;
                d = day;
                replies[replyCount].year = year;
                replies[replyCount].month = month;
                replies[replyCount].day = day;
            } else {
                printf("Nespravny vstup.\n");
                free(replies);
                return 1;
            }
            replies[replyCount].value = baseValue;

            while ((chr = fgetc(stdin)) != EOF && (chr == ' ' || chr == '\t')); //ignore characters and skip them
            int i = 0;
            while (chr != '\n' && chr != EOF) {
                if (i >= 4096 || chr == ' ' || chr == '\t') {
                    printf("Nespravny vstup.\n");
                    free(replies);
                    return 1;
                }
                replies[replyCount].comment[i++] = (char)chr;
                chr = fgetc(stdin);
            }
            replies[replyCount].comment[i] = '\0';
            replyCount++;
        } else if((chr == '?' || chr == '#')){            // load operators
            if(scanf("%i", &minRequest) != 1 || minRequest < 1){
                printf("Nespravny vstup.\n");
                free(replies);
                return 1;
            }
            if(replyCount == 0){
                printf("Nespravny vstup.\n");
                free(replies);
                return 1;
            }else if(replyCount == 1 && minRequest == 1){
                printf("%4d-%02d-%02d - %4d-%02d-%02d: %.6f %i\n",
                    replies[0].year, replies[0].month, replies[0].day,
                    replies[0].year, replies[0].month, replies[0].day,
                    (double)replies[0].value, replies[0].value);
                    if(chr == '?'){
                        printf("  %d: %s\n", replies[0].value, replies[0].comment);
                    }
                continue;
            }
            Interval *intervals = (Interval *)malloc((replyCount * (replyCount - 1)) / 2 * sizeof(Interval));
            int intervalCount = 0;
            int *allRatings = (int*) malloc(replyCount*sizeof(int));
            for(int i = 0; i < replyCount; i++){
                allRatings[i] = replies[i].value;
            }
            for (int i = 0; i < replyCount; i++) {      //firstly we chose all possible intervals
                int intervalSize = 1;
                double mean = replies[i].value;
                double median = replies[i].value;

                for (int j = i + 1; j < replyCount; j++) {
                    intervalSize++;
                    int *intervalRatings = (int *)malloc(intervalSize * sizeof(int));
                    for (int k = i; k <= j; k++) {
                        intervalRatings[k - i] = replies[k].value;
                    }

                    mean = (mean * (intervalSize - 1) + replies[j].value) / intervalSize;
                    median = calculateMedian(intervalRatings, intervalSize);
                    double difference = fabs(mean - median);
                    intervals[intervalCount].start = i;
                    intervals[intervalCount].end = j;
                    intervals[intervalCount].maxDifference = difference;
                    intervals[intervalCount].median = median;
                    intervals[intervalCount].mean = mean;
                    intervals[intervalCount].size = intervalSize;
                    intervals[intervalCount].dates = (int *)malloc(intervalSize * sizeof(int));
                    for (int k = i; k <= j; k++) {
                        intervals[intervalCount].dates[k - i] = replies[k].day +
                                                                 replies[k].month * MONTH_MULTIPLIER +
                                                                 replies[k].year * YEAR_MULTIPLIER;
                    }
                    intervalCount++;
                    free(intervalRatings);
                }
            }
            free(allRatings);
            qsort(intervals, intervalCount, sizeof(Interval), compareIntervals); //then we sort intervals by max difference
            int validIntervalCount = 0;
            for (int i = 0; i < intervalCount; i++) {   // firstly, we count all valid intervals, that meet our conditions (granilurar and number of replies)
                if (containsAllDates(replies, replyCount, intervals[i].start, intervals[i].end, intervals[i].dates, intervals[i].size) && intervals[i].size >= minRequest) {
                    validIntervalCount++;
                }
            }
            if(validIntervalCount == 0){
                printf("Neexistuje.\n");
                freeInterval(intervals, intervalCount);
                continue;
            }
            Interval *validIntervals = (Interval *)malloc(validIntervalCount * sizeof(Interval));
            int validIndex = 0;
            for (int i = 0; i < intervalCount; i++) {       // again validating, but now adding to another dynamic array.
                if (containsAllDates(replies, replyCount, intervals[i].start, intervals[i].end, intervals[i].dates, intervals[i].size) && intervals[i].size >= minRequest) {
                    validIntervals[validIndex++] = intervals[i];
                }
                free(intervals[i].dates);
                intervals[i].dates = NULL;
            }
            free(intervals);
            int maxIntervalCount = moreValues(validIntervals, validIntervalCount);
            Interval *maxIntervals = (Interval *)malloc(maxIntervalCount * sizeof(Interval)); //at last, we chose all intervals, that could have multiple maximal values
            for (int i = 0; i < maxIntervalCount; i++) {
                if (validIntervals[i].maxDifference == validIntervals[0].maxDifference) {
                    maxIntervals[i] = validIntervals[i];
                }
            }
            free(validIntervals);
            if(maxIntervalCount == 0){
                printf("Neexistuje.\n");
            } else if(maxIntervalCount == 1){
                printf("%4d-%02d-%02d - %4d-%02d-%02d: %.6f %i\n",
                    replies[maxIntervals[0].start].year, replies[maxIntervals[0].start].month, replies[maxIntervals[0].start].day,
                        replies[maxIntervals[0].end].year, replies[maxIntervals[0].end].month, replies[maxIntervals[0].end].day,
                        maxIntervals[0].mean, (int)maxIntervals[0].median);
                if(chr == '?'){
                    for(int j  = maxIntervals[0].start; j <= maxIntervals[0].end; j++){
                        printf("  %d: %s\n", replies[j].value, replies[j].comment);
                    }
                }
            } else {
                int numOfLateDates = sameIntervalWithLatestDates(replies, maxIntervals, maxIntervalCount);
                int intervalId;
                if(numOfLateDates == 1){
                    intervalId = intervalWithLatestDate(replies, maxIntervals, maxIntervalCount);
                } else {
                    intervalId = intervalWithMoreDates(maxIntervals, maxIntervalCount); //integer will be always greater than 1
                }
                printf("%4d-%02d-%02d - %4d-%02d-%02d: %.6f %i\n",
                    replies[maxIntervals[intervalId].start].year, replies[maxIntervals[intervalId].start].month, replies[maxIntervals[intervalId].start].day,
                    replies[maxIntervals[intervalId].end].year, replies[maxIntervals[intervalId].end].month, replies[maxIntervals[intervalId].end].day,
                    maxIntervals[intervalId].mean, (int)maxIntervals[intervalId].median);
                if(chr == '?'){
                    for(int j  = maxIntervals[intervalId].start; j <= maxIntervals[intervalId].end; j++){
                        printf("  %d: %s\n", replies[j].value, replies[j].comment);
                    }
                }
            }
            free(maxIntervals);
        } else if((chr != '\n' && chr != '\t' && chr != ' ')){
            printf("Nespravny vstup.\n");
            return 1;
        }
    }
    free(replies);
    return 0;
}
