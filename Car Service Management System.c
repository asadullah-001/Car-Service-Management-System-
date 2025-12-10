#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>  // Added for tolower()

#define MAX_LEN 100
#define MAX_USERS 100
#define FILE_NAME "users.txt"
#define TEMP_FILE_NAME "temp_users.txt"
#define APPOINTMENT_FILE "appointments.txt"
#define TEMP_SERVICES_FILE "temp_services.txt"
#define SERVICE_LIST_FILE "service_list.txt"
#define SERVICE_HISTORY_FILE "service_history.txt"
#define PARTS_USED_FILE "parts_used.txt"
#define BILLING_FILE "billing.txt"

#define CLEAR_COMMAND "cls"
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "5410"

#define CUSTOMER "customer"
#define SALESPERSON "salesperson"

typedef struct {
    char serviceName[MAX_LEN];
    double price;
} ServicePrice;

ServicePrice servicesPricing[] = {
    {"Oil Change", 50.00},
    {"Car Wash", 30.00},
    {"General Service", 120.00},
    {"Interior Clean", 40.00},
    {"Engine Service", 200.00}
};

int servicesCount = 5;  // Number of services

void clearScreen() {
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen() {
    printf("\nPress Enter to continue...");
    while (getchar() != '\n'); // Clear input buffer
    getchar(); // Wait for Enter
}

int usernameExists(const char *username) {
    char file_user[MAX_LEN], file_pass[MAX_LEN], file_type[MAX_LEN];
    FILE *fp = fopen(FILE_NAME, "r");

    if (!fp) return 0;

    while (fscanf(fp, "%s %s %s", file_user, file_pass, file_type) != EOF) {
        if (strcmp(username, file_user) == 0) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void signUp() {
    char username[MAX_LEN], password[MAX_LEN];
    clearScreen();
    printf("\n=== CUSTOMER SIGN UP ===\n");
    while (1) {
        printf("Enter new username: ");
        scanf("%s", username);
        if (usernameExists(username)) {
            printf("Username already exists.\n");
        } else break;
    }
    printf("Enter new password: ");
    scanf("%s", password);
    FILE *fp = fopen(FILE_NAME, "a");
    if (!fp) {
        printf("Error opening file!\n");
        pauseScreen();
        clearScreen();
        return;
    }
    fprintf(fp, "%s %s %s\n", username, password, CUSTOMER);
    fclose(fp);
    printf("Signup successful!\n");
    pauseScreen();
    clearScreen();
}

int logIn(char *userType) {
    char username[MAX_LEN], password[MAX_LEN];
    char file_user[MAX_LEN], file_pass[MAX_LEN], file_type[MAX_LEN];
    int found = 0;

    clearScreen();
    printf("\n=== LOGIN ===\n");
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    // Check for admin login
    if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
        strcpy(userType, "admin");
        printf("Admin login successful!\n");
        pauseScreen();
        clearScreen();
        return 1;
    }

    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) {
        printf("No users found.\n");
        pauseScreen();
        clearScreen();
        return 0;
    }

    while (fscanf(fp, "%s %s %s", file_user, file_pass, file_type) != EOF) {
        if (strcmp(username, file_user) == 0 && strcmp(password, file_pass) == 0) {
            strcpy(userType, file_type);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (found) {
        printf("Login successful!\n");
    } else {
        printf("Invalid username or password.\n");
    }
    
    pauseScreen();
    clearScreen();
    return found;
}

void signUpSalesperson() {
    char username[MAX_LEN], password[MAX_LEN];
    clearScreen();
    printf("\n=== SALESPERSON SIGN UP ===\n");
    while (1) {
        printf("Enter new salesperson username: ");
        scanf("%s", username);
        if (usernameExists(username)) {
            printf("Username already exists.\n");
        } else break;
    }
    printf("Enter new password: ");
    scanf("%s", password);
    FILE *fp = fopen(FILE_NAME, "a");
    if (!fp) {
        printf("Error opening file!\n");
        pauseScreen();
        clearScreen();
        return;
    }
    fprintf(fp, "%s %s %s\n", username, password, SALESPERSON);
    fclose(fp);
    printf("Salesperson signup successful!\n");
    pauseScreen();
    clearScreen();
}

void viewAllUsers() {
    char file_user[MAX_LEN], file_pass[MAX_LEN], file_type[MAX_LEN];
    clearScreen();
    printf("\n=== ALL USERS ===\n");
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) {
        printf("No users found.\n");
        pauseScreen();
        clearScreen();
        return;
    }
    int index = 1;
    while (fscanf(fp, "%s %s %s", file_user, file_pass, file_type) != EOF) {
        printf("%d. Username: %s, Role: %s\n", index++, file_user, file_type);
    }
    fclose(fp);
    pauseScreen();
    clearScreen();
}

void deleteUser() {
    char username[MAX_LEN], password[MAX_LEN], type[MAX_LEN];
    char records[100][MAX_LEN * 3];
    int total = 0, choice;

    clearScreen();
    printf("\n=== DELETE USER ===\n");
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) {
        printf("No users found.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    printf("Registered Users:\n");
    while (fscanf(fp, "%s %s %s", username, password, type) != EOF) {
        if (strcmp(username, ADMIN_USERNAME) != 0) {
            sprintf(records[total], "%s %s %s", username, password, type);
            printf("%d. Username: %s | Type: %s\n", total + 1, username, type);
            total++;
        }
    }
    fclose(fp);

    if (total == 0) {
        printf("No users available to delete.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    printf("\nEnter the user number to delete (1-%d): ", total);
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        pauseScreen();
        clearScreen();
        return;
    }
    getchar();

    if (choice < 1 || choice > total) {
        printf("Invalid choice.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    char confirm;
    char *selectedUser = strtok(records[choice-1], " ");
    printf("\nAre you sure you want to delete user '%s'? (y/n): ", selectedUser);
    scanf(" %c", &confirm);
    getchar();

    if (tolower(confirm) != 'y') {
        printf("Deletion cancelled.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    fp = fopen(FILE_NAME, "w");
    if (!fp) {
        printf("Error opening file for writing.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    // Rewrite admin first if exists
    if (usernameExists(ADMIN_USERNAME)) {
        fprintf(fp, "%s %s admin\n", ADMIN_USERNAME, ADMIN_PASSWORD);
    }

    for (int i = 0; i < total; i++) {
        if (i != choice - 1) {
            fprintf(fp, "%s\n", records[i]);
        }
    }
    fclose(fp);

    printf("User deleted successfully.\n");
    pauseScreen();
    clearScreen();
}

void bookAppointment() {
    char name[MAX_LEN], date[MAX_LEN], vehicle[MAX_LEN];
    clearScreen();
    printf("\n=== BOOK APPOINTMENT ===\n");
    printf("Enter your name: "); 
    scanf("%s", name);
    printf("Enter vehicle model: "); 
    scanf("%s", vehicle);
    printf("Enter appointment date (dd-mm-yyyy): "); 
    scanf("%s", date);

    FILE *fp = fopen(APPOINTMENT_FILE, "a");
    if (!fp) {
        printf("Error booking appointment.\n");
        pauseScreen();
        clearScreen();
        return;
    }
    fprintf(fp, "%s %s %s\n", name, vehicle, date);
    fclose(fp);
    printf("Appointment booked successfully!\n");
    pauseScreen();
    clearScreen();
}

void viewAppointments() {
    char name[MAX_LEN], vehicle[MAX_LEN], date[MAX_LEN];
    int appointmentCount = 0;

    clearScreen();
    printf("\n=== APPOINTMENTS ===\n");
    FILE *fp = fopen(APPOINTMENT_FILE, "r");
    if (!fp) {
        printf("No appointments found.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    while (fscanf(fp, "%s %s %s", name, vehicle, date) != EOF) {
        printf("%d. Customer: %s, Vehicle: %s, Date: %s\n",
              ++appointmentCount, name, vehicle, date);
    }
    fclose(fp);

    if (appointmentCount == 0) {
        printf("\nNo appointments currently scheduled.\n");
    }
    
    printf("\nTotal appointments: %d\n", appointmentCount);
    pauseScreen();
    clearScreen();
}

void selectAppointmentAndService() {
    char name[MAX_LEN], vehicle[MAX_LEN], date[MAX_LEN];
    char records[100][MAX_LEN * 3];
    int total = 0, choice;
    
    clearScreen();
    printf("\n=== SELECT APPOINTMENT ===\n");
    FILE *fp = fopen(APPOINTMENT_FILE, "r");
    if (!fp) {
        printf("No appointments found.\n");
        pauseScreen();
        clearScreen();
        return;
    }
    
    printf("Select an appointment to work on:\n");
    while (fscanf(fp, "%s %s %s", name, vehicle, date) != EOF) {
        sprintf(records[total], "%s %s %s", name, vehicle, date);
        printf("%d. Customer: %s, Vehicle: %s, Date: %s\n", total + 1, name, vehicle, date);
        total++;
    }
    fclose(fp);

    if (total == 0) {
        printf("No appointments available.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    printf("Enter the appointment number (1-%d): ", total);
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        pauseScreen();
        clearScreen();
        return;
    }
    getchar();

    if (choice < 1 || choice > total) {
        printf("Invalid choice.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    clearScreen();
    printf("\n=== SELECT SERVICE ===\n");
    printf("Available Services:\n");
    for (int i = 0; i < servicesCount; i++) {
        printf("%d. %s - $%.2f\n", i + 1, servicesPricing[i].serviceName, servicesPricing[i].price);
    }
    
    printf("Choose a service to assign (1-%d): ", servicesCount);
    int serviceChoice;
    if (scanf("%d", &serviceChoice) != 1) {
        printf("Invalid input.\n");
        pauseScreen();
        clearScreen();
        return;
    }
    getchar();

    if (serviceChoice < 1 || serviceChoice > servicesCount) {
        printf("Invalid service selection.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    FILE *hist = fopen(SERVICE_HISTORY_FILE, "a");
    if (!hist) {
        printf("Error saving service assignment.\n");
        pauseScreen();
        clearScreen();
        return;
    }
    
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timeStr[50];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", t);
    
    fprintf(hist, "Appointment: %s | Service: %s | Date: %s\n", 
            records[choice - 1], servicesPricing[serviceChoice - 1].serviceName, timeStr);
    fclose(hist);
    
    printf("\nAssigned '%s' to appointment %d.\n", 
           servicesPricing[serviceChoice - 1].serviceName, choice);
    pauseScreen();
    clearScreen();
}

void deleteAppointment() {
    char name[MAX_LEN], vehicle[MAX_LEN], date[MAX_LEN];
    char records[100][MAX_LEN * 3];
    int total = 0, choice;

    clearScreen();
    printf("\n=== DELETE APPOINTMENT ===\n");
    FILE *fp = fopen(APPOINTMENT_FILE, "r");
    if (!fp) {
        printf("No appointments found.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    printf("Appointments:\n");
    while (fscanf(fp, "%s %s %s", name, vehicle, date) != EOF) {
        sprintf(records[total], "%s %s %s", name, vehicle, date);
        printf("%d. Customer: %s, Vehicle: %s, Date: %s\n", total + 1, name, vehicle, date);
        total++;
    }
    fclose(fp);

    if (total == 0) {
        printf("No appointments available to delete.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    printf("Enter the appointment number to delete (1-%d): ", total);
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        pauseScreen();
        clearScreen();
        return;
    }
    getchar();

    if (choice < 1 || choice > total) {
        printf("Invalid choice.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    char confirm;
    printf("\nAre you sure you want to delete this appointment? (y/n): ");
    scanf(" %c", &confirm);
    getchar();

    if (tolower(confirm) != 'y') {
        printf("Deletion cancelled.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    fp = fopen(APPOINTMENT_FILE, "w");
    if (!fp) {
        printf("Error saving changes.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    for (int i = 0; i < total; i++) {
        if (i != choice - 1) {
            fprintf(fp, "%s\n", records[i]);
        }
    }
    fclose(fp);

    printf("Appointment deleted successfully.\n");
    pauseScreen();
    clearScreen();
}

void searchAppointmentsByName() {
    char searchName[MAX_LEN];
    char name[MAX_LEN], vehicle[MAX_LEN], date[MAX_LEN];
    int found = 0;

    clearScreen();
    printf("\n=== SEARCH APPOINTMENTS ===\n");
    printf("Enter customer name to search: ");
    scanf("%s", searchName);
    getchar();

    FILE *fp = fopen(APPOINTMENT_FILE, "r");
    if (!fp) {
        printf("No appointments found.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    printf("\nSearch Results:\n");
    while (fscanf(fp, "%s %s %s", name, vehicle, date) != EOF) {
        if (strstr(name, searchName) != NULL) {
            printf("Customer: %s, Vehicle: %s, Date: %s\n", name, vehicle, date);
            found = 1;
        }
    }
    fclose(fp);

    if (!found) {
        printf("No appointments found for '%s'.\n", searchName);
    }
    
    pauseScreen();
    clearScreen();
}

void viewAssignedServices() {
    char line[512];
    clearScreen();
    printf("\n=== ASSIGNED SERVICES ===\n");
    
    FILE *fp = fopen(SERVICE_HISTORY_FILE, "r");
    if (!fp) {
        printf("No service history found.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    int hasServices = 0;
    int count = 1;
    
    while (fgets(line, sizeof(line), fp)) {
        printf("%d. %s", count++, line);
        hasServices = 1;
    }
    fclose(fp);

    if (!hasServices) {
        printf("No assigned services found.\n");
    }
    
    pauseScreen();
    clearScreen();
}

void deleteAssignedService() {
    char line[512];
    char appointments[100][512];
    int totalAppointments = 0, serviceChoice;

    clearScreen();
    printf("\n=== DELETE ASSIGNED SERVICE ===\n");
    
    FILE *fp = fopen(SERVICE_HISTORY_FILE, "r");
    if (!fp) {
        printf("No services assigned.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    printf("Assigned Services:\n");
    while (fgets(line, sizeof(line), fp) != NULL && totalAppointments < 100) {
        strcpy(appointments[totalAppointments], line);
        printf("%d. %s", totalAppointments + 1, line);
        totalAppointments++;
    }
    fclose(fp);

    if (totalAppointments == 0) {
        printf("No services assigned.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    printf("\nEnter the service number to delete (1-%d): ", totalAppointments);
    if (scanf("%d", &serviceChoice) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        pauseScreen();
        clearScreen();
        return;
    }
    getchar();

    if (serviceChoice < 1 || serviceChoice > totalAppointments) {
        printf("Invalid choice.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    char confirm;
    printf("\nAre you sure you want to delete this service? (y/n): ");
    scanf(" %c", &confirm);
    getchar();

    if (tolower(confirm) != 'y') {
        printf("Deletion cancelled.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    fp = fopen(SERVICE_HISTORY_FILE, "w");
    if (!fp) {
        printf("Error opening file for writing.\n");
        pauseScreen();
        clearScreen();
        return;
    }
    
    for (int i = 0; i < totalAppointments; i++) {
        if (i != serviceChoice - 1) {
            fprintf(fp, "%s", appointments[i]);
        }
    }
    fclose(fp);

    printf("Service deleted successfully.\n");
    pauseScreen();
    clearScreen();
}

void generateBill() {
    char line[512];
    char appointments[100][512];
    int totalAppointments = 0, serviceChoice;

    clearScreen();
    printf("\n=== GENERATE BILL ===\n");
    
    FILE *fp = fopen(SERVICE_HISTORY_FILE, "r");
    if (!fp) {
        printf("No services assigned to bill.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    printf("Assigned Services:\n");
    while (fgets(line, sizeof(line), fp) != NULL && totalAppointments < 100) {
        strcpy(appointments[totalAppointments], line);
        printf("%d. %s", totalAppointments + 1, line);
        totalAppointments++;
    }
    fclose(fp);

    if (totalAppointments == 0) {
        printf("No services to bill.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    printf("\nEnter the service number to generate bill (1-%d): ", totalAppointments);
    if (scanf("%d", &serviceChoice) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        pauseScreen();
        clearScreen();
        return;
    }
    getchar();

    if (serviceChoice < 1 || serviceChoice > totalAppointments) {
        printf("Invalid choice.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    char name[MAX_LEN], vehicle[MAX_LEN], date[MAX_LEN], service[MAX_LEN], timestamp[MAX_LEN];
    sscanf(appointments[serviceChoice - 1], "Appointment: %s %s %s | Service: %[^|] | Date: %[^\n]",
           name, vehicle, date, service, timestamp);

    // Trim whitespace from service name
    char *trimmedService = service;
    while (*trimmedService == ' ') trimmedService++;
    char *end = trimmedService + strlen(trimmedService) - 1;
    while (end > trimmedService && (*end == ' ' || *end == '\n')) *end-- = '\0';

    double price = 0.0;
    int found = 0;
    for (int i = 0; i < servicesCount; i++) {
        if (strcmp(trimmedService, servicesPricing[i].serviceName) == 0) {
            price = servicesPricing[i].price;
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Service price not found.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    double tax = price * 0.10;
    double total = price + tax;

    FILE *billFile = fopen(BILLING_FILE, "a");
    if (billFile) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        char timeStr[50];
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", t);
        
        fprintf(billFile, "========== BILL RECEIPT ==========\n");
        fprintf(billFile, "Bill Date: %s\n", timeStr);
        fprintf(billFile, "Customer: %s | Vehicle: %s | Appointment Date: %s\n", name, vehicle, date);
        fprintf(billFile, "Service: %s\n", trimmedService);
        fprintf(billFile, "Service Price: $%.2f\n", price);
        fprintf(billFile, "Tax (10%%): $%.2f\n", tax);
        fprintf(billFile, "----------------------------------\n");
        fprintf(billFile, "Total Amount: $%.2f\n", total);
        fprintf(billFile, "==================================\n\n");
        fclose(billFile);
    }

    printf("\n========== BILL RECEIPT ==========\n");
    printf("Customer Name: %s\n", name);
    printf("Vehicle Model: %s\n", vehicle);
    printf("Appointment Date: %s\n", date);
    printf("Service: %s\n", trimmedService);
    printf("----------------------------------\n");
    printf("Service Price: $%.2f\n", price);
    printf("Tax (10%%): $%.2f\n", tax);
    printf("----------------------------------\n");
    printf("Total Amount: $%.2f\n", total);
    printf("==================================\n");
    printf("\nBill generated and saved successfully.\n");
    pauseScreen();
    clearScreen();
}

void viewBillingHistory() {
    char line[512];
    clearScreen();
    printf("\n=== BILLING HISTORY ===\n");
    
    FILE *fp = fopen(BILLING_FILE, "r");
    if (!fp) {
        printf("No billing history found.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    int hasBills = 0;
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
        hasBills = 1;
    }
    fclose(fp);

    if (!hasBills) {
        printf("No bills generated yet.\n");
    }
    
    pauseScreen();
    clearScreen();
}

void printReceipt() {
    char line[512];
    char bills[100][512];
    int totalBills = 0;

    clearScreen();
    printf("\n=== PRINT RECEIPT ===\n");
    
    FILE *fp = fopen(BILLING_FILE, "r");
    if (!fp) {
        printf("No bills available to print.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    printf("Available Bills:\n\n");
    int billNumber = 1;
    char currentBill[2048] = "";

    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "==========", 10) == 0 && strlen(currentBill) > 0) {
            if (strstr(currentBill, "==========") != NULL) {
                strcpy(bills[totalBills], currentBill);
                totalBills++;
                currentBill[0] = '\0';
            }
        }
        strcat(currentBill, line);
    }
    
    if (strlen(currentBill) > 0) {
        strcpy(bills[totalBills], currentBill);
        totalBills++;
    }
    fclose(fp);

    if (totalBills == 0) {
        printf("No bills found.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    // Display bill dates
    for (int i = 0; i < totalBills; i++) {
        char *dateStart = strstr(bills[i], "Bill Date:");
        if (dateStart) {
            printf("%d. %s", i + 1, dateStart);
        }
    }

    printf("\nEnter bill number to print (1-%d): ", totalBills);
    int choice;
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        pauseScreen();
        clearScreen();
        return;
    }
    getchar();

    if (choice < 1 || choice > totalBills) {
        printf("Invalid choice.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    printf("\n========== RECEIPT PRINTOUT ==========\n");
    printf("%s", bills[choice - 1]);
    printf("\nReceipt printed successfully.\n");
    pauseScreen();
    clearScreen();
}

void viewServicePricing() {
    clearScreen();
    printf("\n========== SERVICE PRICING ==========\n");
    for (int i = 0; i < servicesCount; i++) {
        printf("%d. %-20s - $%.2f\n", i + 1, servicesPricing[i].serviceName, servicesPricing[i].price);
    }
    printf("\nNote: 10%% tax will be added to all services.\n");
    printf("=====================================\n");
    pauseScreen();
    clearScreen();
}

void editAssignedService() {
    char line[512];
    char appointments[100][512];
    int totalAppointments = 0, serviceChoice;

    clearScreen();
    printf("\n=== EDIT ASSIGNED SERVICE ===\n");
    
    FILE *fp = fopen(SERVICE_HISTORY_FILE, "r");
    if (!fp) {
        printf("No services assigned to edit.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    printf("Assigned Services:\n");
    while (fgets(line, sizeof(line), fp) != NULL && totalAppointments < 100) {
        strcpy(appointments[totalAppointments], line);
        printf("%d. %s", totalAppointments + 1, line);
        totalAppointments++;
    }
    fclose(fp);

    if (totalAppointments == 0) {
        printf("No services assigned to edit.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    printf("\nEnter the service number to edit (1-%d): ", totalAppointments);
    if (scanf("%d", &serviceChoice) != 1) {
        printf("Invalid input.\n");
        while (getchar() != '\n');
        pauseScreen();
        clearScreen();
        return;
    }
    getchar();

    if (serviceChoice < 1 || serviceChoice > totalAppointments) {
        printf("Invalid choice.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    // Parse the existing service record
    char name[MAX_LEN], vehicle[MAX_LEN], date[MAX_LEN], service[MAX_LEN], timestamp[MAX_LEN];
    sscanf(appointments[serviceChoice - 1], "Appointment: %s %s %s | Service: %[^|] | Date: %[^\n]",
           name, vehicle, date, service, timestamp);

    // Display current service information
    printf("\nCurrent Service Details:\n");
    printf("Customer: %s\n", name);
    printf("Vehicle: %s\n", vehicle);
    printf("Appointment Date: %s\n", date);
    printf("Current Service: %s\n", service);

    // Show available services
    printf("\nAvailable Services:\n");
    for (int i = 0; i < servicesCount; i++) {
        printf("%d. %s - $%.2f\n", i + 1, servicesPricing[i].serviceName, servicesPricing[i].price);
    }

    // Get new service choice
    printf("\nChoose new service (1-%d): ", servicesCount);
    int newServiceChoice;
    scanf("%d", &newServiceChoice);
    getchar();

    if (newServiceChoice < 1 || newServiceChoice > servicesCount) {
        printf("Invalid service selection.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    // Update the service record
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timeStr[50];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", t);
    
    sprintf(appointments[serviceChoice - 1],
            "Appointment: %s %s %s | Service: %s | Date: %s\n",
            name, vehicle, date, servicesPricing[newServiceChoice - 1].serviceName, timeStr);

    // Write all records back to file
    fp = fopen(SERVICE_HISTORY_FILE, "w");
    if (!fp) {
        printf("Error opening file for writing.\n");
        pauseScreen();
        clearScreen();
        return;
    }

    for (int i = 0; i < totalAppointments; i++) {
        fprintf(fp, "%s", appointments[i]);
    }
    fclose(fp);

    printf("\nService updated successfully.\n");
    pauseScreen();
    clearScreen();
}

int main() {
    int choice;
    char userType[MAX_LEN];

    while (1) {
        clearScreen();
        printf("\n=== CAR SERVICE MANAGEMENT SYSTEM ===\n");
        printf("1. Sign Up (Customer)\n");
        printf("2. Log In\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            pauseScreen();
            continue;
        }
        getchar();

        if (choice == 1) {
            signUp();
        } else if (choice == 2) {
            if (logIn(userType)) {
                if (strcmp(userType, "admin") == 0) {
                    int adminChoice;
                    while (1) {
                        clearScreen();
                        printf("\n=== ADMIN PANEL ===\n");
                        printf("1. View all users\n");
                        printf("2. Delete user\n");
                        printf("3. Sign Up Salesperson\n");
                        printf("4. View Appointments\n");
                        printf("5. Delete Appointment\n");
                        printf("6. Search Appointments\n");
                        printf("7. List & Select Services\n");
                        printf("8. View Assigned Services\n");
                        printf("9. Delete Assigned Services\n");
                        printf("10. Edit Assigned Services\n");
                        printf("11. View Service Pricing\n");
                        printf("12. Generate Bill\n");
                        printf("13. View Billing History\n");
                        printf("14. Print Receipt\n");
                        printf("15. Log out\n");
                        printf("Choose an option: ");
                        
                        if (scanf("%d", &adminChoice) != 1) {
                            printf("Invalid input.\n");
                            while (getchar() != '\n');
                            pauseScreen();
                            continue;
                        }
                        getchar();

                        if (adminChoice == 1) viewAllUsers();
                        else if (adminChoice == 2) deleteUser();
                        else if (adminChoice == 3) signUpSalesperson();
                        else if (adminChoice == 4) viewAppointments();
                        else if (adminChoice == 5) deleteAppointment();
                        else if (adminChoice == 6) searchAppointmentsByName();
                        else if (adminChoice == 7) selectAppointmentAndService();
                        else if (adminChoice == 8) viewAssignedServices();
                        else if (adminChoice == 9) deleteAssignedService();
                        else if (adminChoice == 10) editAssignedService();
                        else if (adminChoice == 11) viewServicePricing();
                        else if (adminChoice == 12) generateBill();
                        else if (adminChoice == 13) viewBillingHistory();
                        else if (adminChoice == 14) printReceipt();
                        else if (adminChoice == 15) { clearScreen(); break; }
                        else {
                            printf("Invalid choice.\n");
                            pauseScreen();
                        }
                    }
                } else if (strcmp(userType, CUSTOMER) == 0) {
                    int custChoice;
                    while (1) {
                        clearScreen();
                        printf("\n=== CUSTOMER MENU ===\n");
                        printf("1. Book Appointment\n");
                        printf("2. View Appointments\n");
                        printf("3. Log out\n");
                        printf("Choose an option: ");
                        
                        if (scanf("%d", &custChoice) != 1) {
                            printf("Invalid input.\n");
                            while (getchar() != '\n');
                            pauseScreen();
                            continue;
                        }
                        getchar();
                        
                        if (custChoice == 1) bookAppointment();
                        else if (custChoice == 2) viewAppointments();
                        else if (custChoice == 3) { clearScreen(); break; }
                        else {
                            printf("Invalid choice.\n");
                            pauseScreen();
                        }
                    }
                } else if (strcmp(userType, SALESPERSON) == 0) {
                    int spChoice;
                    while (1) {
                        clearScreen();
                        printf("\n=== SALESPERSON PANEL ===\n");
                        printf("1. View Appointments\n");
                        printf("2. Select Appointment and Add Service\n");
                        printf("3. View Assigned Services\n");
                        printf("4. Delete Assigned Services\n");
                        printf("5. Edit Assigned Services\n");
                        printf("6. View Service Pricing\n");
                        printf("7. Generate Bill\n");
                        printf("8. View Billing History\n");
                        printf("9. Print Receipt\n");
                        printf("10. Log out\n");
                        printf("Choose an option: ");
                        
                        if (scanf("%d", &spChoice) != 1) {
                            printf("Invalid input.\n");
                            while (getchar() != '\n');
                            pauseScreen();
                            continue;
                        }
                        getchar();
                        
                        if (spChoice == 1) viewAppointments();
                        else if (spChoice == 2) selectAppointmentAndService();
                        else if (spChoice == 3) viewAssignedServices();
                        else if (spChoice == 4) deleteAssignedService();
                        else if (spChoice == 5) editAssignedService();
                        else if (spChoice == 6) viewServicePricing();
                        else if (spChoice == 7) generateBill();
                        else if (spChoice == 8) viewBillingHistory();
                        else if (spChoice == 9) printReceipt();
                        else if (spChoice == 10) { clearScreen(); break; }
                        else {
                            printf("Invalid choice.\n");
                            pauseScreen();
                        }
                    }
                }
            }
        } else if (choice == 3) {
            printf("\nThank you for using the system. Goodbye!\n");
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
            pauseScreen();
        }
    }
    return 0;
}