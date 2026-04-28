#include <stdio.h>
#include <string.h>

// حجم المخزن 
#define SIZE 10 

// بناء هيكل المخزن الدائري
typedef struct {
    char buffer[SIZE];
    int head;
    int tail;
    int count;
} CircularBuffer;

// Initialization
void init(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

// Check Overflow condition
int isFull(CircularBuffer *cb) {
    return cb->count == SIZE;
}

// Check Underflow condition
int isEmpty(CircularBuffer *cb) {
    return cb->count == 0;
}

// تابع الكتابة في المخزن الدائري
void write(CircularBuffer *cb, char data) {
    if (isFull(cb)) {
        printf("\n[Buffer Overflow] Cannot write: '%c'\n", data);
        return;
    }
    cb->buffer[cb->tail] = data;
    cb->tail = (cb->tail + 1) % SIZE;
    cb->count++;
}

// تابع القراءة من المخزن الدائري
char read(CircularBuffer *cb) {
    if (isEmpty(cb)) {
        printf("\n[Buffer Underflow]\n");
        return '\0';
    }
    char data = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % SIZE;
    cb->count--;
    return data;
}

int main() {
    CircularBuffer cb;
    init(&cb);
    
    char name[100];
    char suffix[] = "CE-ESY";
    
    // إدخال الاسم
    printf("Enter your first name: ");
    scanf("%s", name); 
    
    // إضافة السلسلة النصية "CE-ESY" إلى الاسم
    strcat(name, suffix);
    printf("String to store: %s\n\n", name);
    
    // تخزين الناتج داخل المخزن الدائري حرفاً حرفاً
    printf("Writing to buffer...\n");
    for (int i = 0; i < strlen(name); i++) {
        write(&cb, name[i]);
    }
    
    // قراءة البيانات من المخزن وعرضها على الشاشة
    printf("\nReading from buffer: ");
    while (!isEmpty(&cb)) {
        char c = read(&cb);
        if (c != '\0') {
            printf("%c", c);
        }
    }
    printf("\n\n");
    
    // التأكد من أن المخزن فارغ بعد القراءة
    if (isEmpty(&cb)) {
        printf("Success: The buffer is now empty!\n");
    } else {
        printf("Error: The buffer is not empty.\n");
    }
    
    return 0;
}
