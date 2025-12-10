# 🚗 Car Service Management System

A comprehensive command-line application for managing car service appointments, customer interactions, and billing operations. This system supports multiple user roles with distinct functionalities.

## 📋 Features

### 👥 User Management
- **Customer Sign Up/Login** - Register and authenticate customers
- **Salesperson Sign Up** - Admin can create salesperson accounts
- **Admin Panel** - Full system control with user management
- **Role-Based Access** - Different menus for Admin, Customer, and Salesperson

### 📅 Appointment Management
- **Book Appointments** - Customers can schedule service appointments
- **View Appointments** - All users can view scheduled appointments
- **Search Appointments** - Search by customer name
- **Delete Appointments** - Admin can remove appointments

### 🔧 Service Operations
- **Service Selection** - Assign services to appointments
- **Service Pricing** - Predefined service catalog with pricing
- **Service History** - Track all assigned services
- **Edit/Delete Services** - Modify or remove assigned services

### 💰 Billing System
- **Generate Bills** - Create detailed invoices with 10% tax
- **Billing History** - View all generated bills
- **Print Receipts** - Print formatted receipts
- **Automatic Calculation** - Price + tax calculations

## 👨‍💼 User Roles

### 1. **Admin**
- View/Delete users
- Create salesperson accounts
- Manage appointments
- Assign and edit services
- Generate and view bills
- Full system access

### 2. **Customer**
- Sign up for an account
- Book appointments
- View scheduled appointments

### 3. **Salesperson**
- View appointments
- Assign services to appointments
- Manage assigned services
- Generate bills and receipts
- View billing history

## 📁 File Structure

```
Car Service Management System/
├── Car Service Management System.c    # Main source code
├── users.txt                          # User credentials storage
├── appointments.txt                   # Appointment records
├── service_history.txt               # Assigned services log
├── billing.txt                       # Billing records
├── README.md                         # This file
└── Screenshots/                      # Program screenshots
    ├── Screenshot 2025-12-10 214815.jpg
    ├── Screenshot 2025-12-10 214919.jpg
    ├── Screenshot 2025-12-10 215028.jpg
    └── Screenshot 2025-12-10 215057.jpg
```

## 🚀 Getting Started

### Prerequisites
- GCC Compiler or any C compiler
- Windows/Linux/macOS system
- Basic terminal/command prompt knowledge

### Compilation
```bash
gcc "Car Service Management System.c" -o car_service_system
```

### Execution
```bash
./car_service_system      # Linux/macOS
car_service_system.exe    # Windows
```

### Default Admin Credentials
- **Username:** `admin`
- **Password:** `5410`

## 🛠️ Service Catalog

The system includes predefined services with pricing:

1. **Oil Change** - $50.00
2. **Car Wash** - $30.00
3. **General Service** - $120.00
4. **Interior Clean** - $40.00
5. **Engine Service** - $200.00

*Note: All services include 10% tax*

## 📸 Screenshots

### Main Menu
![Main Menu](Screenshots/Screenshot%202025-12-10%20214815.jpg)

### Customer Sign Up
![Customer Sign Up](Screenshots/Screenshot%202025-12-10%20214919.jpg)

### Successful Login
![Login Success](Screenshots/Screenshot%202025-12-10%20215028.jpg)

### Program Exit
![Exit Screen](Screenshots/Screenshot%202025-12-10%20215057.jpg)

## 🔒 Security Features

- Password protection for all accounts
- Admin-only user management
- Role-based menu access
- File-based data persistence
- Input validation and error handling

## 📊 Data Persistence

All data is stored in text files:
- **User data** → `users.txt`
- **Appointments** → `appointments.txt`
- **Service history** → `service_history.txt`
- **Billing records** → `billing.txt`

## 🐛 Error Handling

- Invalid input detection
- File operation error checking
- User existence validation
- Boundary condition checks
- Memory buffer overflow prevention

## 🔧 Technical Details

- **Language:** C
- **Paradigm:** Procedural Programming
- **Data Structures:** Arrays, Structures
- **File Handling:** Text file I/O operations
- **Platform:** Cross-platform (Windows/Linux/macOS)

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push to the branch
5. Open a Pull Request

## 📄 License

This project is open source and available for educational purposes.

## 👤 Author

**Car Service Management System**
- Developed as a comprehensive C programming project
- Demonstrates file handling, user management, and billing systems

## ⚠️ Notes

- This is a console-based application
- No graphical user interface
- Data is stored in plain text files
- For educational and demonstration purposes

## 🎯 Future Enhancements

Potential improvements could include:
- Database integration
- Graphical user interface
- Email notifications
- Advanced reporting
- Inventory management
- Customer feedback system

---

*For any queries or issues, please check the code documentation or create an issue in the repository.*
