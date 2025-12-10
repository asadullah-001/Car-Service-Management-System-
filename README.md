# Car Service Management System

## Description

This is a console-based Car Service Management System implemented in C. It allows users to sign up, log in, book appointments, manage services, and handle billing for a car service center. The system supports different user roles: Admin, Customer, and Salesperson, each with specific functionalities.

The application uses text files for data persistence, such as storing user credentials, appointments, service history, and billing information.

## Features

- **User Authentication**:
  - Customer Sign Up
  - Salesperson Sign Up (Admin only)
  - Login for Admin, Customers, and Salespersons

- **Admin Panel**:
  - View all users
  - Delete users
  - Sign up salespersons
  - View, delete, and search appointments
  - Assign, view, delete, and edit services
  - View service pricing
  - Generate bills
  - View billing history
  - Print receipts

- **Customer Menu**:
  - Book appointments
  - View appointments

- **Salesperson Panel**:
  - View appointments
  - Assign services to appointments
  - View, delete, and edit assigned services
  - View service pricing
  - Generate bills
  - View billing history
  - Print receipts

- **Service Management**:
  - Predefined services with pricing (e.g., Oil Change, Car Wash)
  - Assign services to appointments
  - Edit or delete assigned services

- **Appointment Management**:
  - Book, view, search, and delete appointments

- **Billing**:
  - Generate bills based on services
  - View billing history
  - Print receipts

## Screenshots

### Main Menu
![Main Menu](main_menu.png)

### Customer Sign Up
![Customer Sign Up](signup.png)

### Login
![Login](login.png)

### Exit
![Exit](exit.png)

## Requirements

- C Compiler (e.g., GCC)
- Operating System: Windows (for `cls` command) or Unix-like (for `clear` command). The code handles both via macros.

## Installation

1. Clone the repository:
   ```
   git clone https://github.com/yourusername/car-service-management-system.git
   ```

2. Navigate to the project directory:
   ```
   cd car-service-management-system
   ```

3. Compile the code:
   ```
   gcc "Car Service Management System.c" -o car_service_system
   ```

## Usage

Run the executable:
- On Windows: `car_service_system.exe`
- On Unix: `./car_service_system`

Follow the on-screen prompts to navigate through the menus.

**Note**: Data is stored in text files in the same directory (e.g., `users.txt`, `appointments.txt`). Ensure write permissions.

Admin credentials:
- Username: admin
- Password: 5410

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request.

## License

This project is licensed under the MIT License.
