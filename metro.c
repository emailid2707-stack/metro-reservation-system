#include <stdio.h>
#include <string.h>

#define MAX 100

// Structure for booking
struct Booking {
    int bookingID;
    char name[50];
    char source[30];
    char destination[30];
    int tickets;
    int totalFare;
};

struct Booking bookings[MAX];
int bookingCount = 0;
int nextBookingID = 1;

// Function to display routes
void viewRoutes() {
    printf("\n----- Available Metro Routes -----\n");
    printf("1. Central  -> Airport   (Fare: Rs.50)\n");
    printf("2. Central  -> BusStand  (Fare: Rs.30)\n");
    printf("3. Airport  -> BusStand  (Fare: Rs.40)\n");
    printf("----------------------------------\n");
}

// Function to calculate fare
int calculateFare(char source[], char destination[]) {
    if ((strcmp(source, "Central") == 0 && strcmp(destination, "Airport") == 0) ||
        (strcmp(source, "Airport") == 0 && strcmp(destination, "Central") == 0))
        return 50;

    if ((strcmp(source, "Central") == 0 && strcmp(destination, "BusStand") == 0) ||
        (strcmp(source, "BusStand") == 0 && strcmp(destination, "Central") == 0))
        return 30;

    if ((strcmp(source, "Airport") == 0 && strcmp(destination, "BusStand") == 0) ||
        (strcmp(source, "BusStand") == 0 && strcmp(destination, "Airport") == 0))
        return 40;

    return -1; // Invalid route
}

// Function to book ticket
void bookTicket() {
    if (bookingCount >= MAX) {
        printf("\nBooking limit reached!\n");
        return;
    }

    struct Booking b;
    int farePerTicket;

    printf("\nEnter Passenger Name: ");
    scanf("%s", b.name);

    printf("Enter Source (Central/Airport/BusStand): ");
    scanf("%s", b.source);

    printf("Enter Destination (Central/Airport/BusStand): ");
    scanf("%s", b.destination);

    farePerTicket = calculateFare(b.source, b.destination);

    if (farePerTicket == -1) {
        printf("Invalid Route!\n");
        return;
    }

    printf("Enter Number of Tickets: ");
    scanf("%d", &b.tickets);

    b.totalFare = farePerTicket * b.tickets;
    b.bookingID = nextBookingID++;

    bookings[bookingCount++] = b;

    printf("\nBooking Successful!\n");
    printf("Booking ID: %d\n", b.bookingID);
    printf("Total Fare: Rs.%d\n", b.totalFare);
}

// Function to cancel ticket
void cancelTicket() {
    int id, found = 0;

    printf("\nEnter Booking ID to Cancel: ");
    scanf("%d", &id);

    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].bookingID == id) {
            found = 1;

            for (int j = i; j < bookingCount - 1; j++) {
                bookings[j] = bookings[j + 1];
            }

            bookingCount--;
            printf("Booking Cancelled Successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Booking ID Not Found!\n");
    }
}

// Function to view bookings
void viewBookings() {
    if (bookingCount == 0) {
        printf("\nNo Bookings Found!\n");
        return;
    }

    printf("\n------ Booking Details ------\n");
    for (int i = 0; i < bookingCount; i++) {
        printf("Booking ID: %d\n", bookings[i].bookingID);
        printf("Name: %s\n", bookings[i].name);
        printf("From: %s\n", bookings[i].source);
        printf("To: %s\n", bookings[i].destination);
        printf("Tickets: %d\n", bookings[i].tickets);
        printf("Total Fare: Rs.%d\n", bookings[i].totalFare);
        printf("-----------------------------\n");
    }
}

int main() {
    int choice;

    do {
        printf("\n===== METRO RESERVATION SYSTEM =====\n");
        printf("1. View Routes\n");
        printf("2. Book Ticket\n");
        printf("3. Cancel Ticket\n");
        printf("4. View Bookings\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewRoutes();
                break;
            case 2:
                bookTicket();
                break;
            case 3:
                cancelTicket();
                break;
            case 4:
                viewBookings();
                break;
            case 5:
                printf("\nThank You for using Metro Reservation System!\n");
                break;
            default:
                printf("\nInvalid Choice! Try Again.\n");
        }

    } while (choice != 5);

    return 0;
}

