# Car Service Management System

A comprehensive **Car Service Management System** built in C that manages users, appointments, service assignments, billing, and receipts. This project is designed for use in automotive service centers with three user roles: **Admin**, **Salesperson**, and **Customer**.

This README provides an overview of the system, features, usage instructions, and file structure.

---

## 📸 Screenshots

Below are some reference images from the application UI:

![Screenshot 1][(sediment://file_00000000bab872098979f7c609ad4d23)](https://github.com/asadullah-001/Car-Service-Management-System-/blob/main/main_menu.jpg)
![Screenshot 2][(sediment://file_00000000ddb47206b6089fc0c4a1fce6)](https://github.com/asadullah-001/Car-Service-Management-System-/blob/main/signup.jpg)
![Screenshot 3][(sediment://file_0000000014587206bfd5fdc49715f31b)](https://github.com/asadullah-001/Car-Service-Management-System-/blob/main/exit.jpg)

---

## 🚗 Features

### 🔐 User Management

* Customer sign‑up & login
* Admin login with predefined credentials
* Salesperson account creation (admin‑only)
* View/delete user accounts

### 🗓 Appointment Management

* Customers can book appointments
* View all appointments
* Delete and search appointments (admin)

### 🛠 Service Assignment

* Salespersons/admins can assign services to booked appointments
* Edit or delete assigned services
* Service pricing displayed with predefined list

### 💵 Billing System

* Generate bills with tax calculation
* Store billing history
* Print formatted receipts

### 📁 File-Based Storage

The system stores all info in text files:

* `users.txt` – user accounts
* `appointments.txt` – booked appointments
* `service_history.txt` – assigned services
* `billing.txt` – generated bills

---

## 🧱 File Structure

```
├── main.c
├── users.txt
├── appointments.txt
├── service_history.txt
├── billing.txt
├── parts_used.txt
├── service_list.txt
└── README.md
```

---

## ▶️ How to Run

1. Compile the program:

   ```bash
   gcc main.c -o car_service
   ```
2. Run the executable:

   ```bash
   ./car_service
   ```
3. Default admin credentials:

   * **Username:** admin
   * **Password:** 5410

---

## 👥 User Roles

### **Admin**

* Manage users
* Manage appointments
* Assign/edit/delete services
* View billing & generate receipts

### **Salesperson**

* View appointments
* Assign/edit/delete services
* Generate bills

### **Customer**

* Book appointments
* View own appointments

---

## 🧮 Service Pricing

Predefined services include:

* Oil Change — $50
* Car Wash — $30
* General Service — $120
* Interior Clean — $40
* Engine Service — $200

Tax: **10%** added to all services.

---

## 📝 Notes

* The program uses simple **file‑based storage** (no database).
* Compatible with Windows/macOS/Linux.
* Uses `cls/clear` to clean terminal screen.

---

## 🤝 Contributing

Feel free to fork this repo, create issues, and submit pull requests!

---

## 📜 License

This project is open‑source under the **MIT License**.

---

## ⭐ If you found this useful, give the repo a star!
